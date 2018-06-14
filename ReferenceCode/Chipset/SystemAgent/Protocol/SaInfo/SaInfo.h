/** @file
  This file defines the SA Info Protocol.

@copyright
  Copyright (c) 2011 - 2014 Intel Corporation. All rights reserved
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
#ifndef _SA_INFO_H_
#define _SA_INFO_H_

///
/// Define SA INFO protocol GUID
///
/// EDK and EDKII have different GUID formats
///
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define EFI_SA_INFO_PROTOCOL_GUID \
  { \
    0x493b5bac, 0xbb9e, 0x4bf5, 0x83, 0x79, 0x20, 0xe2, 0xac, 0xa9, 0x85, 0x41 \
  }

#else
#define EFI_SA_INFO_PROTOCOL_GUID \
  { \
    0x493b5bac, 0xbb9e, 0x4bf5, \
    { \
      0x83, 0x79, 0x20, 0xe2, 0xac, 0xa9, 0x85, 0x41 \
    } \
  }
#endif
///
/// Extern the GUID for protocol users.
///
extern EFI_GUID                       gEfiSaInfoProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _EFI_SA_INFO_PROTOCOL  EFI_SA_INFO_PROTOCOL;

///
/// Protocol revision number
/// Any backwards compatible changes to this protocol will result in an update in the revision number
/// Major changes will require publication of a new protocol
///
/// Revision 1:  Original version
///
#define SA_INFO_PROTOCOL_REVISION_1 1
#define SA_RC_VERSION               0x01090000

///
/// Protocol definition
///
struct _EFI_SA_INFO_PROTOCOL {
  UINT8   Revision;
  UINT32  RCVersion;
};

#endif
