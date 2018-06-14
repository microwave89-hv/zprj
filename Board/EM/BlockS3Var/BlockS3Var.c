//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/BlockS3Var/BlockS3Var.c 1     6/18/15 4:02a Calvinchen $
//
// $Revision: 1 $
//
// $Date: 6/18/15 4:02a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/BlockS3Var/BlockS3Var.c $
// 
// 1     6/18/15 4:02a Calvinchen
// [TAG]  		EIP224171
// [Category]  	New Feature
// [Description]  	Initial check-in for New Security Vulnerabilities :
// Intel-TA-201505-001
// [Files]  		BlockS3Var.cif
// BlockS3Var.chm
// BlockS3Var.sdl
// BlockS3Var.mak
// BlockS3Var.c
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        BlockedS3Var.C
//
// Description: This file contains code for blocking Variables at runtime.
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------


#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <BlockedS3Var.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)
#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
    { 0x3aa83745, 0x9454, 0x4f7a, { 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e } }

// Type Definition(s)
typedef struct {
    CHAR16      *Name;
    EFI_GUID    Guid;
} VAR_STRUCT;

// Function Prototype(s)
VOID BdsEvtFunc (
    IN EFI_EVENT Event,
    IN VOID      *Context
);

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
VAR_STRUCT  gBlockedS3VarList[] = { BLOCKED_S3_VAR_ELINK
            {NULL, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}};
static BOOLEAN  gInitializationCompleted = FALSE;
static BOOLEAN  gEndOfDxe = FALSE;
static EFI_GUID gBdsConnectDriversProtocolGuid = BDS_CONNECT_DRIVERS_PROTOCOL_GUID;

// External Declaration(s)
extern  EFI_BOOT_SERVICES       *pBS;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SetVariableS3Hook
//
// Description: This function checks the input Variable whether it needs to
//              be blocked or not.
//
// Input:       VariableName - Pointer to Variable Name in Unicode
//              VendorGuid - Pointer to Variable GUID
//              Attributes - Attributes of the Variable
//              DataSize - Size of the Variable
//              Data - Pointer to memory where Variable data is stored
//
// Output:      EFI_STATUS
//                  EFI_UNSUPPORTED - The Variable isn't found.
//                  EFI_WRITE_PROTECTED - The Variable is found.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SetVariableS3Hook (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32   Attributes,
    IN UINTN    DataSize,
    IN VOID     *Data )
{
    EFI_STATUS      Status;
    EFI_EVENT       BdsEvt;
    VOID            *Registration = NULL;
    UINT32          i;
    
    if (gBlockedS3VarList[0].Name == NULL) return EFI_UNSUPPORTED; // no Variable needs to be checked.

    if (!gInitializationCompleted) {
        gInitializationCompleted = TRUE;
        if (!pSmst) {
            Status = pBS->CreateEvent(EVT_NOTIFY_SIGNAL, TPL_CALLBACK, BdsEvtFunc, NULL, &BdsEvt);
            if (EFI_ERROR(Status)) {
                TRACE((TRACE_ALWAYS,"Unable to create BDS event\n"));
                return Status;
            }
            pBS->RegisterProtocolNotify (\
                            &gBdsConnectDriversProtocolGuid, BdsEvt, &Registration);
        }
    }

    if (gEndOfDxe || pSmst) {
        for (i = 0; gBlockedS3VarList[i].Name != NULL; i++) {
            if (!Wcscmp(VariableName, gBlockedS3VarList[i].Name) && !guidcmp(VendorGuid, &gBlockedS3VarList[i].Guid)) {
                    return EFI_WRITE_PROTECTED;
            }
        }
    }

    return EFI_UNSUPPORTED;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BdsEvtFunc
//
// Description: This function is called when BDS is ready to connect drivers.
//
// Input:       Event   - Event of callback
//              Context - Context of callback.
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID 
BdsEvtFunc (
    IN EFI_EVENT Event,
    IN VOID      *Context )
{
    gEndOfDxe = TRUE;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************