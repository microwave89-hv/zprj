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
// $Header: /Alaska/SOURCE/Modules/SMIFlash/SMIFlashLinks.c 52    4/11/16 9:22p Tristinchou $
//
// $Revision: 52 $
//
// $Date: 4/11/16 9:22p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMIFlash/SMIFlashLinks.c $
// 
// 52    4/11/16 9:22p Tristinchou
// [TAG]  		EIP261702
// [Category]  	Improvement
// [Description]  	Register event to get UsbRtKbcAccessControl()  function
// to disable keyboard
// 
// 51    4/07/15 2:52a Tristinchou
// [TAG]  		EIP211721
// [Category]  	Improvement
// [Description]  	Modify codes to call UsbRtKbcAccessControl() instead of
// using outside smm pointer.
// 
// 50    5/06/14 5:01a Calvinchen
// [TAG]  		EIP166597
// [Category]  	New Feature
// [Description]  	Removing RT from variables could cause problems
// accessing variables if PRESERVE_EFIBOOTORDER=1
// [Files]  		SMIFlash.chm
// SMIFlashLinks.c
// SMIFlash.cif
// 
// 49    3/10/14 2:44a Calvinchen
// [TAG]  		EIP156780
// [Category]  	Improvement
// [Description]  	Boot related variables preserving in Aptio 4 SmiFlash
// 
// 48    12/06/13 4:20a Calvinchen
// [TAG]  		EIP145305
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Variable Restored failed after re-flashing when Nvram is in
// Backup Area.
// [RootCause]  	NVRAM State is not restored after re-flashing.
// [Solution]  	Restore Nvram State.
// [Files]  		SMIFlash.sdl
// SMIFlash.chm
// SMIFlashLinks.c
// SMIFlash.cif
// 
// 47    12/20/12 8:52a Calvinchen
// [TAG]  		EIP103562
// [Category]  	Improvement
// [Description]  	Need a way to preserve debug policy NV+BS variable(
// WIN8 Logo requirement) in Nvram driver
// [Files]  		SMIFlashLinks.c
// 
// 46    12/06/12 4:56a Calvinchen
// [TAG]  		EIP106623
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	SmiFlash breaks build when NVRAM_BACKUP_ADDRESS is not
// defined.
// [RootCause]  	Smiflash don't remove the related procedures if
// FAULT_TOLERANT_NVRAM_UPDATE is disabled.
// [Solution]  	Remove the related procedures if
// FAULT_TOLERANT_NVRAM_UPDATE is disabled.
// [Files]  		SMIFlashLinks.c
// 
// 45    11/20/12 5:39a Calvinchen
// [TAG]  		EIP106623
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SmiFlash breaks build when FAULT_TOLERANT_NVRAM_UPDATE is
// disabled
// [RootCause]  	Smiflash don't remove the related procedures if
// FAULT_TOLERANT_NVRAM_UPDATE is disabled.
// [Solution]  	Remove the related procedures if
// FAULT_TOLERANT_NVRAM_UPDATE is disabled.
// [Files]  		SMIFlashLinks.c
// 
// 44    11/19/12 3:48a Calvinchen
// SmiFlash does not compile when CryptoPkg/Secure Boot Pkg/Secure Flash
// Pkg are not in the project.
// 
// 43    11/02/12 7:13a Calvinchen
// [TAG]  		EIP64328
// [Category]  	Improvement
// [Description]  	Improvement: 
//  1. (EIP64328) Update modules to be compliant with PI 1.2 and UEFI
// 2.3.1 specifications. 
// BugFix: 
//  1. (EIP100950) Fix the attribute of Win8 Debug Variable been changed
// after restored. 
//  2. (EIP98199) The #### in Boot#### should be upper case. 
// [Files]  		SMIFlash.mak
// SMIFlash.dxs
// SMIFlash.c
// SMIFlash.chm
// SMIFlashLinks.c
// SMIFlashDxe.dxs
// SMIFlash.cif
// 
// 41    7/13/12 2:14a Klzhan
// Fix : Backup Flag not clear property.
// 
// 4     7/02/12 3:45a Nerofan
// Update to version 36
// 
// 36    6/13/12 5:17a Klzhan
// [TAG]  		EIP92023
// [Category]  	Improvement
// [Description]  	Emulation SMI should be disabled before Read/Write
// 60/64 ports in smiflash.
// 
// 35    6/01/12 5:13a Klzhan
// Fix sometimes Deadloop when GetNextVariableName
// 
// 34    5/31/12 2:22a Klzhan
// Correct pointers.
// 
// 33    5/30/12 4:19a Klzhan
// Remove un-used GUID.
// 
// 32    5/29/12 5:45a Klzhan
// [TAG]  		EIP86878
// [Category]  	Improvement
// [Description]  	Restore SMBIOS data when recovery.
// [Files]  		SMIFlash.sdl
// SMIFlash.mak
// SMIFlash.dxs
// SMIFlash.c
// SMIFlash.chm
// SMIFlashLinks.c
// SMIFlash.cif
// 
// 31    5/25/12 6:26a Klzhan
// [TAG]  		EIP90325
// [Category]  	Improvement
// [Description]  	UEFI Compliant - Global Defined Variables test
// 
// 30    5/24/12 11:57p Klzhan
// Fix exception error after flash NVRAM.
// 
// 29    5/23/12 2:58a Klzhan
// [TAG]  		EIP81706
// [Category]  	Improvement
// [Description]  	Restore variables when recovery.
// 
// 28    5/22/12 4:43a Klzhan
// [TAG]  		EIP90325
// [Category]  	Improvement
// [Description]  	Fix : UEFI Compliant - Globally Defined Variables test
// fail
// 
// 27    5/22/12 3:09a Klzhan
// [TAG]  		EIP87892
// [Category]  	Improvement
// [Description]  	As Windows Logo requirment, need support to preserve
// all UEFI variables with VendorGuid {77fa9abd-0359-4d32-bd60-
// 28f4e78f784b} between flash updates
// 
// 26    5/22/12 3:00a Klzhan
// Set secure variables with authenticated Attributes.
// 
// 25    5/21/12 4:48a Klzhan
// Improvement : POST resetore only been called after AFU update.
// 
// 24    4/05/12 4:40a Klzhan
// BugFix : AFU will stop when SecureFlash is enabled.
// 
// 23    3/27/12 11:19p Klzhan
// [TAG]  		EIP86161
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Build Error when X64_BUILD = 0
// 
// 22    3/14/12 6:59a Klzhan
// Remove un-use code
// 
// 21    3/09/12 1:02a Klzhan
// Fix variables not been restored property.
// 
// 20    3/06/12 3:01a Klzhan
// Improvement :
// Support restore secure variables in POST.
// 
// 19    2/10/12 7:14a Klzhan
// Support NCB blocks updated with secure flash updated.
// 
// 18    2/07/12 3:05a Klzhan
// BugFIx : Fix erase size not correct.
// 
// 17    2/06/12 3:27a Klzhan
// [TAG]  		EIP80781
// [Category]  	Improvement
// [Description]  	Support OA key in NCB updated when Scure Flash Enabled
// 
// 15    11/23/11 3:39a Calvinchen
// [TAG]  		EIP54533
// [Category]  	Improvement
// [Description]  	1. Removed BiosLockEnablePatchHook hook. Moved to
// Chipset file. 
// 2. Also enable/disable PS2 keyboard in Enable/DisableUSBKBD hook. 
// 3. (EIP54533) Request for afu capable updating OEM firmware volumes 
// [Files]  		SMIFlash.sdl
// SMIFlash.mak
// SMIFlash.chm
// SMIFlashLinks.c
// 
// 14    11/03/11 7:09a Klzhan
// [TAG]  		EIP73027
// [Category]  	Improvement
// [Description]  	Avoid un-inital variable used.
// 
// 13    10/31/11 11:07p Klzhan
// [TAG]  		EIP73017
// [Category]  	Improvement
// [Description]  	SavedBootXXX, conditionally not set.
// 
// 12    5/18/11 6:03a Klzhan
// BugFix : Memory will be crashed, free memory property.
// 
// 11    5/17/11 3:23a Klzhan
// Add Elinks to read buffer form shadow.
// 
// 10    5/16/11 4:03a Klzhan
// [TAG]  		EIP35562
// [Category]  	Improvement
// [Description]  	Boot#### variable,the #### should be upper case of A-F.
// [Files]  		SMIFlahElinks.c
// 
// 9     5/05/11 3:05a Klzhan
// 
// 8     4/26/11 6:07a Calvinchen
// [TAG]  		EIP58402
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	AFUxxx flash utility hangs when Bootxxxx variable size is
// greater than 0x200
// [RootCause]  	The size of Boot0003 variable in the customer's project
// is 0x242 bytes, which causes the memory corruption.
// [Solution]  	Used allocate smm buffer instead of static structure.
// [Files]  		SMIFlashLinks.c
// 
// 6     3/23/11 4:44a Calvinchen
// [TAG]  		EIP53067
// [Category]  	Improvement
// [Description]  	Modified for OEM Secure BIOS Update Requirements.
// [Files]  		SMIFlash.sdl
// SMIFlash.mak
// SMIFlash.dxs
// SMIFlash.c
// SMIFlash.chm
// SMIFlashLinks.c
// SMIFlash.cif
// 
// 5     12/14/10 4:38a Klzhan
// [TAG]  		EIP49217
// [Category]  	Improvement
// [Description]  	Preserve BOOTxxxx for all EFI OS.
// [Files]  		SMIFlashLinks.c
// 
// 4     12/14/10 4:18a Klzhan
// Move Locate USB Protocol to SMIFlashLinks.c.
// 
// 3     12/14/10 3:49a Klzhan
// Improvement : check is ROM layout changed before update NVRAM.
// 
// 2     12/14/10 1:18a Klzhan
// Remove debug codes.
// 
// 1     12/14/10 1:15a Klzhan
// Improvement : Move ELinks to SMIFlashLinks.c.
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    SMIFlashLinks.c
//
// Description: Elinks to SMIFlash.
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol\SmiFlash.h>
#include <Setup.h>
#include <Protocol\FlashProtocol.h>
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
#include <Protocol\AmiUsbController.h>
#endif
#endif

#include <RomLayout.h>
#include <Flash.h>
#include <AmiHobs.h>
#include <Core\EM\NVRAM\NVRam.h>
#include <ImageAuthentication.h>
#include <Protocol\FlashProtocol.h>
#include "timestamp.h"
//----------------------------------------------------------------------
// component MACROs
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID gEfiCertTypePkcs7Guid = EFI_CERT_TYPE_PKCS7_GUID;

//----------------------------------------------------------------------
// Module defined global variables
extern FLASH_PROTOCOL *Flash;
//*********** INSIDE SMM ***********************************************
#if !defined _OUTSIDE_SMM_

extern ROM_AREA RomLayout[];
extern VOID ChipsetFlashDeviceWriteEnable();

EFI_GUID RecoveryPreserveGUID[] = 
{
    { 0x05ca01fc, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca01fd, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca01fe, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca01ff, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0200, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0201, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0202, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0203, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0204, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0205, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0206, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0207, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0208, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca0209, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca020a, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    { 0x05ca020b, 0x0fc1, 0x11dc, 0x90, 0x11, 0x00, 0x17, 0x31, 0x53, 0xeb, 0xa8 },
    PRESERVE_FFS_GUID
    {NULL}
};

//----------------------------------------------------------------------
// Module specific global variable
#define ROM_LAYOUT_FFS_GUID \
    { 0x0DCA793A, 0xEA96, 0x42d8, 0xBD, 0x7B, 0xDC, 0x7F, 0x68, 0x4E, 0x38, 0xC1 }
#define AMITSESETUP_GUID \
 { 0xc811fa38, 0x42c8, 0x4579, 0xa9, 0xbb, 0x60, 0xe9, 0x4e, 0xdd, 0xfb, 0x34 }
#define WIN8_GUID \
 { 0x77FA9ABD, 0x0359, 0x4D32, 0xBD, 0x60, 0x28, 0xF4, 0xE7, 0x8F, 0x78, 0x4B }
EFI_GUID gWin8Guid = WIN8_GUID;
#define  DefaultVariableSize 100

EFI_GUID gAmiTseSetupGuid = AMITSESETUP_GUID;
AMITSESETUP gAmiTseData;
UINT32      gAmiTseDataAttr = 0;

#pragma pack(1)
typedef struct {
    CHAR16 BootVarName[0x20];
    UINT16 BootOrderNO;
    UINTN  BootXXXXSize;
//-    UINT8  *BootXXXX;
} RESTORE_BOOTORDER;
EFI_PHYSICAL_ADDRESS    gSmmBootOrder = NULL;
UINT8                   gNumBootDevice = 0;
#define RESTORE_BOOT_ORDER_BUFFER  0x4000
#define BOOT_ORDER_OFFSET          (RESTORE_BOOT_ORDER_BUFFER - 0x100)
#define LEGACY_BOOT_ORDER_OFFSET   (RESTORE_BOOT_ORDER_BUFFER - 0x200)

typedef struct {
    CHAR16     *BootVarName;
    EFI_GUID   *Guid;
} RESTORE_VARIABLES;

typedef struct {
    UINT32     Attrib;
    UINTN      Size;
    UINT8*     Data;
} RESTORE_ATTR;

typedef struct {
    RESTORE_VARIABLES rVar;
    RESTORE_ATTR      rATTR;
    UINTN             NextData;
} RESTORE_VAR;
#pragma pack()
RESTORE_VAR   *RestoreVarList;
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
EFI_KBC_ACCESS_CONTROL gUsbRtKbcAccessControl = NULL;
#endif
#endif

#define EFI_IMAGE_SECURITY_DATABASE       L"db"
#define EFI_IMAGE_SECURITY_DATABASE1      L"dbx"
#define EFI_PLATFORM_KEY_NAME             L"PK"
#define EFI_KEY_EXCHANGE_KEY_NAME         L"KEK"

EFI_GUID PKeyFileGuid  = EFI_GLOBAL_VARIABLE;
EFI_GUID KekFileGuid  = EFI_GLOBAL_VARIABLE;
EFI_GUID DbFileGuid  =  EFI_IMAGE_SECURITY_DATABASE_GUID;
EFI_GUID DbxFileGuid  =  EFI_IMAGE_SECURITY_DATABASE_GUID;

//-VOID CheckNVRAMArea(VOID);
EFI_FFS_FILE_STATE NvramFFSState;
EFI_FFS_FILE_STATE *NvramFFSStatePtr;

RESTORE_VARIABLES RestoreVariables[] = {
{EFI_IMAGE_SECURITY_DATABASE1, &DbxFileGuid},
{EFI_IMAGE_SECURITY_DATABASE, &DbFileGuid},
{EFI_KEY_EXCHANGE_KEY_NAME, &KekFileGuid},
{EFI_PLATFORM_KEY_NAME, &PKeyFileGuid},
{NULL,NULL}
};

#define NUM_OF_RESTORE_VARS (sizeof(RestoreVariables)/sizeof(RESTORE_VARIABLES))

#ifndef EFI_VARIABLE_AUTHENTICATION_2
typedef struct {
    EFI_TIME                            TimeStamp;
    WIN_CERTIFICATE_UEFI_GUID           AuthInfo;
} EFI_VARIABLE_AUTHENTICATION_2;
#endif

static EFI_TIME EfiTimeStamp = {
    FOUR_DIGIT_YEAR_INT, 
    TWO_DIGIT_MONTH_INT, 
    TWO_DIGIT_DAY_INT, 
    TWO_DIGIT_HOUR_INT, 
    TWO_DIGIT_MINUTE_INT, 
    TWO_DIGIT_SECOND_INT,0,0,0,0,0};

RESTORE_ATTR RestoreAttr[NUM_OF_RESTORE_VARS - 1];

// SMM Nvram Control Protocol Definitions
typedef EFI_STATUS (*SHOW_BOOT_TIME_VARIABLES)(BOOLEAN Show);
typedef struct{
    SHOW_BOOT_TIME_VARIABLES ShowBootTimeVariables;
} AMI_NVRAM_CONTROL_PROTOCOL;

AMI_NVRAM_CONTROL_PROTOCOL *LocateNvramControlSmmProtocol(){
    static EFI_GUID gAmiNvramControlProtocolGuid = { 0xf7ca7568, 0x5a09, 0x4d2c, { 0x8a, 0x9b, 0x75, 0x84, 0x68, 0x59, 0x2a, 0xe2 } };
    return GetSmstConfigurationTable(&gAmiNvramControlProtocolGuid);
}
AMI_NVRAM_CONTROL_PROTOCOL *gNvramControl = NULL;
//----------------------------------------------------------------------
// externally defined variables
//----------------------------------------------------------------------
// Function definitions
// BIT00 = 1 --> Update NVRAM
// BIT01 = 1 --> Update NVRAM Backup Address
UINT8  UpdateNVram = 0;
UINT64 BufAddr;
UINT8  FFSState;
#if FAULT_TOLERANT_NVRAM_UPDATE
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   MoveNVRamToAnotherRegion
//
// Description: Copy current NVRAM to another NBRAM region
//              
//
// Input:       Data            - SW SMI value number
//              pInfoBlock      - AFU Data Buffer
//
// Output:      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
MoveNVRamToAnotherRegion
(
    VOID
)
{
    // Move NVRam to another Region
    // We can keep secure variables
    EFI_STATUS  Status;
    UINT32  UpdateAddress, SourceAddress, i, Buffer32;
    UINTN                  NumberOfPages;
    EFI_PHYSICAL_ADDRESS   Phy_Address;
    UINT8*                 Buffer;

    if(UpdateNVram & BIT00)
    {
        UpdateAddress = NVRAM_BACKUP_ADDRESS;
        SourceAddress = NVRAM_ADDRESS;
    }
    else
    {
        UpdateAddress = NVRAM_ADDRESS;
        SourceAddress = NVRAM_BACKUP_ADDRESS;
    }
    NumberOfPages = ((NVRAM_SIZE) >> 12);
    Status = pSmst->SmmAllocatePages(AllocateAnyPages, 
             EfiRuntimeServicesData, NumberOfPages, &Phy_Address);

    Flash->Erase((UINT8*)UpdateAddress, NVRAM_SIZE);
    if(!EFI_ERROR(Status))
    {
        Buffer = (UINT8*)Phy_Address;
        Flash->Read(
              (UINT8*)(SourceAddress), NVRAM_SIZE, Buffer);

        Flash->Write(
              (UINT8*)(UpdateAddress), NVRAM_SIZE, Buffer);

        pSmst->SmmFreePages(Phy_Address, NumberOfPages);
    }else
    {
        // If no memory , just do it 4 bytes one time.
        for(i = 0; i < NVRAM_SIZE ; i += sizeof(UINT32))
        {
            Flash->Read(
                  (UINT8*)(SourceAddress + i), sizeof(UINT32), &Buffer32);
            if(Buffer32 == 0xFFFFFFFF)
                continue;
            Flash->Write(
                  (UINT8*)(UpdateAddress + i), sizeof(UINT32), &Buffer32);
        }
    }
        
}
#endif  // #if FAULT_TOLERANT_NVRAM_UPDATE
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   ClearFFSState
//
// Description: Clear FFS State of Buffer
//              
//
// Input:       Data            - SW SMI value number
//              pInfoBlock      - AFU Data Buffer
//
// Output:      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearFFSState(
	UINT8		Data,
	UINT64		pInfoBlock
)
{
    FUNC_BLOCK     *pFuncBuff = (FUNC_BLOCK*)pInfoBlock;
    UINT32         FlashAddress;

    FlashAddress = (pFuncBuff->BlockAddr + (0xFFFFFFFF - FLASH_SIZE + 1));
    // Runs in Main Address, clear FFSState
    // if power-off while update, system runs in Backup address
    if((Data == SMIFLASH_WRITE_FLASH) && (FlashAddress == NVRAM_ADDRESS))
    {
        BufAddr = pFuncBuff->BufAddr;
        FFSState = *(UINT8*)(pFuncBuff->BufAddr + 0x5F);
        *(UINT8*)(pFuncBuff->BufAddr + 0x5F) = 0xFF;
    }
}
#if FAULT_TOLERANT_NVRAM_UPDATE
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreSecureVariablesPreHandler
//
// Description: Clear and Set FFS state when NVRAM region updated
//              
//
// Input:       Data            - SW SMI value number
//              pInfoBlock      - AFU Data Buffer
//
// Output:      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreSecureVariablesPreHandler(
	UINT8		Data,
	UINT64		pInfoBlock
)
{
    FUNC_BLOCK     *pFuncBuff = (FUNC_BLOCK*)pInfoBlock;
    UINT32         FlashAddress;
    static BOOLEAN InitDone = FALSE, RunInMain = FALSE;

    if((Data != SMIFLASH_ERASE_FLASH) && 
       (Data != SMIFLASH_WRITE_FLASH) && 
       (Data != SMIFLASH_READ_FLASH))
        return;

    FlashAddress = (pFuncBuff->BlockAddr + (0xFFFFFFFF - FLASH_SIZE + 1));
    if((FlashAddress < NVRAM_ADDRESS) || 
       (FlashAddress >= NVRAM_ADDRESS + NVRAM_SIZE))
        return;

    if(!InitDone)
    {
        NVRAM_STORE_INFO MainNvram;
        BOOLEAN    BackupStoreValid;
        VOID *BackupNvramAddress = (VOID*)NVRAM_BACKUP_ADDRESS;


        MainNvram.NvramAddress = (UINT8*)NVRAM_ADDRESS;
        MainNvram.NvramSize = NVRAM_SIZE;
        if (!IsMainNvramStoreValid(&MainNvram, BackupNvramAddress,&BackupStoreValid)){
            if (BackupStoreValid)
                RunInMain = FALSE;
        }else
            RunInMain = TRUE;

        InitDone = TRUE;
    }

    // NVRam runs in NVRAM address
    if(RunInMain)
    {
        UpdateNVram |= BIT00;
    }else
    {
        if(NVRAM_ADDRESS > NVRAM_BACKUP_ADDRESS)
            pFuncBuff->BlockAddr -= (NVRAM_ADDRESS - NVRAM_BACKUP_ADDRESS);
        else
            pFuncBuff->BlockAddr += (NVRAM_BACKUP_ADDRESS - NVRAM_ADDRESS);

        UpdateNVram |= BIT01;
    }

    // Frist in, move current NVRam to another
    if((Data == SMIFLASH_ERASE_FLASH) && (FlashAddress == NVRAM_ADDRESS))
        MoveNVRamToAnotherRegion();

    // Runs in Main Address, clear FFSState
    // if power-off while update, system runs in Backup address
    if((Data == SMIFLASH_WRITE_FLASH) && (FlashAddress == NVRAM_ADDRESS))
        *(UINT8*)(pFuncBuff->BufAddr + 0x5F) = 0xFF;
    
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreSecureVariablesEndHandler
//
// Description: Clear and Set FFS state when NVRAM region updated
//              
//
// Input:       Data            - SW SMI value number
//              pInfoBlock      - AFU Data Buffer
//
// Output:      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreSecureVariablesEndHandler(
	UINT8		Data,
	UINT64		pInfoBlock
)
{
    FUNC_BLOCK     *pFuncBuff = (FUNC_BLOCK*)pInfoBlock;
    UINT32         FlashAddress, EndNVRamAddress, TempNVRamAddress;
    UINT8          Buffer8 = 0x08;

    if(Data != SMIFLASH_WRITE_FLASH)
        return;

    switch(UpdateNVram)
    {
        case 1:
            EndNVRamAddress = NVRAM_ADDRESS + NVRAM_SIZE;
            TempNVRamAddress = NVRAM_BACKUP_ADDRESS;
            break;
        case 2:
            EndNVRamAddress = NVRAM_BACKUP_ADDRESS + NVRAM_SIZE;
            TempNVRamAddress = NVRAM_ADDRESS;
            break;
        default:
            return;
    }

    FlashAddress = (pFuncBuff->BlockAddr + (0xFFFFFFFF - FLASH_SIZE + 1));
    if(FlashAddress == NVRAM_ADDRESS)
        *(UINT8*)(BufAddr + 0x5F) = FFSState;

    if((FlashAddress + pFuncBuff->BlockSize) != EndNVRamAddress)
        return;

    // Clear State
    Flash->Write((UINT8*)(TempNVRamAddress + 0x5F),
                                            sizeof(UINT8), &Buffer8);

    Buffer8 = 0xF8;
    // Set State
    Flash->Write((UINT8*)(EndNVRamAddress - NVRAM_SIZE + 0x5F),
                                            sizeof(UINT8), &Buffer8);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PostRestoreVariables
//
// Description: Find Variables want to restore and restore then
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
PostRestoreVariables(
    VOID
)
{
    NVRAM_STORE_INFO pInfo; 
    UINTN HeaderSize = 0x60, i; 
    UINT8 Flags = NVRAM_STORE_FLAG_NON_VALATILE;
    EFI_STATUS  Status;
    NVRAM_STORE_INFO MainNvram;
    BOOLEAN    BackupStoreValid, RunInMain, ClearFlag = FALSE;
    VOID *BackupNvramAddress = (VOID*)NVRAM_BACKUP_ADDRESS;
    UINT8                           Buffer8 = 0x08;
    EFI_VARIABLE_AUTHENTICATION_2   *AuthHdr2;
    UINTN                           VarSize;

    for(i = 0 ; i < (NUM_OF_RESTORE_VARS - 1) ; i ++)
    {
        RestoreAttr[i].Size = 0;
        Status = pRS->GetVariable(RestoreVariables[i].BootVarName,
                                  RestoreVariables[i].Guid,
                                  &RestoreAttr[i].Attrib,
                                  &RestoreAttr[i].Size,
                                  NULL);
        // EFI_BUFFER_TOO_SMALL means variable exists
        if(Status != EFI_BUFFER_TOO_SMALL)
            break;
    }

    // All secure variable exist, return
    if(i == (NUM_OF_RESTORE_VARS - 1))
        ClearFlag = TRUE;


    VERIFY_EFI_ERROR(pBS->LocateProtocol(&gFlashProtocolGuid,
                                                 NULL, &Flash));
    // Check current running region
    MainNvram.NvramAddress = (UINT8*)NVRAM_ADDRESS;
    MainNvram.NvramSize = NVRAM_SIZE;
    if (!IsMainNvramStoreValid(&MainNvram, BackupNvramAddress,&BackupStoreValid)){
        if (BackupStoreValid)
            RunInMain = FALSE;
    }else
        RunInMain = TRUE;

    if(RunInMain)
    {

        pInfo.NvramAddress = (UINT8*)NVRAM_BACKUP_ADDRESS;
        // NVRAM update successful, but variables not restored yet.
        if(*(pInfo.NvramAddress + 0x5F) == 0xF8)
        {
            Flash->DeviceWriteEnable();
            Flash->Write((UINT8*)(pInfo.NvramAddress + 0x5F),
                                            sizeof(UINT8), &Buffer8);
            Flash->DeviceWriteDisable();
        }
    }
    else
        pInfo.NvramAddress = (UINT8*)NVRAM_ADDRESS;

    // FFS State is 8 mneas AFU update NVRAM but variables not been restored
    if(*(pInfo.NvramAddress + 0x5F) != 0x08)
        return;

    pInfo.NvramSize = NVRAM_SIZE;
    NvInitInfoBuffer(&pInfo, HeaderSize, Flags);

    for( ; i < (NUM_OF_RESTORE_VARS - 1) && !ClearFlag ; i ++)
    {

        RestoreAttr[i].Size = 0;
        Status = NvGetVariable2(RestoreVariables[i].BootVarName,
                                RestoreVariables[i].Guid,
                                &RestoreAttr[i].Attrib,
                                &RestoreAttr[i].Size,
                                NULL,
                                1,
                                &pInfo);

        // It should be happened on frist few boots
        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            UINT8*     DataBuffer = NULL;

            VarSize = RestoreAttr[i].Size + sizeof(EFI_VARIABLE_AUTHENTICATION_2);

            Status = pBS->AllocatePool (EfiBootServicesData,
                          VarSize,
                          (VOID**)&DataBuffer);

            Status = NvGetVariable2(RestoreVariables[i].BootVarName,
                                    RestoreVariables[i].Guid,
                                    &RestoreAttr[i].Attrib,
                                    &RestoreAttr[i].Size,
                                    DataBuffer + sizeof(EFI_VARIABLE_AUTHENTICATION_2),
                                    1,
                                    &pInfo);

            AuthHdr2 = (EFI_VARIABLE_AUTHENTICATION_2*)DataBuffer;
            MemCpy (&AuthHdr2->TimeStamp, &EfiTimeStamp, sizeof (EFI_TIME));
            AuthHdr2->AuthInfo.Hdr.dwLength = sizeof(WIN_CERTIFICATE_UEFI_GUID);
            AuthHdr2->AuthInfo.Hdr.wRevision = 0x200;
            AuthHdr2->AuthInfo.Hdr.wCertificateType = WIN_CERT_TYPE_EFI_GUID;
            AuthHdr2->AuthInfo.CertType = gEfiCertTypePkcs7Guid;

            if (!EFI_ERROR(Status)) {
                Status = pRS->SetVariable (  RestoreVariables[i].BootVarName,
                                             RestoreVariables[i].Guid,
                                             RestoreAttr[i].Attrib | \
                                             EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS,
                                             VarSize,
                                             DataBuffer);
                pBS->FreePool (DataBuffer);
            }
            
        }
    }
    Buffer8 = 0;
    Flash->DeviceWriteEnable();
    Flash->Write((UINT8*)(pInfo.NvramAddress + 0x5F),
                                    sizeof(UINT8), &Buffer8);
    Flash->DeviceWriteDisable();
}
#endif  // #if FAULT_TOLERANT_NVRAM_UPDATE
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   NCBUpdate
//
// Description: Support All NCBs updated when enable secure Flash Support
//              
//
// Input:       SwSmiNum    - SW SMI value number
//              Buffer      - Flash descriptor address
//
// Output:      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID NCBUpdate(
	UINT8		Data,
	UINT64		pInfoBlock
)
{
    FUNC_BLOCK     *pFuncBuff = (FUNC_BLOCK*)pInfoBlock;
    EFI_STATUS     Status;
    UINT8          *FlashAddress;
    static BOOLEAN BeforeSecure = FALSE;
    ROM_AREA       *Area;

    if(BeforeSecure)
    {
        BeforeSecure = FALSE;
        pFuncBuff->ErrorCode = 0;
        return;
    }

    if((Data != SMIFLASH_ERASE_FLASH) && (Data != SMIFLASH_WRITE_FLASH))
        return;

    FlashAddress = (UINT8*)(UINTN)(pFuncBuff->BlockAddr +
                                (0xFFFFFFFF - FLASH_SIZE + 1));
    for (Area = RomLayout; Area->Size != 0; Area++) {

        if(Area->Type != RomAreaTypeRaw)
            continue;

        if(((UINT32)FlashAddress >= Area->Address) &&
           ((UINT32)FlashAddress < (Area->Address + Area->Size)))
        {
            if(Data == 0x22)
            {
                Status = Flash->Erase(FlashAddress, FLASH_BLOCK_SIZE);
                pFuncBuff->ErrorCode = EFI_ERROR(Status) != 0;
                BeforeSecure = TRUE;
            }
            if(Data == 0x23)
            {
                Status = Flash->Write(FlashAddress, pFuncBuff->BlockSize, 
                                      (UINT8*)pFuncBuff->BufAddr);
                pFuncBuff->ErrorCode = EFI_ERROR(Status) != 0;
                BeforeSecure = TRUE;
            }
        }
    }
}
#if REPORT_NCB_BY_ROM_LAYOUT
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   ReassignNcbByRomLayout
//
// Description: Re-assign NCBs Type Id by ROM Layout definition for 
//              separating NCBs. 
//
// Input:       SwSmiNum    - SW SMI value number
//              Buffer      - Flash descriptor address
//
// Output:      None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
ReassignNcbByRomLayout (
    IN UINT8            SwSmiNum,
    IN UINT64           Buffer
)
{    
    BLOCK_DESC      *BlockDesc;
    ROM_AREA        *Area;
    UINT16          i, j, LastNcb;
    UINT8           NCBTypeId = NC_BLOCK;
    
    // return if SW SMI value is not "Get Flash Info"
    if (SwSmiNum != SMIFLASH_GET_FLASH_INFO) return;
        
    BlockDesc = (BLOCK_DESC*)&((INFO_BLOCK*)Buffer)->Blocks;
    for (i = 0, LastNcb = 0xffff; i < ((INFO_BLOCK*)Buffer)->TotalBlocks; i++) {
        if (BlockDesc[i].Type < NC_BLOCK) continue;
        // check whether NCB is described in RomLayout.    
        for (Area = RomLayout; Area->Size != 0; Area++) {
            if (BlockDesc[i].StartAddress != \
                    (UINT32)(Area->Address - FlashDeviceBase)) continue;
            for (j = 0, NCBTypeId++; j < (Area->Size / FlashBlockSize); j++) {
                BlockDesc[i + j].Type = NCBTypeId;
            }
            i += ((Area->Size / FLASH_BLOCK_SIZE) - 1);
            break;
        }
        // if this NCB isn't describe in RomLayout
        if (Area->Size == 0) {
            if (i != (LastNcb + 1)) NCBTypeId++;
            BlockDesc[i].Type = NCBTypeId;
        }    
        LastNcb = i;
    }
}
#endif // #if REPORT_NCB_BY_ROM_LAYOUT

#ifdef FAULT_TOLERANT_NVRAM_UPDATE
#if FAULT_TOLERANT_NVRAM_UPDATE == 1 && BACKUP_NVRAM_WHEN_FLASH == 0
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetNvramMainFFSStats
//
// Description: Get NVRAM Main FFS state.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_FFS_FILE_STATE*
GetNvramMainFFSStats(
    VOID
)
{
    EFI_FFS_FILE_HEADER *FfsFileHeader;
    EFI_FIRMWARE_VOLUME_HEADER *FwVolHeader;
    
    FwVolHeader = (EFI_FIRMWARE_VOLUME_HEADER *)NVRAM_ADDRESS;
    
    if (FwVolHeader->FvLength == NVRAM_SIZE)
    {
        FfsFileHeader = (EFI_FFS_FILE_HEADER *)(
                            NVRAM_ADDRESS + FwVolHeader->HeaderLength
                        );
        return &FfsFileHeader->State;
    }else
        return NULL;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   CheckNVRAMArea
//
// Description: Check NVRam FFS state.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
CheckNVRAMArea(
    VOID
)
{
    NvramFFSState = *GetNvramMainFFSStats();
    NvramFFSStatePtr = GetNvramMainFFSStats();
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   NVRAMChanged
//
// Description: Check Location of NVRAM region.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     TRUE - Location of NVRAM been changed.
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
NVRAMChanged(
    VOID
)
{
    UINTN FVSignOffset = 0x28, NVRAMRegion = NVRAM_ADDRESS;
    UINT32 FVSig;

    // Check NVRAM_ADDRESS still NVRAM region
    // Can we find signature ??
    Flash->Read((UINT8*)(NVRAMRegion + FVSignOffset),sizeof(FVSig), &FVSig);
    if (FVSig != FV_SIGNATURE) return TRUE;

    // The first Data is NVAR ??
    // Simple verify.
    Flash->Read((UINT8*)(NVRAMRegion + NVRAM_HEADER_SIZE),sizeof(FVSig), &FVSig);
    if ((FVSig != 'RAVN') && (FVSig != 'NVAR')) return TRUE;
    return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   UpdateNVRAMArea
//
// Description: If NVRam updated and current NVRam runs at Backup address.
//              also update NVRAM Backup address.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
UpdateNVRAMArea(
    VOID
)
{
    UINT32              i = 0, Buffer32 = 0;
    UINT8*              Buffer;
    EFI_FFS_FILE_STATE  NewNVRamFFSState;
    EFI_STATUS          Status;
    UINTN               NumberOfPages;
    EFI_PHYSICAL_ADDRESS   Phy_Address;

    // Check NVRAM_ADDRESS FFS State
    // If Status changed.
    // Then, we got an NVRAM area update
    // and current NVRam working at NVRAM_BACKUP_ADDRESS!!
    // So move the NVRAM_MAIN to NVRAM_BACKUP and Restore NVRAM_MAIN State.
    Flash->Read((UINT8*)NvramFFSStatePtr, 
                sizeof(EFI_FFS_FILE_STATE), &NewNVRamFFSState);
    // Before update FFSState to new NVRAM, check ROMLAYOUT changed or not.
    if(NVRAMChanged())
        return;
    if((NvramFFSState == NewNVRamFFSState) || (NvramFFSState == 0))
        return;
    NumberOfPages = ((NVRAM_SIZE) >> 12);
    Status = pSmst->SmmAllocatePages(AllocateAnyPages, EfiRuntimeServicesData, NumberOfPages, &Phy_Address);

    // NVRAM updated !!
    // Move NVRAM Main to NVRAM Backup
    Flash->Erase((UINT8*)NVRAM_BACKUP_ADDRESS, NVRAM_SIZE);
    // For AMD chipset workaround !!
    // AMD SPI can't read SPI ROM as buffer.
    if(!EFI_ERROR(Status))
    {
        Buffer = (UINT8*)Phy_Address;
        Flash->Read(
              (UINT8*)(NVRAM_ADDRESS), NVRAM_SIZE, Buffer);

        Flash->Write(
              (UINT8*)(NVRAM_BACKUP_ADDRESS), NVRAM_SIZE, Buffer);
    
        pSmst->SmmFreePages(Phy_Address, NumberOfPages);

    }else
    {
        // If no memory , just do it 4 bytes one time.
        for(; i < NVRAM_SIZE ; i += sizeof(UINT32))
        {
            Flash->Read(
                  (UINT8*)(NVRAM_ADDRESS + i), sizeof(UINT32), &Buffer32);
            if(Buffer32 == 0xFFFFFFFF)
                continue;
            Flash->Write(
                  (UINT8*)(NVRAM_BACKUP_ADDRESS + i), sizeof(UINT32), &Buffer32);
        }
    }
    // Restore NVRAM Main FFS state!!
    Flash->Write((UINT8*)NvramFFSStatePtr,
                 sizeof(EFI_FFS_FILE_STATE),&NvramFFSState);
}
#endif
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveEfiBootOrders
//
// Description: Save the BootXXXX contains "Windows Boot Manager"
//              For EFI OS.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreserveEfiBootOrders(VOID)
{

    UINTN               BootOrderSize, LegacyOrderSize;
    EFI_STATUS          Status;
    EFI_GUID            EfiVariableGuid = EFI_GLOBAL_VARIABLE;
    EFI_GUID            LegacyDevOrderGuid = LEGACY_DEV_ORDER_GUID;
    RESTORE_BOOTORDER   *SavedBootXXX;
    UINT8               i;
    UINT16              *BootOrder, *LegacyOrder;

    // Get BootOrder for restore
    if (gSmmBootOrder == NULL) {
        Status = pSmst->SmmAllocatePages ( AllocateAnyPages, \
                                           0, \
                                           RESTORE_BOOT_ORDER_BUFFER >> 12, \
                                           &gSmmBootOrder);
        if (EFI_ERROR(Status)) return ;
        SavedBootXXX = (RESTORE_BOOTORDER*)gSmmBootOrder;
        BootOrder = (UINT16*)(gSmmBootOrder + BOOT_ORDER_OFFSET);
    } else return;

    // Get BootOrder variable size
    BootOrderSize = 0;
    Status = pRS->GetVariable(L"BootOrder",&EfiVariableGuid, \
                                         NULL,&BootOrderSize, NULL);
    if(Status != EFI_NOT_FOUND)
    {
        Status = pRS->GetVariable(L"BootOrder", &EfiVariableGuid, \
                                        NULL, &BootOrderSize, BootOrder);
        if(EFI_ERROR(Status)) return;
            
    } else return; // If BootOrder is not found, just return

    // Due to the "RT" attribute could be removed from LegacyDevOreder variable,
    // here to enable Nvram Full Access control for getting variable if "NV+BS" only.
    if (gNvramControl == NULL) gNvramControl = LocateNvramControlSmmProtocol();
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(TRUE);
    // Get LegacyBootOrder variable size
    LegacyOrder = (UINT16*)(gSmmBootOrder + LEGACY_BOOT_ORDER_OFFSET);
    LegacyOrderSize = 0;
    Status = pRS->GetVariable(L"LegacyDevOrder", \
                               &LegacyDevOrderGuid, NULL, &LegacyOrderSize, NULL);
    if(Status != EFI_NOT_FOUND) {
        Status = pRS->GetVariable(L"LegacyDevOrder", 
                        &LegacyDevOrderGuid, \
                        (UINT32*)((UINT8*)LegacyOrder + sizeof(UINT32)), \
                        &LegacyOrderSize, \
                        (UINT8*)LegacyOrder + (sizeof(UINT32) * 2));
        *(UINT32*)LegacyOrder = (UINT32)LegacyOrderSize;            
    } else *(UINT32*)LegacyOrder = 0; // Clear Buffer to indicate no LegacyDevOrder
    // Disable the Nvram Full Access control after processing the "LegacyDevOrder".
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(FALSE);

    // Get BootXXXX for restore
    for(i = 0, gNumBootDevice = 0; i < (BootOrderSize / sizeof(UINT16)); i++)
    {
        Swprintf(SavedBootXXX->BootVarName, L"Boot%04X", *(BootOrder + i));
        // Get Bootxxx variable size
        SavedBootXXX->BootXXXXSize = 0;
        Status = pRS->GetVariable( SavedBootXXX->BootVarName, \
                          &EfiVariableGuid, \
                          NULL, \
                          &SavedBootXXX->BootXXXXSize, \
                          NULL);
        // if not found, try upper case.
        if(Status == EFI_NOT_FOUND)
        {
            Swprintf(SavedBootXXX->BootVarName, L"Boot%04X", *(BootOrder + i));
            // Get Variable size.
            SavedBootXXX->BootXXXXSize = 0;
            Status = pRS->GetVariable( 
                          SavedBootXXX->BootVarName, \
                          &EfiVariableGuid, \
                          NULL, \
                          &SavedBootXXX->BootXXXXSize, \
                          NULL);
        }
        // Get this from BootOrder, there must be a variable
        pRS->GetVariable( SavedBootXXX->BootVarName, \
                          &EfiVariableGuid, \
                          NULL, \
                          &SavedBootXXX->BootXXXXSize, \
                          (UINT8*)SavedBootXXX + sizeof(RESTORE_BOOTORDER));
        SavedBootXXX->BootOrderNO = *(BootOrder + i);
        // Ptr to next "BootXXXX" buffer.
        (UINT8*)SavedBootXXX += (SavedBootXXX->BootXXXXSize + \
                                                sizeof(RESTORE_BOOTORDER));
        gNumBootDevice++;
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreEfiBootOrders
//
// Description: Restore the BootXXXX contains "Windows Boot Manager"
//              For EFI OS.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>

VOID RestoreEfiBootOrders (VOID)
{
    EFI_GUID EfiVariableGuid = EFI_GLOBAL_VARIABLE;
    EFI_GUID LegacyDevOrderGuid = LEGACY_DEV_ORDER_GUID;
    UINTN       BootOrderSize;
    UINT16      *BootOrder;
    RESTORE_BOOTORDER   *SavedBootXXX;
    UINT8 i;
    EFI_STATUS Status;
    
    if (gSmmBootOrder == NULL) return;
    BootOrder = (UINT16*)(gSmmBootOrder + BOOT_ORDER_OFFSET);        
    SavedBootXXX = (RESTORE_BOOTORDER*)gSmmBootOrder;
    BootOrderSize = 0;
    // Get BootOrderSize Variable size if exist.
    Status = pRS->GetVariable(L"BootOrder",&EfiVariableGuid,NULL,&BootOrderSize, NULL);
    if(Status != EFI_NOT_FOUND)
    {
        Status = pRS->GetVariable( L"BootOrder", &EfiVariableGuid, \
                                            NULL, &BootOrderSize, BootOrder);
        // if BootOreder found, update nothing.
        if(!EFI_ERROR(Status))
        {
            // Free BootOrder buffer in SMM.
            pSmst->SmmFreePages (gSmmBootOrder, RESTORE_BOOT_ORDER_BUFFER >> 12);
            // Re-initial global variable.
            gSmmBootOrder = NULL;
            gNumBootDevice = 0;
            return;
        }
    }

    for(i = 0 ; i < gNumBootDevice; i++)
    {
        // Restore BootXXXX
        Status = pRS->SetVariable ( \
                        SavedBootXXX->BootVarName, \
                        &EfiVariableGuid, \
                        EFI_VARIABLE_NON_VOLATILE | \
                        EFI_VARIABLE_RUNTIME_ACCESS | \
                        EFI_VARIABLE_BOOTSERVICE_ACCESS, \
                        SavedBootXXX->BootXXXXSize, \
                        (UINT8*)SavedBootXXX + sizeof(RESTORE_BOOTORDER));
        BootOrder[i] = SavedBootXXX->BootOrderNO;
        // Ptr to next "BootXXXX" buffer.
        (UINT8*)SavedBootXXX += (SavedBootXXX->BootXXXXSize + sizeof(RESTORE_BOOTORDER));
    }
    // Restore "BootOrder"
    pRS->SetVariable (  L"BootOrder",
                        &EfiVariableGuid,
                        EFI_VARIABLE_NON_VOLATILE |
                        EFI_VARIABLE_RUNTIME_ACCESS |
                        EFI_VARIABLE_BOOTSERVICE_ACCESS,
                        (sizeof(UINT16) * i),
                        BootOrder );
    
    // Enable the Nvram Full Access control for processing the "LegacyDevOrder".
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(TRUE);
    // Restore "LegacyDevOrder"
    BootOrder = (UINT16*)(gSmmBootOrder + LEGACY_BOOT_ORDER_OFFSET);
    BootOrderSize = *(UINT32*)BootOrder;
    if (BootOrderSize != 0) pRS->SetVariable (L"LegacyDevOrder", \
                                    &LegacyDevOrderGuid, \
                                    *(UINT32*)((UINT8*)BootOrder + sizeof(UINT32)), \
                                    BootOrderSize, \
                                    (UINT8*)BootOrder + (sizeof(UINT32) * 2));
    // Disable the Nvram Full Access control after processing the "LegacyDevOrder".
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(FALSE);

    // Free BootOrder buffer in SMM.
    pSmst->SmmFreePages (gSmmBootOrder, RESTORE_BOOT_ORDER_BUFFER >> 12);
    // Re-initial global variable.
    gSmmBootOrder = NULL;
    gNumBootDevice = 0;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveSetupPassword
//
// Description: Save the Setup Password
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreserveSetupPassword(VOID)
{
    UINTN       VariableSize;
    EFI_STATUS  Status;
    
    // Due to the "RT" attribute could be removed from "AMITSESetup" variable,
    // here to enable Nvram Full Access control for getting variable with "NV+BS" only.
    if (gNvramControl == NULL) gNvramControl = LocateNvramControlSmmProtocol();
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(TRUE);
        
    VariableSize = sizeof(AMITSESETUP);
    Status = pRS->GetVariable ( L"AMITSESetup", \
                                &gAmiTseSetupGuid, \
                                &gAmiTseDataAttr, \
                                &VariableSize, \
                                &gAmiTseData );
                                
    if (EFI_ERROR(Status)) gAmiTseDataAttr = 0;

    // Disable the Nvram Full Access control after processing the "AMITSESetup".
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(FALSE);
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   RestoreSetupPassword
//
// Description: Restore previous Password
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreSetupPassword (VOID)
{
    UINTN       VariableSize = 0;
    EFI_STATUS  Status;
    AMITSESETUP TempAmiTseData;

    pRS->GetVariable ( L"AMITSESetup", \
                       &gAmiTseSetupGuid, \
                       NULL, \
                       &VariableSize, \
                       &gAmiTseData );

    //
    // Check the length of new AMITSESETUP stucture and old AMITSESETUP
    //
    if(VariableSize != sizeof(AMITSESETUP)) {
        //
        // Sturcture changed, Don't Restore !!
        //
        return;
    }
    
    if (gAmiTseDataAttr == 0) return;
    //
    // Check Nvram is updated or not. If updated, restore only the password.
    // SilentBoot value will be restored to default value.
    //
    VariableSize = sizeof(AMITSESETUP);
    Status = pRS->GetVariable ( L"AMITSESetup", \
    	                        &gAmiTseSetupGuid, \
    	                        NULL, \
    	                        &VariableSize, \
    	                        &TempAmiTseData );

    if(Status == EFI_SUCCESS) {
        //
        // If the nvram is not modified exit without restoring the AMITSESETUP nvram variable.
        //
        if (!MemCmp(&TempAmiTseData, &gAmiTseData, sizeof(AMITSESETUP))){
            return;
        }
    }
    // Enable the Nvram Full Access control for processing the "AMITSESetup".
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(TRUE);
    gAmiTseData.AMISilentBoot= DEFAULT_QUIET_BOOT;
    VariableSize = sizeof(AMITSESETUP);
    pRS->SetVariable (  L"AMITSESetup", \
                        &gAmiTseSetupGuid, \
                        gAmiTseDataAttr, \
                        VariableSize, \
                        &gAmiTseData );
    // Disable the Nvram Full Access control after processing the "AMITSESetup".
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(FALSE);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DisablePowerButton
//
// Description: Disable Power Button when AFU.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisablePowerButton(VOID)
{
    // Disable PWR Button SMI
    IoWrite16(PM_BASE_ADDRESS + 0x02, IoRead16(PM_BASE_ADDRESS + 0x02) & 0xFEDF);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   EnablePowerButton
//
// Description: Re-Enable PowerButton after flash BIOS
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EnablePowerButton (VOID)
{
    //Clear All PM  Statuses
    IoWrite16(PM_BASE_ADDRESS,IoRead16(PM_BASE_ADDRESS));
    // Re-ensable PWR Button SMI
    IoWrite16(PM_BASE_ADDRESS + 0x02, BIT05 + BIT08);
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   DisableUSBKBD
//
// Description: Disable USB Keyboard when flashing BIOS.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DisableUSBKBD(VOID)
{
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
    EFI_GUID EfiVariableGuid = AMITSESETUP_GUID;
    UINTN    VariableSize = sizeof(VOID*);
    EFI_STATUS Status;

    Status = pRS->GetVariable (  L"USB_POINT",
                        &EfiVariableGuid,
                        NULL,
                        &VariableSize,
                        &gUsbRtKbcAccessControl);
    if(!EFI_ERROR(Status) && (gUsbRtKbcAccessControl != NULL))
        gUsbRtKbcAccessControl(1);
#endif
#endif

    // Disable KBC.
    if (0xff != IoRead8(0x60)) {
        IoWrite8(0x64, 0xad);
        IoWrite8(0x21, IoRead8(0x21) | 0x2);
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   EnableUSBKBD
//
// Description: Re-Enable USB KeyBoard after flashing BIOS
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EnableUSBKBD (VOID)
{
    // Enable KBC.
    if (0xff != IoRead8(0x60)) {
        IoWrite8(0x64, 0xae);
        IoWrite8(0x21, IoRead8(0x21) & 0xfd);
    }

#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
    if (gUsbRtKbcAccessControl != NULL)
        gUsbRtKbcAccessControl(0);
#endif
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetUsbProtocol
//
// Description: This hook gets USB Protocol for disabling USB while flashing.
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
GetUsbProtocolPoint(
    IN EFI_EVENT   Event,
    IN VOID        *Context
)
{
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
    EFI_GUID EfiVariableGuid = AMITSESETUP_GUID;
    EFI_USB_PROTOCOL    *AmiUsb = NULL;

    pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &AmiUsb);
    pRS->SetVariable (  L"USB_POINT",
                        &EfiVariableGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS |
                        EFI_VARIABLE_BOOTSERVICE_ACCESS,
                        sizeof(VOID*),
                        (VOID*)&AmiUsb->UsbRtKbcAccessControl );
#endif
#endif
    return;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetUsbControl
//
// Description: This hook gets USB Protocol's function
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
GetUsbControl(
    CONST EFI_GUID  *Protocol,
    VOID            *Interface,
    EFI_HANDLE      Handle
)
{
	GetUsbProtocolPoint( NULL, NULL );

    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   USBInSmmFunction
//
// Description: Notify for USB smm Protocol
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBInSmmFunction(
    VOID
)
{
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
    EFI_STATUS          Status;
    EFI_USB_PROTOCOL    *AmiUsb = NULL;
    EFI_GUID EfiVariableGuid = AMITSESETUP_GUID;
    EFI_GUID AmiUsbSmmProtocolGuid = AMI_USB_SMM_PROTOCOL_GUID;

    Status = pSmst->SmmLocateProtocol(
                        &AmiUsbSmmProtocolGuid,
                        NULL,
                        &AmiUsb );
    if( EFI_ERROR(Status) )
    {
        VOID        *NotifyReg;

        Status = pSmst->SmmRegisterProtocolNotify(
                            &AmiUsbSmmProtocolGuid,
                            GetUsbControl,
                            &NotifyReg );
    }
    else
    {
        GetUsbProtocolPoint( NULL, NULL );
    }

    return;
#else
    return;
#endif
#else
    return;
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   USBNonSmmFunction
//
// Description: Find USB Protocol pointer
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
USBNonSmmFunction(
    VOID
)
{
#if AMIUSB_SUPPORT == 1
#if (((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
    EFI_STATUS Status;
    EFI_USB_PROTOCOL    *AmiUsb = NULL;
    EFI_GUID EfiVariableGuid = AMITSESETUP_GUID;

    Status = pBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &AmiUsb);
    if(EFI_ERROR(Status))
    {
        EFI_EVENT   SmiFlashEvt;
        VOID        *NotifyReg;

        Status = pBS->CreateEvent (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    GetUsbProtocolPoint,
                    NULL,
                    &SmiFlashEvt
                    );

        if (!EFI_ERROR (Status)) {
            Status = pBS->RegisterProtocolNotify (
                          &gEfiUsbProtocolGuid,
                          SmiFlashEvt,
                          &NotifyReg);
        }
    }else
        pRS->SetVariable (  L"USB_POINT",
                            &EfiVariableGuid,
                            EFI_VARIABLE_RUNTIME_ACCESS |
                            EFI_VARIABLE_BOOTSERVICE_ACCESS,
                            sizeof(VOID*),
                            (VOID*)&AmiUsb->UsbRtKbcAccessControl );

    return;
#else
    return;
#endif //(((USB_DRIVER_MAJOR_VER*100 ) + (USB_DRIVER_MINOR_VER*10) + (USB_DRIVER_BUILD_VER)) >= 891)
#else
    return;
#endif //AMIUSB_SUPPORT
}
#if AFU_BUFFER_IN_SHADOW
#include <AmiCspLib.h>
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   UpdateShadowBuffer
//
// Description: This hook enables shadow write for updating buffer pointer
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateShadowBuffer(
  IN     UINT8  Data, 
  IN OUT UINT64 pCommBuff
)
{
    UINT8           FixLen;
    static UINT8*   Buffer = 0;
    UINT32          LowBufferAddress, HighBufferAddress;

    if(Data == SMIFLASH_ENABLE_FLASH)
        OemRuntimeShadowRamWrite(TRUE);
    else
    {
        if((UINTN)Buffer == 0)
        {
            Buffer = (UINT8*)0xF0000;
            for(;*(UINT32*)Buffer != 0x46534124 && 
                        ((UINTN)Buffer < 0x100000);(UINTN)Buffer++);
        }

        if((UINTN)Buffer == 0xFFFFF)
            return;
        // Skip Sig
        FixLen = *(Buffer + 4);

        if(*(UINT32*)(Buffer + FixLen) == 0 || 
           *(UINT32*)(Buffer + FixLen) == 0xFFFFFFFF)
            return;

        LowBufferAddress = *(UINT32*)(Buffer + FixLen);
        HighBufferAddress = 0;
        pCommBuff           = HighBufferAddress;
        pCommBuff           = Shl64(pCommBuff, 32);
        pCommBuff           += LowBufferAddress;
    }
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   ClearShadowBuffer
//
// Description: Elink for Disable shadow and clear buffer pointer
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ClearShadowBuffer (
  IN     UINT8  Data, 
  IN OUT UINT64 pCommBuff
)
{
    UINT8           FixLen;
    static UINT8*   Buffer = 0;

    if(Data == SMIFLASH_DISABLE_FLASH)
        OemRuntimeShadowRamWrite(FALSE);
    else
    {
        if((UINTN)Buffer == 0)
        {
            Buffer = (UINT8*)0xF0000;
            for(;*(UINT32*)Buffer != 0x46534124 && 
                        ((UINTN)Buffer < 0x100000);(UINTN)Buffer++);
            
        }
        if((UINTN)Buffer == 0xFFFFF)
            return;

        // Skip Sig
        FixLen = *(Buffer + 4);
        // Clear Buffer address
        *(UINT32*)(Buffer + FixLen) = 0;
    }
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   FindFfsFileByGuid
//
// Description: This hooks finds FFS file by GUID. 
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32
FindFfsFileByGuid (
    IN UINT8                *pFV,
    IN UINT32               FvLength,
    IN EFI_GUID             *pGuid
)
{
    EFI_FFS_FILE_HEADER     *pFfsFile;
    UINT32                  Length, FileSize;

    if ((((EFI_FIRMWARE_VOLUME_HEADER*)pFV)->Signature != FV_SIGNATURE) || \
        (((EFI_FIRMWARE_VOLUME_HEADER*)pFV)->FvLength != (UINT64)FvLength))
        return FALSE;
    Length = ((EFI_FIRMWARE_VOLUME_HEADER*)pFV)->HeaderLength;
    pFfsFile = (EFI_FFS_FILE_HEADER*)((UINT32)pFV + Length);
    FileSize = *(UINT32 *)pFfsFile->Size & 0x00FFFFFF;
    do {
        if (!MemCmp ((UINT8*)pFfsFile, pGuid ,sizeof(EFI_GUID))) 
            return (UINT32)pFfsFile;
        FileSize = *(UINT32 *)pFfsFile->Size & 0x00FFFFFF;
        pFfsFile = (EFI_FFS_FILE_HEADER*)((UINT32)pFfsFile + FileSize);
        pFfsFile = (EFI_FFS_FILE_HEADER*)(((UINT32)pFfsFile + 7) & 0xfffffff8);
        if ((UINT32)((UINT8*)pFfsFile - pFV) >= FvLength) break;
    } while(((*(UINT32 *)pFfsFile->Size & 0x00FFFFFF) != 0xFFFFFF) && \
            ((*(UINT32 *)pFfsFile->Size & 0x00FFFFFF) != 0));
    return FALSE;
}
#if defined SecSMIFlash_SUPPORT && SecSMIFlash_SUPPORT == 1
#include <FlashUpd.h>
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveRomHole
//
// Description: This hook preserves ROM Holes while flashing.
//
// Input:
//
// Output:
//
// Returns:
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RecoveryPreserveRomHoles(VOID) {
    EFI_GUID        RomLayoutGuid = ROM_LAYOUT_FFS_GUID;
    ROM_AREA        *RomArea;
    UINT32          FfsFile = 0, RomHoleFfs1, RomHoleFfs2, RomHoleSize;
    EFI_GUID        HobListGuid = HOB_LIST_GUID;
    EFI_STATUS      Status;
    RECOVERY_IMAGE_HOB *RecoveryHob; 
    EFI_GUID        RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    EFI_GUID        FlashUpdGuid = FLASH_UPDATE_GUID;
    AMI_FLASH_UPDATE_BLOCK  FlashUpdDesc;
    UINTN           Size, Attributes;
    UINT8	        *Fv;
    EFI_GUID        *pGuid = NULL;

    RecoveryHob = GetEfiConfigurationTable(pST, &HobListGuid);
    if ((RecoveryHob == NULL) || \
        (((EFI_HOB_HANDOFF_INFO_TABLE*)RecoveryHob)->BootMode != \
                                                BOOT_ON_FLASH_UPDATE)) return;
    // Due to AFU 3.03 have support to preserve Romholes if capsule mode, 
    // SMIFlash only preserve Romholes if Recovery mode of Secure Update.
    Status = pRS->GetVariable(FLASH_UPDATE_VAR, \
            &FlashUpdGuid, (UINT32*)&Attributes, &Size, &FlashUpdDesc);
    if (EFI_ERROR(Status) || (FlashUpdDesc.FlashOpType != FlRecovery)) return;

    Status = FindNextHobByGuid(&RecoveryHobGuid, &RecoveryHob);
    if (EFI_ERROR(Status)) return;
    // Search Romlayout in ROM
    for(Fv = (UINT8*)(0xffffffff - FLASH_SIZE + 1); 
        ((Fv < (UINT8*)0xffffffff) && (FfsFile == 0)); 
        FfsFile = FindFfsFileByGuid (Fv,
                  (UINT32)(((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->FvLength), &RomLayoutGuid), 
                  Fv = Fv+16 );

    if(FfsFile == 0) return;
    for(pGuid = RecoveryPreserveGUID; pGuid->Data1 != 0; pGuid++) {
        // Search in ROM File
        RomHoleFfs1 = 0;
        for (RomArea = (ROM_AREA*)(FfsFile + 0x2c); RomArea->Size != 0; RomArea++)
        {
            if (RomArea->Type != RomAreaTypeFv) continue;
            RomHoleFfs1 = FindFfsFileByGuid ((UINT8*)RomArea->Address, \
                                             RomArea->Size, \
                                             pGuid);
            if(RomHoleFfs1 != 0)
                break;
        }
        // if not found, search next.
        if (RomHoleFfs1 == 0) continue;

        // Search in Recovery File
        RomHoleFfs2 = 0;
        for (RomArea = RomLayout; RomArea->Size != 0; RomArea++)
        {

            if (RomArea->Type != RomAreaTypeFv) continue;
            RomHoleFfs2 = FindFfsFileByGuid ( \
                                (UINT8*)(RecoveryHob->Address + RomArea->Offset), \
                                RomArea->Size, \
                                pGuid);
            if(RomHoleFfs2 != 0)
                break;
        }
        // FFS found in ROM and Recovery File
        if (RomHoleFfs2 != 0)
        {
            RomHoleSize = *(UINT32*)(RomHoleFfs1 + 0x14) & 0xFFFFFF;    
            if ((RomHoleSize == (*(UINT32*)(RomHoleFfs2 + 0x14) & 0xFFFFFF)) && \
                MemCmp((UINT8*)(RomHoleFfs1 + sizeof(EFI_FFS_FILE_HEADER)), \
                       (UINT8*)(RomHoleFfs2 + sizeof(EFI_FFS_FILE_HEADER)), \
                       RomHoleSize - sizeof(EFI_FFS_FILE_HEADER))) {
                pBS->CopyMem((UINT8*)(RomHoleFfs2 + sizeof(EFI_FFS_FILE_HEADER)), \
                             (UINT8*)(RomHoleFfs1 + sizeof(EFI_FFS_FILE_HEADER)), \
                             RomHoleSize - sizeof(EFI_FFS_FILE_HEADER));
            }                          
        }
    }
}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   PreserveWin8Variables
//
// Description: Preserve all variables that GUID is {77fa9abd-0359-4d32-bd60-28f4e78f784b}.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PreserveWin8Variables(VOID)
{
    UINTN               VarNameSize = 2;
    CHAR16              *VarName = NULL;
    CHAR16              *OldVarName = NULL;
    EFI_GUID            VarGuid;
    UINTN               VariableSize;
    UINT8               *VariableData;
    EFI_STATUS          Status;
    RESTORE_VAR         *pRestoreVarList;
    UINT8               *pData;
    UINT32              VariableAttr;

    Status = pSmst->SmmAllocatePool (
        EfiRuntimeServicesData,
        VarNameSize, &VarName
    );

    if(EFI_ERROR(Status))
        return;

    Status = pSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof(RESTORE_VAR), &RestoreVarList);

    if(EFI_ERROR(Status))
    {
        RestoreVarList = NULL;
        return;
    }
    gNvramControl = LocateNvramControlSmmProtocol();
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(TRUE);
    pRestoreVarList = RestoreVarList;

    // Init Variable List
    pRestoreVarList->NextData = 0;

    // Get frist variable
    VarName[0] = NULL;
    do{
        if(VarNameSize != 0)
            Status = pRS->GetNextVariableName (&VarNameSize,
                        VarName, &VarGuid);
        else
            Status = EFI_BUFFER_TOO_SMALL;
        if(Status == EFI_BUFFER_TOO_SMALL)
        {
            // If VarNameSize is 0, VarName is not existed.
            if(VarNameSize != 0)
            {
                // Keep the old variable name for next search
                OldVarName = VarName;
            }

            // Avoid dead loop
            VarNameSize = DefaultVariableSize;

            Status = pSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          VarNameSize, &VarName);

            if(EFI_ERROR(Status))
                return;

            MemCpy(VarName, OldVarName, VarNameSize);

            continue;
        }


        if(!EFI_ERROR(Status))
        {
            if(guidcmp(&VarGuid, &gWin8Guid))
            {
                // Make sure every time, it gets a buffer too small,
                // don't waste this buffer
                VarNameSize = DefaultVariableSize;
                continue;
            }

            VariableSize = 0;
            Status = pRS->GetVariable(VarName, &gWin8Guid,
                                      NULL, &VariableSize, NULL);

            if(Status != EFI_BUFFER_TOO_SMALL)
                continue;

            Status = pSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          VariableSize, &VariableData);

            if(EFI_ERROR(Status))
                continue;

            Status = pRS->GetVariable(VarName, &gWin8Guid,
                                      &VariableAttr, &VariableSize, VariableData);

            if(EFI_ERROR(Status))
            {
                pSmst->SmmFreePool(VariableData);
                continue;
            }
            // Store variable in Link list
            Status = pSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          sizeof(RESTORE_VAR), &pData);

            if(EFI_ERROR(Status))
                continue;
            Status = pSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          VarNameSize, &OldVarName);

            if(EFI_ERROR(Status))
                continue;

            MemCpy(OldVarName, VarName, VarNameSize);
            // Free the bigger Varname
            pSmst->SmmFreePool(VarName);


            pRestoreVarList->rVar.BootVarName = OldVarName;
            pRestoreVarList->rVar.Guid = &gWin8Guid;
            pRestoreVarList->rATTR.Attrib = VariableAttr;
            pRestoreVarList->rATTR.Size = VariableSize;
            pRestoreVarList->rATTR.Data = VariableData;
            pRestoreVarList->NextData = (UINTN)pData;

            (UINT8*)pRestoreVarList = pData;
            pRestoreVarList->NextData = 0;
            // Make sure every time, it gets a buffer too small,
            // make it allocate new buffer for name
            VarNameSize = 0;
        }

    }while(Status != EFI_NOT_FOUND);
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(FALSE);
}
//<AMI_PHDR_START>
//---------------------------------------------------------------------
// Procedure:   RestoreWin8Variables
//
// Description: Restore all variables that GUID is {77fa9abd-0359-4d32-bd60-28f4e78f784b}.
//
// Input:       NONE
//
// Output:      NONE
//
// Returns:     NONE
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RestoreWin8Variables (VOID)
{
    RESTORE_VAR         *pRestoreVarList = RestoreVarList, *TempPoint;
    EFI_STATUS          Status;

    if(RestoreVarList == NULL)
        return;
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(TRUE);
    for( ; pRestoreVarList->NextData != 0 ; )
    {
        Status = pRS->SetVariable (  pRestoreVarList->rVar.BootVarName,
                                     pRestoreVarList->rVar.Guid,
                                     pRestoreVarList->rATTR.Attrib,
                                     pRestoreVarList->rATTR.Size,
                                     pRestoreVarList->rATTR.Data );

        (UINTN)TempPoint = pRestoreVarList->NextData;

        pSmst->SmmFreePool(pRestoreVarList->rVar.BootVarName);
        pSmst->SmmFreePool(pRestoreVarList->rATTR.Data);
        pSmst->SmmFreePool(pRestoreVarList);
        pRestoreVarList = TempPoint;
    }
    if (gNvramControl) gNvramControl->ShowBootTimeVariables(FALSE);
    RestoreVarList = NULL;
}
#else // #if defined _OUTSIDE_SMM_
//*********** OUTSIDE SMM ***********************************************
#if defined RECOVERY_PRESERVE_VARS_IN_SMM && RECOVERY_PRESERVE_VARS_IN_SMM == 1
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   mSMIFlashSmi
//
// Description: mSMIFlashSmi structure for generating SW SMI call. 
//
// Input:       
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
static UINT8 mSMIFlashSmi[] = {
	0x50,					// push eax
	0x53,					// push ebx
	0x51,					// push ecx
	0x52,					// push edx
	0xBA, SW_SMI_IO_ADDRESS, 0, 0, 0,	// mov edx, SW_SMI_IO_ADDRESS
	0xB8, 0x00, 0x00, 0x00, 0x00,		// mov eax, 0	//SW SMI value
	0xBB, 0x00, 0x00, 0x00, 0x00,		// mov ebx, 0	//LowBufferAddress
	0xB9, 0x00, 0x00, 0x00, 0x00,		// mov ecx, 0	//HighBufferAddress
	0xEE, 					// out dx, al
	0x5A,					// pop edx
	0x59,					// pop ecx
	0x5B,					// pop ebx
	0x58,					// pop eax
	0xC3,					// ret
};//mSMIFlashSmi[]

FUNC_BLOCK FuncBlock = {0,0,0,0};
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RecoveryHookBeforeFlash
//
// Description: This hook preserves variables in SMM while reflash update.
//
// Input:       
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RecoveryHookBeforeFlash (VOID)
{
    void 	(*IssueSWSMI)(void);
    *(UINT8*)&mSMIFlashSmi[10] = SMIFLASH_ENABLE_FLASH;	//EAX
    *(UINT32*)&mSMIFlashSmi[15] = (UINT32)&FuncBlock;	//EBX
    IssueSWSMI = (void*)mSMIFlashSmi;
    IssueSWSMI();
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
    // For following DeviceWriteEnable call of reflash.c.
    Flash->DeviceWriteDisable(); 
#endif
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   RecoveryHookAfterFlash
//
// Description: This hook restores variables from SMM after reflash update.
//
// Input:       
//
// Output:      
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RecoveryHookAfterFlash (VOID)
{
    void 	(*IssueSWSMI)(void);

#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
    // For following DeviceWriteDisable call of smiflash func#24.
    Flash->DeviceWriteEnable();
#endif
    *(UINT8*)&mSMIFlashSmi[10] = SMIFLASH_DISABLE_FLASH;//EAX
    *(UINT32*)&mSMIFlashSmi[15] = (UINT32)&FuncBlock;	//EBX
    IssueSWSMI = (void*)mSMIFlashSmi;
    IssueSWSMI();
}
#endif // if defined RECOVERY_PRESERVE_IN_SMM && RECOVERY_PRESERVE_IN_SMM == 1
#endif // if defined _OUTSIDE_SMM_                                            

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
