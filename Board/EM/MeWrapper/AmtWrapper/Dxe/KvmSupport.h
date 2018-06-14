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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/KvmSupport.h 1     2/08/12 1:08a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:08a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/KvmSupport.h $
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
// Name:            KvmSupport.h
//
// Description:     KVM BDS Support include file
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

  KvmSupport.h

Abstract:

  KVM BDS Support include file

--*/
#ifndef _KVM_SUPPORT_H_
#define _KVM_SUPPORT_H_

#include "Tiano.h"
#include "EfiDriverLib.h"
#include "BdsLib.h"
#include "AmtLib.h"
#include "MeLib.h"

BOOLEAN
BdsKvmInitialization (
  IN  VOID
  )
/*++

Routine Description:

  Request KVM message.
  
Arguments:

  None.
  
Returns:

  True    KVM Boot Option is an active.
  
--*/
;
#endif
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