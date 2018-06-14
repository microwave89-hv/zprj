/** @file
  PCH S3 Support Protocol SMM Driver Entry

@copyright
  Copyright (c) 2015 Intel Corporation. All rights reserved
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
#include "S3SupportSmm.h"


//
// Global Variables
//
UINT16                                    mS3SupportIoTrapAddress;
EFI_SMM_SYSTEM_TABLE                      *mSmst;
EFI_SMM_BASE_PROTOCOL                     *mSmmBase;
EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL         *mPchIoTrap;
EFI_HANDLE                                mImageHandle;
EFI_PCH_S3_SUPPORT_SMM_PROTOCOL           *mPchS3SupportSmmProtocol;
EFI_HANDLE                                mPchIoTrapHandle;

/**
  An IO Trap SMI callback to copy the DispatchArray data to SMRAM and unregister the IO Trap.

  @param[in] DispatchHandle  - The handle of this callback, obtained when registering
  @param[in] DispatchContext - Pointer to the EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT

  @retval None
**/
VOID
S3SupportSmmExitPmAuthCallback (
  IN  EFI_HANDLE                                  DispatchHandle,
  IN  EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT   *CallbackContext
  )
{
  EFI_PHYSICAL_ADDRESS                      Address;
  EFI_STATUS                                Status;

  DEBUG ((EFI_D_INFO, "S3SupportSmmExitPmAuthCallback() Start\n"));

  ///
  /// Allocate SMRAM memory for the PCH S3 Custom Dispatch Script
  ///
  Status = mSmst->SmmAllocatePages (
    AllocateAnyPages,
    EfiRuntimeServicesData,
    mPchS3SupportSmmProtocol->ProtocolSize,
    &Address
    );
  DEBUG ((EFI_D_INFO, "SMRAM Memory Allocation Failed - S3SupportSmmExitPmAuthCallback()\n"));
  ASSERT_EFI_ERROR (Status);
  
  ///
  /// Copy S3 Support Data from Boot Services memory to SMRAM
  ///
  CopyMem ((VOID *)Address,  mPchS3SupportSmmProtocol->DispatchArray, mPchS3SupportSmmProtocol->ProtocolSize * EFI_PAGE_SIZE);

  ///
  /// Unregister the IO Trap as the copy to SMRAM is only allowed once
  ///
  Status = mPchIoTrap->UnRegister (
                      mPchIoTrap,
                      &mPchIoTrapHandle
                      );
  DEBUG ((EFI_D_INFO, "IO Trap Unregister Failed - S3SupportSmmExitPmAuthCallback()\n"));
  ASSERT_EFI_ERROR (Status);

  ///
  /// Clear the NextDispatchItem in the Boot Services Memory so as to cause an error
  /// if an entity tries to use the Protocol to add more data after the copy to SMRAM.
  ///
  mPchS3SupportSmmProtocol->DispatchArray->NextDispatchItem = NULL;

  DEBUG ((EFI_D_INFO, "S3SupportSmmExitPmAuthCallback() End\n"));

  return;
}

/**
  Initializes the PCH SMM handler for PCH save and restore

  @param[in] ImageHandle - Handle for the image of this driver
  @param[in] SystemTable - Pointer to the EFI System Table

  @retval EFI_SUCCESS    - PCH SMM handler was installed
**/
EFI_STATUS
S3SupportSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                                Status;
  EFI_SMM_IO_TRAP_DISPATCH_REGISTER_CONTEXT PchIoTrapContext;
  
  DEBUG ((EFI_D_INFO, "S3SupportSmmEntryPoint() Start\n"));

  mImageHandle = NULL;

  ///
  /// Locate SmmBase protocol
  ///
  Status = gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, (VOID **)&mSmmBase);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize our module variables
  ///
  Status = mSmmBase->GetSmstLocation (mSmmBase, &mSmst);
  ASSERT_EFI_ERROR (Status);
  
  ///
  /// Locate the PCH S3 SMM Support protocol
  ///
  Status = gBS->LocateProtocol (&gEfiPchS3SupportSmmProtocolGuid, NULL, (void **)&mPchS3SupportSmmProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Locate the PCH Trap dispatch protocol
  ///
  Status = gBS->LocateProtocol (&gEfiSmmIoTrapDispatchProtocolGuid, NULL, &mPchIoTrap);
  ASSERT_EFI_ERROR (Status);

  PchIoTrapContext.Type     = WriteTrap;
  PchIoTrapContext.Length   = 4;
  PchIoTrapContext.Address  = 0;
  PchIoTrapContext.Context  = NULL;
  PchIoTrapContext.MergeDisable = FALSE;
  Status = mPchIoTrap->Register (
                        mPchIoTrap,
                        S3SupportSmmExitPmAuthCallback,
                        &PchIoTrapContext,
                        &mPchIoTrapHandle
                        );
  ASSERT_EFI_ERROR (Status);

  mPchS3SupportSmmProtocol->PchS3SupportIoTrap = PchIoTrapContext.Address;

  DEBUG ((EFI_D_INFO, "Pch S3 Support IO Trap Address = 0x%x\n", PchIoTrapContext.Address));
  DEBUG ((EFI_D_INFO, "S3SupportSmmEntryPoint() End\n"));

  return Status;
}
