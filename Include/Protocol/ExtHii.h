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
// $Header: /Alaska/BIN/Core/Include/Protocol/ExtHii.h 6     12/29/09 1:17p Yakovlevs $Revision: 14 $
//
// $Date: 12/29/09 1:17p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/ExtHii.h $
// 
// 6     12/29/09 1:17p Yakovlevs
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Hii.h
//
// Description:	This file defines the Extended Human Interface 
//				Infrastructure protocol. 
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EXT_HII_PROTOCOL_H__
#define __EXT_HII_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/
#if EFI_SPECIFICATION_VERSION>0x20000 && !defined(GUID_VARIABLE_DEFINITION)
#pragma message("The EXT_HII_PROTOCOL protocol is only supported for the UEFI 2.0 projects")
#pragma message("The supported version of the UEFI specification is defined by the EFI_SPECIFICATION_VERSION SDL token")
#error the protocol is depricated
#else
//======================================================================
#include <EFI.h>

#define EFI_HII_EXT_PROTOCOL_GUID  \
	{ 0x2a57ae75, 0x8b7a, 0x4c64, 0x86, 0x56, 0xdb, 0x51, 0xdd, 0xc3, 0x6f, 0x7b }

GUID_VARIABLE_DECLARATION(gEfiExtHiiProtocolGuid,EFI_HII_EXT_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <AmiDxeLib.h>
#include <Protocol/Hii.h>

//Protocol Prototype
typedef struct _EXT_HII_PROTOCOL	EXT_HII_PROTOCOL;

typedef struct _EXT_STR_INFO {
	UINT16			StrLen;		//Length of the String in unicode characters
	UINT16			ScrLen;		//Length of the string in Narrow Glyphs(Screen Grid)
//	BOOLEAN			AllGlyphs;  //Indicates if all gliphs for the string available.
	UINT16			*StrPtr;	//pointer to UNICODE string itself;
} EXT_STR_INFO;

typedef struct _HII_FORMSET {
	UINT32					HandleId;
	EFI_HII_HANDLE			Handle;		//Actual Handle Value
	//this structure member must be updated each time UpdateForm is called
	//it always reflects an actual length of Last updated Formset!!!!
	UINTN					BufferLength;//in bytes excluding EndOfFormSet OPCODE!!!
	EFI_IFR_FORM_SET		*FormSetData;
	EFI_IFR_END_FORM_SET	*EndFormSet;
	T_ITEM_LIST				Forms;		//contains pointers to HII_FORM Structure
	T_ITEM_LIST		 		Labels;		//contains pointers to HII_LABEL Structure
	T_ITEM_LIST				Storages;
} HII_FORMSET;

typedef struct _HII_FORM {
	EFI_FORM_ID			FormId;
	EFI_IFR_FORM		*FormData;
	EFI_IFR_END_FORM	*EndForm;
	//this structure member must be updated each time UpdateForm is called
	//it always reflects an actual length of Last updated Form!!!!
	UINTN				BufferLength;	//in bytes including EndOfForm OPCODE!!!
	T_ITEM_LIST 		Labels;			//contains pointers to HII_LABEL Structure
	//the very first label is a fake label containing all data from beginning of the form
	//to the first valid label which means to be updated
	//!!!!I'm definetly missing the END_OF_LABEL_OP opcode!!!!!
	HII_FORMSET			*Owner;
} HII_FORM;


typedef VOID (EFIAPI *HII_LABEL_UPDATE_CALLBACK)(UINT16 LabelId, UINT16 HiiHandle, BOOLEAN AddData);


typedef EFI_STATUS  (EFIAPI *HII_EXT_REGISTER_LABEL_UPDATE_CALBACK)(
									IN  EXT_HII_PROTOCOL	*This,
									IN  EFI_HII_HANDLE		Handle,
									IN	EFI_FORM_LABEL		LabelId,
									IN  HII_LABEL_UPDATE_CALLBACK CallBack);

typedef EFI_STATUS  (EFIAPI *HII_EXT_UNREGISTER_LABEL_UPDATE_CALBACK)(
									IN  EXT_HII_PROTOCOL		*This,
									IN  EFI_HII_HANDLE			Handle,
									IN  EFI_FORM_LABEL			LabelId);

typedef EFI_STATUS  (EFIAPI *HII_EXT_GET_FORM_INFO)( 
									IN  EXT_HII_PROTOCOL	*This,
									IN  EFI_HII_HANDLE		Handle,
									IN  EFI_FORM_ID			FormId,
									OUT HII_FORM			**ExtFormInfo);

//Will get extended string info. 
typedef EFI_STATUS  (EFIAPI *HII_EXT_GET_STRING)(
									IN  EXT_HII_PROTOCOL	*This,
									IN  EFI_HII_HANDLE		Handle,
									IN  STRING_REF			Token,
									IN  CHAR16				*Lang,
									OUT EXT_STR_INFO		**ExtStrInfo);
		
typedef EFI_STATUS	(EFIAPI *HII_EXT_GET_FORMSET)(
									IN  EXT_HII_PROTOCOL	*This,
									IN  UINT16				ClassMask,
									IN	UINT16				SubClass,
                                    OUT T_ITEM_LIST			*FormSetList);

typedef EFI_STATUS	(EFIAPI *HII_EXT_GET_FORM_LABELS)(
									IN  EXT_HII_PROTOCOL	*This,
									IN  EFI_HII_HANDLE		Handle,
									IN  EFI_FORM_ID			FormID,
                                    OUT T_ITEM_LIST			*LabelList);


typedef struct _EXT_HII_PROTOCOL{
	HII_EXT_GET_STRING						ExtGetStringInfo;
	HII_EXT_GET_FORM_INFO					ExtGetFormInfo;
	HII_EXT_GET_FORMSET						ExtGetFormsetInfo;
	HII_EXT_REGISTER_LABEL_UPDATE_CALBACK	ExtRegLblCallBack;
	HII_EXT_UNREGISTER_LABEL_UPDATE_CALBACK ExtUnregLblCallBack;
	HII_EXT_GET_FORM_LABELS					ExtGetFormLabels;		
//TODO
// suggestions ?????
//TODO
} EXT_HII_PROTOCOL;

#endif // #if EFI_SPECIFICATION_VERSION>0x20000
/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif
#endif //_EXT_HII_H_

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
