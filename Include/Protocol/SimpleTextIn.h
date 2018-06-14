//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/SimpleTextIn.h 7     7/21/11 3:59p Artems $
//
// $Revision: 7 $
//
// $Date: 7/21/11 3:59p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/SimpleTextIn.h $
// 
// 7     7/21/11 3:59p Artems
// EIP 64356: Combine common keyboard definitions in one file
// 
// 6     8/21/09 10:19a Felixp
// define GUID_VARIABLE_DECLARATION macro only if it has not been already
// defined.
// 
// 5     10/17/07 4:10p Felixp
// Clean up
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:37a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 2     10/11/04 5:56p Olegi
// 
// 1     8/30/04 11:38a Olegi
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	SimpleTextIn.h
//
// Description:	SimpleTextIn protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SIMPLE_TEXT_INPUT_PROTOCOL_H__
#define __SIMPLE_TEXT_INPUT_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h> 
#include <KeyboardCommonDefinitions.h>

#ifndef GUID_VARIABLE_DECLARATION
#define GUID_VARIABLE_DECLARATION(Variable, Guid) extern EFI_GUID Variable
#endif

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
	{0x387477c1, 0x69c7, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }

GUID_VARIABLE_DECLARATION(gEfiSimpleTextInProtocolGuid,EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID);

//EFI.h contains forward declaration of EFI_SIMPLE_TEXT_INPUT_PROTOCOL
//typedef	struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET) ( 
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, 
	BOOLEAN ExtendedVerification );

typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY) (
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	EFI_INPUT_KEY *Key );

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	EFI_EVENT WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
