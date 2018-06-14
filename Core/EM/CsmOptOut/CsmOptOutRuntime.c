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

///**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOutRuntime.c 4     8/29/12 2:25p Artems $
//
// $Revision: 4 $
//
// $Date: 8/29/12 2:25p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOutRuntime.c $
// 
// 4     8/29/12 2:25p Artems
// [TAG]  		EIP98995
// [Category]  	Improvement
// [Description]  	When enable secure boot disable CSM but preserve CSM
// optout options setting,
// so once secure boot is disabled they can be restored
// [Files]  		CsmOptOut.sd, CsmOptOut.sdl, CsmOptOutSetup.c
// CsmOptOutRuntime.c
// 
// 3     6/20/12 6:10p Artems
// [TAG]  		EIP83692
// [Category]  	Improvement
// [Description]  	CSM OptOut setup page grayed out if secure boot is
// enabled
// CSM OptOut PlatformOverride protocol modified to fix SCT bugs
// Removed support for Launch CSM "Auto" option
// 
// [Files]  		CsmOptOut.c CsmOptOut.mak CsmOptOut.sd CsmOptOut.sdl
// CsmOptOut.uni CsmOptOutRuntime.c CsmOptOutSetup.c
// 
// 2     3/23/12 6:26p Artems
// EIP 84012: Added fix to execute entrypoint only once
// 
// 1     3/16/12 4:57p Artems
// Initial check-in
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  CsmOptOutRuntime.c
//
// Description: This is the entry point of CsmOptOut driver
//
//<AMI_FHDR_END>
//**********************************************************************


//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AmiLoadCsmPolicy.h>
#include <ImageAuthentication.h>

//----------------------------------------------------------------------------

static EFI_GUID SetupGuid = SETUP_GUID;
static EFI_GUID AmiLoadCsmGuid = AMI_LOAD_CSM_GUID;
static EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CsmOptOutNotInSmmEntry
//
// Description: CsmOptOut runtime callback for variable services
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CsmOptOutNotInSmmEntry(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle = NULL;
    SETUP_DATA SetupData;
    UINTN Size;
    UINT8 CurrentCsmState;
    UINT32 Attributes;
    BOOLEAN SecureBoot;

    Size = sizeof(UINT8);
    Status = pRS->GetVariable(EFI_SECURE_BOOT_NAME, &gEfiGlobalVariableGuid, NULL, &Size, &CurrentCsmState);
    SecureBoot = (!EFI_ERROR(Status) && CurrentCsmState != 0) ? TRUE : FALSE;

    Size = sizeof(SETUP_DATA);
    Status = pRS->GetVariable(L"Setup", &SetupGuid, &Attributes, &Size, &SetupData);

    CurrentCsmState = (SecureBoot) ? 0 : (EFI_ERROR(Status)) ? DEFAULT_CSM_LAUNCH_POLICY : SetupData.CsmLaunchPolicy;
    if(CurrentCsmState == 1) {
        Status = pBS->InstallMultipleProtocolInterfaces(&Handle, 
                                        &AmiLoadCsmGuid, NULL, 
                                        NULL);
        ASSERT_EFI_ERROR(Status);
    }
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CsmOptOutRuntimeEntry
//
// Description: CsmOptOut runtime callback for variable services
//
// Input:		
//  IN EFI_EVENT Event - Callback event
//  IN VOID *Context - pointer to calling context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CsmOptOutRuntimeEntry(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    UINT32 Var;
    UINTN Size = sizeof(UINT32);

    InitAmiLib(ImageHandle, SystemTable);

    Status = pRS->GetVariable(L"AmiLoadCsm", &AmiLoadCsmGuid, NULL, &Size, &Var);
    if(!EFI_ERROR(Status))
        return EFI_ALREADY_STARTED;

    Size = sizeof(UINT32);
    Var = 0xdeadbeef;
    Status = pRS->SetVariable(L"AmiLoadCsm", &AmiLoadCsmGuid, EFI_VARIABLE_BOOTSERVICE_ACCESS, Size, &Var);
    return CsmOptOutNotInSmmEntry(ImageHandle, SystemTable);
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
