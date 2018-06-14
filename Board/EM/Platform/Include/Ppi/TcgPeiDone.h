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

  TcgPeiDone.h

Abstract: 

This file contains PPI GUID installed at the end of TCG component
initialization

--*/
#ifndef _PEI_TCGPEIDONE_PPI_H_
#define _PEI_TCGPEIDONE_PPI_H_

//
// This is an indicator GUID without any data. It represents the fact that a PEIM
// has written the address of the PEI_TPM_PPI_GUID into the EFI_PEI_SERVICES
//
#define PEI_TPM_PPI_GUID \
{ \
 0xca4853f4, 0xe94b, 0x42b4, 0x86, 0x42, 0xcd, 0xe2, 0x8a, 0x7f, 0xac, 0x2d \
}

extern EFI_GUID gPeiTpmPpiGuid;

#endif
