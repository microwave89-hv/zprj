/*++ @file
  Contains data used to determine if BIOS/ME/PMC are in sync
  with the required platform ChipsetInit settings.

@copyright
  Copyright (c) 2015 Intel Corporation. All rights reserved
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
--*/

#ifndef _S3_SUPPORT_HOBS_H__
#define _S3_SUPPORT_HOBS_H__

#define S3_SUPPORT_HOB_GUID \
  { \
    0xd33ca878, 0xde8f, 0x47d0, 0x9e, 0x47, 0x4d, 0x81, 0xb1, 0xa0, 0x9e, 0x88 \
  }

#define S3_DATA_HOB_GUID \
  { \
    0x806e1de3, 0xc6c1, 0x495c, 0x85, 0xf4, 0x1b, 0xda, 0xbf, 0x93, 0x0, 0x5d \
  }

extern EFI_GUID gS3SupportHobGuid;
extern EFI_GUID gS3DataHobGuid;

#pragma pack(push, 1)

#ifndef _PEI_HOB_H_
#ifndef __HOB__H__
#ifndef __PI_HOB_H__
typedef struct _EFI_HOB_GENERIC_HEADER {
  UINT16  HobType;
  UINT16  HobLength;
  UINT32  Reserved;
} EFI_HOB_GENERIC_HEADER;

typedef struct _EFI_HOB_GUID_TYPE {
  EFI_HOB_GENERIC_HEADER  Header;
  EFI_GUID                Name;
  //
  // Guid specific data goes here
  //
} EFI_HOB_GUID_TYPE;
#endif
#endif
#endif

typedef struct _S3_SUPPORT_HOB {
  EFI_HOB_GUID_TYPE      Header;
  UINT32                 PchS3PeimEntryPoint;    // Entry Point of the PCH S3 PEIM module
} S3_SUPPORT_HOB;

typedef struct _S3_DATA_HOB {
  EFI_HOB_GUID_TYPE      Header;
  VOID                   *S3DispatchDataArray;    // Pointer to the EFI_PCH_S3_DISPATCH_ARRAY to be passed to DXE
} S3_DATA_HOB;

#pragma pack(pop)
#endif

