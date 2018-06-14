/** @file
  GUIDs used for SMRAM CPU DATA Header as signature for search

@copyright
  Copyright (c) 2011 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
**/
#include "Tiano.h"
#include EFI_GUID_DEFINITION (SmramCpuDataHeader)

EFI_GUID gSmramCpuDataHeaderGuid = SMRAM_CPU_DATA_HEADER_GUID;

EFI_GUID_STRING(&gSmramCpuDataHeaderGuid, "SMRAM CPU DATA Header", "SMRAM CPU DATA Header GUID");
