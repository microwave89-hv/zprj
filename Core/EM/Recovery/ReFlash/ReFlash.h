//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/ReFlash/ReFlash.h 2     4/16/13 5:50a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/16/13 5:50a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/ReFlash/ReFlash.h $
// 
// 2     4/16/13 5:50a Thomaschen
// Fixed for EIP106722.
//
// 13    1/02/13 12:18p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Flash update progress report changes:
// - report progress in non-interactive flash update
// - do not report progress in Win8-style flash update
// [Files]  		ReflashWorker.c Reflash.h Esrt.c
// 
// 12    7/20/12 10:20a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Reflash.c Esrt.c Reflash.h Capsule.h ReflashWorker.c
// Protocol.cif AmiReflashProtocol.h Setup.h
// 
// 11    5/22/12 4:44p Artems
// [TAG]  		EIP88314
// [Description]  	Recovery takes a long time for large flash size
// Rewrite reflash code to not give control back to TSE until finished
// reporting progress via DisplayProgress API of AMI Post manager
// [Files]  		Reflash.c Reflash.h ReflashWorker.c Reflash.mak Reflash.vfr
// Reflash.uni
// 
// 10    11/12/11 6:49p Artems
// Added fault tolerant recovery support
// 
// 9     5/13/11 4:52p Artems
// Added extended error reporting for secure flash update/recovery
// 
// 8     11/17/10 2:52p Felixp
// Enhencement (EIP 36355):
// The Reflash component is updated to be extensible with external
// eModules. 
// The eModules can contribute content for the Recovery setup page, 
// and provide callback function that will be periodically called 
// once BIOS update is completed.The external eModules can be used 
// to implement update of non-standard firmware components. 
// For example, update of the non-shared EC firmware.
// 
// 7     12/24/09 12:42p Oleksiyy
// EIP 30173: Support for the EC Firmware Area Update control added. Main
// token to enable this support is EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
// should be located in specific EC-related  .sdl file.
// 
// 6     10/09/09 6:30p Felixp
// ReFlash component is updated to support Framework and UEFI 2.1 HII
// 
// 5     7/09/09 5:59p Oleksiyy
// Files clean-up, some headers added
//
// 4     10/19/07 6:23p Felixp
// Recovery Flash Update module extended to support Boot Block update.
// Boot block update can be enabled or disabled using SDL token.
// In addition to that there is an SDL token that enables/disables
// checkbox on the
// recovery setup page that user can use to enable or disable boot block
// update.
//
// 3     4/13/07 6:08p Ambikas
// Coding standard changes: updated the year in the AMI copyright
// header/footer.
//
// 2     12/22/06 9:38a Felixp
// Support for optional NVRAM reset based on user input added
//
// 1     12/01/05 9:35a Felixp
//
// 1     11/08/05 4:04a Felixp
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    ReFlash.h
//
// Description: Header file for component
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __REFLASH__H__
#define __REFLASH__H__
#ifdef __cplusplus
extern "C"
{
#endif
#include <ReFlashStrTokens.h>
#include <Token.h>
#ifndef VFRCOMPILE
#include <AmiDxeLib.h>
#include <Protocol/FlashProtocol.h>
#endif

#define RECOVERY_FORM_SET_CLASS             0x40
// {80E1202E-2697-4264-9CC9-80762C3E5863}
#define RECOVERY_FORM_SET_GUID { 0x80e1202e, 0x2697, 0x4264, 0x9c, 0xc9, 0x80, 0x76, 0x2c, 0x3e, 0x58, 0x63 }

#if REFLASH_INTERACTIVE
#define RECOVERY_MAIN 1
#define RECOVERY_FLASH 2
#else
#define RECOVERY_FLASH 1
#endif

#define FLASH_PROGRESS_KEY 100
#define FLASH_START_KEY 101

#pragma pack(push, 1)
typedef struct {
        UINT8 FailedRecovery; // EFI_STATUS error code
        UINT8 UpdateNv;
        UINT8 UpdateBb;
        UINT8 UpdateMain;
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
	    UINT8 UpdateEC;
#endif

#define REFLASH_DATA_DEFINITION
#include <ReflashDefinitions.h>
#undef REFLASH_DATA_DEFINITION

} AUTOFLASH;
#pragma pack(pop)
    
#include <Setup.h>

#ifndef VFRCOMPILE

#define FW_VERSION_VARIABLE L"AmiFwVersion"

typedef enum {
    FvTypeMain,
    FvTypeBootBlock,
    FvTypeNvRam,
    FvTypeCustom,
    FvTypeMax
} FLASH_FV_TYPE;

typedef struct _FLASH_AREA_EX FLASH_AREA_EX;

typedef EFI_STATUS (REFLASH_FUNCTION_EX)(
    IN FLASH_AREA_EX *Block,
    IN UINTN BlockNumber
);

struct _FLASH_AREA_EX
{
    UINT8 *BlockAddress;
    UINT8 *BackUpAddress;
    UINTN Size;
    UINT32 BlockSize;
    FLASH_FV_TYPE Type;
    BOOLEAN Update;
    BOOLEAN TopSwapTrigger;
    REFLASH_FUNCTION_EX *BackUp;
    REFLASH_FUNCTION_EX *Program;
    EFI_STRING_ID BackUpString;
    EFI_STRING_ID ProgramString;
};

extern FLASH_AREA_EX BlocksToUpdate[];
extern FLASH_PROTOCOL *Flash;
extern EFI_HII_HANDLE ReflashHiiHandle;
extern UINT8 *RecoveryBuffer;

EFI_STATUS GetHiiString(
    IN     EFI_HII_HANDLE HiiHandle,
    IN     STRING_REF Token,
    IN OUT UINTN *pDataSize, 
    OUT    EFI_STRING *ppData
);

EFI_STATUS AmiFlashBackUp(
    IN FLASH_AREA_EX *Block,
    IN UINTN BlockNumber
);
EFI_STATUS AmiFlashProgram(
    IN FLASH_AREA_EX *Block,
    IN UINTN BlockNumber
);

VOID ApplyUserSelection(
    IN BOOLEAN Interactive
);

VOID OemBeforeFlashCallback(
    VOID
);

VOID OemAfterFlashCallback(
    VOID
);

EFI_STATUS FlashProgressEx(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID KeyValue,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
);

EFI_STATUS IsWin8Update(
    BOOLEAN RecoveryFailed
);

EFI_STATUS FlashWalker(
    IN BOOLEAN BackUp
);

EFI_STATUS Epilogue(
    VOID
);

EFI_STATUS Prologue(
    IN BOOLEAN Interactive,
    IN BOOLEAN Win8StyleUpdate
);

EFI_STATUS InstallEsrtTable(
    VOID
);

#endif
    /****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
