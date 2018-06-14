//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/PTT/FastBoot.h 11    7/17/13 3:01a Simonchen $
//
// $Revision: 11 $
//
// $Date: 7/17/13 3:01a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBoot.h $
// 
// 11    7/17/13 3:01a Simonchen
// [TAG]  		EIP125309
// [Category]  	New Feature
// [Description]  	Add function to make sure before boot to OS, BIOS is in
// fastboot path.
// [Files]  		FastBoot.sdl
// FastBootTseHook.c
// FastBoot.c
// FastBoot.h
// 
// 10    7/11/13 10:23p Simonchen
// [TAG]  		EIP126196
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	If set two HDD password and use Raid mode, fastboot will
// fail
// [RootCause]  	Because when AHCI driver unlock first HDD, Raid driver
// will try to read all HDD, but second HDD is still lock, so access will
// fail.
// [Solution]  	Make sure all HDD unlock then Raid can access HDD. 
// And add "Support Raid Driver" token to control fastboot support Raid
// feature or not.
// [Files]  		FastBoot.c
// FastBoot.sd
// FastBoot.sdl
// FastBootRuntime.c
// FastBoot.h
// 
// 9     4/18/13 5:37a Simonchen
// [TAG]  		EIP113454
// [Category]  	New Feature
// [Description]  	This eip is created for implement or experiment for
// Intel raid mode on fastboot.
// [Files]  		FastBoot.h
// 
// 8     8/07/12 4:43a Bibbyyeh
// [TAG]           EIP97545
// [Category]      Improvement
// [Description]   Updated PTT Module to Implement Support for
// Initializing the Keyboard in First Call of Readkeystroke on Fastboot.
// [Files]         FastBoot.c FastBoot.h FastBootProtocol.h
// 
// 7     6/27/12 4:23a Bibbyyeh
// [TAG]           EIP93038
// [Category]      New Feature
// [Description]   Ability to customize fast boot boot option selection
// [Files]         FastBoot.c FastBoot.h FastBoot.sdl
// 
// 6     6/01/12 6:35a Bibbyyeh
// [TAG]           EIP90455
// [Category]      New Feature
// [Description]   PTT improvement - fastboot policy protocol for dynamic
// control fast boot behavior.
// [Files]         FastBoot.c FastBoot.sdl FastBoot.sd FastBoot.uni
// FastBootRuntime.c FastBootTseHook.c FastBootProtocol.h FastBoot.h
// 
// 5     4/10/12 8:53a Bibbyyeh
// [TAG]           EIP87452
// [Category]      Improvement
// [Description]   1. Create an elink "ReturnNormalMode", OEM/ODM can link
// their procedure to handle the fastboot failure case. 2. Disconnect USB
// controller when return to normal mode.
// [Files]         FastBoot.c FastBoot.h FastBoot.mak FastBoot.sdl
// 
// 4     7/07/11 10:10a Bibbyyeh
// [TAG]           EIP63924
// [Category]      Improvement
// [Description]   
// 1. Add elink for FastBoot mode change, default checking rule is check
// post hotkey.
// 2. Timer call back for check hotkey is not necessary. Create a protocol
// for calling checkforkey in TSE.
// 3. Since EIP68383 improve the performance of ps2 keyboard, we don't
// need to exchange the initial order of ConIn/ConOut for getting more
// time to detect hotkey.
// [Files]         FastBoot.sdl FastBoot.mak FastBoot.c FastBootTseHook.c
// FastBoot.h FastBootProtocol.h
// 
// 3     3/11/11 10:01p Bibbyyeh
// [TAG]		EIP54993
// [Category]	Improvement
// [Description]
// 1.Sync with Fastboot_10
// 2.Remove token "SAVE_LAST_BOOT_DEVICE_CHECKSUM"
// 3.Add token "CALL_DISPATCHER_AGAIN_IN_FASTBOOT"
// 4.Use SimpleText protocol to detect mode change hotkey instead of
// pBS->ConIn.
// 5.Simplify the code about "AMILEGACY16_FASTBOOT_SOLUTION".
// 6.Fixed a bug that SATA device can't be found if keep TSE execution on
// fastboot path.
// [Files]		PPT.cif FastBoot.sdl FastBootRuntime.c FastBootTseHook.c
// FastBoot.c FastBoot.h FastBoot.sd FastBootProtocol.cif
// FastBootProtocol.h FastBootSMI.cif FastBootSMI.sdl FastBootSMI.c
// FastBootSMI.dxs FastBootSMI.mak
// 
// 2     11/17/10 9:44a Bibbyyeh
// [TAG]  		EIP47397
// [Category]  	Improvement
// [Description]  	1. Move all console related functions into PTT module
// to avoid uncompatible with different core version.
// 2. Install dumy SimpleTextCoin protocol when pBS->ConIn & pBS-ConOut is
// Null.
// 3. Raise timer call back as TPL_HIGH_LEVEL level, it will give BIOS
// more chance to mode change successfully.
// 4. Remove FASTBOOT_CONSOLE_SETTING token.Add setup option for fastboot
// setting, "Skip VGA", "Skip USB", Skip "PS2".
// [Files]  		FastBoot.c
// FastBoot.h
// FastBoot.sd
// FastBoot.sdl
// FastBoot.uni
// 
// 1     10/12/10 9:04a Bibbyyeh
// Initial check in
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBoot.h
//
//  Description:
//  Fast boot functions definitions
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __FASTBOOT__H__
#define __FASTBOOT__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol/DevicePath.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextOut.h>
#include <HOB.h>
#include <token.h>


#define FAST_BOOT_TYPE_EFI         0x00000001    //last boot was from UEFI device
#define FAST_BOOT_TYPE_LEGACY      0x00000000    //last boot was from Legacy device

#if FASTBOOT_NEED_RESTART
#define FAST_BOOT_RESTART L"FastbootRestart" 
#define FAST_BOOT_RESTART_COUNT L"FastbootRestartCount"

//{39ac7cb1-789c-45f6-94f0-68873c5c1ff2}
#define FAST_BOOT_RESTART_COUNT_GUID \
    { 0x39ac7cb1, 0x789c, 0x45f6, 0x94, 0xf0, 0x68, 0x87, 0x3c, 0x5c, 0x1f, 0xf2 }

//{800dabd7-ca8d-4611-bd77-3b200ebc275a}
#define FAST_BOOT_RESTART_GUID \
    { 0x800dabd7, 0xca8d, 0x4611, 0xbd, 0x77, 0x3b, 0x20, 0x0e, 0xbc, 0x27, 0x5a }
#endif

// {B540A530-6978-4da7-91CB-7207D764D262}
#define FAST_BOOT_VARIABLE_GUID \
    { 0xb540a530, 0x6978, 0x4da7, 0x91, 0xcb, 0x72, 0x7, 0xd7, 0x64, 0xd2, 0x62 }

GUID_VARIABLE_DECLARATION(FastBootVariableGuid, FAST_BOOT_VARIABLE_GUID);

// {50535FFD-1555-4329-A2C5-F3F44011A449}
#define AMI_SATA_PRESENT_HOB_GUID \
	{0x50535ffd, 0x1555, 0x4329, 0xa2, 0xc5, 0xf3, 0xf4, 0x40, 0x11, 0xa4, 0x49}


#pragma	pack(1)
typedef struct _SATA_INFO {
    UINT16              ClassCode;      //Base class and Sub class code
    UINT32              PresentPortBitMap;    //Upper word is BDF, Lower word is port bitmap
                                              /* Bit map description    
                                                IDE Mode:
                                                Bit0: Primary Master
                                                Bit1: Secondary Master
                                                Bit2: Primary Slave
                                                Bit3: Secondary Slave
                                                
                                                AHCI or RAID mode:
                                                Bit0: Port0
                                                Bit1: Port1
                                                Bit2: Port2
                                                Bit3: Port3
                                                Bit4: Port4
                                                Bit5: Port5
                                              */      
} SATA_INFO;

#if SUPPORT_RAID_DRIVER
typedef struct _SATA_PRESENT_HOB {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;
    UINT8               ControllerCount;
    SATA_INFO           SataInfo[4];
} SATA_PRESENT_HOB;
#endif

#if SUPPORT_RAID_DRIVER
typedef struct _SATA_DEVICE_DATA{ 
    UINT16  BDF;
    UINT16  ClassCode;
    UINT8   DevType;
    UINT8   PortNum; //IDE MODE: bit0:channel, bit1:device
	UINT8	SerialNum[20];
} SATA_DEVICE_DATA;
#endif

typedef struct _FAST_BOOT {
    UINT32 BootOptionNumber : 16;
    UINT32 BootType         : 2;
    UINT32 Reserved         : 14;
    UINT32 BootCount;
    UINT16 DevStrCheckSum; 
//SATA device information
#if SUPPORT_RAID_DRIVER
    SATA_DEVICE_DATA    SataDevice[MAX_SATA_DEVICE_COUNT] ;
#endif
//SATA controller information   
    UINT8  ControllerCount;
    SATA_INFO SataInfo[4];
} FAST_BOOT;
#pragma	pack()

//FastBoot.c
EFI_STATUS DummyInReset( 
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,	
	IN BOOLEAN                        EV 
);          

EFI_STATUS DummyReadKeyStroke(
	IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT	EFI_INPUT_KEY                  *Key 
);



EFI_STATUS  DummyReset(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN                         EV
);

EFI_STATUS DummyOutputString(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16                          *String
);

EFI_STATUS  DummyTestString(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This,
	IN CHAR16 *String
);

EFI_STATUS DummyQueryMode(
	IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This,
	IN  UINTN                           ModeNum,
	OUT UINTN                           *Col,
	OUT UINTN                           *Row
);


EFI_STATUS DummySetMode(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           ModeNum
);


EFI_STATUS  DummySetAttribute(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Attribute
);

EFI_STATUS  DummyClearScreen(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This
);

EFI_STATUS DummySetCursorPosition(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Column,
	IN UINTN                           Row
);

EFI_STATUS  DummyEnableCursor(
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN Visible	
);



VOID FastBootWorker(
    VOID
);

VOID ResetFastBootVariable(
    VOID
);

BOOLEAN OemConfigurationChanged(
    VOID
);

EFI_STATUS CreateLegacyFastBootOption(
    FAST_BOOT *Var
);

EFI_STATUS CreateEfiFastBootOption(
    IN EFI_LOAD_OPTION *BootOption,
    IN UINTN           OptionSize,
    IN UINT16          OptionNumber
);

BOOLEAN IsSupportedDevice(
    IN  EFI_DEVICE_PATH_PROTOCOL *Dp,
    OUT BOOLEAN                  *UsbMassStorage,
    OUT BOOLEAN                  *HddFilePath
);

VOID FastBootClearBootFailFlag(
	IN EFI_EVENT Event, 
    IN VOID      *Context
);

BOOLEAN IsBootToShell(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp
);

VOID FastBootReadyToBootNotify(
	IN EFI_EVENT Event, 
    IN VOID      *Context
);

EFI_STATUS FastLegacyBoot(
    VOID
);

EFI_STATUS FastEfiBoot(
    VOID
);

EFI_STATUS CheckLoader(
    IN EFI_DEVICE_PATH_PROTOCOL *Dp
);

EFI_STATUS TseHandShake();
VOID ReturnToNormalBoot(
    VOID
);

BOOLEAN IsRuntime(
    VOID
);

VOID FbConnectInputDevices(
    VOID
);


//FastBootTseHook.c
										//(EIP63924+)>
EFI_STATUS FastBootCheckForKey( 		
    IN  BOOLEAN *EnterSetup,
    IN  UINT32  *BootFlow);

EFI_STATUS FastBootStopCheckForKeyTimer();

										//<(EIP63924+)
//Hook
typedef BOOLEAN (IS_VALID_FASTBOOT_BOOT_OPTION_FUNC_PTR)(
    IN  UINTN BootOrderIndex,
    IN  EFI_LOAD_OPTION *BootOption
);
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
