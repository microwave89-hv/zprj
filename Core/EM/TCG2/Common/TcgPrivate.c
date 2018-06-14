/*++

   Copyright (c)  1999 - 2007 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   TcgPrivate.c

   Abstract:

      TCG private interface GUID used internally by TCG modules

   --*/
/*++
   This file contains an 'Intel Peripheral Driver' and uniquely
   identified as "Intel Mobile Silicon Support Module" and is
   licensed for Intel Mobile CPUs and chipsets under the terms of your
   license agreement with Intel or your vendor.  This file may
   be modified by the user, subject to additional terms of the
   license agreement
   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgPrivate.c 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgPrivate.c $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 12:00p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:58p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 3     5/19/10 5:20p Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgPrivate.c
//
// Description: 
//  Contains guid definition for Tcg Private protocol
//
//<AMI_FHDR_END>
//*************************************************************************
#include <EFI.h>
#include "TcgPrivate.h"

EFI_GUID gEfiTcgPrivateInterfaceGuid = EFI_TCG_PRIVATE_INTERFACE_GUID;
