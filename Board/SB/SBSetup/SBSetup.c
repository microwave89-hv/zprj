//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBSetup/SBSetup.c 13    1/29/15 4:47a Mirayang $
//
// $Revision: 13 $
//
// $Date: 1/29/15 4:47a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBSetup/SBSetup.c $
// 
// 13    1/29/15 4:47a Mirayang
// [TAG]  		EIP20069
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Add JMB36X module SATA setup status error
// [RootCause]  	SBSetup.c is incomplete to difference betwenn device 28
// and 31.
// [Solution]  	Determine device 28 and 31.
// 
// 12    7/10/14 7:09a Mirayang
// [TAG]  		EIP176980
// [Category]  	Improvement
// [Description]  	Change "#else if" to "#elif"
// 
// 11    7/15/13 3:59a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update LPT-LP steeping.
// [Files]  		SBSetup.c
// 
// 10    7/03/13 8:04a Scottyang
// [TAG]  		EIP124410
// [Category]  	Improvement
// [Description]  	Implement SMBIOS type 88h for CRID.
// [Files]  		SBDxe.c, SB.sdl, SB.sd, SBSetup.c, SBSetup.sdl
// 
// 9     4/25/13 5:59a Scottyang
// [TAG]  		EIP121889
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Sata device will show at wrong port.
// [RootCause]  	The RC will disable sata controller when no device
// connect.
// [Solution]  	If Sata controller D31:F2 is disable then read data form
// sata controller D31:F5.
// [Files]  		SBSetup.c
// 
// 8     4/25/13 2:30a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Update LPT C0 stepping and separate stepping between
// LPT and LPT-LP.
// [Files]  		SBSetup.c
// 
// 7     2/27/13 1:39a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Correct PCH LP B1 stepping.
// [Files]  		SBSetup.c
// 
// 6     1/28/13 3:03a Scottyang
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Create PCH Sku fot LPT-LP at setup.
// 
// 5     12/12/12 9:19a Scottyang
// Update C0 stepping
// 
// 4     7/27/12 6:06a Victortu
// [TAG]           None
// [Category]      Improvement
// [Description]   Support Server/Workstation PCH ID. Please set
// "PCH_SVR_WS_ID_SUPPORT".
// [Files]         SBSetup.c, PchRegs.h, Pch.sdl
// 
// [TAG]           None
// [Category]      Improvement
// [Description]   Update to support ULT Platform.
// [Files]         SB.H, SB.mak, SB.sdl, SB.sd, SBSetup.c,
// AcpiModeEnable.c, SBDxe.c, SBPEI.c, SBSMI.c, SleepSmi.c,
// SmiHandlerPorting.c, SmiHandlerPorting2.c, SBPPI.h, Pch.sdl
// 
// 3     5/14/12 6:00a Victortu
// [TAG]           None 
// [Category]      Improvement 
// [Description]   Add PCH Device ID 0x8C40 to support WorkStation C228.
// [Files]         SBSetup.c
// 
// 2     2/20/12 4:19a Yurenlai
// [TAG]         None
// [Category]    Improvement
// [Description] Update PCH divice IDs by LPT RefCode rev.0.5.1.
// [Files]       SBSetup.c
// 
// 1     2/08/12 8:23a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBSetup.c
//
// Description: South Bridge Setup Routines
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include "Sb.h"
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Protocol\PciIo.h>
#include <Protocol\DevicePath.h>
#include <protocol\BlockIo.h>
#include <Protocol\PDiskInfo.h>
#include <Protocol\PIDEController.h>
#include <Protocol\PIDEBus.h>
#include <Protocol\PciRootBridgeIo.h>
#include <PchInfo\PchInfo.h>
#include <Protocol\SBPlatformData.h>

#define LEFT_JUSTIFY  0x01
#define PREFIX_SIGN   0x02
#define PREFIX_BLANK  0x04
#define COMMA_TYPE    0x08
#define LONG_TYPE     0x10
#define PREFIX_ZERO   0x20

#define DXE_DEVICE_DISABLED  0
#define DXE_DEVICE_ENABLED   1

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

#define CHARACTER_NUMBER_FOR_VALUE              30
#define _48_BIT_ADDRESS_FEATURE_SET_SUPPORTED   0x0400
#define ATAPI_DEVICE                            0x8000
typedef enum {
  EfiCompatibility,
  EfiEnhancedMode
  } EFI_SATA_MODE;

typedef struct {
  UINT16      DeviceId;
  CHAR8       *SkuName;
} AMI_PCH_DID_SKUNAME;

EFI_GUID gEfiDevicePathProtocolGuid       = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gEfiPciRootBridgeIoProtocolGuid  = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
EFI_GUID gEfiDiskInfoProtocolGuid         = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID gEfiPchInfoProtocolGuid          = EFI_PCH_INFO_PROTOCOL_GUID;

STRING_REF gSATA[6] = {
  STRING_TOKEN(STR_SATA0_NAME),
  STRING_TOKEN(STR_SATA1_NAME),
  STRING_TOKEN(STR_SATA2_NAME),
  STRING_TOKEN(STR_SATA3_NAME),
  STRING_TOKEN(STR_SATA4_NAME),
  STRING_TOKEN(STR_SATA5_NAME)
};
STRING_REF gSOFTPRES[6] = {
  STRING_TOKEN(STR_SATA0_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA1_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA2_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA3_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA4_SOFT_PRESERVE_STATUS),
  STRING_TOKEN(STR_SATA5_SOFT_PRESERVE_STATUS)
};

UINT32
GetNumTenthsOfGB (
  UINT32 RemainderBytesOfGB
  );


// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AsciiToUnicode
//
// Description: 
//
// Inpuut:      IN  CHAR8     *AsciiString,
//              OUT CHAR16    *UnicodeString
//
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID AsciiToUnicode (
  IN  CHAR8     *AsciiString,
  OUT CHAR16    *UnicodeString
  )
{
  UINT8 Index = 0;

  while (AsciiString[Index] != 0) {
    UnicodeString[Index] = (CHAR16) AsciiString[Index];
    Index++;
  }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SwapEntries
//
// Description: 
//
// Inpuut:      IN CHAR8    *Data,
//              IN UINT16   Size
//
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SwapEntries (
  IN CHAR8    *Data,
  IN UINT16   Size
)
{
  UINT16  Index;
  CHAR8   Temp8;

  for (Index = 0; (Index+1) < Size; Index+=2) {
    Temp8           = Data[Index];
    Data[Index]     = Data[Index + 1];
    Data[Index + 1] = Temp8;
  }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitSBStrings
//
// Description: Initializes South Bridge Setup String
//
// Inpuut:      HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
// Notes:       PORTING REQUIRED
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitSBStrings(IN EFI_HII_HANDLE HiiHandle, IN UINT16 Class)
{
  EFI_STATUS                      Status;
  PCI_DEVICE_PATH                 *PciDevicePath;
  CHAR8                           *NewString;
  CHAR8                           *SoftPres;
  UINT8                           Index;
  volatile UINT16                 *pAddress;
  UINT16                          SataP0P1Status;
  UINT16                          SataP4P5Status;
  UINT16                          AhciModePortStatus;
  UINT16                          SataMode;
  UINTN                           HandleCount;
  EFI_HANDLE                      *HandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL        *DevicePathNode;
  EFI_DISK_INFO_PROTOCOL          *DiskInfo;
  UINT32                          SataPortIndex, IdeChannel;
  IDENTIFY_DATA                   *IdentifyDriveInfo = NULL;
  UINT32                          BufferSize = 0;
  STRING_REF                      Token;
  STRING_REF                      SoftPresStatus;
  CHAR8                           ModelNumber[42];
  UINT64                          NumSectors = 0; 
  UINT64                          DriveSizeInBytes = 0;
  UINTN                           RemainderInBytes = 0;
  UINT32                          DriveSizeInGB = 0;
  UINT32                          NumTenthsOfGB = 0;
  UINT32                          SectorSize = 512; // Default Sector Size
  UINT8                           w;
  UINT8                           x;
  UINT8                           y;
  UINT8                           z;
  EFI_PCH_INFO_PROTOCOL           *PchInfo;
  UINT16                          Data16;
  UINT32                          SataController02;
  UINT32                          SataController05;
  UINT8                           i;
  CHAR8                           *RevId;
  AMI_PCH_DID_SKUNAME             PchDeviceId[] = { 
                                                    { 0x8C42, "DT Full Sku" },
                                                    { 0x8C44, "Z87" },
                                                    { 0x8C46, "Z85" },
                                                    { 0x8C4A, "H87" },
                                                    { 0x8C4C, "Q85" },
                                                    { 0x8C4E, "Q87" },
                                                    { 0x8C50, "B85" },
                                                    { 0x8C5C, "H81" },
                                                    { 0x8C41, "MB Full Sku" },
                                                    { 0x8C49, "HM86" },
                                                    { 0x8C4B, "HM87" },
                                                    { 0x8C4F, "QM87" },
                                                    { 0x8C52, "C222" },
                                                    { 0x8C54, "C224" },
                                                    { 0x8C56, "C226" },
                                                    { 0x9C41, "MB LP Full SKU" }, // LynxPoint-LP
                                                    { 0x9C43, "Premium SKU"},
                                                    { 0x9C45, "Mainstream SKU"},
                                                    { 0x9C47, "Value SKU"}
                                                  };
  UINTN                           VariableSize;
  EFI_GUID                        SetupGuid = SETUP_GUID;
  SB_PLATFORM_DATA                SbPlatformData;

  Data16 = READ_PCI16_SB(PCI_DID);

  if (Class == ADVANCED_FORM_SET_CLASS) {

    // Assume no line strings is longer than 256 bytes.

    Status = pBS->AllocatePool(EfiBootServicesData, 0x100, &NewString);
    ASSERT_EFI_ERROR(Status);

    Status = pBS->AllocatePool(EfiBootServicesData, 0x40, &SoftPres);
    ASSERT_EFI_ERROR(Status);


    PciDevicePath = NULL;

    SataMode = *((volatile UINT16 *)(UINTN)SATA_PCIE_REG(SATA_REG_MAP));
	                                                  //(EIP121889) >>
    if((Data16 & 0xFF00) != 0x9C00 ){ 
      if(SataMode == 0xFFFF)		//If Ide Controller F2 is disabled, check Ide Controller F5
        SataMode = *((volatile UINT16 *)(UINTN)SATA2_PCIE_REG(SATA_REG_MAP));
    }
	                                                  //(EIP121889) <<
    if ((SataMode & (BIT07 | BIT06)) == 0) { // IDE
      pAddress = (volatile UINT16 *)(UINTN)SATA_PCIE_REG(SATA_REG_PCS);
      SataP0P1Status = *(volatile UINT16 *)pAddress;
      pAddress = (volatile UINT16 *)(UINTN)SATA2_PCIE_REG(SATA_REG_PCS);
      SataP4P5Status = *(volatile UINT16 *)pAddress;
    } else { // AHCI or Raid
      pAddress = (volatile UINT16 *)(UINTN)SATA_PCIE_REG(SATA_REG_PCS);
      AhciModePortStatus = *(volatile UINT16 *)pAddress;
    }

    Status = pBS->LocateHandleBuffer (
                                      ByProtocol,
                                      &gEfiDiskInfoProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer
                                      );
    if (EFI_ERROR(Status)) HandleCount = 0;

    for (Index = 0; Index < HandleCount; Index++) {
      Status = pBS->HandleProtocol (
                                    HandleBuffer[Index],
                                    &gEfiDevicePathProtocolGuid,
                                    (VOID *) &DevicePath
                                    );
      ASSERT_EFI_ERROR(Status);

      DevicePathNode = DevicePath;
      while (!isEndNode (DevicePathNode)) {
        if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
            (DevicePathNode->SubType == HW_PCI_DP))
        {
          PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
          break;
        }
  
        DevicePathNode = NEXT_NODE (DevicePathNode);
      }

      if (PciDevicePath == NULL) continue;

      SataController02 = READ_PCI32(0x00, 0x1F, 0x02, 0x00);
      SataController05 = READ_PCI32(0x00, 0x1F, 0x05, 0x00);

      if (PciDevicePath->Device != 0x1C && (SataController02!=0xffffffff || SataController05!=0xffffffff)) {

        Status = pBS->HandleProtocol (
                                      HandleBuffer[Index],
                                      &gEfiDiskInfoProtocolGuid,
                                      &DiskInfo
                                      );
        ASSERT_EFI_ERROR (Status);

        if ((SataMode & (BIT07 | BIT06)) == 0) {  // IDE MODE
          Status = DiskInfo->WhichIde (
                                    DiskInfo,
                                    &IdeChannel,
                                    &SataPortIndex
                                    );
          SataPortIndex = (IdeChannel * 2) + SataPortIndex;                                                               
                                                          
          if (SataPortIndex == 1 || SataPortIndex == 2)     // SINDX ¡V Serial ATA Index (D31:F2)
            SataPortIndex ^= 3;                             // Port 0 = Primary Master
                                                            // Port 2 = Primary Slave
                                                            // Port 1 = Secondary Master
                                                            // Port 3 = Secondary Slave            
          if (PciDevicePath->Function == SATA2_FUN)         // Port 4, 5 in SATA2
            SataPortIndex += 4;    
          Token = gSATA[SataPortIndex];
          SoftPresStatus = gSOFTPRES[SataPortIndex];
        } else { // AHCI or Raid                                          // SATA MODE
          Status = DiskInfo->WhichIde (
                                    DiskInfo,
                                    &IdeChannel,
                                    &SataPortIndex
                                    );
          Token = gSATA[IdeChannel];
          SoftPresStatus = gSOFTPRES[IdeChannel];
        }

        Status = pBS->AllocatePool(EfiBootServicesData, sizeof (IDENTIFY_DATA), &IdentifyDriveInfo);
        ASSERT_EFI_ERROR (Status);

        pBS->SetMem(IdentifyDriveInfo, sizeof (IDENTIFY_DATA), 0); 

        BufferSize = sizeof (IDENTIFY_DATA);
        Status = DiskInfo->Identify (
                                    DiskInfo,
                                    IdentifyDriveInfo,
                                    &BufferSize
                                    );
       ASSERT_EFI_ERROR (Status);
        
      } else {
        //
        // Off board
        //
        continue;
      }
      pBS->SetMem(ModelNumber, 42, 0);
      pBS->CopyMem (ModelNumber, IdentifyDriveInfo->Model_Number_27, 40);
      SwapEntries (ModelNumber, 40);
      // Truncate it at DEVICE_NAME_LENGTH characters 
      ModelNumber[DEVICE_NAME_LENGTH] = '\0';

      //
      // For HardDisk append the size. Otherwise display atapi
      //
      if (!(IdentifyDriveInfo->General_Config_0 & ATAPI_DEVICE)) {
        if (IdentifyDriveInfo->Command_Set_Supported_83 & _48_BIT_ADDRESS_FEATURE_SET_SUPPORTED) { 
          NumSectors = IdentifyDriveInfo->LBA_48;
          if((IdentifyDriveInfo->Reserved_104_126[2] & 0x4000) && // WORD 106 valid? - BIT 14 - 1
             (!(IdentifyDriveInfo->Reserved_104_126[2] & 0x8000)) && // WORD 106 valid? - BIT 15 - 0
             (IdentifyDriveInfo->Reserved_104_126[2] & 0x1000)) { // WORD 106 bit 12 - Sectorsize > 256 words
              // The sector size is in words 117-118.
              SectorSize = (UINT32)(IdentifyDriveInfo->Reserved_104_126[13] + \
                                    (IdentifyDriveInfo->Reserved_104_126[14] << 16)) * 2;
          }
        } else {
          NumSectors = IdentifyDriveInfo->Addressable_Sector_60; 
        }
        DriveSizeInBytes = Mul64(NumSectors, SectorSize); 

        //DriveSizeInGB is DriveSizeInBytes / 1 GB (1 Binary GB = 2^30 bytes)
//####        DriveSizeInGB = (UINT32) Div64(DriveSizeInBytes, (1 << 30), &RemainderInBytes);  
        //Convert the Remainder, which is in bytes, to number of tenths of a Binary GB.
//####        NumTenthsOfGB = GetNumTenthsOfGB(RemainderInBytes); 

        //DriveSizeInGB is DriveSizeInBytes / 1 GB (1 Decimal GB = 10^9 bytes)
        DriveSizeInGB = (UINT32) Div64(DriveSizeInBytes, 1000000000, &RemainderInBytes);  
        //Convert the Remainder, which is in bytes, to number of tenths of a Decimal GB.
        NumTenthsOfGB = (UINT32)(RemainderInBytes / 100000000);        

        Sprintf(NewString, "%s (%d.%dGB)", ModelNumber, DriveSizeInGB, NumTenthsOfGB);
        if ((IdentifyDriveInfo->Reserved_76_79[0] != 0xFFFF ) && (IdentifyDriveInfo->Reserved_76_79[2] & 0x0040))
          Sprintf(SoftPres, "SUPPORTED");
        else
          Sprintf(SoftPres, "NOT SUPPORTED");

      } else {
        Sprintf(NewString, "%s ATAPI", ModelNumber);
        Sprintf(SoftPres, "  N/A  ");
      }
      InitString(
                HiiHandle,
                Token,
                L"%S", 
                NewString
                );

      InitString(
                HiiHandle,
                SoftPresStatus,
                L"%S", 
                SoftPres
                );

      if (IdentifyDriveInfo) {
        pBS->FreePool (IdentifyDriveInfo);
        IdentifyDriveInfo = NULL;
      }
    }
    if (HandleBuffer) 
      pBS->FreePool (HandleBuffer);
    pBS->FreePool (NewString);
  }

  Status = pBS->LocateProtocol( &gEfiPchInfoProtocolGuid, \
                                NULL, \
                                &PchInfo );
  if (!EFI_ERROR (Status)) {
     x       = (UINT8) ((PchInfo->RCVersion & 0xFF000000) >> 24);
     y       = (UINT8) ((PchInfo->RCVersion & 0xFF0000) >> 16);
     z       = (UINT8) ((PchInfo->RCVersion & 0xFF00) >> 8);
     w       = (UINT8) ((PchInfo->RCVersion & 0xFF));

     InitString ( HiiHandle,
                  STRING_TOKEN (STR_PCH_RC_VER_VALUE),
                  L"%d.%d.%d.%d",
                  x, y, z, w);
  }

  for (i = 0; i < sizeof(PchDeviceId) / sizeof(AMI_PCH_DID_SKUNAME); i++) {
    if (Data16 == PchDeviceId[i].DeviceId) {
      InitString(
                 HiiHandle,
                 STRING_TOKEN (STR_PCH_SKU_VALUE),
                 L"%S", 
                 PchDeviceId[i].SkuName
                );
      break;
    }
  }

  // Read the SB Platform Data
  VariableSize = sizeof (SB_PLATFORM_DATA);
  Status = pRS->GetVariable (
    L"SbPlatformData",
    &SetupGuid,
    NULL,
    &VariableSize,
    &SbPlatformData );
  if( EFI_ERROR (Status)) i = 0xff;
  else i = SbPlatformData.PchRid;
  if((Data16 & 0xFF00) == 0x9C00 ){   //LPT-LP stepping
    switch (i)
    {
       case 0x00:
         RevId = "00/A0";
         break;

       case 0x01:
         RevId = "01/A1";
         break;

       case 0x02:
         RevId = "02/B0";
         break;

       case 0x03:
         RevId = "03/B1";
         break;

       case 0x04:
         RevId = "04/B2";
         break;

       case 0x05:
         RevId = "05/C0";
         break;

       default:
         RevId = "Unknown";
         break;
    }
  }else{                        //LPT stepping
    switch (i)
    {
       case 0x00:
         RevId = "00/A0";
         break;

       case 0x01:
         RevId = "01/A1";
         break;

       case 0x02:
         RevId = "02/B0";
         break;

       case 0x03:
         RevId = "03/C0";
         break;

       case 0x04:
         RevId = "04/C1";
         break;

       case 0x05:
         RevId = "05/C2";
         break;

       default:
         RevId = "Unknown";
         break;
    }
  }
  InitString(
             HiiHandle,
             STRING_TOKEN (STR_PCH_REVID_VALUE),
             L"%S", 
             RevId
            );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetNumTenthsOfGB
//
// Description: 
//               x   x/16    num tenths
//               -   ----    ----------
//               0   0           0
//               1   .0625       1
//               2   .125        1
//               3   .1875       2
//               4   .25         2
//               5   .3125       3
//               6   .375        4
//               7   .4375       4
//               8   .5          5
//               9   .5625       6
//               10  .625        6
//               11  .6875       7
//               12  .75         7
//               13  .8125       8
//               14  .875        9
//               15  .9375       9
//
// Inpuut:      IN  UINT32 RemainderBytesOfGB
//
// Output:      UINT32
//
// Notes:       
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
GetNumTenthsOfGB ( IN  UINT32 RemainderBytesOfGB )
{
  UINT32  Tenths = 0;                   //num tenths of of a GB
  UINT32  Sixteenths = RemainderBytesOfGB / (1 << 26); //num sixteenths of a Binary GB

  switch (Sixteenths) {
    case 0:
          Tenths = 0; break;
    case 1:
    case 2:
          Tenths = 1; break;
    case 3:
    case 4:
          Tenths = 2; break;
    case 5:
          Tenths = 3; break;
    case 6:
    case 7:
          Tenths = 4; break;
    case 8:
          Tenths = 5; break;
    case 9:
    case 10:
          Tenths = 6; break;
    case 11:
    case 12:
          Tenths = 7; break;
    case 13:
          Tenths = 8; break;
    case 14:
    case 15:
          Tenths = 9; break;
    default:
          Tenths = 0; break;
  }

  return Tenths;
}
									//(EIP124410)>>
EFI_STATUS
EFIAPI
SB_CRID_CALLBACK (
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16         Class, 
    IN UINT16         SubClass, 
    IN UINT16         Key
)
{
    EFI_STATUS          Status         = EFI_SUCCESS;
    SETUP_DATA          *SetupData     = NULL;
    CALLBACK_PARAMETERS *pCallbackData = NULL;
#if EFI_SPECIFICATION_VERSION > 0x20000
    UINTN               BufferSize     = sizeof(SETUP_DATA);
    EFI_GUID            SetupGuid      = SETUP_GUID;
#else
    UINT8               *pNvRamMap;
#endif

    pCallbackData = GetCallbackParameters();
    if(pCallbackData == NULL) return Status;      

#if ((TSE_BUILD >= 0x1224) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
    if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGED)
        return Status;
#elif ((TSE_BUILD > 0x1208) && (EFI_SPECIFICATION_VERSION >= 0x2000A))
    // Check callback action
    if (pCallbackData->Action != EFI_BROWSER_ACTION_CHANGING)
        return Status;
#endif

#if EFI_SPECIFICATION_VERSION > 0x20000
    Status = pBS->AllocatePool(EfiBootServicesData, BufferSize, &SetupData);
    if(EFI_ERROR(Status)) return Status;

    Status = HiiLibGetBrowserData(
                &BufferSize, SetupData,
                &SetupGuid,  L"Setup");
    ASSERT_EFI_ERROR(Status);
#else   
    pNvRamMap = pCallbackData->Data->NvRamMap;
    SetupData = (SETUP_DATA*)pNvRamMap;
#endif

    switch (Key)
    {
    case SB_CRID_KEY:
        SetupData->EnableNbCrid = SetupData->PchEnableCrid;
        break;
    }

#if EFI_SPECIFICATION_VERSION > 0x20000
    Status = HiiLibSetBrowserData(
                BufferSize, SetupData,
                &SetupGuid,  L"Setup");
    ASSERT_EFI_ERROR(Status);    
    
    pBS->FreePool(SetupData);
#endif;

    return EFI_SUCCESS;
}
									//(EIP124410)<<
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
