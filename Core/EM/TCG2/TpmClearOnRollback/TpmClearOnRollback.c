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
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TpmClearOnRollback/TpmClearOnRollback.c 1     4/21/14 2:18p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:18p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TpmClearOnRollback/TpmClearOnRollback.c $
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
// Name: TpmClearOnRollback
//
//
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "TpmClearOnRollback.h"
#include <Protocol/AmiPostMgr.h>
#include <PPI/FwVersion.h>
#include <Hob.h>
#include <Token.h>
#include <AmiHobs.h>

VOID DrawMessageBox(
    IN CHAR16 *Caption,
    IN CHAR16 *Message
);



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: RecoveryClearTpmBeforeFlash
//
// Description: 
//  Process TPM clear on Rollback policy
//
// Input:   
// VOID
//
// Output:    
//  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RecoveryClearTpmBeforeFlash (VOID){
    UINT8                       ClearResults;
    AMI_POST_MANAGER_PROTOCOL   *TpmClearAmiPostMgr = NULL;
    FW_VERSION                  Fid;
    EFI_EVENT                   MyEvent;
    FW_VERSION                  RecoveryFid;
    EFI_HOB_HANDOFF_INFO_TABLE  *TpmpHit;
    EFI_GUID                    myGuidHob = HOB_LIST_GUID;
    EFI_GUID                    TpmRecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    UINT32                      ProjectVersion, NewProjectVersion;
    EFI_GUID                   gAmiPostManagerProtocolGuid = \
                                     AMI_POST_MANAGER_PROTOCOL_GUID;
    EFI_STATUS                  Status;

    TpmpHit = GetEfiConfigurationTable(pST, &myGuidHob);
    if(TpmpHit != NULL && !EFI_ERROR(FindNextHobByGuid(&TpmRecoveryHobGuid, &TpmpHit))) {
        
         TpmGetFidFromBuffer(&RecoveryFid, (VOID *)(UINTN)((RECOVERY_IMAGE_HOB*)TpmpHit)->Address);
    }

    TpmRecoveryGetFidFromFv(&Fid);
  
    ProjectVersion = Fid.ProjectMajorVersion[0] + Fid.ProjectMajorVersion[1] + Fid.ProjectMajorVersion[2];
    ProjectVersion <<= 16;
    ProjectVersion += Fid.ProjectMinorVersion[0] + Fid.ProjectMinorVersion[1] + Fid.ProjectMinorVersion[2];

    NewProjectVersion = RecoveryFid.ProjectMajorVersion[0] + RecoveryFid.ProjectMajorVersion[1] + RecoveryFid.ProjectMajorVersion[2];
    NewProjectVersion <<= 16;
    NewProjectVersion += RecoveryFid.ProjectMinorVersion[0] + RecoveryFid.ProjectMinorVersion[1] + RecoveryFid.ProjectMinorVersion[2];

    if(NewProjectVersion < ProjectVersion){
        ClearResults = ClearTpmBeforeFlash();
        if(ClearResults == TPM_CLEAR_RESET_REQUIRED)
        {
           Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, &TpmClearAmiPostMgr);
           if(EFI_ERROR(Status))return;

           if(TpmClearAmiPostMgr != NULL) {
             Status = TpmClearAmiPostMgr->DisplayInfoBox(L"TPM CLEAR",\
                          L"Caution: A Reset is required to Clear the TPM for Flash Update. Enable Recovery after reset",20, &MyEvent);

             FixedDelay(1000000); //10seconds delay
           }

           pRS->ResetSystem( EfiResetCold, 0, 0, NULL );
        }
    }
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
