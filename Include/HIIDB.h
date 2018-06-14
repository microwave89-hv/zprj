//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Core/Include/HIIDB.h 9     12/29/09 1:16p Yakovlevs $Revision: 14 $
//
// $Date: 12/29/09 1:16p $
//**********************************************************************
// Revision History
// ----------------
//$Log: /Alaska/BIN/Core/Include/HIIDB.h $
// 
// 9     12/29/09 1:16p Yakovlevs
// Added Log
//
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HiiDb.h
//
// Description:	Human Interface Infrastructure Driver Internal definitions 
//
//<AMI_FHDR_END>
//**********************************************************************


#ifndef _HII_DRIVER_
#define _HII_DRIVER_

#ifdef __cplusplus
extern "C" {
#endif
#if EFI_SPECIFICATION_VERSION>0x20000
#pragma message("The HiiDb.h header contains UEFI 2.0 definitions")
#pragma message("UEFI 2.1 projects must use UefiHii.h instead")
#pragma message("The supported version of the UEFI specification is defined by the EFI_SPECIFICATION_VERSION SDL token")
#error the header is depricated
#else
#include <Efi.h>
#include <AmiDxeLib.h>
#include <Protocol\ExtHii.h>

//=====================================================================
//Initial Counts for the database
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	//Define SDL tokens for that
#define FONT_DB_MAX_COUNT		 	0x10000
#define KEYB_DB_MAX_COUNT			107
#define STRING_DB_MAX_COUNT			0x200
#define FORM_DB_MAX_COUNT			0x50

//=====================================================================
#define NG_SIZE 	19
#define WG_SIZE		38

typedef enum {
	lNone=0,
	lDel,
	lAdd
} LBL_ACTION;


#pragma  pack(push,1)
//=====================================================================

//typedef UINT8	HII_GL_COL[GLYPH_H];	
//for internal storage we don't need to store UNICODE weight it will be 
//an index in FontDB array
typedef struct _HII_N_FONT {
	UINT8			Attr;		//Font Glyph Attributes 
	UINT8			GlData[NG_SIZE]; 
} HII_N_FONT;

typedef struct _HII_W_FONT {
	UINT8			Attr;		//Font Glyph Attributes 
	UINT8			GlData[WG_SIZE]; 
} HII_W_FONT;

typedef struct _HII_HANDLE{
	EFI_HII_HANDLE		Handle; 
	UINT32				PriLang; //Primary Language Index
	EFI_GUID			Guid; //GUID asociated with this Handle 
	T_ITEM_LIST 		SecLang;
	STRING_REF			StrCount;
	STRING_REF			NextStrToken; //on that handle
	BOOLEAN				HasStr;
	VOID				*Ifr;
}HII_HANDLE;

typedef struct _HII_LANG {
	UINT16			sName[4]; //ISO 639-2 3 char + 0 terminator
	UINT16			*lName;
	UINT32			Attr;
} HII_LANG;


typedef struct _HII_STORE {
	EFI_IFR_VARSTORE	*VarStore;
	UINT8				*VarData;
	BOOLEAN				Updated;
}HII_STORE;

//Order is very importand for this srtructure
typedef struct _HII_STR {
//--Fields Used For DBE Key	--------
	STRING_REF		Token;	//size16	LSW
	UINT32			LangIdx;//size32	
	EFI_HII_HANDLE	Handle;	//size16 total = 8 bytes -> UINT64 MSW
//----------------------------------
	EXT_STR_INFO	String;
	EXT_STR_INFO	NewStr;
} HII_STR;			

typedef struct _HII_STRKEY {
	STRING_REF		Token;	//size16	LSW
	UINT32			LangIdx;//size32	
	EFI_HII_HANDLE	Handle;	//size16 total = 8 bytes -> UINT64 MSW
}HII_STRKEY;

typedef struct _HII_LABEL {
	EFI_FORM_LABEL		LabelId;
	EFI_IFR_LABEL		*Label;		//Points to a label in initial Package	
	EFI_IFR_OP_HEADER	*LabelData;
	UINTN				DataCount;	//number of OPCodes excluding label
	UINTN				DataLength; //in bytes
	HII_FORM			*OwnerForm;
	BOOLEAN				Updated;	//flag to know free *LabelData or not... initialy it is part of a 
									//Form Data buffer but after first update it is independent buffer
	T_ITEM_LIST			Objects;	//Points on list of HII_OBJECT Structure
	T_ITEM_LIST			Conditions;	//Indpendent Conditions the ones which don't have an object;
	HII_LABEL_UPDATE_CALLBACK UpdateCallBack;
} HII_LABEL;

//typedef struct _HII_COND {
//	EFI_IFR_OP_HEADER	*Action;	//EFI_IFR_INCONSISTENT_IF_OP or EFI_IFR_GRAYOUT_IF_OP or EFI_IFR_SUPPRESS_IF_OP; 
//	EFI_IFR_OP_HEADER	*Compare;	//EFI_IFR_EQ_ID_VAL_OP or EFI_IFR_EQ_ID_ID_OP or EFI_IFR_EQ_ID_LIST_OP or EFI_IFR_EQ_VAR_VAL_OP
//	EFI_IFR_OP_HEADER	*Logic;		//EFI_IFR_OR_OP or EFI_IFR_AND_OP or EFI_IFR_OR_OP with nexrt condition in the list
//	BOOLEAN				Result;		//to what logical value (TRUE or FALSE) condition Evaluates  
//	BOOLEAN				Updated;	//Signifies wethe Result reflects Current conditio  of the Object;
//} HII_COND;

typedef struct _HII_OBJECT {
	EFI_IFR_OP_HEADER	*ObjectCode;
	T_ITEM_LIST			Options;	//for composite opcodes like ORDERED_LIST or ONE_OF    
	HII_STORE			*Store1;	//Default NvStore	
	HII_STORE			*Store2;	//when EFI_IFR_VARSTORE_SELECT_PAIR_OP and EFI_IFR_EQ_ID_ID 
	T_ITEM_LIST			Conditions;	//just pointers to logical opcodes they must be following in right order
									//including starting conditions as INCONSISTENT_IF_OP or GRAYOUT_IF_OP or
									//SUPPRESS_IF_OP, Storage Compare options as EQ_xxx.. Logical AND OR NOT 
									//operators and END_IF OpCode. 
    T_ITEM_LIST         SuppressStores; // varstores used for suppress conditions
	BOOLEAN				Supress;	//TRUE if any conditions exicts which changes Suppress property of an Object
	BOOLEAN				GrayOut;	//TRUE if any conditions exicts which changes GrayOut property of an Object
	UINT16				Incons;		//TRUE if any conditions exicts which changes Inconsistant property of an Object
} HII_OBJECT;


#pragma	pack(pop)

typedef struct _HII_KB_LAYOUT_DATA {
	UINTN				HandleIndex;
	UINT8				KeyDscCount;
	EFI_KEY_DESCRIPTOR	*KeyDsc;
	//Here will be following the actual key descriprors
} HII_KB_LAYOUT_DATA;

typedef struct _HII_KB_DATA {
	UINTN				ActiveLayout;
	//Like T_ITEM_LIST
	UINTN				KblInitCount;
	UINTN				KblCount;
	HII_KB_LAYOUT_DATA	**KbLayout;
} HII_KB_DATA;



//=====================================================================
//Definitions of Hii Databases
typedef struct _HII_DB {
	EFI_HII_PROTOCOL_OLD HiiProtocolOld;
	EFI_HII_PROTOCOL	HiiProtocolNew;
	EXT_HII_PROTOCOL	HiiExtProtocol;
	EFI_HANDLE			HiiHandle;
	EFI_HANDLE			ImageHandle;
	EFI_HII_HANDLE		NextHiiHandle;
	T_ITEM_LIST			HandleDb;
	T_ITEM_LIST			LangDb;
	HII_N_FONT			*FontDb[FONT_DB_MAX_COUNT];
	T_ITEM_LIST			IfrDb;
	DBE_DATABASE		StringDb;
	HII_KB_DATA			KeybdDb;
}HII_DB;
#endif // #if EFI_SPECIFICATION_VERSION>0x20000
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
