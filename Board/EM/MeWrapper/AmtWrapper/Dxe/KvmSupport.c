//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/KvmSupport.c 1     2/08/12 1:08a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:08a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/KvmSupport.c $
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:10a Klzhan
// Initial Check-in.
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            KvmSupport.c
//
// Description:     Support routines for KVM init in the BDS
//
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++
 This file contains an 'Intel Peripheral Driver' and is        
 licensed for Intel CPUs and chipsets under the terms of your  
 license agreement with Intel or your vendor.  This file may   
 be modified by the user, subject to additional terms of the   
 license agreement                                             
--*/

/*++

Copyright (c) 2009 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  KvmSupport.c
  
Abstract:

  Support routines for KVM init in the BDS

--*/
// Remove for RC 0.8
/*
#include "KvmSupport.h"

BOOLEAN
BdsKvmInitialization (
  IN  VOID
  )
*/
/*++

Routine Description:

  Request KVM message.
  
Arguments:

  None.
  
Returns:

  True    KVM Boot Option is an active.
  
--*/
/*
{
  EFI_STATUS	  Status;
  UINT32        ResponseCode;

  if(ActiveManagementEnableKvm() == TRUE) {
    Status = HeciQueryKvmRequest(QUERY_REQUEST, &ResponseCode);
    if (EFI_ERROR (Status)) {
      gST->ConOut->ClearScreen (gST->ConOut);
      gST->ConOut->OutputString (gST->ConOut, L"Error!! Times up and the KVM session was cancelled!!");
      Status = HeciQueryKvmRequest(CANCEL_REQUEST, &ResponseCode);
    } else if (ResponseCode == KVM_SESSION_CANCELLED) {
      gST->ConOut->ClearScreen (gST->ConOut);
      gST->ConOut->OutputString (gST->ConOut, L"Error!! The request has rejected and the KVM session was cancelled!!");
    } else {
      return TRUE;    
    }
  }

  return FALSE;
}
*/
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************