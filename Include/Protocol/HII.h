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
// $Header: /Alaska/BIN/Core/Include/Protocol/HII.h 11    10/14/09 10:24p Felixp $Revision: 14 $
//
// $Date: 10/14/09 10:24p $
//**********************************************************************
// Revision History
// ----------------
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Hii.h
//
// Description:	This file defines the Human Interface Infrastructure protocol 
//				which will be used by resources which want to publish 
//				IFR/Font/String data and have it collected by the 
//				Configuration engine.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_PROTOCOL_H__
#define __HII_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
/****** DO NOT WRITE ABOVE THIS LINE *******/
#if EFI_SPECIFICATION_VERSION>0x20000 && !defined(GUID_VARIABLE_DEFINITION)
#pragma message("The Include\\Hii.h header contains UEFI 2.0 definitions")
#pragma message("UEFI 2.1 projects must use different set of headers:")
#pragma message("\tfor generic HII definitions use: UefiHii.h")
#pragma message("\tfor HII database operations use: Protocol\\HiiDatabase.h")
#pragma message("\tfor HII string operations use: Protocol\\HiiString.h")
#pragma message("The supported version of the UEFI specification is defined by the EFI_SPECIFICATION_VERSION SDL token")
#error the header is depricated
#else
//======================================================================
#include <EFI.h>

#define EFI_HII_OLD_PROTOCOL_GUID  \
   	{ 0xcd361957, 0xafbe, 0x425e, 0xa3, 0x58, 0x5f, 0x58, 0x89, 0xcf, 0xfe, 0x7b }
#define EFI_HII_NEW_PROTOCOL_GUID  \
	{ 0xea816d2c, 0xcee5, 0x4f02, 0x99, 0xb5, 0xd3, 0x90, 0x5c, 0xbb, 0xd0, 0x77 }
#define EFI_HII_PROTOCOL_GUID EFI_HII_NEW_PROTOCOL_GUID

GUID_VARIABLE_DECLARATION(gEfiHiiProtocolGuid,EFI_HII_PROTOCOL_GUID);

#ifndef GUID_VARIABLE_DEFINITION
#include <Protocol/UgaDraw.h> 

typedef struct _EFI_HII_PROTOCOL EFI_HII_PROTOCOL;

//======================================================================
// Global definition
//======================================================================

//======================================================================
// Defined Type values
#define EFI_HII_FONT        1
#define EFI_HII_STRING      2
#define EFI_HII_IFR         3
#define EFI_HII_KEYBOARD    4
#define EFI_HII_HANDLES     5
#define EFI_HII_VARIABLE    6 //not in current spec
#define EFI_HII_DEVICE_PATH 7 //not in current spec


//Unicode Char const
//#define NARROW_CHAR         0xFFF0
//#define WIDE_CHAR           0xFFF1
//#define NON_BREAKING_CHAR   0xFFF2


//Gliph const
#define GLYPH_W				8
#define GLYPH_H				19


typedef UINT16        		EFI_FORM_ID;
typedef UINT16        		EFI_FORM_LABEL;
typedef UINT16        		EFI_HII_HANDLE;

// Glyph Attributes
#define GLYPH_NON_SPACING   1
#define GLYPH_WIDE			2

// String attributes
#define LANG_RIGHT_TO_LEFT  1

//String releated definitions
typedef UINT32        		RELOFST;
typedef UINT16        		STRING_REF;
typedef	CHAR16 				*EFI_STRING;

//IFR releated definitions
#define EFI_IFR_FORM_OP                   0x01
#define EFI_IFR_SUBTITLE_OP               0x02
#define EFI_IFR_TEXT_OP                   0x03
#define EFI_IFR_GRAPHIC_OP                0x04
#define EFI_IFR_ONE_OF_OP                 0x05
#define EFI_IFR_CHECKBOX_OP               0x06
#define EFI_IFR_NUMERIC_OP                0x07
#define EFI_IFR_PASSWORD_OP               0x08
#define EFI_IFR_ONE_OF_OPTION_OP          0x09    // ONEOF OPTION field
#define EFI_IFR_SUPPRESS_IF_OP            0x0A
#define EFI_IFR_END_FORM_OP               0x0B
#define EFI_IFR_HIDDEN_OP                 0x0C 
#define EFI_IFR_END_FORM_SET_OP           0x0D
#define EFI_IFR_FORM_SET_OP               0x0E
#define EFI_IFR_REF_OP                    0x0F
#define EFI_IFR_END_ONE_OF_OP             0x10
#define EFI_IFR_END_OP                    EFI_IFR_END_ONE_OF_OP
#define EFI_IFR_INCONSISTENT_IF_OP        0x11
#define EFI_IFR_EQ_ID_VAL_OP              0x12
#define EFI_IFR_EQ_ID_ID_OP               0x13
#define EFI_IFR_EQ_ID_LIST_OP             0x14
#define EFI_IFR_AND_OP                    0x15
#define EFI_IFR_OR_OP                     0x16
#define EFI_IFR_NOT_OP                    0x17
#define EFI_IFR_END_IF_OP                 0x18  // for endif of inconsistentif, suppressif, grayoutif
#define EFI_IFR_GRAYOUT_IF_OP             0x19
#define EFI_IFR_DATE_OP                   0x1A
#define EFI_IFR_TIME_OP                   0x1B
#define EFI_IFR_STRING_OP                 0x1C
#define EFI_IFR_LABEL_OP                  0x1D
#define EFI_IFR_SAVE_DEFAULTS_OP          0x1E
#define EFI_IFR_RESTORE_DEFAULTS_OP       0x1F
#define EFI_IFR_BANNER_OP                 0x20
#define EFI_IFR_INVENTORY_OP              0x21
#define EFI_IFR_EQ_VAR_VAL_OP             0x22
#define EFI_IFR_ORDERED_LIST_OP           0x23
#define EFI_IFR_VARSTORE_OP               0x24
#define EFI_IFR_VARSTORE_SELECT_OP        0x25
#define EFI_IFR_VARSTORE_SELECT_PAIR_OP   0x26
#define EFI_IFR_LAST_OPCODE               EFI_IFR_VARSTORE_SELECT_PAIR_OP
#define EFI_IFR_NV_ACCESS_COMMAND         0xFF  

//Values for the flags fields in some VFR opcodes
#define EFI_IFR_FLAG_DEFAULT              0x01
#define EFI_IFR_FLAG_MANUFACTURING        0x02
#define EFI_IFR_FLAG_INTERACTIVE          0x04
#define EFI_IFR_FLAG_NV_ACCESS            0x08
#define EFI_IFR_FLAG_RESET_REQUIRED       0x10
#define EFI_IFR_FLAG_LATE_CHECK           0x20
#define EFI_IFR_FLAG_CREATED              0x80  // Used to flag dynamically created op-codes.

#define EFI_NON_DEVICE_CLASS              0x00  // Useful when you do not want something in the Device Manager
#define EFI_DISK_DEVICE_CLASS             0x01
#define EFI_VIDEO_DEVICE_CLASS            0x02
#define EFI_NETWORK_DEVICE_CLASS          0x04
#define EFI_INPUT_DEVICE_CLASS            0x08
#define EFI_ON_BOARD_DEVICE_CLASS         0x10
#define EFI_OTHER_DEVICE_CLASS            0x20

#define EFI_SETUP_APPLICATION_SUBCLASS    0x00
#define EFI_GENERAL_APPLICATION_SUBCLASS  0x01
#define EFI_FRONT_PAGE_SUBCLASS           0x02
#define EFI_SINGLE_USE_SUBCLASS           0x03  // Used to display a single entity and then exit

#define EFI_IFR_BANNER_ALIGN_LEFT         0
#define EFI_IFR_BANNER_ALIGN_CENTER       1
#define EFI_IFR_BANNER_ALIGN_RIGHT        2
#define EFI_IFR_BANNER_TIMEOUT            0xFF

//----------------------------------------------------------------------------
// Modifier values

#define EFI_NULL_MODIFIER                 0x0000
#define EFI_LEFT_CONTROL_MODIFIER         0x0001
#define EFI_RIGHT_CONTROL_MODIFIER        0x0002
#define EFI_LEFT_ALT_MODIFIER             0x0003
#define EFI_RIGHT_ALT_MODIFIER            0x0004
#define EFI_ALT_GR_MODIFIER               0x0005
#define EFI_INSERT_MODIFIER               0x0006
#define EFI_DELETE_MODIFIER               0x0007
#define EFI_PAGE_DOWN_MODIFIER            0x0008
#define EFI_PAGE_UP_MODIFIER              0x0009 
#define EFI_HOME_MODIFIER                 0x000A
#define EFI_END_MODIFIER                  0x000B
#define EFI_LEFT_SHIFT_MODIFIER           0x000C
#define EFI_RIGHT_SHIFT_MODIFIER          0x000D
#define EFI_CAPS_LOCK_MODIFIER            0x000E
#define EFI_NUM_LOCK_MODIFIER             0x000F
#define EFI_LEFT_ARROW_MODIFIER           0x0010
#define EFI_RIGHT_ARROW_MODIFIER          0x0011
#define EFI_DOWN_ARROW_MODIFIER           0x0012
#define EFI_UP_ARROW_MODIFIER             0X0013
#define EFI_DEAD_KEY_MODIFIER             0x0014 
#define EFI_DEAD_KEY_DEPENDENCY_MODIFIER  0x0015
#define EFI_FUNCTION_KEY_ONE_MODIFIER     0x0016
#define EFI_FUNCTION_KEY_TWO_MODIFIER     0x0017
#define EFI_FUNCTION_KEY_THREE_MODIFIER   0x0018
#define EFI_FUNCTION_KEY_FOUR_MODIFIER    0x0019
#define EFI_FUNCTION_KEY_FIVE_MODIFIER    0x001A
#define EFI_FUNCTION_KEY_SIX_MODIFIER     0x001B
#define EFI_FUNCTION_KEY_SEVEN_MODIFIER   0x001C
#define EFI_FUNCTION_KEY_EIGHT_MODIFIER   0x001D
#define EFI_FUNCTION_KEY_NINE_MODIFIER    0x001E
#define EFI_FUNCTION_KEY_TEN_MODIFIER     0x001F
#define EFI_FUNCTION_KEY_ELEVEN_MODIFIER  0x0020
#define EFI_FUNCTION_KEY_TWELVE_MODIFIER  0x0021

// Keys that have multiple control functions based on modifier 
// settings are handled in the keyboard driver implementation.  
// For instance PRINT_KEY might have a modifier held down and
// is still a nonprinting character, but might have an alternate
// control function like SYSREQUEST

#define EFI_PRINT_MODIFIER                0x0022
#define EFI_SYS_REQUEST_MODIFIER          0x0023
#define EFI_SCROLL_LOCK_MODIFIER          0x0024
#define EFI_PAUSE_MODIFIER                0x0025
#define EFI_BREAK_MODIFIER                0x0026

// Keyboard layout switching modifiers
// This assumes that the driver implementation will not
// assign a key definition if one of the following modifier
// values is presented.

#define EFI_LAYOUT_SWITCH_MODIFIER        0x0027
#define EFI_LAYOUT_SWITCH_DEPENDENCY_MODIFIER 0x0028


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma pack(push, 1) //must be 1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//======================================================================
//Packages
typedef struct _EFI_HII_PACK_HEADER {
	UINT32 Length;
	UINT16 Type;
} EFI_HII_PACK_HEADER;


//********************************************************
// EFI_HII_HANDLE_PACK
//********************************************************
typedef struct _EFI_HII_HANDLE_PACK{
	EFI_HII_PACK_HEADER 	Header; 			// Must be filled in
	EFI_HANDLE 				ImageHandle; 		// Must be filled in
	EFI_HANDLE 				DeviceHandle; 		// Optional
	EFI_HANDLE 				ControllerHandle;	// Optional
	EFI_HANDLE 				CallbackHandle; 	// Optional
} EFI_HII_HANDLE_PACK;


typedef struct EFI_HII_PACKAGES {
//TODO: HII Spec. 0.92 defines NumberOfPackages as UINT32
//However, EDK header defines it as UINTN
//Should we be compatible with the spec or with EDK?
//For now, we are choosing EDK
//	UINT32 				NumberOfPackages;
    UINTN     			NumberOfPackages;
	EFI_GUID 			*GuidId;
//	EFI_HII_HANDLE_PACK *HandlePack;
	
} EFI_HII_PACKAGES;


//======================================================================
// EFI_HII_IFR_PACK
//======================================================================
typedef struct {
  EFI_HII_PACK_HEADER   Header;
} EFI_HII_IFR_PACK;

//======================================================================
// EFI_HII_VARIABLE_PACK
//======================================================================
typedef struct {
  EFI_HII_PACK_HEADER   Header;
  EFI_GUID              VariableGuid;
  UINT32                VariableNameLength;
  UINT16                VariableId;
//  CHAR16                VariableName[]; //Null-terminated
} EFI_HII_VARIABLE_PACK;

//======================================================================
// EFI_HII_VARIABLE_PACK_LIST
//======================================================================
typedef struct _EFI_HII_VARIABLE_PACK_LIST {
  struct _EFI_HII_VARIABLE_PACK_LIST   *NextVariablePack;
  EFI_HII_VARIABLE_PACK                *VariablePack;
//Per implementation but better to gave it anywhere in the memory.
  //EFI_HII_VARIABLE_PACK 			   Content //
} EFI_HII_VARIABLE_PACK_LIST;


//======================================================================
// EFI_DEVICE_PATH_PACK
//======================================================================
typedef struct {
  EFI_HII_PACK_HEADER   Header;
//  EFI_DEVICE_PATH       DevicePath[];
} EFI_HII_DEVICE_PATH_PACK;

//======================================================================
// EFI_HII_DATA_TABLE
//======================================================================
typedef struct {
  EFI_HII_HANDLE  HiiHandle;
  EFI_GUID        PackageGuid;
  UINT32          DataTableSize;
  UINT32          IfrDataOffset;
  UINT32          StringDataOffset;
  UINT32          VariableDataOffset;
  UINT32          DevicePathOffset;
  UINT32          NumberOfVariableData;
  UINT32          NumberOfLanguages;
  //EFI_HII_DEVICE_PATH_PACK DevicePath[];
  //EFI_HII_VARIABLE_PACK VariableData[];
  //EFI_HII_IFR_PACK IfrData;
  //EFI_HII_STRING_PACK StringData[];
} EFI_HII_DATA_TABLE;

//======================================================================
// EFI_HII_EXPORT_TABLE
//======================================================================
typedef struct {
//HII .91 spec defines following field as UINT32 but Intel's R8 implememtation still 
//using UINT16 value. To be Compliant with ITK, I'll leave this field as UINT16
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//  uncomment this and comment next line
//  UINT32           NumberOfHiiDataTables;
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	UINT16           NumberOfHiiDataTables;
	EFI_GUID         Revision;
  	//EFI_HII_DATA_TABLE HiiDataTable[];
} EFI_HII_EXPORT_TABLE;

//======================================================================
typedef struct {
	BOOLEAN               FormSetUpdate;        // If TRUE, next variable is significant
	EFI_PHYSICAL_ADDRESS  FormCallbackHandle;   // If not 0, will update Formset with this info
  	BOOLEAN               FormUpdate;           // If TRUE, next variable is significant
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	//to maintain compatibility with Intel's Setup I changed this 
	//Intel doesnot have this field included in Sources but they does in Spec??????????
	//UINT16				  FormValue;			// Which Form to be Updated if FormUpdate=TRUE; 
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	STRING_REF            FormTitle;            // If not 0, will update Form with this info
	UINT16                DataCount;            // The number of Data entries in this structure
	UINT8                 *Data;                // An array of 1+ op-codes, specified by DataCount
} EFI_HII_UPDATE_DATA;

//======================================================================
// A string package is used to localize strings to a particular
// language.  The package is associated with a particular driver 
// or set of drivers.  Tools are used to associate tokens with 
// string references in forms and in programs.  These tokens are 
// language agnostic.  When paired with a language pack (directly 
// or indirectly), the string token resolves into an actual 
// UNICODE string.  The NumStringPointers determines how many
// StringPointers (offset values) there are as well as the total
// number of Strings that are defined.
typedef struct {
  EFI_HII_PACK_HEADER   Header;
  RELOFST               LanguageNameString;
  RELOFST               PrintableLanguageName;
  UINT32                NumStringPointers;
  UINT32                Attributes;
//  RELOFST               StringPointers[];
//  EFI_STRING            Strings[];
} EFI_HII_STRING_PACK;

//======================================================================

typedef struct {
  CHAR16                UnicodeWeight;
  UINT8                 Attributes;
  UINT8                 GlyphCol1[GLYPH_H];
} EFI_NARROW_GLYPH;

typedef struct {
  CHAR16                UnicodeWeight;
  UINT8                 Attributes;
  UINT8                 GlyphCol1[GLYPH_H];
  UINT8                 GlyphCol2[GLYPH_H];
  UINT8                 Pad[3];
} EFI_WIDE_GLYPH;

//======================================================================
// A font list consists of a font header followed by a series 
// of glyph structures.  Note that fonts are not language specific.
typedef struct {
  EFI_HII_PACK_HEADER   Header;
  UINT16                NumberOfNarrowGlyphs;
  UINT16                NumberOfWideGlyphs;
} EFI_HII_FONT_PACK;

//======================================================================
// Keyboard Keys Definition
typedef enum {
  EfiKeyLCtrl, EfiKeyA0, EfiKeyLAlt, EfiKeySpaceBar, 
  EfiKeyA2, EfiKeyA3, EfiKeyA4, EfiKeyRCtrl, EfiKeyLeftArrow, 
  EfiKeyDownArrow, EfiKeyRightArrow, EfiKeyZero, 
  EfiKeyPeriod, EfiKeyEnter, EfiKeyLShift, EfiKeyB0,
  EfiKeyB1, EfiKeyB2, EfiKeyB3, EfiKeyB4, EfiKeyB5, EfiKeyB6, 
  EfiKeyB7, EfiKeyB8, EfiKeyB9, EfiKeyB10, EfiKeyRshift, 
  EfiKeyUpArrow, EfiKeyOne, EfiKeyTwo, EfiKeyThree, 
  EfiKeyCapsLock, EfiKeyC1, EfiKeyC2, EfiKeyC3, EfiKeyC4, 
  EfiKeyC5, EfiKeyC6, EfiKeyC7, EfiKeyC8, EfiKeyC9, 
  EfiKeyC10, EfiKeyC11, EfiKeyC12, EfiKeyFour, EfiKeyFive, 
  EfiKeySix, EfiKeyPlus, EfiKeyTab, EfiKeyD1, EfiKeyD2, 
  EfiKeyD3, EfiKeyD4, EfiKeyD5, EfiKeyD6, EfiKeyD7, EfiKeyD8, 
  EfiKeyD9, EfiKeyD10, EfiKeyD11, EfiKeyD12, EfiKeyD13, 
  EfiKeyDel, EfiKeyEnd, EfiKeyPgDn, EfiKeySeven, EfiKeyEight, 
  EfiKeyNine, EfiKeyE0, EfiKeyE1, EfiKeyE2, EfiKeyE3, 
  EfiKeyE4, EfiKeyE5, EfiKeyE6, EfiKeyE7, EfiKeyE8, EfiKeyE9,
  EfiKeyE10, EfiKeyE11, EfiKeyE12, EfiKeyBackSpace, 
  EfiKeyIns, EfiKeyHome, EfiKeyPgUp, EfiKeyNLck, EfiKeySlash,
  EfiKeyAsterisk, EfiKeyMinus, EfiKeyEsc, EfiKeyF1, EfiKeyF2, 
  EfiKeyF3, EfiKeyF4, EfiKeyF5, EfiKeyF6, EfiKeyF7, EfiKeyF8, 
  EfiKeyF9, EfiKeyF10, EfiKeyF11, EfiKeyF12, EfiKeyPrint, 
  EfiKeySLck, EfiKeyPause
} EFI_KEY;

typedef struct {
  EFI_KEY               Key;
  CHAR16                Unicode;
  CHAR16                ShiftedUnicode;
  CHAR16                AltGrUnicode;
  CHAR16                ShiftedAltGrUnicode;
  UINT16                Modifier;
} EFI_KEY_DESCRIPTOR;

//======================================================================
// This structure allows a sparse set of keys to be redefined 
// or a complete redefinition of the keyboard layout.  Most 
// keyboards have a lot of commonality in their layouts, therefore 
// only defining those keys that need to change from the default 
// minimizes the passed in information.  
//
// Additionally, when an update occurs, the active keyboard layout 
// will be switched to the newly updated keyboard layout.  This 
// allows for situations that when a keyboard layout driver is 
// loaded as part of system initialization, the system will default 
// the keyboard behavior to the new layout.
//
// Each call to update the keyboard mapping should contain the 
// complete set of key descriptors to be updated, since every
// call to the HII which contains an EFI_HII_KEYBOARD_PACK will
// wipe the previous set of overrides.  A call to 
//
typedef struct {
  EFI_HII_PACK_HEADER	Header;
  EFI_KEY_DESCRIPTOR    *Descriptor;
  UINT8              	DescriptorCount;
} EFI_HII_KEYBOARD_PACK;



// The StringPack is a pointer to a series of EFI_HII_STRING_PACK structures.
// The terminating instance of this structure will be a NULL entry.


//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//Not actual anymore is been replaced by EFI_HII_PACKAGES structure below
typedef struct {
  EFI_HII_IFR_PACK       *IfrPack;
  EFI_HII_FONT_PACK      *FontPack;
  EFI_HII_STRING_PACK    *StringPack;
  EFI_HII_KEYBOARD_PACK  *KeyboardPack;
  EFI_GUID               *GuidId;
} EFI_HII_PACK_LIST;


//======================================================================
// IFR Structure definitions
typedef struct {
  UINT8                     OpCode;
  UINT8                     Length;
} EFI_IFR_OP_HEADER;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  EFI_GUID                  Guid;
  STRING_REF                FormSetTitle;
  STRING_REF                Help;
  EFI_PHYSICAL_ADDRESS      CallbackHandle;
  UINT16                    Class;
  UINT16                    SubClass;
  UINT16                    NvDataSize;      // set once, size of the NV data as defined in the script
} EFI_IFR_FORM_SET;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    FormId;
  STRING_REF                FormTitle;
} EFI_IFR_FORM;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    LabelId;
} EFI_IFR_LABEL;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  STRING_REF                SubTitle;
} EFI_IFR_SUBTITLE;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  STRING_REF                Help;
  STRING_REF                Text;
  STRING_REF                TextTwo;
  UINT8                     Flags;        // This is included solely for purposes of interactive/dynamic support.
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
} EFI_IFR_TEXT;

//
// goto
//
typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    FormId;
  STRING_REF                Prompt;
  STRING_REF                Help;         // The string Token for the context-help
  UINT8                     Flags;        // This is included solely for purposes of interactive/dynamic support.
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
} EFI_IFR_REF;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_END_FORM;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_END_FORM_SET;

//
// Also notice that the IFR_ONE_OF and IFR_CHECK_BOX are identical in structure......code assumes this to be true, if this ever
// changes we need to revisit the InitializeTagStructures code
//
typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // The ID designating what the question is about...sucked in from a #define, likely in the form of a variable name
  UINT8                     Width;        // The Size of the Data being saved
  STRING_REF                Prompt;       // The String Token for the Prompt
  STRING_REF                Help;         // The string Token for the context-help
} EFI_IFR_ONE_OF;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // The offset in NV for storage of the data
  UINT8                     MaxEntries;   // The maximum number of options in the ordered list (=size of NVStore)
  STRING_REF                Prompt;       // The string token for the prompt
  STRING_REF                Help;         // The string token for the context-help
} EFI_IFR_ORDERED_LIST;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // The ID designating what the question is about...sucked in from a #define, likely in the form of a variable name
  UINT8                     Width;        // The Size of the Data being saved
  STRING_REF                Prompt;       // The String Token for the Prompt
  STRING_REF                Help;         // The string Token for the context-help
  UINT8                     Flags;        // For now, if non-zero, means that it is the default option, - further definition likely 
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
} EFI_IFR_CHECK_BOX;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  STRING_REF                Option;       // The string token describing the option
  UINT16                    Value;        // The value associated with this option that is stored in the NVRAM if chosen
  UINT8                     Flags;        // For now, if non-zero, means that it is the default option, - further definition likely above
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
} EFI_IFR_ONE_OF_OPTION;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // The ID designating what the question is about...sucked in from a #define, likely in the form of a variable name
  UINT8                     Width;        // The Size of the Data being saved
  STRING_REF                Prompt;       // The String Token for the Prompt
  STRING_REF                Help;         // The string Token for the context-help
  UINT8                     Flags;        // This is included solely for purposes of interactive/dynamic support.
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
  UINT16                    Minimum;
  UINT16                    Maximum;
  UINT16                    Step;         // If step is 0, then manual input is specified, otherwise, left/right arrow selection is called for
  UINT16                    Default;
} EFI_IFR_NUMERIC;

//
// There is an interesting twist with regards to Time and Date.  This is one of the few items which can accept input from
// a user, however may or may not need to use storage in the NVRAM space.  The decided method for determining if NVRAM space
// will be used (only for a TimeOp or DateOp) is:  If .QuestionId == 0 && .Width == 0 (normally an impossibility) then use system
// resources to store the data away and not NV resources.  In other words, the setup engine will call gRT->SetTime, and gRT->SetDate
// for the saving of data, and the values displayed will be from the gRT->GetXXXX series of calls.  
//
typedef struct {
  EFI_IFR_NUMERIC            Hour;
  EFI_IFR_NUMERIC            Minute;
  EFI_IFR_NUMERIC            Second;
} EFI_IFR_TIME;

typedef struct {
  EFI_IFR_NUMERIC            Year;
  EFI_IFR_NUMERIC            Month;
  EFI_IFR_NUMERIC            Day;
} EFI_IFR_DATE;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // The ID designating what the question is about...sucked in from a #define, likely in the form of a variable name
  UINT8                     Width;        // The Size of the Data being saved -- BUGBUG -- remove someday
  STRING_REF                Prompt;       // The String Token for the Prompt
  STRING_REF                Help;         // The string Token for the context-help
  UINT8                     Flags;        // This is included solely for purposes of interactive/dynamic support.
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
  UINT8                     MinSize;      // Minimum allowable sized password
  UINT8                     MaxSize;      // Maximum allowable sized password
  UINT16                    Encoding;     
} EFI_IFR_PASSWORD;                       

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // The ID designating what the question is about...sucked in from a #define, likely in the form of a variable name
  UINT8                     Width;        // The Size of the Data being saved -- BUGBUG -- remove someday
  STRING_REF                Prompt;       // The String Token for the Prompt
  STRING_REF                Help;         // The string Token for the context-help
  UINT8                     Flags;        // This is included solely for purposes of interactive/dynamic support.
  UINT16                    Key;          // Value to be passed to caller to identify this particular op-code
  UINT8                     MinSize;      // Minimum allowable sized password
  UINT8                     MaxSize;      // Maximum allowable sized password
} EFI_IFR_STRING;                         

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_END_ONE_OF;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    Value;
  UINT16                    Key;
} EFI_IFR_HIDDEN;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT8                     Flags;
} EFI_IFR_SUPPRESS;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT8                     Flags;
} EFI_IFR_GRAYOUT;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  STRING_REF                Popup;
  UINT8                     Flags;
} EFI_IFR_INCONSISTENT;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // offset into variable storage 
  UINT8                     Width;        // size of variable storage
  UINT16                    Value;        // value to compare against
} EFI_IFR_EQ_ID_VAL;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // offset into variable storage
  UINT8                     Width;        // size of variable storage
  UINT16                    ListLength;
  UINT16                    ValueList[1];
} EFI_IFR_EQ_ID_LIST;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId1;  // offset into variable storage for first value to compare
  UINT8                     Width;        // size of variable storage (must be same for both)
  UINT16                    QuestionId2;  // offset into variable storage for second value to compare
} EFI_IFR_EQ_ID_ID;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    VariableId;   // offset into variable storage 
  UINT16                    Value;        // value to compare against
} EFI_IFR_EQ_VAR_VAL;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_AND;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_OR;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_NOT;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
} EFI_IFR_END_IF;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    FormId;
  STRING_REF                Prompt;
  STRING_REF                Help;
  UINT8                     Flags;
  UINT16                    Key;
} EFI_IFR_SAVE_DEFAULTS;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  STRING_REF                Help;
  STRING_REF                Text;
  STRING_REF                TextTwo;       // optional text
} EFI_IFR_INVENTORY;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  EFI_GUID                  Guid;      // GUID for the variable
  UINT16                    VarId;     // variable store ID, as referenced elsewhere in the form
  UINT16                    Size;      // size of the variable storage
//UINT8						VarName[]  // ASCII representation of VarName		
} EFI_IFR_VARSTORE;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    VarId;     // variable store ID, as referenced elsewhere in the form
} EFI_IFR_VARSTORE_SELECT;

//
// Used for the ideqid VFR statement where two variable stores may be referenced in the
// same VFR statement.
// A browser should treat this as an EFI_IFR_VARSTORE_SELECT statement and assume that all following
// IFR opcodes use the VarId as defined here.
//
typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    VarId;          // variable store ID, as referenced elsewhere in the form
  UINT16                    SecondaryVarId; // variable store ID, as referenced elsewhere in the form
} EFI_IFR_VARSTORE_SELECT_PAIR;

// Save defaults and restore defaults have same structure
#define EFI_IFR_RESTORE_DEFAULTS  EFI_IFR_SAVE_DEFAULTS

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  STRING_REF                Title;        // The string token for the banner title
  UINT16                    LineNumber;   // 1-based line number
  UINT8                     Alignment;    // left, center, or right-aligned
} EFI_IFR_BANNER;

typedef struct {
  EFI_IFR_OP_HEADER         Header;
  UINT16                    QuestionId;   // Offset into the map
  UINT8                     StorageWidth; // Width of the value
  CHAR8                     Data[1];      // The Data itself
} EFI_IFR_NV_DATA;



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma pack(pop) //must be 1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

typedef EFI_STATUS (EFIAPI *EFI_HII_NEW_PACK_OLD)(
	IN  EFI_HII_PROTOCOL		*This,
	IN  EFI_HII_PACK_LIST		*Package,
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
//IN  EFI_HII_PACKAGES	  	*Packages,
//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO//TODO
	OUT EFI_HII_HANDLE			*Handle );

typedef EFI_STATUS (EFIAPI *EFI_HII_NEW_PACK)(
	IN  EFI_HII_PROTOCOL    	*This,
	IN  EFI_HII_PACKAGES    	*Packages,
  	OUT EFI_HII_HANDLE    		*Handle );

typedef EFI_STATUS (EFIAPI *EFI_HII_REMOVE_PACK) (
	IN EFI_HII_PROTOCOL			*This,
	IN EFI_HII_HANDLE			Handle );

typedef EFI_STATUS (EFIAPI *EFI_HII_FIND_HANDLES) (
	IN     EFI_HII_PROTOCOL		*This,
	IN OUT UINT16				*HandleBufferLength,
	OUT    EFI_HII_HANDLE		*Handle );

typedef EFI_STATUS (EFIAPI *EFI_HII_EXPORT) (
	IN     EFI_HII_PROTOCOL		*This,
	IN     EFI_HII_HANDLE		Handle,
	IN OUT UINTN				*BufferSize,
	OUT    VOID					*Buffer );

//Not in Spec and do we need it????
typedef EFI_STATUS (EFIAPI *EFI_HII_RESET_STRINGS) (
	IN     EFI_HII_PROTOCOL		*This,
	IN     EFI_HII_HANDLE		Handle);

typedef EFI_STATUS (EFIAPI *EFI_HII_TEST_STRING) (
	IN     EFI_HII_PROTOCOL		*This,
	IN     CHAR16				*StringToTest,
	IN OUT UINT32				*FirstMissing,
	OUT    UINT32				*GlyphBufferSize );

typedef EFI_STATUS (EFIAPI *EFI_HII_GET_GLYPH) (
	IN     EFI_HII_PROTOCOL		*This,
	IN     CHAR16				*Source,
	IN OUT UINT16				*Index,
	OUT    UINT8				**GlyphBuffer,
	OUT    UINT16				*BitWidth,
	IN OUT UINT32				*InternalStatus );

typedef EFI_STATUS (EFIAPI *EFI_HII_GLYPH_TO_BLT) (
	IN     EFI_HII_PROTOCOL		*This,
	IN     UINT8				*GlyphBuffer,
	IN     EFI_UGA_PIXEL		Foreground,
	IN     EFI_UGA_PIXEL		Background,
	IN     UINTN				Count,
	IN     UINTN				Width,
	IN     UINTN				Height,
	IN OUT EFI_UGA_PIXEL		*BltBuffer);

typedef EFI_STATUS (EFIAPI *EFI_HII_NEW_STRING) (
	IN     EFI_HII_PROTOCOL     *This,
	IN     CHAR16               *Language,
	IN     EFI_HII_HANDLE       Handle,
	IN OUT STRING_REF           *Reference,
	IN     CHAR16               *NewString );

typedef EFI_STATUS (EFIAPI *EFI_HII_GET_PRI_LANGUAGES) (
	IN  EFI_HII_PROTOCOL		*This,
	IN  EFI_HII_HANDLE			Handle,
	OUT EFI_STRING				*LanguageString);

typedef EFI_STATUS (EFIAPI *EFI_HII_GET_SEC_LANGUAGES) (
	IN  EFI_HII_PROTOCOL		*This,
	IN  EFI_HII_HANDLE			Handle,
	IN  CHAR16					*PrimaryLanguage,
	OUT EFI_STRING				*LanguageString );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_STRING_OLD) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     STRING_REF        Token,
  IN     BOOLEAN           Raw,
  IN     CHAR16            *LanguageString,
  IN OUT UINT16            *BufferLength,
  OUT    EFI_STRING        StringBuffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_STRING_NEW) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     STRING_REF        Token,
  IN     BOOLEAN           Raw,
  IN     CHAR16            *LanguageString,
  IN OUT UINTN             *BufferLength, //0.92 Spec Update
  OUT    EFI_STRING        StringBuffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_LINE) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     STRING_REF        Token,
  IN OUT UINT16            *Index,
  IN     UINT16            LineWidth,
  IN     CHAR16           *LanguageString,
  IN OUT UINT16            *BufferLength,
  OUT    EFI_STRING        StringBuffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_FORMS_OLD) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     EFI_FORM_ID      FormId,
  IN OUT UINT16            *BufferLength,
  OUT    UINT8            *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_FORMS_NEW) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     EFI_FORM_ID      FormId,
  IN OUT UINTN            *BufferLength,
  OUT    UINT8            *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_DEFAULT_IMAGE_OLD) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     UINTN             DefaultMask,
  IN OUT UINT16            *BufferLength,
  OUT    UINT8             *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_HII_GET_DEFAULT_IMAGE_NEW) (
  IN     EFI_HII_PROTOCOL  *This,
  IN     EFI_HII_HANDLE    Handle,
  IN     UINTN             DefaultMask,
  OUT    EFI_HII_VARIABLE_PACK_LIST **VariablePackList
  );


typedef
EFI_STATUS
(EFIAPI *EFI_HII_UPDATE_FORM) (
  IN EFI_HII_PROTOCOL     *This,
  IN EFI_HII_HANDLE       Handle,
  IN EFI_FORM_LABEL       Label,
  IN BOOLEAN              AddData,
  IN EFI_HII_UPDATE_DATA  *Data
  );

typedef EFI_STATUS (EFIAPI *EFI_HII_GET_KEYBOARD_LAYOUT)(
	IN     EFI_HII_PROTOCOL    *This,
	OUT    UINT16              *DescriptorCount,
	OUT    EFI_KEY_DESCRIPTOR  *Descriptor);


typedef struct _EFI_HII_PROTOCOL_OLD {
  EFI_HII_NEW_PACK_OLD          NewPack;		//part kb data is missing
  EFI_HII_REMOVE_PACK           RemovePack;		//ok
  EFI_HII_FIND_HANDLES          FindHandles;	//ok
  EFI_HII_EXPORT                ExportDatabase;	//ok

  EFI_HII_TEST_STRING           TestString;		//ok
  EFI_HII_GET_GLYPH             GetGlyph;		//ok
  EFI_HII_GLYPH_TO_BLT          GlyphToBlt;		//ok

  EFI_HII_NEW_STRING            NewString;		//ok
  EFI_HII_GET_PRI_LANGUAGES     GetPrimaryLanguages;//ok
  EFI_HII_GET_SEC_LANGUAGES     GetSecondaryLanguages;//ok
  EFI_HII_GET_STRING_OLD        GetString;		//ok
  EFI_HII_RESET_STRINGS         ResetStrings;	//ok
  EFI_HII_GET_LINE              GetLine;		//ok
  EFI_HII_GET_FORMS_OLD         GetForms;		//ok
  EFI_HII_GET_DEFAULT_IMAGE_OLD GetDefaultImage;//
  EFI_HII_UPDATE_FORM           UpdateForm;

  EFI_HII_GET_KEYBOARD_LAYOUT   GetKeyboardLayout;
} EFI_HII_PROTOCOL_OLD;

typedef struct _EFI_HII_PROTOCOL {
  EFI_HII_NEW_PACK              NewPack;		//part kb data is missing
  EFI_HII_REMOVE_PACK           RemovePack;		//ok
  EFI_HII_FIND_HANDLES          FindHandles;	//ok
  EFI_HII_EXPORT                ExportDatabase;	//ok

  EFI_HII_TEST_STRING           TestString;		//ok
  EFI_HII_GET_GLYPH             GetGlyph;		//ok
  EFI_HII_GLYPH_TO_BLT          GlyphToBlt;		//ok

  EFI_HII_NEW_STRING            NewString;		//ok
  EFI_HII_GET_PRI_LANGUAGES     GetPrimaryLanguages;//ok
  EFI_HII_GET_SEC_LANGUAGES     GetSecondaryLanguages;//ok
  EFI_HII_GET_STRING_NEW        GetString;		//ok
  EFI_HII_RESET_STRINGS         ResetStrings;	//ok
  EFI_HII_GET_LINE              GetLine;		//ok
  EFI_HII_GET_FORMS_NEW         GetForms;		//ok
  EFI_HII_GET_DEFAULT_IMAGE_NEW GetDefaultImage;//ok
  EFI_HII_UPDATE_FORM           UpdateForm;

  EFI_HII_GET_KEYBOARD_LAYOUT   GetKeyboardLayout;
} EFI_HII_PROTOCOL;

#endif // #if EFI_SPECIFICATION_VERSION>0x20000
/****** DO NOT WRITE BELOW THIS LINE *******/
#endif // #ifndef GUID_VARIABLE_DEFINITION
#ifdef __cplusplus
}
#endif

#endif

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
