//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/RsdpPlus/Rsdp+ Includes/Protocol/ManageShadowProtocol.h 3     9/17/12 11:35p Norlwu $
//
// $Revision: 3 $
//
// $Date: 9/17/12 11:35p $
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/RsdpPlus/Rsdp+ Includes/Protocol/ManageShadowProtocol.h $
// 
// 3     9/17/12 11:35p Norlwu
// [TAG]  		EIP92735
// [Category]  	Improvement
// [Description]  	Please help to return the pointer and offset of
// HeapToF000 in MANAGE_SHADOW_RAM_PROTOCOL
// [Files]  		RsdpPlus.c
// ManageShadowRam.c
// ManageShadowProtocol.h
// 
// 2     8/17/12 8:14a Norlwu
// [TAG]  		EIP98247
// [Category]  	Improvement
// [Description]  	[RsdpPlus]Add alignment support in
// MANAGE_SHADOW_RAM_PROTOCOL
// [Files]  		RsdpPlus.sdl
// RsdpPlus.mak
// RsdpPlus.c
// ManageShadowRam.c
// ManageShadowRam.h
// 
// 1     2/09/12 3:17a Norlwu
// [TAG]  		EIP81756
// [Category]  	New Feature
// [Description]  	Enhance RspdPlus module.
// [Files]  		ManageShadowProtocol.h
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           ManageShadowProtocol.h
//
//  Description:    
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __MANAGE_SHADOW_PROTOCOL_H__
#define __MANAGE_SHADOW_PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MANAGE_SHADOW_RAM_PROTOCOL_GUID \
	{0x1fa319e, 0xc36c, 0x4f19, 0x9d, 0x9d, 0xd0, 0x29, 0xd, 0xbe, 0xe9, 0x28}

typedef struct{
	UINTN	BuffAddress;
	UINTN	UsedLength;
}DATA_BUFF_STRUC;

typedef
EFI_STATUS
(EFIAPI *HEAP_TO_E000) (
	UINT8	*pData,
	UINT32	Align,
	UINTN	Length,
	DATA_BUFF_STRUC	*pData2
);

typedef
EFI_STATUS
(EFIAPI *HEAP_TO_F000) (
	UINT8	*pData,
	UINT32	Align,
	UINTN	Length,
	DATA_BUFF_STRUC	*pData2
);

typedef struct {
	HEAP_TO_E000	HeapToE000;
	HEAP_TO_F000	HeapToF000;
} MANAGE_SHADOW_RAM_PROTOCOL;


//elink struct type define
typedef VOID (UPDATE_E000_SHDOW_RAM_HOOK)(
    IN UINT32*	pShadowRam,
	IN UINTN	Length
);

typedef VOID (UPDATE_F000_SHDOW_RAM_HOOK)(
    IN UINT32*	pShadowRam,
	IN UINTN	Length
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
