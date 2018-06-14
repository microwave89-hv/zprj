/*++
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/

/*++

Copyright (c)  1999 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  AmtPeiPolicyInit.h

Abstract:

  Header file for the AmtPeiPolicyInit PEIM.

--*/
#ifndef _AMT_PEI_PLATFORM_POLICY_H_
#define _AMT_PEI_PLATFORM_POLICY_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#endif

#include EFI_PPI_DEFINITION (AmtPlatformPolicyPei)
// Debug #include "AmtPlatformPolicyUpdatePeiLib.h"

EFI_STATUS
AmtPeiPolicyInitEntryPoint (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN EFI_PEI_SERVICES          **PeiServices
  )
/*++

Routine Description:

  Initilize Intel AMT PEI Platform Policy

Arguments:

  FfsHeader               Pointer to Firmware File System file header.
  PeiServices             General purpose services available to every PEIM.

Returns:

  EFI_STATUS
  
--*/
;
#endif
