/*++
  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/*++

Copyright (c)  2008 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  HeciSmm.c

Abstract:

  SMM HECI driver

--*/

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "HeciHpet.h"
#include "HeciCore.h"
#endif // EDK_RELEASE_VERSION
//
// Global driver data
//
EFI_SMM_BASE_PROTOCOL *mSmmBase;
HECI_INSTANCE_SMM     *mHeciContext;

UINT32
CheckAndFixHeciForAccess (
  VOID
  )
/*++

Routine Description:
  This function provides a standard way to verify the HECI cmd and MBAR regs
  in its PCI cfg space are setup properly and that the local mHeciContext
  variable matches this info.

Arguments:
  None.

Returns:
  VOID

--*/
{
  UINTN HeciPciAddressBase;

  HeciPciAddressBase = mHeciContext->PciAddressBase;

  //
  // Read HECI_MBAR in case it has changed
  //
  mHeciContext->HeciMBAR = PciRead32 (HeciPciAddressBase + R_HECIMBAR) & 0xFFFFFFF0;

  //
  // Check if HECI_MBAR is disabled
  //
  if ((
        PciRead8 (HeciPciAddressBase + PCI_COMMAND_OFFSET) & (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)
    ) != (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER)
      ) {
    //
    // If cmd reg in pci cfg space is not turned on turn it on.
    //
    PciOr8 (
      HeciPciAddressBase + PCI_COMMAND_OFFSET,
      EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER
      );
  }

  return mHeciContext->HeciMBAR;
}

VOID
EnableHpet (
  VOID
  )
/*++

Routine Description:

  Enable Hpet function.

Arguments:

  None.

Returns:

  None.

--*/
{
  VOLATILE UINT32 *HpetConfigReg;

  HpetConfigReg = NULL;
  //
  // Get the High Precision Event Timer base address and enable the memory range
  //
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
  //
  // Read this back to force the write-back.
  //
  *HpetConfigReg = *HpetConfigReg | B_PCH_RCRB_HPTC_AE;

  //
  // Start the timer so it is up and running
  //
  mHeciContext->HpetTimer[HPET_GEN_CONFIG_LOW]  = HPET_START;
  mHeciContext->HpetTimer[HPET_GEN_CONFIG_LOW]  = HPET_START;

  return ;
}

EFI_STATUS
InitializeHECI (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:
  HECI driver entry point used to initialize support for the HECI device.

Arguments:
  ImageHandle - Standard entry point parameter.
  SystemTable - Standard entry point parameter.

Returns:
  EFI_STATUS

--*/
{
  EFI_STATUS  Status;

  Status = gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, &mSmmBase);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Create database record and add to database
  //
  Status = mSmmBase->SmmAllocatePool (
                      mSmmBase,
                      EfiRuntimeServicesData,
                      sizeof (HECI_INSTANCE_SMM),
                      &mHeciContext
                      );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mHeciContext->Handle = ImageHandle;

  //
  // Initialize HECI protocol pointers
  //
  mHeciContext->HeciCtlr.ResetHeci    = ResetHeciInterface;
  mHeciContext->HeciCtlr.SendwACK     = HeciSendwACK;
  mHeciContext->HeciCtlr.ReadMsg      = HeciReceive;
  mHeciContext->HeciCtlr.SendMsg      = HeciSend;
  mHeciContext->HeciCtlr.InitHeci     = HeciInitialize;
  mHeciContext->HeciCtlr.ReInitHeci   = HeciReInitialize;
  mHeciContext->HeciCtlr.MeResetWait  = MeResetWait;
  mHeciContext->HeciCtlr.GetMeStatus  = HeciGetMeStatus;
  mHeciContext->HeciCtlr.GetMeMode    = HeciGetMeMode;
  //
  // Initialize the HECI device
  //
  Status = InitializeHeciPrivate ();
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  //
  // Install the HECI interface
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mHeciContext->Handle,
                  &gSmmHeciProtocolGuid,
                  &mHeciContext->HeciCtlr,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  return EFI_SUCCESS;
}
