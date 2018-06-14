/*++ @file
  SMM Variable Protocol

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
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
--*/

#ifndef _SMM_VARIABLE_H_
#define _SMM_VARIABLE_H_

//
// SmmVariable Protocol GUID value
//
// Note: The GUID value is the same as the protocol produced in EDKII.
#define EFI_SMM_VARIABLE_PROTOCOL_GUID \
  { \
    0xed32d533, 0x99e6, 0x4209, 0x9c, 0xc0, 0x2d, 0x72, 0xcd, 0xd9, 0x98, 0xa7 \
  }

EFI_FORWARD_DECLARATION (EFI_SMM_VARIABLE_PROTOCOL);

typedef struct _EFI_SMM_VARIABLE_PROTOCOL  EFI_SMM_VARIABLE_PROTOCOL;

///
/// EFI SMM Variable Protocol is intended for use as a means
/// to store data in the EFI SMM environment.
///
struct _EFI_SMM_VARIABLE_PROTOCOL {
  EFI_GET_VARIABLE            SmmGetVariable;
  EFI_GET_NEXT_VARIABLE_NAME  SmmGetNextVariableName;
  EFI_SET_VARIABLE            SmmSetVariable;
  EFI_QUERY_VARIABLE_INFO     SmmQueryVariableInfo;
};

///
/// SmmVariable Protocol GUID variable.
///
extern EFI_GUID gEfiSmmVariableProtocolGuid;

#endif
