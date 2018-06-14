/** @file
  Defines and prototypes for the At driver.
  This driver implements the At protocol.

@copyright
  Copyright (c) 2004 - 2012 Intel Corporation. All rights reserved
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

//
// Statements that include other files
//
#include "EdkIIGlueDxe.h"

//
// Include the protocol header file
//
#include EFI_PROTOCOL_DEFINITION (At)

//
// Protocol GUID definition
//
EFI_GUID  gEfiAtProtocolGuid = EFI_AT_PROTOCOL_GUID;

//
// Protocol description
//
EFI_GUID_STRING(&gEfiAtProtocolGuid, "AT Protocol", "Intel (R) AT Protocol Services.");
