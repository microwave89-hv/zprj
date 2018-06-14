/** @file
  Provide the ResetSystem AP

@copyright
  Copyright (c) 2011 - 2013 Intel Corporation. All rights reserved
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
#include "PlatformReset.h"
#include "MeLib.h"
PCH_RESET_PROTOCOL  *mPchReset;

/**
  Reset the system

  @param[in] ResetType            Warm or cold
  @param[in] ResetStatus          Possible cause of reset
  @param[in] DataSize             Size of ResetData in bytes
  @param[in] ResetData            Optional Unicode string

  @retval Does not return if the reset takes place.
**/
VOID
EFIAPI
PlatformResetSystem (
  IN EFI_RESET_TYPE               ResetType,
  IN EFI_STATUS                   ResetStatus,
  IN UINTN                        DataSize,
  IN CHAR16                       *ResetData OPTIONAL
  )
{
  EFI_STATUS                          Status;
  ME_PLATFORM_GET_RESET_TYPE_PROTOCOL *MePlatformGetResetType;
  PCH_RESET_TYPE                      OverridePchResetType;
  PCH_RESET_TYPE                      PchResetType;
  UINTN                               NumberMePlatformGetResetHandles;
  EFI_HANDLE                          *MePlatformGetResetHandles;
  UINTN                               Index;

  PchResetType = ResetType;
  OverridePchResetType = ResetType;

  if (!EfiAtRuntime ()) {
    Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gMePlatformGetResetTypeGuid,
                    NULL,
                    &NumberMePlatformGetResetHandles,
                    &MePlatformGetResetHandles
                    );
    if (!EFI_ERROR (Status)) {
      for (Index = 0; Index < NumberMePlatformGetResetHandles; Index++) {
        Status = gBS->HandleProtocol (
                        MePlatformGetResetHandles[Index],
                        &gMePlatformGetResetTypeGuid,
                        (VOID **) &MePlatformGetResetType
                        );
        if (!EFI_ERROR (Status)) {
          PchResetType = MePlatformGetResetType->GetResetType (ResetType);
          DEBUG ((EFI_D_INFO, "Returned Pch ResetType is: %x\n", PchResetType));
          if (PchResetType >= MaxRestReq) {
            DEBUG ((EFI_D_ERROR, "Platform Reset failed, invalid parameter\n"));
            ASSERT (FALSE);
          }
          if (OverridePchResetType < PchResetType) {
            DEBUG ((EFI_D_INFO, "Previous Pch ResetType is: %x\n", OverridePchResetType));
            OverridePchResetType = PchResetType;
          }
          DEBUG ((EFI_D_INFO, "Current Pch ResetType is: %x\n", OverridePchResetType));
        }
      }
    }
    PchResetType = OverridePchResetType;
    if ((PchResetType == GlobalReset) || (PchResetType == GlobalResetWithEc)) {
      ///
      /// Let ME do global reset if Me Fw is available
      ///
      Status = HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
      if (!EFI_ERROR (Status)) {
        ///
        /// ME Global Reset should fail after EOP is sent.
        /// Go to use PCH Reset
        ///
        gBS->Stall (1000000);
      }
    }
  }

  mPchReset->Reset (mPchReset, PchResetType);

  ASSERT (FALSE);
}

/**
  Entry point of Platform Reset driver.

  @param[in] ImageHandle          Standard entry point parameter
  @param[in] SystemTable          Standard entry point parameter

  @retval EFI_SUCCESS             Reset RT protocol installed
  @retval All other error conditions encountered result in an ASSERT
**/
EFI_STATUS
InitializePlatformReset (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_HANDLE                      Handle;
  EFI_STATUS                      Status;

  Status = gBS->LocateProtocol (&gPchResetProtocolGuid, NULL, (VOID **) &mPchReset);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Make sure the Reset Architectural Protocol is not already installed in the system
  ///
  ASSERT_PROTOCOL_ALREADY_INSTALLED (NULL, &gEfiResetArchProtocolGuid);

  ///
  /// Hook the runtime service table
  ///
  SystemTable->RuntimeServices->ResetSystem = PlatformResetSystem;

  ///
  /// Now install the Reset RT AP on a new handle
  ///
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiResetArchProtocolGuid,
                  NULL,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Fixup internal data pointers so that the services can be called in virtual mode.

  @param[in] Event                The event registered.
  @param[in] Context              Event context. Not used in this event handler.

  @retval None
**/
EFI_RUNTIMESERVICE
VOID
PchResetVirtualddressChangeEvent (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
{
  gRT->ConvertPointer (EFI_INTERNAL_POINTER, (VOID *) &mPchReset);
}
