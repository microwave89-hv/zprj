/** @file
  Power state and boot mode save and restore data functions.

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved.
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

#ifndef _MrcSaveRestore_h_
#define _MrcSaveRestore_h_
#pragma pack(push, 1)

#include "MrcTypes.h"
#include "MrcGlobal.h"

typedef struct {
  U16 StartMchbarOffset;
  U16 EndMchbarOffset;
} SaveDataControl;

/**
  This function verifies that neither CPU fuses or DIMMs have changed.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if fast boot is allowed, otherwise mrcColdBootRequired.
**/
extern
MrcStatus
MrcFastBootPermitted (
  IN     MrcParameters *const MrcData
  );

/**
  This function saves any values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcSaveMCValues (
  IN OUT MrcParameters *const MrcData
  );

/**
@brief
  This function saves any remaining values that need to be used during non-cold boots.

  @param[in, out] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the save occurred with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcSaveMCValuesFinal (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function copies the non-training information that needs to be restored
  from the 'save' data structure to the 'Output' data structure.

  @param[in, out] MrcData - include all the MRC global data.

  @retval mrcSuccess if the copy completed with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcRestoreNonTrainingValues (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function writes the previously determined training values back to the memory controller.

  @param[in] MrcData - Include all the MRC global data.

  @retval mrcSuccess if the memory controller write back completed with no errors, otherwise returns an error code.
**/
extern
MrcStatus
MrcRestoreTrainingValues (
  IN     MrcParameters *const MrcData
  );

/**
  Calculates a CRC-32 of the specified data buffer.

  @param[in] Data     - Pointer to the data buffer.
  @param[in] DataSize - Size of the data buffer, in bytes.

  @retval The CRC-32 value.
**/
extern
U32
MrcCalculateCrc32 (
  IN     const U8          *const Data,
  IN     const U32         DataSize
  );

#pragma pack(pop)
#endif
