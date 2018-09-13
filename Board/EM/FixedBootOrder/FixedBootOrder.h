//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*****************************************************************//
// $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrder.h $
//
// $Author: Dukeyeh $
//
// $Revision: 11 $
//
// $Date: 9/09/14 3:36a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrder.h $
// 
// 11    9/09/14 3:36a Dukeyeh
// [TAG]  		EIP171752 
// [Category]  	Improvement
// [Description]  	Add FIXED_BOOT_ORDER_SUBMENU_MAX_NUM and
// FIXED_BOOT_ORDER_GROUP_MAX_NUM tokens to decide maximum number of
// submenus and groups at boot time.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// 
// Board\em\FixedBootOrder\FixedBootOrderHII.h
// FixedBootOrder.cif
// 
// 10    8/13/14 11:19p Walonli
// [TAG]  		EIP180632
// [Category]  	New Feature
// [Description]  	Add FixedBootOrder Protocol to change device/group
// name.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// FixedBootOrder.cif
// 
// 9     5/20/14 3:48a Klzhan
// [TAG]  		EIP167196
// [Category]  	Improvement
// [Description]  	Runtime attribute set for the some of the variable used
// by FixedBootOrder needs to be reviewed.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FixedBootOrder.mak
// Board\em\FixedBootOrder\FBOSetOrder.c
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// Board\em\FixedBootOrder\FixedBootOrder.chm
// Board\em\FixedBootOrder\FixedBootOrderHII.c
// Board\em\FixedBootOrder\FixedBootOrderHII.h
// FixedBootOrder.cif
// 
// 8     4/15/14 2:26a Klzhan
// [TAG]  		EIP143078
// [Category]  	Improvement
// [Description]  	Set LOAD_OPTION_ACTIVE must be 0 when
// LOAD_OPTION_HIDDEN=1
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.sdl
// Board\em\FixedBootOrder\FixedBootOrder.mak
// Board\em\FixedBootOrder\FBOSetOrder.c
// Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// Board\em\FixedBootOrder\FixedBootOrder.chm
// Board\em\FixedBootOrder\FixedBootOrderHII.c
// Board\em\FixedBootOrder\FixedBootOrderHII.h
// FixedBootOrder.cif
// 
// 7     5/31/13 1:46a Easonchen
// EIP123284
// Set Boot Priority unicode string 
// 
// 6     10/04/12 2:15a Easonchen
// [TAG]  		EIP96232
// [Category]  	Improvement
// [Description]  	Support USB Floppy in UEFI mode
// 
// 5     6/28/12 11:22a Easonchen
// Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
// functionality. 
// 
// 2     12/06/28 11:04p Readwrite
// 
// 2     12/06/28 10:41p Readwrite
// 
// 4     4/14/11 4:00a Easonchen
// [TAG]  	EIP35562
// [Category]  	Improvement
// [Description]  	In Core 4.6.4.1 or Last, Fixed boot variable name - hex
// digits should be in upper case
// 
// 
// 3     11/12/10 3:46a Easonchen
// n           TAG: EIP22689
// TAG: EIP22689
// Improvement: Support submenu function.
// 
// 2     9/14/10 2:41a Easonchen
// 
// 1     4/15/09 3:35a Jameswang
// 
//*****************************************************************//

//<AMI_FHDR_START>
//**********************************************************************
//
// Name:        FixedBootOrder.h
//
// Description: Header file of FixedBootOrder module
//
//**********************************************************************
//<AMI_FHDR_END>


#ifndef _FIXED_BOOT_ORDER_H
#define _FIXED_BOOT_ORDER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef VFRCOMPILE

#define FIXED_BOOT_ORDER_GUID \
    {0xc923ca9, 0xdf73, 0x4ac8, 0xb6, 0xd2, 0x98, 0xdd, 0xc3, 0xd, 0x99, 0xfc}

#define FIXED_BOOT_ORDER_SETUP_GUID \
    {0x7e07911a, 0x4807, 0x4b0f, 0xa4, 0x74, 0xf5, 0x43, 0x1c, 0xa9, 0x07, 0xb4}	

#define DEFAULTS_GUID  \
  {0x4599d26f, 0x1a11, 0x49b8, 0xb9, 0x1f, 0x85, 0x87, 0x45, 0xcf, 0xf8, 0x24}

#define DEFAULT_LEGACY_DEV_ORDER_VARIABLE_GUID  \
  { 0x3c4ead08, 0x45ae, 0x4315, 0x8d, 0x15, 0xa6, 0x0e, 0xaa, 0x8c, 0xaf, 0x69 }

#define VARIABLE_ATTRIBUTES \
	(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)

#define BS_NV_VARIABLE_ATTRIBUTES \
	(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)

#pragma pack(1)

typedef struct _FBODevMap {
	UINT16 DevType;
	UINT16 BBSType;
	UINT16 Port;
	UINT8 Attr;
}FBODevMap;

typedef struct _FBOHiiMap {
	UINT16 DevType;
	UINT16 StrToken;
	UINT16 FormID;
	UINT16 Label;
	UINT16 DeviceCountOffset;
}FBOHiiMap;

typedef struct{
	UINT32 Type;
	UINT16 Length;
	UINT16 StrToken[1]; 
}HII_DEVICE_INFO;

typedef struct{
	UINT32 Type;
	UINT16 Length;
	UINT16 Device[1]; 
}UEFI_DEVICE_ORDER;

typedef struct _FBO_DEVICE_INFORM {
    CHAR16 *DevName;
    UINT16 DevType ;
    UINT16 DevPortNum ;
    UINT32 DevBDF ;
    EFI_DEVICE_PATH_PROTOCOL *DevPath;
    struct _FBO_DEVICE_INFORM *Next ;
} FBO_DEVICE_INFORM ;

typedef struct _FBO_GROUP_OPTION {
    UINT16 StrToken;
    CHAR16 *OrgGroupName ;
    CHAR16 *NewGroupName ;
    struct _FBO_GROUP_OPTION *Next ;
} FBO_GROUP_OPTION ;

#pragma pack()
//FBO Attr
//#define TYPES_ALWAYS_PRESENT 0x01
#define F_USB 		0x02
#define F_USBKEY 	0x04

#define FixedBootOrderStratKey	0x1000
#define LegacyBootItemKey	FixedBootOrderStratKey
#define UefiBootItemKey		(FixedBootOrderStratKey+0x80)
#define DualBootItemKey		(FixedBootOrderStratKey+0x100)
#define LegacyForms_StartKey	(FixedBootOrderStratKey+0x200)
#define UefiForms_StartKey	(FixedBootOrderStratKey+0x800)

#if CORE_COMBINED_VERSION > 0x40280	//4.6.4.1 or Last
#define gBootName L"Boot%04X"
#else
#define gBootName L"Boot%04x"
#endif

// Calculate the number of orders in this group (DevOrder->Type)
#define DEVORDER_COUNT(DevOrder) (DevOrder->Length - sizeof(DevOrder->Length)) / sizeof(DevOrder->Device)

#define FBO_LEGACY_DISABLED_MASK    0xff00      // LegacyDevOrder disabled flag mask
#define FBO_LEGACY_ORDER_MASK       0x00ff      // LegacyDevOrder valid BBS index mask
#define FBO_UEFI_DISABLED_MASK      0xff000000  // UefiDevOrder disabled flag mask
#define FBO_UEFI_ORDER_MASK         0x0000ffff  // UefiDevOrde valid Boot number mask

typedef EFI_STATUS (EFIAPI *LOAD_DEFAULT_STRING)();

typedef struct _EFI_FIXED_BOOT_ORDER_SETUP_PROTOCOL {
	LOAD_DEFAULT_STRING load_default_string;
} EFI_FIXED_BOOT_ORDER_SETUP_PROTOCOL;


typedef EFI_STATUS (EFIAPI *FBOSetDevMap)(IN FBODevMap *p);
typedef EFI_STATUS (EFIAPI *FBOSetHiiMap)(IN FBOHiiMap *p);
typedef FBODevMap *(EFIAPI *FBOGetDevMap)(IN VOID);
typedef FBOHiiMap *(EFIAPI *FBOGetHiiMap)(IN VOID);
typedef EFI_STATUS (EFIAPI *FBOSetBootOptionTokenMap)(IN UINT16 *p);    //(EIP123284+)
typedef UINT16 *(EFIAPI *FBOGetBootOptionTokenMap)(IN VOID);            //(EIP123284+)
typedef EFI_STATUS (EFIAPI *FBOSetNewDescription)(IN FBO_DEVICE_INFORM *p);
typedef FBO_DEVICE_INFORM* (EFIAPI *FBOGetNewDescription)(IN VOID);


typedef struct _EFI_FIXED_BOOT_ORDER_PROTOCOL {
	FBOSetDevMap SetLegacyDevMap;
	FBOSetDevMap SetUefiDevMap;
	FBOSetDevMap SetDualDevMap;	
	FBOSetHiiMap SetHiiMap;
    FBOSetBootOptionTokenMap SetBootOptionTokenMap;                     //(EIP123284+)
    FBOSetNewDescription SetNewDescription;
	FBOGetDevMap GetLegacyDevMap;
	FBOGetDevMap GetUefiDevMap;
	FBOGetDevMap GetDualDevMap;
	FBOGetHiiMap GetHiiMap;
    FBOGetBootOptionTokenMap GetBootOptionTokenMap;                     //(EIP123284+)
    FBOGetNewDescription GetNewDescription ;
} EFI_FIXED_BOOT_ORDER_PROTOCOL;


#endif	//#ifndef VFRCOMPILE

//This structure is used for setup.
typedef struct {
	UINT8	LegacyDevice[FIXED_BOOT_ORDER_TOTAL_DEVICES_MAX_NUM];	//groups * submenu device.
	UINT8	UefiDevice[FIXED_BOOT_ORDER_TOTAL_DEVICES_MAX_NUM];	//groups * submenu device.
} FIXED_BOOT_SETUP;

//This structure is used for FixedBootOrder Group control.
typedef struct {
	UINT8	LegacyHDD;
	UINT8	LegacyODD;
	UINT8	LegacyNET;
	UINT8	LegacyUSBHDD;
	UINT8	LegacyUSBODD;
	UINT8	LegacyUSBFDD;
	UINT8	LegacyUSBKEY;
	UINT8	UefiHDD;
	UINT8	UefiODD;
	UINT8	UefiNET;
	UINT8	UefiUSBHDD;
	UINT8	UefiUSBODD;
	UINT8	UefiUSBKEY;
	UINT8   UefiUSBFDD;		//(EIP96232+)
} FIXED_BOOT_GROUP;

#ifdef __cplusplus
}
#endif


#endif  //#ifndef _FIXED_BOOT_ORDER_H

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************


