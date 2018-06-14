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
// $Header: /Alaska/SOURCE/Core/EDK/GUID/MemoryTypeInformation.h 1     5/19/06 11:28p Felixp $
//
// $Revision: 1 $
//
// $Date: 5/19/06 11:28p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/EDK/GUID/MemoryTypeInformation.h $
// 
// 1     5/19/06 11:28p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	MemoryTypeInformation.h
//
// Description:	Memory Type Information GUID
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_MEMORY_TYPE_INFORMATION_GUID__H__
#define __EFI_MEMORY_TYPE_INFORMATION_GUID__H__
#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MEMORY_TYPE_INFORMATION_GUID \
	{ 0x4c19049f,0x4137,0x4dd3,0x9c,0x10,0x8b,0x97,0xa8,0x3f,0xfd,0xfa }

GUID_VARIABLE_DECLARATION(gEfiMemoryTypeInformationGuid, EFI_MEMORY_TYPE_INFORMATION_GUID);

#define EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME L"MemoryTypeInformation"

typedef struct {
	UINT32  Type;
	UINT32  NumberOfPages;
} EFI_MEMORY_TYPE_INFORMATION;
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