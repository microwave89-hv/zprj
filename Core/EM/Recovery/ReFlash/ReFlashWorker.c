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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/ReFlash/ReFlashWorker.c 3     5/13/13 6:26a Thomaschen $
//
// $Revision: 3 $
//
// $Date: 5/13/13 6:26a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/ReFlash/ReFlashWorker.c $
// 
// 3     5/13/13 6:26a Thomaschen
// Update for EIP122037.
// 
// 2     4/16/13 5:47a Thomaschen
// Fixed for EIP106722.
//
// 
// 7     2/11/13 3:42p Artems
// [TAG]  		EIP112180
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	In non-interactive mode system updated flash even when
// there is no valid image
// [RootCause]  	In non-interactive mode system didn't check flash image
// validity
// [Solution]  	Added check of flash image validity. Inform user if image
// is invalid or not found
// [Files]  		Reflash.c ReflashWorker.c Reflash.uni Reflash.vfr
// 
// 6     1/02/13 12:20p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Flash update progress report changes:
// - report progress in non-interactive flash update
// - do not report progress in Win8-style flash update
// [Files]  		ReflashWorker.c Reflash.h Esrt.c
// 
// 5     8/02/12 12:00p Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Recovery.h Recovery.sdl Recovery.c Reflash.c ReflashWorker.c
// Esrt.c
// 
// 4     7/24/12 11:56a Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Added dependency on fault-tolerant support module in
// top-swap triggering code
// [Files]  		ReflashWorker.c
// 
// 3     7/20/12 10:19a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Reflash.c Esrt.c Reflash.h Capsule.h ReflashWorker.c
// Protocol.cif AmiReflashProtocol.h Setup.h
// 
// 2     6/08/12 12:35p Artems
// [TAG]  		EIP88314
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Incorrect strings in progress message
// [RootCause]  	String tokens were twisted up
// [Solution]  	Put string tokens in a correct order
// [Files]  		ReflashWorker.c
// 
// 1     5/23/12 1:19p Artems
// [TAG]  		EIP 88314
// [Category]  	Improvement
// [Description]  	Recovery takes a long time for large flash size
// Rewrite reflash code to not give control back to TSE until finished
// reporting progress via DisplayProgress API of AMI Post manager
// 
// [Files]  		Reflash.c Reflash.h ReflashWorker.c Reflash.mak Reflash.vfr
// Reflash.uni
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    ReFlashWorker.c
//
// Description: Implementation of Reflash driver
//
//<AMI_FHDR_END>
//**********************************************************************

#include <Token.h>
#include <FFS.h>
#include <AmiCspLib.h>
#include <Protocol/AmiPostMgr.h>
#include <Protocol/ConsoleControl.h>
#include "Reflash.h"

#define FLASH_PART_START_ADDRESS (0xFFFFFFFF - FLASH_SIZE + 1)
static UINT32 FlashEraser       = (FLASH_ERASE_POLARITY) ? 0 : 0xffffffff;
static UINT8 *FlashPartStart    = (UINT8 *)(UINTN)FLASH_PART_START_ADDRESS;
extern EFI_STATUS RecoveryStatus;

FLASH_AREA_EX BlocksToUpdate[] = {
#if FtRecovery_SUPPORT
    { 
        (UINT8 *)FV_RECOVERY_BASE, 
        (UINT8 *)FV_RECOVERY_BACKUP_ADDRESS, 
        FV_RECOVERY_BLOCKS * FLASH_BLOCK_SIZE, 
        FLASH_BLOCK_SIZE, 
        FvTypeBootBlock,
        REFLASH_UPDATE_BOOT_BLOCK,
        FALSE,
        AmiFlashBackUp,
        AmiFlashProgram,
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_BACKUP_RECOVERY),
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_FLASH_RECOVERY)
    },
    { 
        (UINT8 *)FV_BB_BASE, 
        (UINT8 *)FV_BB_BACKUP_ADDRESS, 
        (FV_BB_BLOCKS - FV_RECOVERY_BLOCKS) * FLASH_BLOCK_SIZE, 
        FLASH_BLOCK_SIZE, 
        FvTypeBootBlock,
        REFLASH_UPDATE_BOOT_BLOCK,
        TRUE,
        AmiFlashBackUp,
        AmiFlashProgram,
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_BACKUP_BB),
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_FLASH_BB)
    },
#else
    { 
        (UINT8 *)FV_BB_BASE, 
        NULL, 
        FV_BB_BLOCKS * FLASH_BLOCK_SIZE, 
        FLASH_BLOCK_SIZE, 
        FvTypeBootBlock,
        REFLASH_UPDATE_BOOT_BLOCK, 
        FALSE,
        NULL,
        AmiFlashProgram,
        0,
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_FLASH_BB)
    },
#endif

//             EIP122037>>
#if INTEL_FIT_SUPPORT
    {
        (UINT8 *)FV_DATA_BASE,
        NULL,
        FV_DATA_SIZE,
        FLASH_BLOCK_SIZE,
        FvTypeBootBlock,
        REFLASH_UPDATE_BOOT_BLOCK,
        FALSE,
        NULL,
        AmiFlashProgram,
        0,
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_FLASH_DATA)
    },
#endif
//             EIP122037<<
    { 
        (UINT8 *)FV_MAIN_BASE, 
        NULL, 
        FV_MAIN_BLOCKS * FLASH_BLOCK_SIZE, 
        FLASH_BLOCK_SIZE, 
        FvTypeMain,
        REFLASH_UPDATE_MAIN_BLOCK, 
        FALSE,
        NULL,
        AmiFlashProgram,
        0,
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_FLASH_MAIN)
    },
    { 
        (UINT8 *)NVRAM_ADDRESS, 
        NULL, 
        NVRAM_BLOCKS * FLASH_BLOCK_SIZE, 
        FLASH_BLOCK_SIZE, 
        FvTypeNvRam,
        REFLASH_UPDATE_NVRAM, 
        FALSE,
        NULL,
        AmiFlashProgram,
        0,
        STRING_TOKEN(STR_FLASH_PROGRESS_MESSAGE_FLASH_NVRAM)
    },
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
    { 
        (UINT8 *)EC_BASE, 
        NULL, 
        EC_BLOCKS * FLASH_BLOCK_SIZE, 
        FLASH_BLOCK_SIZE, 
        FvTypeCustom,
        REFLASH_UPDATE_EC_FIRMWARE, 
        FALSE,
        NULL,
        AmiFlashProgram,
        0,
        STRING_TOKEN(STR_FLASH_PROGRESS_CAPTION_FLASH)
    },
#endif

    { 
        NULL, 
        NULL,
        0,
        0,
        FvTypeMax,
        FALSE, 
        FALSE,
        NULL,
        NULL,
        0,
        0
    }       //terminator
};



static EFI_GUID AmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
static AMI_POST_MANAGER_PROTOCOL *AmiPostMgr = NULL;
static EFI_CONSOLE_CONTROL_PROTOCOL *ConsoleControl = NULL;
static BOOLEAN UserConfirmation = TRUE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    DrawMessageBox
// 
// Description:  This function draws message box on screen and waits till user presses Enter
//               
// Input:   
//  IN CHAR16 *Caption - message box caption
//  IN CHAR16 *Message - message box message
//
// Output: 
//  None
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DrawMessageBox(
    IN CHAR16 *Caption,
    IN CHAR16 *Message
)
{
    EFI_STATUS Status;
    UINT8 MsgKey;

    if(!UserConfirmation)
        return;

    if(AmiPostMgr != NULL) {
        if(ConsoleControl != NULL)
            ConsoleControl->LockStdIn(ConsoleControl, L"");

        pST->ConIn->Reset(pST->ConIn, FALSE);    //discard all keystrokes happend during flash update
            
        Status = AmiPostMgr->DisplayMsgBox(Caption, Message, MSGBOX_TYPE_OK, &MsgKey);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    CountDown
// 
// Description:  This function draws ResetSystem waiting bar
//               
// Input:   
//  None
//
// Output: 
//  None
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
//TODO
VOID CountDown(
    VOID
)
{
    pBS->Stall(5000000);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    Prologue
// 
// Description:  This function is called before actual flashing takes place
//               
// Input:   
//  IN BOOLEAN Interactive - if TRUE reflash is interactive
//  IN BOOLEAN Win8StyleUpdate - if TRUE reflash is Win8Style
//
// Output: 
//  EFI_SUCCESS - system prepared for flashing
//  EFI_NOT_STARTED - recovery image not found
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Prologue(
    IN BOOLEAN Interactive,
    IN BOOLEAN Win8StyleUpdate
)
{
    static BOOLEAN Executed = FALSE;
    static EFI_STATUS Status = EFI_SUCCESS;

    if(Executed)
        return Status;

    Executed = TRUE;
    ApplyUserSelection(Interactive);

    if(!Win8StyleUpdate)    //we do not report progress during Win8-style flash update
        Status = pBS->LocateProtocol(&AmiPostManagerProtocolGuid, NULL, &AmiPostMgr);

    if(Interactive) {
        Status = pBS->LocateProtocol(&gEfiConsoleControlProtocolGuid, NULL, &ConsoleControl);
        if(!EFI_ERROR(Status))
            ConsoleControl->LockStdIn(ConsoleControl, L"");
    } else {
        if(EFI_ERROR(RecoveryStatus)) { //we can't perform flash update, inform user and return error for resetting system
            CountDown();
            return EFI_ABORTED;
        }
        UserConfirmation = FALSE;
    }

    OemBeforeFlashCallback();
    Flash->DeviceWriteEnable();
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    Epilogue
// 
// Description:  This function is called after actual flashing takes place
//               
// Input:   
//  None
//
// Output: (this function is not supposed to return control to caller
//  EFI_SUCCESS - flash updated successfully
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS Epilogue(VOID)
{
    Flash->DeviceWriteDisable();
    OemAfterFlashCallback();

    DrawMessageBox(L"Flash update", L"Flash update completed. Press Enter key to reset the system");
    pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    FlashWalker
// 
// Description:  This function walks through flash regions and calls respective
//  backup and flash functions
//               
// Input:   
//  IN BOOLEAN BackUp - if TRUE, backup functions should be called on this pass
//  flash programm functions should be called otherwise
//
// Output:
//  EFI_SUCCESS - flash updated successfully
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FlashWalker(
    IN BOOLEAN BackUp
)
{
    EFI_STATUS Status;
    UINTN i;
    UINTN k;
    EFI_STRING Title;
    EFI_STRING Message;
    UINTN Size;
    UINTN Step;
    UINTN Threshold;
    UINTN Blocks;

    VOID *DisplayHandle;
    AMI_POST_MGR_KEY OutKey;

    if(AmiPostMgr != NULL) {
        Title = NULL;
        if(BackUp)
            GetHiiString(ReflashHiiHandle, STRING_TOKEN(STR_FLASH_PROGRESS_TITLE_BACKUP), &Size, &Title);
        else
            GetHiiString(ReflashHiiHandle, STRING_TOKEN(STR_FLASH_PROGRESS_TITLE_FLASH), &Size, &Title);

        AmiPostMgr->DisplayProgress(AMI_PROGRESS_BOX_INIT,
                 (Title == NULL) ? L"Flash Update Progress" : Title,
                 NULL,
                 NULL,
                 0,
                 &DisplayHandle,
                 &OutKey);
    }

    for(i = 0; BlocksToUpdate[i].Type != FvTypeMax; i++) {
        if(!BlocksToUpdate[i].Update)
            continue;   //block is not updated

        if(BackUp && BlocksToUpdate[i].BackUp == NULL)
            continue; //no backup function

        if(AmiPostMgr != NULL) {
        /* prepare display progress window */
            Message = NULL;
            if(BackUp)
                GetHiiString(ReflashHiiHandle, BlocksToUpdate[i].BackUpString, &Size, &Message);
            else
                GetHiiString(ReflashHiiHandle, BlocksToUpdate[i].ProgramString, &Size, &Message);
        }

    /* calculate number of blocks to flash */
        Blocks = BlocksToUpdate[i].Size / BlocksToUpdate[i].BlockSize;

    /* calculate progress steps */
        Step = 0;
        if(Blocks > 100) {
            Threshold = (Blocks / 100) + 1;
        } else {
            Threshold = 1;
        }

    /* now we're ready to do actual job */
        for(k = 0; k < Blocks; k++) {
            if(BackUp)
                Status = BlocksToUpdate[i].BackUp(&BlocksToUpdate[i], k);
            else
                Status = BlocksToUpdate[i].Program(&BlocksToUpdate[i], k);

            if(EFI_ERROR(Status))
                return Status;

            Step++;
            if(Step == Threshold && AmiPostMgr != NULL) {
            /* report progress to user */
                AmiPostMgr->DisplayProgress(AMI_PROGRESS_BOX_UPDATE,
                                 (Title == NULL) ? L"Flash Update Progress" : Title,
                                 (Message == NULL) ? L"Flash new data" : Message,
                                 NULL,
                                 (k * 100) / Blocks,
                                 &DisplayHandle,
                                 &OutKey);
                Step = 0;
            }
        }
        
#if FtRecovery_SUPPORT
    /* check if TopSwap should be triggered */
        if(BlocksToUpdate[i].TopSwapTrigger) {
            if(BackUp)
                SetTopSwap(TRUE);
            else
                SetTopSwap(FALSE);
        }
#endif
    }

    if(AmiPostMgr != NULL) {
    /* close progress window */
        AmiPostMgr->DisplayProgress(AMI_PROGRESS_BOX_CLOSE,
                 (Title == NULL) ? L"Flash Update Progress" : Title,
                 NULL,
                 NULL,
                 0,
                 &DisplayHandle,
                 &OutKey);
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    FlashProgressEx
// 
// Description:  This function is called by Setup browser to perform flash update
//               
// Input:   
//  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This - pointer to the instance of 
//                                                  ConfigAccess protocol
//  IN EFI_BROWSER_ACTION Action - action, that setup browser is performing
//  IN EFI_QUESTION_ID KeyValue - value of currently processed setup control
//  IN UINT8 Type - value type of setup control data
//  IN EFI_IFR_TYPE_VALUE *Value - pointer to setup control data
//  OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest - pointer where to store requested action
//
// Output:
//  EFI_SUCCESS - flash updated successfully
//  EFI_UNSUPPORTED - browser action is not supported
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS FlashProgressEx(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID KeyValue,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
)
{
    EFI_STATUS Status;

    if (ActionRequest) 
        *ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;

    if(Action != EFI_BROWSER_ACTION_CHANGING)
        return EFI_UNSUPPORTED;


#if REFLASH_INTERACTIVE
    if(KeyValue == FLASH_START_KEY) {
        Status = Prologue(TRUE, FALSE);
        if(EFI_ERROR(Status)) {
        /* inform user, that flashing can't be performed */
            DrawMessageBox(L"ERROR!!!!", L"Flash update failed to initialize. Press Enter key to reset system");
            pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
        }
    /* we have to give control back to setup browser to refresh the screen */
        return EFI_SUCCESS;
    }
/* nothing to do here, wait for user response */
    if (KeyValue != FLASH_PROGRESS_KEY) {
        return EFI_SUCCESS;     
    }
#else
    Status = Prologue(FALSE, FALSE);
    if(EFI_ERROR(Status)) {
        pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
#endif

    Status = EFI_SUCCESS;

#if FtRecovery_SUPPORT
    if(!IsTopSwapOn()) {
        Status = FlashWalker(TRUE);
    }
#endif

    if(!EFI_ERROR(Status)) {
        Status = FlashWalker(FALSE);
    }

    if(EFI_ERROR(Status)) {
    /* something was wrong - inform user */
        DrawMessageBox(L"ERROR!!!!", L"Flash update failed. Press Enter key to reset system");
        pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }

    Status = Epilogue();
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    SetBackUpArea
// 
// Description:  This function prepares FV_MAIN region to be backup region
//               
// Input:   
//  None
//
// Output:
//  None
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SetBackUpArea(VOID)
{
    static BOOLEAN FirstRun = TRUE;
    static UINT32 FlashEraser = (FLASH_ERASE_POLARITY) ? 0 : 0xffffffff;
    EFI_FIRMWARE_VOLUME_HEADER *Fv;

    if(!FirstRun)
        return;

    FirstRun = FALSE;
    Fv = (EFI_FIRMWARE_VOLUME_HEADER *)(UINTN)FV_MAIN_BASE;
    Flash->Write(&(Fv->Signature), sizeof(UINT32), &FlashEraser);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    AmiFlashBackUp
// 
// Description:  This function backs up given block from given region
//               
// Input:   
//  IN FLASH_AREA_EX *Block - flash region to work with
//  IN UINTN BlockNumber - block number within flash region
//
// Output:
//  EFI_SUCCESS - block saved successfully
//  EFI_ERROR - there was an error during operation
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiFlashBackUp(
    IN FLASH_AREA_EX *Block,
    IN UINTN BlockNumber
)
{
    UINT8 *Source;
    UINT8 *Destination;
    VOID *Tmp;
    EFI_STATUS Status;
    EFI_TPL OldTpl;

    Status = pBS->AllocatePool(EfiBootServicesData, Block->BlockSize, &Tmp);
    if(EFI_ERROR(Status))
        return Status;

    Source = Block->BlockAddress + BlockNumber * Block->BlockSize;
    Destination = Block->BackUpAddress + BlockNumber * Block->BlockSize;

    if(Block->Type == FvTypeBootBlock)
        SetBackUpArea();

    Status = Flash->Read(Source, Block->BlockSize, Tmp);
    if(EFI_ERROR(Status)) {
        pBS->FreePool(Tmp);
        return Status;
    }

//save to backup address
    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
    Status = Flash->Update(Destination, Block->BlockSize, Tmp);
    pBS->RestoreTPL(OldTpl);
    
    pBS->FreePool(Tmp);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    AmiFlashProgram
// 
// Description:  This function programs given block from given region
//               
// Input:   
//  IN FLASH_AREA_EX *Block - flash region to work with
//  IN UINTN BlockNumber - block number within flash region
//
// Output:
//  EFI_SUCCESS - block updated successfully
//  EFI_ERROR - there was an error during operation
// 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS AmiFlashProgram(
    IN FLASH_AREA_EX *Block,
    IN UINTN BlockNumber
)
{
    UINT8 *ImageStart;
    UINT8 *Source;
    UINT8 *Destination;
    EFI_STATUS Status;
    EFI_TPL OldTpl;

    ImageStart = Block->BlockAddress - FlashPartStart + RecoveryBuffer;
    Source = ImageStart + BlockNumber * Block->BlockSize;
    Destination = Block->BlockAddress + BlockNumber * Block->BlockSize;

    OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
    Status = Flash->Update(Destination, Block->BlockSize, Source);
    pBS->RestoreTPL(OldTpl);

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
