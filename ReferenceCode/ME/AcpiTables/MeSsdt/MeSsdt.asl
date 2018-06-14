/*++
  This file contains an 'Intel Peripheral Driver' and uniquely  
  identified as "Intel Reference Module" and is                 
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/

/*++

Copyright (c)  2012 - 2013 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

Module Name:

  MeSsdt.asl

Abstract:

  Me SSDT Table ASL code

--*/


DefinitionBlock (
  "MeSsdt.aml",
  "SSDT",
  0x01,
  "MeSsdt",
  "MeSsdt ",
  0x3000
  )
{

  OperationRegion(MENV,SystemMemory,0xFFFF0000,0xAA55)
  Field(MENV,AnyAcc,Lock,Preserve)
  {
  MERV, 32,     ///   (000) ME NVS Protocol Revision
  ///
  /// PTT Solution
  ///
  PTTS, 8,       ///   (004) PTT Solution Method Selection
  ///
  /// PTT Allocated Buffer Address
  ///
  PTTB, 64,      ///   (005) PTT Allocated Buffer Address

  }
}