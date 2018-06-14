//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Library/Tokens.c 2     9/17/13 10:18p Thomaschen $
//
// $Revision: 2 $
//
// $Date: 9/17/13 10:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Library/Tokens.c $
// 
// 2     9/17/13 10:18p Thomaschen
// Update for PS2CTL module which labeled 4.6.5_PS2CTL_003.
// 
// 1     6/04/13 1:50a Thomaschen
// Fixed for EIP118202.
// 
// 23    11/01/12 6:40a Deepthins
// [TAG]  		EIP101100 
// [Category]  	Improvement
// [Description]  	Multi Language is supported in Ps2ctl driver
// [Files]  		CORE_DXE.sdl, kbc.h, ps2kbd.c and Tokens.c
// 
// 22    5/24/12 3:22p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Graphics console tokens moved from BdsBoard.c to
// tokens.c
// [Files]  		BdsBoard.c Tokens.c
// 
// 21    4/20/12 2:28p Artems
// [TAG]  		EIP87678
// [Category]  	New Feature
// [Description]  	Selection of image to boot from on flash update boot
// path - either old image (currently in flash) or new one in recovery
// capsule
// [Files]  		Recovery.c
// DxeIpl.c
// Core.sdl
// Tokens.c
// 
// 20    2/01/12 1:57a Deepthins
// [TAG]  		EIP63116
// [Category]  	New Feature
// [Description]  	PS/2 Keyboard/Mouse IRQ mode generic support
// [Files]  		Token.c, Ps2main.c, Ps2kbd.c, Mouse.c, kbc.h, kbc.c,
// CORE_DXE.sdl
// 
// 19    4/27/11 4:47a Lavanyap
// [TAG] - EIP49407
// [Category] - IMPROVEMENT
// [Description] - Move the Ps2 driver SDL tokens from Core Source to Core
// Bin,So that we don't need to add Core source for changing the Ps2
// driver SDL tokens.
// [Files] - Ps2Ctl.sdl, ps2kbd.c, ps2main.c, ps2ctl.h, kbc.c, mouse.c,
// hotkey.c, CORE_DXE.sdl, Tokens.c
// 
// 18    1/25/11 12:50p Oleksiyy
// [TAG]  		EIP42253 
// [Category]  	New Feature
// [Description]  	Added support for platforms, where flash part is not
// memory mapped while write enabled, controlled by
// NO_MMIO_FLASH_ACCESS_DURING_UPDATE sdl token. Flash protocol used to
// access flash in that case.
// [Files]  		NVRAMDXE.c, Flash.c, Tokens.c and Runtime.sdl
// 
// 17    9/02/10 3:36p Felixp
// Enhancement(EIP 39460): Runtime Garbage Collection Support.
// NvramRtGarbageCollectionSupport variable is added.
// 
// 16    8/23/10 3:29p Felixp
// Enhancement(EIP 29307): HideComPort variable is added. Part of Runtime
// Trace support.
// 
// 15    8/20/10 12:48p Felixp
// LZMA compression support: GetDecompressInterface function is added.
// 
// 14    11/25/09 1:30p Felixp
// 
// 13    11/25/09 1:24p Felixp
// 
// 12    11/25/09 1:22p Felixp
// TraceLevelMask constant is added
// 
// 11    11/24/09 11:31a Felixp
// DefaultLanguageCode constant is added.
// 
// 10    8/25/09 4:12p Felixp
// NvramChecksumSupport constant is added.
// 
// 9     7/10/09 9:21a Felixp
// Headers updated
// 
// 8     7/10/09 8:54a Felixp
// New NVRAM_MONOTONIC_COUNTER_SUPPORT SDL token is created. 
// The token can be used to disable Core NVRAM-based implementation of the
// monotonic counter
// architectural protocol and to use stand alone monotonic counter driver
// instead.
// 
// 7     10/09/08 11:47a Felixp
// NvramBackupAddress variable added
// 
// 6     8/31/07 9:36a Felixp
// NVRAM code update related changes
// 
// 5     3/31/07 1:45p Felixp
// Bug fix: NvramEnd was improperly defined. It caused NVRAM overflaw
// (NVRAM garbage collection never happened).
// 
// 4     12/20/06 1:48p Felixp
// FlashBlockSize type changed from UINTN to UINT32
// 
// 2     7/22/05 2:20a Felixp
//  NVRAM enclosed into Firmware volume
// 
// 1     6/16/05 10:40a Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	Tokens.c
//
// Description:	
//    This file contains constants and variables corresponding to some of the SDL tokens.
//    The constants and variables are used by modules that are distributed in binary 
//    and cannot directly consume token.h
//
//<AMI_FHDR_END>
//**********************************************************************
#include <FFS.h>
#include <AmiLib.h>
#include <token.h>

// Constants
const char *sAmiRomFile = CONVERT_TO_STRING(AMI_ROM);

const UINTN FlashSize = FLASH_SIZE;
const UINT32 FlashBlockSize = FLASH_BLOCK_SIZE;
const UINT32 FlashRetries = FLASH_RETRIES;
const UINTN FlashEmpty = (UINTN)(-FLASH_ERASE_POLARITY);
const UINT32 FlashEmptyNext = (FLASH_ERASE_POLARITY ? 0xffffff : 0);
const UINTN NvramAddress = NVRAM_ADDRESS;
#if FAULT_TOLERANT_NVRAM_UPDATE
const UINTN NvramBackupAddress = NVRAM_BACKUP_ADDRESS;
#else
const UINTN NvramBackupAddress = 0;
#endif
#if RUNTIME_TRACE_SUPPORT
const BOOLEAN HideComPort = TRUE;
#else
const BOOLEAN HideComPort = FALSE;
#endif
const UINTN NvramSize = NVRAM_SIZE;
const BOOLEAN NvSimulation = NV_SIMULATION;
const UINT32 NvramHeaderLength = NVRAM_HEADER_SIZE;
const BOOLEAN NvramMonotonicCounterSupport = NVRAM_MONOTONIC_COUNTER_SUPPORT;
const BOOLEAN NvramChecksumSupport = NVRAM_RECORD_CHECKSUM_SUPPORT;

#ifdef DEFAULT_LANGUAGE_CODE
const char *DefaultLanguageCode = CONVERT_TO_STRING(DEFAULT_LANGUAGE_CODE);
#endif
const UINT32 TraceLevelMask = TRACE_LEVEL_MASK;

// Variables
#define FLASH_DEVICE_BASE_ADDRESS (0xFFFFFFFF-FLASH_SIZE+1)
UINTN FlashDeviceBase = FLASH_DEVICE_BASE_ADDRESS;
UINTN FwhFeatureSpaceBase = FLASH_DEVICE_BASE_ADDRESS & ~(UINTN)0x400000;

#if NVRAM_RT_GARBAGE_COLLECTION_SUPPORT
const BOOLEAN NvramRtGarbageCollectionSupport = NVRAM_RT_GARBAGE_COLLECTION_SUPPORT;
#else
const BOOLEAN NvramRtGarbageCollectionSupport = 0;
#endif
#if NO_MMIO_FLASH_ACCESS_DURING_UPDATE
const BOOLEAN FlashNotMemoryMapped = NO_MMIO_FLASH_ACCESS_DURING_UPDATE;
#else
const BOOLEAN FlashNotMemoryMapped = 0;
#endif

#ifdef USE_RECOVERY_IMAGE_ON_FLASH_UPDATE
const BOOLEAN UseNewImage = USE_RECOVERY_IMAGE_ON_FLASH_UPDATE;
#else
const BOOLEAN UseNewImage = TRUE;
#endif

typedef struct _TEXT_MODE  {
	INT32	ModeNum;
	INT32	Col;
	INT32	Row;
	UINT32	VideoCol; // horizontal pixels
	UINT32	VideoRow; // vertical pixels
} TEXT_MODE;

const TEXT_MODE TextModeArray[] = {GC_MODE_LIST};
const INT32 MaxTextMode=(sizeof(TextModeArray)/sizeof(TEXT_MODE));


//Ps2Ctl driver global variables

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    KbdIrqSupport
//
// Description:	Variable to replace KB_IRQ_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN KbdIrqSupport = 
#ifdef KB_IRQ_SUPPORT
    KB_IRQ_SUPPORT
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    MsIrqSupport
//
// Description:	Variable to replace MS_IRQ_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN MsIrqSupport = 
#ifdef MS_IRQ_SUPPORT
    MS_IRQ_SUPPORT
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    Ps2MouseSupport
//
// Description:	Variable to replace PS2MOUSE_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN Ps2MouseSupport = 
#ifdef PS2MOUSE_SUPPORT
    PS2MOUSE_SUPPORT
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    Ps2KbdSupport
//
// Description:	Variable to replace PS2KBD_SUPPORT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN Ps2KbdSupport = 
#ifdef PS2KBD_SUPPORT
PS2KBD_SUPPORT
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    KbRdBeforeInstall
//
// Description:	Variable to replace KBD_READ_BEFORE_INSTALL token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN KbRdBeforeInstall = 
#ifdef KBD_READ_BEFORE_INSTALL
    KBD_READ_BEFORE_INSTALL
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    KbcAutoDetectPorts
//
// Description:	Variable to replace KBC_AUTODETECT_PORTS token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN KbcAutoDetectPorts = 
#ifdef KBC_AUTODETECT_PORTS
KBC_AUTODETECT_PORTS
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    BlockKbcPin2223Bit
//
// Description:	Variable to replace BLOCK_KBC_PIN_22_23_BIT token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN BlockKbcPin2223Bit = 
#ifdef BLOCK_KBC_PIN_22_23_BIT
BLOCK_KBC_PIN_22_23_BIT
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    LedsAtStartup
//
// Description:	Variable to replace LEDS_AT_STARTUP token.
//
// Notes: UINT8
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINT8 LedsAtStartup = 
#ifdef LEDS_AT_STARTUP
LEDS_AT_STARTUP
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    MaxHotKeys
//
// Description:	Variable to replace MAX_HOTKEYS token.
//
// Notes: UINT8
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINT8 MaxHotKeys = 
#ifdef MAX_HOTKEYS
MAX_HOTKEYS
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    InitDefaultHotKeys
//
// Description:	Variable to replace INIT_DEFAULT_HOTKEYS token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN InitDefaultHotKeys = 
#ifdef INIT_DEFAULT_HOTKEYS
INIT_DEFAULT_HOTKEYS
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    KbcBasicAssuranceTest
//
// Description:	Variable to replace KBC_BASIC_ASSURANCE_TEST token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN KbcBasicAssuranceTest = 
#ifdef KBC_BASIC_ASSURANCE_TEST
KBC_BASIC_ASSURANCE_TEST
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DetectPs2KeyboardValue
//
// Description:	Variable to replace DETECT_PS2_KEYBOARD token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN DetectPs2KeyboardValue = 
#ifdef DETECT_PS2_KEYBOARD
DETECT_PS2_KEYBOARD
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    DetectPs2MouseValue
//
// Description:	Variable to replace DETECT_PS2_MOUSE token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN DetectPs2MouseValue = 
#ifdef DETECT_PS2_MOUSE
DETECT_PS2_MOUSE
#else
    0
#endif
    ;
//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    InstallKeyboardMouseAlways
//
// Description:	Variable to replace INSTALL_KEYBOARD_MOUSE_ALWAYS token.
//
// Notes: BOOLEAN
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
BOOLEAN InstallKeyboardMouseAlways = 
#ifdef INSTALL_KEYBOARD_MOUSE_ALWAYS
INSTALL_KEYBOARD_MOUSE_ALWAYS
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    IbFreeTimeoutValue
//
// Description:	Variable to replace IBFREE_TIMEOUT token.
//
// Notes: UINT32
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINT32 IbFreeTimeoutValue = 
#ifdef IBFREE_TIMEOUT
IBFREE_TIMEOUT
#else
    0
#endif
    ;

//<AMI_SHDR_START>
//----------------------------------------------------------------------------
// Name:    IbMaxFreeTimeoutValue
//
// Description:	Variable to replace MAXIMUM_TIMEOUT_FOR_IBFREE token.
//
// Notes: UINT32
//
//----------------------------------------------------------------------------
//<AMI_SHDR_END>
UINT32 IbFreeMaxTimeoutValue = 
#ifdef MAXIMUM_TIMEOUT_FOR_IBFREE
MAXIMUM_TIMEOUT_FOR_IBFREE
#else
    0
#endif
    ;

//Decompression
BOOLEAN GetDecompressInterface(
    UINT8 CompressionType, GET_INFO *GetInfoPtr, DECOMPRESS *DecompressPtr
)
{
    if (CompressionType==EFI_STANDARD_COMPRESSION){
        *GetInfoPtr=GetInfo;
        *DecompressPtr=Decompress;
        return TRUE;
    }
#if LZMA_SUPPORT==1
    else if (CompressionType==EFI_CUSTOMIZED_COMPRESSION){
        *GetInfoPtr=LzmaGetInfo;
        *DecompressPtr=LzmaDecompress;
        return TRUE;
    }
#endif
    return FALSE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
