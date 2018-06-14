//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/NVMe/NvmeInt13/NvmeInt13.c 2     2/02/16 1:31a Karthikar $
//
// $Revision: 2 $
//
// $Date: 2/02/16 1:31a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/NVMe/NvmeInt13/NvmeInt13.c $
// 
// 2     2/02/16 1:31a Karthikar
// [TAG]  		EIP254245
// [Category]  	Bug Fix
// [Symptom]  	Static code analysis issues found in Aptio4 Nvme module
// [RootCause]  	In for loop comma operator is used instead of && for
// mutiple test conditions.
// [Solution]  	Replaced comma operator with &&.
// [Files]  		NvmeInt13.c
// 
// 1     9/04/14 7:56a Anandakrishnanl
// [TAG]  		EIP180861
// [Category]  	Improvement
// [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
// [Files]  		NvmeInt13.cif
// NvmeInt13.c
// NvmeInt13.h
// NvmeInt13.sdl
// NvmeInt13.mak
// NvmeInt13.inf
// NvmeInt13.dxs
// 
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:      NvmeInt13.c
//
// Description: Nvme Driver for Legacy Mode. It installs the Int13 
//              support for the Nvme devices 
//
//<AMI_FHDR_END>
//**********************************************************************

#include "Token.h"
#include "AmiDxeLib.h"
#include "NvmeInt13.h"
#include <Protocol/ComponentName.h>
#include <Protocol/LegacyBiosExt.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/PciIo.h>
#include <Protocol/BlockIo.h>

EFI_LEGACY_BIOS_EXT_PROTOCOL        *gBiosExtensions = NULL;
NVME_INT13_DATA                     *gNvmeInt13BinData = NULL;
AMI_NVME_LEGACY_PROTOCOL            gNvmeLegacyProtocol;

static EFI_GUID gAmiNvmeLegacyProtocolGuid 	        = AMI_NVME_LEGACY_PROTOCOL_GUID;

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeInt13EntryPoint
//
// Description:     NVMe INT13 driver entry point. Installs call back 
//                  notification on gAmiNvmeLegacyProtocolGuid installation.
//
// Input:
//    IN  EFI_HANDLE       ImageHandle,
//    IN  EFI_SYSTEM_TABLE *SystemTable
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
NvmeInt13EntryPoint (
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  NvmeInt13Handle=NULL;

    InitAmiLib(ImageHandle, SystemTable);

    Status = InitInt13RuntimeImage();
    if (EFI_ERROR(Status)) { 
        return Status;
    }

    gNvmeLegacyProtocol.AddNvmeLegacyDevice = NvmeInstallLegacyDevice;

    Status = pBS->InstallProtocolInterface (
                                    &NvmeInt13Handle,
                                    &gAmiNvmeLegacyProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    &gNvmeLegacyProtocol
                                    );

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:    InitInt13RuntimeImage
//
// Description:  Initialization of data structures and placement of runtime
//
// Input:
//         NONE
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
InitInt13RuntimeImage()
{
    EFI_STATUS  Status;
    VOID        *Image;
    UINTN       ImageSize = 0;


    //
    // Get the NVMe INT13 runtime image
    //
    Status = pBS->LocateProtocol(
        &gEfiLegacyBiosExtProtocolGuid, NULL, &gBiosExtensions);
    if (EFI_ERROR(Status)) return Status;

    Status = gBiosExtensions->GetEmbeddedRom(
        CSM16_MODULEID, CSM16_VENDORID, CSM16_NVME_RT_DID, &Image, &ImageSize);
    if (EFI_ERROR(Status)) return Status;

    //
    // Do the necessary RT data initialization here using Image before it is shadowed
    //..............................
    {
#pragma pack(push, 1)
        // Update NVMe SMI information
        typedef struct _NVME_SMM_RTS {
            UINT8   MiscInfo;
            UINT16  SmmAttr;
            UINT32  SmmPort;
            UINT32  SmmData;
        } NVME_SMM_RTS;

        static NVME_SMM_RTS NvmeSmmRt = {1, 0, SW_SMI_IO_ADDRESS, NVME_SWSMI};

        *(NVME_SMM_RTS*)((UINTN)Image + ((NVME_INT13_DATA*)Image)->NvmeSmmDataOffset) = NvmeSmmRt;
#pragma pack(pop)
    }

    // Copy image to shadow E000/F000 area
    (UINTN)gNvmeInt13BinData = gBiosExtensions->CopyLegacyTable(Image, (UINT16)ImageSize, 0x10, 2);

    TRACE((-1, "gNvmeInt13BinData : %lX\n", gNvmeInt13BinData));
    
    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CreateDeviceName
//
// Description: This function retrieves NVMe device name, copies it into
//              lower memory and returns a pointer to the string
//
// Input:
//    UINT8   DevIndex,
//    UINT8   *DevNameStringSrc,
//    UINT16  *StringDestinationSegment,
//    UINT16  *StringDestinationOffset,
//    UINT16  *MfgStringDestinationSegment,
//    UINT16  *MfgStringDestinationOffset
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CreateDeviceName (
    UINT8   DevIndex,
    UINT8   *DevNameStringSrc,
    UINT16  *StringDestinationSegment,
    UINT16  *StringDestinationOffset,
    UINT16  *MfgStringDestinationSegment,
    UINT16  *MfgStringDestinationOffset
)
{
    UINT8 *DevName = (gNvmeInt13BinData->NvmeMassI13Dev)[DevIndex].DeviceNameString;
    UINT8 i;

    //
    // Copy the string, compact it on the way (no more that one ' ' in a row)
    //
    for (i=0; i<31 && *DevNameStringSrc != 0; i++, DevNameStringSrc++)
    {
        if ((*DevNameStringSrc == 0x20) && (*(DevNameStringSrc-1) == 0x20)) continue;
        *DevName++ = *DevNameStringSrc;  // DevNameStringSrc incremented unconditionally
    }
    *DevName = 0;   // string terminator

    DevName = (gNvmeInt13BinData->NvmeMassI13Dev)[DevIndex].DeviceNameString;

    *StringDestinationSegment = (UINT16)(((UINTN)DevName & 0xf0000) >> 4);
    *StringDestinationOffset = (UINT16)((UINTN)DevName & 0xffff);

    *MfgStringDestinationSegment = (UINT16)(((UINTN)gNvmeInt13BinData->MfgGenericName & 0xf0000) >> 4);
    *MfgStringDestinationOffset = (UINT16)((UINTN)gNvmeInt13BinData->MfgGenericName & 0xffff);

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   CreateBbsEntry
//
// Description: This function takes the device index within NVMEMASS_INT13_DEV
//              list and prepares BBS entry for this device
//
// Input:
//    UINT8                       DevIndex,
//    IN NVME_LEGACY_MASS_DEVICE  *NvmeLegacyMassDevice,
//    OUT BBS_TABLE               *BbsEntry
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
CreateBbsEntry (
    UINT8                       DevIndex,
    IN NVME_LEGACY_MASS_DEVICE  *NvmeLegacyMassDevice,
    OUT BBS_TABLE               *BbsEntry
)
{
    EFI_STATUS  Status;
    UINT8       Handle;
    UINT8       DevAndSysType;
    UINT8       BaidDeviceType;
    BBS_STATUS_FLAGS    StatusFlags;

    ASSERT(DevIndex < NVMEDEVS_MAX_ENTRIES);

    if (gBiosExtensions == NULL) { 
        return EFI_NOT_FOUND;
    }

    pBS->SetMem(BbsEntry, sizeof(BBS_TABLE), 0);

    //
    // Get the HC PCI location
    //
    BbsEntry->Bus = (UINT32)(NvmeLegacyMassDevice->PciBDF >> 8);
    BbsEntry->Device = (UINT32)((NvmeLegacyMassDevice->PciBDF & 0xFF) >> 3);
    BbsEntry->Function = (UINT32)(NvmeLegacyMassDevice->PciBDF & 7);

    //
    // Update class/subclass information
    //
    BbsEntry->Class = PCI_CLASS_MASS_STORAGE;
    BbsEntry->SubClass = PCI_CLASS_MASS_STORAGE_SOLID_STATE;

    StatusFlags.Enabled = 1; StatusFlags.MediaPresent = 1;
    BbsEntry->StatusFlags = StatusFlags;  // Enabled, Unknown media

    //
    // Copy the device name string into low memory at gLegacyMemoryAddress, and
    // update the string pointer in BBS table entry
    //
    Status = CreateDeviceName(
                DevIndex,
                NvmeLegacyMassDevice->DevString,
                &BbsEntry->DescStringSegment,
                &BbsEntry->DescStringOffset,
                &BbsEntry->MfgStringSegment,
                &BbsEntry->MfgStringOffset
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) return Status;

    DevAndSysType = (SYSTYPE_ATA << 4)+DEVTYPE_SYS;
    Handle = (UINT8)NvmeLegacyMassDevice->LogicalAddress;

    switch (NvmeLegacyMassDevice->StorageType) {

        case NVME_MASS_DEV_HDD:
            BbsEntry->DeviceType = BBS_HARDDISK;
            BaidDeviceType = BAID_TYPE_HDD;
            Handle |= 0x80;
            BbsEntry->BootHandlerSegment = (UINT16)((UINTN)gNvmeInt13BinData >> 4);
            BbsEntry->BootHandlerOffset = gNvmeInt13BinData->BcvOffset + DevIndex*4;
            break;

        default:
            BbsEntry->DeviceType = BBS_UNKNOWN;
    }

    BbsEntry->InitPerReserved = ((UINT32)BaidDeviceType<<24)
                        +((UINT32)Handle<<8)
                        +(UINT32)DevAndSysType;

    *(UINTN*)(&BbsEntry->IBV1) = (UINTN)NvmeLegacyMassDevice->Handle;

    return EFI_SUCCESS;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   NvmeInstallLegacyDevice
//
// Description: This API is called by NVMe bus driver. The device is added into CSM16 
//               data area for legacy boot
//
// Input:
//          NVME_LEGACY_MASS_DEVICE *NvmeLegacyMassDevice
//
// Output:
//      EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:  None  
//
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
NvmeInstallLegacyDevice (
    NVME_LEGACY_MASS_DEVICE *NvmeLegacyMassDevice
)
{
    BBS_TABLE               BbsEntry;
    EFI_STATUS              Status;
    UINT8                   EntryNumber = 0xff;
    UINT8                   Index;
    NVME_MASS_DEV_INFO      *Device;
    NVME_DEV_PCI_LOCATION   *NvmePciDataOffset;

    TRACE((-1, "Installing NVMe INT13 device %lx\n", NvmeLegacyMassDevice));

    //
    // See if device is already in the list, if yes - return error.
    //
    for (Index = 0; Index < NVMEDEVS_MAX_ENTRIES; Index++) {
        if ((gNvmeInt13BinData->NvmeMassI13Dev)[Index].Handle == (UINT8)NvmeLegacyMassDevice->LogicalAddress) {
            ASSERT(FALSE);  // ERROR: Device already exists
            return EFI_INVALID_PARAMETER;
        }
    }
    //
    // Look for an empty slot in BcvLookupTable
    //
    for (Index=0; Index<NVMEDEVS_MAX_ENTRIES; Index++) {
        if  ((gNvmeInt13BinData->NvmeMassI13Dev)[Index].Handle == 0) { 
            break;
        }
    }
    
    ASSERT(Index<NVMEDEVS_MAX_ENTRIES);

    if (Index==NVMEDEVS_MAX_ENTRIES) {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = gBiosExtensions->UnlockShadow(0, 0, 0, 0);
    ASSERT_EFI_ERROR(Status);

    Status = CreateBbsEntry(Index, NvmeLegacyMassDevice, &BbsEntry);
    ASSERT_EFI_ERROR(Status);

    Status = gBiosExtensions->InsertBbsEntryAt(gBiosExtensions,
                                                &BbsEntry,
                                                &EntryNumber);
    ASSERT_EFI_ERROR(Status);

    //
    // Entry has been successfully added, update the lookup table
    //
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].Handle = (UINT8)NvmeLegacyMassDevice->LogicalAddress;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].BbsEntryNo = EntryNumber;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].DevBaidType = (UINT8)(BbsEntry.InitPerReserved>>24);

    //
    // Update device geometry related information
    //
    Device = (NVME_MASS_DEV_INFO*)NvmeLegacyMassDevice->DevInfo;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].NumHeads = Device->bNonLBAHeads;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].LBANumHeads = Device->bHeads;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].NumCylinders = Device->wNonLBACylinders;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].LBANumCyls = Device->wCylinders;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].NumSectors = Device->bNonLBASectors;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].LBANumSectors = Device->bSectors;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].BytesPerSector = Device->wBlockSize;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].LastLBA = Device->dMaxLba;
    (gNvmeInt13BinData->NvmeMassI13Dev)[Index].BpbMediaDesc = 0;

    // Update PCI Bus#
    NvmePciDataOffset = (NVME_DEV_PCI_LOCATION *)((UINTN)gNvmeInt13BinData + gNvmeInt13BinData->NvmePciDataOffset);
    NvmePciDataOffset[Index].Handle = (UINT8)NvmeLegacyMassDevice->LogicalAddress;
    NvmePciDataOffset[Index].PciBDF = NvmeLegacyMassDevice->PciBDF;
    
    Status = gBiosExtensions->LockShadow(0, 0);
    ASSERT_EFI_ERROR(Status);

    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
