/** @file
  Various CPU-specific definitions.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
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
#ifndef _CPU_H_
#define _CPU_H_

#define B_FAMILY_MODEL_STEPPING       0x00000FFF

#define EFI_MSR_IA32_PERF_STS         0x198
#define EFI_MSR_IA32_PERF_CTL         0x199
#define EFI_MSR_IA32_CLOCK_MODULATION 0x19A
#define EFI_MSR_IA32_THERM_STATUS     0x19C

#define B_BS_VID                      0x0000003F
#define N_BS_VID                      0
#define B_BS_RATIO                    0x00001F00
#define N_BS_RATIO                    8

///
/// UINT64 workaround
///
/// The MS compiler doesn't handle QWORDs very well.  I'm breaking
/// them into DWORDs to circumvent the problems.  Converting back
/// shouldn't be a big deal.
///
#pragma pack(1)
typedef union _MSR_REGISTER {
  UINT64 Qword;

  struct _DWORDS {
    UINT32 Low;
    UINT32 High;
  } Dwords;

  struct _BYTES {
    UINT8 FirstByte;
    UINT8 SecondByte;
    UINT8 ThirdByte;
    UINT8 FouthByte;
    UINT8 FifthByte;
    UINT8 SixthByte;
    UINT8 SeventhByte;
    UINT8 EighthByte;
  } Bytes;

} MSR_REGISTER;
#pragma pack()
#endif
