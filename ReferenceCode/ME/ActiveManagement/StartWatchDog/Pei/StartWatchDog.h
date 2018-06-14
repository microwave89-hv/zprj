/** @file
  StartWatchDog header file

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights
  reserved This software and associated documentation (if any)
  is furnished under a license and may only be used or copied in
  accordance with the terms of the license. Except as permitted
  by such license, no part of this software or documentation may
  be reproduced, stored in a retrieval system, or transmitted in
  any form or by any means without the express written consent
  of Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _EFI_START_WATCH_DOG_H_
#define _EFI_START_WATCH_DOG_H_

#include "BootMode.h"
#include "AmtLibPei.h"

#include EFI_PPI_DEPENDENCY (Heci)

//
// Function Prototypes
//

/**
  Perform the platform spefific initializations.

  @param[in] FfsHeader            FFS file header pointer of this driver.
  @param[in] PeiServices          General purpose services available to every PEIM.

  @retval EFI_SUCCESS             if the interface could be successfully installed.
**/
EFI_STATUS
EFIAPI
PeiInitStartWatchDog (
  IN EFI_FFS_FILE_HEADER          *FfsHeader,
  IN EFI_PEI_SERVICES             **PeiServices
  )
;

#endif // _EFI_START_WATCH_DOG_H_
