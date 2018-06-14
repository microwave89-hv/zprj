//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBSmi.c 2     4/16/13 5:29a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/16/13 5:29a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBSmi.c $
// 
// 2     4/16/13 5:29a Thomaschen
// 
// 1     2/12/12 10:38p Victortu
// Intel SharkBay CRB initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBSMI.c
//
// Description: This file contains code for all CRB SMI events
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Produced Protocols

// Consumed Protocols
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\S3SmmSaveState.h>
#include <Protocol\SmmBase2.h>
#include <Protocol\SmmSwDispatch2.h>
#include <Protocol\SmmSxDispatch2.h>
#else
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmSxDispatch.h>
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#define CRB_S3_SAVE_PROTOCOL         EFI_S3_SAVE_STATE_PROTOCOL
#define CRB_SMM_SW_DISPATCH_PROTOCOL EFI_SMM_SW_DISPATCH2_PROTOCOL
#define CRB_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_REGISTER_CONTEXT
#define CRB_SMM_SX_DISPATCH_PROTOCOL EFI_SMM_SX_DISPATCH2_PROTOCOL
#define CRB_SMM_SX_DISPATCH_CONTEXT  EFI_SMM_SX_REGISTER_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS   EFI_SUCCESS
#else
#define CRB_S3_SAVE_PROTOCOL         EFI_BOOT_SCRIPT_SAVE_PROTOCOL
#define CRB_SMM_SW_DISPATCH_PROTOCOL EFI_SMM_SW_DISPATCH_PROTOCOL
#define CRB_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_DISPATCH_CONTEXT
#define CRB_SMM_SX_DISPATCH_PROTOCOL EFI_SMM_SX_DISPATCH_PROTOCOL
#define CRB_SMM_SX_DISPATCH_CONTEXT  EFI_SMM_SX_DISPATCH_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS
#endif

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

CRB_S3_SAVE_PROTOCOL *gBootScriptSave = NULL;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   GetCRBSmiContext
//
// Description: This is a template CRB SMI GetContext for Porting.
//
// Input:       None
//
// Output:      None
//
// Notes:       Here is the control flow of this function:
//              1. Check if CRB Smi source.
//              2. If yes, return TRUE.
//              3. If not, return FALSE.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN GetCRBSmiContext (VOID)
{
    // Porting if needed
    return FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBSmiHandler
//
// Description: This is a template CRB SMI Handler for Porting.
//
// Input:       None
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CRBSmiHandler (VOID)
{
    // Porting if needed
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBSwSmiHandler
//
// Description: This is a template CRB software SMI Handler for Porting.
//
// Input:       PI 0.91, 1.0
//                  DispatchHandle   - SMI dispatcher handle
//                  *DispatchContext - Pointer to the dispatch context
//              PI 1.1, 1.2
//                  DispatchHandle  - SMI dispatcher handle
//                  *DispatchContext- Points to an optional S/W SMI context
//                  CommBuffer      - Points to the optional communication
//                                    buffer
//                  CommBufferSize  - Points to the size of the optional
//                                    communication buffer
//
// Output:      EFI_STATUS if the new SMM PI is applied.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
EFI_STATUS CRBSwSmiHandler (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID CRBSwSmiHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
#endif
{
    // Porting if needed
    return SMM_CHILD_DISPATCH_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBSxSmiHandler
//
// Description: This is a template CRB Sx SMI Handler for Porting.
//
// Input:       PI 0.91, 1.0
//                  DispatchHandle   - SMI dispatcher handle
//                  *DispatchContext - Pointer to the dispatch context
//              PI 1.1, 1.2
//                  DispatchHandle  - SMI dispatcher handle
//                  *DispatchContext- Points to an optional Sx SMI context
//                  CommBuffer      - Points to the optional communication
//                                    buffer
//                  CommBufferSize  - Points to the size of the optional
//                                    communication buffer
//
// Output:      EFI_STATUS if the new SMM PI is applied.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
EFI_STATUS CRBSxSmiHandler (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
VOID CRBSxSmiHandler (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SX_DISPATCH_CONTEXT  *DispatchContext )
#endif
{
    // Porting if needed
    return SMM_CHILD_DISPATCH_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   CRBChildDispatcher
//
// Description: This is an entry for CRB SMM Child Dispatcher Handler.
//
// Input:       PI 0.91, 1.0
//                  SmmImageHandle       - SMI Image Hander
//                  *CommunicationBuffer - Pointer to optional communication 
//                                         buffer                            
//                  *SourceSize          - Pointer to size of communication 
//                                         buffer                           
//              PI 1.1, 1.2
//                  DispatchHandle  - SMI dispatcher handle
//                  *DispatchContext- Pointer to the dispatched context
//                  CommBuffer      - Pointer to a collection of data in
//                                    memory that will be conveyed from a
//                                    non-SMM environment into an SMM 
//                                    environment 
//                  CommBufferSize  - Pointer to the size of the CommBuffer
//
// Output:      EFI_STATUS
//                  EFI_HANDLER_SUCCESS
//
// Referrals:   GetCRBSmiContext, CRBSmiHandler 
//
// Notes:       Here is the control flow of this function:
//              1. Read SMI source status registers.
//              2. If source, call handler.
//              3. Repeat #2 for all sources registered.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CRBChildDispatcher (
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
#else
    IN EFI_HANDLE   SmmImageHandle,
    IN OUT VOID     *CommunicationBuffer OPTIONAL,
    IN OUT UINTN    *SourceSize OPTIONAL )
#endif
{
    if (GetCRBSmiContext()) CRBSmiHandler();

    return EFI_HANDLER_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InSmmFunction
//
// Description: Installs CRB SMM Child Dispatcher Handler.
//
// Input:       ImageHandle - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The SMM Base protocol is not found.
//                  EFI_SUCCESS   - Installs CRB SMM Child Dispatcher Handler
//                                  successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                   Status;
    CRB_SMM_SW_DISPATCH_PROTOCOL *pSwDispatch;
    CRB_SMM_SX_DISPATCH_PROTOCOL *pSxDispatch;
    CRB_SMM_SW_DISPATCH_CONTEXT  SwContext = {CRB_SWSMI};
    CRB_SMM_SX_DISPATCH_CONTEXT  SxContext = {SxS3, SxEntry};
    EFI_HANDLE                   Handle;
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    EFI_HANDLE                   RootHandle;
#else
    EFI_SMM_BASE_PROTOCOL        *SmmBaseProtocol;
#endif

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
    Status = InitAmiSmmLib( ImageHandle, SystemTable );
    if (EFI_ERROR(Status)) return Status;

    Status  = pSmst->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid, \
                                        NULL, \
                                        &pSwDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSwDispatch->Register( pSwDispatch, \
                                         CRBSwSmiHandler, \
                                         &SwContext, \
                                         &Handle );
    }

    Status  = pSmst->SmmLocateProtocol( &gEfiSmmSxDispatch2ProtocolGuid, \
                                        NULL, \
                                        &pSxDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSxDispatch->Register( pSxDispatch, \
                                         CRBSxSmiHandler, \
                                         &SxContext, \
                                         &Handle );
    }

    Status = pSmst->SmmLocateProtocol( &gEfiS3SmmSaveStateProtocolGuid, \
                                       NULL, \
                                       &gBootScriptSave );
    ASSERT_EFI_ERROR(Status);

    Status  = pSmst->SmiHandlerRegister( CRBChildDispatcher, \
                                         NULL, \
                                         &RootHandle );
#else
    Status = pBS->LocateProtocol( &gEfiSmmBaseProtocolGuid, \
                                  NULL, \
                                  &SmmBaseProtocol );
    if (EFI_ERROR(Status)) return Status;

    Status  = pBS->LocateProtocol( &gEfiSmmSwDispatchProtocolGuid, \
                                   NULL, \
                                   &pSwDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSwDispatch->Register( pSwDispatch, \
                                         CRBSwSmiHandler, \
                                         &SwContext, \
                                         &Handle );
    }

    Status = pBS->LocateProtocol( &gEfiSmmSxDispatchProtocolGuid, \
                                  NULL, \
                                  &pSxDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSxDispatch->Register( pSxDispatch, \
                                         CRBSxSmiHandler, \
                                         &SxContext, \
                                         &Handle );
    }

    Status = pBS->LocateProtocol( &gEfiBootScriptSaveGuid, \
                                  NULL, \
                                  &gBootScriptSave );
    ASSERT_EFI_ERROR(Status);

    //Register call backs
    Status = SmmBaseProtocol->RegisterCallback( SmmBaseProtocol, \
                                                ImageHandle, \
                                                CRBChildDispatcher, \
                                                FALSE, \
                                                FALSE );
#endif
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitializeCRBSmm
//
// Description: Installs CRB SMM Child Dispatcher Handler.
//
// Input:       ImageHandle - Image handle
//              *SystemTable - Pointer to the system table
//
// Output:      EFI_STATUS
//                  EFI_NOT_FOUND - The SMM Base protocol is not found.
//                  EFI_SUCCESS   - Installs CRB SMM Child Dispatcher Handler
//                                  successfully.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InitializeCRBSmm (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    InitAmiLib(ImageHandle, SystemTable);
    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
