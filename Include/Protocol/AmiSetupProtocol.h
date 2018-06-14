//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Board/Setup/AmiSetupProtocol.h 1     8/28/12 4:18p Artems $
//
// $Revision: 1 $
//
// $Date: 8/28/12 4:18p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/Setup/AmiSetupProtocol.h $
// 
// 1     8/28/12 4:18p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Add infrastructure to support runtime registration of
// setup controls callbacks
// [Files]  		Setup.c Setup.h Setup.cif AmiSetupProtocol.c
// AmiSetupProtocol.h
// 
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  AmiSetupProtocol.h
//
//  Description:
//  AMI Setup protocol definitions
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __AMI_SETUP_PROTOCOL__H__
#define __AMI_SETUP_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Setup.h>

// {C528AA1C-4011-42ee-A551-5238B8FB5A9F}
#define AMI_SETUP_PROTOCOL_GUID \
    { 0xc528aa1c, 0x4011, 0x42ee, 0xa5, 0x51, 0x52, 0x38, 0xb8, 0xfb, 0x5a, 0x9f }


GUID_VARIABLE_DECLARATION(AmiSetupProtocolGuid, AMI_SETUP_PROTOCOL_GUID);

typedef
EFI_STATUS
(EFIAPI *AMI_SETUP_REGISTER_CALLBACK) (
	IN UINT16 Class,
    IN UINT16 Subclass,
    IN UINT16 Key,
    IN SETUP_ITEM_CALLBACK_HANDLER *Handler,
    OUT EFI_HANDLE *Handle
	);

typedef
EFI_STATUS
(EFIAPI *AMI_SETUP_UNREGISTER_CALLBACK) (
	IN EFI_HANDLE Handle
	);

typedef
EFI_STATUS
(EFIAPI *AMI_SETUP_GET_CALLBACKS) (
	IN OUT UINTN *BufferSize,
    OUT SETUP_ITEM_CALLBACK *Buffer
	);

typedef
EFI_STATUS
(EFIAPI *AMI_SETUP_GET_CALLBACK_PARAMETERS) (
    OUT CALLBACK_PARAMETERS **Parameters
	);

typedef struct _AMI_SETUP_PROTOCOL
{
	AMI_SETUP_REGISTER_CALLBACK RegisterCallback;
    AMI_SETUP_UNREGISTER_CALLBACK UnregisterCallback;
    AMI_SETUP_GET_CALLBACKS GetCallbacks;
    AMI_SETUP_GET_CALLBACK_PARAMETERS GetCallbackParameters;
} AMI_SETUP_PROTOCOL;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
