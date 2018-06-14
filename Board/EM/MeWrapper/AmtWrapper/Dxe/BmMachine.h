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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BmMachine.h 2     10/30/12 8:23a Klzhan $
//
// $Revision: 2 $
//
// $Date: 10/30/12 8:23a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/BmMachine.h $
// 
// 2     10/30/12 8:23a Klzhan
// [TAG]  		EIP92074
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	AMT EFI Boot fail
// [RootCause]  	File path incorrect.
// 
// 1     2/08/12 1:08a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:43a Klzhan
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
// Name:            BmMachine.h
//
// Description:     Boot Manager Machine type 
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c) 2004, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  BmMachine.h

Abstract:

  Boot Manager Machine type 



Revision History

--*/

#ifndef _BM_MACHINE_H
#define _BM_MACHINE_H
#include "Token.h"

#if x64_BUILD
#define DEFAULT_REMOVABLE_FILE_NAME L"\\EFI\\BOOT\\BOOTX64.EFI"
#else
#define DEFAULT_REMOVABLE_FILE_NAME L"\\EFI\\BOOT\\BOOTIA32.EFI"
#endif

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