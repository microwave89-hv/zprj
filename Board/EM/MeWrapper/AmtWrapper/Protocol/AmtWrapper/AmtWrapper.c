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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperProtocolLib/AmtWrapper/AmtWrapper.c 1     2/08/12 1:09a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:09a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperProtocolLib/AmtWrapper/AmtWrapper.c $
// 
// 1     2/08/12 1:09a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:42a Klzhan
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
// Name:            AmtWrapper.c
//
// Description:     Amt Wrapper Define file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "Efi.h"

#include EFI_PROTOCOL_DEFINITION(AmtWrapper)

EFI_GUID gEfiAmtWrapperProtocolGuid = EFI_AMT_WRAPPER_PROTOCOL_GUID;

EFI_GUID_STRING(&gEfiAmtWrapperProtocolGuid, "AMT Wrapper Protocol", "AMT Wrapper Protocol");

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