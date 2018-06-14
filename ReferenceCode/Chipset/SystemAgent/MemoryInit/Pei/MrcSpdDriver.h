/** @file
  This file contains functions that read the SPD data for each DIMM slot over
  the SMBus interface.

@Copyright
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
  license agreement
**/

#ifndef _MrcSpdDriver_h_
#define _MrcSpdDriver_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcGlobal.h"
#include "MrcOemDebugPrint.h"
#include "MrcOemSmbus.h"

/**
@brief
  Read the SPD data over the SMBus, for all DIMM slots and copy the data to the MrcData structure.
  The SPD data locations read is controlled by the current boot mode.

  @param[in] BootMode - Mrc Boot Mode
  @param[in] Inputs - Mrc Inputs structure

  @retval mrcSuccess if the read is successful, otherwise mrcDimmNotExist, which
  @retval indicates that no slots are populated.
**/
extern
MrcStatus
MrcGetSpdData (
  IN     const MrcBootMode BootMode,
  IN OUT MrcInput *const   Inputs
  );

#endif
