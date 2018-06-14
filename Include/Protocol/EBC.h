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
// $Header: /Alaska/BIN/Core/Include/Protocol/EBC.h 3     3/13/06 1:40a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/EBC.h $
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:34a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     8/22/04 11:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EBC.h
//
// Description:	EBC Protocol definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EBC_PROTOCOL__H__
#define __EBC_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_EBC_PROTOCOL_GUID \
	{0x13AC6DD1,0x73D0,0x11D4,0xB0,0x6B,0x00,0xAA,0x00,0xBD,0x6D,0xE7}

GUID_VARIABLE_DECLARATION(gEfiEbcProtocolGuid, EFI_EBC_PROTOCOL_GUID );

typedef struct _EFI_EBC_PROTOCOL EFI_EBC_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_EBC_CREATE_THUNK) (
	IN EFI_EBC_PROTOCOL *This, IN EFI_HANDLE ImageHandle,
	IN VOID *EbcEntryPoint, OUT VOID **Thunk
);

typedef EFI_STATUS (EFIAPI *EFI_EBC_UNLOAD_IMAGE) (
	IN EFI_EBC_PROTOCOL *This, IN EFI_HANDLE ImageHandle
);

typedef EFI_STATUS (* EBC_ICACHE_FLUSH) (
	IN EFI_PHYSICAL_ADDRESS Start, IN UINT64 Length
);

typedef EFI_STATUS (* EFI_EBC_REGISTER_ICACHE_FLUSH) (
	IN EFI_EBC_PROTOCOL *This, IN EBC_ICACHE_FLUSH Flush
);

typedef EFI_STATUS (* EFI_EBC_GET_VERSION) (
	IN EFI_EBC_PROTOCOL *This, OUT UINT64 *Version
);

struct _EFI_EBC_PROTOCOL {
	EFI_EBC_CREATE_THUNK CreateThunk;
	EFI_EBC_UNLOAD_IMAGE UnloadImage;
	EFI_EBC_REGISTER_ICACHE_FLUSH RegisterICacheFlush;
	EFI_EBC_GET_VERSION GetVersion;
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
