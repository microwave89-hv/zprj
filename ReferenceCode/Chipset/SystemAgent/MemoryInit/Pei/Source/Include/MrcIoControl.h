/** @file
  Memory controller IO configuration definition header.

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
#ifndef _MrcIoControl_h_
#define _MrcIoControl_h_

#include "MrcTypes.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"

/**
@brief
  Reset the MC IO module. The MC hardware will handle creating the 20 dclk pulse
  after the bit is set and will also clear the bit.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess    - IO Reset was done successfully
  @retval mrcDeviceBusy - Timed out waiting for the IO to clear the bit
**/
MrcStatus
IoReset (
  IN MrcParameters *const MrcData
  );

#endif // _MrcIoControl_h_
