/** @file
  HECI driver

@copyright
  Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved
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
#include "HeciDrv.h"
#include "HeciHpet.h"
#include "HeciCore.h"
#include "MeLib.h"
#include "EfiScriptLib.h"
#include "PchPlatformLib.h"

#include EFI_GUID_DEFINITION (MePlatformReadyToBoot)
#include EFI_GUID_DEFINITION (MeBiosExtensionSetup)
#include EFI_PROTOCOL_DEFINITION (MeplatformPolicy)
#include EFI_PROTOCOL_DEFINITION (AmtReadyToBoot)
#include EFI_PROTOCOL_CONSUMER (ExitPmAuth)

extern DXE_ME_POLICY_PROTOCOL *mDxePlatformMePolicy;

#ifdef TCG_SUPPORT_FLAG
#include "Acpi1_0.h"
#include "Acpi2_0.h"
#include "Acpi3_0.h"
#include EFI_PROTOCOL_DEFINITION (TcgService)
#include "TpmPc.h"
#endif // TCG_SUPPORT_FLAG
#endif // EDK_RELEASE_VERSION
#define ONE_SECOND_TIMEOUT  1000000
#define FWU_TIMEOUT         90

//
// Global driver data
//
HECI_INSTANCE         *mHeciContext;
EFI_HANDLE            mHeciDrv;
EFI_EVENT             mExitBootServicesEvent;
EFI_EVENT             mLegacyBootEvent;
DXE_MBP_DATA_PROTOCOL mMbpData;

/**
  This function provides a standard way to verify the HECI cmd and MBAR regs
  in its PCI cfg space are setup properly and that the local mHeciContext
  variable matches this info.

  @param[in] None.

  @retval UINT64                  HeciMar address
**/
UINT64
CheckAndFixHeciForAccess (
  VOID
  )
{
  ///
  /// Read HECI_MBAR in case it has changed
  ///
  ///
  /// Check if Base register is 64 bits wide.
  ///
  if (HeciPciRead32 (R_HECIMBAR) & 0x4) {
    mHeciContext->HeciMBAR = (((UINT64) HeciPciRead32 (R_HECIMBAR + 4) << 32) |
                              (UINT64) HeciPciRead32 (R_HECIMBAR)) & 0xFFFFFFF0;
  } else {
    mHeciContext->HeciMBAR = (UINT64) HeciPciRead32 (R_HECIMBAR) & 0xFFFFFFF0;
  }
  ///
  /// Check if HECI_MBAR is disabled
  ///
  if ((HeciPciRead8 (PCI_COMMAND_OFFSET) & (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)) !=
        (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)
        ) {
    ///
    /// If cmd reg in pci cfg space is not turned on turn it on.
    ///
    HeciPciOr8 (
      PCI_COMMAND_OFFSET,
      EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER
      );
  }

  return mHeciContext->HeciMBAR;
}

/**
  Enable Hpet function.

  @param[in] None.

  @retval None
**/
VOID
EnableHpet (
  VOID
  )
{
  VOLATILE UINT32 *HpetConfigReg;

  HpetConfigReg = NULL;
  ///
  /// Get the High Precision Event Timer base address and enable the memory range
  ///
  HpetConfigReg = (UINT32 *) (UINTN) (PCH_RCRB_BASE + R_PCH_RCRB_HPTC);
  switch (*HpetConfigReg & B_PCH_RCRB_HPTC_AS) {
  case 0:
    mHeciContext->HpetTimer = (VOID *) (UINTN) (HPET_ADDRESS_0);
    break;

  case 1:
    mHeciContext->HpetTimer = (VOID *) (UINTN) (HPET_ADDRESS_1);
    break;

  case 2:
    mHeciContext->HpetTimer = (VOID *) (UINTN) (HPET_ADDRESS_2);
    break;

  case 3:
    mHeciContext->HpetTimer = (VOID *) (UINTN) (HPET_ADDRESS_3);
    break;

  default:
    mHeciContext->HpetTimer = NULL;
    break;
  }
  ///
  /// Read this back to force the write-back.
  ///
  *HpetConfigReg = *HpetConfigReg | B_PCH_RCRB_HPTC_AE;

  ///
  /// Start the timer so it is up and running
  ///
  mHeciContext->HpetTimer[HPET_GEN_CONFIG_LOW]  = HPET_START;
  mHeciContext->HpetTimer[HPET_GEN_CONFIG_LOW]  = HPET_START;

  return ;
}

#ifdef TCG_SUPPORT_FLAG

/**
  Perform measurement for HER register.

  @param[in] HerValue             The value of HECI Extend Register.
  @param[in] Index                HerValue Size.

  @retval EFI_SUCCESS             Measurement performed
**/
EFI_STATUS
MeasureHer (
  IN  UINT32                      *HerValue,
  IN  UINT8                       Index
  )
{
  EFI_STATUS            Status;
  EFI_TCG_PROTOCOL      *TcgProtocol;
  EFI_TCG_PCR_EVENT     TcgEvent;
  UINT32                EventNumber;
  EFI_PHYSICAL_ADDRESS  EventLogLastEntry;

  Status = gBS->LocateProtocol (
                  &gEfiTcgProtocolGuid,
                  NULL,
                  (VOID **) &TcgProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ///
  /// This below data will be stored in Tcg eventlog
  ///
  TcgEvent.Event.PostCode.PostCodeAddress = *HerValue;
  TcgEvent.Event.PostCode.PostCodeLength  = sizeof (UINT32);

  ///
  /// Fill the TcgEvent Header
  ///
  TcgEvent.Header.PCRIndex      = PCRi_CRTM_AND_POST_BIOS;
  TcgEvent.Header.EventType     = EV_S_CRTM_CONTENTS;

  TcgEvent.Header.EventDataSize = (Index * sizeof (UINT32));

  Status = TcgProtocol->HashLogExtendEvent (
                          TcgProtocol,
                          (EFI_PHYSICAL_ADDRESS) HerValue,
                          TcgEvent.Header.EventDataSize,
                          TPM_ALG_SHA,
                          (TCG_PCR_EVENT *) &TcgEvent,
                          &EventNumber,
                          &EventLogLastEntry
                          );
  return Status;
}

/**
  Me Measurement.

  @param[in] None.

  @retval EFI_NOT_READY           Not ready for measurement.
  @retval EFI_SUCCESS             Measurement done
**/
EFI_STATUS
MeMeasurement (
  VOID
  )
{
  EFI_STATUS    Status;
  DATA32_UNION  Data32[7];
  UINT8         HerMax;
  UINT8         HerIndex;
  UINT8         Index;

  Index = 0;
  ///
  /// Measure HER
  ///
  HerMax                = R_ME_HER5;
  Data32[Index].Data32  = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HERS));

  if ((Data32[Index].Data32 & B_ME_EXTEND_REG_VALID) == B_ME_EXTEND_REG_VALID) {
    if ((Data32[Index].Data8[0] & B_ME_EXTEND_REG_ALGORITHM) == V_ME_SHA_256) {
      HerMax = R_ME_HER8;
    }

    for (HerIndex = R_ME_HER1, Index = 0; HerIndex <= HerMax; HerIndex += 4, Index++) {
      Data32[Index].Data32 = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, HerIndex));
    }

    Status = MeasureHer (&Data32->Data32, Index);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "ME Measurement feature failed, Status is %r \n", Status));
    }
  } else {
    Status = EFI_NOT_READY;
  }

  return Status;
}

/**
  Signal a event for last checking.

  @param[in] Event                The event that triggered this notification function
  @param[in] Context    Pointer to the notification functions context

  @retval EFI_SUCCESS             Event excuted and closed.
**/
EFI_STATUS
MeMeasurementEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  MeMeasurement ();

  gBS->CloseEvent (Event);

  return EFI_SUCCESS;
}
#endif

/**
  Show warning message to user.

  @param[in] None.

  @retval EFI_SUCCESS             Warning reported
**/
EFI_STATUS
MeWarningMessage (
  VOID
  )
{
  HECI_FWS_REGISTER MeFirmwareStatus;

  MeFirmwareStatus.ul = HeciPciRead32 (R_FWSTATE);

  ///
  /// Check for ME FPT Bad & FT BUP LD FLR
  ///
  if (MeFirmwareStatus.r.FptBad != 0 || MeFirmwareStatus.r.FtBupLdFlr != 0) {
    MeReportError (MSG_ME_FW_UPDATE_FAILED);
  }

  return EFI_SUCCESS;
}

/**
  Store the current value of DEVEN for S3 resume path

  @param[in] None

  @retval None
**/
VOID
DeviceStatusSave (
  VOID
  )
{
  UINT32  Data;

  ///
  /// Read RCBA register for saving
  ///
  Data = Mmio16 (PCH_RCRB_BASE, R_PCH_RCRB_FD2);

  SCRIPT_MEM_WRITE (
    EFI_ACPI_S3_RESUME_SCRIPT_TABLE,
    EfiBootScriptWidthUint16,
    (UINTN) (PCH_RCRB_BASE + R_PCH_RCRB_FD2),
    1,
    &Data
    );
  Data = Mmio16 (PCH_RCRB_BASE, R_PCH_RCRB_FDSW);

  SCRIPT_MEM_WRITE (
    EFI_ACPI_S3_RESUME_SCRIPT_TABLE,
    EfiBootScriptWidthUint16,
    (UINTN) (PCH_RCRB_BASE + R_PCH_RCRB_FDSW),
    1,
    &Data
    );
}

/**
  ME BWG 1.0 5.3.1.1: IDER Workaround, perform this only when IDER device is present.

  @param[in] None

  @retval None
**/
VOID
PerformIderWorkaround (
  VOID
  )
{
  EFI_STATUS  Status;
  UINT64      BaseAddress;
  UINT64      BaseAddress2;
  UINT64      Index;
  BOOLEAN     WorkaroundFlag;

  WorkaroundFlag = TRUE;

  Status = gDS->AllocateIoSpace (
                  EfiGcdAllocateAnySearchBottomUp,
                  EfiGcdIoTypeIo,
                  4,
                  0x10,
                  &BaseAddress,
                  mHeciDrv,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Program BAR4
  ///
  PciWrite32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x20), (UINT32) BaseAddress);

  ///
  /// Enable IDER IOE
  ///
  PciOr8 (
    PCI_LIB_ADDRESS (ME_BUS,
    ME_DEVICE_NUMBER,
    IDER_FUNCTION_NUMBER,
    PCI_COMMAND_OFFSET),
    EFI_PCI_COMMAND_IO_SPACE
    );

  ///
  /// Perform the workaround if offset 3 bit 0 is not set
  ///
  if ((IoRead8 ((UINTN) BaseAddress + 3) & 0x01) == 00) {
    Status = gDS->AllocateIoSpace (
                    EfiGcdAllocateAnySearchBottomUp,
                    EfiGcdIoTypeIo,
                    4,
                    0x10,
                    &BaseAddress2,
                    mHeciDrv,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
    PciWrite32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x10), (UINT32) BaseAddress2);
    ///
    /// check all ports to make sure all are 0x7f before running the workaround
    ///
    for (Index = 0; Index <= 7; Index++) {
      if (IoRead8 ((UINTN) BaseAddress2 + (UINTN) Index) != 0x7f) {
        WorkaroundFlag = FALSE;
        break;
      }
    }
    ///
    /// Disable IDER IOE and clear BAR0 and BAR4
    ///
    PciAnd8 (
      PCI_LIB_ADDRESS (ME_BUS,
      ME_DEVICE_NUMBER,
      IDER_FUNCTION_NUMBER,
      PCI_COMMAND_OFFSET),
      (UINT8)~EFI_PCI_COMMAND_IO_SPACE
      );
    PciWrite32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x10), 0);
    PciWrite32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x20), 0);

    if (WorkaroundFlag) {
      IderDisable ();
    }

    gDS->FreeIoSpace (BaseAddress2, (UINT64) 0x10);
  } else {
    PciAnd8 (
      PCI_LIB_ADDRESS (ME_BUS,
      ME_DEVICE_NUMBER,
      IDER_FUNCTION_NUMBER,
      PCI_COMMAND_OFFSET),
      (UINT8)~EFI_PCI_COMMAND_IO_SPACE
      );
    PciWrite32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x20), 0);
  }

  gDS->FreeIoSpace (BaseAddress, (UINT64) 0x10);
  return ;
}

/**
  Disable ME Devices when needed

  @param[in] None

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
MeDeviceConfigure (
  VOID
  )
{
  UINT32  MeMode;
  UINT16  VendorID;
  UINT16  DeviceID;

  HeciGetMeMode (&MeMode);
  if (MeMode == ME_MODE_NORMAL) {
    if (mHeciContext->MeFwImageType != INTEL_ME_5MB_FW) {
      ///
      /// We will disable all AMT relevant devices in 1.5M SKU
      ///
      IderDisable ();
      SolDisable ();
      Usbr1Disable ();
      Usbr2Disable ();
    } else {
      ///
      /// ME BWG 1.0 5.3.1.1: IDER Workaround, perform this only when IDER device is present.
      ///
      VendorID = PciRead16 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x00));
      DeviceID = PciRead16 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, IDER_FUNCTION_NUMBER, 0x02));
      if ((VendorID == V_ME_IDER_VENDOR_ID) && IS_PCH_LPT_IDER_DEVICE_ID(DeviceID)
      ) {
        PerformIderWorkaround ();
      }
    }
  }

  return EFI_SUCCESS;
}

/**
  Send ME the BIOS end of Post message.

  @param[in] None.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS except for policy initization failure.
  @exception EFI_UNSUPPORTED      Policy initization failure.
**/
EFI_STATUS
MeEndOfPostEvent (
  VOID
  )
{
  EFI_STATUS                          Status;
  EFI_HECI_PROTOCOL                   *Heci;
  UINT32                              MeStatus;
  UINT8                               EopSendRetries;
  UINT32                              HECI_BASE_ADDRESS;
  HECI_HOST_CONTROL_REGISTER          HeciRegHCsr;
  VOLATILE HECI_HOST_CONTROL_REGISTER *HeciRegHCsrPtr;
  VOLATILE HECI_ME_CONTROL_REGISTER   *HeciRegMeCsrHaPtr;

  //
  // Init ME Policy Library, continue to send EOP message even if can't find Me Platform Policy
  //
  if (mDxePlatformMePolicy == NULL) {
    MePolicyLibInit ();
  }
  
  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (!EFI_ERROR (Status)) {
    ///
    /// Send EOP message when ME is ready. Do not care about if ME FW INIT is completed.
    ///
    Status = Heci->GetMeStatus (&MeStatus);
    ASSERT_EFI_ERROR (Status);

    if (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY) {

      if (MeEndOfPostEnabled ()) {
        DEBUG ((EFI_D_INFO, "Sending EOP...\n"));

        //
        // Initialize pointers to control registers
        //
        HECI_BASE_ADDRESS = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_HECIMBAR)) & 0xFFFFFFF0;
        HeciRegHCsrPtr    = (VOID *) (UINTN) (HECI_BASE_ADDRESS + H_CSR);
        HeciRegMeCsrHaPtr = (VOID *) (UINTN) (HECI_BASE_ADDRESS + ME_CSR_HA);

        for (EopSendRetries = 0; EopSendRetries <= MAX_EOP_SEND_RETRIES; EopSendRetries++) {

          Status = HeciSendEndOfPostMessage (mHeciDrv);
          if (Status == EFI_SUCCESS) {
            break;
          }

          MeReportError (MSG_EOP_ERROR);

          //
          // Set H_RST and H_IG bits to reset HECI
          //
          HeciRegHCsr.ul      = HeciRegHCsrPtr->ul;
          HeciRegHCsr.r.H_RST = 1;
          HeciRegHCsr.r.H_IG  = 1;
          HeciRegHCsrPtr->ul  = HeciRegHCsr.ul;

          //
          // Wait for ME_RDY
          //
          if (WaitForMEReady () != EFI_SUCCESS) {
            Status = EFI_TIMEOUT;
            break;
          }

          //
          // Clear H_RST, set H_RDY & H_IG bits
          //
          HeciRegHCsr.ul      = HeciRegHCsrPtr->ul;
          HeciRegHCsr.r.H_RST = 0;
          HeciRegHCsr.r.H_IG  = 1;
          HeciRegHCsr.r.H_RDY = 1;
          HeciRegHCsrPtr->ul  = HeciRegHCsr.ul;
        }

        if (EFI_ERROR(Status)) {
          //
          // Send HECI_BUS_DISABLE
          //
          for (EopSendRetries = 0; EopSendRetries <= MAX_EOP_SEND_RETRIES; EopSendRetries++) {
            Status = HeciDisableHeciBusMsg();
            if (!EFI_ERROR(Status)) {
              break;
            }
          }

          //
          // Disable HECI function
          //
          HeciDisable();
          Heci2Disable();
        }

      }
    } else if (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_DISABLE_WAIT) {
        MeReportError (MSG_PLAT_DISABLE_WAIT);
    }
    
  }

  return Status;
}

/**
  1. Cf9Gr Lock Config
      - PCH BIOS Spec Rev 0.9 Section 18.4  Additional Power Management Programming
        Step 2
        Set "Power Management Initialization Register (PMIR) Field 1", D31:F0:ACh[31] = 1b
        for production machine according to "RS - PCH Intel Management Engine
        (Intel(r) ME) BIOS Writer's Guide".
  2. Function Disable SUS Well Lock
      - PCH EDS 10.1.76 request that FDSW must be set when Intel Active Management Technology
        is Enabled

  @param[in] None

  @retval Status.
**/
EFI_STATUS
LockConfig (
  VOID
  )
{
  EFI_STATUS        Status;
  EFI_HECI_PROTOCOL *Heci;
  UINT32            MeMode;
  HECI_FWS_REGISTER MeFirmwareStatus;
  UINTN             Address;
  UINT32            Data;

  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (!EFI_ERROR (Status)) {
    ///
    /// Check ME Status
    ///
    Status = Heci->GetMeMode (&MeMode);
    ASSERT_EFI_ERROR (Status);

    MeFirmwareStatus.ul = HeciPciRead32 (R_FWSTATE);

    ///
    /// PCH BIOS Spec Rev 0.9 Section 18.4  Additional Power Management Programming
    /// Step 2
    ///   Set "Power Management Initialization Register (PMIR) Field 1", D31:F0:ACh[31] = 1b
    ///   for production machine according to "RS - PCH Intel Management Engine
    ///  (Intel(r) ME) BIOS Writer's Guide".
    ///
    /// PCH ME BWG section 4.5.1
    /// The IntelR FPT tool /GRST option uses CF9GR bit to trigger global reset.
    /// Based on above reason, the BIOS should not lock down CF9GR bit during Manufacturing and
    /// Re-manufacturing environment.
    ///
    Data = 0;
    if ((((MeMode == ME_MODE_NORMAL) || (MeMode == ME_MODE_TEMP_DISABLED)) && !(MeFirmwareStatus.r.ManufacturingMode))) {
      ///
      /// PCH ME BWG section 4.4.1
      /// BIOS must also ensure that CF9GR is cleared and locked (via bit31 of the same register) before
      /// handing control to the OS in order to prevent the host from issuing global resets and reseting
      /// Intel Management Engine.
      ///
      Data |= B_PCH_LPC_PMIR_CF9LOCK;
    }

    Address = PCI_LIB_ADDRESS (
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_LPC,
                PCI_FUNCTION_NUMBER_PCH_LPC,
                R_PCH_LPC_PMIR
                );
    PciAndThenOr32 (
      Address,
      (UINT32) (~(B_PCH_LPC_PMIR_CF9LOCK | B_PCH_LPC_PMIR_CF9GR)),
      (UINT32) Data
      );

    ///
    /// Function Disable SUS Well lockdown
    ///
    if (MeMode == ME_MODE_NORMAL) {
      if (mHeciContext->MeFwImageType == INTEL_ME_5MB_FW) {
        DEBUG ((EFI_D_ERROR, "Function Disable SUS Well lockdown!\n"));
        FunctionDisableWellLockdown ();
      }
    }
  }

  return Status;
}

/**
  Halt Boot for up to 90 seconds if Bit 11 of FW Status Register (FW_UPD_IN_PROGRESS) is set

  @param[in] None

  @retval None
**/
VOID
CheckFwUpdInProgress (
  VOID
  )
{
  HECI_FWS_REGISTER FwStatus;
  UINT8             StallCount;
  EFI_STATUS        Status;

  StallCount  = 0;
  Status      = mHeciContext->HeciCtlr.GetMeStatus (&FwStatus.ul);
  if (!EFI_ERROR (Status)) {
    if (FwStatus.ul & ME_FW_UPDATES_IN_PROGRESS) {
      MeReportError (MSG_ME_FW_UPDATE_WAIT);
    }

    while ((FwStatus.ul & ME_FW_UPDATES_IN_PROGRESS) && (StallCount < FWU_TIMEOUT)) {
      gBS->Stall (ONE_SECOND_TIMEOUT);
      StallCount  = StallCount + 1;
      Status      = mHeciContext->HeciCtlr.GetMeStatus (&FwStatus.ul);
    }
  }

  return ;
}

/**
  Signal a event for Me ready to boot.

  @param[in] Event                The event that triggered this notification function
  @param[in] Context              Pointer to the notification functions context

  @retval None
**/
VOID
EFIAPI
MeReadyToBootEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       MePlatformReadyToBootEvent;
  EFI_HANDLE                      *Handles;
  UINTN                           Index;
  UINTN                           Count;
  AMT_READY_TO_BOOT_PROTOCOL      *AmtReadyToBoot;
  UINT32                          MeMode;
  UINT32                          MeStatus;
#ifdef TCG_SUPPORT_FLAG
  EFI_EVENT                       LegacyBootEvent;
  EFI_EVENT                       ExitBootServicesEvent;

  Status = MeMeasurement ();
  if (Status == EFI_NOT_READY) {
    ///
    /// Create a Legacy Boot event.
    ///
    Status = EfiCreateEventLegacyBootEx (
              EFI_TPL_CALLBACK,
              MeMeasurementEvent,
              NULL,
              &LegacyBootEvent
              );
    ASSERT_EFI_ERROR (Status);

    ///
    /// Create a ExitBootService event.
    ///
    Status = gBS->CreateEvent (
                    EVENT_SIGNAL_EXIT_BOOT_SERVICES,
                    EFI_TPL_CALLBACK,
                    MeMeasurementEvent,
                    NULL,
                    &ExitBootServicesEvent
                    );
    ASSERT_EFI_ERROR (Status);
  }

#endif //TCG_SUPPORT_FLAG
  ///
  /// PCH BIOS Spec Rev 0.8.0, Section 22.8.3.1 ASPM on DMI and the PCI Express Root Ports
  /// Step g 
  /// Issue "WRITE_ICC_REGISTER" MEI message to program ICC register offset 0x4 with 0x000999999
  /// This is always needed for PCIE with hotplug on and off and PCIE RP enabled and disabled.
  ///
  if(GetPchSeries() == PchLp) {
    Status = HeciWriteIccRegDword(0x0004, 0x00999999, ICC_RESPONSE_MODE_SKIP);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Heci writes to TMCSRCCLK failed. Status = %X\n", Status));
    }
  }

  ///
  /// We will trigger all events in order
  ///
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gAmtReadyToBootProtocolGuid,
                  NULL,
                  &Count,
                  &Handles
                  );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < Count; Index++) {
      Status = gBS->HandleProtocol (Handles[Index], &gAmtReadyToBootProtocolGuid, (VOID **) &AmtReadyToBoot);
      ASSERT_EFI_ERROR (Status);
      AmtReadyToBoot->Signal ();
    }
  }

  Status = gBS->CreateEventEx (
                  EFI_EVENT_NOTIFY_SIGNAL,
                  EFI_TPL_CALLBACK,
                  MeEmptyEvent,
                  NULL,
                  &gMePlatformReadyToBootGuid,
                  &MePlatformReadyToBootEvent
                  );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    gBS->SignalEvent (MePlatformReadyToBootEvent);
    gBS->CloseEvent (MePlatformReadyToBootEvent);
  }

  HeciGetMeMode (&MeMode);
  HeciGetMeStatus (&MeStatus);
  if ((MeMode == ME_MODE_NORMAL) &&
      ((ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) || (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY))
      ) {

    CheckFwUpdInProgress ();

    Status = MeWarningMessage ();
    ASSERT_EFI_ERROR (Status);

    Status = MeEndOfPostEvent ();
    ASSERT_EFI_ERROR (Status);
  }

  ///
  /// Set EndOfPostDone regardless whether the EOP msg was sent
  ///
  if (MeEndOfPostEnabled ()) {
    mDxePlatformMePolicy->MeConfig.EndOfPostDone = 1;
  }

  ///
  /// PMIR Configuration & FDSW Lockdown
  ///
  Status = LockConfig ();
  ASSERT_EFI_ERROR (Status);

  ///
  /// Disable Heci2 if policy dictates
  ///
  Heci2Disable ();

  ///
  /// If ME Mode is running in ME Temp Disable state, disable Heci1, HECI2, Ider and Sol
  ///
  HeciGetMeMode (&MeMode);
  if (MeMode == ME_MODE_TEMP_DISABLED) {
    DisableAllMEDevices ();
  }

  gBS->CloseEvent (Event);

  return;
}

/**
  Signal a event to save Me relevant registers and this event must be run before ExitPmAuth.

  @param[in] Event                The event that triggered this notification function
  @param[in] ParentImageHandle    Pointer to the notification functions context

  @retval None
**/
VOID
EFIAPI
MeScriptSaveEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *ParentImageHandle
  )
{
  EFI_STATUS              Status;
  VOID                    *ProtocolPointer;
  EFI_HECI_PROTOCOL       *Heci;
  UINT32                  MeMode;
  HECI_FWS_REGISTER       MeFirmwareStatus;
  UINTN                   Address;
  UINT32                  Data;
  UINT32                  MebxSetupVariableAttributes;
  UINTN                   MebxSetupVariableDataSize;
  ME_BIOS_EXTENSION_SETUP MeBiosExtensionSetup;
  const UINT8             Str5MBFw[sizeof (MEFW_5M_STRING)]     = MEFW_5M_STRING;
  EFI_MEBX_PROTOCOL       *MebxProtocol;

  INITIALIZE_SCRIPT (ParentImageHandle, gST);

  ///
  /// Check whether this is real ExitPmAuth notification, or just a SignalEvent
  ///
  Status = gBS->LocateProtocol (&gExitPmAuthProtocolGuid, NULL, &ProtocolPointer);
  if (EFI_ERROR (Status)) {
    return;
  }
  ///
  /// PMIR Configuration Save
  ///
  Status = gBS->LocateProtocol (
                  &gEfiHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return;
  }
  ///
  /// Check ME Status
  ///
  Status = Heci->GetMeMode (&MeMode);
  ASSERT_EFI_ERROR (Status);

  MeFirmwareStatus.ul = HeciPciRead32 (R_FWSTATE);

  ///
  /// Init ME Policy Library
  ///
  Status = MePolicyLibInit ();
  if (EFI_ERROR (Status)) {
    return;
  }

#ifdef EFI_DEBUG
  //
  // Dump the ME platform policy
  //
  DxeMePolicyDebugDump ();
#endif

  ///
  /// Report ME components version information to FVI
  ///
  InitFviDataHubCbContext (
    mDxePlatformMePolicy->MeMiscConfig.FviSmbiosType,
    (UINT8) mMeFviElements,
    &mMeFviVersionData
    );

  mMeFviElementsData[EnumMeFw].Element.Version.MajorVersion = (UINT8) mMbpData.MeBiosPayload.FwVersionName.MajorVersion;
  mMeFviElementsData[EnumMeFw].Element.Version.MinorVersion = (UINT8) mMbpData.MeBiosPayload.FwVersionName.MinorVersion;
  mMeFviElementsData[EnumMeFw].Element.Version.Revision = (UINT8) mMbpData.MeBiosPayload.FwVersionName.HotfixVersion;
  mMeFviElementsData[EnumMeFw].Element.Version.BuildNum = (UINT16) mMbpData.MeBiosPayload.FwVersionName.BuildVersion;
  if (mMbpData.MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType == INTEL_ME_5MB_FW) {
    CopyMem (mMeFviElementsData[EnumMeFw].Element.VerString, Str5MBFw, sizeof (MEFW_5M_STRING));
  }
  Status = gBS->LocateProtocol (&gEfiMebxProtocolGuid, NULL, (VOID **) &MebxProtocol);
  if (!EFI_ERROR (Status)) {
    mMeFviElementsData[EnumMebx].Element.Version.MajorVersion = (UINT8) MebxProtocol->MebxVersion.Major;
    mMeFviElementsData[EnumMebx].Element.Version.MinorVersion = (UINT8) MebxProtocol->MebxVersion.Minor;
    mMeFviElementsData[EnumMebx].Element.Version.Revision = (UINT8) MebxProtocol->MebxVersion.Hotfix;
    mMeFviElementsData[EnumMebx].Element.Version.BuildNum = (UINT16) MebxProtocol->MebxVersion.Build;
  }

  CreateRcFviDatahub (&mMeFviVersionData);

  ///
  /// PCH BIOS Spec Rev 0.9 Section 18.4  Additional Power Management Programming
  /// Step 2
  ///   Set "Power Management Initialization Register (PMIR) Field 1", D31:F0:ACh[31] = 1b
  ///   for production machine according to "RS - PCH Intel Management Engine
  ///  (Intel(r) ME) BIOS Writer's Guide".
  ///
  /// PCH ME BWG section 4.5.1
  /// The IntelR FPT tool /GRST option uses CF9GR bit to trigger global reset.
  /// Based on above reason, the BIOS should not lock down CF9GR bit during Manufacturing and
  /// Re-manufacturing environment.
  ///
  Address = PCI_LIB_ADDRESS (
              DEFAULT_PCI_BUS_NUMBER_PCH,
              PCI_DEVICE_NUMBER_PCH_LPC,
              PCI_FUNCTION_NUMBER_PCH_LPC,
              R_PCH_LPC_PMIR
              );
  Data = PciRead32 (Address);
  Data &= (UINT32) (~(B_PCH_LPC_PMIR_CF9LOCK | B_PCH_LPC_PMIR_CF9GR));

  if ((((MeMode == ME_MODE_NORMAL) || (MeMode == ME_MODE_TEMP_DISABLED)) && !(MeFirmwareStatus.r.ManufacturingMode))) {
    ///
    /// PCH ME BWG section 4.4.1
    /// BIOS must also ensure that CF9GR is cleared and locked (via bit31 of the same register) before
    /// handing control to the OS in order to prevent the host from issuing global resets and reseting
    /// Intel Management Engine.
    ///
    Data |= (UINT32) (B_PCH_LPC_PMIR_CF9LOCK);
  }
#ifdef SUS_WELL_RESTORE
  ///
  /// PMIR is a resume well register and has no script save for it.
  /// System may go through S3 resume path from G3 if RapidStart is enabled,
  /// that means all resume well registers will be reset to defaults.
  /// Save boot script for PMIR register if RapidStart is enabled.
  ///
  SCRIPT_MEM_WRITE (
    EFI_ACPI_S3_RESUME_SCRIPT_TABLE,
    EfiBootScriptWidthUint32,
    (UINTN) MmPciAddress (0x0,
            DEFAULT_PCI_BUS_NUMBER_PCH,
            PCI_DEVICE_NUMBER_PCH_LPC,
            PCI_FUNCTION_NUMBER_PCH_LPC,
            R_PCH_LPC_PMIR),
    1,
    &Data
    );
#endif
  ///
  ///
  /// Read RCBA register for saving
  ///
  Data = Mmio16 (PCH_RCRB_BASE, R_PCH_RCRB_FD2);
  ///
  /// Disable Heci2 if policy dictates
  ///
  Data |= (BIT0 << HECI2);

  ///
  /// If ME Mode is running in ME Temp Disable state, disable Heci1, HECI2, Ider and Sol
  ///
  if ((MeMode == ME_MODE_TEMP_DISABLED) || (MeMode == ME_MODE_SECOVER)) {
    Data |= ((BIT0 << HECI1) + (BIT0 << HECI2) + (BIT0 << IDER) + (BIT0 << SOL));
  }

  if (MeMode == ME_MODE_NORMAL) {
    if (mHeciContext->MeFwImageType == INTEL_ME_1_5MB_FW) {
      ///
      /// We will disable HECI2, Ider and Sol in 1.5M SKU
      ///
      Data |= ((BIT0 << HECI2) + (BIT0 << IDER) + (BIT0 << SOL));
    } else if (mHeciContext->MeFwImageType == INTEL_ME_5MB_FW) {
      MebxSetupVariableAttributes = EFI_VARIABLE_BOOTSERVICE_ACCESS |
        EFI_VARIABLE_RUNTIME_ACCESS |
        EFI_VARIABLE_NON_VOLATILE;
      MebxSetupVariableDataSize = sizeof (ME_BIOS_EXTENSION_SETUP);

      Status = gST->RuntimeServices->GetVariable (
                                      gEfiMeBiosExtensionSetupName,
                                      &gEfiMeBiosExtensionSetupGuid,
                                      &MebxSetupVariableAttributes,
                                      &MebxSetupVariableDataSize,
                                      &MeBiosExtensionSetup
                                      );
      if (!EFI_ERROR (Status)) {
        if ((MeBiosExtensionSetup.AmtSolIder & SOL_ENABLE) == 0) {
          Data |= (BIT0 << SOL);
        }

        if ((MeBiosExtensionSetup.AmtSolIder & IDER_ENABLE) == 0) {
          Data |= (BIT0 << IDER);
        }
      }
    }
  }

  SCRIPT_MEM_WRITE (
    EFI_ACPI_S3_RESUME_SCRIPT_TABLE,
    EfiBootScriptWidthUint16,
    (UINTN) (PCH_RCRB_BASE + R_PCH_RCRB_FD2),
    1,
    &Data
    );
  ///
  /// Function Disable SUS Well lockdown
  ///
  Data = Mmio16 (PCH_RCRB_BASE, R_PCH_RCRB_FDSW);

  if (MeMode == ME_MODE_NORMAL) {
    if (mHeciContext->MeFwImageType == INTEL_ME_5MB_FW) {
      Data |= B_PCH_RCRB_FDSW_FDSWL;
    }
  }

  SCRIPT_MEM_WRITE (
    EFI_ACPI_S3_RESUME_SCRIPT_TABLE,
    EfiBootScriptWidthUint16,
    (UINTN) (PCH_RCRB_BASE + R_PCH_RCRB_FDSW),
    1,
    &Data
    );

  gBS->CloseEvent (Event);
  return;
}

/**
  Send Get Firmware SKU Request to ME

  @param[out] FwCapsSku     Return FwCapsSku mask for Get Firmware Capability SKU

  @exception EFI_UNSUPPORTED        Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too smallfor the Acknowledge
**/
EFI_STATUS
MbpGetFwCapsSkuThroughHeci (
  OUT MEFWCAPS_SKU             *FwCapsSku
  )
{
  EFI_STATUS                      Status;
  GEN_GET_FW_CAPS_SKU_BUFFER      MsgGenGetFwCapsSku;
  UINT32                          Length;
  UINT32                          RespLength;

  MsgGenGetFwCapsSku.Request.MKHIHeader.Data               = 0;
  MsgGenGetFwCapsSku.Request.MKHIHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  MsgGenGetFwCapsSku.Request.MKHIHeader.Fields.Command     = FWCAPS_GET_RULE_CMD;
  MsgGenGetFwCapsSku.Request.MKHIHeader.Fields.IsResponse  = 0;
  MsgGenGetFwCapsSku.Request.Data.RuleId                   = 0;
  Length = sizeof (GEN_GET_FW_CAPSKU);
  RespLength = sizeof(GEN_GET_FW_CAPS_SKU_ACK);

  ///
  /// Send Get FW SKU Request to ME
  ///
  Status = HeciSendwACK (
                  (UINT32 *) &MsgGenGetFwCapsSku,
                  Length,
                  &RespLength,
                  BIOS_FIXED_HOST_ADDR,
                  HECI_CORE_MESSAGE_ADDR
                  );

  if (!EFI_ERROR(Status) &&
      ((MsgGenGetFwCapsSku.Response.MKHIHeader.Fields.Command) == FWCAPS_GET_RULE_CMD) &&
      ((MsgGenGetFwCapsSku.Response.MKHIHeader.Fields.IsResponse) == 1) &&
      (MsgGenGetFwCapsSku.Response.MKHIHeader.Fields.Result == 0)
      ) {
    *FwCapsSku = MsgGenGetFwCapsSku.Response.Data.FWCapSku;
    return EFI_SUCCESS;
  }

  return Status;
}

/**
  Send Get Platform Type Request to ME

  @param[in] RuleData             PlatformBrand,
                                  IntelMeFwImageType,
                                  SuperSku,
                                  PlatformTargetMarketType,
                                  PlatformTargetUsageType

  @exception EFI_UNSUPPORTED        Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too smallfor the Acknowledge
**/
EFI_STATUS
MbpGetPlatformTypeThroughHeci (
  OUT PLATFORM_TYPE_RULE_DATA     *RuleData
  )
{
  EFI_STATUS                      Status;
  GEN_GET_PLATFORM_TYPE_BUFFER    MsgGenGetPlatformType;
  UINT32                          Length;
  UINT32                          RespLength;

  MsgGenGetPlatformType.Request.MKHIHeader.Data               = 0;
  MsgGenGetPlatformType.Request.MKHIHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  MsgGenGetPlatformType.Request.MKHIHeader.Fields.Command     = FWCAPS_GET_RULE_CMD;
  MsgGenGetPlatformType.Request.MKHIHeader.Fields.IsResponse  = 0;
  MsgGenGetPlatformType.Request.Data.RuleId                   = 0x1D;
  Length = sizeof (GEN_GET_PLATFORM_TYPE);
  RespLength = sizeof(GEN_GET_PLATFORM_TYPE_ACK);

  ///
  /// Send Get FW SKU Request to ME
  ///
  Status = HeciSendwACK (
                  (UINT32 *) &MsgGenGetPlatformType,
                  Length,
                  &RespLength,
                  BIOS_FIXED_HOST_ADDR,
                  HECI_CORE_MESSAGE_ADDR
                  );

  if (!EFI_ERROR(Status) &&
      ((MsgGenGetPlatformType.Response.MKHIHeader.Fields.Command) == FWCAPS_GET_RULE_CMD) &&
      ((MsgGenGetPlatformType.Response.MKHIHeader.Fields.IsResponse) == 1) &&
      (MsgGenGetPlatformType.Response.MKHIHeader.Fields.Result == 0)
      ) {
    *RuleData = MsgGenGetPlatformType.Response.Data.RuleData;
    return EFI_SUCCESS;
  }

  return Status;
}

/**
  Send Get Firmware Features State Request to ME

  @param[out] FwFeaturesState     Return FwFeaturesState mask for Get Firmware Features State

  @exception EFI_UNSUPPORTED        Current ME mode doesn't support this function
  @retval EFI_SUCCESS               Command succeeded
  @retval EFI_DEVICE_ERROR          HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT               HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL      Message Buffer is too smallfor the Acknowledge
**/
EFI_STATUS
MbpGetFwFeaturesStateThroughHeci (
  OUT MEFWCAPS_SKU             *FwFeaturesState
  )
{
  EFI_STATUS                      Status;
  GEN_GET_FW_CAPS_SKU_BUFFER      MsgGenGetFwCapsSku;
  UINT32                          Length;
  UINT32                          RespLength;

  MsgGenGetFwCapsSku.Request.MKHIHeader.Data               = 0;
  MsgGenGetFwCapsSku.Request.MKHIHeader.Fields.GroupId     = MKHI_FWCAPS_GROUP_ID;
  MsgGenGetFwCapsSku.Request.MKHIHeader.Fields.Command     = FWCAPS_GET_RULE_CMD;
  MsgGenGetFwCapsSku.Request.MKHIHeader.Fields.IsResponse  = 0;
  MsgGenGetFwCapsSku.Request.Data.RuleId                   = 0x20;
  Length = sizeof (GEN_GET_FW_CAPSKU);
  RespLength = sizeof(GEN_GET_FW_CAPS_SKU_ACK);

  ///
  /// Send Get FW SKU Request to ME
  ///
  Status = HeciSendwACK (
                  (UINT32 *) &MsgGenGetFwCapsSku,
                  Length,
                  &RespLength,
                  BIOS_FIXED_HOST_ADDR,
                  HECI_CORE_MESSAGE_ADDR
                  );

  if (!EFI_ERROR(Status) &&
      ((MsgGenGetFwCapsSku.Response.MKHIHeader.Fields.Command) == FWCAPS_GET_RULE_CMD) &&
      ((MsgGenGetFwCapsSku.Response.MKHIHeader.Fields.IsResponse) == 1) &&
      (MsgGenGetFwCapsSku.Response.MKHIHeader.Fields.Result == 0)
      ) {
    *FwFeaturesState = MsgGenGetFwCapsSku.Response.Data.FWCapSku;
    return EFI_SUCCESS;
  }

  return Status;
}

/**
  Install MbpData protocol.

  @param[in] None

  @retval None
**/
VOID
InstallMbpDataProtocol (
  VOID
  )
{
  EFI_STATUS                          Status;
  UINT32                              MeMode;
  UINT32                              MeStatus;
  MEFWCAPS_SKU                        FwCapsSku;
  PLATFORM_TYPE_RULE_DATA             RuleData;

  ZeroMem (&mMbpData, sizeof (DXE_MBP_DATA_PROTOCOL));

  HeciGetMeMode (&MeMode);

  mMbpData.Revision = DXE_MBP_DATA_PROTOCOL_REVISION_2;

  PERF_START_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8010);
  Status = PrepareMeBiosPayload (&mMbpData.MeBiosPayload);
  PERF_END_EX (NULL, EVENT_REC_TOK, NULL, AsmReadTsc (), 0x8011);

  if (!EFI_ERROR (Status)) {
    HeciGetMeStatus (&MeStatus);
    HeciGetMeMode (&MeMode);

    if (mMbpData.MeBiosPayload.FwCapsSku.Available == 0) {
      if ((MeMode == ME_MODE_NORMAL) &&
          (
            (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) ||
          (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY)
        )
          ) {
        Status = MbpGetFwCapsSkuThroughHeci (&FwCapsSku);
        if (!EFI_ERROR (Status)) {
          mMbpData.MeBiosPayload.FwCapsSku.FwCapabilities.Data = FwCapsSku.Data;
          mMbpData.MeBiosPayload.FwCapsSku.Available = TRUE;
        }
      }
    }

    if (mMbpData.MeBiosPayload.FwPlatType.Available == 0) {
      if ((MeMode == ME_MODE_NORMAL) &&
          (
            (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) ||
          (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY)
        )
          ) {
        Status = MbpGetPlatformTypeThroughHeci (&RuleData);
        if (!EFI_ERROR (Status)) {
          mMbpData.MeBiosPayload.FwPlatType.RuleData.Data = RuleData.Data;
          mMbpData.MeBiosPayload.FwPlatType.Available = TRUE;
        }
      }
    }

    if (mMbpData.MeBiosPayload.FwVersionName.MajorVersion == 10) {
      //
      // For ME 10 get the FW features state mask
      //
      if (mMbpData.MeBiosPayload.FwFeaturesState.Available == 0) {
        if ((MeMode == ME_MODE_NORMAL) &&
            (
              (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) ||
            (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY)
          )
            ) {
          Status = MbpGetFwFeaturesStateThroughHeci ((MEFWCAPS_SKU*)&RuleData.Data);
          if (!EFI_ERROR (Status)) {
            mMbpData.MeBiosPayload.FwFeaturesState.FwFeatures.Data = RuleData.Data;
            mMbpData.MeBiosPayload.FwFeaturesState.Available = TRUE;
          }
        }
      }
    }

#ifdef EFI_DEBUG
    //
    // Dump the Mbp data
    //
    DxeMbpDebugDump (&mMbpData);
#endif

    ///
    /// Install the MBP protocol
    ///
    mMbpData.Handle = NULL;
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &mMbpData.Handle,
                    &gMeBiosPayloadDataProtocolGuid,
                    &mMbpData,
                    NULL
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "MBP data protocol install failed, Status is %r \n", Status));
    }
  }
}

/**
  HECI driver entry point used to initialize support for the HECI device.

  @param[in] ImageHandle          Standard entry point parameter.
  @param[in] SystemTable          Standard entry point parameter.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
InitializeHECI (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       ReadyToBootEvent;
  VOID                            *Registration;
  BOOLEAN                         HeciInitializeError;
  UINT32                          MeStatus;
  UINT32                          MeMode;
  MEFWCAPS_SKU                    FwCapsSku;
  PLATFORM_TYPE_RULE_DATA         RuleData;
  DXE_MBP_DATA_PROTOCOL           *MbpData;

  INITIALIZE_SCRIPT (ImageHandle, SystemTable);

  mHeciDrv            = ImageHandle;
  HeciInitializeError = FALSE;
  mHeciContext        = AllocateZeroPool (sizeof (HECI_INSTANCE));
  ///
  /// Initialize HECI protocol pointers
  ///
  if (mHeciContext != NULL) {
    mHeciContext->HeciCtlr.ResetHeci    = ResetHeciInterface;
    mHeciContext->HeciCtlr.SendwACK     = HeciSendwACK;
    mHeciContext->HeciCtlr.ReadMsg      = HeciReceive;
    mHeciContext->HeciCtlr.SendMsg      = HeciSend;
    mHeciContext->HeciCtlr.InitHeci     = HeciInitialize;
    mHeciContext->HeciCtlr.ReInitHeci   = HeciReInitialize;
    mHeciContext->HeciCtlr.MeResetWait  = MeResetWait;
    mHeciContext->HeciCtlr.GetMeStatus  = HeciGetMeStatus;
    mHeciContext->HeciCtlr.GetMeMode    = HeciGetMeMode;
  }
  ///
  /// Initialize the HECI device
  ///
  Status = InitializeHeciPrivate ();
  if ((EFI_ERROR (Status)) || (mHeciContext == NULL)) {
    HeciInitializeError = TRUE;
  }
  ///
  /// Install the MBP information
  ///
  InstallMbpDataProtocol ();

  if (HeciInitializeError) {
    ///
    /// Don't install on ERR
    ///
    if (Status != EFI_NOT_READY) {
      DEBUG ((EFI_D_ERROR, "HECI not initialized - Removing devices from PCI space!\n"));
      DisableAllMEDevices ();
      ///
      /// Store the current value of DEVEN for S3 resume path
      ///
    }
    DeviceStatusSave ();
    return EFI_SUCCESS;
  }
  ///
  /// Install the HECI interface
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mHeciContext->Handle,
                  &gEfiHeciProtocolGuid,
                  &mHeciContext->HeciCtlr,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  HeciGetMeStatus (&MeStatus);
  HeciGetMeMode (&MeMode);

  Status = gBS->LocateProtocol (
                  &gMeBiosPayloadDataProtocolGuid,
                  NULL,
                  (VOID **) &MbpData
                  );
  if (!EFI_ERROR (Status)) {
    if (MbpData->MeBiosPayload.FwCapsSku.Available == 0) {
      if ((MeMode == ME_MODE_NORMAL) &&
          (
            (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) ||
          (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY)
        )
          ) {
        Status = HeciGetFwCapsSku (&FwCapsSku);
        if (!EFI_ERROR (Status)) {
          MbpData->MeBiosPayload.FwCapsSku.FwCapabilities.Data = FwCapsSku.Data;
        }
      }
    }

    if (MbpData->MeBiosPayload.FwPlatType.Available == 0) {
      if ((MeMode == ME_MODE_NORMAL) &&
          (
            (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_IN_RECOVERY_MODE) ||
          (ME_STATUS_ME_STATE_ONLY (MeStatus) == ME_READY)
        )
          ) {
        Status = HeciGetPlatformType (&RuleData);
        if (!EFI_ERROR (Status)) {
          MbpData->MeBiosPayload.FwPlatType.RuleData.Data = RuleData.Data;
        }
      }
    }
    ///
    /// Dxe Mbp data is gone after ExitPmAuth, so we keep MeFwImageType for the inspection after ExitPmAuth
    ///
    mHeciContext->MeFwImageType = (UINT8) MbpData->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType;
  }

  
  ///
  /// Hide Me relevant Devices
  ///
  Status = MeDeviceConfigure ();
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize the Me Reference Code Information
  ///
  mHeciContext->MeRcInfo.Revision   = ME_RC_INFO_PROTOCOL_REVISION_1;
  mHeciContext->MeRcInfo.RCVersion  = ME_RC_VERSION;

  ///
  /// Install the Me Reference Code Information
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mHeciContext->Handle,
                  &gEfiMeRcInfoProtocolGuid,
                  &mHeciContext->MeRcInfo,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  
  ///
  /// Create an ExitPmAuth protocol call back event.
  ///
  EfiCreateProtocolNotifyEvent (
    &gExitPmAuthProtocolGuid,
    EFI_TPL_CALLBACK,
    MeScriptSaveEvent,
    NULL,
    &Registration
    );

  ///
  /// Create a Ready to Boot event.
  ///
  Status = EfiCreateEventReadyToBootEx (
            EFI_TPL_CALLBACK,
            MeReadyToBootEvent,
            (VOID *) &ImageHandle,
            &ReadyToBootEvent
            );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
