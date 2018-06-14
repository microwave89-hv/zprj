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
// $Header: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/BDS.h 3     3/13/06 1:45a Felixp $
//
// $Revision: 3 $
//
// $Date: 3/13/06 1:45a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/CORE_DXE/ArchProtocol/BDS.h $
// 
// 3     3/13/06 1:45a Felixp
// 
// 2     3/04/05 10:30a Mandal
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:21p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:42a Felixp
// 
// 1     12/23/04 9:29a Felixp
// 
// 1     3/30/04 2:24a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BDS.h
//
// Description:	BDS Architectural Protocol Definition
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __BDS_ARCH_PROTOCOL_H__
#define __BDS_ARCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_BDS_ARCH_PROTOCOL_GUID \
	{0x665E3FF6,0x46CC,0x11d4,0x9A,0x38,0x00,0x90,0x27,0x3F,0xC1,0x4D}

GUID_VARIABLE_DECLARATION(gEfiBdsArchProtocolGuid, EFI_BDS_ARCH_PROTOCOL_GUID);

typedef struct _EFI_BDS_ARCH_PROTOCOL EFI_BDS_ARCH_PROTOCOL;

typedef VOID (EFIAPI *EFI_BDS_ENTRY) (
	IN EFI_BDS_ARCH_PROTOCOL *This
);

struct _EFI_BDS_ARCH_PROTOCOL{
	EFI_BDS_ENTRY Entry;
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
