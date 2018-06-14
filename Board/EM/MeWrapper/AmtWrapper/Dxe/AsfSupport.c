//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AsfSupport.c 10    5/14/14 9:52p Tristinchou $
//
// $Revision: 10 $
//
// $Date: 5/14/14 9:52p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AsfSupport.c $
// 
// 10    5/14/14 9:52p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 9     1/08/14 10:23p Tristinchou
// [TAG]  		EIP144445
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AMT IDER Floppy failed on HSW ULT
// [RootCause]  	IDER Device ID is different on HSW ULT
// [Solution]  	Determine the bus, device and function number directly
// 
// 8     9/24/13 4:22a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Raise TPL is not needed
// 
// 7     4/08/13 3:10a Klzhan
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	TC015 fail
// 
// 6     3/01/13 4:38a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Boot to legacy when UEFI boot fail.
// Correct secure boot fail behavior
// 
// 5     2/25/13 7:05a Klzhan
// [TAG]  		EIP113605
// [Category]  	Improvement
// [Description]  	Support IDER Floppy BOOT.
// 
// 4     10/30/12 8:30a Klzhan
// Improvement : Boot to Legacy when EFI boot fail.
// Improvement : Correct Secure IDER Boot.
// 
// 3     8/14/12 7:26a Klzhan
// Support UEFI IDER boot.
// 
// 2     4/24/12 12:36a Klzhan
// Update modulepart to latest
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 3     7/08/11 4:20a Klzhan
// 
// 2     6/16/11 4:56a Klzhan
// Update IDER related code.
// 
// 1     2/25/11 1:43a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            AsfSupport.c
//
// Description:
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
 This file contains an 'Intel Peripheral Driver' and is        
 licensed for Intel CPUs and chipsets under the terms of your  
 license agreement with Intel or your vendor.  This file may   
 be modified by the user, subject to additional terms of the   
 license agreement                                             
--*/

/*++

Copyright (c) 2005-2008 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  AsfSupport.c
  
Abstract:

  Support routines for ASF boot options in the BDS

--*/

#include "AsfSupport.h"

#pragma pack(push,1)

typedef struct {
	UINT32 Attributes;
	UINT16 FilePathListLength;
} EFI_LOAD_OPTION;
#pragma pack(pop)

//
// Global variables
//
EFI_ASF_BOOT_OPTIONS            *mAsfBootOptions;

static EFI_DEVICE_PATH_PROTOCOL EndDevicePath[] = {
  END_DEVICE_PATH_TYPE,
  END_ENTIRE_DEVICE_PATH_SUBTYPE,
  END_DEVICE_PATH_LENGTH,
  0
};

//
// Legacy Device Order
//
typedef struct {
  UINT32  Type;
  UINT16  Length;
  UINT16  Device[1];
} LEGACY_DEVICE_ORDER;

#define LEGACY_DEV_ORDER_GUID \
  { \
    0xA56074DB, 0x65FE, 0x45F7, 0xBD, 0x21, 0x2D, 0x2B, 0xDD, 0x8E, 0x96, 0x52 \
  }

EFI_GUID  gLegacyDeviceOrderGuid = LEGACY_DEV_ORDER_GUID;

EFI_STATUS
BdsAsfInitialization (
  IN  VOID
  )
/*++

Routine Description:

  Retrieve the ASF boot options previously recorded by the ASF driver.
  
Arguments:

  None.
  
Returns:

  Initialize Boot Options global variable and AMT protocol
  
--*/
{
  EFI_STATUS                          Status;
  EFI_ALERT_STANDARD_FORMAT_PROTOCOL  *Asf;

  mAsfBootOptions = NULL;

  //
  // Amt Library Init
  //
  Status = AmtLibInit ();
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Info : Error init AmtLibInit -> %r\n", Status));
    return Status;
  }
  //
  // Get Protocol for ASF
  //
  Status = gBS->LocateProtocol (
                  &gEfiAlertStandardFormatProtocolGuid,
                  NULL,
                  &Asf
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Info : Error gettings ASF protocol -> %r\n", Status));
    return Status;
  }

  Status = Asf->GetBootOptions (Asf, &mAsfBootOptions);

  return Status;
}

BDS_COMMON_OPTION *
BdsCreateBootOption (
  IN  EFI_DEVICE_PATH_PROTOCOL       *DevicePath,
  IN  CHAR16                         *Description
  )
/*++

Routine Description:
  
  This function will create a BootOption from the give device path and 
  description string.

Arguments:

  DevicePath       - The device path which the option represent
  Description      - The description of the boot option
  
Returns:
  
  BDS_COMMON_OPTION - A BDS_COMMON_OPTION pointer
  
--*/
{
  BDS_COMMON_OPTION *Option;

  Option = EfiLibAllocateZeroPool (sizeof (BDS_COMMON_OPTION));
  if (Option == NULL) {
    return NULL;
  }

  Option->Signature   = BDS_LOAD_OPTION_SIGNATURE;
  Option->DevicePath  = EfiLibAllocateZeroPool (EfiDevicePathSize (DevicePath));
  EfiCopyMem (Option->DevicePath, DevicePath, EfiDevicePathSize (DevicePath));

  Option->Attribute   = LOAD_OPTION_ACTIVE;
  Option->Description = EfiLibAllocateZeroPool (EfiStrSize (Description));
  EfiCopyMem (Option->Description, Description, EfiStrSize (Description));

  return Option;
}

EFI_DEVICE_PATH_PROTOCOL *
BdsCreateShellDevicePath (
  VOID
  )
/*++

Routine Description:
  
  This function will create a SHELL BootOption to boot.

Arguments:

  None.
  
Returns:
  
  Shell Device path for booting.
  
--*/
{
  UINTN                             FvHandleCount;
  EFI_HANDLE                        *FvHandleBuffer;
  UINTN                             Index;
  EFI_STATUS                        Status;
#if (PI_SPECIFICATION_VERSION < 0x00010000)
  EFI_FIRMWARE_VOLUME_PROTOCOL      *Fv;
#else
  EFI_FIRMWARE_VOLUME2_PROTOCOL     *Fv;
#endif
  EFI_FV_FILETYPE                   Type;
  UINTN                             Size;
  EFI_FV_FILE_ATTRIBUTES            Attributes;
  UINT32                            AuthenticationStatus;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  MEDIA_FW_VOL_FILEPATH_DEVICE_PATH ShellNode;

  DevicePath  = NULL;
  Status      = EFI_SUCCESS;

  gBS->LocateHandleBuffer (
        ByProtocol,
    #if (PI_SPECIFICATION_VERSION < 0x00010000)
        &gEfiFirmwareVolumeProtocolGuid,
    #else
        &gEfiFirmwareVolume2ProtocolGuid,
    #endif
        NULL,
        &FvHandleCount,
        &FvHandleBuffer
        );

  for (Index = 0; Index < FvHandleCount; Index++) {
    gBS->HandleProtocol (
          FvHandleBuffer[Index],
      #if (PI_SPECIFICATION_VERSION < 0x00010000) 
          &gEfiFirmwareVolumeProtocolGuid,
      #else
          &gEfiFirmwareVolume2ProtocolGuid,
      #endif
          (VOID **) &Fv
          );

    Status = Fv->ReadFile (
                  Fv,
                  &gEfiShellFileGuid,
                  NULL,
                  &Size,
                  &Type,
                  &Attributes,
                  &AuthenticationStatus
                  );
    if (EFI_ERROR (Status)) {
      //
      // Skip if no shell file in the FV
      //
      continue;
    } else {
      //
      // Found the shell
      //
      break;
    }
  }

  if (EFI_ERROR (Status)) {
    //
    // No shell present
    //
    if (FvHandleCount) {
      gBS->FreePool (FvHandleBuffer);
    }

    return NULL;
  }
  //
  // Build the shell boot option
  //
  DevicePath = EfiDevicePathFromHandle (FvHandleBuffer[Index]);

  //
  // Build the shell device path
  //
  ShellNode.Header.Type     = MEDIA_DEVICE_PATH;
  ShellNode.Header.SubType  = MEDIA_FV_FILEPATH_DP;
  SetDevicePathNodeLength (&ShellNode.Header, sizeof (MEDIA_FW_VOL_FILEPATH_DEVICE_PATH));
  EfiCopyMem (&ShellNode.NameGuid, &gEfiShellFileGuid, sizeof (EFI_GUID));
  DevicePath = EfiAppendDevicePathNode (DevicePath, (EFI_DEVICE_PATH_PROTOCOL *) &ShellNode);

  if (FvHandleCount) {
    gBS->FreePool (FvHandleBuffer);
  }

  return DevicePath;
}

static
EFI_DEVICE_PATH_PROTOCOL *
BdsCreatePxeDevicePath (
  IN UINT16     DeviceIndex
  )
/*++

Routine Description:
  
  This function will create a PXE BootOption to boot.

Arguments:

  DeviceIndex - PXE handle index
  
Returns:
  
  PXE Device path for booting.
  
--*/
{
  UINTN                     Index;
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     NumberLoadFileHandles;
  EFI_HANDLE                *LoadFileHandles;
  VOID                      *ProtocolInstance;

  DevicePath  = NULL;
  Status      = EFI_SUCCESS;

  //
  // We want everything connected up for PXE
  //
  BdsLibConnectAllDriversToAllControllers ();

  //
  // Parse Network Boot Device
  //
  gBS->LocateHandleBuffer (
        ByProtocol,
        &gEfiSimpleNetworkProtocolGuid,
        NULL,
        &NumberLoadFileHandles,
        &LoadFileHandles
        );
  for (Index = 0; Index < NumberLoadFileHandles; Index++) {
    Status = gBS->HandleProtocol (
                    LoadFileHandles[Index],
                    &gEfiLoadFileProtocolGuid,
                    (VOID **) &ProtocolInstance
                    );
    if (EFI_ERROR (Status)) {
      //
      // try next handle
      //
      continue;
    } else {
      if (Index == DeviceIndex) {
        //
        // Found a PXE handle
        //
        break;
      } else {
        Status = EFI_UNSUPPORTED;
      }
    }
  }

  if (EFI_ERROR (Status)) {
    //
    // No PXE present
    //
    if (NumberLoadFileHandles) {
      gBS->FreePool (LoadFileHandles);
    }

    return NULL;
  }
  //
  // Build the PXE device path
  //
  DevicePath = EfiDevicePathFromHandle (LoadFileHandles[Index]);

  if (NumberLoadFileHandles) {
    gBS->FreePool (LoadFileHandles);
  }

  return DevicePath;
}

static
VOID
GetAmtBusDevFcnVal (
  OUT  UINT32   *Bus,
  OUT  UINT32   *Device,
  OUT  UINT32   *Function
  )
/*++

Routine Description:
  
  This function will get Bus, Device and Function.

Arguments:

  Bus      - AMT Bus
  Device   - AMT Device
  Function - AMT Function
  
Returns:

  None.  
  
--*/
{
  UINT32                          Index;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;
  UINT64                          Address;
  DATA32_UNION                    Data32Union;
  EFI_STATUS                      Status;

  *Bus      = 0;
  *Device   = 0;
  *Function = 0;

  //
  // Locate root bridge IO protocol
  //
  Status = gBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
  ASSERT_EFI_ERROR (Status);

  //
  // Need to fill in IDER bus dev function so find this for Tekoa i82573E here.
  //
  for (Index = 0; Index < 0x255; Index++) {
    Address = EFI_PCI_ADDRESS (
                Index,
                ME_DEVICE_NUMBER,     //
                IDER_FUNCTION_NUMBER, // fun 2 IDER capability
                PCI_VENDOR_ID_OFFSET
                );
    Status = PciRootBridgeIo->Pci.Read (
                                    PciRootBridgeIo,
                                    EfiPciWidthUint32,
                                    Address,
                                    1,
                                    &Data32Union
                                    );
    if ((Data32Union.Data16[0] == V_ME_IDER_VENDOR_ID) && 
      (Data32Union.Data16[1] == V_ME_IDER_DEVICE_ID)) {
      //
      // LOM i82573E is always Device 0 and function 2 so or this 8 bit value of 0x02
      // into bus number discovered.  Bus # upper byte and Dev-Fcn lower byte.
      //
      *Bus      = Index;
      *Device   = ME_DEVICE_NUMBER;
      *Function = IDER_FUNCTION_NUMBER;
      break;
    }
  }
}

UINTN
GetFirstIndexByType (
  UINT16 DevType
  )
/*++

Routine Description:

  Boot HDD by BIOS Default Priority

Arguments:

  DevType - Boot device whose device type

Returns:

  None

--*/
{
  EFI_STATUS          Status;
  UINTN               LegacyDevOrderSize;
  LEGACY_DEVICE_ORDER *LegacyDevOrder;
  UINTN               Index;
  UINT8               *p;
  UINTN               o;

  Index               = 0;
  o                   = 0;

  LegacyDevOrderSize  = 0;
  LegacyDevOrder      = NULL;

  Status = gRT->GetVariable (
                  L"LegacyDevOrder",
                  &gLegacyDeviceOrderGuid,
                  NULL,
                  &LegacyDevOrderSize,
                  NULL
                  );

  if (Status == EFI_BUFFER_TOO_SMALL) {
    LegacyDevOrder = EfiLibAllocateZeroPool (LegacyDevOrderSize);
    if (LegacyDevOrder != NULL) {
      Status = gRT->GetVariable (
                      L"LegacyDevOrder",
                      &gLegacyDeviceOrderGuid,
                      NULL,
                      &LegacyDevOrderSize,
                      LegacyDevOrder
                      );
      if (!EFI_ERROR (Status)) {
        p = (UINT8 *) LegacyDevOrder;
        o = 0;
        for (o = 0; o < LegacyDevOrderSize; o += sizeof (LegacyDevOrder->Type) + LegacyDevOrder->Length) {
          LegacyDevOrder = (LEGACY_DEVICE_ORDER *) (p + o);
          if (LegacyDevOrder->Type == DevType) {
            Index = LegacyDevOrder->Device[0];
          }
        }
      }
    }
  }

  return Index;
}

static
EFI_STATUS
RefreshBbsTableForBoot (
  IN     UINT16        DeviceIndex,
  IN     UINT16        DevType,
  IN     UINT16        BbsCount,
  IN OUT BBS_TABLE     *BbsTable
  )
/*++

Routine Description:
  
  Update the table with our required boot device

Arguments:

  DeviceIndex - Boot device whose device index
  DevType     - Boot device whose device type
  BbsCount    - Number of BBS_TABLE structures
  BbsTable    - BBS entry
  
Returns:

  EFI_STATUS
  
--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINT16      BootDeviceIndex;
  UINT16      TempIndex;

  Status          = EFI_NOT_FOUND;
  TempIndex       = 1;

  BootDeviceIndex = DeviceIndex;

  //
  // Find the first present boot device whose device type
  // matches the DevType, we use it to boot first. This is different
  // from the other Bbs table refresh since we are looking for the device type
  // index instead of the first device to match the device type.
  //
  // And set other present boot devices' priority to BBS_UNPRIORITIZED_ENTRY
  // their priority will be set by LegacyBiosPlatform protocol by default
  //
  if (DeviceIndex > 0) {
    for (Index = 0; Index < BbsCount; Index++) {
      if (BbsTable[Index].BootPriority == BBS_IGNORE_ENTRY) {
        continue;
      }

      BbsTable[Index].BootPriority = BBS_DO_NOT_BOOT_FROM;

      if (BbsTable[Index].DeviceType == DevType) {
        if (TempIndex++ == DeviceIndex) {
          BbsTable[Index].BootPriority  = 0;
          Status                        = EFI_SUCCESS;
          continue;
        }
      }
    }
  } else {
    //
    // Boot HDD by BIOS Default Priority
    //
    Index                         = GetFirstIndexByType (DevType);
    BbsTable[Index].BootPriority  = 0;
    Status                        = EFI_SUCCESS;
  }

  return Status;
}

static
EFI_STATUS
RefreshBbsTableForIdeRBoot (
  IN     UINT16        DeviceIndex,
  IN     UINT16        DevType,
  IN     UINT16        BbsCount,
  IN OUT BBS_TABLE     *BbsTable
  )
/*++

Routine Description:
  
  Update the table with IdeR boot device

Arguments:

  DeviceIndex - Boot device whose device index
  DevType     - Boot device whose device type
  BbsCount    - Number of BBS_TABLE structures
  BbsTable    - BBS entry
  
Returns:

  EFI_STATUS
  
--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  BOOLEAN     IderDeviceFound;

  Status          = EFI_NOT_FOUND;

  IderDeviceFound = FALSE;

  //
  // Find the first present boot device whose device type
  // matches the DevType, we use it to boot first.
  //
  // And set other present boot devices' priority to BBS_DO_NOT_BOOT_FROM
  // their priority will be set by LegacyBiosPlatform protocol by default
  //
  for (Index = 0; Index < BbsCount; Index++) {
    if (BBS_IGNORE_ENTRY == BbsTable[Index].BootPriority) {
      continue;
    }

    BbsTable[Index].BootPriority = BBS_DO_NOT_BOOT_FROM;

    if ( (BbsTable[Index].Bus == ME_BUS) &&
         (BbsTable[Index].Device == ME_DEVICE_NUMBER) &&
         (BbsTable[Index].Function == IDER_FUNCTION_NUMBER) ) {
      if (DeviceIndex == 0 && IderDeviceFound != TRUE) {
        BbsTable[Index].BootPriority  = 0;
        IderDeviceFound               = TRUE;
        Status                        = EFI_SUCCESS;
      } else {
        DeviceIndex--;
      }

      continue;
    }
  }

  return Status;
}
static
EFI_DEVICE_PATH_PROTOCOL *
BuildDevicePathFromBootOrder
(
  VOID
)
{
  UINT8                       BootMediaType = 0;   
  UINT8                       BootMediaSubType = 0;   
  BOOLEAN                     IDERBoot = FALSE, IDERFloppy = FALSE;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath = NULL;
  UINT16                      *BootOrder;
  EFI_LOAD_OPTION             *BootOption;
  UINTN                       BootOrderSize;
  UINTN                       BootOptionSize;
  CHAR16                      BootVarName[9];
  UINTN                       i;
  EFI_STATUS                  Status;
  EFI_DEVICE_PATH_PROTOCOL    *Dp, *DevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL    *DummyDp;
  UINTN                       BufferSize = 0;
  if (ActiveManagementEnableIdeR ()) {
    //
    // Check if any media exist in Ider device
    //
    if (BdsCheckIderMedia ()) {

      // IDER Floppy
      if(mAsfBootOptions->SpecialCommandParam == 1)
      {
          IDERFloppy = TRUE;       
      }

      // IDER CD
      if((mAsfBootOptions->SpecialCommandParam == 0x101) ||
         (mAsfBootOptions->SpecialCommandParam == 0x103))
      {
          BootMediaType = MEDIA_DEVICE_PATH;
          BootMediaSubType = MEDIA_CDROM_DP;
      }
      IDERBoot = TRUE;
    }
  }else
  {
    switch (mAsfBootOptions->SpecialCommand) {
    case FORCE_PXE:
      if (mAsfBootOptions->SpecialCommandParam != 0) {
        //
        // ASF spec says 0 currently only option
        //
        return NULL;
      }
      BootMediaType = MESSAGING_DEVICE_PATH;
      BootMediaSubType = MSG_MAC_ADDR_DP;
      break;
  
    case FORCE_HARDDRIVE:
    case FORCE_SAFEMODE:
      BootMediaType = MEDIA_DEVICE_PATH;
      BootMediaSubType = MEDIA_HARDDRIVE_DP;
      break;
  
    case FORCE_DIAGNOSTICS:
      if (mAsfBootOptions->SpecialCommandParam != 0) {
        //
        // ASF spec says 0 currently only option
        //
        return NULL;
      }
  
      DevicePath = BdsCreateShellDevicePath ();
  
      //
      // We want everything connected up for shell
      //
      BdsLibConnectAllDriversToAllControllers ();
      break;
  
    case FORCE_CDDVD:
      BootMediaType = MEDIA_DEVICE_PATH;
      BootMediaSubType = MEDIA_CDROM_DP;
      break;
  
    default:
      return NULL;
      break;
    }
  }//else IDER check
  // Get Device Path from BootXXXX
  BootOrder = NULL;
  BootOption = NULL;
  BootOrderSize = 0;

  Status = gRT->GetVariable(
              L"BootOrder", 
              &gEfiGlobalVariableGuid, 
              NULL,
              &BootOrderSize,
              NULL
            );
            
  if (Status == EFI_BUFFER_TOO_SMALL) 
  {
      BootOrder = EfiLibAllocateZeroPool(BootOrderSize);
      if (BootOrder != NULL)
      {
          Status = gRT->GetVariable(
                  L"BootOrder", 
                  &gEfiGlobalVariableGuid, 
                  NULL,
                  &BootOrderSize,
                  BootOrder
                  );
          if (!EFI_ERROR(Status)) 
          {  
              for (i=0; i<BootOrderSize/sizeof(UINT16); i++)
              {                 
                  SPrint(BootVarName, sizeof(BootVarName), L"Boot%04x", BootOrder[i] );
                  BootOptionSize = 0;
                  Status = gRT->GetVariable(
                          BootVarName, 
                          &gEfiGlobalVariableGuid,
                          NULL,
                          &BootOptionSize, 
                          NULL
                        );
                   if (Status == EFI_BUFFER_TOO_SMALL) 
                   {
                       BootOption = EfiLibAllocateZeroPool(BootOptionSize);
                       if (BootOption != NULL)
                       {
                         Status = gRT->GetVariable(
                                          BootVarName, 
                                          &gEfiGlobalVariableGuid,
                                          NULL,
                                          &BootOptionSize, 
                                          BootOption);
                         if (!EFI_ERROR(Status)) 
                         {
                           Dp = (EFI_DEVICE_PATH_PROTOCOL *) (
                           //
                           // skip the header
                           //
                           (UINT8 *) (BootOption + 1)
                           //
                           // skip the string
                           //
                           + (EfiStrLen ((CHAR16 *) (BootOption + 1)) + 1) * sizeof (CHAR16));
                           DevicePathNode = Dp;
                           while (!EfiIsDevicePathEnd (DevicePathNode)) 
                           {
                   // Skip USB device
                   /*
                               if((DevicePathNode->Type == MESSAGING_DEVICE_PATH) &&
                                  (DevicePathNode->SubType == MSG_USB_DP))
                                   break;
                   */

                               if( IDERBoot && 
                                  (DevicePathNode->Type == MESSAGING_DEVICE_PATH) &&
                                  (DevicePathNode->SubType == MSG_SATA_DP))
                                      break;

                               // Do something special for IDER Floppy,
                               // In AMT commander tool, If redirect to Floppy and CD image
                               // The device path are almost the same
                               if(IDERFloppy && 
                                  (DevicePathNode->Type == MESSAGING_DEVICE_PATH) &&
                                  (DevicePathNode->SubType == MSG_ATAPI_DP)) 
                               {
                                 EFI_DEVICE_PATH_PROTOCOL *tDP = 
                                             EfiNextDevicePathNode (DevicePathNode);
                                 // IDER CD image has Next Device Path Node, but Floppy doesn't
                                 if(EfiIsDevicePathEnd (tDP))
                                 {
                                   // Correct Pointer of DP, Fix freepool hang issue
                                   BufferSize = 
                                   (UINTN)((UINTN *)BootOptionSize - 
                                   ((UINTN *)Dp - 
                                   (UINTN *)BootOption))/sizeof(UINT8);

                                   Status = gBS->AllocatePool( 
                                   EfiBootServicesData, BufferSize, &DummyDp );

                                   if(!EFI_ERROR(Status))
                                   {
                                       gBS->CopyMem( 
                                       (VOID*)DummyDp, (VOID*)Dp, BufferSize );
                                   }
                                   else
                                   {
                                       Status = gBS->FreePool(BootOption);
                                       Status = gBS->FreePool(BootOrder);
                                       return NULL;
                                   }
                                   Status = gBS->FreePool(BootOption);
                                   Status = gBS->FreePool(BootOrder);
                                   return DummyDp;
                                 }
                                 break;
                               }
                               if((DevicePathNode->Type == BootMediaType) &&
                                  (DevicePathNode->SubType == BootMediaSubType))
                               {
                                 // Correct Pointer of DP, Fix freepool hang issue
                                 BufferSize = 
                                 (UINTN)((UINTN *)BootOptionSize - 
                                 ((UINTN *)Dp - 
                                 (UINTN *)BootOption))/sizeof(UINT8);

                                 Status = gBS->AllocatePool( 
                                 EfiBootServicesData, BufferSize, &DummyDp );

                                 if(!EFI_ERROR(Status))
                                 {
                                     gBS->CopyMem( 
                                     (VOID*)DummyDp, (VOID*)Dp, BufferSize );
                                 }
                                 else
                                 {
                                     Status = gBS->FreePool(BootOption);
                                     Status = gBS->FreePool(BootOrder);
                                     return NULL;

                                 }
                                 Status = gBS->FreePool(BootOption);
                                 Status = gBS->FreePool(BootOrder);
                                 return DummyDp;
                               }

                               DevicePathNode = EfiNextDevicePathNode (DevicePathNode);
                           }
                         }
                         gBS->FreePool (BootOption);
                       }
                   }
              }
          }
          gBS->FreePool (BootOrder);
      }
  }

  return DevicePath;
}
static
EFI_DEVICE_PATH_PROTOCOL *
BdsCreateLegacyBootDevicePath (
  IN UINT16     DeviceType,
  IN UINT16     DeviceIndex,
  IN BOOLEAN    IdeRBoot
  )
/*++

Routine Description:
  
  Build the BBS Device Path for this boot selection

Arguments:

  DeviceType  - Boot device whose device type
  DeviceIndex - Boot device whose device index
  IdeRBoot    - If IdeRBoot is TRUE then check Ider device
  
Returns:

  EFI_STATUS
  
--*/
{
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;
  BBS_BBS_DEVICE_PATH       BbsDevicePathNode;
  BBS_TABLE                 *BbsTable;
  UINT16                    HddCount;
  UINT16                    BbsCount;
  HDD_INFO                  *LocalHddInfo;
  UINT16                    Index;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_STATUS                Status;

  HddCount      = 0;
  BbsCount      = 0;
  LocalHddInfo  = NULL;

  Index         = DeviceIndex;

  //
  // Make sure the Legacy Boot Protocol is available
  //
  Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
  if (EFI_ERROR (Status)) {
    return NULL;
  }
  //
  // Get BBS table instance
  //
  Status = LegacyBios->GetBbsInfo (
                        LegacyBios,
                        &HddCount,
                        &LocalHddInfo,
                        &BbsCount,
                        &BbsTable
                        );
  if (EFI_ERROR (Status)) {
    return NULL;
  }
  //
  // For debug
  //
  PrintBbsTable (BbsTable);

  //
  // Update the table with our required boot device
  //
  if (IdeRBoot) {
    Status = RefreshBbsTableForIdeRBoot (
              Index,
              DeviceType,
              BbsCount,
              BbsTable
              );
  } else {
    Status = RefreshBbsTableForBoot (
              Index,
              DeviceType,
              BbsCount,
              BbsTable
              );
  }
  //
  // For debug
  //
  PrintBbsTable (BbsTable);

  if (EFI_ERROR (Status)) {
    //
    // Device not found - do normal boot
    //
    gST->ConOut->OutputString (
                  gST->ConOut,
                  L"Can't Find Boot Device by Boot Option !!\r\n"
                  );
    while(1);
    return NULL;
  }
  //
  // Build the BBS Device Path for this boot selection
  //
  DevicePath = EfiLibAllocateZeroPool (sizeof (EFI_DEVICE_PATH_PROTOCOL));
  if (DevicePath == NULL) {
    return NULL;
  }

  BbsDevicePathNode.Header.Type     = BBS_DEVICE_PATH;
  BbsDevicePathNode.Header.SubType  = BBS_BBS_DP;
  SetDevicePathNodeLength (&BbsDevicePathNode.Header, sizeof (BBS_BBS_DEVICE_PATH));
  BbsDevicePathNode.DeviceType  = DeviceType;
  BbsDevicePathNode.StatusFlag  = 0;
  BbsDevicePathNode.String[0]   = 0;

  DevicePath = EfiAppendDevicePathNode (
                EndDevicePath,
                (EFI_DEVICE_PATH_PROTOCOL *) &BbsDevicePathNode
                );
  if (NULL == DevicePath) {
    return NULL;
  }

  return DevicePath;
}

EFI_STATUS
AsfDoLegacyBoot (
  IN  BDS_COMMON_OPTION           *Option
  )
/*++

Routine Description:
 
  Boot the legacy system with the boot option

Arguments:

  Option           - The legacy boot option which have BBS device path

Returns:

  EFI_UNSUPPORTED  - There is no legacybios protocol, do not support
                     legacy boot.
                         
  EFI_STATUS       - Return the status of LegacyBios->LegacyBoot ().

--*/
{
  EFI_STATUS                Status;
  EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios;

  Status = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios);
  if (EFI_ERROR (Status)) {
    //
    // If no LegacyBios protocol we do not support legacy boot
    //
    return EFI_UNSUPPORTED;
  }
  //
  // Write boot to OS performance data to a file
  //
  WRITE_BOOT_TO_OS_PERFORMANCE_DATA;

  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Legacy Boot: %S\n", Option->Description));
  return LegacyBios->LegacyBoot (
                      LegacyBios,
                      (BBS_BBS_DEVICE_PATH *) Option->DevicePath,
                      Option->LoadOptionsSize,
                      Option->LoadOptions
                      );
}

BOOLEAN CompareDP(
	EFI_DEVICE_PATH_PROTOCOL *dp1,
	EFI_DEVICE_PATH_PROTOCOL *dp2
	)
{
	UINTN s1,s2;
	BOOLEAN st = FALSE;
	
	s1 = EfiDevicePathSize(dp1);
	
	s2 = EfiDevicePathSize(dp2);	
	
	if (s1 == s2) {
		if (EfiCompareMem(dp1, dp2, s1) == 0)
			st = TRUE;
	}
	
	return st;
}


UINT16 GetBootCurrent(
  IN  EFI_DEVICE_PATH_PROTOCOL      *DevicePath
)
{
  UINT16 *BootOrder;
  EFI_LOAD_OPTION *BootOption;
  UINTN BootOrderSize; //size of BootOrder Variable
  UINTN BootOptionSize;
  CHAR16 BootVarName[9];
  UINTN i;
  EFI_STATUS Status;
  BOOLEAN st;
  UINT16 BootCurrent;
  EFI_DEVICE_PATH_PROTOCOL *Dp;

  BootOrder = NULL;
  BootOption = NULL;
  BootCurrent = 0;
  BootOrderSize = 0;

  Status = gRT->GetVariable(
              L"BootOrder", 
              &gEfiGlobalVariableGuid, 
              NULL,
              &BootOrderSize,
              NULL
            );
            
  if (Status == EFI_BUFFER_TOO_SMALL) {
      BootOrder = EfiLibAllocateZeroPool(BootOrderSize);
      if (BootOrder != NULL){
          Status = gRT->GetVariable(
                  L"BootOrder", 
                  &gEfiGlobalVariableGuid, 
                  NULL,
                  &BootOrderSize,
                  BootOrder
                  );
          if (!EFI_ERROR(Status)) {  
              for (i=0; i<BootOrderSize/sizeof(UINT16); i++){                 
                  SPrint(BootVarName, sizeof(BootVarName), L"Boot%04x", BootOrder[i] );
                  BootOptionSize = 0;
                  Status = gRT->GetVariable(
                          BootVarName, 
                          &gEfiGlobalVariableGuid,
                          NULL,
                          &BootOptionSize, 
                          NULL
                        );
                   if (Status == EFI_BUFFER_TOO_SMALL) {
                       BootOption = EfiLibAllocateZeroPool(BootOptionSize);
                       if (BootOption != NULL){ 
                       Status = gRT->GetVariable(
                                        BootVarName, 
                                        &gEfiGlobalVariableGuid,
                                        NULL,
                                        &BootOptionSize, 
                                        BootOption
                                      );
                            if (!EFI_ERROR(Status)) {   
                                Dp = (EFI_DEVICE_PATH_PROTOCOL*)
                                    (   //skip the header
                                      (UINT8*)(BootOption+1) 
                                      //skip the string
                                      +(EfiStrLen((CHAR16*)(BootOption+1))+1)*sizeof(CHAR16)
                                        );                  
                                st = CompareDP(Dp, DevicePath);
                                if (st == TRUE) {
                                    BootCurrent = BootOrder[i];
                                }
                            }                   
                        gBS->FreePool(BootOption);                                                   
                      }
                  }
              }
          }
          gBS->FreePool(BootOrder);
      }
  }
  return BootCurrent; 
}

EFI_STATUS
AsfBootViaBootOption (
  IN  BDS_COMMON_OPTION             * Option,
  IN  EFI_DEVICE_PATH_PROTOCOL      * DevicePath,
  OUT UINTN                         *ExitDataSize,
  OUT CHAR16                        **ExitData OPTIONAL
  )
/*++

Routine Description:

  Process the boot option follow the EFI 1.1 specification and 
  special treat the legacy boot option with BBS_DEVICE_PATH.

Arguments:

  Option       - The boot option need to be processed
  DevicePath   - The device path which describe where to load 
                 the boot image or the legcy BBS device path 
                 to boot the legacy OS
  ExitDataSize - Returned directly from gBS->StartImage ()
  ExitData     - Returned directly from gBS->StartImage ()

Returns:

  EFI_SUCCESS   - Status from gBS->StartImage (),
                  or BdsBootByDiskSignatureAndPartition ()
  EFI_NOT_FOUND - If the Device Path is not found in the system

--*/
{
  EFI_STATUS                Status;
  EFI_HANDLE                Handle;
  EFI_HANDLE                ImageHandle;
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *FilePath;
  EFI_LOADED_IMAGE_PROTOCOL *ImageInfo;
  EFI_EVENT                 ReadyToBootEvent;
  EFI_ACPI_S3_SAVE_PROTOCOL *AcpiS3Save;
  UINT32                    VarAttr;
  UINTN                     VarSize;

  *ExitDataSize = 0;
  *ExitData     = NULL;

  //
  // Notes: put EFI64 ROM Shadow Solution
  //
  EFI64_SHADOW_ALL_LEGACY_ROM ();

  //
  // Notes: this code can be remove after the s3 script table
  // hook on the event EFI_EVENT_SIGNAL_READY_TO_BOOT or
  // EFI_EVENT_SIGNAL_LEGACY_BOOT
  //
  Status = gBS->LocateProtocol (&gEfiAcpiS3SaveGuid, NULL, &AcpiS3Save);
  if (!EFI_ERROR (Status)) {
    AcpiS3Save->S3Save (AcpiS3Save, NULL);
  }
  //
  // If it's Device Path that starts with a hard drive path,
  // this routine will do the booting.
  //
  Status = BdsBootByDiskSignatureAndPartition (
            Option,
            (HARDDRIVE_DEVICE_PATH *) DevicePath,
            Option->LoadOptionsSize,
            Option->LoadOptions,
            ExitDataSize,
            ExitData
            );
  if (!EFI_ERROR (Status)) {
    //
    // If we found a disk signature and partition device path return success
    //
    return EFI_SUCCESS;
  }
  //
  // Signal the EFI_EVENT_SIGNAL_READY_TO_BOOT event
  //


  Option->BootCurrent = GetBootCurrent(DevicePath);

  //
  // Get Variable Attribute
  //
  VarAttr = 0;
  VarSize = 0;
  Status = gRT->GetVariable(
                    L"BootCurrent",
                    &gEfiGlobalVariableGuid,
                    &VarAttr,
                    &VarSize,
                    NULL );
  if( Status != EFI_BUFFER_TOO_SMALL )
  {
    VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
    VarSize = sizeof(UINT16);
  }
  
  //
  // Set Boot Current
  //
  gRT->SetVariable(
          L"BootCurrent",
          &gEfiGlobalVariableGuid,
          VarAttr,
          VarSize,
          &Option->BootCurrent );

  //
  // Abstract: Modified for EFI 2.0 required
  //
#if defined(EFI_EVENT_SIGNAL_READY_TO_BOOT) && EFI_SPECIFICATION_VERSION < 0x20000
  Status = gBS->CreateEvent (
                  EFI_EVENT_SIGNAL_READY_TO_BOOT | EFI_EVENT_NOTIFY_SIGNAL_ALL,
                  EFI_TPL_CALLBACK,
                  NULL,
                  NULL,
                  &ReadyToBootEvent
                  );
#else
  Status = EfiCreateEventReadyToBoot (
            EFI_TPL_CALLBACK,
            NULL,
            NULL,
            &ReadyToBootEvent
            );
#endif
  if (!EFI_ERROR (Status)) {
    gBS->SignalEvent (ReadyToBootEvent);
    gBS->CloseEvent (ReadyToBootEvent);
  }
  
  if ((DevicePathType (Option->DevicePath) == BBS_DEVICE_PATH) &&
      (DevicePathSubType (Option->DevicePath) == BBS_BBS_DP)
      ) {
    //
    // Check to see if we should legacy BOOT. If yes then do the legacy boot
    //
    return AsfDoLegacyBoot (Option);
  }

  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Booting EFI 1.1 way %S\n", Option->Description));

  Status = gBS->LoadImage (
                  TRUE,
                  mBdsImageHandle,
                  DevicePath,
                  NULL,
                  0,
                  &ImageHandle
                  );

  //
  // If we didn't find an image, we may need to load the default
  // boot behavior for the device.
  //
  if (EFI_ERROR (Status)) {
    //
    // Find a Simple File System protocol on the device path. If the remaining
    // device path is set to end then no Files are being specified, so try
    // the removable media file name.
    //
    TempDevicePath = DevicePath;
    Status = gBS->LocateDevicePath (
                    &gEfiSimpleFileSystemProtocolGuid,
                    &TempDevicePath,
                    &Handle
                    );
    if (!EFI_ERROR (Status) && IsDevicePathEnd (TempDevicePath)) {
      FilePath = EfiFileDevicePath (Handle, DEFAULT_REMOVABLE_FILE_NAME);
      if (FilePath) {
        Status = gBS->LoadImage (
                        TRUE,
                        mBdsImageHandle,
                        FilePath,
                        NULL,
                        0,
                        &ImageHandle
                        );
        if (EFI_ERROR (Status)) {
          // System Halt when IDER boot fail !!
          if(ActiveManagementEnableIdeR () && ((Status == EFI_SECURITY_VIOLATION) || (Status == EFI_ACCESS_DENIED)))
          {
            gST->ConOut->OutputString (
                 gST->ConOut,
                 L"IDER Boot Fail, system halt !! \r\n");

            while(1);
          }
          //
          // The DevicePath failed, and it's not a valid
          // removable media device.
          //
          goto Done;
        }
      }
    } else {
      Status = EFI_NOT_FOUND;
    }
  }

  if (EFI_ERROR (Status)) {
    //
    // It there is any error from the Boot attempt exit now.
    //
    goto Done;
  }
  //
  // Provide the image with it's load options
      //
  Status = gBS->HandleProtocol (ImageHandle, &gEfiLoadedImageProtocolGuid, &ImageInfo);
  ASSERT_EFI_ERROR (Status);

  if (Option->LoadOptionsSize != 0) {
    ImageInfo->LoadOptionsSize  = Option->LoadOptionsSize;
    ImageInfo->LoadOptions      = Option->LoadOptions;
  }
  //
  // Before calling the image, enable the Watchdog Timer for
  // the 5 Minute period
  //
  gBS->SetWatchdogTimer (5 * 60, 0x0000, 0x00, NULL);

      Status = gBS->StartImage (ImageHandle, ExitDataSize, ExitData);
      DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Image Return Status = %r\n", Status));
  // System Halt when IDER boot fail !!
  if(ActiveManagementEnableIdeR ())
  {
    gST->ConOut->OutputString (
         gST->ConOut,
         L"IDER Boot Fail, system halt !! \r\n");

    while(1);
  }

  //
  // Clear the Watchdog Timer after the image returns
  //
  gBS->SetWatchdogTimer (0x0000, 0x0000, 0x0000, NULL);

Done:
  //
  // Clear Boot Current
  //
  gRT->SetVariable(
        L"BootCurrent",
        &gEfiGlobalVariableGuid,
        VarAttr,
        0,
        &Option->BootCurrent );

  return Status;
}

EFI_STATUS
BdsAsfBoot (
  OUT  EFI_DEVICE_PATH_PROTOCOL        **DevicePath
  )
/*++

Routine Description:

  Found out ASF boot options.

Arguments:

  DevicePath - The device path which describe where to load 
               the boot image or the legcy BBS device path 
               to boot the legacy OS

Returns:

  EFI_STATUS

--*/
{
  BOOLEAN EfiBoot;

  EfiBoot = FALSE;

  //
  // First we check ASF boot options Special Command
  //
  switch (mAsfBootOptions->SpecialCommand) {
  //
  // No additional special command is included; the Special Command Parameter has no
  // meaning.
  //
  case NOP:
    break;

  //
  // The Special Command Parameter can be used to specify a PXE
  // parameter. When the parameter value is 0, the system default PXE device is booted. All
  // other values for the PXE parameter are reserved for future definition by this specification.
  //
  case FORCE_PXE:
    if (mAsfBootOptions->SpecialCommandParam != 0) {
      //
      // ASF spec says 0 currently only option
      //
      return EFI_UNSUPPORTED;
    }

    if (EfiBoot == TRUE) {
      *DevicePath = BdsCreatePxeDevicePath (mAsfBootOptions->SpecialCommandParam);
    } else {
      *DevicePath = BdsCreateLegacyBootDevicePath (BBS_EMBED_NETWORK, mAsfBootOptions->SpecialCommandParam, FALSE);
    }
    break;

  //
  // The Special Command Parameter identifies the boot-media index for
  // the managed client. When the parameter value is 0, the default hard-drive is booted, when the
  // parameter value is 1, the primary hard-drive is booted; when the value is 2, the secondary
  // hard-drive is booted ¡V and so on.
  //
  case FORCE_HARDDRIVE:
  //
  // The Special Command Parameter identifies the boot-media
  // index for the managed client. When the parameter value is 0, the default hard-drive is
  // booted, when the parameter value is 1, the primary hard-drive is booted; when the value is 2,
  // the secondary hard-drive is booted ¡V and so on.
  //
  case FORCE_SAFEMODE:
    *DevicePath = BdsCreateLegacyBootDevicePath (BBS_TYPE_HARDDRIVE, mAsfBootOptions->SpecialCommandParam, FALSE);
    break;

  //
  // The Special Command Parameter can be used to specify a
  // diagnostic parameter. When the parameter value is 0, the default diagnostic media is booted.
  // All other values for the diagnostic parameter are reserved for future definition by this
  // specification.
  //
  case FORCE_DIAGNOSTICS:
    if (mAsfBootOptions->SpecialCommandParam != 0) {
      //
      // ASF spec says 0 currently only option
      //
      return EFI_UNSUPPORTED;
    }

    *DevicePath = BdsCreateShellDevicePath ();

    //
    // We want everything connected up for shell
    //
    BdsLibConnectAllDriversToAllControllers ();
    break;

  //
  // The Special Command Parameter identifies the boot-media index for
  // the managed client. When the parameter value is 0, the default CD/DVD is booted, when the
  // parameter value is 1, the primary CD/DVD is booted; when the value is 2, the secondary
  // CD/DVD is booted ¡V and so on.
  //
  case FORCE_CDDVD:
    *DevicePath = BdsCreateLegacyBootDevicePath (BBS_TYPE_CDROM, mAsfBootOptions->SpecialCommandParam, FALSE);
    break;

  default:
    return EFI_UNSUPPORTED;
    break;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BdsAmtBoot (
  OUT  EFI_DEVICE_PATH_PROTOCOL        **DevicePath
  )
/*++

Routine Description:

  Check IdeR boot device and Asf boot device

Arguments:

  DevicePath - The device path which describe where to load 
               the boot image or the legcy BBS device path 
               to boot the legacy OS

Returns:

  EFI_STATUS

--*/
{
  EFI_STATUS  Status;

  //
  // OEM command values; the interpretation of the Special Command and associated Special
  // Command Parameters is defined by the entity associated with the Enterprise ID.
  //
  if (ActiveManagementEnableIdeR ()) {
    //
    // Check if any media exist in Ider device
    //
    if (BdsCheckIderMedia ()) {
      *DevicePath = BdsCreateLegacyBootDevicePath (
                      BBS_TYPE_CDROM,
                      (mAsfBootOptions->SpecialCommandParam & IDER_BOOT_DEVICE_MASK) >> IDER_BOOT_DEVICE_SHIFT,
                      TRUE
                      );
    }

    Status = EFI_SUCCESS;
  } else {
    Status = BdsAsfBoot (DevicePath);
  }

  return Status;
}

EFI_STATUS
BdsBootViaAsf (
  IN  VOID
  )
/*++

Routine Description:

  Process ASF boot options and if available, attempt the boot 

Arguments:

  None.

Returns:

  EFI_SUCCESS - The command completed successfully
  Other       - Error!!

--*/
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  BDS_COMMON_OPTION         *BootOption;
  UINTN                     ExitDataSize;
  CHAR16                    *ExitData;

  Status      = EFI_SUCCESS;
  DevicePath  = NULL;

  //
  // Check if ASF Boot Options is present.
  //
  if (mAsfBootOptions->SubCommand != ASF_BOOT_OPTIONS_PRESENT) {
    return EFI_NOT_FOUND;
  }

  DevicePath = BuildDevicePathFromBootOrder();

  if(DevicePath != NULL)
  {

    BootOption = BdsCreateBootOption (DevicePath, L"ASF Boot");
    if (BootOption != NULL) {
      Status = AsfBootViaBootOption (BootOption, BootOption->DevicePath, &ExitDataSize, &ExitData);
      if (EFI_ERROR (Status)) {
        gBS->FreePool (BootOption);
      }

      gBS->FreePool (DevicePath);
    }
  }
  // UEFI BOOT fail, try Legacy Boot
  switch (mAsfBootOptions->IanaId) 
  {
  case ASF_INTEL_CONVERTED_IANA:
    Status = BdsAmtBoot (&DevicePath);
    break;

  case ASF_INDUSTRY_CONVERTED_IANA:
    Status = BdsAsfBoot (&DevicePath);
    break;
  }
  //
  // If device path was set, the we have a boot option to use
  //
  if (DevicePath == NULL) {
    return EFI_UNSUPPORTED;
  }

  BootOption = BdsCreateBootOption (DevicePath, L"ASF Boot");
  if (BootOption == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = AsfBootViaBootOption (BootOption, BootOption->DevicePath, &ExitDataSize, &ExitData);
  if (EFI_ERROR (Status)) {
    gBS->FreePool (BootOption);
  }

  gBS->FreePool (DevicePath);

  return Status;
}

BOOLEAN
BdsCheckIderMedia (
  IN  VOID
  )
/*++

Routine Description:
  This will return if Media in IDE-R is present.
  
Arguments:
  None.
      
Returns:
  True    Media is present.
  False   Media is not present.
  
--*/
{
  UINTN                     HandleNum;
  EFI_HANDLE                *HandleBuf;
  EFI_HANDLE                Handle;
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *DPath;
  UINTN                     Index;
  UINTN                     EventIndex;
  EFI_INPUT_KEY             Key;
  EFI_BLOCK_IO_PROTOCOL     *BlkIo;
  EFI_DISK_INFO_PROTOCOL    *DiskInfo;
  EFI_BLOCK_IO_MEDIA        *BlkMedia;
  VOID                      *Buffer;
  UINT8                     IdeBootDevice;
  UINT32                    IdeChannel;
  UINT32                    IdeDevice;

  IdeBootDevice = ActiveManagementIderBootDeviceGet ();

  DEBUG ((EFI_D_INFO | EFI_D_LOAD, "Ide Channel Device Index = %d\n", IdeBootDevice));

  //
  // Make sure the Legacy Boot Protocol is available
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiBlockIoProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuf
                  );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  for (Index = 0; Index < HandleNum; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuf[Index],
                    &gEfiDevicePathProtocolGuid,
                    &DPath
                    );
    if (!EFI_ERROR (Status)) {
      Status = gBS->LocateDevicePath (
                      &gEfiIderControllerDriverProtocolGuid,
                      &DPath,
                      &Handle
                      );
      if (!EFI_ERROR (Status)) {
        Status = gBS->HandleProtocol (
                        HandleBuf[Index],
                        &gEfiBlockIoProtocolGuid,
                        &BlkIo
                        );

        Status = gBS->HandleProtocol (
                        HandleBuf[Index],
                        &gEfiDiskInfoProtocolGuid,
                        &DiskInfo
                        );

        DiskInfo->WhichIde (DiskInfo, &IdeChannel, &IdeDevice);

        if (IdeBootDevice != (UINT8) (IdeChannel * 2 + IdeDevice)) {
          continue;
        }

        if (BlkIo->Media->MediaPresent) {
          if (HandleBuf != NULL) {
            gBS->FreePool (HandleBuf);
          }
          return TRUE;
        } else {
          while (TRUE) {
            BlkMedia  = BlkIo->Media;
            Buffer    = EfiLibAllocatePool (BlkMedia->BlockSize);
            if (Buffer) {
              BlkIo->ReadBlocks (
                      BlkIo,
                      BlkMedia->MediaId,
                      0,
                      BlkMedia->BlockSize,
                      Buffer
                      );
              gBS->FreePool (Buffer);
            }

            if (BlkMedia->MediaPresent) {
              if (HandleBuf != NULL) {
                gBS->FreePool (HandleBuf);
              }
              return TRUE;
            }

            gST->ConOut->OutputString (
                          gST->ConOut,
                          L"Boot disk missing, please insert boot disk and press ENTER\r\n"
                          );
            Key.ScanCode    = 0;
            Key.UnicodeChar = 0;
            gBS->RestoreTPL (EFI_TPL_APPLICATION);
            while (!(Key.ScanCode == 0 && Key.UnicodeChar == L'\r')) {
              Status = gBS->WaitForEvent (1, &(gST->ConIn->WaitForKey), &EventIndex);
              gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
            }

            gBS->RaiseTPL (EFI_TPL_DRIVER);
          }

          if (HandleBuf != NULL) {
            gBS->FreePool (HandleBuf);
          }
          return FALSE;
        }
      }
    }
  }

  if (HandleBuf != NULL) {
    gBS->FreePool (HandleBuf);
  }
  return FALSE;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
