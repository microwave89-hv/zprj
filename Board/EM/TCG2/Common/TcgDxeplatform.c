//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxeplatform/TcgDxeplatform.c 1     4/21/14 2:17p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:17p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxeplatform/TcgDxeplatform.c $
// 
// 1     4/21/14 2:17p Fredericko
// 
// 1     10/08/13 12:04p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:56p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 5     1/20/12 9:14p Fredericko
// 
// 4     4/04/11 2:16p Fredericko
// Removed #pragma optimization directives
// 
// 3     4/01/11 9:39a Fredericko
// Updated function Header
// 
// 2     3/29/11 1:21p Fredericko
// [TAG]        EIP 54642
// [Category] Improvement
// [Description] 1. Checkin Files related to TCG function override 
// 2. Include TCM and TPM auto detection
// [Files] Affects all TCG files
//
//
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:	TcgDxeplatform.c
//
// Description:	Function file for TcgDxeplatform
//
//<AMI_FHDR_END>
//*************************************************************************
#include<EFI.h>
#include "AmiTcgPlatformDxe.h"


EFI_GUID gAmiTcgPlatformProtocolguid     = AMI_TCG_PLATFORM_PROTOCOL_GUID;


//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   TcgDxeplatformEntry
//
// Description: 
//
// Input:       IN EFI_HANDLE       ImageHandle,
//              IN EFI_SYSTEM_TABLE *SystemTable
//
// Output:      EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI TcgDxeplatformEntry(
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable ){

    AMI_TCG_PLATFORM_PROTOCOL  *AmiTcgPlatformProtocol = NULL;
    EFI_STATUS                 Status;
    BOOLEAN                    *ResetAllTcgVar = NULL;
    EFI_GUID                   legTcgGuid = AMI_TCG_RESETVAR_HOB_GUID;
    void                       ** DummyPtr;

    InitAmiLib( ImageHandle, SystemTable );

    DummyPtr       = &ResetAllTcgVar;
    ResetAllTcgVar = (UINT8*)LocateATcgHob(
        pST->NumberOfTableEntries,
        pST->ConfigurationTable,
        &legTcgGuid );

    Status = pBS->LocateProtocol( &gAmiTcgPlatformProtocolguid, NULL, 
                                            &AmiTcgPlatformProtocol);

    DummyPtr = &ResetAllTcgVar;

    if ( *DummyPtr != NULL )
    {
        //if ResetAllTcgVar, call setAllTcgVariable to zero
        if ( *ResetAllTcgVar == TRUE )
        {
            AmiTcgPlatformProtocol->ResetOSTcgVar();
        }
    }
  
    if(EFI_ERROR(Status)){
        return EFI_SUCCESS;
    }   


    Status = AmiTcgPlatformProtocol->ProcessTcgPpiRequest();
    if(EFI_ERROR(Status)){
      TRACE((TRACE_ALWAYS, "\n Possible ERROR Processing Ppi Request from O.S.\n"));
    }

    Status = AmiTcgPlatformProtocol->ProcessTcgSetup();
    if(EFI_ERROR(Status)){
      TRACE((TRACE_ALWAYS, "\n Possible ERROR Processing Tcg Setup\n"));
    }

#if (defined(MeasureCPUMicrocodeToken) && (MeasureCPUMicrocodeToken == 1))
    Status = AmiTcgPlatformProtocol->MeasureCpuMicroCode();
    if(EFI_ERROR(Status)){
        TRACE((TRACE_ALWAYS, "\n Possible ERROR Measuring CPU Microde\n"));
    }
#endif

    Status = AmiTcgPlatformProtocol->MeasurePCIOproms();
    if(EFI_ERROR(Status)){
        TRACE((TRACE_ALWAYS, "\n Possible ERROR Measuring PCI Option Roms\n"));
    }
    
    Status = AmiTcgPlatformProtocol->SetTcgReadyToBoot();
    if(EFI_ERROR(Status)){
      TRACE((TRACE_ALWAYS, "\n Possible ERROR process Tcg Ready to boot Callback\n"));
    }

    return Status;   
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
