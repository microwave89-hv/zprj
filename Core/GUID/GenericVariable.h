//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Core/EDK/GUID/GenericVariable.h 1     11/19/09 12:28p Felixp $
//
// $Revision: 1 $
//
// $Date: 11/19/09 12:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/GUID/GenericVariable.h $
// 
// 1     11/19/09 12:28p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	GenericVariable.h
//
// Description:	gEfiGenericVariableGuid declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_GENERIC_VARIABLE_GUID__H__
#define __EFI_GENERIC_VARIABLE_GUID__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_GENERIC_VARIABLE_GUID \
  { 0x59d1c24f, 0x50f1, 0x401a, 0xb1, 0x01, 0xf3, 0x3e, 0x0d, 0xae, 0xd4, 0x43 }

GUID_VARIABLE_DECLARATION(gEfiGenericVariableGuid, EFI_GENERIC_VARIABLE_GUID);
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************