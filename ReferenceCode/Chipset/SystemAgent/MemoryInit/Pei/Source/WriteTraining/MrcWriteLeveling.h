/** @file
  The write leveling training algorithm definitions.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved.
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
  license agreement.
**/

#ifndef _MrcWriteLeveling_h_
#define _MrcWriteLeveling_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcReset.h"
#include "MrcDdr3.h"
#include "MrcIoControl.h"
#include "MrcReadReceiveEnable.h"
#include "MrcOem.h"

///
/// This defines the maximum ADD delay that can be programmed to the register. It may change in the future
///
#define MAX_ADD_DELAY (2)

/**
@brief
  this function execute the Jedec write leveling Cleanup.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded return mrcSuccess
**/
extern
MrcStatus
MrcJedecWriteLevelingCleanUp (
  IN OUT MrcParameters *const MrcData
  );

/**
@brief
  this function execute the functional write leveling training.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded return mrcSuccess
**/
extern
MrcStatus
MrcWriteLevelingTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
@brief
  this function execute the Jedec write leveling training.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succedes return mrcSuccess
**/
extern
MrcStatus
MrcJedecWriteLevelingTraining (
  IN OUT MrcParameters *const MrcData
  );

#endif // _MrcWriteLeveling_h_
