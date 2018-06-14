//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/Protocol/EdidDiscovered.h 1     12/20/06 1:45p Felixp $
//
// $Revision: 1 $
//
// $Date: 12/20/06 1:45p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/EdidDiscovered.h $
// 
// 1     12/20/06 1:45p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EdidDiscovered.h
//
// Description:	EFI_EDID_DISCOVERED_PROTOCOL protocol declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_EDID_DISCOVERED_PROTOCOL__H__
#define __EFI_EDID_DISCOVERED_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_EDID_DISCOVERED_PROTOCOL_GUID \
    { 0x1c0c34f6, 0xd380, 0x41fa, 0xa0, 0x49, 0x8a, 0xd0, 0x6c,0x1a, 0x66, 0xaa }

GUID_VARIABLE_DECLARATION (gEfiEdidDiscoveredProtocolGuid, EFI_EDID_DISCOVERED_PROTOCOL_GUID);

typedef struct {
    UINT32 SizeOfEdid;
    UINT8 *Edid;
} EFI_EDID_DISCOVERED_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************