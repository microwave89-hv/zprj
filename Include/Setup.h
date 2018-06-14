//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Setup.h 38    8/28/12 4:20p Artems $
//
// $Revision: 38 $
//
// $Date: 8/28/12 4:20p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Setup.h $
// 
// 38    8/28/12 4:20p Artems
// [TAG]  		EIP N/A
// [Category]  	New Feature
// [Description]  	Add infrastructure to support runtime registration of
// setup controls callbacks
// [Files]  		Setup.c Setup.h Setup.cif AmiSetupProtocol.c
// AmiSetupProtocol.h
// 
// 37    7/20/12 10:05a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Added new Boot Flow value
// [Files]  		Setup.h
// 
// 36    4/05/11 2:23p Yakovlevs
// [TAG]  		EIP 38174
// [Category]  	New Feature
// [Description]  	Generic support to handle PCI OUT OF RESOURDCES added. 
// [Files]  		PciBus Module.
// 
// 35    3/02/11 12:14p Felixp
// EIP 54862(Enhancement): 
// Setup.h required Setup_SUPPORT to be defined to include AUTOID.h, which
// was a problem for project that do not use Setup eModule but would like
// to keep using AUTOID.h
// The condition of inclusion of the AUTOID.h has been modified. It is
// updated from #if Setup_SUPPORT to 
// #if Setup_SUPPORT || AUTOID_HEADER_SUPPORT.
// To use AutioId.h without Setup eModule AUTOID_HEADER_SUPPORT must be
// defined. It is also necessary to provide a build target that generates
// AutoId.h
// 
// 34    2/09/11 12:13p Felixp
// Minor enhancement(EIP 53617): 
// #include "AMIVfr.h" is replaced with #include <AMIVfr.h> (AMIVfr.h is a
// system header)
// 
// 33    6/09/10 10:41p Felixp
// Setup Customization Support
// 
// 32    2/24/10 8:20a Felixp
// FastBoot field is removed.
// 
// 31    2/10/10 3:50p Felixp
// declaration of CALLBACK_PARAMETERS is updated
// 
// 30    2/05/10 1:58p Felixp
// The definition of the SETUP_ITEM_CALLBACK_HANDLER type is added.
// The declaration of the GetCallbackParameters functions is added.
// 
// 29    2/04/10 5:12p Felixp
// Auto-generated file Build\AutoId.h is included in Setup.h
// 
// 28    12/14/09 3:10p Aaronp
// 
// 27    12/14/09 3:02p Aaronp
// Added macro definition for INTERACTIVE_TEXT for support in UEFI2.1
// 
// 26    10/13/09 6:00p Felixp
// Hii.h renamed to UefiHii.h
// 
// 25    10/09/09 4:28p Felixp
// UEFI 2.1 related updates.
// 
// 24    4/18/08 6:35p Felixp
// 
// 23    1/31/08 11:52a Olegi
// Numlock field added.
// 
// 22    8/31/07 3:04p Felixp
// TSE-specific definitions moved to a separate header AmiVfr.h, which is
// part of AMITSE module.
// 
// 21    15/08/07 12:34p Anandakrishnanl
// Updated the IDE Security Config. structure with HardDisk Security User
// and Master Password status.
// 
// 20    25/06/07 5:31p Anandakrishnanl
// Missed To Fix the Build Error occured after previous Checkin
// 
// 19    22/06/07 12:47p Anandakrishnanl
// HardDisk Security Support Module Added.
// Need ACPI Module and SB Module and under Core\Include we updated
// Setup.h.
// Also New IdeBus bin module.
// 
// 18    6/04/07 6:05p Felixp
// 
// 16    3/13/07 5:21p Pavell
// Support for SETUP_ITK_COMPATIBILITY
// 
// 15    2/12/07 2:33p Felixp
// Definitions to support AMITSE 1.19.1089 features added.
// 
// 14    11/10/06 11:42a Felixp
// clean up
// 
// 13    10/13/06 2:56p Felixp
// 
// 12    1/12/06 9:49a Felixp
// 
// 11    12/05/05 9:30a Felixp
// 
// 10    12/05/05 9:27a Felixp
// 
// 9     12/05/05 9:19a Felixp
// PBA support added
// 
// 8     11/08/05 5:10a Felixp
// Password and AMISilentBoot field removed from SETUP_DATA to be
// complient
// with TSE 1.15.1044
// 
// 7     11/07/05 10:10a Felixp
// support for fast boot (with minimum configuration) added
// 
// 6     10/05/05 7:04p Felixp
// new values (supported by TSE 1.15.1033) added
// 
// 5     9/07/05 2:35p Girim
// Corrected the SYSTEM_ACCESS_GUID value and code cleanup.
// 
// 4     7/14/05 3:54p Felixp
// VFR.h removed.
// Code moved to Setup.h
// 
// 5     5/24/05 3:07p Felixp
// Modular setup framework implemented
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        Setup.h
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SETUP__H__
#define __SETUP__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Token.h>
#ifndef VFRCOMPILE
#if EFI_SPECIFICATION_VERSION>0x20000
#include <UefiHii.h>
#include <Protocol/HiiConfigAccess.h>
#else
#include <Protocol/Hii.h>
#include <Protocol/FormCallBack.h>
#endif//EFI_SPECIFICATION_VERSION
#else//VFRCOMPILE
#include<ControlDefinitions.h>
#endif//VFRCOMPILE
#if Setup_SUPPORT || AUTOID_HEADER_SUPPORT
#include <AutoId.h>
#endif
//**********************************************************************//
//                      Generic Definitions                             //
//**********************************************************************//
#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

#if EFI_SPECIFICATION_VERSION > 0x20000
#define MAIN_FORM_SET_GUID     { 0x985eee91, 0xbcac, 0x4238, 0x87, 0x78, 0x57, 0xef, 0xdc, 0x93, 0xf2, 0x4e }
#define ADVANCED_FORM_SET_GUID { 0xe14f04fa, 0x8706, 0x4353, 0x92, 0xf2, 0x9c, 0x24, 0x24, 0x74, 0x6f, 0x9f }
#define CHIPSET_FORM_SET_GUID  { 0xadfe34c8, 0x9ae1, 0x4f8f, 0xbe, 0x13, 0xcf, 0x96, 0xa2, 0xcb, 0x2c, 0x5b }
#define BOOT_FORM_SET_GUID     { 0x8b33ffe0, 0xd71c, 0x4f82, 0x9c, 0xeb, 0xc9, 0x70, 0x58, 0xc1, 0x3f, 0x8e }
#define SECURITY_FORM_SET_GUID { 0x981ceaee, 0x931c, 0x4a17, 0xb9, 0xc8, 0x66, 0xc7, 0xbc, 0xfd, 0x77, 0xe1 }
#define EXIT_FORM_SET_GUID     { 0xa43b03dc, 0xc18a, 0x41b1, 0x91, 0xc8, 0x3f, 0xf9, 0xaa, 0xa2, 0x57, 0x13 }
#else
#define MAIN_FORM_SET_GUID SETUP_GUID
#define ADVANCED_FORM_SET_GUID SETUP_GUID
#define CHIPSET_FORM_SET_GUID SETUP_GUID
#define BOOT_FORM_SET_GUID SETUP_GUID
#define SECURITY_FORM_SET_GUID SETUP_GUID
#define EXIT_FORM_SET_GUID SETUP_GUID
#endif

#define MAIN_FORM_SET_CLASS             0x01
#define ADVANCED_FORM_SET_CLASS         0x02
#define CHIPSET_FORM_SET_CLASS          0x04
#define BOOT_FORM_SET_CLASS             0x08
#define SECURITY_FORM_SET_CLASS         0x10
#define EXIT_FORM_SET_CLASS             0x20


#include <SetupDataDefinition.h>

#include <AMIVfr.h>

#ifdef VFRCOMPILE
//**********************************************************************//
//                        VFR Definitions                               //
//**********************************************************************//
#if defined(INVENTORY_SUPPORT) && INVENTORY_SUPPORT == 1
  #define INVENTORY(Name,Value) \
    inventory \
      help  = STRING_TOKEN(STR_EMPTY), \
      text  = Name, \
      text  = Value;
#else
  #define INVENTORY(Name,Value) \
    text \
      help  = STRING_TOKEN(STR_EMPTY), \
      text  = Name, \
      text  = Value, \
      flags = 0, \
      key   = 0;
#endif

#define SUBTITLE(Text) subtitle text = Text;
#define SEPARATOR SUBTITLE(STRING_TOKEN(STR_EMPTY))

#define SYSTEM_ACCESS_KEY_ID            0xF000

#if EFI_SPECIFICATION_VERSION>0x20000
#define INTERACTIVE_TEXT(HelpToken, CaptionToken, ValueToken, Key)\
    text help  = HelpToken,\
    	text  = CaptionToken,\
    	text  = ValueToken;\
    suppressif TRUE;\
        suppressif ideqval AMI_CALLBACK.Value == INTERACTIVE_TEXT_VALUE;\
	    text help  = HelpToken,\
	    	text  = CaptionToken,\
	    	text  = ValueToken,\
			flags = INTERACTIVE, key = Key;\
        endif;\
    endif;
#else
#define INTERACTIVE_TEXT(HelpToken, CaptionToken, ValueToken, Key)\
    text help  = HelpToken,\
        text  = CaptionToken,\
        text  = ValueToken,\
        flags = INTERACTIVE, key = Key;
#endif

#if EFI_SPECIFICATION_VERSION>0x20000
#define SUPPRESS_GRAYOUT_ENDIF endif; endif;
#else
#define SUPPRESS_GRAYOUT_ENDIF endif;
#endif
//definitions of the standard varstores
#if EFI_SPECIFICATION_VERSION>0x20000
#define SETUP_DATA_VARSTORE\
    varstore SETUP_DATA, name = Setup, guid = SETUP_GUID;
#define LANGUAGE_VARSTORE\
    varstore LANGUAGE, key = LANGUAGE_KEY_ID,\
        name = PlatformLang, guid = EFI_GLOBAL_VARIABLE_GUID;
#define LANGUAGE_CODES_VARSTORE\
    varstore LANGUAGE_CODES, key = LANGUAGE_CODES_KEY_ID,\
        name = PlatformLangCodes, guid = EFI_GLOBAL_VARIABLE_GUID;
#else //#if EFI_SPECIFICATION_VERSION>0x20000
#define SETUP_DATA_VARSTORE 
#define LANGUAGE_VARSTORE\
    varstore LANGUAGE, key = LANGUAGE_KEY_ID,\
        name = Lang, guid = EFI_GLOBAL_VARIABLE_GUID;
#define LANGUAGE_CODES_VARSTORE\
    varstore LANGUAGE_CODES, key = LANGUAGE_CODES_KEY_ID,\
        name = LangCodes, guid = EFI_GLOBAL_VARIABLE_GUID;
#endif //#if EFI_SPECIFICATION_VERSION>0x20000
#define SYSTEM_ACCESS_VARSTORE\
    varstore SYSTEM_ACCESS, key = SYSTEM_ACCESS_KEY_ID,\
        name = SystemAccess, guid = SYSTEM_ACCESS_GUID;
#define AMITSESETUP_VARSTORE\
    varstore AMITSESETUP, key = AMITSESETUP_KEY,\
        name = AMITSESetup, guid = AMITSESETUP_GUID;
#define BOOT_MANAGER_VARSTORE\
    varstore BOOT_MANAGER, key = BOOT_MANAGER_KEY_ID,\
        name = BootManager, guid = BOOT_MANAGER_GUID;
#define TIMEOUT_VARSTORE\
    varstore TIMEOUT, key = BOOT_TIMEOUT_KEY_ID,\
        name = Timeout, guid = EFI_GLOBAL_VARIABLE_GUID;
#define BOOT_ORDER_VARSTORE\
    varstore BOOT_ORDER, key = BOOT_ORDER_KEY_ID,\
        name = BootOrder, guid = EFI_GLOBAL_VARIABLE_GUID;
#define NEW_BOOT_OPTION_VARSTORE\
    varstore NEW_BOOT_OPTION, key = NEW_BOOT_OPTION_KEY_ID,\
        name = AddBootOption, guid = ADD_BOOT_OPTION_GUID;
#define DEL_BOOT_OPTION_VARSTORE\
    varstore DEL_BOOT_OPTION, key = DEL_BOOT_OPTION_KEY_ID,\
        name = DelBootOption, guid = DEL_BOOT_OPTION_GUID;
#define LEGACY_DEV_INFO_VARSTORE\
    varstore LEGACY_DEV_INFO, key = LEGACY_DEV_KEY_ID,\
        name = LegacyDev, guid = LEGACY_DEV_ORDER_GUID;
#define LEGACY_GROUP_INFO_VARSTORE\
    varstore LEGACY_GROUP_INFO, key = LEGACY_GROUP_KEY_ID,\
        name = LegacyGroup, guid = LEGACY_DEV_ORDER_GUID;
#define LEGACY_DEV_ORDER_VARSTORE\
    varstore LEGACY_DEV_ORDER, key = LEGACY_ORDER_KEY_ID,\
        name = LegacyDevOrder, guid = LEGACY_DEV_ORDER_GUID;
#define AMI_CALLBACK_VARSTORE\
    varstore AMI_CALLBACK, key = AMI_CALLBACK_KEY_ID,\
        name = AMICallback, guid = AMI_CALLBACK_GUID;
#define BOOT_NOW_COUNT_VARSTORE\
    varstore BOOT_NOW_COUNT, key = BOOT_NOW_COUNT_KEY_ID,\
        name = BootNowCount, guid = BOOT_NOW_COUNT_GUID;
#define EFI_SHELL_VARSTORE\
    varstore EFI_SHELL, key = EFI_SHELL_KEY_ID,\
        name = Shell, guid = EFI_SHELL_FILE_GUID;
#else // #ifdef VFRCOMPILE
//**********************************************************************//
//                        C Definitions                                 //
//**********************************************************************//
//Type of the Setup Callback Handling function registered using 
// ITEM_CALLBACK eLink
typedef EFI_STATUS (SETUP_ITEM_CALLBACK_HANDLER)(
    EFI_HII_HANDLE HiiHandle, 
    UINT16 Class, 
    UINT16 SubClass, 
    UINT16 Key
);

typedef struct{
    UINT16 Class;
    UINT16 SubClass;
    UINT16 Key;
    SETUP_ITEM_CALLBACK_HANDLER *UpdateItem;
} SETUP_ITEM_CALLBACK;

#if EFI_SPECIFICATION_VERSION>0x20000
typedef struct{
    EFI_HII_CONFIG_ACCESS_PROTOCOL *This;
    EFI_BROWSER_ACTION Action;
    EFI_QUESTION_ID KeyValue;
    UINT8 Type;
    EFI_IFR_TYPE_VALUE *Value;
    EFI_BROWSER_ACTION_REQUEST *ActionRequest;
} CALLBACK_PARAMETERS;
#else
typedef struct{
    EFI_FORM_CALLBACK_PROTOCOL *This;
    UINT16 KeyValue;
    EFI_IFR_DATA_ARRAY *Data;
    EFI_HII_CALLBACK_PACKET **Packet;
} CALLBACK_PARAMETERS;
#endif // EFI_SPECIFICATION_VERSION>0x20000

//Defined in the Setup Module
VOID InitString(EFI_HII_HANDLE HiiHandle, STRING_REF StrRef, CHAR16 *sFormat, ...);
CALLBACK_PARAMETERS* GetCallbackParameters();
#endif

//Boot Flow Definitions
// EF152FB4-7B2F-427D-BDB4-7E0A05826E64
#define	BOOT_FLOW_VARIABLE_GUID \
	{ 0xEF152FB4, 0x7B2F, 0x427D, 0xBD, 0xB4, 0x7E, 0x0A, 0x05, 0x82, 0x6E, 0x64 }

#define	BOOT_FLOW_CONDITION_RECOVERY            2
#define	BOOT_FLOW_CONDITION_FIRST_BOOT          4
#define BOOT_FLOW_CONDITION_PCI_OUT_OF_RESOURCE 9
#define	BOOT_FLOW_CONDITION_OS_UPD_CAP 			0xB


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************