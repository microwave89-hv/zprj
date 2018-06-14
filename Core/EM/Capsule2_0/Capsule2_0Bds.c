//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Core/Modules/Capsule2_0/Capsule2_0Bds.c 2     7/31/12 6:19p Artems $
//
// $Revision: 2 $
//
// $Date: 7/31/12 6:19p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Core/Modules/Capsule2_0/Capsule2_0Bds.c $
// 
// 2     7/31/12 6:19p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Remove Capsule mailbox from NVRAM once capsule is
// processed
// [Files]  		Capsule2_0Bds.c
// 
// 1     5/24/12 4:22p Artems
// [TAG]  		EIP74625
// [Category]  	New Feature
// [Description]  	New Capsule PPI required by latest Intel's MRC code
// [Files]  		Capsule2_0.cif
// Capsule2_0.sdl
// Capsule2_0.mak
// Capsule2_0.c
// Capsule2_0.h
// Capsule2_0Runtime.c
// Capsule2_0Bds.c
// 
//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name:    Capsule2_0Bds.c
//
// Description: Capsule execution implementation
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiHobs.h>
#include <Capsule.h>
#include <Protocol/Capsule.h>


typedef EFI_STATUS (OEM_PROCESS_CAPSULE) (EFI_CAPSULE_HEADER *Capsule);
extern OEM_PROCESS_CAPSULE OEM_PROCESS_CAPSULE_LIST EndOfList;
OEM_PROCESS_CAPSULE* OemProcessCapsuleList[] = { OEM_PROCESS_CAPSULE_LIST NULL };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ProcessCapsule
//
// Description: Retrieve capsule and process it
//
// Input:       
//  IN EFI_HANDLE ImageHandle - Image handle
//  IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ProcessCapsule(
    VOID
)
{
    static EFI_GUID HobListGuid = HOB_LIST_GUID;
    static EFI_GUID AmiCapsuleHobGuid = AMI_CAPSULE_HOB_GUID;
    static EFI_GUID CapsuleVendorGuid    = EFI_CAPSULE_AMI_GUID;
    EFI_STATUS Status;
    EFI_HOB_HANDOFF_INFO_TABLE *pHit;
    UINTN i;
    EFI_CAPSULE_HEADER *Capsule = NULL;
    AMI_CAPSULE_HOB *CapsuleHob;
    VOID *Save;
    

    pHit = GetEfiConfigurationTable(pST, &HobListGuid);
    if(EFI_ERROR(FindNextHobByGuid(&AmiCapsuleHobGuid, &pHit)))
        return;     //capsule HOB not found

//capsule was found and coalesced, we have to kill mailbox
    Status = pRS->SetVariable (
                 CAPSULE_UPDATE_VAR,  
                 &CapsuleVendorGuid,     
                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS,  
                 0, 
                 (VOID *) Capsule);
    
    CapsuleHob = (AMI_CAPSULE_HOB *)pHit;
    Capsule = (EFI_CAPSULE_HEADER *)(VOID *)(UINTN)(CapsuleHob->CapsuleData);
    for(i = 0; OemProcessCapsuleList[i] != NULL; i++) {
        Status = OemProcessCapsuleList[i](Capsule);
        if(!EFI_ERROR(Status))
            return;      //capsule is processed by OEM hook
    }

    if(Capsule->Flags & CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE) {
    /* populate capsule via system table, move to runtime memory */
        Status = pBS->AllocatePool(EfiRuntimeServicesData, (UINTN)(CapsuleHob->CapsuleLength), &Save);
        if(EFI_ERROR(Status))
            return;

        MemCpy(Save, (VOID *)(UINTN)(CapsuleHob->CapsuleData), (UINTN)(CapsuleHob->CapsuleLength));
        Status = pBS->InstallConfigurationTable(&(CapsuleHob->CapsuleGuid), Save);
    }
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************