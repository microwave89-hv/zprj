/*++

Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  TcgLogHob.h

Abstract:

  GUIDs used for TCG event log table

--*/

#ifndef _TCG_LOG_HOB_GUID_H_
#define _TCG_LOG_HOB_GUID_H_

//
// Definitions for Flash Map
//
#define EFI_TCG_LOG_HOB_GUID \
  { 0x5f7d4e0e, 0x3d6d, 0x42bc, 0xa9, 0x42, 0xe, 0x91, 0xe8, 0x3e, 0x3c, 0x31 }

typedef struct _TCG_LOG_HOB_ {
  UINT32                        TableMaxSize;
  UINT32                        TableSize;
  UINT32                        EventNum;
  UINT32                        Reserved;
} TCG_LOG_HOB;

extern EFI_GUID gEfiTcgLogHobGuid;

#endif // _TCG_LOG_HOB_GUID_H_
