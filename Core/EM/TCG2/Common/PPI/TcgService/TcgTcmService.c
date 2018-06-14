/*++

   Copyright (c)  2005 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Abstract:

   GUID definition for PEI_TCG_PPI

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgTcmService.c 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TcgService_PPI/TcgService/TcgTcmService.c $
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
// 2     3/29/11 3:00p Fredericko
// 
// 1     3/28/11 3:16p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
// 
// 2     5/19/10 6:48p Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TcgService.c
//
// Description: 
//  Defines TcgPpiguid
//
//<AMI_FHDR_END>
//*************************************************************************

#include <Efi.h>
#include <Pei.h>
#include <Tpm12.h>

#include EFI_PPI_DEFINITION( TcgTcmService )

EFI_GUID gPeiTcmPpiGuid = PEI_TCG_PPI_GUID;

EFI_GUID_STRING( &gPeiTcgPpiGuid, "TcgTcmService", "TCM Services PPI" );
