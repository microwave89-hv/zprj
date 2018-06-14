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
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardPei.c 2     3/07/13 5:43a Bensonlai $
//
// $Revision: 2 $
//
// $Date: 3/07/13 5:43a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardPei.c $
// 
// 2     3/07/13 5:43a Bensonlai
// [TAG]  		EIP117307
// [Category]  	Improvement
// [Description]  	[Boot Guard] Implementation of speed up the post time
// for Chain of Trust
// [Files]  		BootGuardDxe.h, BootGuardPei.c, BootGuardPei.h,
// BpmKmGen.exe, ReserveBootGuardFvMainHashKey.bin
// 
// 1     2/25/13 1:15a Bensonlai
// [TAG]  		EIP114386
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
// for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
// BIOS Writer's Guide - Rev 0.8.1
// [Files]  		BootGuardPei.cif
// BootGuardPei.c
// BootGuardPei.h
// BootGuardPei.dxs
// BootGuardPei.sdl
// BootGuardPei.mak
// PeiCryptLib.lib
// OpensslLib.lib
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardPei.c
//
// Description: Chain of trust for Pei
//
//<AMI_FHDR_END>
//*************************************************************************

#include "BootGuardPei.h"

EFI_GUID ReserveBootGuardFvMainHashKeyGuid = RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY_FFS_FILE_RAW_GUID;

STATIC EFI_PEI_NOTIFY_DESCRIPTOR  BootGuardVerificationForPeiToDxeHandoffEndOfPeiNotifyDesc = {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEndOfPeiSignalPpiGuid,
    BootGuardVerificationForPeiToDxeHandoffEndOfPei
};

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: LocateBootGuardFvMainHashKey
//
// Description:    Loads binary from RAW section of X firwmare volume
//
//
// Output:         Buffer - returns a pointer to allocated memory. Caller
//                          must free it when done.
//                 Size   - returns the size of the binary loaded into the
//                          buffer.
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
LocateBootGuardFvMainHashKey (
    IN EFI_PEI_SERVICES  **PpSv,
    IN OUT VOID          **Buffer
)
{
    EFI_STATUS                    Status;
    EFI_FIRMWARE_VOLUME_HEADER    *pFV;
    UINTN                         FvNum=0;
    EFI_FFS_FILE_HEADER           *ppFile=NULL;
    BOOLEAN                       Found = FALSE;

    Status = (*PpSv)->FfsFindNextVolume (PpSv, FvNum, &pFV);

    while ( TRUE ) {
        Status = (*PpSv)->FfsFindNextVolume( PpSv, FvNum, &pFV );
        if ( EFI_ERROR( Status ) ) {
            return Status;
        }

        ppFile = NULL;

        while ( TRUE ) {
            Status = (*PpSv)->FfsFindNextFile( PpSv,
                                               EFI_FV_FILETYPE_FREEFORM,
                                               pFV,
                                               &ppFile );

            if ( Status == EFI_NOT_FOUND ) {
                break;
            }

            if (CompareGuid( &ppFile->Name, &ReserveBootGuardFvMainHashKeyGuid )) {
                Found = TRUE;
                break;
            }
        }

        if ( Found ) {
            break;
        } else {
            FvNum++;
        }
    }

    Status = (*PpSv)->FfsFindSectionData( PpSv,
                                          EFI_SECTION_RAW,
                                          ppFile,
                                          Buffer );

    if ( EFI_ERROR( Status ) ) {
        return EFI_NOT_FOUND;
    }

    return Status;
}

//**********************************************************************
//<AMI_PHDR_START>
//
// Procedure: BootGuardVerificationForPeiToDxeHandoffEndOfPei
//
// Description:    BootGuardVerificationForPeiToDxeHandoffEndOfPei at end of Pei
//                 handler.
//
// Output:         PeiServices - Pointer to PEI Services Table.
//                 NotifyDesc  - Pointer to the descriptor for the Notification
//                               event that caused this function to execute.
//                 Ppi         - Pointer to the PPI data associated with
//                               this function.
//
//<AMI_PHDR_END>
//**********************************************************************
STATIC
EFI_STATUS
BootGuardVerificationForPeiToDxeHandoffEndOfPei (
    IN      EFI_PEI_SERVICES          **PeiServices,
    IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN      VOID                      *Ppi
)
{
    EFI_STATUS                             Status;
    UINTN                                  BootGuardHashDataSize = 0, i;
    UINT8                                  CurrentBootGuardFvMainHash256Val[32];
    VOID                                   *BootGuardSha256Context;
    UINT8                                  *BootGuardOrgFvMainHash256;
    AMI_BOOT_GUARD_HOB                     *AmiBootGuardHobPtr;
    EFI_GUID                               AmiBootGuardHobGuid = AMI_BOOT_GUARD_HOB_GUID;
    EFI_BOOT_MODE                          BootMode;
    RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY    *ReserveBootGuardFvMainHashKey;

    Status = PeiServicesGetBootMode (&BootMode);
    if ( EFI_ERROR( Status ) ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] Get Boot Mode is fail\n"));
        return   Status;
    }

    if ( BootMode == BOOT_IN_RECOVERY_MODE ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] In the BOOT_IN_RECOVERY_MODE\n"));
        return   Status;
    }

    if ( BootMode == BOOT_ON_S3_RESUME ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] In the BOOT_ON_S3_RESUME\n"));
        return   Status;
    }

    Status = (*PeiServices)->CreateHob (PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, sizeof (AMI_BOOT_GUARD_HOB), (VOID **) &AmiBootGuardHobPtr);
    if ( EFI_ERROR( Status ) ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] CreateHob is fail for AmiBootGuardHobPtr\n"));
        return   Status;
    }

    AmiBootGuardHobPtr->EfiHobGuidType.Name = AmiBootGuardHobGuid;
    AmiBootGuardHobPtr->AmiBootGuardVerificationforPEItoDXEFlag = 0;
    BootGuardHashDataSize = Sha256GetContextSize ();
    Status = ((*PeiServices)->AllocatePool) (PeiServices, BootGuardHashDataSize, &BootGuardSha256Context);
    if ( EFI_ERROR( Status ) ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] AllocatePool is fail for BootGuardSha256Context\n"));
        return   Status;
    }

    BootGuardOrgFvMainHash256 = AllocateZeroPool (32);
    if (BootGuardOrgFvMainHash256 == NULL) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] AllocateZeroPool is fail for BootGuardOrgFvMainHash256\n"));
        return Status;
    }

    Status  = LocateBootGuardFvMainHashKey(PeiServices , &BootGuardOrgFvMainHash256);
    if ( EFI_ERROR( Status ) ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] LocateBootGuardFvMainHashKey is fail\n"));
        return   Status;
    }

    ReserveBootGuardFvMainHashKey = (RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY*)BootGuardOrgFvMainHash256;

    for ( i = 0; i < sizeof(ReserveBootGuardFvMainHashKey->BootGuardFvMainHashKey); i++ ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] BootGuardOrgFvMainHash256[%x]= %x.\n", i, ReserveBootGuardFvMainHashKey->BootGuardFvMainHashKey[i]));
    }
    DEBUG ((EFI_D_ERROR, "\n[BootGuardPei.c] BootGuardFvMainUsedLength= %x.\n", ReserveBootGuardFvMainHashKey->BootGuardFvMainUsedLength));

    Sha256Init (BootGuardSha256Context);
    Sha256Update (BootGuardSha256Context, (UINT8 *)(DXE_SEGMENT_BASE), (UINTN)ReserveBootGuardFvMainHashKey->BootGuardFvMainUsedLength);
    Sha256Final (BootGuardSha256Context,  CurrentBootGuardFvMainHash256Val);

    for ( i = 0; i < sizeof (CurrentBootGuardFvMainHash256Val); i++ ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] CurrentBootGuardFvMainHash256Val[%x]= %x.\n", i, CurrentBootGuardFvMainHash256Val[i]));
    }

    if ( !CompareMem(BootGuardOrgFvMainHash256, CurrentBootGuardFvMainHash256Val, 32) ) {
        AmiBootGuardHobPtr->AmiBootGuardVerificationforPEItoDXEFlag = 1;
    } else {
        AmiBootGuardHobPtr->AmiBootGuardVerificationforPEItoDXEFlag = 0;
    }

    DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] AmiBootGuardHobPtr->AmiBootGuardVerificationforPEItoDXEFlag= %x.\n", AmiBootGuardHobPtr->AmiBootGuardVerificationforPEItoDXEFlag));

    return   Status;
}

EFI_STATUS
BootGuardPeiEntryPoint (
    IN  EFI_FFS_FILE_HEADER  *FfsHeader,
    IN  EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS                      Status;
    PCH_SERIES                      PchSeries = GetPchSeries();

    if ( PchSeries != PchLp ) {
        return   EFI_SUCCESS;
    }

    if ( IsBootGuardSupported() == FALSE ) {
        return   EFI_SUCCESS;
    }

    if ( (UINT32)AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) == 0 ) {
        DEBUG ((EFI_D_ERROR, "[BootGuardPei.c] Boot Guard is disabled by Anchor Cove Profile Configuration in the Intel Fitc\n"));
        return   EFI_SUCCESS;
    }

    Status = PeiServicesNotifyPpi (&BootGuardVerificationForPeiToDxeHandoffEndOfPeiNotifyDesc);
    if ( EFI_ERROR( Status ) ) {
        return   Status;
    }

    return   Status;
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
