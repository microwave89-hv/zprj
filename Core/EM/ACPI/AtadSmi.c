//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
// $Header: /Alaska/BIN/Modules/ACPI/Template/Core/AtadSmi.c 1     1/23/14 5:47p Oleksiyy $
//
// $Revision: 1 $
//
// $Date: 1/23/14 5:47p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/ACPI/Template/Core/AtadSmi.c $
// 
// 1     1/23/14 5:47p Oleksiyy
// [TAG]  		EIP113941
// [Category]  	New Feature
// [Description]  	Time and Alarm ACPI device implemented.
// [Files]  		AtadSmi.cif
// AtadSmi.sdl
// AtadSmi.mak
// AtadSmi.dxs
// AtadSmi.h
// AtadSmi.c
// 
// 6     1/13/10 2:13p Felixp
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <AtadSmi.c>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <AmiSmm.h>
#include "AtadSmi.h"
#include <token.h>

#if PI_SPECIFICATION_VERSION<0x0001000A
    #include <Protocol/SmmSwDispatch.h>
    #include <Protocol/SmmControl.h>
#else
    #include <Protocol/SmmSwDispatch2.h>
    #include <Protocol/SmmControl2.h>
    #include <Protocol/SmmCpu.h>
#endif



EFI_HANDLE  VarSmiHandle = NULL;

VOID        *gAtadBuffer = NULL;
EFI_EVENT   EvtAtadSmi;
VOID        *RegAtadSmi;
UINT32 i=0;
UINT32 j=0;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AtadSmiHandler
//
// Description: The SMI handler for Nvram services.
//
// Input:       NONE
//
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS AtadSmiHandler ()
{
    EFI_STATUS              Status = EFI_DEVICE_ERROR;
    ATAD_VARIABLE            *SmmVarBuffer;
    EFI_GUID gEfiTimeVariableGuid  = EFI_TIME_VARIABLE_GUID;
    TIME_VARIABLE TimeVar;
    UINTN TimeVarSize = sizeof(TIME_VARIABLE);
    UINT32 TimeVarFlags = EFI_VARIABLE_NON_VOLATILE | 
                           EFI_VARIABLE_BOOTSERVICE_ACCESS | 
                           EFI_VARIABLE_RUNTIME_ACCESS;
    //TRACE((-1,"AtadSmiHandler . 1.\n"));
    //checkpoint(0x24);
    if (gAtadBuffer == NULL) return EFI_SUCCESS;
    
    SmmVarBuffer = (ATAD_VARIABLE*)gAtadBuffer;


 
    	
    //checkpoint(0x25);
    switch (SmmVarBuffer->Signature){

        case ATAD_SW_SMI_UPDATE:
        	//TRACE((-1,"AtadSmiHandler . ATAD_SW_SMI_UPDATE.\n"));
        	TimeVar.TimeZone = SmmVarBuffer->TimeZone;
        	TimeVar.Daylight = SmmVarBuffer->DayLight;
        	Status = pRS->SetVariable( L"EfiTime",
        												&gEfiTimeVariableGuid,
        												TimeVarFlags,
        												TimeVarSize,
        												&TimeVar );
        
        	if (!EFI_ERROR(Status)) SmmVarBuffer->Signature = ATAD_SW_SMI_OK;
        	else SmmVarBuffer->Signature = ATAD_SW_SMI_NOT_GOOD;
            //checkpoint(0x30+i++);
        	break;

        case ATAD_SW_SMI_GET:
			//TRACE((-1,"AtadSmiHandler . ATAD_SW_SMI_GET.\n"));
		    Status = pRS->GetVariable( L"EfiTime",
		                               &gEfiTimeVariableGuid, 
		                               &TimeVarFlags, 
		                               &TimeVarSize, 
		                               &TimeVar );
		    if (!EFI_ERROR(Status))
		    {
			SmmVarBuffer->TimeZone = TimeVar.TimeZone;
			SmmVarBuffer->DayLight = TimeVar.Daylight;
			SmmVarBuffer->Signature = ATAD_SW_SMI_OK;
		    }
		    else SmmVarBuffer->Signature = ATAD_SW_SMI_NOT_GOOD;
		    //checkpoint(0x40+j++);
        break;
        
        default:
			SmmVarBuffer->Signature = ATAD_SW_SMI_NOT_GOOD;
	}
    //checkpoint(0x26);
    return EFI_SUCCESS;
}

EFI_STATUS AtadSmiHandler2 (
		IN EFI_HANDLE	DispatchHandle,
		IN CONST VOID	*Context OPTIONAL,
		IN OUT VOID		*CommBuffer OPTIONAL,
		IN OUT UINTN	*CommBufferSize OPTIONAL
)

{

	CONST EFI_SMM_SW_REGISTER_CONTEXT  *DispatchContext = Context;
	//checkpoint(0x22);
	//TRACE((-1,"AtadSmiHandler2\n"));
    if ((gAtadBuffer == NULL) || ((UINT8)DispatchContext->SwSmiInputValue != ACPI_TIME_AND_ALARM_SW_SMI))
        return EFI_DEVICE_ERROR;
    //TRACE((-1,"AtadSmiHandler22\n"));
    //checkpoint(0x23);
    return AtadSmiHandler();

}

EFI_STATUS AtadInSmmFunction(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS Status;
    EFI_HANDLE Handle = 0;

#if PI_SPECIFICATION_VERSION<0x0001000A
    EFI_GUID EfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
    EFI_SMM_SW_DISPATCH_PROTOCOL *SwDispatch = NULL;
    EFI_SMM_SW_DISPATCH_CONTEXT  SwContext;
    Status = pBS->LocateProtocol( 
#else
    EFI_GUID EfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID;
    EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT   SwContext;
    Status = pSmst->SmmLocateProtocol(
#endif
        &EfiSmmSwDispatchProtocolGuid, 
        NULL, 
        &SwDispatch 
    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status))
        return Status;

    SwContext.SwSmiInputValue = ACPI_TIME_AND_ALARM_SW_SMI;
    Status  = SwDispatch->Register ( SwDispatch,
                                      AtadSmiHandler2,
                                      &SwContext,
                                      &Handle );
    ASSERT_EFI_ERROR(Status);
    TRACE((TRACE_ALWAYS,"AtadInitSmmHandler pSwDispatch->Register Status=%r\n",Status));
    return Status;
}


EFI_STATUS
AtadSmiEntry(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
 

    EFI_STATUS          Status;
    EFI_GUID            AtadSmiGuid = ATAD_SMI_GUID;
    UINTN               VariableSize = sizeof(gAtadBuffer);

    InitAmiLib(ImageHandle, SystemTable);

    TRACE((TRACE_ALWAYS,"AtadSmiEntry\n"));

    Status = pRS->GetVariable ( L"AtadSmiBuffer",
                                &AtadSmiGuid,
                                NULL,
                                &VariableSize,
                                &gAtadBuffer );
    if ((EFI_ERROR(Status)) || (gAtadBuffer == NULL)) return EFI_NOT_FOUND;
    //TRACE((-1, "AtadSmiEntry2 \n"));
    Status = InitSmmHandler( 
            ImageHandle, 
            SystemTable, 
            AtadInSmmFunction, 
            NULL 
        );
    TRACE((TRACE_ALWAYS,"AtadInitSmmHandler Status=%r\n",Status));
    ASSERT_EFI_ERROR(Status);
    
    return EFI_SUCCESS;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************