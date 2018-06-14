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
// $Header: /Alaska/SOURCE/Modules/PTT/FastBootProtocol.h 8     4/18/13 5:35a Simonchen $
//
// $Revision: 8 $
//
// $Date: 4/18/13 5:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/PTT/FastBootProtocol.h $
// 
// 8     4/18/13 5:35a Simonchen
// [TAG]  		EIP113454
// [Category]  	New Feature
// [Description]  	create for implement or experiment for Intel raid mode
// on fastboot.
// [Files]  		FastBootProtocol.h
// 
// 7     8/23/12 6:08a Bibbyyeh
// Add a flag "InFastBootPath" in FAST_BOOT_POLICY protocol.
// 
// 6     8/10/12 3:26a Bibbyyeh
// [TAG]           EIP96276
// [Category]      New Feature
// [Description]   Function request for PTT_12
// EIP96276.2 Fixed USB skip table issue. 
// EIP96276.3 Add token ¡¥CONNECT_ALL_SATA_DEVICE_IN_FASTBOOT¡¦ to
// gFastBootPolicy.
// EIP96276.4 Add IsValidFBBootOptionPtr support by driver type. Exp : usb
// type skip or other type
// EIP96276.5 Add token ¡¥Test mode¡¨ to gFastBootPolicy Setup menu.
// EIP96276.6 Disable Tse Hotkey support in fastboot path.
// EIP96276.7 Modify TRACE message.
// [Files]         FastBoot.c FastBoot.sd FastBoot.sdl FastBoot.uni
// FastBootRuntime.c FastBootProtocol.c
// 
// 5     8/07/12 4:42a Bibbyyeh
// [TAG]           EIP97545
// [Category]      Improvement
// [Description]   Updated PTT Module to Implement Support for
// Initializing the Keyboard in First Call of Readkeystroke on Fastboot.
// [Files]         FastBoot.c FastBoot.h FastBootProtocol.h
// 
// 4     6/01/12 6:51a Bibbyyeh
// [TAG]           EIP90455
// [Category]      New Feature
// [Description]   PTT improvement - fastboot policy protocol for dynamic
// control fast boot behavior.
// [Files]         FastBoot.c FastBoot.sdl FastBoot.sd FastBoot.uni
// FastBootRuntime.c FastBootTseHook.c FastBootProtocol.h FastBoot.h
// 
// 3     9/08/11 5:27a Bibbyyeh
// [TAG]           EIP68329
// [Category]      Bug Fix
// [Severity]      Important
// [Symptom]       OS can't back to desktop correctly after resumed from
// S3. 
// [RootCause]     TSEIDEPasswordFreezeDevices is skipped in fastboot path
// if SKIP_TSE_HANDSHAKE is enabled. 
// [Solution]      Call TSEIDEPasswordFreezeDevices after ReadyToBoot
// Event in fastboot path.
// [Files]         FastBoot.c FastBootProtocol.h FastBootTseHook.c
// 
// 2     7/07/11 10:11a Bibbyyeh
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
// 1     3/11/11 10:04p Bibbyyeh
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
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  FastBootProtocol.h
//
//  Description:
//  Fast boot protocol definitions
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef __FASTBOOT_PROTOCOL__H__
#define __FASTBOOT_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif
#pragma	pack(1)


// {3496A19A-2E99-41ba-833E-0FDE2EBF2A55}
#define AMI_FAST_BOOT_PROTOCOL_GUID \
   { 0x3496a19a, 0x2e99, 0x41ba, 0x83, 0x3e, 0xf, 0xde, 0x2e, 0xbf, 0x2a, 0x55 }

										//(EIP63924+)>
// {8fba43b8-acdb-4ee2-ab31-0fa4d5b6c3c5}
#define FAST_BOOT_TSE_PROTOCOL_GUID \
   { 0x0fba43b8, 0xacdb, 0x4ee2, 0xab, 0x31, 0x0f, 0xa4, 0xd5, 0xb6, 0xc3, 0xc5 }
										//<(EIP63924+)

#define FAST_BOOT_POLICY_PROTOCOL_GUID \
    { 0xb2a07be9, 0xc754, 0x4c36, 0x93, 0x02, 0x7c, 0xc7, 0x8a, 0xa0, 0xd8, 0x75 }
                                        
GUID_VARIABLE_DECLARATION(AmiFastBootProtocolGuid, AMI_FAST_BOOT_PROTOCOL_GUID);

typedef struct _SKIP_PCI_LIST{
	UINT8   Class;
    UINT8   SubClass;
} SKIP_PCI_LIST;

typedef struct _FAST_BOOT_POLICY {
    BOOLEAN                     FastBootEnable;
    BOOLEAN                     TestMode;
//pervious boot information    
    BOOLEAN                     UEfiBoot;    
    UINT16                      BootOptionNumber;
    UINT16                      DevStrCheckSum;
    EFI_DEVICE_PATH_PROTOCOL    *FastBootOption;   
    BOOLEAN                     LastBootFailure;
    BOOLEAN                     LastBootVarPresence;    
    UINT32                      BootCount;    
//previous boot sata information
    VOID                        *SataDevice;
//fast boot behavior para
    BOOLEAN                     FirstFastBootInS4;
    BOOLEAN                     CheckBootOptionNumber;
    BOOLEAN                     CheckDevStrCheckSum;
    UINT8                       SataSupport;     
    BOOLEAN                     VGASupport;
    UINT8                       UsbSupport; 
    VOID                        *UsbSkipTable;
    UINTN                       UsbSkipTableSize;    
    BOOLEAN                     Ps2Support;
    BOOLEAN                     NetWorkStackSupport;
    SKIP_PCI_LIST               *SkipPciList;
    UINTN                       SkipPciListSize;
    BOOLEAN                     CheckPassword;
    BOOLEAN                     SkipTSEHandshake;
//    BOOLEAN                     ConnectAllSata;     //(EIP96276.3)+
    BOOLEAN                     InFastBootPath;
} FAST_BOOT_POLICY;


typedef
EFI_STATUS
(EFIAPI *AMI_FAST_BOOT_LAUNCH) (
	VOID
	);

typedef
VOID
(EFIAPI *AMI_FAST_BOOT_CONNECT_INPUT_DEVICE) (
	VOID
	);

typedef
BOOLEAN
(EFIAPI *AMI_FAST_BOOT_IS_RUNTIME) (
	VOID
	);

typedef struct _AMI_FAST_BOOT_PROTOCOL
{
	AMI_FAST_BOOT_LAUNCH Launch;
    AMI_FAST_BOOT_CONNECT_INPUT_DEVICE ConnectInputDevices;
    AMI_FAST_BOOT_IS_RUNTIME IsRuntime;
}AMI_FAST_BOOT_PROTOCOL;


										//(EIP63924+)>
typedef
EFI_STATUS
(EFIAPI *FAST_BOOT_CHECK_FOR_KEY) (
    BOOLEAN *EnterSetup,
    UINT32  *BootFlow
	);
                                        
typedef
EFI_STATUS
(EFIAPI *FAST_BOOT_STOP_CHECK_FOR_KEY_TIMER)();

										//(EIP68329+)>
typedef
VOID
(EFIAPI *FAST_BOOT_PASSWORD_FREEZE_DEVICES)();
										//<(EIP68329+)
typedef struct _FAST_BOOT_TSE_PROTOCOL
{
    FAST_BOOT_CHECK_FOR_KEY FastBootCheckForKey;
    FAST_BOOT_STOP_CHECK_FOR_KEY_TIMER FastBootStopCheckForKeyTimer;
    FAST_BOOT_PASSWORD_FREEZE_DEVICES FastBootPasswordFreezeDevices; //(EIP68329+)
}
FAST_BOOT_TSE_PROTOCOL; 
										//<(EIP63924+)
#pragma	pack()									
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
