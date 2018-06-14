/** @file
  Implementation file for AMT functionality

@copyright
  Copyright (c) 2006 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement

**/

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)

#include "EdkIIGlueDxe.h"
#include "AmtLib.h"
#include "MeLib.h"

#include EFI_PROTOCOL_CONSUMER (Heci)
#include EFI_PROTOCOL_CONSUMER (ActiveManagement)
#include EFI_PROTOCOL_CONSUMER (AmtPlatformPolicy)
#include EFI_GUID_DEFINITION (MeBiosExtensionSetup)
#endif

EFI_ACTIVE_MANAGEMENT_PROTOCOL  *mActiveManagement = NULL;
//
// AMT GUID and Variable Name
//
EFI_GUID                        mEfiMeBiosExtensionSetupGuid    = EFI_ME_BIOS_EXTENSION_SETUP_GUID;
CHAR16                          mEfiMeBiosExtensionSetupName[]  = EFI_ME_BIOS_EXTENSION_SETUP_VARIABLE_NAME;

/**
  Check if Asf is enabled in setup options.

  @param[in] None.
  @retval EFI_SUCCESS             mActiveManagement is not NULL
  @retval                         Error Status code returned by
                                  LocateProtocol.
**/
EFI_STATUS
AmtLibInit (
  VOID
  )
{
  EFI_STATUS  Status;

  if (mActiveManagement == NULL) {
    Status = gBS->LocateProtocol (
                    &gEfiActiveManagementProtocolGuid,
                    NULL,
                    (VOID **) &mActiveManagement
                    );
  } else {
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  This will return IDE Redirection Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    IDE-R is enabled.
  @retval False                   IDE-R is disabled.
**/
BOOLEAN
ActiveManagementEnableIdeR (
  VOID
  )
{
  BOOLEAN                 CurrentState;
  UINTN                   VariableSize;
  EFI_STATUS              Status;
  ME_BIOS_EXTENSION_SETUP MeBiosExtensionSetupData;

  CurrentState  = FALSE;
  VariableSize  = 0;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetIderState (mActiveManagement, &CurrentState);
  }

  VariableSize = sizeof (MeBiosExtensionSetupData);
  Status = gRT->GetVariable (
                  mEfiMeBiosExtensionSetupName,
                  &mEfiMeBiosExtensionSetupGuid,
                  NULL,
                  &VariableSize,
                  &MeBiosExtensionSetupData
                  );
  if (!EFI_ERROR (Status)) {
    if ((MeBiosExtensionSetupData.AmtSolIder & IDER_ENABLE) == 0) {
      CurrentState = FALSE;
    }
  }

  return CurrentState;
}

/**
  This will return Enforce Secure Boot over IDER Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    Enforce Secure Boot is enabled.
  @retval False                   Enforce Secure Boot is disabled.
**/
BOOLEAN
ActiveManagementEnforceSecureBoot (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetEnforceSecureBootState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This will return BIOS Pause Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    BIOS Pause is enabled.
  @retval False                   BIOS Pause is disabled.
**/
BOOLEAN
ActiveManagementPauseBoot (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetBiosPauseState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This will return BIOS Setup Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    BIOS Setup is enabled.
  @retval False                   BIOS Setup is disabled.
**/
BOOLEAN
ActiveManagementEnterSetup (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetBiosSetupState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    Console Lock is enabled.
  @retval False                   Console Lock is disabled.
**/
BOOLEAN
ActiveManagementConsoleLocked (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetConsoleLockState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This will return KVM Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    KVM is enabled.
  @retval False                   KVM is disabled.
**/
BOOLEAN
ActiveManagementEnableKvm (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetKvmState (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  This will return Serial-over-Lan Boot Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    Serial-over-Lan is enabled.
  @retval False                   Serial-over-Lan is disabled.
**/
BOOLEAN
ActiveManagementEnableSol (
  VOID
  )
{
  BOOLEAN                 CurrentState;
  UINTN                   VariableSize;
  EFI_STATUS              Status;
  ME_BIOS_EXTENSION_SETUP MeBiosExtensionSetupData;

  CurrentState  = FALSE;
  VariableSize  = 0;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetSolState (mActiveManagement, &CurrentState);
  }

  VariableSize = sizeof (MeBiosExtensionSetupData);
  Status = gRT->GetVariable (
                  mEfiMeBiosExtensionSetupName,
                  &mEfiMeBiosExtensionSetupGuid,
                  NULL,
                  &VariableSize,
                  &MeBiosExtensionSetupData
                  );
  if (!EFI_ERROR (Status)) {
    if ((MeBiosExtensionSetupData.AmtSolIder & SOL_ENABLE) == 0) {
      CurrentState = FALSE;
    }
  }

  return CurrentState;
}

/**
  This will return IDE Redirection boot device index to boot

  @param[in] None.

  @retval IdeBootDevice           Return the boot device number to boot
                                  Bits 0-1: If IDER boot is selected in Perimeter 1 then Bits 1,2 define the drive on the IDER controller to be used as the boot driver.
                                  Bit 1  Bit0
                                   0    0    Primary Master Drive
                                   0    1    Primary Slave Drive
                                   1    0    Secondary Master Drive
                                   1    1    Secondary Slave Drive
                                  Bits 2-7: Reserved set to 0
**/
UINT8
ActiveManagementIderBootDeviceGet (
  VOID
  )
{
  UINT8 IderBootDevice;
  IderBootDevice = 0;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetIderBootDeviceSelectd (mActiveManagement, &IderBootDevice);
  }

  return IderBootDevice;
}

/**
  Stop ASF Watch Dog Timer

  @param[in] None.

  @retval None
**/
VOID
AsfStopWatchDog (
  VOID
  )
{
  EFI_STATUS        Status;
  UINT32            HeciLength;
  ASF_STOP_WDT      AsfStopWdt;
  UINT32            MeStatus;
  UINT32            MeMode;
  EFI_HECI_PROTOCOL *Heci;

  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );

  if (!EFI_ERROR (Status)) {
    Status = Heci->GetMeMode (&MeMode);
    if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
      DEBUG ((EFI_D_ERROR, "MeMode is %x, Unable to Stop ME BIOS Watch Dog Timer", MeMode));

      return ;
    }
    ///
    /// Check ME Status
    ///
    Status = Heci->GetMeStatus (&MeStatus);
    ASSERT_EFI_ERROR (Status);
    ///
    /// Send EOP/WDT message when ME is ready.  Do not care about if ME FW INIT is completed.
    ///
    if (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY) {
      ///
      /// Check if watch dog is enabled in BIOS Setup
      ///
      if (AmtWatchDog ()) {
        ZeroMem ((VOID *) &AsfStopWdt, sizeof (ASF_STOP_WDT));
        AsfStopWdt.Command        = EFI_ASF_MESSAGE_COMMAND_MANAGEMENT_CONTROL;
        AsfStopWdt.ByteCount      = EFI_ASF_STOP_WDT_BYTE_COUNT;
        AsfStopWdt.SubCommand     = ASF_SUB_COMMAND_STOP_WDT;
        AsfStopWdt.VersionNumber  = EFI_ASF_STOP_WDT_VERSION;

        HeciLength                = ASF_STOP_WDT_LENGTH;
        Status = Heci->SendMsg (
                        (UINT32 *) &AsfStopWdt,
                        HeciLength,
                        BIOS_FIXED_HOST_ADDR,
                        HECI_ASF_MESSAGE_ADDR
                        );
        if (EFI_ERROR (Status)) {
          DEBUG ((EFI_D_ERROR, "Unable to Stop ME BIOS Watch Dog Timer"));
        }
      }
    }
  }

  return ;
}

/**
  Start ASF Watch Dog Timer

  @param[in] WatchDogType         Which kind of WatchDog, ASF OS WatchDog Timer setting or ASF BIOS WatchDog Timer setting

  @retval None
**/
VOID
AsfStartWatchDog (
  IN  UINT8                       WatchDogType
  )
{
  EFI_STATUS        Status;
  UINT32            HeciLength;
  ASF_START_WDT     AsfStartWdt;
  EFI_HECI_PROTOCOL *Heci;
  UINT32            MeStatus;
  UINT32            MeMode;
  UINT16            WaitTimer;

  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );

  if (!EFI_ERROR (Status)) {
    Status = Heci->GetMeMode (&MeMode);
    if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
      DEBUG ((EFI_D_ERROR, "MeMode is %x, Unable to Start ME Watch Dog Timer", MeMode));

      return ;
    }
    ///
    /// Check ME Status
    ///
    Status = Heci->GetMeStatus (&MeStatus);
    ASSERT_EFI_ERROR (Status);
    ///
    /// Send EOP/WDT message when ME is ready.  Do not care about if ME FW INIT is completed.
    ///
    if (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY) {
      ///
      /// Check if watch dog is enabled in BIOS Setup
      ///
      if (AmtWatchDog ()) {
        ZeroMem ((VOID *) &AsfStartWdt, sizeof (ASF_START_WDT));
        AsfStartWdt.Command         = EFI_ASF_MESSAGE_COMMAND_MANAGEMENT_CONTROL;
        AsfStartWdt.ByteCount       = EFI_ASF_START_WDT_BYTE_COUNT;
        AsfStartWdt.SubCommand      = ASF_SUB_COMMAND_START_WDT;
        AsfStartWdt.VersionNumber   = EFI_ASF_START_WDT_VERSION_NUMBER;
        AsfStartWdt.EventSensorType = EFI_ASF_START_WDT_EVENT_SENSOR_TYPE;
        AsfStartWdt.EventType       = EFI_ASF_START_WDT_EVENT_TYPE;
        AsfStartWdt.EventOffset     = EFI_ASF_START_WDT_EVENT_OFFSET;
        AsfStartWdt.EventSeverity   = EFI_ASF_START_WDT_EVENT_SEVERITY;
        AsfStartWdt.SensorDevice    = EFI_ASF_START_WDT_SENSOR_DEVICE;
        AsfStartWdt.SensorNumber    = EFI_ASF_START_WDT_SENSOR_NUMBER;
        AsfStartWdt.Entity          = EFI_ASF_START_WDT_ENTITY;
        AsfStartWdt.EntityInstance  = EFI_ASF_START_WDT_ENTITY_INSTANCE;
        AsfStartWdt.EventData[0]    = EFI_ASF_START_WDT_EVENT_DATA_BYTE_0;
        if (WatchDogType == ASF_START_BIOS_WDT) {
          AsfStartWdt.EventSourceType = EFI_ASF_START_WDT_EVENT_SOURCE_TYPE_BIOS;
          AsfStartWdt.EventData[1]    = EFI_ASF_START_WDT_EVENT_DATA_BYTE_1_BIOS_TIMEOUT;
          WaitTimer                   = AmtWatchDogTimerBiosGet ();
        } else {
          AsfStartWdt.EventSourceType = EFI_ASF_START_WDT_EVENT_SOURCE_TYPE_OS;
          AsfStartWdt.EventData[1]    = EFI_ASF_START_WDT_EVENT_DATA_BYTE_1_OS_TIMEOUT;
          WaitTimer                   = AmtWatchDogTimerOsGet ();
        }

        AsfStartWdt.TimeoutLow  = (UINT8) WaitTimer;
        AsfStartWdt.TimeoutHigh = (UINT8) (WaitTimer >> 8);

        HeciLength              = ASF_START_WDT_LENGTH;

        Status = Heci->SendMsg (
                        (UINT32 *) &AsfStartWdt,
                        HeciLength,
                        BIOS_FIXED_HOST_ADDR,
                        HECI_ASF_MESSAGE_ADDR
                        );
        if (EFI_ERROR (Status)) {
          DEBUG ((EFI_D_ERROR, "Unable to Start ME Watch Dog Timer"));
        }
      }
    }
  }

  return ;
}

/**
  This will return progress event Option.
  True if the option is enabled.

  @param[in] None.

  @retval True                    progress event is enabled.
  @retval False                   progress event is disabled.
**/
BOOLEAN
ActiveManagementFwProgress (
  VOID
  )
{
  BOOLEAN CurrentState;

  CurrentState = FALSE;

  if (mActiveManagement != NULL) {
    mActiveManagement->GetProgressMsgRequest (mActiveManagement, &CurrentState);
  }

  return CurrentState;
}

/**
  Sent initialize KVM message

  @param[in] None.

  @retval True                    KVM Initialization is successful
  @retval False                   KVM is not enabled
**/
BOOLEAN
BdsKvmInitialization (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT32                          ResponseCode;

  MeReportError (MSG_KVM_WAIT);
  Status = HeciQueryKvmRequest (QUERY_REQUEST, &ResponseCode);
  if (EFI_ERROR (Status)) {
    MeReportError (MSG_KVM_TIMES_UP);
    Status = HeciQueryKvmRequest (CANCEL_REQUEST, &ResponseCode);
  } else if (ResponseCode == KVM_SESSION_CANCELLED) {
    MeReportError (MSG_KVM_REJECTED);
  } else {
    return TRUE;
  }

  return FALSE;
}
