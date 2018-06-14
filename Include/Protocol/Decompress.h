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
// $Header: /Alaska/BIN/Core/Include/Protocol/Decompress.h 3     3/13/06 1:40a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:40a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/Decompress.h $
// 
// 3     3/13/06 1:40a Felixp
// 
// 2     3/04/05 10:33a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     3/30/04 2:24a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Decompress.h
//
// Description:	Decompress Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __DECOMPRESS_PROTOCOL__H__
#define __DECOMPRESS_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_DECOMPRESS_PROTOCOL_GUID \
{0xd8117cfe,0x94a6,0x11d4,0x9a,0x3a,0x0,0x90,0x27,0x3f,0xc1,0x4d}

GUID_VARIABLE_DECLARATION(gEfiDecompressProtocolGuid, EFI_DECOMPRESS_PROTOCOL_GUID);

typedef struct _EFI_DECOMPRESS_PROTOCOL EFI_DECOMPRESS_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_DECOMPRESS_GET_INFO) (
	IN EFI_DECOMPRESS_PROTOCOL *This,
	IN VOID *Source, IN UINT32 SourceSize,
	OUT UINT32 *DestinationSize, OUT UINT32 *ScratchSize
);

typedef EFI_STATUS (EFIAPI *EFI_DECOMPRESS_DECOMPRESS) (
	IN EFI_DECOMPRESS_PROTOCOL *This,
	IN VOID* Source, IN UINT32 SourceSize,
	IN OUT VOID* Destination, IN UINT32 DestinationSize,
	IN OUT VOID* Scratch, IN UINT32 ScratchSize
);

struct _EFI_DECOMPRESS_PROTOCOL {
	EFI_DECOMPRESS_GET_INFO GetInfo;
	EFI_DECOMPRESS_DECOMPRESS Decompress;
} ;
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
