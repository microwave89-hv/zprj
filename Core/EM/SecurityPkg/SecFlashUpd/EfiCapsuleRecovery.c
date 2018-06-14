//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014 American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/EfiCapsuleRecovery.c 13    3/18/14 3:02p Alexp $
//
// $Revision: 13 $
//
// $Date: 3/18/14 3:02p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/FlashUpdate/EfiCapsuleRecovery.c $
// 
// 13    3/18/14 3:02p Alexp
// year '2014' in file hdr & ftr
// 
// 12    2/27/13 6:31p Alexp
// don't assume the Capsule hob starts with FWCapsule header.
// helps to hadle Windows Update Capsule with Ami.rom as payload
// 
// 11    12/17/12 2:40p Alexp
// optimized LoadRecoveryCapsule()
// 
// 10    8/28/12 4:19p Alexp
// change return NULL to return 0 for EFI_PHYSICAL_ADDRESS types
// 
// 8     4/19/12 2:43p Alexp
// EIP:87678: Woking image during Recovery and Capsule Secure Flash Update
// Deffer Publishing of FV DXE to DxeIpl. Launch DXE from original FV on
// Flash updates while in Recovery use DXE form new image
// 
// 7     2/14/12 3:24p Alexp
// Replace VOID (32bit) with EFI_PHYSICAL_ADDRESS(64bit) pointer for an
// address of a Recovery Hob data.
// 
// 6     12/08/11 12:22p Alexp
// Re-define EFI_HOB_TYPE_CV type as EFI_HOB_TYPE_UEFI_CAPSULE
// for forward compatibility with PI 1.2 Hob.h definitions
// 
// 5     11/17/11 10:01a Alexp
// 1. Replace local Capsule pointer with global one. 
// 2. Locate FW CApsule includes search in 2 potential Capsule Hob types
//     - EFI_HOB_TYPE_GUID_EXTENSION
//     - EFI_HOB_TYPE_CV
// 
// 4     10/11/11 12:23p Alexp
// re-arrange Function defines and global defines
// 
// 3     9/20/11 2:26p Alexp
// do not change BootMode from FlUpdate to Recovery if FwCapsule update is
// pending
// 
// 2     7/20/11 7:16p Alexp
// remove dependency on Capsule module
// 
// 1     7/01/11 4:39p Alexp
// 
// 3     4/29/11 10:28a Alexp
// Capsule Recovery to be invoked sepparately from generic Recovery PPI 
// 
// 
//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: EFICapsuleRecovery.c - PEI driver
//
// Description:    Implements EFI_PEI_RECOVERY_BLOCK_IO_PPI for Capsule HOB.
// Capsule Recovery to be invoked separately from generic Recovery PPI 
//----------------------------------------------------------------------
//<AMI_FHDR_END>
#include <Token.h>
#include <PPI/RecoveryModule.h>

#include <AmiPeiLib.h>
#include <AmiHobs.h>
#include <Hob.h>
#include "AmiCertificate.h"
#include <FlashUpd.h>

// Definitions

EFI_GUID gFWCapsuleGuid   = APTIO_FW_CAPSULE_GUID;
EFI_GUID guidRecoveryModule = EFI_PEI_RECOVERY_MODULE_PPI_GUID;

#ifndef EFI_HOB_TYPE_CV
#define EFI_HOB_TYPE_CV EFI_HOB_TYPE_UEFI_CAPSULE
typedef EFI_HOB_UEFI_CAPSULE EFI_HOB_CAPSULE_VOLUME;
#endif // PI BACKWARD_COMPATIBLE_MODE

EFI_PHYSICAL_ADDRESS gCapsuleAddress = 0;
UINT64               gCapsuleLength = 0;
//----------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------
EFI_STATUS ReportFV2Dxe(
    IN VOID* RecoveryCapsule OPTIONAL,
    IN EFI_PEI_SERVICES **PeiServices
);

EFI_STATUS VerifyFwImage(
  IN EFI_PEI_SERVICES  **PeiServices,
  IN OUT VOID          **pCapsule,
  IN OUT UINT32         *pCapsuleSize,
  IN OUT UINT32         *FailedVTask
);

//----------------------------------------------------------------------------
// Function Definitions
//----------------------------------------------------------------------------
EFI_STATUS LoadRecoveryCapsule(
    IN EFI_PEI_SERVICES **PeiServices,
    IN struct _EFI_PEI_RECOVERY_MODULE_PPI *This
);

BOOLEAN IsFlashUpdateS3Capsule (
    EFI_PEI_SERVICES    **PeiServices,
    EFI_BOOT_MODE       *BootMode
);
//----------------------------------------------------------------------------
// PPI to be installed
//----------------------------------------------------------------------------
static EFI_PEI_RECOVERY_MODULE_PPI RecoveryModule = 
{
    LoadRecoveryCapsule
};
 
//----------------------------------------------------------------------------
// Notify list that are installed
//----------------------------------------------------------------------------
static EFI_PEI_PPI_DESCRIPTOR RecoveryPpiList[] =
{ 
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &guidRecoveryModule, &RecoveryModule
    }
};

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    FindFWCapsuleHOB
//
// Description:    Locates Aptio FW Capsule in Capsule Hob 
//
// Input:   EFI_PEI_SERVICES **PeiServices
// Output:  EFI_PHYSICAL_ADDRESS pointer to FW CApsule
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS
FindFWCapsuleHOB
(
    IN    EFI_PEI_SERVICES        **PeiServices
){
    EFI_HOB_GUID_TYPE       *pHob;
    EFI_HOB_CAPSULE_VOLUME  *pHob1;
    EFI_PHYSICAL_ADDRESS        CapsuleAddress;
    UINT64                      CapsuleLength;
    EFI_CAPSULE_HEADER         *FWCapsuleVolume;

    (*PeiServices)->GetHobList(PeiServices, &pHob);
    pHob1 = (EFI_HOB_CAPSULE_VOLUME*)pHob;
// 1. attempt to locate Capsule by GUID guidAmiCapsuleHob
    while (!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &pHob)))
    {
        if((pHob->Header.HobType == EFI_HOB_TYPE_GUID_EXTENSION)&&
            !(guidcmp(&((AMI_CAPSULE_HOB*)pHob)->CapsuleGuid, &gFWCapsuleGuid)))
        {
            PEI_TRACE((-1, PeiServices, "FW Capsule found in GUIDed Capsule Hob\n"));
            gCapsuleLength = ((AMI_CAPSULE_HOB*)pHob)->CapsuleLength;
            gCapsuleAddress = (EFI_PHYSICAL_ADDRESS)(((AMI_CAPSULE_HOB*)pHob)->CapsuleData);
            return EFI_SUCCESS;
        }
    }
// 2. attempt to locate capsule volume hob
    while (!EFI_ERROR(FindNextHobByType(EFI_HOB_TYPE_CV, &pHob1)))
    {
        // if capsule volume hob is found, determine the capsule's location
        CapsuleAddress = pHob1->BaseAddress;
        CapsuleLength  = pHob1->Length;
        FWCapsuleVolume = (EFI_CAPSULE_HEADER*) CapsuleAddress;
        if(CapsuleLength != 0 && FWCapsuleVolume->CapsuleImageSize <= CapsuleLength &&
            !(guidcmp(&(FWCapsuleVolume->CapsuleGuid), &gFWCapsuleGuid)))
        {
            PEI_TRACE((-1, PeiServices, "FW Capsule found in Capsule Volume Hob\n"));
            gCapsuleLength = CapsuleLength;
            gCapsuleAddress = CapsuleAddress;
            return EFI_SUCCESS;
        }
    }

    PEI_TRACE((-1,PeiServices, "FW capsule HOB not found\n"));
    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    LoadRecoveryCapsule
//
// Description:    LoadRecoveryCapsule function of EFI_PEI_RECOVERY_MODULE_PPI 
//              ppi.  RecoveryDeviceOrder is a list of guids; each guid 
//              represents a type of recovery device.  We go through 
//              this list and call FindRecoveryDevice for each type of 
//              device. 
//              -This function should not be confused with LoadRecoveryCapsule
//              function of the EFI_PEI_DEVICE_RECOVERY_MODULE_PPI ppi.  
//              -Called by DxeIpl.
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS LoadRecoveryCapsule(
    IN EFI_PEI_SERVICES **PeiServices,
    IN struct _EFI_PEI_RECOVERY_MODULE_PPI *This
)
{
    EFI_STATUS Status;
    static EFI_GUID RecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    RECOVERY_IMAGE_HOB *pRecoveryHob;
    UINTN       Size;
    EFI_PHYSICAL_ADDRESS       CapsuleAddress;

    PEI_PROGRESS_CODE(PeiServices,PEI_RECOVERY_STARTED);

    PEI_TRACE((TRACE_DXEIPL, PeiServices, "Loading Recovery Image..."));

// Locate Capsule Hob
    if(!gCapsuleAddress || !gCapsuleLength) return EFI_NOT_FOUND;

    //create HOB that describes location of the Recovery image
    Status = (*PeiServices)->CreateHob(
        PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, 
        sizeof(RECOVERY_IMAGE_HOB), &pRecoveryHob
    );
    pRecoveryHob->Header.Name = RecoveryHobGuid;
    pRecoveryHob->Address = 0;

//    Size = (UINTN)((APTIO_FW_CAPSULE_HEADER*)gFwCapsule)->CapHdr.CapsuleImageSize;
    Size = (UINTN)gCapsuleLength;
    CapsuleAddress = (EFI_PHYSICAL_ADDRESS)gCapsuleAddress;
    Status = VerifyFwImage(PeiServices, (VOID**)&CapsuleAddress, (UINT32*)&Size,(UINT32*)&pRecoveryHob->FailedStage ); 
    pRecoveryHob->Status = (UINT8)Status;
    pRecoveryHob->Address = CapsuleAddress;
    if (EFI_ERROR(Status)) {
        PEI_ERROR_CODE(PeiServices, PEI_RECOVERY_INVALID_CAPSULE, EFI_ERROR_MAJOR | Status);
    } 
// < 4.6.5.4
#if defined(CORE_COMBINED_VERSION) && CORE_COMBINED_VERSION < 0x4028e
    else{
    // DxeIpl from 4.6.5.4. will publish Dxe FV
      Status = ReportFV2Dxe((VOID *)CapsuleAddress, PeiServices);
    }
#endif

    if (EFI_ERROR(Status)) {
        PEI_ERROR_CODE(PeiServices, PEI_RECOVERY_NO_CAPSULE, EFI_ERROR_MAJOR);
    }

    return Status;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:    EFICapsuleRecoveryPeimEntry
//
// Description:    Entry point.  Installs EFI_PEI_RECOVERY_MODULE_PPI ppi 
//              (which has function LoadRecoveryCapsule).  
//
//---------------------------------------------------------------------- 
//<AMI_PHDR_END>
EFI_STATUS
EFICapsuleRecoveryPeimEntry (
    IN    EFI_FFS_FILE_HEADER        *FfsHeader,
    IN    EFI_PEI_SERVICES        **PeiServices
)
{
    EFI_STATUS      Status;
    EFI_BOOT_MODE   BootMode;

// Change the Boot Mode to Recovery from S3_RESUME/BOOT_ON_FLASH_UPDATE
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    PEI_TRACE((-1, PeiServices, "FW Capsule Recovery Module, BootMode 0x%x\n", BootMode));
    if(BootMode == BOOT_ON_S3_RESUME || BootMode ==  BOOT_ON_FLASH_UPDATE)
    {
// Locate Capsule Hob
        Status = FindFWCapsuleHOB(PeiServices);
        if (EFI_ERROR(Status) || !gCapsuleAddress || !gCapsuleLength) {
// Capsule not found:
// Change the Boot Mode to BOOT_WITH_FULL_CONFIGURATION from BOOT_ON_FLASH_UPDATE
            BootMode = BOOT_WITH_FULL_CONFIGURATION;
            Status = (*PeiServices)->SetBootMode(PeiServices, BootMode);
        } else {    
            Status = (*PeiServices)->InstallPpi(PeiServices,RecoveryPpiList);
            ASSERT_PEI_ERROR (PeiServices, Status);
        }
        PEI_TRACE((-1, PeiServices, "\tchange mode to 0x%x\n",BootMode));
    }

    return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014 American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************