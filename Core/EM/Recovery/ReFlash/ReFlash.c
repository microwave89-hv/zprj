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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/ReFlash/ReFlash.c 3     10/01/13 2:03a Thomaschen $
//
// $Revision: 3 $
//
// $Date: 10/01/13 2:03a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/ReFlash/ReFlash.c $
// 
// 3     10/01/13 2:03a Thomaschen
// Update for EIP137328.
// 
// 2     4/16/13 5:48a Thomaschen
// Fixed for EIP106722.
//
// 
// 40    2/11/13 3:41p Artems
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
// 39    2/05/13 1:41p Artems
// [TAG]  		EIP111562
// [Category]  	Improvement
// [Description]  	Add Enable/Disable support for Windows8-style firmware
// update
// [Files]  		Esrt.c Reflash.c Reflash.sdl
// 
// 38    7/20/12 10:17a Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Support of Microsoft ESRT spec
// [Files]  		Reflash.c Esrt.c Reflash.h Capsule.h ReflashWorker.c
// Protocol.cif AmiReflashProtocol.h Setup.h
// 
// 37    5/22/12 4:54p Artems
// [TAG]  		EIP88314
// [Category]  	Improvement
// [Description]  	Recovery takes a long time for large flash size
// Rewrite reflash code to not give control back to TSE until finished
// reporting progress via DisplayProgress API of AMI Post manager
// [Files]  		Reflash.c Reflash.h ReflashWorker.c Reflash.mak Reflash.vfr
// Reflash.uni
// 
// 36    4/09/12 6:03p Artems
// Undo previous change
// 
// 35    2/08/12 4:27a Nerofan
// Update it  for capsule function if memory size is over 2G.
// 
// 34    12/05/11 1:49p Artems
// EIP 74623: Add capabilities similar to ones in SMIFlash module
// 
// 33    11/14/11 4:07p Artems
// Fixed bug with hob size comparison
// Set default attributes for Reflash Setup variable
// 
// 32    11/14/11 3:18p Artems
// Defined Extended errors for security recovery capsule check
// 
// 31    11/12/11 6:48p Artems
// Added fault tolerant recovery support
// 
// 30    11/02/11 4:54p Artems
// EIP 74446: Fixed bug - reflash is enabled when recovery image is not
// found
// 
// 29    5/13/11 4:51p Artems
// Added secure flash recovery/update support. Extended error reporting
// Added handling of unsupported FormBrowser actions
// 
// 28    5/05/11 2:00p Artems
// Bugfix: callback supports only "CHANGING" browser action
// 
// 27    5/04/11 5:54p Artems
// Bugfix: function FlashProgress output parameter ActionRequest was
// undefined
// 
// 26    11/17/10 2:52p Felixp
// Enhencement (EIP 36355):
// The Reflash component is updated to be extensible with external
// eModules. 
// The eModules can contribute content for the Recovery setup page, 
// and provide callback function that will be periodically called 
// once BIOS update is completed.The external eModules can be used 
// to implement update of non-standard firmware components. 
// For example, update of the non-shared EC firmware.
// 
// 25    10/07/10 11:02a Felixp
// FlashDeviceWriteEnable/FlashDeviceWriteDisable calls added.
// 
// 24    10/01/10 2:14p Felixp
// Previous changes related to descrete EC firmware update are rolled back
// for the Core labeling.
// 
// 22    12/24/09 12:42p Oleksiyy
// EIP 30173: Support for the EC Firmware Area Update control added. Main
// token to enable this support is EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
// should be located in specific EC-related  .sdl file.
// 
// 21    11/25/09 11:38a Felixp
// 
// 20    11/25/09 11:27a Felixp
// Action parameter of the Callback function is updated  based on UEFI
// errata
// 
// 19    10/09/09 6:30p Felixp
// ReFlash component is updated to support Framework and UEFI 2.1 HII
// 
// 18    8/25/09 5:29p Felixp
// Recovery module is updated to pass recovery image location via special
// GUIDed HOB. 
// Old implementation that was relying on Firmware Volume (FV) handle, 
// required porting for a projects with non standard FV management policy.
// 
// 17    7/09/09 5:59p Oleksiyy
// Files clean-up, some headers added
//
// 16    5/21/09 4:44p Felixp
// ReFlash driver is updated to use FlashProtocol instead of Flash library
// functions.
//
// 15    1/02/09 1:14p Felixp
// Bug fix: initialize size before call to GetVariable
//
// 14    10/10/08 5:30p Felixp
//
// 13    3/12/08 2:55p Felixp
// Error code reporting when flash update failed added
//
// 12    10/19/07 6:23p Felixp
// Recovery Flash Update module extended to support Boot Block update.
// Boot block update can be enabled or disabled using SDL token.
// In addition to that there is an SDL token that enables/disables
// checkbox on the
// recovery setup page that user can use to enable or disable boot block
// update.
//
// 11    4/13/07 6:07p Ambikas
// Coding standard changes: updated the year in the AMI copyright
// header/footer.
//
// 10    1/26/07 10:31a Anandakrishnanl
// Added Flash Device Write Enabling and Disabling code to make the device
// Write wnable before Flash Block writes.
//
// 9     12/29/06 2:58p Felixp
// Updated to use new Flash Interface
//
// 8     12/22/06 9:38a Felixp
// Support for optional NVRAM reset based on user input added
//
// 7     12/20/06 1:36p Felixp
//
// 6     10/30/06 5:44p Felixp
// Updated to be complient with HII Spec. 0.92 (used to be 0.91)
//
// 5     10/27/06 11:48a Felixp
// Flash related external variables from Tokens.c are used (instead of
// global variables declared in Reflash.c)
//
// 4     8/24/06 9:19a Felixp
// x64 Support
//
// 3     4/12/06 5:49p Felixp
//
// 2     3/13/06 1:47a Felixp
//
// 1     12/01/05 9:35a Felixp
//
// 1     11/08/05 4:04a Felixp
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    ReFlash.c
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
#include <HOB.h>
#include <Flash.h>
#include <AmiCspLib.h>
#include <AmiHobs.h>
#include "ReFlash.h"


static EFI_GUID guidRecovery = RECOVERY_FORM_SET_GUID;
EFI_HANDLE ThisImageHandle;
FLASH_PROTOCOL *Flash;
EFI_HII_HANDLE ReflashHiiHandle = NULL;
UINT8 *RecoveryBuffer = NULL;
EFI_STATUS RecoveryStatus = EFI_SUCCESS;


EFI_HII_CONFIG_ACCESS_PROTOCOL CallBack = { NULL,NULL,FlashProgressEx };

CALLBACK_INFO SetupCallBack[] =
{
    // Last field in every structure will be filled by the Setup
    { &guidRecovery, &CallBack, RECOVERY_FORM_SET_CLASS, 0, 0},
};


//-------------------------------
//Before flash and After flash eLinks

typedef VOID (OEM_FLASH_UPDATE_CALLBACK) (VOID);
extern OEM_FLASH_UPDATE_CALLBACK OEM_BEFORE_FLASH_UPDATE_CALLBACK_LIST EndOfList;
extern OEM_FLASH_UPDATE_CALLBACK OEM_AFTER_FLASH_UPDATE_CALLBACK_LIST EndOfList;
OEM_FLASH_UPDATE_CALLBACK* OemBeforeFlashCallbackList[] = { OEM_BEFORE_FLASH_UPDATE_CALLBACK_LIST NULL };
OEM_FLASH_UPDATE_CALLBACK* OemAfterFlashCallbackList[] = { OEM_AFTER_FLASH_UPDATE_CALLBACK_LIST NULL };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    OemBeforeFlashCallback
// 
// Description:  This function executes OEM porting hooks before starting flash update
//               
//  Input:
// 	None
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OemBeforeFlashCallback(
    VOID
)
{
    UINT32 i;
    for(i = 0; OemBeforeFlashCallbackList[i] != NULL; i++)
        OemBeforeFlashCallbackList[i]();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:    OemAfterFlashCallback
// 
// Description:  This function executes OEM porting hooks after finishing flash update
//               
//  Input:
// 	None
//
//  Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID OemAfterFlashCallback(
    VOID
)
{
    UINT32 i;
    for(i = 0; OemAfterFlashCallbackList[i] != NULL; i++)
        OemAfterFlashCallbackList[i]();
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetHiiString
//
// Description: This function reads a string from HII
//
// Input:       IN EFI_HII_HANDLE   HiiHandle - Efi Hii Handle
//              IN STRING_REF       Token     - String Token
//              IN OUT UINTN        *pDataSize - Length of the StringBuffer
//              OUT EFI_STRING      *ppData - The buffer to receive the characters in the string.
//
// Output:      EFI_STATUS - Depending on result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetHiiString(
    IN EFI_HII_HANDLE HiiHandle,
    IN STRING_REF Token,
    IN OUT UINTN *pDataSize, 
    OUT EFI_STRING *ppData
)
{
    EFI_STATUS Status;
    
    if (!*ppData) *pDataSize=0;
    
    Status = HiiLibGetString(HiiHandle, Token, pDataSize, *ppData);
    if (!EFI_ERROR(Status)) return Status;
    //--- If size was too small free pool and try with right size, which was passed
    if (Status==EFI_BUFFER_TOO_SMALL)
    {
        if (*ppData) pBS->FreePool(*ppData);
        
        if (!(*ppData=Malloc(*pDataSize))) return EFI_OUT_OF_RESOURCES;
        
        Status = HiiLibGetString(HiiHandle, Token, pDataSize, *ppData);
    }
    
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ApplyUserSelection
//
// Description: This function updates flash parameteres based on user selection
// or Setup values
//
// Input:
//  IN BOOLEAN Interactive - if TRUE get selection from user input, otherwise
//                           use Setup values
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ApplyUserSelection(
    IN BOOLEAN Interactive
)
{
    EFI_STATUS Status;
    AUTOFLASH FlashUpdateControl;
    UINTN Size = sizeof(FlashUpdateControl);
    UINT32 i;

    if(Interactive) {
    /* get values from Setup Browser */
        Status = HiiLibGetBrowserData(&Size, &FlashUpdateControl, &guidRecovery, L"Setup");
    } else {
    /* get values from NVRAM */
        Status = pRS->GetVariable(L"Setup", &guidRecovery, NULL, &Size, &FlashUpdateControl);
    }
    if(EFI_ERROR(Status)) {
    /* no user selection, use defaults */
        FlashUpdateControl.UpdateMain = REFLASH_UPDATE_MAIN_BLOCK;
        FlashUpdateControl.UpdateBb = REFLASH_UPDATE_BOOT_BLOCK;
        FlashUpdateControl.UpdateNv = REFLASH_UPDATE_NVRAM;
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
        FlashUpdateControl.UpdateEC = REFLASH_UPDATE_EC_FIRMWARE;
#endif
    }

    for(i = 0; BlocksToUpdate[i].Type != FvTypeMax; i++) {
        switch(BlocksToUpdate[i].Type) {
            case FvTypeMain:
                BlocksToUpdate[i].Update = FlashUpdateControl.UpdateMain;
#if FtRecovery_SUPPORT
                if(FlashUpdateControl.UpdateBb == 1)
                    BlocksToUpdate[i].Update = TRUE;    //with fault tolerant recovery FV_MAIN is used for backup - force update
#endif
                break;
            case FvTypeBootBlock:
                BlocksToUpdate[i].Update = FlashUpdateControl.UpdateBb;
#if FtRecovery_SUPPORT
                if(IsTopSwapOn())   //if we're here BB update failed we use backup copy - force BB update again
                    BlocksToUpdate[i].Update = TRUE;
#endif
                break;
            case FvTypeNvRam:
                BlocksToUpdate[i].Update = FlashUpdateControl.UpdateNv;
                break;
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
            case FvTypeCustom:
                BlocksToUpdate[i].Update = FlashUpdateControl.UpdateEC;
                break;
#endif
            default:
                break;
        }
    }
}

//----------------------------------------------------------------------------
// IsRecovery prototypes
//----------------------------------------------------------------------------
// Bit Mask of checks to perform on Aptio FW Image
// 1- Capsule integrity
// 2- Verify Signature
// 3- Verify FW Key
// 4- Verify FW Version compatibility. 
//    To prevent possible re-play attack:
//    update current FW with older version with lower security.
// 5- Compare MonotonicCounters/date. Replay attack
//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateSetupStrings
//
// Description: This function updates status strings in setup window, based
// on execution results
//
// Input:
//  IN EFI_HII_HANDLE Handle - handle of Reflash setup formset (page)
//  IN EFI_STATUS Error - execution error if any
//  IN UINT32 FailedStage - in case of authentication error failed stage description
//
// Output:
//  None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID UpdateSetupStrings(
    IN EFI_HII_HANDLE Handle,
    IN EFI_STATUS Error,
    IN UINT32 FailedStage
)
{
    UINTN Size;
    EFI_STRING Template = NULL;
    EFI_STRING Template2 = NULL;
    CHAR16 ReportString[100];

    if(!EFI_ERROR(Error)) {
        GetHiiString(Handle, STRING_TOKEN(STR_SUBTITLE1_SUCCESS), &Size, &Template);
        if(FailedStage == 0)
            GetHiiString(Handle, STRING_TOKEN(STR_SUBTITLE2_SUCCESS), &Size, &Template2);
        else    //if we're here we're on manual BIOS rollback to older version
            GetHiiString(Handle, STRING_TOKEN(STR_SUBTITLE2_ROLLBACK_WARNING), &Size, &Template2);

        if(Template != NULL) {
            HiiLibSetString(Handle, STRING_TOKEN(STR_SUBTITLE1), Template);
            pBS->FreePool(Template);
        }

        if(Template2 != NULL) {
            HiiLibSetString(Handle, STRING_TOKEN(STR_SUBTITLE2), Template2);
            pBS->FreePool(Template2);
        }

        return;
    }

//Get Error string template
    GetHiiString(Handle, STRING_TOKEN(STR_SUBTITLE1_ERROR), &Size, &Template);
    if(Template != NULL) {
        HiiLibSetString(Handle, STRING_TOKEN(STR_SUBTITLE1), Template);
        pBS->FreePool(Template);
        Template = NULL;
    }

    GetHiiString(Handle, STRING_TOKEN(STR_SUBTITLE2_ERROR_TEMPLATE), &Size, &Template);
    switch(FailedStage) {
        case InvalidHeader:
            GetHiiString(Handle, STRING_TOKEN(STR_ERR), &Size, &Template2);
            break;
        case InvalidSignature:
            GetHiiString(Handle, STRING_TOKEN(STR_ERR1), &Size, &Template2);
            break;
        case IvalidPlatformKey:
            GetHiiString(Handle, STRING_TOKEN(STR_ERR2), &Size, &Template2);
            break;
        case InvalidFwVersion:
            GetHiiString(Handle, STRING_TOKEN(STR_ERR3), &Size, &Template2);
            break;
        default:
            GetHiiString(Handle, STRING_TOKEN(STR_ERR4), &Size, &Template2);
            break;
    }

    if((Template != NULL) && (Template2 != NULL)) {
        Swprintf(ReportString, Template, Error, Template2);
        HiiLibSetString(Handle, STRING_TOKEN(STR_SUBTITLE2), ReportString);
        pBS->FreePool(Template);
        pBS->FreePool(Template2);
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReFlashEntry
//
// Description: This is the standard EFI driver entry point called for
//              Recovery flash module initlaization
// Input:       IN EFI_HANDLE ImageHandle - ImageHandle of the loaded driver
//              IN EFI_SYSTEM_TABLE SystemTable - Pointer to the System Table
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI ReFlashEntry (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    static EFI_GUID guidHob = HOB_LIST_GUID;
    static EFI_GUID guidBootFlow = BOOT_FLOW_VARIABLE_GUID;
    static EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    UINT32 BootFlow = BOOT_FLOW_CONDITION_RECOVERY;
    EFI_HOB_HANDOFF_INFO_TABLE *pHit;
    UINTN Size;
    UINT32 Attributes;
    UINT32 FailedStage;
    EFI_STATUS Status = EFI_SUCCESS;

    AUTOFLASH AutoFlash = {
        (UINT8)(EFI_SUCCESS), 
        REFLASH_UPDATE_NVRAM, 
        REFLASH_UPDATE_BOOT_BLOCK, 
        REFLASH_UPDATE_MAIN_BLOCK
#if EC_FIRMWARE_UPDATE_INTERFACE_SUPPORT
       ,REFLASH_UPDATE_EC_FIRMWARE
#endif
    };

    ThisImageHandle = ImageHandle;
    InitAmiLib(ImageHandle,SystemTable);

    //Get Boot Mode
    pHit = GetEfiConfigurationTable(pST, &guidHob);
    
    //unload the module if we are not in recovery mode
   // TODO:need to distinguish between recovery and Flash Update
    if (!pHit || (pHit->BootMode != BOOT_IN_RECOVERY_MODE && pHit->BootMode != BOOT_ON_FLASH_UPDATE)) {
#if SUPPORT_WIN8_STYLE_FW_UPDATE
        InstallEsrtTable();
#endif
        return EFI_UNLOAD_IMAGE;
    }
    
    VERIFY_EFI_ERROR(pBS->LocateProtocol(&gFlashProtocolGuid, NULL, &Flash));
//Get Recovery Image verification status
    if(!EFI_ERROR(FindNextHobByGuid(&RecoveryHobGuid, &pHit))) {
        if(((EFI_HOB_GENERIC_HEADER *)pHit)->HobLength < sizeof(RECOVERY_IMAGE_HOB)) {
            //we got update from older Core here
            FailedStage = 0;
            RecoveryStatus = EFI_SUCCESS;
        } else {
            FailedStage = ((RECOVERY_IMAGE_HOB*)pHit)->FailedStage;
            RecoveryStatus = ((RECOVERY_IMAGE_HOB*)pHit)->Status;

            //Since RECOVERY_IMAGE_HOB Status field is byte long, we should set error bit by ourselves
            if(RecoveryStatus != NULL)
                RecoveryStatus |= EFI_ERROR_BIT;
        }
        RecoveryBuffer = (UINT8 *)(UINTN)((RECOVERY_IMAGE_HOB*)pHit)->Address;
    } else {    //Recovery Hob not found - should not happen, we always create this hob to report errors
        FailedStage = 0;
        RecoveryStatus = EFI_ABORTED;
    }

    AutoFlash.FailedRecovery = (UINT8)RecoveryStatus;

//Update Reflash parameters
    Size = sizeof(AUTOFLASH);
    Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
        pRS->SetVariable(L"Setup", &guidRecovery, Attributes, Size, &AutoFlash);

#if SUPPORT_WIN8_STYLE_FW_UPDATE
//Verify if we're on OS firmware update path
    Status = IsWin8Update((EFI_ERROR(RecoveryStatus)) ? TRUE : FALSE);
    if(Status == EFI_SUCCESS || Status == EFI_UNLOAD_IMAGE)
        return Status;
#endif

//Load setup page and create error message if necessary
    LoadResources(ImageHandle, sizeof(SetupCallBack) / sizeof(CALLBACK_INFO), SetupCallBack, NULL);
    ReflashHiiHandle = SetupCallBack[0].HiiHandle;
    pRS->SetVariable(L"BootFlow", &guidBootFlow, EFI_VARIABLE_BOOTSERVICE_ACCESS, sizeof(BootFlow), &BootFlow);

    UpdateSetupStrings(ReflashHiiHandle, RecoveryStatus, FailedStage);

    return EFI_SUCCESS;
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