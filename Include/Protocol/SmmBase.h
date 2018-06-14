//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmBase.h 4     4/15/11 4:41p Markw $
//
// $Revision: 4 $
//
// $Date: 4/15/11 4:41p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmBase.h $
// 
// 4     4/15/11 4:41p Markw
// [TAG]  		EIP57440
// [Category]  	New Feature
// [Description]  	Update from previous check-in. Add inclusion Guards.
// [Files]  		SmmBase.h
// 
// 3     7/08/09 8:00p Markw
// Update headers.
// 
// 2     3/28/07 2:48p Markw
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmBase.h
//
// Description:	Smm Base Protocol header file.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_BASE_PROTOCOL_H__
#define __SMM_BASE_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#include <SMM.h>

#define EFI_SMM_BASE_PROTOCOL_GUID \
    {0x1390954D,0xda95,0x4227,0x93,0x28,0x72,0x82,0xc2,0x17,0xda,0xa8}

GUID_VARIABLE_DECLARATION(gEfiSmmBaseProtocolGuid,EFI_SMM_BASE_PROTOCOL_GUID);

//*******************************************************
//EFI SMM Handler Return Code
//*******************************************************
#define EFI_HANDLER_SUCCESS			0x0000
#define EFI_HANDLER_CRITICAL_EXIT	0x0001
#define EFI_HANDLER_SOURCE_QUIESCED	0x0002
#define EFI_HANDLER_SOURCE_PENDING	0x0003
	
#define SMM_COMMUNICATE_HEADER_GUID \
	{0xF328E36C,0x23B6,0x4a95,0x85,0x4B,0x32,0xE1,0x95,0x34,0xCD,0x75}


//******************************************************
// EFI_SMM_COMMUNICATE_HEADER
//******************************************************

#ifndef EFI_SMM_COMM_HDR_DEF
#define EFI_SMM_COMM_HDR_DEF


typedef struct {
	EFI_GUID	HeaderGuid;
	UINTN		MessageLength;
	UINT8		Data[1];
} EFI_SMM_COMMUNICATE_HEADER;
	
#endif

//***********************************************
// EFI_SMM_CALLBACK_ENTRY_POINT
//***********************************************
typedef EFI_STATUS (EFIAPI *EFI_SMM_CALLBACK_ENTRY_POINT) (
	IN EFI_HANDLE	SmmImageHandle,
	IN OUT VOID		*CommunicationBuffer OPTIONAL,
	IN OUT UINTN	*SourceSize OPTIONAL
);	


typedef struct _EFI_SMM_BASE_PROTOCOL EFI_SMM_BASE_PROTOCOL;
    
typedef EFI_STATUS (EFIAPI *EFI_SMM_REGISTER_HANDLER) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_DEVICE_PATH_PROTOCOL	*FilePath,
	IN VOID						*SourceBuffer OPTIONAL,
	IN UINTN					SourceSize,
	OUT EFI_HANDLE				*ImageHandle,
	IN BOOLEAN					LegacyIA32Binary OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_UNREGISTER_HANDLER) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_HANDLE				ImageHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_COMMUNICATE) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_HANDLE				ImageHandle,
	IN OUT VOID					*CommunicationBuffer,
	IN OUT UINTN				*SourceSize
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_CALLBACK_SERVICE) (
	IN EFI_SMM_BASE_PROTOCOL		*This,
	IN EFI_HANDLE					SmmImageHandle,
	IN EFI_SMM_CALLBACK_ENTRY_POINT	CallbackAddress,
	IN BOOLEAN						MakeLast OPTIONAL,
	IN BOOLEAN						FloatingPointSave OPTIONAL
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_INSIDE_OUT) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	OUT BOOLEAN					*InSmm
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_ALLOCATE_POOL) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN EFI_MEMORY_TYPE			PoolType,
	IN UINTN					Size,
	OUT VOID					**Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_FREE_POOL) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN VOID						*Buffer
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_GET_SMST_LOCATION) (
	IN EFI_SMM_BASE_PROTOCOL	*This,
	IN OUT EFI_SMM_SYSTEM_TABLE	**Smst
);


struct _EFI_SMM_BASE_PROTOCOL {
    EFI_SMM_REGISTER_HANDLER	Register;
    EFI_SMM_UNREGISTER_HANDLER	UnRegister;
    EFI_SMM_COMMUNICATE			Communicate;
    EFI_SMM_CALLBACK_SERVICE	RegisterCallback;
    EFI_SMM_INSIDE_OUT			InSmm;
    EFI_SMM_ALLOCATE_POOL		SmmAllocatePool;
    EFI_SMM_FREE_POOL			SmmFreePool;
    EFI_SMM_GET_SMST_LOCATION	GetSmstLocation;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
