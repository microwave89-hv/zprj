//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS SMM/CmosManagerSmm.c 8     1/25/12 2:38p Michaela $
//
// $Revision: 8 $
//
// $Date: 1/25/12 2:38p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS SMM/CmosManagerSmm.c $
// 
// 8     1/25/12 2:38p Michaela
// 
// 7     1/25/12 2:37p Michaela
// [TAG]         EIP56197
// [Category]    New Feature
// [Severity]    Normal
// [Description] CMOS Manager Support in Runtime Code
// [Files]       CmosManager.sdl
//               CmosSetup.uni
//               CmosMessages.uni
//               CmosManagerSmm.cif
//               CmosAccess.h
//               CmosManagerSmm.c
//               CmosAccess.asl
// 
// 6     12/11/11 8:56p Michaela
// 
// 4     11/30/11 11:48p Michaela
// [TAG]         EIP75889
// [Category]    Spec Update
// [Severity]    Normal
// [Description] Support Setup Customization
// [Files]       CmosManager.sdl
//               CmosSetup.sd
//               CmosSetup.uni
//               CmosMessages.uni
// 
// 3     3/16/11 2:45p Michaela
// 
// 2     3/05/10 4:54p Michaela
// 
// 1     11/10/09 8:45p Michaela
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:    CmosManagerSmm.c
//
// Description: Contains the routines that initialize the CMOS manager's
//              SMM services.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "CmosManagerSmm.h"
#include <Protocol\Reset.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\AcpiSupport.h>
#include <Acpi.h>
#include <AcpiRes.h>

EFI_CMOS_ACCESS_INTERFACE   *gCmos = NULL;
CMOS_SMM_CONTEXT            *gAslContext = NULL;  // ASL communication buffer

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   SmiHandler
//
// Description:
//      This is called from SMM or ASL code to access CMOS during
//      runtime.
//
// Input:
//      IN EFI_HANDLE DispatchHandle
//      IN EFI_SMM_SW_DISPATCH_CONTEXT *DispatchContext
//
// Output:
//      NONE
//
// Modified:
//      NONE
//
// Referrals:
//
// Notes:
//      
//
//<AMI_PHDR_END>
//**********************************************************************

VOID SmiHandler (
    IN  EFI_HANDLE                    DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext )
{

    UINT8               Function = (UINT8)DispatchContext->SwSmiInputValue;
    EFI_STATUS          Status = EFI_NOT_FOUND;

    if (Function == CSMI){
        if (gCmos == NULL){
            gAslContext->Status = 0; // FALSE => operation failed
        }
        else {
            switch (gAslContext->Opcode) {
            case 0:  // Write from the communication buffer
                Status = gCmos->Write(gCmos, gAslContext->CmosToken, 
                    gAslContext->CmosByte);
                break;
            case 1:  // Read into the communication buffer
                Status = gCmos->Read(gCmos, gAslContext->CmosToken, 
                    &gAslContext->CmosByte);
                break;
            }
            if (EFI_ERROR(Status)){
               gAslContext->Status = 0; // FALSE => operation failed
            }
            else {
               gAslContext->Status = 1; // FALSE => operation success
            }
        }
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InSmmFunction
//
// Description:
//      This function is executed from SMM in order to install the SMRAM-based
//      CMOS Access Interface pointer.
//
// Input:
//      IN EFI_HANDLE ImageHandle
//                  - Image handle
//      IN EFI_SYSTEM_TABLE *SystemTable
//                  - System table pointer
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//               *  Initializes/Installs the EFI_CMOS_ACCESS_INTERFACE 
//                  Protocol for SMM.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InSmmFunction (
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable )
{
    EFI_STATUS                      Status;
    EFI_CMOS_MANAGER_INTERFACE      *Mgr;
    EFI_SMM_SW_DISPATCH_CONTEXT     SwContext;
    EFI_SMM_SW_DISPATCH_PROTOCOL    *SwDispatch;
    EFI_HANDLE                      SwHandle  = NULL;
    
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CmosManagerSMM Entry\n" ));
 
    //-----------------------------------------------------------------------
    // Initialize the manager interface and, at this point, only check for  
    // interface initialization errors.
    //-----------------------------------------------------------------------

    Mgr = NewCmosManagerInterface(NULL);
    if ( Mgr == NULL || !Mgr->CheckStatus(Mgr, CMOS_VALID_INTERFACE) ) {
        return  Status = EFI_UNSUPPORTED;
    }
    if ( Mgr->CheckStatus( Mgr, CMOS_INTERFACE_ALREADY_INSTALLED) )
        return  Status = EFI_SUCCESS;

    //-----------------------------------------------------------------------
    // Handle specific reported errors.
    //
    // Note:    All boot time error conditions should have been handled
    //          before execution gets here.
    //
    //          All that is needed is to report the status for debugging.
    //-----------------------------------------------------------------------

    if (  Mgr->CheckStatus(Mgr, CMOS_BAD_BATTERY) ) {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "CmosManagerSMM: CMOS_BAD_BATTERY = TRUE\n" ));

        // Default handler is to continue from DXE phase
    }
    else if ( Mgr->CheckAnyStatus(Mgr,   CMOS_BAD_CHECKSUM 
                                       | CMOS_OPTIMAL_DEFAULTS_ENABLED) )
    {
#if (FULL_CMOS_MANAGER_DEBUG)
        if (  Mgr->CheckStatus(Mgr, CMOS_BAD_CHECKSUM) ) {
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "CmosManagerSMM: CMOS_BAD_CHECKSUM = TRUE\n" ));
        }

        if (  Mgr->CheckStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED) ) {
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "CmosManagerSMM: CMOS_OPTIMAL_DEFAULTS_ENABLED = TRUE\n" ));
        }
#endif
    }


    //-----------------------------------------------------------------------
    // Install the CMOS Access interface
    //-----------------------------------------------------------------------

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "CmosManagerSMM: Installing CMOS Access SMM Protocol @ 0x%x\n",
        Mgr ));
    Mgr->InstallAccessInterface(Mgr);
    if ( !Mgr->CheckStatus(Mgr, CMOS_VALID_MANAGER) ){
        CMOS_TRACE((CMOS_TRACE_ALWAYS, 
            "CmosManagerSMM: Invalid interface\n" ));
        return Status = EFI_UNSUPPORTED;
    }

    // Update the module-scope interface pointer.
    gCmos = (EFI_CMOS_ACCESS_INTERFACE*) &Mgr->Access;

    //Register the SW SMI handler
    Status = pBS->LocateProtocol (&gEfiSmmSwDispatchProtocolGuid, 
        NULL, &SwDispatch);
    ASSERT_EFI_ERROR(Status);

    SwContext.SwSmiInputValue = CSMI;
    Status = SwDispatch->Register (SwDispatch, SmiHandler, &SwContext, 
        &SwHandle);

    if (EFI_ERROR(Status)){
        CMOS_TRACE((CMOS_TRACE_ALWAYS,
            "InSmmFunction: could not register...\n"));
    }
    ASSERT_EFI_ERROR(Status);

    CMOS_TRACE((CMOS_TRACE_ALWAYS, "InSmmFunction Registered.\n"));

    return Status = EFI_SUCCESS;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetAslNameObject
//
// Description:
//      This function returns the 64-bit value assigned to the ASL named
//      object.
//
// Input:
//      IN ACPI_HDR *PDsdt 
//                  - pointer to the DSDT table
//      IN UINT8 *ObjName
//                  - pointer to the name string
//      OUT UINT64 *Value
//                  - pointer to the value to be updated
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//      N/A
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS  GetAslNameObject(
    IN  ACPI_HDR  *PDsdt,
    IN  UINT8     *ObjName,
    OUT UINT64    *Value)
{
    ASL_OBJ_INFO    Obj;
    EFI_STATUS      Status;

    if (PDsdt->Signature != DSDT_SIG){
        return EFI_INVALID_PARAMETER;
    }

    Status = GetAslObj((UINT8*)(PDsdt+1), PDsdt->Length-sizeof(ACPI_HDR)-1,
        ObjName, otName, &Obj);
    
    if (!EFI_ERROR(Status)){
        *Value = *((UINT64*)((UINT8*)Obj.DataStart + 1));
    }
    
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: UpdateAslCommunicationBuffer
//
// Description:
//      This function is executed in non-SMM in order to allocate the 
//      runtime communication buffer used by the \CMOS.ACCE asl method
//      to use CMOS Manager services at runtime.
//
// Input:
//      N/A
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//      N/A
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS UpdateAslCommunicationBuffer ( VOID )
{
    EFI_PHYSICAL_ADDRESS  DsdtAddress = NULL;
    ACPI_HDR              *Dsdt = NULL;
    UINT64                CurrentValue;
    EFI_STATUS            Status;

    // Get a pointer to the DSDT.

    Status = LibGetDsdt(&DsdtAddress, EFI_ACPI_TABLE_VERSION_ALL);
    if (EFI_ERROR(Status)){
        CMOS_TRACE((CMOS_TRACE_ALWAYS, "CMOS Manager: failed to get DSDT\n"));
        goto EXIT;
    }
    Dsdt = (ACPI_HDR*)DsdtAddress;

    // Get the current value of \CCOM.

    Status = GetAslNameObject(Dsdt, "CCOM", &CurrentValue);
    if (EFI_ERROR(Status)){
        CMOS_TRACE((CMOS_TRACE_ALWAYS, "Could not get \\CCOM ASL object.\n"));
        goto EXIT;
    }
    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CurrentValue of \\CCOM is 0x%lX\n",
        CurrentValue));

    // If \CCOM has not been updated yet, allocate the runtime communication
    // buffer and update the ASL object.  Otherwise, save the value of 
    // \CCOM to the global variable in SMRAM scope.

    if (CurrentValue == 0x0123456789ABCDEF){
        Status = pBS->AllocatePool(EfiRuntimeServicesData, 
            sizeof(CMOS_SMM_CONTEXT), &gAslContext);
        if (EFI_ERROR(Status)){
            CMOS_TRACE((CMOS_TRACE_ALWAYS, 
                "failed to allocate CMOS_SMM_CONTEXT\n"));
            goto EXIT;
        }
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "CMOS_SMM_CONTEXT allocated to 0x%lX\n", gAslContext ));

        Status = UpdateAslNameObject(Dsdt, "CCOM", (UINT64)gAslContext);
        if (EFI_ERROR(Status)){
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "failed to update \\CCOM\n"));
            goto EXIT;
        }
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Updated \\CCOM ASL object.\n"));
    }
    else {
        gAslContext = (CMOS_SMM_CONTEXT*)CurrentValue;
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "gAslContext was updated\n"));
    }

EXIT:
    return Status;
}


//---------------------------------------------------------------------------
//  SMM entry point function
//
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerSmmEntry
//
// Description:
//      This function is the entrypoint for installing the SMM driver for
//      CMOS Manager.
//
// Input:
//      IN EFI_HANDLE ImageHandle
//                  - Image handle
//      IN EFI_SYSTEM_TABLE *SystemTable
//                  - System table pointer
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//               *  Initializes/Installs the EFI_CMOS_ACCESS_INTERFACE 
//                  Protocol for SMM.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosManagerSmmEntry (
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable )
{
    EFI_STATUS               Status = EFI_SUCCESS;

    InitAmiLib(ImageHandle, SystemTable);

#if CMOS_MANAGER_ASL_SUPPORT
    Status = UpdateAslCommunicationBuffer();
    if (EFI_ERROR(Status)){
        CMOS_TRACE((CMOS_TRACE_ALWAYS,
            "CMOS Manager failed to update ASL communication buffer\n"));
        ASSERT_EFI_ERROR(Status);
    }
#endif

    return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);

}


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
