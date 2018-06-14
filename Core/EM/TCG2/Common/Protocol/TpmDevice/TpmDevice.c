/*++

   Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Abstract:

   --*/
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TpmDevice_Protocol/TpmDevice/TpmDevice.c 1     4/21/14 2:15p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:15p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/CommonHeaders/TpmDevice_Protocol/TpmDevice/TpmDevice.c $
// 
// 1     4/21/14 2:15p Fredericko
// 
// 1     10/08/13 12:01p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:59p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 2     5/20/10 8:46a Fredericko
// Included File Header
// Included File Revision History 
// EIP 37653
//
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  TpmDevice.c
//
// Description: 
//  Defines Tpm Device Protocol GUID
//
//<AMI_FHDR_END>
//*************************************************************************
#include "Efi.h"
#include EFI_PROTOCOL_DEFINITION( TpmDevice )

EFI_GUID gEfiTpmDeviceProtocolGuid = EFI_TPM_DEVICE_PROTOCOL_GUID;

EFI_GUID_STRING( &gEfiTpmDeviceProtocolGuid,
                 "TPM DXE Driver Protocol",
                 "TPM DXE Driver Protocol" );
