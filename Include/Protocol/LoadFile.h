//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/LoadFile.h 4     3/13/06 1:40a Felixp $
//
// $Revision: 4 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/LoadFile.h $
// 
// 4     3/13/06 1:40a Felixp
// 
// 3     6/17/05 5:56p Felixp
// 
// 2     3/04/05 10:35a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     3/19/04 1:14p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	LoadFile.h
//
// Description:	LOAD_FILE protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __LOAD_FILE_PROTOCOL_H__
#define __LOAD_FILE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_LOAD_FILE_PROTOCOL_GUID \
	{0x56EC3091,0x954C,0x11d2,0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}

GUID_VARIABLE_DECLARATION(gEfiLoadFileProtocolGuid, EFI_LOAD_FILE_PROTOCOL_GUID);

typedef struct _EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_LOAD_FILE) (
	IN EFI_LOAD_FILE_PROTOCOL *This, IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN BOOLEAN BootPolicy, IN OUT UINTN *BufferSize,
	IN VOID *Buffer OPTIONAL
);

struct _EFI_LOAD_FILE_PROTOCOL{
	EFI_LOAD_FILE LoadFile;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
