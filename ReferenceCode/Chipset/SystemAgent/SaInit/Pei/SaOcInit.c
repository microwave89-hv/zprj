/** @file
  OC System Agent Early Post initializations.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
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

///
/// External include files do NOT need to be explicitly specified in real EDKII
/// environment
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "SaOcInit.h"
#endif

EFI_STATUS
SaOcInit (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN SA_PLATFORM_POLICY_PPI      *SaPlatformPolicyPpi
  )
/**
  Initializes Overclocking settings in the processor.

  @param[in] PeiServices - General purpose services available to every PEIM.
  @param[in] OverclockingtConfig      Pointer to Policy protocol instance

  @retval EFI_SUCCESS
**/
{
  EFI_STATUS    Status;
  OC_CAPABILITIES_ITEM OcCaps;
  VOLTAGE_FREQUENCY_ITEM CurrentVfItem;
  VOLTAGE_FREQUENCY_ITEM RequestedVfItem;
  UINT32      LibStatus;
  UINT8       DomainId;
  BOOLEAN     VfUpdateNeeded;
  WDT_PPI     *gWdtPei;

  LibStatus = 0;
  VfUpdateNeeded = FALSE;

  if (SaPlatformPolicyPpi->OcConfig->OcSupport == 0){
    ///
    /// Overclocking is disabled
    ///
    DEBUG ((EFI_D_ERROR, "(OC) Overclocking is disabled. Bypassing SA overclocking flow.\n"));
    return EFI_SUCCESS;
  }

  Status = EFI_SUCCESS;
  ZeroMem(&CurrentVfItem,sizeof(CurrentVfItem));
  ZeroMem(&RequestedVfItem,sizeof(RequestedVfItem));

  //
  // Locate WDT_PPI (ICC WDT PPI)
  //
  Status = PeiServicesLocatePpi (
             &gWdtPpiGuid,
             0,
             NULL,
             (VOID **) &gWdtPei
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// We will loop on the CPU domains to manage the voltage/frequency settings
  ///
  for (DomainId = OC_LIB_DOMAIN_ID_GT; DomainId <= OC_LIB_DOMAIN_ID_IOD; DomainId++) {
    ///
    /// Only GT, Uncore, IOA, and IOD are valid for System Agent
    ///
    if ((DomainId == OC_LIB_DOMAIN_ID_GT) ||(DomainId == OC_LIB_DOMAIN_ID_UNCORE) ||
        (DomainId == OC_LIB_DOMAIN_ID_IOA) || (DomainId == OC_LIB_DOMAIN_ID_IOD)){
      ///
      /// Get OC Capabilities of the domain
      ///
      ZeroMem(&OcCaps,sizeof(OcCaps));
      OcCaps.DomainId = DomainId;
      Status = GetOcCapabilities(&OcCaps,&LibStatus);

      if (LibStatus == OC_LIB_COMPLETION_CODE_SUCCESS){
        ///
        /// If any OC is supported on this domain, then proceed
        ///
        if (OcCaps.RatioOcSupported || OcCaps.VoltageOverridesSupported || OcCaps.VoltageOffsetSupported){
          ///
          /// Need to populate the user requested settings from the platform policy
          /// to determine if OC changes are desired.
          ///
          ZeroMem(&CurrentVfItem,sizeof(CurrentVfItem));
          CurrentVfItem.DomainId = DomainId;

          ///
          /// Get a copy of the current domain VfSettings from the Mailbox Library
          ///
          Status = GetVoltageFrequencyItem(&CurrentVfItem,&LibStatus);
          if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)){
            continue;
          }

          ///
          /// Populate the user requested VfSettings struct
          ///
          ZeroMem(&RequestedVfItem,sizeof(RequestedVfItem));
          RequestedVfItem.DomainId = DomainId;
          if (DomainId == OC_LIB_DOMAIN_ID_GT){
            RequestedVfItem.VfSettings.MaxOcRatio = (UINT8) SaPlatformPolicyPpi->OcConfig->GtMaxOcTurboRatio;

            ///
            /// VoltageTarget has 2 uses and we need to update the target based
            /// on the voltagemode requested
            ///
            RequestedVfItem.VfSettings.VoltageTargetMode = SaPlatformPolicyPpi->OcConfig->GtVoltageMode;
            if (RequestedVfItem.VfSettings.VoltageTargetMode == OC_LIB_OFFSET_ADAPTIVE){
              RequestedVfItem.VfSettings.VoltageTarget = SaPlatformPolicyPpi->OcConfig->GtExtraTurboVoltage;
            }
            else {
              RequestedVfItem.VfSettings.VoltageTarget = SaPlatformPolicyPpi->OcConfig->GtVoltageOverride;
            }
            RequestedVfItem.VfSettings.VoltageOffset = SaPlatformPolicyPpi->OcConfig->GtVoltageOffset;

            VfUpdateNeeded = (BOOLEAN)CompareMem((VOID*)&RequestedVfItem,(VOID*)&CurrentVfItem,sizeof(VOLTAGE_FREQUENCY_ITEM));
          }
          else if ((DomainId == OC_LIB_DOMAIN_ID_UNCORE) || (DomainId == OC_LIB_DOMAIN_ID_IOA) || (DomainId == OC_LIB_DOMAIN_ID_IOD)){
            ///
            /// Uncore,IOA, and IOD domains only supports voltage offset, other settings are ignored
            ///
            switch (DomainId) {
              case OC_LIB_DOMAIN_ID_UNCORE:
                RequestedVfItem.VfSettings.VoltageOffset = SaPlatformPolicyPpi->OcConfig->SaVoltageOffset;
              break;

              case OC_LIB_DOMAIN_ID_IOA:
                RequestedVfItem.VfSettings.VoltageOffset = SaPlatformPolicyPpi->OcConfig->IoaVoltageOffset;
              break;

              case OC_LIB_DOMAIN_ID_IOD:
                RequestedVfItem.VfSettings.VoltageOffset = SaPlatformPolicyPpi->OcConfig->IodVoltageOffset;
              break;
            }

            if (RequestedVfItem.VfSettings.VoltageOffset != CurrentVfItem.VfSettings.VoltageOffset)
              VfUpdateNeeded = TRUE;
          }

          if (VfUpdateNeeded){
            VfUpdateNeeded = FALSE;

            ///
            /// Arm watchdog timer for OC changes
            ///
            Status = gWdtPei->ReloadAndStart (WDT_TIMEOUT_BETWEEN_PEI_DXE);

            ///
            /// Need to update the requested voltage/frequency values
            ///
            Status = SetVoltageFrequencyItem(RequestedVfItem,&LibStatus);
            if ((Status != EFI_SUCCESS) || (LibStatus != OC_LIB_COMPLETION_CODE_SUCCESS)){
              DEBUG ((EFI_D_ERROR, "(OC) Set Voltage Frequency failed. EFI Status = %X, Library Status = %X\n", Status, LibStatus));
            }
          }
        }
        else {
          DEBUG ((EFI_D_INFO, "(OC) No OC support for this Domain = %X\n", DomainId));
        }
      }
      else {
        DEBUG ((EFI_D_ERROR, "(OC) GetOcCapabilities message failed. Library Status = %X, Domain = %X\n", LibStatus, DomainId));
      }
    }
  }

  return Status;
}
