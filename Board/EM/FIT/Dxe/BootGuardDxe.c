//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardDxe.c 1     2/25/13 1:11a Bensonlai $
//
// $Revision: 1 $
//
// $Date: 2/25/13 1:11a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardDxe.c $
// 
// 1     2/25/13 1:11a Bensonlai
// [TAG]  		EIP114386
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
// for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
// BIOS Writer's Guide - Rev 0.8.1
// [Files]  		BootGuardDxe.cif
// BootGuardDxe.c
// BootGuardDxe.h
// BootGuardDxe.sdl
// BootGuardDxe.dxs
// BootGuardDxe.mak
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardDxe.c
//
// Description: Chain of trust for Dxe
//
//<AMI_FHDR_END>
//**********************************************************************

#include "BootGuardDxe.h"

VOID
BootGuardDxeCallback (
    IN EFI_EVENT Event,
    IN VOID      *Context
)
{
    EFI_INPUT_KEY           Key;
    EFI_STATUS              Status;

    gST->ConOut->ClearScreen (gST->ConOut);

    gST->ConOut->OutputString (
        gST->ConOut,
        L"Anchor Cove verified DXE that is fail\n\r"
    );

    gST->ConOut->OutputString (
        gST->ConOut,
        L"System will shutdown\n\r"
    );

    gST->ConOut->OutputString (
        gST->ConOut,
        L"Press any key\n\r"
    );

    do {
        Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    } while (Status != EFI_SUCCESS);

    gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
    EFI_DEADLOOP ();

    gBS->CloseEvent (Event);
}

VOID
BootGuardDxeRegisterCallBack (
    VOID
)
{
    EFI_EVENT   Event;
    VOID        *NotifyReg;
    EFI_STATUS  Status;

    Status = gBS->CreateEvent (
                 EFI_EVENT_NOTIFY_SIGNAL,
                 EFI_TPL_CALLBACK,
                 BootGuardDxeCallback,
                 NULL,
                 &Event
             );

    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    Status = gBS->RegisterProtocolNotify (
                 &gNotifyProtocolGuid ,
                 Event,
                 &NotifyReg
             );

    if ( EFI_ERROR(Status) ) {
        ASSERT_EFI_ERROR (Status);
        return;
    }

    return;
}

EFI_STATUS
BootGuardDxeEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_GUID                      AmiBootGuardHobGuid = AMI_ANCHOR_COVE_HOB_GUID;
    AMI_ANCHOR_COVE_HOB           *AmiBootGuardHobPtr;
    PCH_SERIES                    PchSeries = GetPchSeries();
    EFI_BOOT_MODE                 BootMode;
    EFI_PEI_HOB_POINTERS          HobList;

    if ( PchSeries != PchLp ) {
        return   EFI_SUCCESS;
    }

    if ( IsBootGuardSupported() == FALSE ) {
        return   EFI_SUCCESS;
    }

    DEBUG ((EFI_D_INFO, "[BootGuardDxe.c] : Entry Point...\n"));

    //
    // Check Boot Type
    //
    EfiGetSystemConfigurationTable (&gEfiHobListGuid, (VOID **) &HobList.Raw);
    if (HobList.Header->HobType != EFI_HOB_TYPE_HANDOFF) {
        DEBUG ((EFI_D_ERROR, "[BootGuardDxe.c] : Get HOB fail\n"));
        return EFI_SUCCESS;
    }

    BootMode  = HobList.HandoffInformationTable->BootMode;
    if ( BootMode == BOOT_IN_RECOVERY_MODE ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardDxe.c] : In the BOOT_IN_RECOVERY_MODE\n"));
        return   EFI_SUCCESS;
    }

    AmiBootGuardHobPtr = GetFirstGuidHob (&AmiBootGuardHobGuid);
    if (AmiBootGuardHobPtr == NULL) {
        DEBUG ((EFI_D_ERROR, "[BootGuardDxe.c] : AmiBootGuard DXE Hob not available\n"));
        return   EFI_NOT_FOUND;
    }

    if ( AmiBootGuardHobPtr->AmiBootGuardVerificationforPEItoDXEFlag == 0 ) {
        BootGuardDxeRegisterCallBack();
    }

    DEBUG ((EFI_D_INFO, "[BootGuardDxe.c] : Entry End...\n"));

    return   EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
