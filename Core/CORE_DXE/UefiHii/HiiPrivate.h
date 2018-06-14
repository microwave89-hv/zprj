//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/UefiHii/HiiPrivate.h 2     9/18/13 1:41a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 9/18/13 1:41a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/CORE_DXE/UefiHii/HiiPrivate.h $
// 
// 2     9/18/13 1:41a Thomaschen
// Update for EIP126176.
// 
// 16    5/02/13 1:48p Artems
// [TAG]  		EIP113105
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Wording for proportional font display was vague. After
// clarification
// code logic was slightly changed
// [Files]  		HiiFontEx.c HiiPrivate.h
// 
// 14    2/25/13 4:45p Artems
// [TAG]  		EIP101673
// [Category]  	New Feature
// [Description]  	Add support for AMI custom large fixed font
// [Files]  		HiiDatabase.c HiiFontEx.c HiiPrivate.h UefiHiiUtils.c GC.c
// new LargeFont Core modulePart
// 
// 13    8/15/12 3:36p Artems
// [TAG]  		EIP96755
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Strings in new language added at runtime lost during export
// [RootCause]  	Every language represented by its own string package.
// When 
// strings of new language added at runtime, they're added to database,
// but not to the list of packages. Export function is working with 
// list of packages, so new language strings will be missed
// [Solution]  	Added code to create new string package at runtime when
// new string
// of new language is added to database
// [Files]  		HiiPrivate.h HiiString.c
// 
// 12    5/22/12 4:16p Artems
// [TAG]  		EIP83593
// [Category]  	New Feature
// [Description]  	Proportional font support for Aptio
// [Files]  		HiiDatabase.c HiiFont.c HiiFontEx.c HiiPrivate.h HiiString.c
// UefiHii.h
// 
// 11    1/05/12 5:05p Artems
// EIP 76735: Font FFS file is not loaded in framework mode, when in
// nested FV
// 
// 10    5/13/11 6:14p Artems
// Renamed functions HiiGetString and HiiSetString to AmiHiiGetString and
// AmiHiiSetString 
// to avoid collusion with EdkII native library functions
// 
// 9     5/13/11 5:17p Artems
// Function CompareGuid (native EdkII) renamed to HiiCompareGuid to avoid
// collusion
// 
// 8     5/05/11 4:14p Artems
// Add signal "layout changed" event if current layout is deleted
// 
// 7     1/05/11 12:41p Artems
// EIP 50995: Added checking of driver handle before adding packages to
// HII database
// 
// 6     11/05/10 5:17p Artems
// EIP 46880: Fixed bug, where two functions referred to the same global
// pointer
// 
// 5     9/30/10 6:11p Artems
// EIP 44657 Added GetAltConfig functionality
// 
// 4     1/29/10 5:43p Artems
// EIP 34553 Updated function ExportPackageLists to support NULL pointer
// as input
// 
// 3     12/04/09 11:16a Artems
// Remove keyboard layout functionality added
// 
// 2     12/03/09 6:04p Artems
// SCT bug fix
// 
// 1     10/09/09 6:12p Felixp
// 
// 1     2/27/09 3:55p Artems
// Initial check-in
// 
// 1     3/18/07 5:23p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	HiiPrivate.h
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __HII_PRIVATE__H__
#define __HII_PRIVATE__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <AmiDxeLib.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>
#include <Protocol/HiiFont.h>
#include <Protocol/HiiConfigRouting.h>

#define NULL_GUID \
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

#define PACKAGE_LIST_RECORD_SIGNATURE 0x53524c80	//"PLRS"
#define NOTIFY_LIST_RECORD_SIGNATURE  0x53524c4e	//"NLRS"

#define DEFAULT_FONT_HANDLE 0xDEADF000
#define AMI_HII_PACKAGE_FONTS   0xE1

#pragma pack (push,1)

typedef struct _PACKAGE_LIST_RECORD {
    DLINK		 Link;
	UINT32		 Signature;
	EFI_GUID	 Guid;
    EFI_HANDLE	 DriverHandle;
	DLIST		 PackageList;
	DLIST		 LanguageList;
	DLIST		 StringFontList;
	DBE_DATABASE StringDb;
} PACKAGE_LIST_RECORD;

typedef struct _NOTIFY_RECORD {
	DLINK						 Link;
	UINT32						 Signature;
    UINT8                        PackageType;
    EFI_GUID                     PackageGuid;
    EFI_HII_DATABASE_NOTIFY      PackageNotifyFn;
    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType;
} NOTIFY_RECORD;

typedef struct _HII_DATABASE_PRIVATE_DATA {
    EFI_HII_DATABASE_PROTOCOL   DatabaseProtocol;
    EFI_HII_STRING_PROTOCOL     StringProtocol;
    EFI_HII_FONT_PROTOCOL       FontProtocol;
    EFI_HII_CONFIG_ROUTING_PROTOCOL ConfigRoutingProtocol;
	DLIST						PackList;
	DLIST						NotifyList;
	DLIST						KeyLayoutList;
    DLIST                       FontList;
	EFI_HII_KEYBOARD_LAYOUT		*CurrentLayout;
} HII_DATABASE_PRIVATE_DATA;

typedef struct _PACKAGE_LINK {
	DLINK					Link;
	EFI_HII_PACKAGE_HEADER  Package;
} PACKAGE_LINK;

typedef struct _KEY_LAYOUT_LINK {
	DLINK					Link;
	EFI_HII_KEYBOARD_LAYOUT Layout;
} KEY_LAYOUT_LINK;

typedef struct _SIMPLE_FONT {
	EFI_NARROW_GLYPH *NarrowGlyph;
	EFI_WIDE_GLYPH	 *WideGlyph;
} SIMPLE_FONT;

typedef struct _FONT_LINK {
	DLINK   Link;
    EFI_HII_FONT_PACKAGE_HDR *FontPackage;
    UINTN FontHeight;
    UINTN FontBaseLine;
	DLIST   Glyphs;
} FONT_LINK;

typedef struct _STRING_FONT_LINK {
	DLINK Link;
    UINT16 FontId;
    UINT32 FontInfoSize;
//	EFI_FONT_INFO FontInfo;
} STRING_FONT_LINK;

typedef struct _GLYPH_LINK {
	DLINK   Link;
    CHAR16  Char;
    EFI_HII_GLYPH_INFO Cell;
    UINT8 *GlyphBlock;
} GLYPH_LINK;

typedef struct _LANGUAGE_LINK {
	DLINK		  Link;
	UINT16		  LastStringId;
	CHAR8		  Language[1];
} LANGUAGE_LINK;

typedef struct _STRING_RECORD {
	UINT16		StringId;    
	UINT16		LanguageId;
	UINT16		FontId;
	CHAR16      String[1];
} STRING_RECORD;

typedef struct _DRAW_LINE {
	DLINK		Link;
	UINTN		StartIndex;
	UINTN		EndIndex;
	UINTN		LineHeight;
	UINTN		LineWidth;
	UINTN		BaseLineOffset;
} DRAW_LINE;

typedef struct _NAME_PATTERN
{
    UINTN Length;
    CHAR16 *Tag;
} NAME_PATTERN;

typedef struct {
    CHAR16 *ResultString;
    UINTN  MaxResultStringSize;
    UINTN  CurrentSize;
} RESULT_BLOCK;

#define MATCH_INGNORE 0
#define MATCH_STRICT  1
#define MATCH_LOOSE   2

typedef struct {
    UINT32 MatchName  : 1;
    UINT32 MatchSize  : 2;
    UINT32 MatchStyle : 2;
    UINT32 Reserved   : 1;
} FONT_MATCH_MASK;

typedef struct {
    UINTN x;
    UINTN y;
} POINT_COORD;

typedef struct {
    POINT_COORD *st;
    POINT_COORD *size;
} RECT_COORD;

typedef struct {
    EFI_HII_PACKAGE_HEADER Header;
    UINT16 NumberOfNarrowGlyphs;
    UINT8 Height;
    UINT8 Width;
//    EFI_NARROW_GLYPH NarrowGlyphs[]; //based on height and width given
} AMICUSTOM_SIMPLE_FONT_PACKAGE_HDR;

#pragma pack (pop)

//************ Database Protocol functions definition **************************

EFI_STATUS HiiNewPack (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList,
    IN CONST EFI_HANDLE                     DriverHandle,
    OUT EFI_HII_HANDLE                      *Handle
);

EFI_STATUS HiiRemovePack (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle
);

EFI_STATUS HiiUpdatePack (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle,
    IN CONST EFI_HII_PACKAGE_LIST_HEADER    *PackageList
);

EFI_STATUS HiiListPacks (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN UINT8                                PackageType,
    IN CONST EFI_GUID                       *PackageGuid,
    IN OUT UINTN                            *HandleBufferLength,
    OUT EFI_HII_HANDLE                      *Handle
);

EFI_STATUS HiiExportPacks (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HII_HANDLE                       Handle,
    IN OUT UINTN                            *BufferSize,
    OUT EFI_HII_PACKAGE_LIST_HEADER         *Buffer
);

EFI_STATUS HiiRegisterNotify (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN UINT8                                PackageType,
    IN CONST EFI_GUID                       *PackageGuid,
    IN CONST EFI_HII_DATABASE_NOTIFY        PackageNotifyFn,
    IN EFI_HII_DATABASE_NOTIFY_TYPE         NotifyType,
    OUT EFI_HANDLE                          *NotifyHandle
);

EFI_STATUS HiiUnregisterNotify (
    IN CONST EFI_HII_DATABASE_PROTOCOL      *This,
    IN EFI_HANDLE                           NotificationHandle
);

EFI_STATUS HiiFindKeyboardLayouts (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN OUT UINT16                           *KeyGuidBufferLength,
    OUT EFI_GUID                            *KeyGuidBuffer
);

EFI_STATUS HiiGetKeyboardLayout (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN EFI_GUID                             *KeyGuid,
    IN OUT UINT16                           *KeyGuidBufferLength,
    OUT EFI_HII_KEYBOARD_LAYOUT             *KeyboardLayout
);

EFI_STATUS HiiSetKeyboardLayout (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN EFI_GUID                             *KeyGuid
);

EFI_STATUS HiiGetPackageListHandle (
    IN EFI_HII_DATABASE_PROTOCOL            *This,
    IN EFI_HII_HANDLE                       PackageListHandle,
    OUT EFI_HANDLE                          *DriverHandle
);

//************************* String protocol functions definition **********

EFI_STATUS HiiNewString (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	OUT EFI_STRING_ID				 *StringId,
	IN CONST CHAR8					 *Language,
	IN CONST CHAR16					 *LanguageName OPTIONAL,
	IN CONST EFI_STRING				 String,
	IN CONST EFI_FONT_INFO			 *StringFontInfo
);

EFI_STATUS AmiHiiGetString(
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN CONST CHAR8					 *Language,
	IN EFI_HII_HANDLE				 PackageList,
	IN EFI_STRING_ID				 StringId,
	OUT EFI_STRING					 String,
	IN OUT UINTN					 *StringSize,
	OUT EFI_FONT_INFO				 **StringFontInfo OPTIONAL
);

EFI_STATUS AmiHiiSetString (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN EFI_STRING_ID				 StringId,
	IN CONST CHAR8					 *Language,
	IN CONST EFI_STRING				 String,
	IN CONST EFI_FONT_INFO			 *StringFontInfo OPTIONAL
);

EFI_STATUS HiiGetLanguages (
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN OUT CHAR8					 *Languages,
	IN OUT UINTN					 *LanguagesSize
);

EFI_STATUS HiiGetSecondLanguages(
	IN CONST EFI_HII_STRING_PROTOCOL *This,
	IN EFI_HII_HANDLE				 PackageList,
	IN CONST CHAR8*					 FirstLanguage,
	IN OUT CHAR8					 *SecondLanguages,
	IN OUT UINTN					 *SecondLanguagesSize
);

//************************* Font protocol functions definition ****************

EFI_STATUS HiiStringToImage(
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN EFI_HII_OUT_FLAGS			Flags,
	IN CONST EFI_STRING				String,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo OPTIONAL,
	IN OUT EFI_IMAGE_OUTPUT			**Blt,
	IN UINTN						BltX,
	IN UINTN						BltY,
	OUT EFI_HII_ROW_INFO			**RowInfoArray OPTIONAL,
	OUT UINTN						*RowInfoArraySize OPTIONAL,
	OUT UINTN						*ColumnInfoArray OPTIONAL
);

EFI_STATUS HiiStringIdToImage (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN EFI_HII_OUT_FLAGS			Flags,
	IN EFI_HII_HANDLE				PackageList,
	IN EFI_STRING_ID				StringId,
	IN CONST CHAR8*					Language,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo OPTIONAL,
	IN OUT EFI_IMAGE_OUTPUT			**Blt,
	IN UINTN						BltX,
	IN UINTN						BltY,
	OUT EFI_HII_ROW_INFO			**RowInfoArray OPTIONAL,
	OUT UINTN						*RowInfoArraySize OPTIONAL,
	OUT UINTN						*ColumnInfoArray OPTIONAL
);

EFI_STATUS HiiGetGlyph (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN CHAR16						Char,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfo,
	OUT EFI_IMAGE_OUTPUT			**Blt,
	OUT UINTN						*Baseline OPTIONAL
);

EFI_STATUS HiiGetFontInfo (
	IN CONST EFI_HII_FONT_PROTOCOL	*This,
	IN OUT EFI_FONT_HANDLE			*FontHandle,
	IN CONST EFI_FONT_DISPLAY_INFO	*StringInfoIn,
	OUT EFI_FONT_DISPLAY_INFO		**StringInfoOut,
	IN CONST EFI_STRING				String OPTIONAL
);

//************************* Config Routing protocol functions definition ******

EFI_STATUS HiiExtractConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING Request,
    OUT EFI_STRING      *Progress,
    OUT EFI_STRING      *Results
);

EFI_STATUS HiiExportConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    OUT EFI_STRING *Results
);

EFI_STATUS HiiRouteConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING Configuration,
    OUT EFI_STRING      *Progress
);

EFI_STATUS HiiBlockToConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigRequest,
    IN CONST UINT8      *Block,
    IN CONST UINTN      BlockSize,
    OUT EFI_STRING      *Config,
    OUT EFI_STRING      *Progress
);

EFI_STATUS HiiConfigToBlock (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigResp,
    IN OUT CONST UINT8 *Block,
    IN OUT UINTN *BlockSize,
    OUT EFI_STRING *Progress
);

EFI_STATUS HiiGetAltConfig (
    IN CONST EFI_HII_CONFIG_ROUTING_PROTOCOL *This,
    IN CONST EFI_STRING ConfigResp,
    IN CONST EFI_GUID   *Guid,
    IN CONST EFI_STRING Name,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN CONST EFI_STRING AltCfgId,
    OUT EFI_STRING      *AltCfgResp
);

//*************************Service functions (not for public use)**************

VOID InvokeRegisteredNotify (
    IN EFI_HII_PACKAGE_HEADER		*Package,
    IN EFI_HII_HANDLE               Handle,
    IN EFI_HII_DATABASE_NOTIFY_TYPE NotifyType
);

BOOLEAN FindAndRemovePackages (
    IN EFI_HII_HANDLE  Handle,
    IN UINT8           PackageType,
    IN CONST EFI_GUID  *PackageGuid,
	IN BOOLEAN		   FindOnly
);

VOID RemovePackage (
    IN EFI_HII_HANDLE Handle,
    IN PACKAGE_LINK   *Package
);

EFI_STATUS AddPackage(
    IN EFI_HII_HANDLE			 Handle,
	IN EFI_HII_PACKAGE_HEADER	 *Package,
	EFI_HII_DATABASE_NOTIFY_TYPE NotifyType
);

EFI_STATUS AddPackages(
    IN EFI_HII_HANDLE				Handle,
	IN EFI_HII_PACKAGE_LIST_HEADER *PackageList,
	BOOLEAN							Update
);

EFI_STATUS UpdateStringPackages(
    IN EFI_HII_HANDLE   Handle
);

UINTN GetStringBlockSize(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN CHAR8 *Language
);

VOID GetStringBlock(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN CHAR8 *Language,
    IN UINT8 *Buffer
);

BOOLEAN MatchPackage(
    IN UINT8                  PackageType,
    IN EFI_GUID               *PackageGuid,
    IN EFI_HII_PACKAGE_HEADER *Package
);

BOOLEAN CheckIfPresent(
	IN EFI_GUID *Guid,
	IN EFI_HANDLE DriverHandle
); 

EFI_HII_KEYBOARD_LAYOUT* FindLayoutByGuid(
	IN EFI_GUID *Guid
);

EFI_STATUS ParseKeyLayoutPackage(
	IN EFI_HII_KEYBOARD_PACKAGE_HDR *Package
);

EFI_STATUS DeleteKeyboardLayout(
	IN EFI_HII_KEYBOARD_PACKAGE_HDR *Package
);

EFI_STATUS ParseSimpleFontsPackage(
	IN EFI_HII_SIMPLE_FONT_PACKAGE_HDR *Package
);

EFI_STATUS ParseFontsPackage(
	IN EFI_HII_FONT_PACKAGE_HDR *Package
);

EFI_STATUS ParseStringsPackage(
   PACKAGE_LIST_RECORD			  *PackageList,
	IN EFI_HII_STRING_PACKAGE_HDR *Package
);

PACKAGE_LIST_RECORD* NewPackageListRecord(
	VOID
);

NOTIFY_RECORD* NewNotifyRecord(
	VOID
);

VOID* CreateNewLink(
	UINT32 Size
);

VOID DeleteList(
	DLIST *List
);

VOID DeleteStringsFromDatabase(DBE_DATABASE *Database);
VOID DeleteSimpleFonts(IN EFI_HII_SIMPLE_FONT_PACKAGE_HDR *Package);

UINT32 StrSize8(CHAR8 *String);

UINT32 StrSize16(CHAR16 *String);

VOID StrCpy8(CHAR8 *Dest, CHAR8 *Src);

VOID StrCpy16(CHAR16 *Dest, CHAR16 *Src);

INTN StrCmp8(CHAR8 *Dest, CHAR8 *Src);

INTN StrCmp16(CHAR16 *Dest, CHAR16 *Src);

EFI_STATUS AddLanguage(
   PACKAGE_LIST_RECORD *PackageList,
   CHAR8 *Language,
   CHAR16* LanguageName,
   UINT16 LastStringId
);

EFI_STATUS GetLanguageId(
   PACKAGE_LIST_RECORD *PackageList,
   CHAR8 *Language,
   UINT16 *LanguageId,
   LANGUAGE_LINK **Found
);

EFI_STATUS AddString(
	PACKAGE_LIST_RECORD *PackageList,
	UINT16		LanguageId,
	UINT16		StringId,
	UINT16		FontId,
	EFI_STRING  String
);

EFI_STATUS ExtractStrings(
	PACKAGE_LIST_RECORD *PackageList,
	UINT16		LanguageId,
	UINT16		*StringId,
	UINT16		FontId,
	UINT16		StringCount,
	BOOLEAN		Compressed,
	VOID		*StringBlock
);

BOOLEAN IsLineBreak(CHAR16 Char);

BOOLEAN IsLineBreakOpp(CHAR16 Char);

UINTN GetGlyphWidth(CHAR16 Char);

UINTN GetLineLength(UINTN StartIndex, UINTN EndIndex);

UINTN GetClipLineLength(
	UINTN StartIndex, 
	UINTN MaxLength, 
	BOOLEAN ClipClean, 
	UINTN *EndIndex
);

UINTN GetWrapIndex(
	UINTN StartIndex, 
	UINTN MaxLength, 
	UINTN *EndIndex, 
	UINTN *StartIndex2
);

UINTN GetMaxLineLength(VOID);

EFI_STATUS SplitByLineBreaks(EFI_STRING String);

EFI_STATUS AdjustLineSize(VOID);

VOID DrawNarrowGlyph(
	UINTN StartX, 
	UINTN StartY, 
	UINTN SizeX, 
	UINTN SizeY, 
	CHAR16 Char, 
	BOOLEAN Transparent, 
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt
);

VOID DrawWideGlyph(
	UINTN StartX, 
	UINTN StartY, 
	UINTN SizeX, 
	UINTN SizeY, 
	CHAR16 Char, 
	BOOLEAN Transparent, 
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt
);

VOID Draw(VOID);

BOOLEAN CheckPattern(CHAR16 *String, NAME_PATTERN *Pattern);

EFI_STATUS ExtractConfigString(CHAR16 *String, UINTN *NextIndex, CHAR16 **NewString);

BOOLEAN CheckDevicePath(
    IN UINT8 *DevicePath, 
    IN UINTN DeviceLength, 
    IN EFI_HII_PACKAGE_HEADER *Package);

EFI_STATUS SearchDevicePath(UINT8 *DevicePach, UINTN DpLength, EFI_HANDLE *Handle);

EFI_STATUS ExtractDevicePath(CHAR16 *ConfigString, UINT8 **DevicePath, UINTN *DpLength);

EFI_STATUS FindDeviceHandle(
    IN CHAR16 *ConfigString,
    OUT EFI_HANDLE *Handle);

BOOLEAN IsHexDigit(CHAR16 Char);
UINT8 HexValue(CHAR8 Char);

VOID StringToBlock(
    IN CHAR16 *String,
    IN UINTN StringSize,
    OUT UINT8 *Block);

EFI_STATUS CollectResults(CHAR16 *Result, UINTN Symbols, RESULT_BLOCK *ResultBlock);

UINT32 GetValue(CHAR16 *String, UINTN Start, UINTN End);

EFI_STATUS GetPatternValue(
    CHAR16 *String, 
    UINTN *Index, 
    NAME_PATTERN *Pattern, 
    UINT32 *Value);

EFI_STATUS GetStringValue(
    CHAR16 *String,
    UINTN  *Index,
    UINT8  *Output,
    UINT32 Width);

EFI_STATUS ReallocResultString(UINTN NewSize, RESULT_BLOCK *ResultBlock);

EFI_STATUS CollectValueResults(UINT8 *Value, UINT32 Width, RESULT_BLOCK *ResultBlock);

EFI_STATUS InitResultBlock(RESULT_BLOCK *ResultBlock);

VOID WriteSwappedBuffer(
    OUT UINT8 *Output,
    IN  UINT8 *Input,
    IN  UINTN Size);

EFI_STATUS LoadSystemFont();

EFI_STATUS ExportPack(
    IN EFI_HII_HANDLE                Handle,
    IN OUT UINTN                    *BufferSize,
    OUT EFI_HII_PACKAGE_LIST_HEADER *Buffer,
    IN BOOLEAN                      FirstCall
);

VOID StringToChar16(
    IN CHAR16 *String,
    IN OUT UINTN  *Size,
    OUT CHAR16 *Block
);

BOOLEAN CompareDevicePath(
    IN EFI_STRING ConfigString,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

BOOLEAN CompareName(
    IN EFI_STRING ConfigString,
    IN CONST EFI_STRING  Name
);

BOOLEAN HiiCompareGuid(
    IN EFI_STRING ConfigString,
    IN CONST EFI_GUID   *Guid
);

EFI_STATUS CheckAltCfg (
    IN EFI_STRING ConfigString,
    IN CONST EFI_GUID   *Guid,
    IN CONST EFI_STRING Name,
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN CONST EFI_STRING AltCfgId
);

EFI_STATUS SignalKbLayoutChangedEvent(
    VOID
);

EFI_STATUS FillFontInfo(
    IN EFI_FONT_HANDLE FontHandle,
    OUT EFI_FONT_DISPLAY_INFO **StringInfoOut
);

EFI_STATUS FindFont(
    IN OUT EFI_FONT_HANDLE *FontHandle,
    IN CHAR16 *FontName,
    IN EFI_HII_FONT_STYLE FontStyle,
    IN UINT16 FontSize,
    IN FONT_MATCH_MASK Mask,
    IN CONST EFI_STRING	String
);

EFI_STATUS IntGetGlyph(
    IN EFI_FONT_HANDLE Font, 
    IN CHAR16 Char, 
    OUT EFI_HII_GLYPH_INFO *Cell, 
    OUT UINT8 **GlyphBlock OPTIONAL,
    OUT BOOLEAN *Free
);

VOID UpdateLineSize(
    IN OUT DRAW_LINE *Line
);

VOID ClipLine(
    IN OUT DRAW_LINE *Line,
    IN UINTN Width,
    IN BOOLEAN ClipClean
);

BOOLEAN CheckVisible(
    IN OUT RECT_COORD *Glyph, 
    IN RECT_COORD *Image
);

VOID DrawGlyph(
    IN UINTN StartX,
    IN UINTN StartY,
    IN UINTN SizeX,
    IN UINTN SizeY,
    IN UINT8 *GlyphBlock,
    IN BOOLEAN Transparent,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt,
    IN UINT16 CharWidth
);

VOID GetDrawImageSize(
    OUT UINTN *Width,
    OUT UINTN *Height
);

EFI_STATUS WrapLine(
    IN OUT DRAW_LINE *Line,
    IN UINTN Width
);

EFI_STATUS AddStringFont(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN UINT16 FontId,
    IN UINT16 FontSize,
    IN EFI_HII_FONT_STYLE FontStyle,
    IN CHAR16 *FontName,
    OUT UINT16 *NewFontId OPTIONAL
);

UINT16 GetAvailableFontId(
    IN PACKAGE_LIST_RECORD *PackageList
);

EFI_STATUS FindStringFontInfoByTemplate(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN EFI_FONT_INFO *Template,
    OUT UINT16 *FontId
);

EFI_STATUS FindStingFontInfoById(
    IN PACKAGE_LIST_RECORD *PackageList,
    IN UINT16 FontId,
    OUT EFI_FONT_INFO **Info
);

VOID CreateLanguageName(
    IN CHAR8 *RfcName, 
    OUT CHAR16* OutName, 
    UINTN MaxSize
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************