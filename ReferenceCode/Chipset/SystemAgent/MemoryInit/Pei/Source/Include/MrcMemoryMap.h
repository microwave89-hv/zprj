/** @file
  The physical memory map configuration definitions.

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
#ifndef _MrcMemoryMap_h_
#define _MrcMemoryMap_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcOem.h"

#define MEM_4GB (0x1000)  ///< Define the 4 GB size in 1MB units (1000MB = 1GB).

/**
@brief
  After BIOS determines the total physical memory size.
  Determines TOM which is defined by the total physical memory size.
  Determines TOM minus the ME memory size. The ME memory size is calculated from MESEG_BASE and MESEG_MASK.
  Determines MMIO allocation, which is system configuration dependent.

  Determines TOLUD which is the minimum value by comparing between "4GB minus MMIO size" and "TOM minus ME size".
  Determines Graphics Stolen Base, BDSM by subtracting the graphics data stolen memory size from TOLUD.
  Graphics Data Stolen Memory size is given by GMS field in GGC register.  It must be define before this stage.
  Determines Graphics GTT Stolen Base, BGSM by subtracting the GTT graphics stolen memory size from BDSM.
  GTT Stolen Memory size is given by GGMS field in GGC register.  It must be define before this stage.
  Determines TSEG Base, TSEGMB by subtracting TSEG size from BGSM.
  TSEG should be defined.
  Remove the memory hole caused by aligning TSEG to a 8MB boundary.
  Determine whether Memory Reclaim is available.  If "TOM minus ME Stolem Memory Size" is greater than the value of TOLUD, then memory reclaim is available to enable.
  Determine REMAPBASE if reclaim is enabled.  This is the maximum value by comparing between 4GB and "TOM minus ME size".
  Determine REMAPLIMIT () if reclaim is enabled.  This is the value of REMAPBASE plus "the difference between the value in TOLUD register and the lower of either 4GB or 'TOM minus ME Stolen memory size", and then minus 1 boundary.
  Determine TOUUD. TOUUD indicates the address one byte above the maximum DRAM.  If relcaim is disabled, this value is calculated by "TOM minus ME stolen size".  Otherwise, this value is set to REMAPLIMIT plus 1MB.

  @param[in, out] MrcData - Include all MRC global data. include also the memory map data.

  @retval MrcStatus -  if the reset is succeded.
**/
extern
MrcStatus
MrcSetMemoryMap (
  MrcParameters *const MrcData
  );

/**

@brief
  This function find the total memory in the system.
  and write it to TotalPhysicalMemorySize in MrcData structure.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing
**/
extern
void
MrcTotalMemory (
  MrcParameters *const MrcData
  );

/**

@brief
  this function write to the memory init registers.

  @param[in] PciEBaseAddress  - Address of the PCI Express BAR
  @param[in] GdxcBaseAddress  - Address of the GDXC BAR
  @param[in] MemoryMap        - Include all the memory map definitions

  @retval Nothing
**/
extern
void
UpdateMemoryMapRegisters (
  const U32                 PciEBaseAddress,
  const U32                 GdxcBaseAddress,
  const MrcMemoryMap *const MemoryMap
  );

#endif // _MrcMemoryMap_h_
