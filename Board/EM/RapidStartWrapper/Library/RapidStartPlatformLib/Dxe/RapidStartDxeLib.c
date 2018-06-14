//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxeLib/RapidStartDxeLib.c 5     3/14/14 9:56a Joshchou $
//
// $Revision: 5 $
//
// $Date: 3/14/14 9:56a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxeLib/RapidStartDxeLib.c $
// 
// 5     3/14/14 9:56a Joshchou
// 
// 4     8/05/13 3:02a Joshchou
// [TAG]  		EIP130093
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System will hang at CP 0xA2 when plug in special mSATA SSD
// and Intel Rapid Start Technology support
// [RootCause]  	The buffer size isn't enough.
// [Solution]  	Modify the size when allocate.
// 
// 3     2/20/13 1:47a Bensonlai
// [TAG]  		EIP115468
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	[SharkBay][Rapid Start] Rapid Start can't work using GPT
// partition when enabled RAID mode
// [RootCause]  	Rapid Start can't work using GPT partition when enabled
// RAID mode
// [Files]  		RapidStartDxeLib.c
// 
// 2     12/07/12 1:25a Bensonlai
// [TAG]  		EIP108737
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When system in the RAID mode without the partition of the
// RapidStart,  RapidStart menu still show "No Valid Partition" in the
// setup.
// [RootCause]  	We didn't check the RAID mode.
// [Solution]  	Add the RAID mode for checking whether in the RAID mode.
// [Files]  		RapidStartDxeLib.c
// 
// 1     10/15/12 4:41a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Severity] Important
// [Description] Rename all IFFS sting to Rapid Start.
// [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
// 
// [Files]  		RapidStartDxeLib.cif
// RapidStartDxeLib.sdl
// RapidStartDxeLib.mak
// RapidStartDxeLib.c
// RapidStartDxeLib.h
// RapidStartDxeLib.inf
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartDxeLib.c
//
// Description: RapidStart Dxe Platform Library.
//
//<AMI_FHDR_END>
//**********************************************************************

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGlueDxe.h"

#include EFI_PROTOCOL_CONSUMER (BlockIo)
#include EFI_PROTOCOL_CONSUMER (DiskIo)
#include EFI_PROTOCOL_CONSUMER (RapidStartPlatformPolicy)
#include <SaAccess.h>
#include <PchAccess.h>
#include <UefiGpt.h>
#include <mbr.h>
#include "RapidStartDxeLib.h"
#endif

//AMIOVERRIDE_BEGIN  
#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))
#define SIGNATURE_64(A, B, C, D, E, F, G, H) \
   (SIGNATURE_32 (A, B, C, D) | ((UINT64) (SIGNATURE_32 (E, F, G, H)) << 32))
//AMIOVERRIDE_END  

#define RAPID_START_PART_TYPE_MBR 0x84  /* Hibernation partition -- APM 1.1f */
#define PCH_EFI_RAID_DRIVER_EXECUTION_GUID \
    { 0x99D5757C, 0xD906, 0x11E0, 0x8D, 0x78, 0x8D, 0xE4, 0x48, 0x24, 0x01, 0x9B };

EFI_GUID  gRapidStartGptGuid = RAPID_START_GPT_GUID;
UINT8     gDriveNum = 0x80;
EFI_GUID  gPchEfiRaidDriverExecutionGuid = PCH_EFI_RAID_DRIVER_EXECUTION_GUID;                             
BOOLEAN   gPchEfiRaidDriver = FALSE;

/**
  Search device path by specific Type and SubType

  @param[in,out] DevicePath  - A pointer to the device path
  @param[in] Type             - Device path type
  @param[in] SubType          - Device path SubType

  @retval EFI_DEVICE_PATH_PROTOCOL - Device path found and the pointer of device path returned
  @retval NULL                     - Specific device path not found
**/
STATIC
EFI_DEVICE_PATH_PROTOCOL *
SearchDevicePath (
  IN OUT   EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN       UINT8                    Type,
  IN       UINT8                    SubType
  )
{
  if (DevicePath == NULL) {
    return NULL;
  }

  while (!IsDevicePathEnd (DevicePath)) {
    if ((DevicePathType (DevicePath) == Type) && (DevicePathSubType (DevicePath) == SubType)) {
      return DevicePath;
    }

    DevicePath = NextDevicePathNode (DevicePath);
  }

  return NULL;
}

STATIC
EFI_STATUS
RetrieveSataPortNumberInt13 (
  IN OUT   UINT8                    *PortNumber,
  IN       BOOLEAN                   GPTDetect
  )
{
  UINTN                     Index;
  BOOLEAN                   CarryFlag;
  EFI_IA32_REGISTER_SET     Regs;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
  EFI_PHYSICAL_ADDRESS      TheRealModeBuffer;
  VOID*                     Int13Buffer = NULL;
  EFI_STATUS                Status;
  UINT8                     MaxDriveCount;

  Status = gBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
  ASSERT_EFI_ERROR(Status);

  // allocate conventional memory for int code
  TheRealModeBuffer = 0x00000000000FFFFF;
  Status = (gBS->AllocatePages)(
              AllocateMaxAddress,
              EfiBootServicesData,
              1,
              &TheRealModeBuffer);
  ASSERT_EFI_ERROR(Status);

  Int13Buffer = (VOID*)TheRealModeBuffer;
  // clear 4K page
  (gBS->SetMem)(Int13Buffer, 1024 * 4, 0);

  MaxDriveCount = *(UINT8*)0x475;
//####  DEBUG ((EFI_D_ERROR, "MaxDriveCount = %x\n", MaxDriveCount));

  for (Index = 0; Index < MaxDriveCount; Index++) {
    *(UINT16*)Int13Buffer = 0x004A;
    // Get physical hard disk information by ATA identify command
    Regs.X.DS = EFI_SEGMENT(Int13Buffer);
    Regs.X.SI = EFI_OFFSET(Int13Buffer);
    Regs.H.AH = 0x48;

    if (GPTDetect)
      Regs.H.DL = 0x80 + (UINT8)Index;
    else
      Regs.H.DL = gDriveNum;

    DEBUG ((EFI_D_ERROR, "Drive Number = %x\n", Regs.H.DL));

    LegacyBios->Int86 (LegacyBios, 0x13, &Regs);
    CarryFlag = (BOOLEAN)Regs.X.Flags.CF;
    if ((!CarryFlag) && (Regs.H.AH == 0)) {

      DEBUG ((EFI_D_ERROR, "0x28 = %x\n", *((UINT8*)(Int13Buffer)+0x28)));
      DEBUG ((EFI_D_ERROR, "0x29 = %x\n", *((UINT8*)(Int13Buffer)+0x29)));
      DEBUG ((EFI_D_ERROR, "0x2A = %x\n", *((UINT8*)(Int13Buffer)+0x2A)));
      DEBUG ((EFI_D_ERROR, "0x2B = %x\n", *((UINT8*)(Int13Buffer)+0x2B)));
      DEBUG ((EFI_D_ERROR, "0x3C = %x\n", *((UINT8*)(Int13Buffer)+0x3C)));

      if ((*((UINT8*)(Int13Buffer)+0x28) == 'R') && \
          (*((UINT8*)(Int13Buffer)+0x29) == 'A') && \
          (*((UINT8*)(Int13Buffer)+0x2A) == 'I') && \
          (*((UINT8*)(Int13Buffer)+0x2B) == 'D')) {
        switch (*((UINT8*)(Int13Buffer)+0x3c)) {
          case 0x01:
            *PortNumber = 0;
            break;
          case 0x02:
            *PortNumber = 1;
            break;
          case 0x04:
            *PortNumber = 2;
            break;
          case 0x08:
            *PortNumber = 3;
            break;
          case 0x10:
            *PortNumber = 4;
            break;
          case 0x20:
            *PortNumber = 5;
            break;
          default:
            *PortNumber = 0;
            break;
        }
      }
    }
    if (!GPTDetect) break;
  }
  if (Int13Buffer) (gBS->FreePages) (TheRealModeBuffer, 1);

  return Status;
}

/**
  Scan and check if GPT type RapidStart Store present.

  @param[in] Device        - Device handle
  @param[in] DevicePath    - A pointer to the device path
  @param[out] StoreSectors  - Size of RapidStart store partition
  @param[out] StoreLbaAddr  - Address of RapidStart store partition

  @retval EFI_SUCCESS   - GPT type RapidStart Store found.
  @retval EFI_NOT_FOUND - GPT type RapidStart Store not found.
**/
STATIC
EFI_STATUS
ScanForRapidStartGptPartition (
  IN     EFI_HANDLE                    Device,
  IN     EFI_DEVICE_PATH_PROTOCOL      *DevicePath,
  OUT    UINT32                        *StoreSectors,
  OUT    UINT64                        *StoreLbaAddr
  )
{
  EFI_STATUS                  Status;
  EFI_BLOCK_IO_PROTOCOL       *BlockIo;
  EFI_DISK_IO_PROTOCOL        *DiskIo;
  EFI_PARTITION_TABLE_HEADER  *PrimaryHeader;
  EFI_PARTITION_ENTRY         *PartitionEntry;
  UINT32                      Index;

  Status = gBS->HandleProtocol (Device, &gEfiBlockIoProtocolGuid, (VOID*)&BlockIo);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->HandleProtocol (Device, &gEfiDiskIoProtocolGuid, (VOID*)&DiskIo);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  //
  // Read the EFI Partition Table Header
  //
  PrimaryHeader = (EFI_PARTITION_TABLE_HEADER *) AllocatePool (BlockIo->Media->BlockSize);
  if (PrimaryHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     1 * BlockIo->Media->BlockSize,
                     BlockIo->Media->BlockSize,
                     (UINT8 *)PrimaryHeader
                     );
  if (EFI_ERROR (Status)) {
    FreePool (PrimaryHeader);
    return EFI_DEVICE_ERROR;
  }
//AMIOVERRIDE_BEGIN  
  if(PrimaryHeader->Header.Signature != EFI_PTAB_HEADER_ID ){//Check for "EFI PART" signature
	    FreePool (PrimaryHeader);
  return EFI_NOT_FOUND;
  }
//AMIOVERRIDE_END  
  //
  // Read the partition entry.
  //
//AMIOVERRIDE_BEGIN
  //  PartitionEntry = AllocatePool (PrimaryHeader->NumberOfPartitionEntries * sizeof (EFI_PARTITION_ENTRY));	
  PartitionEntry = AllocatePool (PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry);
//AMIOVERRIDE_END
  if (PartitionEntry == NULL) {
    FreePool (PrimaryHeader);
    return EFI_OUT_OF_RESOURCES;
  }
  Status = DiskIo->ReadDisk (
                     DiskIo,
                     BlockIo->Media->MediaId,
                     MultU64x32(PrimaryHeader->PartitionEntryLBA, BlockIo->Media->BlockSize),
                     PrimaryHeader->NumberOfPartitionEntries * PrimaryHeader->SizeOfPartitionEntry,
                     PartitionEntry
                     );
  if (EFI_ERROR (Status)) {
    FreePool (PrimaryHeader);
    FreePool (PartitionEntry);
    return EFI_DEVICE_ERROR;
  }

  //
  // Count the valid partition
  //
  for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++) {
    if (CompareGuid (&PartitionEntry[Index].PartitionTypeGUID, &gRapidStartGptGuid)) {
      *StoreLbaAddr = PartitionEntry[Index].StartingLBA;
      *StoreSectors = (UINT32) (PartitionEntry[Index].EndingLBA - PartitionEntry[Index].StartingLBA + 1);
       DEBUG (
        (EFI_D_INFO,
        "Found RapidStart GPT partition: start=%x size=%x\n",
        *StoreLbaAddr,
        *StoreSectors)
        );
      FreePool (PrimaryHeader);
      FreePool (PartitionEntry);
      return EFI_SUCCESS;
    }
  }

  FreePool (PrimaryHeader);
  FreePool (PartitionEntry);
  return EFI_NOT_FOUND;
}

/**
  Scan and check if MBR type RapidStart Store present.

  @param[in] Device         - Device handle
  @param[out] StoreSectors  - Size of RapidStart store partition
  @param[out] StoreLbaAddr  - Address of RapidStart store partition

  @retval EFI_SUCCESS   - MBR type RapidStart Store found.
  @retval EFI_NOT_FOUND - MBR type RapidStart Store not found.
**/
STATIC
EFI_STATUS
ScanForRapidStartMbrPartition (
  IN     EFI_HANDLE                    Device,
  OUT    UINT32                        *StoreSectors,
  OUT    UINT64                        *StoreLbaAddr
  )
{
  EFI_STATUS            Status;
  EFI_BLOCK_IO_PROTOCOL *BlockIo;
  UINTN                 Idx;
  UINT8                 OsType;

  MASTER_BOOT_RECORD    BootRecord;
  MASTER_BOOT_RECORD    *Mbr;
  MASTER_BOOT_RECORD    ExtBootRecord;
  MASTER_BOOT_RECORD    *ExtPart;
  EFI_LBA               Lba;

  Mbr     = &BootRecord;

  Status  = gBS->HandleProtocol (Device, &gEfiBlockIoProtocolGuid, (VOID *) &BlockIo);
  ASSERT_EFI_ERROR (Status);
  ASSERT (BlockIo != NULL);

  ///
  /// read the MBR
  ///
  Status = BlockIo->ReadBlocks (BlockIo, BlockIo->Media->MediaId, 0, sizeof (*Mbr), Mbr);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "Cannot read MBR\n"));
    return Status;
  }

  if (Mbr->Sig != MBR_SIGNATURE) {
    DEBUG ((EFI_D_ERROR, "Bad MBR\n"));
    if (!BlockIo->Media->RemovableMedia)
      gDriveNum++;
    return EFI_NOT_FOUND;
  }

  for (Idx = 0; Idx < NUM_MBR_PARTITIONS; Idx++) {
    OsType = Mbr->PartRec[Idx].OSType;

    ///
    /// ignore partitions whose OSType or Size is zero
    ///
    if ((OsType == 0) || (Mbr->PartRec[Idx].SizeInLba == 0)) {
      continue;
    }

    if (OsType == RAPID_START_PART_TYPE_MBR) {
      DEBUG (
        (EFI_D_INFO,
        "Found RapidStart MBR partition: start=%x size=%x\n",
        Mbr->PartRec[Idx].StartingLba,
        Mbr->PartRec[Idx].SizeInLba)
        );
      *StoreLbaAddr = Mbr->PartRec[Idx].StartingLba;
      *StoreSectors = Mbr->PartRec[Idx].SizeInLba;
      return EFI_SUCCESS;
    }

    // Now that a valid partition is found process it
    if ((Mbr->PartRec[Idx].OSType == EXTENDED_PARTITION) ||
        (Mbr->PartRec[Idx].OSType == WIN95_EXTENDED_PARTITION)) {

        ExtPart = &ExtBootRecord;

        // defines where to start reading the next MBR/partition
        // table from
        Lba = Mbr->PartRec[Idx].StartingLba;

        // loop through logical partitions: any number of
        // possible partitions
        while (TRUE) {

            // if the table points back to itself, exit
            if ( Lba == 0) {
                break;
            }

            // get Partition table from the first block of the device
            Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId,
                                             Lba, sizeof (*ExtPart), ExtPart);

            if (EFI_ERROR(Status)) {
                return Status;
            }

            // make sure this is a valid partition
            if (ExtPart->PartRec[0].OSType == NO_PARTITION) {
                break;
            }

            // check for problems that make the partition invalid
            if ((Lba + ExtPart->PartRec[0].SizeInLba) >
                 (Mbr->PartRec[Idx].StartingLba
                 + Mbr->PartRec[Idx].SizeInLba)) {

                break;
            }

            OsType = ExtPart->PartRec[0].OSType;

            if (OsType == RAPID_START_PART_TYPE_MBR) {
                DEBUG (
                        (EFI_D_INFO,
                        "Found RapidStart MBR partition: start=%x size=%x\n",
                        Mbr->PartRec[Idx].StartingLba,
                        Mbr->PartRec[Idx].SizeInLba)
                    );

                *StoreLbaAddr = ExtPart->PartRec[0].StartingLba + Lba;
                *StoreSectors = ExtPart->PartRec[0].SizeInLba;
                return EFI_SUCCESS;
            }

            // check to see if the next partition is an extended partition
            if ((ExtPart->PartRec[1].OSType != EXTENDED_PARTITION) &&
                (ExtPart->PartRec[1].OSType != WIN95_EXTENDED_PARTITION) ) {
                break;
            }

            // get set up for the next partition.  The Starting Lba
            //  address is a relative address inside the extended
            //  partition add the starting address of the extended
            //  partition to get the actual LBA where it starts
            Lba = ExtPart->PartRec[1].StartingLba
                      + Mbr->PartRec[Idx].StartingLba;
        }
    }
  }

  if (!BlockIo->Media->RemovableMedia)
   gDriveNum++;

  return EFI_NOT_FOUND;
}

/**
  Verify if this device path was RapidStart store partition. Get SATA port number if it was.

  @param[in] AhciMode          - TRUE means current SATA operation mode is AHCI, otherwise it is RAID
  @param[in,out] DevicePath   - A pointer to the device path
  @param[in,out] PortNumber   - Port Number connecting to this drive

  @retval EFI_SUCCESS     - This is RapidStart Store partition and Port Number retrieved successfully.
  @retval EFI_NOT_FOUND   - This is not RapidStart Store
**/
STATIC
EFI_STATUS
VerifyDevicePath (
  IN       BOOLEAN                  AhciMode,
  IN OUT   EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN OUT   UINT8                    *PortNumber
  )
{
  EFI_STATUS                Status;
  UINT8                     Index;

  Status = EFI_NOT_FOUND;

    DevicePath = SearchDevicePath (DevicePath, MESSAGING_DEVICE_PATH, MSG_SATA_DP);
    if ((SATA_DEVICE_PATH *) DevicePath != NULL) {
#if (EFI_SPECIFICATION_VERSION >= 0x0002000A)
      * PortNumber = (UINT8) ((SATA_DEVICE_PATH *) DevicePath)->HBAPortNumber;
#else
      *PortNumber = (UINT8) ((SATA_DEVICE_PATH *) DevicePath)->HbaPortNumber;
#endif
      Status = EFI_SUCCESS;
    }

    // Support Intel RST SATA UEFI Driver
    if (gPchEfiRaidDriver) {
      for (Index = 0; Index < 6; Index++) {
        if (*PortNumber & (1 << Index)) {
          *PortNumber = Index;
          break;
        }
      }
    }


  if (Status == EFI_SUCCESS) {
    DEBUG ((EFI_D_INFO, "Port number=%X\n", *PortNumber));
  }

  return Status;
}

/**
  Look through all device handles to detect if any GPT/MBR type RapidStart Store present

  @param[in] AhciMode         - TRUE means current SATA operation mode is AHCI, otherwise it is RAID
  @param[in] RapidStartPolicy - RapidStart Platform Policy protocol
  @param[out] StoreSectors     - Size of RapidStart store partition
  @param[out] StoreLbaAddr     - Address of RapidStart store partition
  @param[out] StoreSataPort    - Port number for RapidStart store partition

  @retval EFI_SUCCESS   - RapidStart Store found
  @retval EFI_NOT_FOUND - RapidStart Store not found
**/
STATIC
EFI_STATUS
DetectRapidStartPartition (
  IN     BOOLEAN                              AhciMode,
  IN     RAPID_START_PLATFORM_POLICY_PROTOCOL *RapidStartPolicy,
  OUT    UINT32                               *StoreSectors,
  OUT    UINT64                               *StoreLbaAddr,
  OUT    UINT8                                *StoreSataPort
  )
{
  EFI_STATUS                Status;
  UINTN                     HandleCount;
  EFI_HANDLE                *HandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     Index;

  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &HandleCount, &HandleBuffer);
  if (!EFI_ERROR (Status)) {
    //
    // Loop through all the device handles that support the BLOCK_IO Protocol
    //
    for (Index = 0; Index < HandleCount; Index++) {
      Status = gBS->HandleProtocol (HandleBuffer[Index], &gEfiDevicePathProtocolGuid, (VOID *) &DevicePath);
      if (EFI_ERROR (Status) || DevicePath == NULL) {
        continue;
      }

      if (VerifyDevicePath (AhciMode, DevicePath, StoreSataPort) == EFI_SUCCESS || (AhciMode == 0)) { //Raid mode
        Status = ScanForRapidStartGptPartition (HandleBuffer[Index], DevicePath, StoreSectors, StoreLbaAddr);
        if (Status == EFI_SUCCESS) {
          if ( (!AhciMode) && (!gPchEfiRaidDriver) ) RetrieveSataPortNumberInt13(StoreSataPort, TRUE);
          DEBUG ((EFI_D_INFO, "Found Gpt RapidStart Store on SATA port=%d\n", *StoreSataPort));
          break;
        }
        Status = ScanForRapidStartMbrPartition (HandleBuffer[Index], StoreSectors, StoreLbaAddr);
        if (Status == EFI_SUCCESS) {

        if ( (!AhciMode) && (!gPchEfiRaidDriver) ) RetrieveSataPortNumberInt13(StoreSataPort, FALSE);

          DEBUG ((EFI_D_INFO, "Found Mbr RapidStart Store on SATA port=%d\n", *StoreSataPort));
          break;
        }
      }
    }

    FreePool (HandleBuffer);
  }

  return Status;
}

/**
  Search if any type of RapidStart Store partition present

  @param[in] RapidStartPolicy  - RapidStart Platform Policy protocol
  @param[out] StoreSectors     - Size of RapidStart store partition
  @param[out] StoreLbaAddr     - Address of RapidStart store partition
  @param[out] StoreSataPort    - Port number for RapidStart store partition

  @retval EFI_SUCCESS   - GPT or MBR type RapidStart Store found
  @retval EFI_NOT_FOUND - GPT or MBR type RapidStart Store not found
**/
EFI_STATUS
SearchRapidStartStore (
  IN     RAPID_START_PLATFORM_POLICY_PROTOCOL *RapidStartPolicy,
  OUT    UINT32                               *StoreSectors,
  OUT    UINT64                               *StoreLbaAddr,
  OUT    UINT8                                *StoreSataPort
  )
{
  BOOLEAN     AhciMode;
  EFI_STATUS  Status;
  VOID        *Empty;

  *StoreSectors = 0;
  *StoreLbaAddr = 0;
  *StoreSataPort = 0;

  //
  // Get current SATA operation mode (only AHCI or RAID mode is supported)
  //
  AhciMode = (MmioRead8 (
                MmPciAddress (
                0,
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_SATA,
                PCI_FUNCTION_NUMBER_PCH_SATA,
                R_PCH_SATA_SUB_CLASS_CODE)
                ) == V_PCH_SATA_SUB_CLASS_CODE_AHCI);

  Status = gBS->LocateProtocol(&gPchEfiRaidDriverExecutionGuid, NULL, &Empty);
  if (Status == EFI_SUCCESS) gPchEfiRaidDriver = TRUE;

  Status = DetectRapidStartPartition (AhciMode, RapidStartPolicy, StoreSectors, StoreLbaAddr, StoreSataPort);

  return Status;
}

/**
  Generate RapidStart Store UID

  @retval UINT64 as RapidStart Store UID
**/
UINT64
GenerateRapidStartStoreUid (
  VOID
  )
{
  UINT64  Uid;
  UINT32  HpetBase;
  UINT32  HpetSetting;

  Uid         = AsmReadTsc ();

  HpetSetting = MmioRead32 (PCH_RCRB_BASE + R_PCH_RCRB_HPTC);
  if (HpetSetting & B_PCH_RCRB_HPTC_AE) {
    HpetBase = R_PCH_PCH_HPET_CONFIG + (HpetSetting & B_PCH_RCRB_HPTC_AS) * 0x1000;
    Uid ^= (LShiftU64 ((*(UINT64 *) (UINTN) (HpetBase + 0xF0)), 32));
  } else {
    //
    // Use certain random memory content as part of UID.
    //
    Uid ^= (LShiftU64 ((*(UINT64 *) (UINTN) (0xF5C00)), 32));
  }

  return Uid;
}

VOID
EnableHibernate (
  VOID
  )
/*++

Routine Description:

  Re-enable Hibernation when RapidStart enabled but RapidStart Store not present.

Arguments:

  None

Returns:

  None

--*/
{
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
