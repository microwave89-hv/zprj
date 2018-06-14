/** @file
  AMT Status Code support at PEI phase

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
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
#include "Tiano.h"
#include "Pei.h"

#include EFI_PPI_DEFINITION (AmtStatusCode)

EFI_GUID  gPeiAmtStatusCodePpiGuid  = PEI_AMT_STATUS_CODE_PPI_GUID;
EFI_GUID  gAmtPetQueueHobGuid       = AMT_PET_QUEUE_HOB_GUID;
EFI_GUID  gAmtForcePushPetHobGuid   = AMT_FORCE_PUSH_PET_HOB_GUID;

EFI_GUID_STRING(&gPeiAmtStatusCodePpiGuid, "PEI AMT Status Code PPI", "PEI AMT Status Code PPI");
EFI_GUID_STRING(&gAmtPetQueueHobGuid, "PEI AMT PET Queue Hob", "PEI AMT PET Queue Hob");
EFI_GUID_STRING(&gAmtForcePushPetHobGuid, "PEI AMT Force Push PET Hob", "PEI AMT Force Push PET Hob");
