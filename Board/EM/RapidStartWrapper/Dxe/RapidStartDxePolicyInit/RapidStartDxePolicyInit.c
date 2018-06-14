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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxePolicyInit/RapidStartDxePolicyInit.c 9     5/13/14 4:55a Joshchou $
//
// $Revision: 9 $
//
// $Date: 5/13/14 4:55a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxePolicyInit/RapidStartDxePolicyInit.c $
// 
// 9     5/13/14 4:55a Joshchou
// [TAG]  		EIP167032
// [Category]  	Improvement
// [Description]  	Review the variable's attribute, we shouldn't use
// runtime attribute with setup variable.
// [Files]  		RapidStartDxePolicyInit.h
// RapidStartDxePolicyInit.c
// RapidStartDxePolicyInit.cif
// 
// 8     6/21/13 5:59a Joshchou
// [TAG]  		EIP126792
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Can't do AMI capsule when Intel Rapid Start eanble
// [RootCause]  	CMOS RapidStartFlag does not clear.
// [Solution]  	Clear RapidStartFlag when cold boot.
// 
// 7     1/15/13 4:44a Bensonlai
// [TAG]  		EIP112263
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	[RapidStart] Instant-on can't work
// [RootCause]  	Intel reference code can't work on AMI base.
// [Solution]  	Modified the PeiGfxDriver.dxs and RapidStartDxe.dxs for
// AMI code
// [Files]  		RapidStartDxePolicyInit.c, RapidStartSetup.uni,
// RapidStartSetup.sdl, RapidStartSetup.sd, PeiGfxDriver.dxs,
// RapidStartDxe.dxs
// 
// 6     1/13/13 7:46a Bensonlai
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Disabling the RapidStart while STAT mode in the IDE
// mode
// [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
// RapidStartDxePolicyInit.mak, RapidStartSetup.c, RapidStartSetup.mak,
// RapidStartSetup.sd, RapidStartSetup.sdl
// 
// 5     12/11/12 10:59p Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Removed unused code
// [Files]  		RapidStartDxePolicyInit.c
// 
// 4     12/07/12 1:15a Bensonlai
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	When installed memory size less than HDD partition size of
// teh RapidStart, it still can work.
// [RootCause]  	The RAPID_START_PERSISTENT_DATA wasn't updated in the
// BdsAllDriversConnectedCallback().
// [Solution]  	Get the real total size of memory directly.
// [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
// RapidStartDxePolicyInit.mak
// 
// 3     12/03/12 2:12a Bensonlai
// [TAG]  		EIP107865 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	While system has no disk drives, we still free the null
// pointer IdentifyDriveInfo/HandleBuffer and that will cause an assert
// error with DEBUG_MODE=1.
// [Solution]  	Improved the function of SsdDetection.
// 
// 2     11/15/12 12:24a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	Move the RAPID_START_PARTITION_DETECT_BEFORE_SETUP to
// RapidStartDxePolicyInit.c
// 
// 1     10/15/12 4:40a Bensonlai
// [TAG]  		None
// [Category]  	Improvement
// [Description]  	[Category] Improvement
// [Severity] Important
// [Description] Rename all IFFS sting to Rapid Start.
// [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
// 
// [Category] Improvement
// [Severity] Important
// [Description] Implementation of the LOCK_DISABLE_RAPID_START_IF_NO_SSD
// using EDKII.
// [Files] Board\EM\RapidStartWrapper\Dxe\RapidStartDxePolicyInit\*.*
// [Files]  		RapidStartDxePolicyInit.cif
// RapidStartDxePolicyInit.sdl
// RapidStartDxePolicyInit.mak
// RapidStartDxePolicyInit.h
// RapidStartDxePolicyInit.c
// RapidStartDxePolicyInit.dxs
// RapidStartDxePolicyInit.inf
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartDxePolicyInit.c
//
// Description:	This file is a wrapper for Intel RapidStart Platform Policy driver.
//              Get Setup Value to initilize Intel DXE Platform Policy.
//
//<AMI_FHDR_END>
//**********************************************************************

#include "RapidStartDxePolicyInit.h"

RAPID_START_PLATFORM_POLICY_PROTOCOL  mDxePlatformRapidStartPolicy;
EFI_GUID                              gRapidStartPlatformPolicyProtocolGuid = RAPID_START_PLATFORM_POLICY_PROTOCOL_GUID;

//
// Function implementations
//
#if LOCK_DISABLE_RAPID_START_IF_NO_SSD
BOOLEAN SsdDetection (
    VOID
)
{
    EFI_STATUS               Status;
    UINTN                    HandleCount;
    EFI_HANDLE               *HandleBuffer;
    UINT8                    Index;
    PCI_DEVICE_PATH          *PciDevicePath;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL *DevicePathNode;
    EFI_DISK_INFO_PROTOCOL   *DiskInfo;
    EFI_IDENTIFY_DATA        *IdentifyDriveInfo;
    UINT32                   BufferSize = 0;

    Status = gBS->LocateHandleBuffer ( ByProtocol, \
                                       &gEfiDiskInfoProtocolGuid, \
                                       NULL, \
                                       &HandleCount, \
                                       &HandleBuffer \
                                     );

    if ( EFI_ERROR(Status) ) return FALSE;

    for (Index = 0; Index < HandleCount; Index++) {
        Status = gBS->HandleProtocol ( HandleBuffer[Index], \
                                       &gEfiDevicePathProtocolGuid, \
                                       (VOID *) &DevicePath \
                                     );

        if ( EFI_ERROR(Status) ) {
               continue;
        }

        DevicePathNode = DevicePath;
        while (!IsDevicePathEnd (DevicePathNode)) {
            if ((DevicePathType (DevicePathNode) == HARDWARE_DEVICE_PATH) &&
                    (DevicePathSubType (DevicePathNode) == HW_PCI_DP)
               ) {
                PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
                break;
            }

            DevicePathNode = NextDevicePathNode (DevicePathNode);
        }


        if (PciDevicePath == NULL) continue;

        if ( ((PciDevicePath->Device == PCI_DEVICE_NUMBER_PCH_SATA) && (PciDevicePath->Function == PCI_FUNCTION_NUMBER_PCH_SATA)) ||
             ((PciDevicePath->Device == PCI_DEVICE_NUMBER_PCH_SATA) && (PciDevicePath->Function == PCI_FUNCTION_NUMBER_PCH_SATA2)) ) {

            Status = gBS->HandleProtocol ( HandleBuffer[Index], \
                                           &gEfiDiskInfoProtocolGuid, \
                                           &DiskInfo \
                                         );

            if ( EFI_ERROR(Status) ) {
                continue;
            }

            BufferSize        = sizeof (EFI_IDENTIFY_DATA);
            IdentifyDriveInfo = AllocatePool (BufferSize);
            if (IdentifyDriveInfo == NULL) {
                FreePool (HandleBuffer);
                return FALSE;
            }

            Status = DiskInfo->Identify (
                         DiskInfo,
                         IdentifyDriveInfo,
                         &BufferSize
                     );

            if ( EFI_ERROR(Status) ) {
                FreePool (IdentifyDriveInfo);
                continue;
            }

            if (IdentifyDriveInfo->AtaData.reserved_160_255[57] == 0x0001) {
                FreePool (IdentifyDriveInfo);
                FreePool (HandleBuffer);
                return TRUE;
            }

            FreePool (IdentifyDriveInfo);
        }
    }

    if (HandleCount > 0) {
        FreePool (HandleBuffer);
    }
    return FALSE;
}

VOID
SsdDetectionCallback (
    IN EFI_EVENT Event,
    IN VOID      *Context
)
{

    EFI_STATUS  Status;
    UINTN       VariableSize;
    SETUP_DATA  SetupData; 
    UINT32      Attributes = 0;

    VariableSize = sizeof( SETUP_DATA );
    Status = gRT->GetVariable( L"Setup", \
                               &SetupGuid, \
                               &Attributes, \
                               &VariableSize, \
                               &SetupData );

    if ( EFI_ERROR(Status) ) {
        gBS->CloseEvent (Event);
        ASSERT_EFI_ERROR (Status);
        return;
    }

    if (!SsdDetection()) {
        SetupData.RapidStartLock = 1;
        SetupData.RapidStartEnabled = 0;
    } else {
        SetupData.RapidStartLock = 0;
    }

    Status = gRT->SetVariable( L"Setup", \
                               &SetupGuid, \
                               Attributes, \
                               sizeof (SETUP_DATA), \
                               &SetupData
                             );

    if ( EFI_ERROR(Status) ) {
        gBS->CloseEvent (Event);
        ASSERT_EFI_ERROR (Status);
        return;
    }

    gBS->CloseEvent (Event);
}

VOID
SsdDetectionRegisterCallBack (
    VOID
)
{
    EFI_EVENT   Event;
    VOID        *NotifyReg;
    EFI_STATUS  Status;

    Status = gBS->CreateEvent (
                 EFI_EVENT_NOTIFY_SIGNAL,
                 EFI_TPL_CALLBACK,
                 SsdDetectionCallback,
                 NULL,
                 &Event
             );

    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    Status = gBS->RegisterProtocolNotify (
                 &gNotifyProtocolGuid ,
                 Event,
                 &NotifyReg
             );

    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    return;
}
#endif

#ifdef RAPID_START_PARTITION_DETECT_BEFORE_SETUP
VOID
BdsAllDriversConnectedCallback (
    IN EFI_EVENT Event,
    IN VOID      *Context
)
{
    EFI_STATUS                            Status;
    EFI_GUID                              RapidStartPartitionProtocolGuid = RAPID_START_PARTITION_STATUS_PROTOCOL_GUID;
    RAPID_START_PERSISTENT_DATA           *mRapidStartData;
    UINTN                                 MchBase;

    mRapidStartData = AllocateZeroPool (sizeof(RAPID_START_PERSISTENT_DATA));
    if (mRapidStartData == NULL) {
       return;
    }

    MchBase               = MmPciAddress (0, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
    mRapidStartData->Tolm = MmioRead32 (MchBase + R_SA_BDSM) & B_SA_BDSM_BDSM_MASK;
    mRapidStartData->Tohm = MmioRead64 (MchBase + R_SA_TOUUD) & B_SA_TOUUD_TOUUD_MASK;
    ///
    /// Calculate total size of memory to be stored
    ///
    mRapidStartData->TotalMem = mRapidStartData->Tolm;
    if (mRapidStartData->Tohm > MEM_EQU_4GB) {
      mRapidStartData->TotalMem += mRapidStartData->Tohm - MEM_EQU_4GB;
    }

    //
    // Rapid Start has been enabled, check if Rapid Start store valid.
    //
    Status = SearchRapidStartStore (
                 &mDxePlatformRapidStartPolicy,
                 &(mRapidStartData->StoreSectors),
                 &(mRapidStartData->StoreLbaAddr),
                 &(mRapidStartData->StoreSataPort)
             );
    if ( (EFI_ERROR (Status)) ||
            (MEM_TO_SECT (mRapidStartData->TotalMem) > mRapidStartData->StoreSectors) &&
            (mDxePlatformRapidStartPolicy.ActivePageThresholdSupport == 0) ) {
        //
    } else {
        Status = gBS->InstallProtocolInterface (
                     &gImageHandle,
                     &RapidStartPartitionProtocolGuid,
                     EFI_NATIVE_INTERFACE,
                     NULL );
        ASSERT_EFI_ERROR (Status);
    }

    gBS->CloseEvent (Event);
}

VOID
RegisterForBdsAllDriversConnected (
    IN EFI_HANDLE ImageHandle
)
{
    EFI_EVENT   Event;
    VOID        *NotifyReg;
    EFI_STATUS  Status;

    gImageHandle = ImageHandle;

    Status = gBS->CreateEvent (
                 EFI_EVENT_NOTIFY_SIGNAL,
                 EFI_TPL_CALLBACK,
                 BdsAllDriversConnectedCallback,
                 NULL,
                 &Event
             );

    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    Status = gBS->RegisterProtocolNotify (
                 &gBdsAllDriversConnectedProtocolGuid,
                 Event,
                 &NotifyReg
             );

    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    return;
}
#endif

#if SYNC_UP_DRIVER_AND_BIOS_VARIABLE
VOID
SyncUpDriverAndBiosVariable (
        VOID
)
{
    EFI_STATUS       Status;
    UINTN            VariableSize;
    RAPID_START_WRAPPER_SMM_DATA  RapidStartWrapperSmmData;
    UINT32      Attributes = 0;
    SETUP_DATA  SetupData;
 
    VariableSize = sizeof( RAPID_START_WRAPPER_SMM_DATA );
    Status = gRT->GetVariable( L"RstWrapVar",
                               &RapidStartWrapperSmmDataGuid,
                               &Attributes,
                               &VariableSize,
                               &RapidStartWrapperSmmData );    
    
    //TRACE((-1,"SYNC_UP_DRIVER_AND_BIOS_VARIABLE Get Setup Variable RstWrapVar Attributes = %x.\n",Attributes));

    if ( EFI_ERROR (Status) ) {
        //TRACE((-1,"SYNC_UP_DRIVER_AND_BIOS_VARIABLE Get Variable Failed!\n"));
        return;
    }
    else{
//        TRACE((-1,"SYNC_UP_DRIVER_AND_BIOS_VARIABLE S3WakeTimerMin = %d\n",RapidStartWrapperSmmData.S3WakeTimerMin));
//        TRACE((-1,"SYNC_UP_DRIVER_AND_BIOS_VARIABLE EntryOnS3RtcWake = %x\n",RapidStartWrapperSmmData.EntryOnS3RtcWake));
//        TRACE((-1,"SYNC_UP_DRIVER_AND_BIOS_VARIABLE EntryOnS3CritBattWake = %x\n",RapidStartWrapperSmmData.EntryOnS3CritBattWake));

        VariableSize = sizeof( SETUP_DATA );
        Status = gRT->GetVariable( L"Setup",
                                   &SetupGuid,
                                   &Attributes,
                                   &VariableSize,
                                   &SetupData );    

//        TRACE((-1,"SYNC_UP_DRIVER_AND_BIOS_VARIABLE Get Setup Variable Attributes = %x.\n",Attributes));
        SetupData.S3WakeTimerMin = RapidStartWrapperSmmData.S3WakeTimerMin;
        SetupData.EntryOnS3RtcWake = RapidStartWrapperSmmData.EntryOnS3RtcWake;
        SetupData.EntryOnS3CritBattWake = RapidStartWrapperSmmData.EntryOnS3CritBattWake;
 
        Status = gRT->SetVariable( L"Setup", \
                                   &SetupGuid, \
                                   Attributes, \
                                   sizeof (SETUP_DATA), \
                                   &SetupData );
    
        return; 
    }
    
    
}
#endif

VOID
SetCriticalBatteryThreshole (
    IN UINT8 Value
)
{
    UINT8 RtcIndexPort;
    UINT8 RtcDataPort;

    //
    // CMOS access registers (using alternative access not to handle NMI bit)
    //
    if (FFS_CBTH_DATA_REG < 0x80) {
        //
        // First bank
        //
        RtcIndexPort  = 0x74;
        RtcDataPort   = 0x75;
    } else {
        //
        // Second bank
        //
        RtcIndexPort  = 0x76;
        RtcDataPort   = 0x77;
    }

    IoWrite8 (RtcIndexPort, FFS_CBTH_DATA_REG & 0x7F);
    IoWrite8 (RtcDataPort, Value);
}

/**
  Initilize Intel RapidStart DXE Platform Policy

  @param[in] ImageHandle       Image handle of this driver.
  @param[in] SystemTable       Global system service table.

  @retval EFI_SUCCESS           Initialization complete.
  @exception EFI_UNSUPPORTED       The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES  Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR      Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
RapidStartDxePolicyInitEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    UINTN       VariableSize;
    SETUP_DATA  SetupData;
    PCH_SERIES  PchSeries = GetPchSeries();
    ///
    /// Initialize the EFI Driver Library
    ///
    ZeroMem (&mDxePlatformRapidStartPolicy, sizeof (RAPID_START_PLATFORM_POLICY_PROTOCOL));

    VariableSize = sizeof( SETUP_DATA );
    Status = gRT->GetVariable( L"Setup",
                               &SetupGuid,
                               NULL,
                               &VariableSize,
                               &SetupData );

    if ( EFI_ERROR(Status) ) {
        mDxePlatformRapidStartPolicy.EnableRapidStart           = 0;
        mDxePlatformRapidStartPolicy.EntryOnS3RtcWake           = 0;
        mDxePlatformRapidStartPolicy.S3WakeTimerMin             = 0;
        mDxePlatformRapidStartPolicy.EntryOnS3CritBattWake      = 0;
        mDxePlatformRapidStartPolicy.ActivePageThresholdSupport = 0;
        mDxePlatformRapidStartPolicy.ActivePageThresholdSize    = 0;
        mDxePlatformRapidStartPolicy.HybridHardDisk             = 0;
        mDxePlatformRapidStartPolicy.DisplaySaveRestore         = 0;
        mDxePlatformRapidStartPolicy.DisplayType                = 0;
        mDxePlatformRapidStartPolicy.RaidModeSataPortNumber     = 255;
    } else {
        if (PchSeries == PchLp) {
            if ( SetupData.ULTSataInterfaceMode == 0 ) { //IDE mode
                mDxePlatformRapidStartPolicy.EnableRapidStart = 0;
            } else {
                mDxePlatformRapidStartPolicy.EnableRapidStart  = SetupData.RapidStartEnabled;
            }
        } else {
            if ( SetupData.SataInterfaceMode == 0 ) {    //IDE mode
                mDxePlatformRapidStartPolicy.EnableRapidStart = 0;
            } else {
                mDxePlatformRapidStartPolicy.EnableRapidStart  = SetupData.RapidStartEnabled;
            }
        }
        mDxePlatformRapidStartPolicy.EntryOnS3RtcWake           = SetupData.EntryOnS3RtcWake;
        mDxePlatformRapidStartPolicy.S3WakeTimerMin             = SetupData.S3WakeTimerMin;
        mDxePlatformRapidStartPolicy.EntryOnS3CritBattWake      = SetupData.EntryOnS3CritBattWake;
        mDxePlatformRapidStartPolicy.ActivePageThresholdSupport = SetupData.ActivePageThresholdSupport;
        mDxePlatformRapidStartPolicy.ActivePageThresholdSize    = SetupData.ActivePageThresholdSize;
        mDxePlatformRapidStartPolicy.HybridHardDisk             = SetupData.RapidStartHybridHardDisk;
        mDxePlatformRapidStartPolicy.DisplaySaveRestore         = SetupData.RapidStartDisplaySaveRestore;
        mDxePlatformRapidStartPolicy.DisplayType                = SetupData.RapidStartDisplayType;
        SetCriticalBatteryThreshole(SetupData.CritBattWakeThreshold);

        ///
        /// By default set to 255 as not used
        ///
        mDxePlatformRapidStartPolicy.RaidModeSataPortNumber = 255;
    }
	//AMI_OVERRIDE_FOR_RAPID_START
    //Clear CMOS RapidStartFlag in DXE
    RapidStartSetConfig(0);
    //AMI_OVERRIDE_FOR_RAPID_START
#if LOCK_DISABLE_RAPID_START_IF_NO_SSD
    SsdDetectionRegisterCallBack();
#endif

#ifdef RAPID_START_PARTITION_DETECT_BEFORE_SETUP
    RegisterForBdsAllDriversConnected(ImageHandle);
#endif

#if SYNC_UP_DRIVER_AND_BIOS_VARIABLE
    SyncUpDriverAndBiosVariable();
#endif

    ///
    /// Protocol revision number
    ///
    mDxePlatformRapidStartPolicy.Revision = DXE_RAPID_START_PLATFORM_POLICY_PROTOCOL_REVISION;

    ///
    /// FviSmbiosType is the SMBIOS OEM type (0x80 to 0xFF) defined in SMBIOS Type 14 - Group
    /// Associations structure - item type. FVI structure uses it as SMBIOS OEM type to provide
    /// version information. The default value is type 221.
    ///
    mDxePlatformRapidStartPolicy.FviSmbiosType = 0xDD;


    ///
    /// Install protocol to to allow access to this Policy.
    ///
    Status = gBS->InstallMultipleProtocolInterfaces (
                 &ImageHandle,
                 &gRapidStartPlatformPolicyProtocolGuid,
                 &mDxePlatformRapidStartPolicy,
                 NULL
             );
    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return Status;
    }

    return Status;
}

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
