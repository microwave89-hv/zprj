//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/BootScriptHide/BootScriptHideDxe.c 1     9/10/14 6:31p Aaronp $
//
// $Revision: 1 $
//
// $Date: 9/10/14 6:31p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/BootScriptHide/BootScriptHideDxe.c $
// 
// 1     9/10/14 6:31p Aaronp
// First addition of BootScriptHide emodule.
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:	BootScriptHideDxe.c
//
// Description:	Source file for the DXE driver. This file contains the 
//              code to trigger the SWSMI that will save the boot scripts
//              into SMM. Depending on the boot path, either a legacy
//              boot event or an Exit Boot Services notification will
//              notify the trigger function
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol/SmmControl2.h>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      GenerateSaveBootScriptSwSmi
//
//  Description:    Callback function called when either Exit Boot Services is called, 
//                  or a legacy boot event is raised. This function will use the 
//                  SmmControl protocol to trigger a SWSMI.
//
//  Input:
//  IN EFI_EVENT Event - Event that caused this function to be called
//  IN VOID *Context - Context for the event that triggered this function
//
//  Output:
//  None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID GenerateSaveBootScriptSwSmi (
    IN EFI_EVENT Event, IN VOID *Context
){
    static BOOLEAN BootScriptSaved = FALSE;
    EFI_STATUS Status;
    EFI_SMM_CONTROL2_PROTOCOL  *SmmControl;
    UINT8 SwSmiValue = BOOT_SCRIPT_SAVE_SW_SMI_VALUE;
    
    if (BootScriptSaved){
        pBS->CloseEvent(Event);
        return;
    }
    Status = pBS->LocateProtocol (&gEfiSmmControl2ProtocolGuid, NULL, (VOID **)&SmmControl);
    if (EFI_ERROR(Status)) return;
    SmmControl->Trigger (SmmControl, &SwSmiValue, NULL, FALSE, 0);
    BootScriptSaved = TRUE;
    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:      BootScriptHideDxeEntryPoint
//
//  Description:    Entry point for the DXE driver. Entry point will register a 
//                  legacy boot event notification function, and a Exit Boot Services
//                  event handler.  The same function is called for the legacy boot
//                  event and the exit boot services notification function.
//
//  Input:
//  IN EFI_HANDLE ImageHandle - The handle that corresponds this this loaded DXE driver
//  IN EFI_SYSTEM_TABLE *SystemTable - Pointer to the EFI System Table
//
//  Output:
//  EFI_STATUS The return status of this function
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EFIAPI BootScriptHideDxeEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_EVENT Event;
    
    InitAmiLib(ImageHandle,SystemTable);
    // We're using TPL_NOTIFY here (as oppose to TPL_CALLBACK) to make sure our callback is called prior to NVRAM driver callback.
    // Otherwise we may be unable to read boot time variable in our SMI handler.
    CreateLegacyBootEvent(TPL_NOTIFY, &GenerateSaveBootScriptSwSmi, NULL, &Event);
    pBS->CreateEvent(
        EVT_SIGNAL_EXIT_BOOT_SERVICES,TPL_NOTIFY,
        &GenerateSaveBootScriptSwSmi, NULL, &Event
    );
    return EFI_SUCCESS;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************