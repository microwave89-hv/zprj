//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrder.c $
//
// $Author: Dukeyeh $
//
// $Revision: 34 $
//
// $Date: 12/12/14 4:47a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrder.c $
// 
// 34    12/12/14 4:47a Dukeyeh
// [TAG]  		EIP176263
// [Category]  	Bug Fix
// [RootCause]  	The malfunction of GroupkeyProcess function that makes
// duplicated devices in BBS priority menu of Setup.
// [Solution]  	Update the comparision mechanism of GroupkeyProcess
// function.
// [Files]  		FixedBootOrder.c
// 
// 33    10/08/14 1:45a Dukeyeh
// [TAG]  		EIP184538
// [Category]  	Improvement
// [Description]  	FixedBootOrder changes the values of variables in
// StdDefaults variable and updates their checksum also if need be. 
// [Files]  		FixedBootOrder.c
// FixedBootOrder.mak
// 
// 32    9/22/14 2:58a Dukeyeh
// [TAG]  		EIP182196 
// [Category]  	Improvement
// [Description]  	In order to adapt with UEFI spec. and TSE policy,
// adding EFI_BROWSER_ACTION_DEFAULT_STANDARD action and returning
// EFI_UNSUPPORTED to load default. 
// [Files]  		FixedBootOrder.c
// 
// 31    9/09/14 3:36a Dukeyeh
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
// 30    8/21/14 9:38a Dukeyeh
// [TAG]  		EIP171752 
// [Category]  	Bug Fix
// [RootCause]  	Need 33 bytes to save a BBS name(32 + one terminator),
// not 32.
// [Solution]  	Allocate 33 bytes for saving a BBS name.
// [Files]  		FixedBootOrder.c
// 
// 29    8/14/14 2:32a Walonli
// [TAG]  		EIP180632
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Legacy device name show incorrect
// [RootCause]  	String format incorrect with legacy option.
// [Solution]  	Add Swprintf to covert string.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrder.c
// FixedBootOrder.cif
// 
// 28    8/13/14 11:19p Walonli
// [TAG]  		EIP180632
// [Category]  	New Feature
// [Description]  	Add FixedBootOrder Protocol to change device/group
// name.
// [Files]  		Board\em\FixedBootOrder\FixedBootOrderTSE.c
// Board\em\FixedBootOrder\FixedBootOrder.h
// Board\em\FixedBootOrder\FixedBootOrder.c
// FixedBootOrder.cif
// 
// 27    5/20/14 3:48a Klzhan
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
// 26    4/15/14 2:26a Klzhan
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
// 25    11/18/13 10:19p Klzhan
// [TAG]  		EIP137765
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Setup Item abnormal after remove USB KEY
// [RootCause]  	BBS information will be deleted after removing USB key.
// [Solution]  	Keep the Name string in a buffer
// 
// 24    8/12/13 4:19a Easonchen
// [TAG]  		N/A
// [Category]  	Improvement
// [Description]  	CppCheck error fix.
// [Files]  		FixedBootOrder.c
// 
// 23    5/31/13 1:45a Easonchen
// [TAG]  		EIP123284
// [Category]  	Improvement
// [Description]  	Set Boot Priority unicode string
// [Files]  		FixedBootOrder.c
// FixedBootOrder.h
// FixedBootOrder.sdl
// FixedBootOrderTSE.c
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 22    5/28/13 5:26a Easonchen
// [TAG]  		EIP122146
// [Category]  	Improvement
// [Description]  	Support Dual mode default priority with tool AMIBCP. 
// [Files]  		
// FboSetOrder.c
// FixedBootOrder.c
// FixedBoorOrderTse.c
// DefaultFixedBootOrder.c
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 21    4/19/13 2:47a Easonchen
// [TAG]  		EIP116436
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Fixed Boot Order doesn't work in Manufacturing mode
// [RootCause]  	LegacyPriorities[],UefiPriorities[] not initializes in
// Manufacturing mode
// [Solution]  	set variable MfgDefaults, initial
// LegacyPriorities[],UefiPriorities[] value.
// [Files]  		FixedBootOrder.c
// 
// 20    2/05/13 3:47a Easonchen
// [TAG]  		EIP107268
// [Category]  	Improvement
// [Description]  	Add support managing default boot order list using
// AMIBCP.
// [Files]  		
// FBOSetOrder.c
// FixedBootOrder.c
// FixedBootOrderTSE.c
// FixedBootOrder.sdl
// DefaultFixedBootOrder.sd
// DefaultFixedBootOrder.uni
// 
// 19    1/26/13 2:55a Easonchen
// [TAG]  		EIP112714
// [Category]  	Improvement
// [Description]  	Add include file elink
// [Files]  		
// FixedBootOrder.c
// FixedBootOrder.sdl
// FixedBootOrder.mak
// 
// 18    11/09/12 2:46a Easonchen
// [TAG]  		N/A
// [Category]  	Improvement
// [Description]  	1.Set Variable "StdDefaults"  LegacyPriorities[],
// UefiPriorities[] value
// 2.Add TOKEN function
// "INITIAL_LEGCAY_HII_ITEM_FUNCTION","INITIAL_UEFI_HII_ITEM_FUNCTION","IN
// ITIAL_LEGCAY_GROUP_FUNCTION","INITIAL_UEFI_GROUP_FUNCTION"
// [Files]  		FixedBootOrder.c
// 
// 17    11/02/12 4:23a Easonchen
// [TAG]  		EIP103171
// [Category]  	Improvement
// [Description]  	FixedBootOrder should not change setup.c after 4.6.5.4
// [Files]  		FixedBootOrder.c
// 
// 16    10/02/12 3:56a Easonchen
// [TAG]  		EIP101408
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	FxiedBootOrder for multi-language problem
// [RootCause]  	NewString don't support multi-language
// [Solution]  	Add SetString for multi-language
// [Files]  		FixedBootOrder.c
// 
// 15    6/28/12 11:22a Easonchen
// Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
// functionality. 
// 
// 14    6/11/12 10:04a Easonchen
// [TAG]  		EIP92141
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	build error with TSE 1227
// [RootCause]  	TSE EDKhelper.c change function name DivU64x32 to
// AmiTseDivU64x32.
// [Solution]  	Change to use function Div64
// [Files]  		FBOSetOrder.c
// 
// 12    5/02/12 2:49a Easonchen
// [TAG]  		EIP87316
// [Category]  	Improvement
// [Description]  	 FixedBootOrder Module needs support CsmOptOut Boot
// Filter UEFI Only. Set BBS Table BootPriority to BBS_IGNORE_ENTRY.
// [Files]  		FBOSetOrder.c
// 
// 11    6/17/11 3:44a Easonchen
// [TAG]  		EIP57950
// [Category]  	Improvement
// [Description]  	
// Replace BBS_TABLE BootPriority BBS_UNPRIORITIZED_ENTRY to
// BBS_DO_NOT_BOOT_FROM.
// 
// 10    4/14/11 4:01a Easonchen
// TAG: EIP35562
// In Core 4.6.4.1 or Last, Fixed boot variable name - hex digits should
// be in upper case
// 
// TAG: EIP54209
// Improvement: NetBootHotKey eModule Functionality with TSE 1210
// Verification Check
// [Description] 
// Check TSE gBootFlow status in function FBOCheckNormalBoot
// 
// TAG: EIP57727
// Improvement: It always increase one device while reboot in F12 (Boot
// device menu) even you only insert one HDD in it.
// [Description] 
// Modify function UpdateBootOrder() and AddUEFIDevice() to support
// 4.6.4.1
// 
// 9     3/31/11 2:03a Easonchen
// [TAG]  		EIP57272
// [Category]  	Improvement
// [Description]  	Check BootMode BOOT_ON_S4_RESUME and exit
// [Files]  		FBOSetOrder.c
// 
// 8     3/22/11 4:35a Easonchen
// [TAG]  		EIP51709
// [Category]  	Improvement
// [Description]  	1.Code is reformatted in accordance with the coding
// standards.
// 2.Remove file boot.vfr and setup.c, OEM need patch boot.vfr to remove
// original boot options.
// 
// 7     12/10/10 4:41a Easonchen
// Minor bug fix (EIP47257.2)
// 
// 6     11/12/10 2:57a Easonchen
// Add TSE ELINK ProcessProceedToBootNowHook.
// 
// TAG: EIP33514
// Improvement: The FixedBootOrder function caused the side effect
// -"AMT_TC010( IDE-Redirection).
// [Description] 
// Check variable "AmtBootOption" created, OemFixedBootOrder() don't
// change BBS_TABE Boot priority.
// 
// TAG: EIP47257
// Improvement: Load Default user define HDD order will lost.
// [Description] 
// Modified routine BbsChecksum(), If can't get hard disk serial number.
// use device name to make checksum.
// 
// 5     9/14/10 3:04a Easonchen
// TAG: EIP33514
// Improvement: Modify function FixedBootOrderSaveChange().
// [Description] 
// 1.Change BOOT#### LoadOption Bit Active status.
// 2.Update variable BootOrder after SaveChange.
// TAG: EIP33900
// Improvement: add function FixedBootOrderLoadedConfigDefaults() for TSE
// ELINK LoadedConfigDefaults().
// [Description]
// 1.Add function CreateDefaultDevOrder().
// 2.Call FixedBootOrderProtocol->load_default_string().
// TAG: EIP30275
// Improvement: Windows Boot Manager delete and restore.
// [Description]
// 1.Add function WindowsBootManager().
// TAG: EIP26947
// Improvement: Update variable "BootOrder" and "LegacyDevOrder"
// [Description]
// 1.Add function UpdateBootOrder().
// TAG: EIP22689
// Improvement: Support submenu function.
// 
// 4     3/31/10 6:54a Jameswang
// [Tag] EIP35944
// [Bug fix] Fixed USB CDROM will be analyzed as USB key with some CD
// medium(HD format)
// [Severity] Medium
// [Root cause] We only checked the USB device size to determined if it is
// a USB key, if USB CDROM has a medium that is emulated as a HDD / Floppy
// between 2MB and 64GB then it will also be determined as USB key.
// [Solution] Not only checks the size but also checks BBS types for HDD
// and Floppy, excludes CDROM.
// 
// 3     4/15/09 6:12a Jameswang
// TAG: EIP19998
// Improvement: New type:BOOT_USB_KEY is added and boot option can display
// the device name.
// [Description]
// 1. Added BOOT_USB_KEY type: 64GB > USB KEY!=USB floppy >= 2MB
// 2. SetPriorityForStringInit is added for pre-running the boot order for
// each boot options, so the FixedBootOrderStringInit can add device names
// to strings accordingly.
// 3. When FixedBootOrderStringInit signaling a protocol event,
// SetPriorityForStringInit::SetPriorityForStringInit will be called and
// gInitStrPhase=TRUE, the BBS_TABLE[].BootPriority = BOOT_XXXX enum value
// if the device is present.
// 4. FBORegisterEvent is linked to MinisetupDriverEntryHook and register
// a fake protocol so FixedBootOrderStringInit can signal it and callback
// to SetPriorityForStringInit accross the EDK.
// 
// 2     3/26/09 2:46a Jameswang
// All include use <> only without any path.  So that include files can be
// override by CIF2MAK "/x" option.
// All debug message add "\n".
// 
// 1     3/02/09 3:31a Jameswang
// Separate OemFixedBootOrder here to be linked with minisetup because we
// changed to use eLinks instead of using events.  We will not need to
// modify bbs.c using eLinks.
// 
//*****************************************************************//

//<AMI_FHDR_START>
//**********************************************************************
//
// Name:        FixedBootOrder.c
//
// Description: This file is linked to Setup Binary for form callback
//
//**********************************************************************
//<AMI_FHDR_END>

#include <token.h>
#include <efi.h>
#include <AmiDxeLib.h>
#include <setup.h>

#if CSM_SUPPORT
#include <Protocol/LegacyBios.h>
#endif

#if EFI_SPECIFICATION_VERSION>0x20000
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiString.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/HiiConfigRouting.h>
#ifdef DEFAULT_LANGUAGE_CODE
const char *DefaultLanguageCode = CONVERT_TO_STRING(DEFAULT_LANGUAGE_CODE);
#endif
#else	//#if EFI_SPECIFICATION_VERSION>0x20000			
#include <FormCallback.h>
#include <HIIDB.h>
#include <Protocol/ExtHii.h>
#endif
							//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
#include <Protocol/AmiSetupProtocol.h>	
#endif
							//<(EIP103171+)

#include <FixedBootOrderStrTokens.h> 			//(EIP112714)
#include <FixedBootOrder.h>		 
#include <FixedBootOrderHII.h>	

#include <AUTOID.h>
#include <NVRAM.h>

#pragma pack(1)
typedef struct{
	UINT32 Type;
	UINT16 Length;
	UINT16 Device[1]; 
} LEGACY_DEVICE_ORDER;
#pragma pack()

BOOLEAN LoadedDefault = FALSE;

#if CSM_SUPPORT
BBS_TABLE *BbsTable = NULL;
HDD_INFO  *HddInfo;
UINT16    HddCount=0;
UINT16    BbsCount=0;
UINT8     *BbsDeviceName = NULL;
#define   BBS_DEVICE_NAME_LENGTH 32
#endif
							//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
static AMI_SETUP_PROTOCOL *AmiSetupProtocol = NULL;
#endif
							//<(EIP103171+)
EFI_HII_STRING_PROTOCOL *gHiiString = NULL;
CHAR8 Language[] = "en-US";
EFI_HII_HANDLE FixedBoot_HiiHandle;

EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
EFI_GUID LegacyDevOrderGuid = LEGACY_DEV_ORDER_GUID;
EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
EFI_GUID DefaultLegacyDevOrderGuid = DEFAULT_LEGACY_DEV_ORDER_VARIABLE_GUID;

FBODevMap *pFBODualDevMap = NULL;
FBODevMap *pFBOLegacyDevMap = NULL;
FBODevMap *pFBOUefiDevMap = NULL;
FBOHiiMap *pFBOHiiMap = NULL;
UINT16 *pBootOptionTokenMap = NULL;     //(EIP123284+)

CALLBACK_PARAMETERS *MyCallbackParametersPtr = NULL;
CALLBACK_PARAMETERS *GetCallbackParameters();


UINT8 TypeLegacyDeviceOptions[FIXED_BOOT_ORDER_GROUP_MAX_NUM][FIXED_BOOT_ORDER_SUBMENU_MAX_NUM];
UINT8 TypeLegacyDeviceCount[FIXED_BOOT_ORDER_GROUP_MAX_NUM];        //GROUP
UINT8 TypeUefiDeviceOptions[FIXED_BOOT_ORDER_GROUP_MAX_NUM][FIXED_BOOT_ORDER_SUBMENU_MAX_NUM];
UINT8 TypeUefiDeviceCount[FIXED_BOOT_ORDER_GROUP_MAX_NUM];          //GROUP

typedef EFI_STATUS (FBO_INITIAL_HII_ITEM)(EFI_HII_HANDLE HiiHandel);
extern FBO_INITIAL_HII_ITEM INITIAL_LEGCAY_HII_ITEM_FUNCTION;
FBO_INITIAL_HII_ITEM *InitialLegacyHiiItem = INITIAL_LEGCAY_HII_ITEM_FUNCTION;
extern FBO_INITIAL_HII_ITEM INITIAL_UEFI_HII_ITEM_FUNCTION;
FBO_INITIAL_HII_ITEM *InitialUefiHiiItem = INITIAL_UEFI_HII_ITEM_FUNCTION;

typedef EFI_STATUS (FBO_INITIAL_GROUP)();
extern FBO_INITIAL_GROUP INITIAL_LEGCAY_GROUP_FUNCTION;
FBO_INITIAL_GROUP *InitLegacyGroup = INITIAL_LEGCAY_GROUP_FUNCTION;
extern FBO_INITIAL_GROUP INITIAL_UEFI_GROUP_FUNCTION;
FBO_INITIAL_GROUP *InitUefiGroup = INITIAL_UEFI_GROUP_FUNCTION;

#define CONFIG_PORT0        0x2E
#define INDEX_PORT0         0x2E
#define DATA_PORT0          0x2F
#define SEND_BYTE_DELEY     0x200
#define SEND_BYTE_ATEMPTS   0x10

#define COM_BASE_ADDR       0x03f8

#define LSR_OFFSET          0x05
#define LCR_OFFSET          0x03
#define DIV_MSB             0x01
#define DIV_LSB             0

#define TRANSMIT_READY_BIT  0x020
#ifdef UART_INPUT_CLOCK
UINTN   UartInputClock=UART_INPUT_CLOCK;
#else
//
// Set the default value((24000000/13)MHz input clock) if the UART_INPUT_CLOCK SDL token is not present.
//
UINTN   UartInputClock=1843200;
#endif

#define BAUD_RATE_DIVISOR   115200

#define DATA_BITS           3   // 0 - 5 bits / 1 - 6 bits
// 2 - 7 bits / 3 - 8 bits
// RSP BUGBUG #define STOP_BIT          0   // 0 - 1 stop bit
#define STOP_BIT            1   // 0 - 1 stop bit
// 1 - mutiple bits depending on the databits
#define PARITY_BITS         0   // 0 - None / 1 enables parity
#define BREAK_BIT           0   // 0 - No break
#define DLAB_BIT            1   // 0 - Divisor Latch Disabled

BOOLEAN SendByte(UINT8 Byte)
{
    UINT8 Buffer8;
    UINT32 Cntr = 0;
    
    do
    {
        // Read the ready signal to see if the serial port is
        // ready for the next byte.
        Buffer8 = IoRead8(COM_BASE_ADDR + LSR_OFFSET);
        // Increment timeout counter.
        Cntr++;
        // Loop until the serial port is ready for the next byte.
    }
    while ( (Cntr < SEND_BYTE_DELEY) && 
            ((Buffer8 & TRANSMIT_READY_BIT) == FALSE) );
    if (Cntr < SEND_BYTE_DELEY){
       
        IoWrite8(COM_BASE_ADDR, Byte);
        return TRUE;
    } else return FALSE;

}

EFI_STATUS SerialOutput(
    IN CHAR8 *String
)
{
//#if SERIAL_STATUS_SUPPORT
    UINT8       *Buffer, i;
    UINT32       Delay;
    BOOLEAN     ByteSent;
    
    if (String == NULL) return EFI_SUCCESS;
    // first make data useable
    Buffer = String;
    
    // now send data one byte at a time until the string hits the end of string
    // or we hit the max number of characters
    while (*Buffer)
    {
        // replace "\n" with "\r\n"
        for (i = 0; i <= SEND_BYTE_ATEMPTS; i++){
            ByteSent = TRUE;

            if (*Buffer=='\n') ByteSent = SendByte('\r');
            
            if (ByteSent)  ByteSent = SendByte(*Buffer);
            
            if (ByteSent) break;
            else
                for (Delay = 0; Delay <= 100000; Delay++);
        }
        
        // move Data pointer to the next byte if previous was sent
        if (ByteSent) Buffer++;
        else return EFI_SUCCESS;
    }
//#endif    
    return EFI_SUCCESS;
}

VOID SerialCheckpoint(UINT16 Checkpoint)
{
    char s[20];
    Sprintf_s(s, sizeof(s), " == %X\n",Checkpoint);
    SerialOutput(s);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetDevMapDataCount
//
// Description:	 get the FBODevMap data amount.
//
// Input:
//  IN FBODevMap *pFBODevMap
//
// Output:
//  OUT UINT16
//
// Modified: None
//      
// Referrals: None
//
// Notes: None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetDevMapDataCount(FBODevMap *pFBODevMap)
{
	UINT16 count = 0;

	if( !pFBODevMap ) return 0;			//end of data

	do{
		if( pFBODevMap[count].DevType == 0 ) break;
		count++;
	}while(1);

	return count;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetHiiMapDataCount
//
// Description:	 get the FBOHiiMap data amount.
//
// Input:
//  None
//
// Output:
//  OUT UINT16
//
// Modified: None
//      
// Referrals: None
//
// Notes: None	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetHiiMapDataCount()
{
	UINT16 count = 0;

	if( !pFBOHiiMap ) return 0;			//end of data

	do{
		if( pFBOHiiMap[count].DevType == 0 ) break;
		count++;
	}while(1);

	return count;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	SearchDevMapByType
//
// Description:	 Search DevMap data index by device type.
//
// Input:
//  IN FBODevMap *pFBODevMap
//  IN UINT16 DevType
//
// Output:
//  OUT UINT16
//
// Modified: None
//      
// Referrals: None
//
// Notes: None	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 SearchDevMapByType(FBODevMap *pFBODevMap, UINT16 DevType)
{
	UINT16 i=0;
	
	do{
		if(pFBODevMap[i].DevType == 0 ) break;	//end of data
		if(pFBODevMap[i].DevType == DevType)
			return i;
		i++;
	}while(1);

	return 0;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SearchHiiMapByType
//
// Description:	Search HiiMap data index by device type.
//
// Input:
//  IN UINT16 DevType
//
// Output:
//  OUT UINT16
//
// Modified: None
//      
// Referrals: None
//
// Notes: None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 SearchHiiMapByType(UINT16 DevType)
{
	UINT16 i=0;
	
	do{
		if(pFBOHiiMap[i].DevType == 0 ) break;	//end of data
		if(pFBOHiiMap[i].DevType == DevType)
			return i;
		i++;
	}while(1);

	return 0;
}

/**
    Compare whether two HDD device paths are the same.

    @param  DevDp1  Device path in comparison.
    @param  DevDp2  Device path in comparison.

    @retval  EFI_SUCCESS    Two HDD paths are the same.
    @retval  EFI_NOT_FOUND  Two Hdd paths are not the same.
*/
EFI_STATUS CompareHddDevicePath( EFI_DEVICE_PATH_PROTOCOL *DevDp1, EFI_DEVICE_PATH_PROTOCOL *DevDp2 )
{

    if ( DevDp1->Type == MEDIA_DEVICE_PATH &&
            DevDp1->SubType == MEDIA_HARDDRIVE_DP )
    {
        if (MemCmp(DevDp1+1, DevDp2+1, sizeof(HARDDRIVE_DEVICE_PATH)-sizeof(EFI_DEVICE_PATH_PROTOCOL)) == 0) //Skip Header EFI_DEVICE_PATH_PROTOCOL.
        {
            DevDp1 = NEXT_NODE(DevDp1);
            if ( DevDp1->Type == MEDIA_DEVICE_PATH &&
                    DevDp1->SubType == MEDIA_FILEPATH_DP ) Wcsupr( (CHAR16*)DevDp1+1 );

            DevDp2 = NEXT_NODE(DevDp2);
            if ( DevDp2->Type == MEDIA_DEVICE_PATH &&
                    DevDp2->SubType == MEDIA_FILEPATH_DP ) Wcsupr( (CHAR16*)DevDp2+1 );

            if (MemCmp(DevDp1, DevDp2, DPLength(DevDp2)) == 0)
                return EFI_SUCCESS;
        }
    }

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: IsDevicePathMatch
//
// Description:	Judge Dp1 and Dp2 is same device path
//
// Input:
//  IN EFI_DEVICE_PATH_PROTOCOL *Dp1
//  IN EFI_DEVICE_PATH_PROTOCOL *Dp2
//
// Output:
//  TRUE : Same Device Path.
//	FALSE : Not same.
// Modified: None
//
// Referrals: None
//
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN IsDevicePathMatch(
	IN EFI_DEVICE_PATH_PROTOCOL *Dp1, 
	IN EFI_DEVICE_PATH_PROTOCOL *Dp2)
{
    // Check null device path
    if (!Dp1 || !Dp2)
        return FALSE ;

    if (DPLength(Dp1) != DPLength(Dp2))
        return FALSE ;
    
    if (!MemCmp(Dp1, Dp2, DPLength(Dp1)))
        return TRUE ;
    else if (!CompareHddDevicePath(Dp1, Dp2))
        return TRUE ;

    return FALSE ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ChangeLegacyDeviceOptionName
//
// Description:	Change Uefi Device option name in setup utility
//
// Input:
//	IN EFI_HANDLE Handle
//  IN OUT VOID *DevName
//
// Output:
//  IN OUT VOID *DevName
//  TRUE : Changed.
//	FALSE : Not Changed.
// Modified: None
//
// Referrals: None
//
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ChangeLegacyDeviceOptionName(
	IN EFI_HANDLE Handle, 
	IN OUT CHAR16 *DevName)
{
	EFI_STATUS Status ;
	EFI_FIXED_BOOT_ORDER_PROTOCOL *FBOProtocol ; 
	Status = pBS->LocateProtocol (&FixedBootOrderGuid, NULL, &FBOProtocol);
	if (!EFI_ERROR(Status))
	{		
		EFI_DEVICE_PATH_PROTOCOL *Dp ;
		Status = pBS->HandleProtocol(Handle, &gEfiDevicePathProtocolGuid, &Dp);
		if (!EFI_ERROR(Status))
		{
			FBO_DEVICE_INFORM *DescriptionPtr ;
			DescriptionPtr = FBOProtocol->GetNewDescription() ;
			while( DescriptionPtr )
			{
				if (IsDevicePathMatch(Dp, DescriptionPtr->DevPath))
				{
					MemSet(DevName,0x100,0) ;
					Wcscpy(DevName, DescriptionPtr->DevName) ;
					TRACE((-1,"Set New Legacy Device Name: %S", DevName)) ;
					return TRUE ;
				}
				DescriptionPtr = DescriptionPtr->Next ;
			}
		}
	}
	return FALSE ;
	
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ChangeUefiDeviceOptionName
//
// Description:	Change Uefi Device option name in setup utility
//
// Input:
//	IN EFI_LOAD_OPTION *BootOption
//  IN OUT VOID *DevName
//
// Output:
//  IN OUT VOID *DevName
//  TRUE : Changed.
//	FALSE : Not Changed.
// Modified: None
//
// Referrals: None
//
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ChangeUefiDeviceOptionName(
	IN EFI_LOAD_OPTION *BootOption, 
	IN OUT VOID **DevName)
{
	EFI_STATUS Status ;
	EFI_FIXED_BOOT_ORDER_PROTOCOL *FBOProtocol ;
	Status = pBS->LocateProtocol (&FixedBootOrderGuid, NULL, &FBOProtocol);
	if (!EFI_ERROR(Status))
	{
		FBO_DEVICE_INFORM *DescriptionPtr ;
		UINT8 *FilePathList ;
		UINTN OldNameSize ;
		OldNameSize = (Wcslen((CHAR16*)(BootOption+1))+1)*sizeof(CHAR16);
		FilePathList = (UINT8*)(BootOption+1)+OldNameSize;
		DescriptionPtr = FBOProtocol->GetNewDescription() ;
		while( DescriptionPtr )
		{
			if (IsDevicePathMatch((EFI_DEVICE_PATH_PROTOCOL*)FilePathList, DescriptionPtr->DevPath))
			{
				*DevName = DescriptionPtr->DevName ;
				TRACE((-1,"Set New Uefi Device Name: %S", (CHAR16*)*DevName)) ;
				return TRUE ;
			}
			DescriptionPtr = DescriptionPtr->Next ;
		}
	}
	return FALSE ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: FBO_AdjustGroupName
//
// Description: Change FBO Group Name
//
// Input:
//
// Output:
// 
// Referrals: None
//
// Notes: EIP 143657
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
FBO_AdjustGroupName()
{
    EFI_STATUS Status ;
	CHAR8* Languages = NULL, *OrgLanguages = NULL;
    UINT16 x ;
    UINT16 HiiSize = GetHiiMapDataCount() ;
    UINT32 Attr ;
	UINTN *GroupPtrAddr = NULL;
	UINTN LangSize = 0, Size = 0 ;
    UINTN OptionMaxSize = 0x100;
    BOOLEAN LastLanguage = FALSE;
	FBO_GROUP_OPTION *Group = NULL, *PreGroup = NULL ;
	
	if (gHiiString == NULL)
		Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &gHiiString);
	if (EFI_ERROR(Status))return;

    Status = gHiiString->GetLanguages(gHiiString, FixedBoot_HiiHandle, Languages, &LangSize);
    if (Status == EFI_BUFFER_TOO_SMALL)
    {
        Status = pBS->AllocatePool(EfiBootServicesData, LangSize, &Languages);
        if (EFI_ERROR(Status)) return;        //not enough resources to allocate string
        Status = gHiiString->GetLanguages(gHiiString, FixedBoot_HiiHandle, Languages, &LangSize);
    }
    if (EFI_ERROR(Status)) return;	
	
    // Get Pointer Address 
    Status = GetEfiVariable(L"FboGroupNameData", &FixedBootOrderGuid, &Attr, &Size, &GroupPtrAddr);
	if ( EFI_ERROR(Status)) return ;
	
	OrgLanguages = Languages ;
    while(!LastLanguage) 
    {
        CHAR8* CurrentLanguage, StrSaveTemp ;
        CurrentLanguage = Languages;        //point CurrentLanguage 
        while (*Languages != ';' && *Languages != 0)
            Languages++;

        StrSaveTemp = *Languages;
        *Languages = 0;         //put null-terminator
        
        Group = (FBO_GROUP_OPTION*)*GroupPtrAddr ;
		while (Group)
		{
            for ( x=0; x < HiiSize ; x++ )
            {
                if (Group->StrToken == pFBOHiiMap[x].StrToken )
                {
                    TRACE((-1,"FixedBootOrder.c AdjustFBOGroupName Change Group Name(StrToken)\n")) ;
                    Status = gHiiString->SetString(gHiiString, FixedBoot_HiiHandle, pFBOHiiMap[x].StrToken, 
                                               CurrentLanguage, Group->NewGroupName, NULL);
                }
                else
                {
                    CHAR16 *TempString = MallocZ(OptionMaxSize) ;
                    Size = OptionMaxSize ;	
                    Status = gHiiString->GetString(gHiiString, CurrentLanguage, FixedBoot_HiiHandle, 
                                                   pFBOHiiMap[x].StrToken, TempString, &Size, NULL);
                    // if string match, update the new group name.
                    if (Group->OrgGroupName && !Wcscmp(TempString, Group->OrgGroupName))
                    {
                        TRACE((-1,"FixedBootOrder.c AdjustFBOGroupName Change Group Name(OrgName)\n")) ;
                        Status = gHiiString->SetString(gHiiString, FixedBoot_HiiHandle, pFBOHiiMap[x].StrToken, 
                                                       CurrentLanguage, Group->NewGroupName, NULL);
                    }
                    pBS->FreePool(TempString) ;
                }   
            }     
			Group = Group->Next ;
		}
        *Languages = StrSaveTemp;
        
        if (*Languages == 0)    //last language in language list
            LastLanguage = TRUE ;
        else
            Languages++ ;
	}
    
    
    // Free all pointer and content
    while (Group)
    {
       PreGroup = Group;
       Group = Group->Next;
       pBS->FreePool(PreGroup);
    }
    Status = pRS->SetVariable(L"FboGroupNameData", &FixedBootOrderGuid, 0, 0, NULL);
    pBS->FreePool(OrgLanguages) ;
	pBS->FreePool(GroupPtrAddr) ;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GetUEFIBootName
//
// Description:	 Get Variable Boot#### and return data pointer.
//
// Input:
//  IN UINT16 BootIndex
//
// Output:
//  EFI_LOAD_OPTION
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_LOAD_OPTION* GetUEFIBootName(IN UINT16 BootIndex)
{
//    	EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
	EFI_STATUS Status;
	UINTN OptionSize;
	CHAR16 BootVarName[15];

	Swprintf( BootVarName, gBootName, BootIndex);			//(EIP35562)

	OptionSize = 0;
	Status = pRS->GetVariable( BootVarName, &EfiVariableGuid, NULL, &OptionSize, NULL);
	if(Status != EFI_NOT_FOUND)
	{
                EFI_LOAD_OPTION *BootOption = NULL; 				//buffer for BootXXX variables

		BootOption=Malloc( OptionSize );
		Status = pRS->GetVariable( BootVarName, &EfiVariableGuid, NULL, &OptionSize, BootOption);
		if(!EFI_ERROR(Status))
                    return BootOption;
	}
	return NULL;

}
						//(EIP101408+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	UpdateDeviceHiiString
//
// Description:	 Update device item multi-language Hii string
//
// Input:
//  UINT16 StrToken
//  CHAR16 *DeviceName
//
// Output:
//  None
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void UpdateDeviceHiiString(IN UINT16 StrToken, IN CHAR16 *DeviceName)
{
    EFI_STATUS Status;
    CHAR8* Languages = NULL;
    CHAR8* OrgLanguages = NULL;
    UINTN LangSize = 0;
    BOOLEAN LastLanguage = FALSE;
    CHAR8 StrSaveTemp;
    UINTN  i, Size=0;
    CHAR16 OldStr[0x100],DeviceStr[0x100];

    if(gHiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &gHiiString);
        if(EFI_ERROR(Status))
            return;
    }

    Status = gHiiString->GetLanguages(gHiiString, FixedBoot_HiiHandle, Languages, &LangSize);
    if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, LangSize, &Languages);
            if(EFI_ERROR(Status))
                return;        //not enough resources to allocate string
            Status = gHiiString->GetLanguages(gHiiString, FixedBoot_HiiHandle, Languages, &LangSize);
    }
    if(EFI_ERROR(Status))
        return;

    OrgLanguages = Languages;
    while(!LastLanguage) {
        CHAR8* CurrentLanguage;
        CurrentLanguage = Languages;        //point CurrentLanguage to start of new language
        while(*Languages != ';' && *Languages != 0)
            Languages++;

        StrSaveTemp = *Languages;
        *Languages = 0;         //put null-terminator
        Size=0x100;
        TRACE((-1,"CurrentLanguage=%s\n", CurrentLanguage));
        Status=gHiiString->GetString(gHiiString, CurrentLanguage, FixedBoot_HiiHandle, StrToken, OldStr, &Size, NULL);
        *Languages = StrSaveTemp;

        if( EFI_ERROR(Status) )		//Language not define in .uni
        {
            if(*Languages == 0)     //last language in language list
                LastLanguage = TRUE;
            else
            {
                *Languages = ';';       //restore original character
                Languages++;
            }
            continue;
        }
        
    
        //removec char ":"
        for( i=0; i<Wcslen(OldStr); i++ )
        {
            if( OldStr[i] == 0x003A ) 
            {
                OldStr[i] = (CHAR16)0;
                break;
            }				
        }
    
        if( DeviceName == NULL )
            Swprintf( DeviceStr, L"%s", OldStr);
        else
            Swprintf( DeviceStr, L"%s:%s", OldStr, DeviceName);
    
        if(*Languages == 0) {       //last language in language list
            LastLanguage = TRUE;
            Status = gHiiString->SetString(gHiiString, FixedBoot_HiiHandle, StrToken, CurrentLanguage, DeviceStr, NULL);
            if(EFI_ERROR(Status))
                {pBS->FreePool(OrgLanguages); return;}
         } else {
            *Languages = 0;         //put null-terminator
            Status = gHiiString->SetString(gHiiString, FixedBoot_HiiHandle, StrToken, CurrentLanguage, DeviceStr, NULL);
            *Languages = ';';       //restore original character
            Languages++;
            if(EFI_ERROR(Status))
                {pBS->FreePool(OrgLanguages); return;}
         }
    }

    if( OrgLanguages )
    	pBS->FreePool(OrgLanguages);
}

						//<(EIP101408+)
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	UpdateLegacyDeviceHiiString
//
// Description:	Update boot option type string token
//
// Input:
//  IN UINT16 DevType
//  IN UINT8 Index
//
// Output:
//  
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void UpdateLegacyDeviceHiiString(IN UINT16 DevType, IN UINT8 Index)
{
#if CSM_SUPPORT
	EFI_STATUS Status;
	VOID *DevOrderBuffer = NULL;
	UINTN BBSNamePtr;
	UINTN Size=0;
	CHAR16 DeviceName[0x100];
	UINT16 HiiDevMapIndex, HiiDevMapCount;

	HiiDevMapCount = GetHiiMapDataCount();
	for( HiiDevMapIndex=0; HiiDevMapIndex<HiiDevMapCount; HiiDevMapIndex++ )
	{
		if( pFBOHiiMap[HiiDevMapIndex].DevType == DevType )
			break;
	}

    if (Index >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
	{
		UpdateDeviceHiiString(  pFBOHiiMap[HiiDevMapIndex].StrToken, NULL);	//(EIP101408+)
	}
	else
	{
		if(LoadedDefault)
			Status = GetEfiVariable(L"DefaultLegacyDevOrder", &DefaultLegacyDevOrderGuid, NULL, &Size, &DevOrderBuffer);
		else
			Status = GetEfiVariable( L"FboLegacyDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer );

		if (!EFI_ERROR(Status) && Size >= 6)
		{
			UINTN j;
			LEGACY_DEVICE_ORDER *DevOrder;

			for(  DevOrder = DevOrderBuffer
				;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
				; DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
			{

				if(DevOrder->Type != DevType) continue;
				if(DevOrder->Length <= 2) continue;

				j= DevOrder->Device[Index] & 0xff;

				{
					char *pStr;	
                    UINTN x ;

                    if( BbsDeviceName )
                        BBSNamePtr = (UINTN)&BbsDeviceName[j*(BBS_DEVICE_NAME_LENGTH+1)];
                    else
                    {
                        BBSNamePtr = (UINTN)( ((UINTN)BbsTable[j].DescStringSegment<<4)  
                                    + BbsTable[j].DescStringOffset );
                    }
				
					pStr=(char *)BBSNamePtr;	
					for(x=0; x<10 ;x++)
					{					
						if( *pStr == ':')
						{
							BBSNamePtr += x + 1;
							break;
						}
						else
							pStr++;
					}							
                    Swprintf(DeviceName, L"%a", BBSNamePtr);
                    ChangeLegacyDeviceOptionName((EFI_HANDLE)BbsTable[j].IBV1,(CHAR16*)&DeviceName) ; 
                    UpdateDeviceHiiString(pFBOHiiMap[HiiDevMapIndex].StrToken, DeviceName);
				}
				break;
			} //for(  DevOrder = DevOrderBuffer..........
		} //if (!EFI_ERROR(Status) && Size>=6)
	
		if(DevOrderBuffer != NULL)
			pBS->FreePool(DevOrderBuffer);
	}
#endif //#if CSM_SUPPORT
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	UpdateUefiDeviceHiiString
//
// Description:	Update boot option type string token
//
// Input:
//  IN UINT16 DevType
//  IN UINT8 Index
//
// Output:
//  
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
void UpdateUefiDeviceHiiString(IN UINT16 DevType, IN UINT8 Index)
{
	EFI_STATUS Status;
	EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
	VOID *DevOrderBuffer = NULL;
	UINTN Size=0;
	UINT16 i=0, HiiDevMapIndex, HiiDevMapCount;

	HiiDevMapCount = GetHiiMapDataCount();
	for( HiiDevMapIndex=0; HiiDevMapIndex<HiiDevMapCount; HiiDevMapIndex++ )
	{
		if( pFBOHiiMap[HiiDevMapIndex].DevType == DevType )
			break;
	}

	if(Index >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
	{
		UpdateDeviceHiiString(  pFBOHiiMap[HiiDevMapIndex].StrToken, NULL);		//(EIP101408+)
	}
	else
	{
		if(LoadedDefault)
			Status = GetEfiVariable(L"DefaultUefiDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer);
		else
			Status = GetEfiVariable( L"UefiDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer );

		if (!EFI_ERROR(Status) && Size >= 6)
		{
			UINTN j;
			LEGACY_DEVICE_ORDER *DevOrder;

			for(  DevOrder = DevOrderBuffer
				;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
				; DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(DevOrder->Type)) ) 
			{

				if(DevOrder->Type != DevType) continue;
				if(DevOrder->Length <= 2) continue;

				j= DevOrder->Device[Index] & 0xff;

				{
					EFI_LOAD_OPTION *BootOption=NULL;
					BootOption=GetUEFIBootName( (UINT16)j );
					if( BootOption )
					{
					        UINT8 *NameStr;

						NameStr=((UINT8*)BootOption)+sizeof(EFI_LOAD_OPTION);
						ChangeUefiDeviceOptionName(BootOption,&NameStr) ;
                        UpdateDeviceHiiString(pFBOHiiMap[HiiDevMapIndex].StrToken, (CHAR16*)NameStr);
						pBS->FreePool( BootOption );
					}
				}
				break;
			} //for(  DevOrder = DevOrderBuffer..........
		} //if (!EFI_ERROR(Status) && Size>=6)
	
		if(DevOrderBuffer != NULL)
			pBS->FreePool(DevOrderBuffer);
	}
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	GroupkeyProcess
//
// Description:	Avoid each group boot priorities from being duplicated to each 
//				other by using INTERACTIVE callback.
//
// Input:
//  IN OUT UINT8 *NewBootDevice
//  IN UINT8 *OldBootDevice
//  IN UINT8 DeviceIndex
//  IN UINT8 DeviceCount
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GroupkeyProcess(IN OUT UINT8 *NewBootDevice, IN UINT8 *OldBootDevice, IN UINT8 DeviceIndex, IN UINT8 DeviceCount)
{
    UINTN i;
    UINT8 NewVal = NewBootDevice[DeviceIndex];
    UINT8 OldVal = OldBootDevice[DeviceIndex];


    for (i = 0; i < DeviceCount ; i++)
        TRACE((-1, "%d ", NewBootDevice[i]));
    TRACE((-1,"\n")); 

    if(OldVal == NewVal)
    {
        return EFI_SUCCESS;
    }
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
    else if( OldVal == FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
    {
        //
        //  Disabled to Enabled
        //
        for(i = 0; i < DeviceIndex; i++)
        {
            //
            //  Duplicated value
            //
            if(OldBootDevice[i] == NewVal)
            {
                NewBootDevice[DeviceIndex] = FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
                break;
            }

            //
            //  Find first disabled device then exchange
            //
            if(NewBootDevice[i] == FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
            {
                NewBootDevice[i] = NewVal;
                NewBootDevice[DeviceIndex] = FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
                break;
            }
        }
    }
    else if(NewVal == FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
    {
        //
        //  Enabled to Disabled
        //

        UINTN j = DeviceIndex;
        for(i = j + 1; i < DeviceCount; i++)
        {
            //
            //  Move disabled one to last step by step.
            //
            if(NewBootDevice[i] != FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)
            {
                NewBootDevice[j] = NewBootDevice[i];
                NewBootDevice[i] = FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
                j = i;
            }

        }
    }
#endif
    else
    {
        //
        //  Both are not equal and disabled.
        //
        for(i = 0; i < DeviceCount; i++)
        {
            if(i == DeviceIndex)
                continue;
            if(NewVal == NewBootDevice[i])
                NewBootDevice[i] = OldVal;
        }
    }
			

	for(i=0;i< DeviceCount ;i++)
	{
		OldBootDevice[i] = NewBootDevice[i];
		TRACE((-1,"%d ",NewBootDevice[i]));
	}
	TRACE((-1,"\n"));

	return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FixedBootOrderFormCallBack
//
// Description:	Avoid each boot priorities from being duplicated to each 
//				other by using INTERACTIVE callback.
//
// Input:
// 	IN EFI_HII_HANDLE HiiHandle 
// 	IN UINT16 Class
// 	IN UINT16 SubClass
// 	IN UINT16 KeyValue
//
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FixedBootOrderFormCallBack (
 IN EFI_HII_HANDLE HiiHandle, 
 IN UINT16 Class, 
 IN UINT16 SubClass, 
 IN UINT16 KeyValue
)
{  
	EFI_STATUS	Status=EFI_SUCCESS;    
	EFI_GUID 	gSetupGuid = SETUP_GUID;
	UINT16 		Current, Swap=0xffff, MapPri=0;
	UINT16		Mapped[16];
	UINT16		i=0, DeviceCount;
	BOOLEAN		Uefi_Boot_item = FALSE;
#if FBO_DUAL_MODE
	BOOLEAN		Dual_Boot_item = FALSE;
#endif
    UINT16      Offset;
    UINT8       DeviceIndex;
    UINT16      DevTypeIndex;
	SETUP_DATA   	pSetup;
    	SETUP_DATA   	*IfrNvData = &pSetup;
    	UINTN 		BufferSize;
	BufferSize = sizeof (SETUP_DATA);

    	MyCallbackParametersPtr=GetCallbackParameters();
	TRACE((-1,"[FixedBootOrder.c] Action=%X\n",MyCallbackParametersPtr->Action));

#if (EFI_SPECIFICATION_VERSION >= 0x2000A)
    if (MyCallbackParametersPtr->Action == EFI_BROWSER_ACTION_CHANGING)
        return EFI_SUCCESS;
    else if (MyCallbackParametersPtr->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD)
        return EFI_UNSUPPORTED; 
    else if (MyCallbackParametersPtr->Action != EFI_BROWSER_ACTION_CHANGED)
        return EFI_INVALID_PARAMETER;		
#endif
	
	KeyValue = MyCallbackParametersPtr->KeyValue;
	TRACE((-1,"[FixedBootOrder.c] ***** INTERACTIVE callback.  KEY=%X\n",KeyValue));

	if( KeyValue < FixedBootOrderStratKey  ) return EFI_UNSUPPORTED;	//Check Is FixedBootOrder assigned keys?

	//--------------------------------------
	//SubMenu UEFI Boot device change process
	//--------------------------------------
	if( KeyValue >= UefiForms_StartKey  )
	{
#if FIXED_BOOT_DISPLAY_DEVICE_NAME_IN_SETUP
		UINT16 DevType=0;
#endif
		FIXED_BOOT_SETUP *IfrNvDataSubMenu=NULL;	
		//
		// Retrive uncommitted data from Browser
		//
		BufferSize = sizeof (FIXED_BOOT_SETUP);
		pBS->AllocatePool (EfiBootServicesData, BufferSize, &IfrNvDataSubMenu);
		ASSERT (IfrNvDataSubMenu != NULL);

		Status = HiiLibGetBrowserData( &BufferSize, IfrNvDataSubMenu, &gSetupGuid, L"FixedBoot");
		TRACE((-1,"[FixedBootOrder.c] HiiLibGetBrowserData(%r) BufferSize=%x\n", Status, BufferSize));
		if (EFI_ERROR (Status)) {
	  		pBS->FreePool (IfrNvDataSubMenu);
	  		return Status;
		}

        Offset = (KeyValue - UefiForms_StartKey);
        DevTypeIndex = Offset / FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
        DeviceIndex = Offset % FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
        GroupkeyProcess( &IfrNvDataSubMenu->UefiDevice[DevTypeIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM],
                         &TypeUefiDeviceOptions[DevTypeIndex][0],
                         DeviceIndex,
                         TypeUefiDeviceCount[DevTypeIndex] );

#if FIXED_BOOT_DISPLAY_DEVICE_NAME_IN_SETUP
        DevType=pFBOUefiDevMap[DevTypeIndex].DevType;
        UpdateUefiDeviceHiiString( DevType, TypeUefiDeviceOptions[DevTypeIndex][0]);
#endif

#if EFI_SPECIFICATION_VERSION>0x20000
		Status = HiiLibSetBrowserData( BufferSize, IfrNvDataSubMenu, &gSetupGuid, L"FixedBoot");
		TRACE((-1,"[FixedBootOrder.c] HiiLibSetBrowserData(%r) BufferSize=%x\n", Status, BufferSize));
		pBS->FreePool (IfrNvDataSubMenu);
#endif
		return Status;
	}
	else
	//--------------------------------------
	//SubMenu Legacy Boot device change process
	//--------------------------------------
	if( KeyValue >= LegacyForms_StartKey )
	{
#if FIXED_BOOT_DISPLAY_DEVICE_NAME_IN_SETUP
		UINT16 DevType=0;
#endif
		FIXED_BOOT_SETUP *IfrNvDataSubMenu=NULL;	
		//
		// Retrive uncommitted data from Browser
		//
		BufferSize = sizeof (FIXED_BOOT_SETUP);
		pBS->AllocatePool (EfiBootServicesData, BufferSize, &IfrNvDataSubMenu);
		ASSERT (IfrNvDataSubMenu != NULL);

		Status = HiiLibGetBrowserData( &BufferSize, IfrNvDataSubMenu, &gSetupGuid, L"FixedBoot");
		TRACE((-1,"[FixedBootOrder.c] HiiLibGetBrowserData(%r) BufferSize=%x\n", Status, BufferSize));
		if (EFI_ERROR (Status)) {
	  		pBS->FreePool (IfrNvDataSubMenu);
	  		return Status;
		}

            Offset = (KeyValue - LegacyForms_StartKey);
            DevTypeIndex =  Offset / FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
            DeviceIndex = Offset % FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
            GroupkeyProcess( &IfrNvDataSubMenu->LegacyDevice[DevTypeIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM],
                             &TypeLegacyDeviceOptions[DevTypeIndex][0],
                             DeviceIndex,
                             TypeLegacyDeviceCount[DevTypeIndex] );

#if FIXED_BOOT_DISPLAY_DEVICE_NAME_IN_SETUP
            DevType=pFBOLegacyDevMap[DevTypeIndex].DevType;
            UpdateLegacyDeviceHiiString( DevType, TypeLegacyDeviceOptions[DevTypeIndex][0]);
#endif

#if EFI_SPECIFICATION_VERSION>0x20000
		Status = HiiLibSetBrowserData( BufferSize, IfrNvDataSubMenu, &gSetupGuid, L"FixedBoot");
		TRACE((-1,"[FixedBootOrder.c] HiiLibSetBrowserData(%r) BufferSize=%x\n", Status, BufferSize));
		pBS->FreePool (IfrNvDataSubMenu);
#endif

		return Status;
	}
	
	//--------------------------------------
	//Legacy & Uefi Boot item change process
	//--------------------------------------
#if FBO_DUAL_MODE
	if( KeyValue >= DualBootItemKey )
	{
		DeviceCount = GetDevMapDataCount(pFBODualDevMap);
		Dual_Boot_item=TRUE;
	}
	else
#endif
	if( KeyValue >= UefiBootItemKey )
	{
		DeviceCount = GetDevMapDataCount(pFBOUefiDevMap);
		Uefi_Boot_item=TRUE;
	}
	else
	{
		DeviceCount = GetDevMapDataCount(pFBOLegacyDevMap);
		Uefi_Boot_item=FALSE;	
	}

	KeyValue = (KeyValue & 0x7f)+1;
	Current = MyCallbackParametersPtr->Value->u16;	// current user selection
	//
	// Retrive uncommitted data from Browser
	//
	Status = HiiLibGetBrowserData( &BufferSize, IfrNvData, &gSetupGuid, L"Setup");
	if (EFI_ERROR (Status)) {
		TRACE((-1,"FixedBootOrder.c HiiLibGetBrowserData (%r)\n", Status));
	  	return Status;
	}

	TRACE((-1,"[FixedBootOrder.c] Current=%X\n",Current));

	// Init all Mapped to FALSE
	for (i=0; i<DeviceCount; i++)
		Mapped[i]=FALSE;

	// Find duplicated boot order to (Swap)
	for (i=0; i<DeviceCount; i++)
	{
#if FBO_DUAL_MODE
		if(Dual_Boot_item)
			MapPri=IfrNvData->DualPriorities[i];
		else
#endif
		if(Uefi_Boot_item)
			MapPri=IfrNvData->UefiPriorities[i];		
		else
			MapPri=IfrNvData->LegacyPriorities[i];

		TRACE((0x800,"[FixedBoot] Priorities[%d]=%d\n", i, MapPri));
	
		if ( MapPri == Current && i+1 != KeyValue && Current < DeviceCount)
		{
		    // i = duplicated index
			Swap = i;
			TRACE((0x800,"[FixedBoot] Need to change Priorities[%d]\n", Swap));
		}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
		if( MapPri == DeviceCount) continue; 	//is Disable?
#endif
		Mapped[MapPri]=TRUE;		// TRUE = priority set
	}

	if (Swap == 0xffff)		// not found duplicated?
		return EFI_SUCCESS;

	// Change the duplicated value according to Mapped[]
	for (i=0; i<DeviceCount; i++)
	{ 
		if (Mapped[i] == FALSE)		// This priority #i is not set yet
		{
#if FIXED_BOOT_SWAP_POLICY == 0        // just swap the duplicated
#if FBO_DUAL_MODE
			if(Dual_Boot_item)
				IfrNvData->DualPriorities[Swap] = i; // not minus nor plus, just make no duplication			
			else
#endif
			if(Uefi_Boot_item)
				IfrNvData->UefiPriorities[Swap] = i; // not minus nor plus, just make no duplication
			else		
            			IfrNvData->LegacyPriorities[Swap] = i; // not minus nor plus, just make no duplication
#endif  //#if FIXED_BOOT_SWAP_POLICY == 0

#if FIXED_BOOT_SWAP_POLICY == 1        // move up or down
            		UINT16      Val1;
        		UINT16      Val2;
            		BOOLEAN     PlusWrap;
            		BOOLEAN     MinusWrap;
	    	        UINT16      NewVal;
#if FBO_DUAL_MODE
		        if(Dual_Boot_item)
			    NewVal = IfrNvData->DualPriorities[Swap];  // new value		
		        else
#endif
		        if(Uefi_Boot_item)
			    NewVal = IfrNvData->UefiPriorities[Swap];		
		        else
        		    NewVal = IfrNvData->LegacyPriorities[Swap];  // new value
        
            		if (MinusWrap = (i == 0 && NewVal == DeviceCount-1))      // old = 0, new = last, wrapped?
			{
#if FBO_DUAL_MODE
				if(Dual_Boot_item)
					IfrNvData->DualPriorities[KeyValue-1] = 0;		
				else
#endif
				if(Uefi_Boot_item)
					IfrNvData->UefiPriorities[KeyValue-1] = 0;
				else
                			IfrNvData->LegacyPriorities[KeyValue-1] = 0;
			}

            		if (PlusWrap = (i == DeviceCount-1 && NewVal == 0))       // old = last, new = 0, wrapped?
			{
#if FBO_DUAL_MODE
				if(Dual_Boot_item)
					IfrNvData->DualPriorities[KeyValue-1] = i;	
				else
#endif
				if(Uefi_Boot_item)
					IfrNvData->UefiPriorities[KeyValue-1] = i;
				else
                			IfrNvData->LegacyPriorities[KeyValue-1] = i;
			}
	            	// Prohibit wrapping

            		if(KeyValue == 1)       // first one?
            		{
                		if (MinusWrap)      // wrap?
                    			continue;       // skip
                		if (NewVal == i-1)  // -1?
                		{
#if FBO_DUAL_MODE
					if(Dual_Boot_item)
						IfrNvData->DualPriorities[KeyValue-1] = NewVal+1;
					else
#endif
					if(Uefi_Boot_item)
						IfrNvData->UefiPriorities[KeyValue-1] = NewVal+1;
					else
                    				IfrNvData->LegacyPriorities[KeyValue-1] = NewVal+1;
                    			continue;
                		}
            		}

            		if  (KeyValue == DeviceCount)       // last one?
            		{
                		if (PlusWrap)       // wrap?
                    			continue;       // skip
                		if (NewVal == i+1)  // +1?
                		{
#if FBO_DUAL_MODE
					if(Dual_Boot_item)
						IfrNvData->DualPriorities[KeyValue-1] = NewVal-1;
					else
#endif
					if(Uefi_Boot_item)
						IfrNvData->UefiPriorities[KeyValue-1] = NewVal-1;
					else
                    				IfrNvData->LegacyPriorities[KeyValue-1] = NewVal-1;
                    			continue;
                		}
            		}

		
			if (NewVal == i-1 || MinusWrap)       // new = old-1 or wrapped?
			{
		        // Minus

//		        	if (KeyValue!=1)     // !=1?  (1-based)
		        	{
#if FBO_DUAL_MODE
					if(Dual_Boot_item)
					{
		            			if (!MinusWrap)
                        				IfrNvData->DualPriorities[KeyValue-1]++;   // +1 because it was -1 by "-" key

    		            			Val1 = IfrNvData->DualPriorities[KeyValue-2];    // previous
    		            			Val2 = IfrNvData->DualPriorities[KeyValue-1];  // current
    		            			IfrNvData->DualPriorities[KeyValue-2]=Val2;
    		            			IfrNvData->DualPriorities[KeyValue-1]=Val1;
					}
					else
#endif
					if(Uefi_Boot_item)
					{
		            			if (!MinusWrap)
                        				IfrNvData->UefiPriorities[KeyValue-1]++;   // +1 because it was -1 by "-" key

    		            			Val1 = IfrNvData->UefiPriorities[KeyValue-2];    // previous
    		            			Val2 = IfrNvData->UefiPriorities[KeyValue-1];  // current
    		            			IfrNvData->UefiPriorities[KeyValue-2]=Val2;
    		            			IfrNvData->UefiPriorities[KeyValue-1]=Val1;
					}
					else
					{
		            			if (!MinusWrap)
                        				IfrNvData->LegacyPriorities[KeyValue-1]++;   // +1 because it was -1 by "-" key

    		            			Val1 = IfrNvData->LegacyPriorities[KeyValue-2];    // previous
    		            			Val2 = IfrNvData->LegacyPriorities[KeyValue-1];  // current
    		            			IfrNvData->LegacyPriorities[KeyValue-2]=Val2;
    		            			IfrNvData->LegacyPriorities[KeyValue-1]=Val1;
					}
		        	}
			}
			else
			{
    		    		if (NewVal == i+1 || PlusWrap)                // new = old+1 or wrapped?
    		    		{
    		        	// Plus    		        
//    		        		if (KeyValue!=FIXED_BOOT_TOTAL_BOOT_OPTIONS)     // != last?
    		       			{
#if FBO_DUAL_MODE
						if(Dual_Boot_item)
						{
    		            				if (!PlusWrap)
                            					IfrNvData->DualPriorities[KeyValue-1]--;      // -1 because it was +1 by "+" key
                        
        		    				Val1 = IfrNvData->DualPriorities[KeyValue-1];    // current
        		    				Val2 = IfrNvData->DualPriorities[KeyValue];    // next
        		    				IfrNvData->DualPriorities[KeyValue-1]=Val2;
        		    				IfrNvData->DualPriorities[KeyValue]=Val1;
						}
						else
#endif
						if(Uefi_Boot_item)
						{
    		            				if (!PlusWrap)
                            					IfrNvData->UefiPriorities[KeyValue-1]--;      // -1 because it was +1 by "+" key
                        
        		    				Val1 = IfrNvData->UefiPriorities[KeyValue-1];    // current
        		    				Val2 = IfrNvData->UefiPriorities[KeyValue];    // next
        		    				IfrNvData->UefiPriorities[KeyValue-1]=Val2;
        		    				IfrNvData->UefiPriorities[KeyValue]=Val1;
						}
						else
						{
    		            				if (!PlusWrap)
                            					IfrNvData->LegacyPriorities[KeyValue-1]--;      // -1 because it was +1 by "+" key
                        
        		    				Val1 = IfrNvData->LegacyPriorities[KeyValue-1];    // current
        		    				Val2 = IfrNvData->LegacyPriorities[KeyValue];    // next
        		    				IfrNvData->LegacyPriorities[KeyValue-1]=Val2;
        		    				IfrNvData->LegacyPriorities[KeyValue]=Val1;
						}
    		        		}	        
    	        		}
                		else
				{
#if FBO_DUAL_MODE
					if(Dual_Boot_item)
    	            				IfrNvData->DualPriorities[Swap] = i; // not minus nor plus, just make no duplication					
					else
#endif
					if(Uefi_Boot_item)
    	            				IfrNvData->UefiPriorities[Swap] = i; // not minus nor plus, just make no duplication					
					else
    	            				IfrNvData->LegacyPriorities[Swap] = i; // not minus nor plus, just make no duplication
				}
    	    		}
#endif  //#if FIXED_BOOT_SWAP_POLICY == 1
#if FBO_DUAL_MODE
			if(Dual_Boot_item)
				TRACE((0x800,"[FixedBoot] NEW DualPriorities[%d]=%d\n", Swap, IfrNvData->DualPriorities[Swap] ));
			else
#endif
			if(Uefi_Boot_item)
				TRACE((0x800,"[FixedBoot] NEW UefiPriorities[%d]=%d\n", Swap, IfrNvData->UefiPriorities[Swap] ));
			else
				TRACE((0x800,"[FixedBoot] NEW LegacyPriorities[%d]=%d\n", Swap, IfrNvData->LegacyPriorities[Swap] ));
			break;
	        }

	}

#if EFI_SPECIFICATION_VERSION>0x20000
	Status = HiiLibSetBrowserData( BufferSize, IfrNvData, &gSetupGuid, L"Setup" );
	TRACE((-1,"FixedBootOrder.c HiiLibSetBrowserData (%r)\n", Status));
#endif
	return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitLegacyGroupDefault
//
// Description: Each group device name Hii String Update, and fixed HiiDB Oneof
//	 	Data.
//			
//
// Input:
//  
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitLegacyGroupDefault()
{
#if CSM_SUPPORT
EFI_STATUS		Status;
VOID 			*DevOrderBuffer = NULL;
UINT16			i, j, DevMapIndex;
UINTN                   BBSNamePtr;
UINTN 			Size = 0;
UINT8			DeviceItem =0, DisableItem = 0;
CHAR16                  DeviceName[0x100];
HII_DEVICE_INFO 	*pHiiDevTokenData = NULL;
UINTN			HiiDevDataSize=0;

	if( LoadedDefault )							
		Status = GetEfiVariable( L"DefaultLegacyDevOrder", &DefaultLegacyDevOrderGuid, NULL, &Size, &DevOrderBuffer);
	else
		Status = GetEfiVariable( L"FboLegacyDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer );

	if (!EFI_ERROR(Status) && Size>6)
	{
		LEGACY_DEVICE_ORDER *DevOrder;
		HII_DEVICE_INFO *HiiDevOrder;

		Status = GetEfiVariable( L"FixedHiiLegacyDevData", &FixedBootOrderGuid, NULL, &HiiDevDataSize, &pHiiDevTokenData );
                if(EFI_ERROR(Status)) return Status;

		HiiDevOrder = pHiiDevTokenData;
		for(  DevOrder = DevOrderBuffer
			;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
			;DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(UINT32)) ) 
		{
			UINT16 SubmenuIndex;
			DeviceItem=0;
			DisableItem=0;

			SubmenuIndex = SearchHiiMapByType( DevOrder->Type );
			DevMapIndex = SearchDevMapByType( pFBOLegacyDevMap, DevOrder->Type);
			if( pFBOHiiMap[SubmenuIndex].FormID != 0 ) 
			{
				for( HiiDevOrder = pHiiDevTokenData
					;(UINT8*)HiiDevOrder<(UINT8*)pHiiDevTokenData+HiiDevDataSize
					;HiiDevOrder = (HII_DEVICE_INFO*)((UINT8*)HiiDevOrder + HiiDevOrder->Length + sizeof(UINT32)) ) 
				{
					if( HiiDevOrder->Type == DevOrder->Type )
						break;
				}
			}

			for(i=0; i<(DevOrder->Length-2)/sizeof(UINT16); i++)
			{
				j= DevOrder->Device[i] & 0xff;
				
				if( pFBOHiiMap[SubmenuIndex].FormID != 0 ) 
                {
                    if( BbsDeviceName )
                        BBSNamePtr = (UINTN)&BbsDeviceName[j*(BBS_DEVICE_NAME_LENGTH+1)];
                    else
                    {
                        BBSNamePtr = (UINTN)( ((UINTN)BbsTable[j].DescStringSegment<<4) 
                                            + BbsTable[j].DescStringOffset );
                    }

                    Swprintf(DeviceName, L"%a", BBSNamePtr);
					ChangeLegacyDeviceOptionName((EFI_HANDLE)BbsTable[j].IBV1,(CHAR16*)&DeviceName) ;
                   	InitString(FixedBoot_HiiHandle, HiiDevOrder->StrToken[i], L"%s", DeviceName);

                    TRACE((-1, "BBS DEVICE(%d):%S \n", i, DeviceName));										
				}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
				if( DevOrder->Device[i] & 0xff00 )
				{
					TypeLegacyDeviceOptions[DevMapIndex][DeviceItem+DisableItem]=FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
					DisableItem++;
				}
				else
#endif
				{
					TypeLegacyDeviceOptions[DevMapIndex][DeviceItem+DisableItem]=DeviceItem+DisableItem;
					DeviceItem++;
				}
                if ((DeviceItem + DisableItem) >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
	
			}
	

			
			TRACE((-1,"[FixedBoot] DeviceItem=%d DisableItem=%d \n", DeviceItem, DisableItem));

#if FIXED_BOOT_DISPLAY_DEVICE_NAME_IN_SETUP
			if(DeviceItem)
				UpdateLegacyDeviceHiiString(DevOrder->Type, 0);
			else
                UpdateLegacyDeviceHiiString(DevOrder->Type, FIXED_BOOT_ORDER_SUBMENU_MAX_NUM);       //no device, show type
#endif

			TypeLegacyDeviceCount[DevMapIndex]=DeviceItem;
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
			if(DisableItem)
				TypeLegacyDeviceCount[DevMapIndex]+=DisableItem;
#endif
			TRACE((-1,"[FixedBoot] Type(%x)DevCount=%x\n",DevMapIndex, TypeLegacyDeviceCount[DevMapIndex]));
		}
	}
	
	if( DevOrderBuffer )
		pBS->FreePool( DevOrderBuffer );
	if( pHiiDevTokenData )
		pBS->FreePool( pHiiDevTokenData );
#endif //#if CSM_SUPPORT
	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitUefiGroupDefault
//
// Description: Each group device name Hii String Update, and fixed HiiDB Oneof
//	 	Data.
//			
//
// Input:
//  	NONE
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitUefiGroupDefault()
{
EFI_STATUS		Status;
EFI_GUID 		FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;
VOID 			*DevOrderBuffer = NULL;
UINT16			i, j, DevMapIndex;
//UINTN                 BBSNamePtr;
UINTN 			Size = 0;
UINT8			DeviceItem =0, DisableItem = 0;
//CHAR16                DeviceName[0x100];
HII_DEVICE_INFO 	*pHiiDevTokenData = NULL;
UINTN			HiiDevDataSize=0;

	if( LoadedDefault )							
		Status = GetEfiVariable( L"DefaultUefiDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer);
	else
		Status = GetEfiVariable( L"UefiDevOrder", &FixedBootOrderGuid, NULL, &Size, &DevOrderBuffer );

	if (!EFI_ERROR(Status) && Size>6)
	{
		LEGACY_DEVICE_ORDER *DevOrder;
		HII_DEVICE_INFO *HiiDevOrder;

		Status = GetEfiVariable( L"FixedHiiUefiDevData", &FixedBootOrderGuid, NULL, &HiiDevDataSize, &pHiiDevTokenData );
                if(EFI_ERROR(Status)) return Status;
		
		for(  DevOrder = DevOrderBuffer
			;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+Size
			;DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(UINT32)) ) 
		{
			UINT16 SubmenuIndex;
			DeviceItem=0;
			DisableItem=0;

			SubmenuIndex = SearchHiiMapByType( DevOrder->Type );
			DevMapIndex = SearchDevMapByType( pFBOUefiDevMap, DevOrder->Type);
			if( pFBOHiiMap[SubmenuIndex].FormID != 0 ) 
			{			

				for( HiiDevOrder = pHiiDevTokenData
					;(UINT8*)HiiDevOrder<(UINT8*)pHiiDevTokenData+HiiDevDataSize
					;HiiDevOrder = (HII_DEVICE_INFO*)((UINT8*)HiiDevOrder + HiiDevOrder->Length + sizeof(UINT32)) ) 
				{
					if( HiiDevOrder->Type == DevOrder->Type )
						break;
				}
			}

			for(i=0; i<(DevOrder->Length-2)/sizeof(UINT16); i++)
			{
				EFI_LOAD_OPTION *BootOption=NULL;

				j= DevOrder->Device[i] & 0xff;

				BootOption=GetUEFIBootName(j);
				if( BootOption )
				{
					if( pFBOHiiMap[SubmenuIndex].FormID != 0 ) 
					{
                                                CHAR16 *NameStr;
						NameStr=(CHAR16*)((UINT8*)BootOption+sizeof(EFI_LOAD_OPTION));	
                        ChangeUefiDeviceOptionName(BootOption,&NameStr) ; // (EIP143657+)
               			InitString(FixedBoot_HiiHandle, HiiDevOrder->StrToken[i], L"%s", NameStr);							
						TRACE((-1,"UEFI DEVICE(%d):%S \n", i, NameStr));
					}
					pBS->FreePool( BootOption );
				}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
				if( DevOrder->Device[i] & 0xff00 )
				{
                    TypeUefiDeviceOptions[DevMapIndex][DeviceItem+DisableItem] = FIXED_BOOT_ORDER_SUBMENU_MAX_NUM;
					DisableItem++;
				}
				else
#endif
				{
					TypeUefiDeviceOptions[DevMapIndex][DeviceItem+DisableItem]=DeviceItem+DisableItem;
					DeviceItem++;
				}
                if ((DeviceItem + DisableItem) >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
			}
			TRACE((-1,"[FixedBoot] DeviceItem=%d DisableItem=%d \n", DeviceItem, DisableItem));

#if FIXED_BOOT_DISPLAY_DEVICE_NAME_IN_SETUP
			if(DeviceItem)
				UpdateUefiDeviceHiiString(DevOrder->Type, 0);
			else
                UpdateUefiDeviceHiiString(DevOrder->Type, FIXED_BOOT_ORDER_SUBMENU_MAX_NUM);     //no device, show type
#endif

			TypeUefiDeviceCount[DevMapIndex]=DeviceItem;
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION
			if(DisableItem)
				TypeUefiDeviceCount[DevMapIndex]+=DisableItem;
#endif
			TRACE((-1,"[FixedBoot] Type(%x)DevCount=%x\n",DevMapIndex, TypeUefiDeviceCount[DevMapIndex]));
		}
	}

	if( DevOrderBuffer )
		pBS->FreePool( DevOrderBuffer );
	if( pHiiDevTokenData )
		pBS->FreePool( pHiiDevTokenData );

	return EFI_SUCCESS;
}
							//(EIP101408+)>
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	HiiAddLanguageBootOptionString
//
// Description: Install multi-language for STR_BOOT_OPTION.
//
// Input:
// 	NONE 
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
STRING_REF HiiAddLanguageBootOptionString(IN EFI_HII_HANDLE HiiHandle, IN UINT16 BootOptionNumber)
{
    EFI_STATUS Status;
    CHAR8* Languages = NULL;
    CHAR8* OrgLanguages = NULL;
    UINTN LangSize = 0;
    BOOLEAN LastLanguage = FALSE;
    STRING_REF  StringId = 0;
    CHAR8 StrSaveTemp;

    UINTN  Size=0;
    CHAR16 BootOptionStr[0x100];
    CHAR16 BootStr[32];

    if(gHiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &gHiiString);
        if(EFI_ERROR(Status))
            return 0;
    }

    Status = gHiiString->GetLanguages(gHiiString, HiiHandle, Languages, &LangSize);
    if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, LangSize, &Languages);
            if(EFI_ERROR(Status))
                return NULL;        //not enough resources to allocate string
            Status = gHiiString->GetLanguages(gHiiString, HiiHandle, Languages, &LangSize);
    }
    if(EFI_ERROR(Status))
        return 0;

    OrgLanguages = Languages;
    while(!LastLanguage) {
        CHAR8* CurrentLanguage;

        CurrentLanguage = Languages;        //point CurrentLanguage to start of new language
        while(*Languages != ';' && *Languages != 0)
            Languages++;

	StrSaveTemp = *Languages;
        *Languages = 0;         //put null-terminator
	Size=0x100;
	Status=gHiiString->GetString(gHiiString, CurrentLanguage, HiiHandle, STRING_TOKEN(STR_BOOT_OPTION), BootOptionStr, &Size, NULL);
	*Languages = StrSaveTemp;
	if( EFI_ERROR(Status) )		//Language not define in .uni
	{
        	if(*Languages == 0)     //last language in language list
            		LastLanguage = TRUE;
		else
		{
            		*Languages = ';';       //restore original character
            		Languages++;
		}
		continue;
	}

	Swprintf(BootStr, BootOptionStr, BootOptionNumber);

        if(*Languages == 0) {       //last language in language list
            LastLanguage = TRUE;
            if(StringId == 0)
                Status = gHiiString->NewString(gHiiString, HiiHandle, &StringId, CurrentLanguage, NULL, BootStr, NULL);
            else
                Status = gHiiString->SetString(gHiiString, HiiHandle, StringId, CurrentLanguage, BootStr, NULL);
            if(EFI_ERROR(Status))
                {pBS->FreePool(OrgLanguages); return 0;}
        } else {
            *Languages = 0;         //put null-terminator
            if(StringId == 0)
                Status = gHiiString->NewString(gHiiString, HiiHandle, &StringId, CurrentLanguage, NULL, BootStr, NULL);
            else
                Status = gHiiString->SetString(gHiiString, HiiHandle, StringId, CurrentLanguage, BootStr, NULL);
            *Languages = ';';       //restore original character
            Languages++;
            if(EFI_ERROR(Status))
                 {pBS->FreePool(OrgLanguages); return 0;}
        }
    }

    if( OrgLanguages )
    	pBS->FreePool(OrgLanguages);
    return StringId;        
}
							//<(EIP101408+)

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitialLegacyHiiItemDefault
//
// Description: Create legacy boot item device Hii Item data.
//
// Input:
// 	EFI_HANDLE HiiHandle 
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitialLegacyHiiItemDefault(EFI_HANDLE HiiHandle)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;	
							//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
	EFI_HANDLE RegHandle = NULL;
#endif
							//<(EIP103171+)
	UINTN DevOrderSize = 0;
	UINT16 DevMapCount=0;
	UINT16 VarSetupID, VarFixedBootID;
	LEGACY_DEVICE_ORDER *DevOrder=NULL, *DevOrderBuffer=NULL;

	DevMapCount = GetDevMapDataCount(pFBOLegacyDevMap);
	TRACE((-1,"[FixedBootOrderTSE.c]HiiDevMap count=%d\n", DevMapCount ));

	InitHiiData( HiiHandle );
	VarSetupID = FIndVariableID( "Setup" );
	TRACE((-1,"[FixedBootOrderTSE.c] Find Setup VarID=%02x\n", VarSetupID));
	VarFixedBootID = FIndVariableID( "FixedBoot" );
	TRACE((-1,"[FixedBootOrderTSE.c] Find FixedBoot VarID=%02x\n", VarFixedBootID));
	FreeHiiData();

	{
		STRING_REF Strid=0;
		EFI_HII_UPDATE_DATA Update;
		
		if( gHiiString == NULL )
			Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &gHiiString);

		if( pFBOHiiMap == NULL ) 
		{ 
			TRACE((-1,"pFBOHiiMap == NULL\n"));
			ASSERT(pFBOHiiMap);
		}

		if(!EFI_ERROR(Status)) 
		{
			UINT8 *IfrTempPtr,*OldIfrTempPtr = NULL;
			SETUP_DATA *pSetup=0;
			UINT16 i,j;
                        HII_DEVICE_INFO *pHiiDevTokenData = NULL, *pHiiDevTokenData2 = NULL;
                                                      
            OldIfrTempPtr = IfrTempPtr = Malloc(
                ( sizeof(EFI_IFR_ONE_OF)
                +sizeof(EFI_IFR_ONE_OF_OPTION)*(DevMapCount+1)  // include one disable option
                +sizeof(EFI_IFR_END) )
                *DevMapCount);
            if (IfrTempPtr == NULL)
            {
                TRACE((-1, "Error allocation memory for creating IFR\n"));
                ASSERT(IfrTempPtr);
            }
			Update.Data = IfrTempPtr;

			for(i=0;i<DevMapCount;i++)
			{
				UINT16 HiiMapIndex;

				if( pBootOptionTokenMap == NULL )                               //(EIP123284+)
					Strid = HiiAddLanguageBootOptionString(HiiHandle, i+1);		//(EIP101408+)
				else                                                            //(EIP123284+)
					Strid = pBootOptionTokenMap[i];                             //(EIP123284+)

				Status = CreateHiiOneOfItem( &IfrTempPtr, VarSetupID, (UINT16)&pSetup->LegacyPriorities[i], LegacyBootItemKey+i, Strid, STR_BOOT_OPTION_HELP, 0x11);

				for(j=0;j<DevMapCount;j++)
				{

					HiiMapIndex = SearchHiiMapByType( pFBOLegacyDevMap[j].DevType );
					Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 1, j, pFBOHiiMap[HiiMapIndex].StrToken );
				}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION	
				Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 1, DevMapCount, STR_DISABLED );
#endif
				CreateHiiIfrEndItem( &IfrTempPtr );
											//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
				RegHandle = NULL;
				if( AmiSetupProtocol != NULL )
					AmiSetupProtocol->RegisterCallback(FBO_STRING_INIT_FORM_SET_CLASS, 0, LegacyBootItemKey+i, FixedBootOrderFormCallBack, &RegHandle);
#endif
											//<(EIP103171+)
			}


			Update.Offset = (UINT32)((UINT8*)IfrTempPtr-(UINT8*)Update.Data);	//Calc Hii data length.
			TRACE((-1,"Update.Data...............\n"));
//			TraceOutData( (UINT8*)Update.Data, Update.Offset );	
				
			Status = IfrLibUpdateForm (
  					HiiHandle,
					NULL,
  					FBO_VFR_FORM_ID,
					FIXED_BOOT_ITEM_LABEL1,
  					TRUE,
  					&Update);

			TRACE((-1,"IfrLibUpdateForm (%r)\n", Status));
            pBS->FreePool(OldIfrTempPtr);

            OldIfrTempPtr = IfrTempPtr = Malloc(
                ( sizeof(EFI_IFR_ONE_OF)
                +sizeof(EFI_IFR_ONE_OF_OPTION)*(FIXED_BOOT_ORDER_SUBMENU_MAX_NUM+1)  // include one disable option
                +sizeof(EFI_IFR_END) )
                *FIXED_BOOT_ORDER_SUBMENU_MAX_NUM);
            if (IfrTempPtr == NULL)
            {
                TRACE((-1, "Error allocation memory for creating IFR\n"));
                ASSERT(IfrTempPtr);
            }

			Status = GetEfiVariable( L"FboLegacyDevOrder", &FixedBootOrderGuid, NULL, &DevOrderSize, &DevOrderBuffer );
			TRACE((-1,"GetEfiVariable(FboLegacyDevOrder) %r\n", Status));
			if (EFI_ERROR(Status) || DevOrderSize<=6) return Status;

			pHiiDevTokenData2 = pHiiDevTokenData = Malloc( DevOrderSize );
			if( pHiiDevTokenData == NULL ) return EFI_OUT_OF_RESOURCES;

			for(  DevOrder = DevOrderBuffer
				;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+DevOrderSize
				;DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(UINT32)) ) 
			{
				UINT16 SubmenuIndex;

				SubmenuIndex = SearchHiiMapByType( DevOrder->Type );
				if( pFBOHiiMap[SubmenuIndex].FormID == 0 ) continue;		//this type no Submenu 

				pHiiDevTokenData->Type=DevOrder->Type;
				pHiiDevTokenData->Length=DevOrder->Length;

				//Create BootOption item string token ID.
				for(i=0;i<(DevOrder->Length-2)/sizeof(UINT16);i++)
				{
                    if (i >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
					Status = gHiiString->NewString(gHiiString, HiiHandle, &Strid, Language, NULL, L" ", NULL);			
					if( EFI_ERROR(Status) )
						return Status;				
					pHiiDevTokenData->StrToken[i]=Strid;
				}

				Update.Data = IfrTempPtr = OldIfrTempPtr;			//reset IFR data memory. 
				for(i=0;i<(DevOrder->Length-2)/sizeof(UINT16);i++)
				{
					UINT16 VarOffset;
					UINT16 CallBackKey;
					UINT16 DevDataIndex=0;

                    if (i >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
					DevDataIndex = SearchDevMapByType( pFBOLegacyDevMap, pHiiDevTokenData->Type );
                    VarOffset=(DevDataIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) + i;				//offset to FIXED_BOOT_SETUP.LegacyDevice[]
                    CallBackKey=(DevDataIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) + i + LegacyForms_StartKey;
				
				    if( pBootOptionTokenMap == NULL )                               //(EIP123284+)
					    Strid = HiiAddLanguageBootOptionString(HiiHandle, i+1);		//(EIP101408+)
				    else                                                            //(EIP123284+)
					    Strid = pBootOptionTokenMap[i];                             //(EIP123284+)
					Status = CreateHiiOneOfItem( &IfrTempPtr, VarFixedBootID, VarOffset, CallBackKey, Strid, STR_BOOT_OPTION_HELP, 0x10);

					for(j=0;j<(pHiiDevTokenData->Length-2)/sizeof(UINT16);j++)
					{
                        if (j >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
						if( pFBOHiiMap == NULL ) 
						{ 
							TRACE((-1,"pFBOHiiMap == NULL\n"));
							ASSERT(pFBOHiiMap);
						}

						Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 0, j, pHiiDevTokenData->StrToken[j] );	//UINT8
					}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION	
                    Status = CreateHiiOneOfOptionItem(&IfrTempPtr, 0, FIXED_BOOT_ORDER_SUBMENU_MAX_NUM, STR_DISABLED);
#endif
					CreateHiiIfrEndItem( &IfrTempPtr );
												//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
					RegHandle = NULL;
					if( AmiSetupProtocol != NULL )
						AmiSetupProtocol->RegisterCallback(FBO_STRING_INIT_FORM_SET_CLASS, 0, CallBackKey, FixedBootOrderFormCallBack, &RegHandle);
#endif
												//<(EIP103171+)
				}

				Update.Offset = (UINT32)((UINT8*)IfrTempPtr-(UINT8*)Update.Data);	//Calc Hii data length.			
				TRACE((-1,"Update.Data...............\n"));
//				TraceOutData( (UINT8*)Update.Data, Update.Offset );
				
				Status = IfrLibUpdateForm (
  					HiiHandle,
					NULL,
  					pFBOHiiMap[SubmenuIndex].FormID,
					pFBOHiiMap[SubmenuIndex].Label,
  					TRUE,
  					&Update);

				TRACE((-1,"IfrLibUpdateForm (%r)\n", Status));
				pHiiDevTokenData = (HII_DEVICE_INFO*)((UINT8*)pHiiDevTokenData+pHiiDevTokenData->Length+sizeof(UINT32));

			}
            pBS->FreePool(OldIfrTempPtr);

			{
				UINT16 HiiDevInfoSize;
				HiiDevInfoSize=(UINT16)((UINT8*)pHiiDevTokenData-(UINT8*)pHiiDevTokenData2);
		
				if(HiiDevInfoSize)
				{
	    				pRS->SetVariable(
 		       				L"FixedHiiLegacyDevData", 
	  		      			&FixedBootOrderGuid,
		        			EFI_VARIABLE_BOOTSERVICE_ACCESS,
		        			HiiDevInfoSize,
		        			pHiiDevTokenData2);
				}
			}
			pBS->FreePool( pHiiDevTokenData2 );
		}
	}

	return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitialUefiHiiItemDefault
//
// Description: Create UEFI boot item device Hii Item data.
//
// Input:
// 	EFI_HANDLE HiiHandle 
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitialUefiHiiItemDefault(EFI_HANDLE HiiHandle)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_GUID FixedBootOrderGuid = FIXED_BOOT_ORDER_GUID;	
							//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
	EFI_HANDLE RegHandle = NULL;
#endif
							//<(EIP103171+)
	UINTN DevOrderSize = 0;
	UINT16 DevMapCount=0;
	UINT16 VarSetupID, VarFixedBootID;
	LEGACY_DEVICE_ORDER *DevOrder=NULL, *DevOrderBuffer=NULL;

	DevMapCount = GetDevMapDataCount(pFBOUefiDevMap);
	TRACE((-1,"[FixedBootOrderTSE.c]HiiDevMap count=%d\n", DevMapCount ));

	InitHiiData( HiiHandle );
	VarSetupID = FIndVariableID( "Setup" );
	TRACE((-1,"[FixedBootOrderTSE.c] Find Setup VarID=%02x\n", VarSetupID));
	VarFixedBootID = FIndVariableID( "FixedBoot" );
	TRACE((-1,"[FixedBootOrderTSE.c] Find FixedBoot VarID=%02x\n", VarFixedBootID));
	FreeHiiData();

	{
		STRING_REF Strid=0;
		EFI_HII_UPDATE_DATA Update;
		
		if( gHiiString == NULL )
			Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &gHiiString);

		if( pFBOHiiMap == NULL ) 
		{ 
			TRACE((-1,"pFBOHiiMap == NULL\n"));
			ASSERT(pFBOHiiMap);
		}

		if(!EFI_ERROR(Status)) 
		{
			UINT8 *IfrTempPtr,*OldIfrTempPtr = NULL;
			SETUP_DATA *pSetup=0;
			UINT16 i,j;
                        HII_DEVICE_INFO *pHiiDevTokenData = NULL, *pHiiDevTokenData2 = NULL;

            OldIfrTempPtr = IfrTempPtr = Malloc(
                ( sizeof(EFI_IFR_ONE_OF)
                +sizeof(EFI_IFR_ONE_OF_OPTION)*(DevMapCount+1)  // include one disable option
                +sizeof(EFI_IFR_END) )
                *DevMapCount);
            if (IfrTempPtr == NULL)
            {
                TRACE((-1, "Error allocation memory for IFR\n"));
                ASSERT(IfrTempPtr);
            }
			Update.Data = IfrTempPtr;

			for(i=0;i<DevMapCount;i++)
			{	
				UINT16 HiiMapIndex;

				if( pBootOptionTokenMap == NULL )                               //(EIP123284+)
					Strid = HiiAddLanguageBootOptionString(HiiHandle, i+1);		//(EIP101408+)
				else                                                            //(EIP123284+)
					Strid = pBootOptionTokenMap[i];                             //(EIP123284+)
				Status = CreateHiiOneOfItem( &IfrTempPtr, VarSetupID, (UINT16)&pSetup->UefiPriorities[i], UefiBootItemKey+i, Strid, STR_BOOT_OPTION_HELP, 0x11);

				for(j=0;j<DevMapCount;j++)
				{

					HiiMapIndex = SearchHiiMapByType( pFBOUefiDevMap[j].DevType );
					Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 1, j, pFBOHiiMap[HiiMapIndex].StrToken );
				}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION	
				Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 1, DevMapCount, STR_DISABLED );
#endif
				CreateHiiIfrEndItem( &IfrTempPtr );
											//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
				RegHandle = NULL;
				if( AmiSetupProtocol != NULL )
					AmiSetupProtocol->RegisterCallback(FBO_STRING_INIT_FORM_SET_CLASS, 0, UefiBootItemKey+i, FixedBootOrderFormCallBack, &RegHandle);
#endif
											//<(EIP103171+)
			}

			Update.Offset = (UINT32)((UINT8*)IfrTempPtr-(UINT8*)Update.Data);	//Calc Hii data length.
			TRACE((-1,"Update.Data...............\n"));
//			TraceOutData( (UINT8*)Update.Data, Update.Offset );	
					
			Status = IfrLibUpdateForm (
  					HiiHandle,
					NULL,
  					FBO_VFR_FORM_ID,
					FIXED_BOOT_ITEM_LABEL2,
  					TRUE,
  					&Update);

			TRACE((-1,"IfrLibUpdateForm (%r)\n", Status));
            pBS->FreePool(OldIfrTempPtr);
		
            OldIfrTempPtr = IfrTempPtr = Malloc(
                ( sizeof(EFI_IFR_ONE_OF)
                +sizeof(EFI_IFR_ONE_OF_OPTION)*(FIXED_BOOT_ORDER_SUBMENU_MAX_NUM+1)  // include one disable option
                +sizeof(EFI_IFR_END) )
                *FIXED_BOOT_ORDER_SUBMENU_MAX_NUM);
            if (IfrTempPtr == NULL)
            {
                TRACE((-1, "Error allocation memory for creating IFR\n"));
                ASSERT(IfrTempPtr);
            }

			//Create submenu boot item.
			Status = GetEfiVariable( L"UefiDevOrder", &FixedBootOrderGuid, NULL, &DevOrderSize, &DevOrderBuffer );
			TRACE((-1,"GetEfiVariable(UefiDevOrder) %r\n", Status));
			if (EFI_ERROR(Status) || DevOrderSize<=6) return Status;

			pHiiDevTokenData2 = pHiiDevTokenData = Malloc( DevOrderSize );
			if( pHiiDevTokenData == NULL ) return EFI_OUT_OF_RESOURCES;
			
			for(  DevOrder = DevOrderBuffer
				;(UINT8*)DevOrder<(UINT8*)DevOrderBuffer+DevOrderSize
				;DevOrder = (LEGACY_DEVICE_ORDER*)((UINT8*)DevOrder + DevOrder->Length + sizeof(UINT32)) ) 
			{
				UINT16 SubmenuIndex;

				SubmenuIndex = SearchHiiMapByType( DevOrder->Type );
				if( pFBOHiiMap[SubmenuIndex].FormID == 0 ) continue;		//this type no Submenu 

				pHiiDevTokenData->Type=DevOrder->Type;
				pHiiDevTokenData->Length=DevOrder->Length;

				//Create BootOption item string token ID.
				for(i=0;i<(DevOrder->Length-2)/sizeof(UINT16);i++)
				{
                    if (i >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
					Status = gHiiString->NewString(gHiiString, HiiHandle, &Strid, Language, NULL, L" ", NULL);
					if( EFI_ERROR(Status) )
						return Status;
					pHiiDevTokenData->StrToken[i]=Strid;
				}


				Update.Data = IfrTempPtr = OldIfrTempPtr;			//reset IFR data memory. 

				for(i=0;i<(pHiiDevTokenData->Length-2)/sizeof(UINT16);i++)
				{
					UINT16 VarOffset;
					UINT16 CallBackKey;
					UINT16 DevDataIndex=0;
				
                    if (i >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
					DevDataIndex = SearchDevMapByType( pFBOUefiDevMap, pHiiDevTokenData->Type );
                    VarOffset = (DevDataIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) + EFI_FIELD_OFFSET(FIXED_BOOT_SETUP, UefiDevice) + i;     //offset to FIXED_BOOT_SETUP.UefiDevice[]
                    CallBackKey=(DevDataIndex * FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) + i +UefiForms_StartKey;	//
		
				    if( pBootOptionTokenMap == NULL )                               //(EIP123284+)
					    Strid = HiiAddLanguageBootOptionString(HiiHandle, i+1);		//(EIP101408+)
				    else                                                            //(EIP123284+)
					    Strid = pBootOptionTokenMap[i];                             //(EIP123284+)
					Status = CreateHiiOneOfItem( &IfrTempPtr, VarFixedBootID, VarOffset, CallBackKey, Strid, STR_BOOT_OPTION_HELP, 0x10);

					for(j=0;j<(pHiiDevTokenData->Length-2)/sizeof(UINT16);j++)
					{
                        if (j >= FIXED_BOOT_ORDER_SUBMENU_MAX_NUM) break;
						if( pFBOHiiMap == NULL ) 
						{ 
							TRACE((-1,"pFBOHiiMap == NULL\n"));
							ASSERT(pFBOHiiMap);
						}

						Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 0, j, pHiiDevTokenData->StrToken[j] );	//UINT8
					}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION	
				Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 0, FIXED_BOOT_ORDER_SUBMENU_MAX_NUM, STR_DISABLED );
#endif
					CreateHiiIfrEndItem( &IfrTempPtr );
												//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
					RegHandle = NULL;
					if( AmiSetupProtocol != NULL )
						AmiSetupProtocol->RegisterCallback(FBO_STRING_INIT_FORM_SET_CLASS, 0, CallBackKey, FixedBootOrderFormCallBack, &RegHandle);
#endif
												//<(EIP103171+)
				}

				Update.Offset = (UINT32)((UINT8*)IfrTempPtr-(UINT8*)Update.Data);	//Calc Hii data length.			
				TRACE((-1,"Update.Data...............\n"));
//				TraceOutData( (UINT8*)Update.Data, Update.Offset );
					
				Status = IfrLibUpdateForm (
  					HiiHandle,
					NULL,
  					pFBOHiiMap[SubmenuIndex].FormID,
					pFBOHiiMap[SubmenuIndex].Label,
  					TRUE,
  					&Update);

				TRACE((-1,"IfrLibUpdateForm (%r)\n", Status));
				pHiiDevTokenData = (HII_DEVICE_INFO*)((UINT8*)pHiiDevTokenData+pHiiDevTokenData->Length+sizeof(UINT32));
			}
            pBS->FreePool(OldIfrTempPtr);

			{
				UINT16 HiiDevInfoSize;
				HiiDevInfoSize=(UINT16)((UINT8*)pHiiDevTokenData-(UINT8*)pHiiDevTokenData2);
		
				if(HiiDevInfoSize)
				{
	    				pRS->SetVariable(
 		       				L"FixedHiiUefiDevData", 
	  		      			&FixedBootOrderGuid,
		        			EFI_VARIABLE_BOOTSERVICE_ACCESS,
		        			HiiDevInfoSize,
		        			pHiiDevTokenData2);
				}
			}

			pBS->FreePool( pHiiDevTokenData2 );
		}
	}

	return EFI_SUCCESS;
}

#if FBO_DUAL_MODE
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	InitialDaulHiiItem
//
// Description: Create Dual mode boot item device Hii Item data.
//
// Input:
// 	EFI_HANDLE HiiHandle 
// Output:
//  	EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS InitialDaulHiiItem(EFI_HANDLE HiiHandle)
{
	EFI_STATUS Status = EFI_SUCCESS;
							//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
	EFI_HANDLE RegHandle = NULL;
#endif
							//<(EIP103171+)
	UINT16 DevMapCount=0;
	UINT16 VarSetupID, VarFixedBootID;


	DevMapCount = GetDevMapDataCount(pFBODualDevMap);
	TRACE((-1,"[FixedBootOrderTSE.c]HiiDevMap count=%d\n", DevMapCount ));

	InitHiiData( HiiHandle );
	VarSetupID = FIndVariableID( "Setup" );
	TRACE((-1,"[FixedBootOrderTSE.c] Find Setup VarID=%02x\n", VarSetupID));
	VarFixedBootID = FIndVariableID( "FixedBoot" );
	TRACE((-1,"[FixedBootOrderTSE.c] Find FixedBoot VarID=%02x\n", VarFixedBootID));
	FreeHiiData();

	{
		STRING_REF Strid=0;
		EFI_HII_UPDATE_DATA Update;
		
		if( gHiiString == NULL )
			Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, &gHiiString);

		if( pFBOHiiMap == NULL ) 
		{ 
			TRACE((-1,"pFBOHiiMap == NULL\n"));
			ASSERT(pFBOHiiMap);
		}

		if(!EFI_ERROR(Status)) 
		{
			UINT8 *IfrTempPtr,*OldIfrTempPtr = NULL;
			SETUP_DATA *pSetup=0;
			UINT16 i,j;

            OldIfrTempPtr = IfrTempPtr = Malloc(
                ( sizeof(EFI_IFR_ONE_OF)
                +sizeof(EFI_IFR_ONE_OF_OPTION)*(DevMapCount+1)  // include one disable option
                +sizeof(EFI_IFR_END) )
                *DevMapCount);
            if (IfrTempPtr == NULL)
            {
                TRACE((FBO_TRACE_LEVEL, "Error allocation memory for IFR\n"));
                ASSERT(IfrTempPtr);
            }
			Update.Data = IfrTempPtr;

			for(i=0;i<DevMapCount;i++)
			{
				UINT16 HiiMapIndex;

				if( pBootOptionTokenMap == NULL )                               //(EIP123284+)
				    Strid = HiiAddLanguageBootOptionString(HiiHandle, i+1);		//(EIP101408+)
				else                                                            //(EIP123284+)
                    Strid = pBootOptionTokenMap[i];                             //(EIP123284+)
				Status = CreateHiiOneOfItem( &IfrTempPtr, VarSetupID, (UINT16)&pSetup->DualPriorities[i], DualBootItemKey+i, Strid, STR_BOOT_OPTION_HELP, 0x11);

				for(j=0;j<DevMapCount;j++)
				{

					HiiMapIndex = SearchHiiMapByType( pFBODualDevMap[j].DevType );
					Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 1, j, pFBOHiiMap[HiiMapIndex].StrToken );
				}
#if FIXED_BOOT_INCLUDE_DISABLED_OPTION	
				Status = CreateHiiOneOfOptionItem( &IfrTempPtr, 1, DevMapCount, STR_DISABLED );
#endif
				CreateHiiIfrEndItem( &IfrTempPtr );
											//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
				RegHandle = NULL;
				if( AmiSetupProtocol != NULL )
					AmiSetupProtocol->RegisterCallback(FBO_STRING_INIT_FORM_SET_CLASS, 0, DualBootItemKey+i, FixedBootOrderFormCallBack, &RegHandle);
#endif
											//<(EIP103171+)
			}

			Update.Offset = (UINT32)((UINT8*)IfrTempPtr-(UINT8*)Update.Data);	//Calc Hii data length.
			TRACE((-1,"Update.Data...............\n"));
//			TraceOutData( (UINT8*)Update.Data, Update.Offset );	
					
			Status = IfrLibUpdateForm (
  					HiiHandle,
					NULL,
  					FBO_VFR_FORM_ID,
					FIXED_BOOT_ITEM_LABEL3,
  					TRUE,
  					&Update);

			TRACE((-1,"IfrLibUpdateForm (%r)\n", Status));

			pBS->FreePool( OldIfrTempPtr );
		}
	}	

	return EFI_SUCCESS;
}
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	load_default_string
//
// Description:	This function called after setup utility loaded config defaults
//		based on user input. change fixedbootorder display default 
//		devcie string.
//
// Input:
//
// Output:
//  EFI_STATUS
//
// Modified:
//      
// Referrals: 
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS load_default_string()
{
	TRACE((-1,"[FixedBootOrder.c]Load Default String\n"));
	LoadedDefault=TRUE;		//TRUE = Load default
	//Initial Legacy Device HiiString name.
	InitLegacyGroup();
	//Initial Uefi Device HiiString.
	InitUefiGroup();

	return EFI_SUCCESS;
}

static EFI_FIXED_BOOT_ORDER_SETUP_PROTOCOL gFixedBootOrderSetupProtocol =
{
    	load_default_string
};


VOID SetVarDefaults(CHAR16 *VarNames, UINT8 *pFixedBootGroup)
{
    EFI_STATUS  Status;
    UINT16      i, j;
    UINT32      Attr;
    UINTN       Size = 0, NameSize;
    EFI_GUID    DefaultsGuid = DEFAULTS_GUID;
    NVAR        *pDefaultsBuffer = NULL, *pNVAR;
    NVRAM_STORE_INFO    NvStore;
    EFI_GUID            gSetupGuid = SETUP_GUID;
    SETUP_DATA          *StdSetupData;
    FIXED_BOOT_SETUP    *FixedBootSetup;
    FIXED_BOOT_GROUP    *StdFixedBootGroup;
    UINT8*              p;
    BOOLEAN Update = FALSE;
    static BOOLEAN SetupOnce = FALSE;
    
    //Update variable Defaults data, use for load default.
    Status = GetEfiVariable(VarNames, &DefaultsGuid, &Attr, &Size, &pDefaultsBuffer);
    TRACE((-1, "[FixedBootOrder.c] GetEfiVariable(%S) %r\n", VarNames, Status));
    if(EFI_ERROR(Status))
        return;
    
    NvStore.NvramAddress = (UINT8*)pDefaultsBuffer;
    NvStore.NvramSize = Size;
    NvInitInfoBuffer(
        &NvStore,
        0,
        NVRAM_STORE_FLAG_NON_VALATILE
    );

    if(!SetupOnce)
    {
        pNVAR = (NVAR*)NvFindVariable(L"Setup",&gSetupGuid,&NameSize,&NvStore);
        if(pNVAR)
        {
            UINT16 DevCount = 0;
            SetupOnce = TRUE;
            StdSetupData = (SETUP_DATA*)NvGetData(pNVAR, NameSize, &Size, &NvStore);
            //(EIP107268+)>
#if USE_BCP_DEFAULT_PRIORITIES
            DevCount = GetDevMapDataCount(pFBOUefiDevMap);
            for (i = 0; i < DevCount; i++)
                StdSetupData->UefiPriorities[i] = StdSetupData->BcpDefaultUefiPriorities[i];    //(EIP115686+)

            DevCount = GetDevMapDataCount(pFBOLegacyDevMap);
            for (i = 0; i < DevCount; i++)
                StdSetupData->LegacyPriorities[i] = StdSetupData->BcpDefaultLegacyPriorities[i];  //(EIP115686+)
            //(EIP122146+)>
#if FBO_DUAL_MODE
            DevCount = GetDevMapDataCount(pFBODualDevMap);
            for (i = 0; i < DevCount; i++)
                StdSetupData->DualPriorities[i] = StdSetupData->BcpDefaultDualPriorities[i];
#endif
            //<(EIP122146+)
#else                                       //<(EIP107268+) 
            DevCount = GetDevMapDataCount(pFBOUefiDevMap);
            for (i = 0; i < DevCount; i++)
                StdSetupData->UefiPriorities[i] = (UINT16)i;

            DevCount = GetDevMapDataCount(pFBOLegacyDevMap);
            for (i = 0; i < DevCount; i++)
                StdSetupData->LegacyPriorities[i] = (UINT16)i;
#if FBO_DUAL_MODE
            DevCount = GetDevMapDataCount(pFBODualDevMap);
            for (i = 0; i < DevCount; i++)
                StdSetupData->DualPriorities[i] = (UINT16)i;
#endif

#endif  //#if USE_BCP_DEFAULT_PRIORITIES    //(EIP107268+)  
            Update = TRUE;

            // It's hard code in NVRam Driver, so we just hard code here.
            if (   (pNVAR->flags & NVRAM_FLAG_EXT_HEDER)
                && (*NvGetExtFlags(pNVAR) & NVRAM_EXT_FLAG_CHECKSUM) )
            {
                p = ((UINT8*)pNVAR) + pNVAR->size - 3;
                // Set CheckSum to 0 them Calculate it
                *p = 0;
                *p = NvCalculateNvarChecksum(pNVAR);
            }
        }
    }

    pNVAR = (NVAR*)NvFindVariable(L"FixedBoot",&gSetupGuid,&NameSize,&NvStore);
    if(pNVAR)
    {
        FixedBootSetup = (FIXED_BOOT_SETUP*)NvGetData(pNVAR, NameSize, &Size, &NvStore);
        for (i = 0; i < FIXED_BOOT_ORDER_GROUP_MAX_NUM; i++)
            for (j = 0; j < FIXED_BOOT_ORDER_SUBMENU_MAX_NUM; j++)
                FixedBootSetup->LegacyDevice[(i*FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)+j] = (UINT8)j;
        for (i = 0; i < FIXED_BOOT_ORDER_GROUP_MAX_NUM; i++)
            for (j = 0; j < FIXED_BOOT_ORDER_SUBMENU_MAX_NUM; j++)
                FixedBootSetup->UefiDevice[(i*FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)+j] = (UINT8)j;

        Update = TRUE;

        if (   (pNVAR->flags & NVRAM_FLAG_EXT_HEDER)
            && (*NvGetExtFlags(pNVAR) & NVRAM_EXT_FLAG_CHECKSUM) )
        {
            // It's hard code in NVRam Driver, so we just hard code here.
            p = ((UINT8*)pNVAR) + pNVAR->size - 3;
            // Set CheckSum to 0 them Calculate it
            *p = 0;
            *p = NvCalculateNvarChecksum(pNVAR);
        }
    }
    
    pNVAR = (NVAR*)NvFindVariable(L"FixedBootGroup",&gSetupGuid,&NameSize,&NvStore);
    if(pNVAR)
    {
        StdFixedBootGroup = (FIXED_BOOT_GROUP*)NvGetData(pNVAR, NameSize, &Size, &NvStore);
        pBS->CopyMem(StdFixedBootGroup, pFixedBootGroup, sizeof(FIXED_BOOT_GROUP));
        Update = TRUE;

        if (   (pNVAR->flags & NVRAM_FLAG_EXT_HEDER)
            && (*NvGetExtFlags(pNVAR) & NVRAM_EXT_FLAG_CHECKSUM) )
        {
            // It's hard code in NVRam Driver, so we just hard code here.
            p = ((UINT8*)pNVAR) + pNVAR->size - 3;
            // Set CheckSum to 0 them Calculate it
            *p = 0;
            *p = NvCalculateNvarChecksum(pNVAR);
        }
    }

    if (Update)
    {
        pRS->SetVariable(VarNames,
                         &DefaultsGuid,
                         Attr,
                         NvStore.NvramSize,
                         pDefaultsBuffer);
    }

    pBS->FreePool(pDefaultsBuffer);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:	FixedBootOrderStringInit
//
// Description:	Install a form callback.
//
// Input:
//  	IN EFI_HII_HANDLE 	HiiHandle
//	IN UINT16 		Class
//
// Output:
//
// Modified:
//      
// Referrals: SetupStringInit
//
// Notes:	
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FixedBootOrderStringInit(
  IN EFI_HII_HANDLE 	HiiHandle, 
  IN UINT16 		Class
)
{
#if CSM_SUPPORT
EFI_GUID gEfiLegacyBiosProtocolGuid = EFI_LEGACY_BIOS_PROTOCOL_GUID;
EFI_LEGACY_BIOS_PROTOCOL  *LegacyBios=NULL;
#endif
EFI_GUID gSetupGuid = SETUP_GUID;
EFI_STATUS Status = EFI_SUCCESS;
EFI_FIXED_BOOT_ORDER_PROTOCOL *pFBO=NULL;
FIXED_BOOT_GROUP FixedBootGroup;
UINT8 *pFixedBootGroup = (UINT8*)&FixedBootGroup;
UINT8 i,j;

    if (Class != FBO_STRING_INIT_FORM_SET_CLASS) return EFI_SUCCESS;
    
    pRS->SetVariable(
        	L"FixedBootOrderHii", 
	        &FixedBootOrderGuid,
	        EFI_VARIABLE_BOOTSERVICE_ACCESS,
	        sizeof(EFI_HII_HANDLE),
	        &HiiHandle);

	TRACE((-1,"FixedBootOrderStringInit HiiHanlde = %x\n", HiiHandle));
	FixedBoot_HiiHandle = HiiHandle;

#if CSM_SUPPORT
	Status = pBS->LocateProtocol( &gEfiLegacyBiosProtocolGuid, NULL, &LegacyBios );
	if(!EFI_ERROR(Status))
	{

		Status = LegacyBios->GetBbsInfo(LegacyBios, &HddCount, &HddInfo, &BbsCount, &BbsTable);
		if(EFI_ERROR(Status)) return Status;

        BbsDeviceName = MallocZ(BbsCount * (BBS_DEVICE_NAME_LENGTH+1));

        if( BbsDeviceName != NULL )
        {
            for(i=0; i<BbsCount ;i++)
            {
                UINT8 *BBSNamePtr = NULL;
               
                if( BbsTable[i].BootPriority == BBS_IGNORE_ENTRY ) continue;

                BBSNamePtr = (UINT8*)( ((UINTN)BbsTable[i].DescStringSegment << 4) 
                                             + BbsTable[i].DescStringOffset );

                if( BBSNamePtr != NULL )
                    pBS->CopyMem( &BbsDeviceName[i*(BBS_DEVICE_NAME_LENGTH+1)], BBSNamePtr, BBS_DEVICE_NAME_LENGTH);
            }
        }
	}
#endif
 	Status = pBS->LocateProtocol( &FixedBootOrderGuid, NULL, &pFBO );
	if(!EFI_ERROR(Status))
	{
		pFBOLegacyDevMap = pFBO->GetLegacyDevMap();
		pFBOUefiDevMap = pFBO->GetUefiDevMap();
		pFBODualDevMap = pFBO->GetDualDevMap();
		pFBOHiiMap = pFBO->GetHiiMap();
        FBO_AdjustGroupName() ;
                                //(EIP123284+)>
#if FBO_USE_BOOT_OPTION_NUMBER_UNI
		pBootOptionTokenMap = pFBO->GetBootOptionTokenMap();
#else
        pBootOptionTokenMap = NULL;
#endif
                                //<(EIP123284+)
	}

	pBS->SetMem( TypeLegacyDeviceCount, sizeof(TypeLegacyDeviceCount), 0);
	pBS->SetMem( TypeUefiDeviceCount, sizeof(TypeUefiDeviceCount), 0);
	pBS->SetMem( &FixedBootGroup, sizeof(FIXED_BOOT_GROUP), 0);
								//(EIP103171+)>
#if CORE_COMBINED_VERSION>=0x4028e
    Status = pBS->LocateProtocol(&AmiSetupProtocolGuid, NULL, &AmiSetupProtocol);
#endif
								//<(EIP103171+)		
	InitialLegacyHiiItem(HiiHandle);
	InitialUefiHiiItem(HiiHandle);
#if FBO_DUAL_MODE
	InitialDaulHiiItem(HiiHandle);
#endif
	//Initial Legacy Device HiiString name.
	InitLegacyGroup();
	//Initial Uefi Device HiiString.
	InitUefiGroup();

	{
		EFI_HANDLE Handle = NULL;
		EFI_GUID FixedBootOrderSetupGuid = FIXED_BOOT_ORDER_SETUP_GUID;

    		Status = pBS->InstallProtocolInterface (
             			&Handle,
             			&FixedBootOrderSetupGuid,
             			EFI_NATIVE_INTERFACE,
             			&gFixedBootOrderSetupProtocol);
	}

	//Set all types device count and set variable FixedBootGroup.
	{
		UINT16 DevMapCount;
		UINT16 HiiDevIndex;
		UINT16 DeviceCountOffset;


		DevMapCount = GetDevMapDataCount(pFBOLegacyDevMap);
		for(i=0;i<DevMapCount;i++)
		{
			HiiDevIndex = SearchHiiMapByType(pFBOLegacyDevMap[i].DevType);
			if(pFBOHiiMap[HiiDevIndex].FormID == 0) continue;	//no group submenu
			DeviceCountOffset = pFBOHiiMap[HiiDevIndex].DeviceCountOffset;
			pFixedBootGroup[DeviceCountOffset]=TypeLegacyDeviceCount[i];
		}

		DevMapCount = GetDevMapDataCount(pFBOUefiDevMap);
		for(i=0;i<DevMapCount;i++)
		{
			HiiDevIndex = SearchHiiMapByType(pFBOUefiDevMap[i].DevType);
			if(pFBOHiiMap[HiiDevIndex].FormID == 0) continue;	//no group submenu
			DeviceCountOffset = pFBOHiiMap[HiiDevIndex].DeviceCountOffset;
			pFixedBootGroup[DeviceCountOffset]=TypeUefiDeviceCount[i];
		}

    	pRS->SetVariable(
        		L"FixedBootGroup", 
	       		&gSetupGuid,
	       		BS_NV_VARIABLE_ATTRIBUTES,
	       		sizeof(FIXED_BOOT_GROUP),
	       		&FixedBootGroup);

		SetVarDefaults(L"StdDefaults",pFixedBootGroup);
		SetVarDefaults(L"MfgDefaults",pFixedBootGroup);
	}

    //Initial ALL "FixedBoot" data.
    {
		EFI_GUID gSetupGuid = SETUP_GUID;
		FIXED_BOOT_SETUP pFixedBoot;

        for (i = 0; i < FIXED_BOOT_ORDER_GROUP_MAX_NUM; i++)
            for (j = 0; j < FIXED_BOOT_ORDER_SUBMENU_MAX_NUM; j++)
                pFixedBoot.LegacyDevice[(i*FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)+j] = TypeLegacyDeviceOptions[i][j];
        for (i = 0; i < FIXED_BOOT_ORDER_GROUP_MAX_NUM; i++)
            for (j = 0; j < FIXED_BOOT_ORDER_SUBMENU_MAX_NUM; j++)
                pFixedBoot.UefiDevice[(i*FIXED_BOOT_ORDER_SUBMENU_MAX_NUM)+j] = TypeUefiDeviceOptions[i][j];

		Status = pRS->SetVariable(L"FixedBoot",
									&gSetupGuid, 
									BS_NV_VARIABLE_ATTRIBUTES,
									sizeof(pFixedBoot),
					  				&pFixedBoot);
    }
   	return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
