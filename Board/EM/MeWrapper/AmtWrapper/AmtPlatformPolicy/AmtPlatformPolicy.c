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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPlatformPolicy.c 11    9/21/15 10:12p Tristinchou $
//
// $Revision: 11 $
//
// $Date: 9/21/15 10:12p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPlatformPolicy.c $
// 
// 11    9/21/15 10:12p Tristinchou
// [TAG]  		EIP238392
// [Category]  	Improvement
// [Description]  	Disable USB provision while Intel AMT is disabled in
// setup
// 
// 10    5/14/14 9:45p Tristinchou
// [TAG]  		EIP160730
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 9     12/16/13 9:55p Tristinchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Free memory while error occur in InstallDiskInfo()
// 
// 8     8/27/13 4:21a Tristinchou
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix system hangs while boot with ME 1.5MB firmware.
// [Files]  		AmtPlatformPolicy.c
// 
// 7     8/22/13 8:51a Tristinchou
// [TAG]  		EIP131034
// [Category]  	Improvement
// [Description]  	The system will hang after create/ reset/delete raid
// mode
// [Files]  		AmtPlatformPolicy.c
// 
// 6     11/07/12 8:47a Klzhan
// Clear Cira request item after loaded.
// 
// 5     9/19/12 6:56a Klzhan
// Fix Windows capsule update fail.
// 
// 4     7/02/12 11:39p Klzhan
// [TAG]  		EIP94113
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC0.6
// 
// 3     5/14/12 4:50a Klzhan
// [TAG]  		EIP89952
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC 0.56
// [Files]  		AmtPlatformPolicy.c
// AmtPlatformPolicy.h
// AmtPlatformPolicy.sdl
// AmtPlatformPolicy.mak
// AmtPlatformPolicy.dxs
// AmtPlatformPolicy.cif
// 
// 2     4/24/12 12:41a Klzhan
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 8     9/29/11 11:47p Klzhan
// Fill Amt Wrapper protocol with setup data.
// 
// 7     9/26/11 6:19a Klzhan
// [TAG]  		EIP70516
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME 8.0 RC 0.8
// [Files]  		AmtPlatformPolicy.c
// AmtPlatformPolicy.h
// AmtPlatformPolicy.sdl
// AmtPlatformPolicy.mak
// AmtPlatformPolicy.dxs
// AmtPlatformPolicy.cif
// 
// 6     7/08/11 4:23a Klzhan
// [TAG]  		EIP64189
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Update ME RC to 0.7
// 
// 5     5/24/11 5:01a Klzhan
// Add support ME RC 0.60
// 
// 4     4/18/11 9:45a Klzhan
// [TAG]  		EIP58005
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Move ME FW downgrade related code to ME platform
// policy.
// 
// 3     4/18/11 9:17a Klzhan
// Improvement : Update DXE_PLATFORM_AMT_POLICY_PROTOCOL_REVISION from 7
// to A.
// 
// 2     3/29/11 3:48a Klzhan
// A token to keep ME always in Disable Mode.
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AmtPlatformPolicy.c
//
// Description:	
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "AmtPlatformPolicy.h"
#include "token.h"
#include <SetupDataDefinition.h>
DXE_AMT_POLICY_PROTOCOL mDxePlatformAmtPolicy       = { 0 };
INSTALL_DISK_INFO_PROTOCOL      mInstallDiskInfo = { InstallDiskInfo };
UINT64                  mPciDeviceFilterOutTable[]  = { EFI_MAX_ADDRESS, };
#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

#define AMT_READY_TO_BOOT_PROTOCOL_GUID \
  { \
    0x40b09b5a, 0xf0ef, 0x4627, 0x93, 0xd5, 0x27, 0xf0, 0x4b, 0x75, 0x4d, 0x5 \
  }

#define END_DEVICE_PATH                 0x7F
#define END_DEVICE_PATH1                0xFF
#define NODE_LENGTH(pPath) (*(UINT16*)&(pPath)->Length[0])
#define NEXT_NODE(pPath) ((EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(pPath)+NODE_LENGTH(pPath)))
#define isEndNode(pDp) ((pDp)->Type==END_DEVICE_PATH||(pDp)->Type==END_DEVICE_PATH1)
EFI_GUID  gAmtReadyToBootProtocolGuid = AMT_READY_TO_BOOT_PROTOCOL_GUID;
EFI_GUID gEfiDiskInfoProtocolGuid   = EFI_DISK_INFO_PROTOCOL_GUID;
EFI_GUID gDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
UINT8 GetDevicePathSubtype(EFI_DEVICE_PATH_PROTOCOL *Dp, UINT8 Type);

//
// Driver entry point
//
EFI_DRIVER_ENTRY_POINT (AmtPlatformPolicyEntryPoint)
EFI_STATUS
EFIAPI
InstallDiskInfo (
  VOID
  )
{
	EFI_STATUS Status;
	UINTN BlockIoHandleCount = 0;
	UINTN DiskInfoHandleCount = 0;
	EFI_HANDLE *BlockIoHandleBuffer  = NULL;
	EFI_HANDLE *DiskInfoHandleBuffer = NULL;
	UINTN UsedBlockIoHandle = 0;
	UINTN UsedDiskInfoHandle = 0;
	EFI_DISK_INFO_PROTOCOL *DiskInfoProtocol;
	EFI_DISK_INFO_PROTOCOL *DiskInfoProtocolBuffer;
	EFI_BLOCK_IO_PROTOCOL *BlockIoProtocol;
	EFI_DEVICE_PATH_PROTOCOL *DevicePathProtocol;
	UINT8 DevicePathSubtype = 0;
	IDENTIFY_DATA *IdentifyData = NULL;
	UINT32 BufferSize = sizeof (IDENTIFY_DATA);
	UINT8 ThisDiskInfoHandleIsHdd = 0;	// 1 is HDD, 0 is ODD 
	UINT8 ThisBlockIoHandleIsHdd = 0;	// 1 is HDD, 0 is ODD

	//Locate all handle which have BlockIo
	Status = gBS->LocateHandleBuffer(
					ByProtocol,
					&gEfiBlockIoProtocolGuid,
					NULL,
					&BlockIoHandleCount,
					&BlockIoHandleBuffer );
	if(EFI_ERROR(Status))
        goto ErrorExit;

	//Locate all handle which have DiskInfo
	Status = gBS->LocateHandleBuffer(
					ByProtocol,
					&gEfiDiskInfoProtocolGuid,
					NULL,
					&DiskInfoHandleCount,
					&DiskInfoHandleBuffer );
	if(EFI_ERROR(Status))
        goto ErrorExit;

	if( DiskInfoHandleCount != 0 )
	{
		for( UsedBlockIoHandle = 0 ; UsedBlockIoHandle < BlockIoHandleCount ; UsedBlockIoHandle++ )
		{
			ThisBlockIoHandleIsHdd = 0;
			//Block to install DiskInfoProtocol to USB
			Status = gBS->HandleProtocol(
						BlockIoHandleBuffer[UsedBlockIoHandle],
						&gDevicePathProtocolGuid,
						&DevicePathProtocol);
			if( !EFI_ERROR(Status) )
			{
				DevicePathSubtype = GetDevicePathSubtype( DevicePathProtocol, MESSAGING_DEVICE_PATH );
			}
			if( DevicePathSubtype == MSG_USB_DP ||
				DevicePathSubtype == MSG_USB_CLASS_DP )
			{
				continue;
			}
			//Block to install DiskInfoProtocol to Partition
			Status = gBS->HandleProtocol(
						BlockIoHandleBuffer[UsedBlockIoHandle],
						&gEfiBlockIoProtocolGuid,
						&BlockIoProtocol);
			if(EFI_ERROR(Status))
	  			goto ErrorExit;

			if( BlockIoProtocol->Media->LogicalPartition )
			{
				continue;
			}

			//Handle is HDD or ODD
			if( BlockIoProtocol->Media->RemovableMedia == 0 )
			{
				ThisBlockIoHandleIsHdd = 1;
			}

			for( UsedDiskInfoHandle = 0 ; UsedDiskInfoHandle < DiskInfoHandleCount ; UsedDiskInfoHandle++ )
			{
				ThisDiskInfoHandleIsHdd = 0;
				if( DiskInfoHandleBuffer[UsedDiskInfoHandle] == NULL )
				{
					continue;
				}

				//Handle is HDD or ODD
				Status = gBS->HandleProtocol(
								DiskInfoHandleBuffer[UsedDiskInfoHandle],
								&gEfiDiskInfoProtocolGuid,
								&DiskInfoProtocol);
				if(EFI_ERROR(Status))
	  				goto ErrorExit;

				IdentifyData = AllocatePool(BufferSize);
                if( IdentifyData == NULL )
                    goto ErrorExit;

				Status = DiskInfoProtocol->Identify( DiskInfoProtocol, IdentifyData, &BufferSize );
				if(EFI_ERROR(Status))
	  				goto ErrorExit;

				if( IdentifyData->LBA_48 !=0 )
				{
					ThisDiskInfoHandleIsHdd = 1;
				}

				//If handles the same type( HDD or ODD)
				if(	ThisDiskInfoHandleIsHdd == ThisBlockIoHandleIsHdd )
				{
					Status = gBS->HandleProtocol(
									BlockIoHandleBuffer[UsedBlockIoHandle],
									&gEfiDiskInfoProtocolGuid,
									&DiskInfoProtocolBuffer );
					//If this BlockIoHandle isn't installed DiskInfoProtocol
					if(EFI_ERROR(Status))
					{
						Status = gBS->InstallMultipleProtocolInterfaces(
											&BlockIoHandleBuffer[UsedBlockIoHandle],
											&gEfiDiskInfoProtocolGuid,
											DiskInfoProtocol,
											NULL );
						if( !EFI_ERROR(Status) )
						{
							FreePool(IdentifyData);
							//Release used handle pointer
							DiskInfoHandleBuffer[UsedDiskInfoHandle] = NULL;
							break;
						}
					}
				}
				FreePool(IdentifyData);
			}
		}
	}
	FreePool(BlockIoHandleBuffer);
	FreePool(DiskInfoHandleBuffer);

	return EFI_SUCCESS;

ErrorExit:
    if( BlockIoHandleBuffer != NULL )
        FreePool(BlockIoHandleBuffer);
    if( DiskInfoHandleBuffer != NULL )
        FreePool(DiskInfoHandleBuffer);
    if( IdentifyData != NULL )
        FreePool(IdentifyData);

    return EFI_NOT_FOUND;
}

UINT8 GetDevicePathSubtype(EFI_DEVICE_PATH_PROTOCOL *Dp, UINT8 Type)
{
    UINT8 SubType;

    if (Dp == NULL) return 0;
    SubType = 0;

    for( ; !(isEndNode(Dp)); Dp=NEXT_NODE(Dp))
        if (Dp->Type == Type) SubType = Dp->SubType;
    return SubType;
}

//
// Function implementations
//
EFI_STATUS
EFIAPI
AmtPlatformPolicyEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
/*++
 
Routine Description:
 
  Initilize Intel AMT DXE Platform Policy
  
Arguments:
 
  ImageHandle       Image handle of this driver.
  SystemTable       Global system service table.
 
Returns:
 
  EFI_SUCCESS           Initialization complete.
  EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  EFI_DEVICE_ERROR      Device error, driver exits abnormally.
 
--*/
{
  EFI_STATUS                Status;
  UINT32                    SetupVarAttr;
  UINTN                     VariableSize;
  UINT32                    MebxVarAttr;
  ME_BIOS_EXTENSION_SETUP   MeBiosExtensionSetupData;
  SETUP_DATA                SetupData;
  EFI_GUID                  gSetupGuid = SETUP_GUID;
  DXE_MBP_DATA_PROTOCOL     *mBIOSPayLoad;
  EFI_HANDLE                Handle;

  EfiInitializeDriverLib (ImageHandle, SystemTable);

  Handle = NULL;

  Status = gBS->LocateProtocol (
               &gMeBiosPayloadDataProtocolGuid,
               NULL,
               &mBIOSPayLoad
               );
  if( EFI_ERROR(Status) ) {
    // Install Dummy MeBios Payload Data Protocol for avoiding relating driver
    // not run. (For EIP#96807 - EFI Capsule Update)
    SetupVarAttr = 0;
    VariableSize = sizeof(SETUP_DATA);
    Status = gRT->GetVariable( L"Setup", &gSetupGuid, \
                                    &SetupVarAttr, &VariableSize, &SetupData );
    if( EFI_ERROR(Status) ) return Status;
    {    
      DXE_MBP_DATA_PROTOCOL   mMbpData;
      ZeroMem (&mMbpData, sizeof (DXE_MBP_DATA_PROTOCOL));
      mMbpData.Revision = DXE_MBP_DATA_PROTOCOL_REVISION_2;
      mMbpData.MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType = SetupData.MeImageType;
      mMbpData.Handle = NULL;
      Status = gBS->InstallMultipleProtocolInterfaces (
                      &mMbpData.Handle,
                      &gMeBiosPayloadDataProtocolGuid,
                      &mMbpData,
                      NULL
                      );
      if (!EFI_ERROR(Status)) mBIOSPayLoad = &mMbpData;
    }    
  }  
  if (mBIOSPayLoad->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != INTEL_ME_5MB_FW) {
    return EFI_UNSUPPORTED;
  }

  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmtReadyToBootProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mInstallDiskInfo
                  );

  SetupVarAttr = 0;
  VariableSize = sizeof(SETUP_DATA);
  //
  // Get iAMT configuration from Setup Data
  //	
  Status = gRT->GetVariable(
                    L"Setup",
                    &gSetupGuid,
                    &SetupVarAttr,
                    &VariableSize,
                    &SetupData );

  //
  // AMT DXE Policy Init
  //
  mDxePlatformAmtPolicy.Revision      = DXE_PLATFORM_AMT_POLICY_PROTOCOL_REVISION_1;
///////////////////////////////////////////////////////////////////////////
  if (EFI_ERROR(Status))  // Default Setting for AMT
  {
      //
      // Initialzie the Me Configuration
      //
      mDxePlatformAmtPolicy.AmtConfig.AsfEnabled                = 1;
      mDxePlatformAmtPolicy.AmtConfig.iAmtEnabled               = 1;
      mDxePlatformAmtPolicy.AmtConfig.WatchDog                  = 0;
      mDxePlatformAmtPolicy.AmtConfig.WatchDogTimerOs           = 0;
      mDxePlatformAmtPolicy.AmtConfig.WatchDogTimerBios         = 0;
      mDxePlatformAmtPolicy.AmtConfig.CiraRequest               = 0;
      mDxePlatformAmtPolicy.AmtConfig.CiraTimeout               = 0;
      mDxePlatformAmtPolicy.AmtConfig.UnConfigureMe             = 0;
      mDxePlatformAmtPolicy.AmtConfig.HideUnConfigureMeConfirm  = 0;
      mDxePlatformAmtPolicy.AmtConfig.MebxDebugMsg              = 0;
      mDxePlatformAmtPolicy.AmtConfig.USBProvision              = 0;
      mDxePlatformAmtPolicy.AmtConfig.FWProgress                = 1;
      mDxePlatformAmtPolicy.AmtConfig.iAmtbxSelectionScreen     = 0;
      mDxePlatformAmtPolicy.AmtConfig.iAmtbxHotkeyPressed       = 0;
      mDxePlatformAmtPolicy.AmtConfig.AtEnabled                 = 1;    
      mDxePlatformAmtPolicy.AmtConfig.ManageabilityMode         = 1;
      //
      // Oem Resolution Settings
      //
      mDxePlatformAmtPolicy.AmtConfig.MebxNonUiTextMode         = 0;    // MEBX_TEXT_AUTO
      mDxePlatformAmtPolicy.AmtConfig.MebxUiTextMode            = 0;    // MEBX_TEXT_AUTO
      mDxePlatformAmtPolicy.AmtConfig.MebxGraphicsMode          = 0;    // MEBX_GRAPHICS_AUTO

  } else {
      mDxePlatformAmtPolicy.AmtConfig.AsfEnabled               = SetupData.Asf;
      mDxePlatformAmtPolicy.AmtConfig.iAmtEnabled              = SetupData.Amt;
      mDxePlatformAmtPolicy.AmtConfig.WatchDog                 = SetupData.WatchDog;
      mDxePlatformAmtPolicy.AmtConfig.WatchDogTimerOs          = SetupData.WatchDogTimerOs;
      mDxePlatformAmtPolicy.AmtConfig.WatchDogTimerBios        = SetupData.WatchDogTimerBios;
      mDxePlatformAmtPolicy.AmtConfig.CiraRequest              = SetupData.AmtCiraRequest;
      mDxePlatformAmtPolicy.AmtConfig.CiraTimeout              = SetupData.AmtCiraTimeout;
      mDxePlatformAmtPolicy.AmtConfig.UnConfigureMe            = SetupData.UnConfigureMe;
      mDxePlatformAmtPolicy.AmtConfig.HideUnConfigureMeConfirm = SetupData.HideUnConfigureMeConfirm;
      mDxePlatformAmtPolicy.AmtConfig.MebxDebugMsg             = SetupData.MebxDebugMsg;
      mDxePlatformAmtPolicy.AmtConfig.USBProvision             = SetupData.USBProvision;
      mDxePlatformAmtPolicy.AmtConfig.FWProgress               = SetupData.FWProgress;
      mDxePlatformAmtPolicy.AmtConfig.iAmtbxSelectionScreen    = SetupData.AmtbxSelectionScreen;
      mDxePlatformAmtPolicy.AmtConfig.iAmtbxHotkeyPressed      = SetupData.AmtbxHotKeyPressed;
      mDxePlatformAmtPolicy.AmtConfig.AtEnabled                = 1;
      mDxePlatformAmtPolicy.AmtConfig.ManageabilityMode        = 1;
      //
      // Oem Resolution Settings
      //
      mDxePlatformAmtPolicy.AmtConfig.MebxNonUiTextMode         = 0;    // MEBX_TEXT_AUTO
      mDxePlatformAmtPolicy.AmtConfig.MebxUiTextMode            = 0;    // MEBX_TEXT_AUTO
      mDxePlatformAmtPolicy.AmtConfig.MebxGraphicsMode          = 0;    // MEBX_GRAPHICS_AUTO

      if(SetupData.AmtbxHotKeyPressed == 1)
          SetupData.AmtbxHotKeyPressed = 0;

      if(SetupData.AmtCiraRequest == 1)
          SetupData.AmtCiraRequest = 0;

      if(SetupData.UnConfigureMe == 1)
          SetupData.UnConfigureMe = 0;

      if(SetupData.Amt == 0)
          mDxePlatformAmtPolicy.AmtConfig.USBProvision = USB_PROVISION_DEFAULT_WITHOUT_AMT;
  }

///////////////////////////////////////////////////////////////////////////
  mDxePlatformAmtPolicy.AmtConfig.PciDeviceFilterOutTable   = (UINT32) (UINTN) mPciDeviceFilterOutTable;
  //
  // Please don't change the default value of ForcMebxSyncUp and 
  // This let customer to force MEBX execution if they need and 
  //
  mDxePlatformAmtPolicy.AmtConfig.ForcMebxSyncUp            = 0;

  //
  // Get BIOS Sync-up data from MEBx to AMT platform policy
  //  
  MebxVarAttr = 0;
  VariableSize = sizeof (MeBiosExtensionSetupData);
  Status = gRT->GetVariable (
                  gEfiMeBiosExtensionSetupName,
                  &gEfiMeBiosExtensionSetupGuid,
                  &MebxVarAttr,
                  &VariableSize,
                  &MeBiosExtensionSetupData
                  );
  if (EFI_ERROR (Status)) {
    mDxePlatformAmtPolicy.AmtConfig.ManageabilityMode = 0;
  } else {
    mDxePlatformAmtPolicy.AmtConfig.ManageabilityMode = MeBiosExtensionSetupData.PlatformMngSel;
  }
  //
  // Install protocol to to allow access to this Policy.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gDxePlatformAmtPolicyGuid,
                  &mDxePlatformAmtPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Get iAMT configuration from Setup Data
  //
  VariableSize = sizeof(SETUP_DATA);
  Status = gRT->SetVariable (
                    L"Setup",
                    &gSetupGuid,
                    SetupVarAttr,
                    VariableSize,
                    &SetupData );

  return Status;
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