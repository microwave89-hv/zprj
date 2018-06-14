//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TpmClearOnRollback/TpmClearOnRollbackSmiFlash.c 1     4/21/14 2:18p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TpmClearOnRollback/TpmClearOnRollbackSmiFlash.c $
// 
// 1     4/21/14 2:18p Fredericko
// 
// 1     10/08/13 12:06p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:57p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
//**********************************************************************
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name: 
//
//
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "TpmClearOnRollback.h"
#include <Protocol/AmiPostMgr.h>

CLEAR_TPM_ROLLBACK_PROTOCOL *PrivateProtocol;
EFI_SMM_SYSTEM_TABLE2               *mSmst;
static FW_VERSION                          Fid;


UINT8 SmiFlashClearTpmBeforeFlash (){
    return(ClearTpmBeforeFlash());
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure:   InstallTpmClearProtocolInSmm
//
// Description: InstallTcgSmmFlash Protocol
//
//
// Input:       IN    EFI_HANDLE ImageHandle,
//              IN    EFI_SYSTEM_TABLE *SystemTable
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
EFI_STATUS InstallTpmClearProtocolInSmm(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_SMM_BASE2_PROTOCOL        *SmmBase;
    EFI_HANDLE                    Handle=NULL;
    EFI_STATUS                    Status;
    EFI_GUID                      TpmRollbackSmmGuid = \
                                                AMI_TPM_ROLLBACK_SMM_PROTOCOL_GUID;

    Status = pBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, &SmmBase);
    if((EFI_ERROR(Status)) || (SmmBase == NULL)){
        return Status;
    }

    Status = SmmBase->GetSmstLocation(SmmBase, &mSmst);
    if(EFI_ERROR(Status)){
            return Status;
    }

    Status = mSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (CLEAR_TPM_ON_ROLLBACK),
                    &PrivateProtocol
                    );

    if((EFI_ERROR(Status)) || (PrivateProtocol == NULL)){
        return Status;
    }

    TpmRecoveryGetFidFromFv(&Fid);    

    PrivateProtocol->ClearTpmOnRollBack = (VOID *)&SmiFlashClearTpmBeforeFlash;

    Status = mSmst->SmmInstallProtocolInterface( &Handle, \
                                               &TpmRollbackSmmGuid, \
                                               EFI_NATIVE_INTERFACE, \
                                               PrivateProtocol );
   
    return Status;
}



//****************************************************** ****************
//<AMI_PHDR_START>
//
// Procedure:    TpmClearRollBackSmmInit
//
// Description: Entry point for subcomponent
//
// Input:       IN    EFI_HANDLE ImageHandle,
//              IN    EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS TpmClearRollBackSmmInit(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    InitAmiLib( ImageHandle, SystemTable );

    return InitSmmHandler( ImageHandle, SystemTable, InstallTpmClearProtocolInSmm, NULL );
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
