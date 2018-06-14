//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/CapsuleRecovery.c 2     4/16/13 5:51a Thomaschen $
//
// $Revision: 2 $
//
// $Date: 4/16/13 5:51a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Recovery/CapsuleRecovery.c $
// 
// 2     4/16/13 5:51a Thomaschen
// Fixed for EIP106722.
//
// 4     2/07/13 5:17p Artems
// [TAG]  		EIP106722
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	Win8 firmware update doesn't work
// [RootCause]  	For Win8 update capsule CapsuleRecovery device didn't
// skip capsule header
// [Solution]  	Added unique GUID to distinguish between AFU and Win8
// capsule update
// [Files]  		Capsule2_0.c CapsuleRecovery.c Capsule.h
// 
// 3     11/15/12 4:28p Artems
// [TAG]  		EIP103898
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	After updating Core 4.6.5.4, the Capsule mode of Secure
// Flash can't work.
// [RootCause]  	Capsule recovery device was stripping capsule header from
// provided image, 
// but verification code requires header to be present
// [Solution]  	Keep header together with recovery image for verification
// purposes
// [Files]  		CapsuleRecovery.c
// 
// 2     9/17/12 2:50p Artems
// [TAG]  		EIP N/A
// [Category]  	Improvement
// [Description]  	Removed unnecessary debug messages
// [Files]  		CapsuleRecovery.c
// 
// 1     8/02/12 12:04p Artems
// [TAG]  		EIP93520
// [Category]  	New Feature
// [Description]  	Windows 8 firmware update spec
// [Files]  		Recovery.h Recovery.sdl Recovery.c Reflash.c ReflashWorker.c
// Esrt.c CapsuleRecovery.c
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------
//
// Name: CapsuleRecovery.c
//
// Description:	Recovery from Capsule support
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiPeiLib.h>
#include <AmiHobs.h>
#include <Capsule.h>
#include <Token.h>
#include "Recovery.h"
#include "RecoveryCsp.h"


/************************************************************************/
/*                 Device Recovery Module PPI                           */
/************************************************************************/
//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetNumberRecoveryCapsules
//
// Description:	
//  GetNumberRecoveryCapsules function of ppi 
//  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI.
//
// Input:
//
// Output:
//  EFI_SUCCESS - number of recovery capsules returned
//  EFI_INVALID_PARAMETER - the pointer NumberRecoveryCapsules is NULL
//----------------------------------------------------------------------
//<AMI_PHDR_END>

static EFI_STATUS GetNumberRecoveryCapsules(
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    OUT UINTN                             *NumberRecoveryCapsules 
)
{
    if ( !NumberRecoveryCapsules ) {
        return EFI_INVALID_PARAMETER;
    }
    *NumberRecoveryCapsules = 1;
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	GetRecoveryCapsuleInfo
//
// Description:	
//  GetRecoveryCapsuleInfo function of ppi EFI_PEI_DEVICE_RECOVERY_MODULE_PPI 
//  for any block devices including floppies, USB keys, CD-ROMs and HDDs.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PeiServices Structure
//  IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This - pointer to the PPI structure
//  IN UINTN CapsuleInstance - value indicating the instance of the PPI
//  OUT UINTN *Size - Size of the recovery capsule
//  OUT EFI_GUID *CapsuleType OPTIONAL - Type of recovery capsule
//
// Output:
//  EFI_SUCCESS - Parameters are valid and output parameters are updated
//  EFI_INVALID_PARAMETER - Size pointer is NULL
//  EFI_NOT_FOUND - asking for a 1 or greater instance of the PPI
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS GetRecoveryCapsuleInfo(
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    IN UINTN                              CapsuleInstance,
    OUT UINTN                             *Size,
    OUT EFI_GUID                          *CapsuleType )
{
    EFI_STATUS Status;
    if ( !Size ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( CapsuleInstance > 0 ) {
        return EFI_NOT_FOUND;
    }

    Status = GetRecoveryFileInfo(PeiServices, NULL, Size, NULL);
    if(EFI_ERROR(Status))
        return Status;

    if ( CapsuleType ) {
        *CapsuleType = guidOemCapsule;
    }
    return EFI_SUCCESS;
}

#define NUMBER_OF_RETRIES 3

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	LoadRecoveryCapsule
//
// Description:	
//  Locates all EFI_PEI_RECOVERY_BLOCK_IO_PPI PPIs.  Calls function 
//  GetNumberOfBlockDevices.  For each block device, calls the function 
//  FsRecoveryRead, to find the recovery image named in var sAmiRomFile.
//
// Input:
//  IN EFI_PEI_SERVICES **PeiServices - pointer to PeiServices Structure 
//  IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This - pointer to the PPI structure
//  IN UINTN CapsuleInstance - value indicating the instance of the PPI
//  OUT VOID *Buffer - contains information read from the block device
//
// Output:
//  EFI_SUCCESS - File read from recovery media
//  EFI_INVALID_PARAMETER - Buffer is a NULL pointer
//  EFI_NOT_FOUND - asking for a 1 or greater instance of the PPI
//  Other - return error values from LocatePpi or FsRecoveryRead
//----------------------------------------------------------------------
//<AMI_PHDR_END>
static EFI_STATUS LoadRecoveryCapsule(
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    IN UINTN                              CapsuleInstance,
    OUT VOID                              *Buffer )
{
    EFI_STATUS Status;
    AMI_CAPSULE_HOB *CapsuleHob;
    static EFI_GUID CapsuleHobGuid = AMI_CAPSULE_HOB_GUID;
    static EFI_GUID AptioFwCapsuleGuid = APTIO_FW_CAPSULE_GUID;
    static EFI_GUID W8FwUpdateImageCapsuleGuid = W8_FW_UPDATE_IMAGE_CAPSULE_GUID;
    EFI_CAPSULE_HEADER *Capsule;
    VOID *Data;
    UINTN CapsuleSize;

    Status = (*PeiServices)->GetHobList(PeiServices, &CapsuleHob);
    if(EFI_ERROR(Status))
        return EFI_SUCCESS;

    do {
        Status = FindNextHobByGuid(&CapsuleHobGuid, &CapsuleHob);
        if(!EFI_ERROR(Status)) {
            Capsule = (EFI_CAPSULE_HEADER *)(VOID *)(UINTN)(CapsuleHob->CapsuleData);
            if(!guidcmp(&AptioFwCapsuleGuid, &(CapsuleHob->CapsuleGuid))) { //we found AFU recovery capsule, let's keep capsule header and put into provided buffer
                MemCpy(Buffer, Capsule, Capsule->CapsuleImageSize);
                return EFI_SUCCESS;
            }
            if(!guidcmp(&W8FwUpdateImageCapsuleGuid, &(CapsuleHob->CapsuleGuid))) { //we found Win8 recovery capsule, let's skip capsule header and put into provided buffer
                CapsuleSize = Capsule->CapsuleImageSize - Capsule->HeaderSize;
                Data = (VOID *)((UINT8 *)Capsule + Capsule->HeaderSize);
                MemCpy(Buffer, Data, CapsuleSize);
                return EFI_SUCCESS;
            }                
        }
    } while(!EFI_ERROR(Status));

    return Status;
}

/************************************************************************/
/*				Entry Point												*/
/************************************************************************/
EFI_PEI_DEVICE_RECOVERY_MODULE_PPI CapsuleDeviceRecoveryModule = {
    GetNumberRecoveryCapsules, GetRecoveryCapsuleInfo, LoadRecoveryCapsule
};

// PPI to be installed
static EFI_PEI_PPI_DESCRIPTOR CapsuleDeviceRecoveryPpiList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &guidRecoveryDevice, &CapsuleDeviceRecoveryModule
    }
};


//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure:	CapsuleDeviceRecoveryEntry
//
// Description:	
//  Installs EFI_PEI_DEVICE_RECOVERY_MODULE_PPI for loading recovery 
//  images from APTIO_FW_CAPSULE_GUID capsule
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS CapsuleDeviceRecoveryEntry(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    return (*PeiServices)->InstallPpi( PeiServices, CapsuleDeviceRecoveryPpiList );
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
