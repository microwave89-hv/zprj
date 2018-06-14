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
// $Header: /Alaska/BIN/Core/Include/Protocol/EdidActive.h 1     12/20/06 1:45p Felixp $
//
// $Revision: 1 $
//
// $Date: 12/20/06 1:45p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/EdidActive.h $
// 
// 1     12/20/06 1:45p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	EdidActive.h
//
// Description:	EFI_EDID_ACTIVE_PROTOCOL protocol declaration
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_EDID_ACTIVE_PROTOCOL__H__
#define __EFI_EDID_ACTIVE_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_EDID_ACTIVE_PROTOCOL_GUID \
    { 0xbd8c1056, 0x9f36, 0x44ec, 0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86 }

GUID_VARIABLE_DECLARATION (gEfiEdidActiveProtocolGuid, EFI_EDID_ACTIVE_PROTOCOL_GUID);

typedef struct {
    UINT32 SizeOfEdid;
    UINT8 *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;

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