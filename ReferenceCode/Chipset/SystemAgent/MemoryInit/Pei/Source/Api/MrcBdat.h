/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved.
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

#ifndef _MrcBdat_h_
#define _MrcBdat_h_
#pragma pack(push, 1)

#include "MrcTypes.h"
#include "MrcApi.h"

/**
  Fill the compatible data structure RMT with the information provided by
  the memory initialization code.

  @param[in, out] MrcData - Constant pointer to the Mrc data structure which conatins the Rmt structure to fill.

  @retval Nothing.
**/
extern
MrcStatus
MrcFillRmtStructure (
  IN OUT MrcParameters *const MrcData
  );

#pragma pack(pop)
#endif // _MrcBdat_h_
