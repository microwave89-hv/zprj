/** @file
  Digital Thermal Sensor (DTS) SMM Library.
  This SMM Library configures and supports the DigitalThermalSensor features
  for the platform.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#include "DTSHookLib.h"

/**
  Prepare data and protocol for Dts Hooe Lib

  @retval EFI_SUCCESS - Initialize complete
**/
EFI_STATUS
InitializeDtsHookLib (
  VOID
  )
{
  ///
  /// Nothing to do on CRB.
  ///
  return EFI_SUCCESS;
}

/**
  Platform may need to register some data to private data structure before generate
  software SMI or SCI.
**/
VOID
PlatformHookBeforeGenerateSCI (
  VOID
  )
{
  ///
  /// Nothing to do on CRB.
  ///
}

/**
  When system temperature out of specification, do platform specific programming to prevent
  system damage.
**/
VOID
PlatformEventOutOfSpec (
  VOID
  )
{
  EFI_STATUS Status;

  ///
  /// Handle critical event by shutting down via EC
  ///
  Status = InitializeKscLib ();
  if (Status == EFI_SUCCESS) {
    SendKscCommand (KSC_C_SYSTEM_POWER_OFF);
  }
}
