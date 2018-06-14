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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatRecovery/PfatRecovery.c 1     4/05/13 5:36p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/05/13 5:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatRecovery/PfatRecovery.c $
// 
// 1     4/05/13 5:36p Fredericko
// [TAG]  		EIP119706
// [Category]  	Improvement
// [Description]  	Support Recovery in pfat module
// [Files]  		PfatRecovery.cif
// PfatRecovery.sdl
// PfatRecovery.mak
// PfatRecovery.dxs
// PfatRecovery.c
// PfatRecoveryHook.c
// 
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <PEI.h>
#include <AmiPeiLib.h>
#include <token.h>
#include <PPI\stall.h>
#include <PPI\DeviceRecoveryModule.h>
#include <HOB.h>
#include <AmiHobs.h>
#include <PfatDefinitions.h>

#define PFAT_PACKAGE_CERT   524
//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes
typedef struct
{
    EFI_PEI_DEVICE_RECOVERY_MODULE_PPI      *pDRM_Ppi;
    EFI_PEI_DEVICE_LOAD_RECOVERY_CAPSULE    SavedLoadCapsule;
    
} DEVICE_RECOVERY_MODULE_INFO;

//----------------------------------------------------------------------------
// Local Variables
DEVICE_RECOVERY_MODULE_INFO gDeviceRecoveryModuleInfo[MAX_DEVICE_RECOVERY_MODULE];


//----------------------------------------------------------------------------
// Function Definitions
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: FindAvailableMemory
//
// Description: 
//
// Input:
//  IN EFI_PEI_SERVICES             **PeiServices,
//
// Output:
//      EFI_PHYSICAL_ADDRESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_PHYSICAL_ADDRESS 
FindAvailableMemory (
    IN EFI_PEI_SERVICES             **PeiServices
)    
{
 	VOID                    *p;
 	UINT8                   i;
 	EFI_PHYSICAL_ADDRESS    TopOfMemory = 0xffffffff;

	for ((*PeiServices)->GetHobList(PeiServices, &p), i = 0; \
	     !(FindNextHobByType(EFI_HOB_TYPE_MEMORY_ALLOCATION, &p));	i++) {
	    if (TopOfMemory > ((EFI_HOB_MEMORY_ALLOCATION*)p)->AllocDescriptor.MemoryBaseAddress)
    	    TopOfMemory = ((EFI_HOB_MEMORY_ALLOCATION*)p)->AllocDescriptor.MemoryBaseAddress;
    }
    return (TopOfMemory - (PFAT_RECOVERY_IMAGE_SIZE & 0xFFF00000));
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: PfatRecoveryFileLoaded
//
// Description: Call this function at end of Pei. This currently
//  check recovery file.
//
// Input:
//  IN EFI_PEI_SERVICES             **PeiServices,
//  IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//  IN VOID                         *Ppi
//
//
// Output:
//      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PfatRecoveryFileLoaded (
    IN EFI_PEI_SERVICES         **PeiServices,
    IN RECOVERY_IMAGE_HOB       *RecoveryHob
)
{
    UINT8                   *p;
    UINT32                  i = 0, j = 0; 
    PUP_HEADER              *PupHdr;
    EFI_STATUS              Status;
    EFI_PHYSICAL_ADDRESS    Buffer = NULL;
    EFI_BOOT_MODE           BootMode;
    UINT8                   pAmiPfatSign[] = "_AMIPFAT"; 
    EFI_GUID                PfatHobGuid     = PFAT_HOB_GUID;
    PFAT_HOB                *PfatHob;
    
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    if ((EFI_ERROR(Status)) || (BootMode != BOOT_IN_RECOVERY_MODE)) 
        return EFI_SUCCESS;

    // To avoid out of memory resource with AllocatePages in PEI phase, find 
    // out the top of available memory to re-collate rom image w/o PAT headers.
    Buffer = FindAvailableMemory(PeiServices);
    
    p = (UINT8*)RecoveryHob->Address;
    
    // Verify AMIPFAT Header.
    if (MemCmp (p + 8, pAmiPfatSign, 8)) return Status;
    
    i = *(UINT32*)p; 
    PupHdr = (PUP_HEADER*)(p + i);
    do {
        // skip ScriptSection and PUP Header
        i += (PupHdr->ScriptSectionSize + sizeof(PUP_HEADER));
        // collect DataSection only to buffer.
        (*PeiServices)->CopyMem ((UINT8*)Buffer + j, \
                                    (UINT8*)p + i, PupHdr->DataSectionSize);
        // pointer to next PUP block.
        i += (PupHdr->DataSectionSize + PFAT_PACKAGE_CERT);
        j += PupHdr->DataSectionSize;
        PupHdr = (PUP_HEADER*)(p + i);

    } while (i < PFAT_RECOVERY_IMAGE_SIZE);

    // Skip ME Region if needed (j = Original image size).
    (*PeiServices)->CopyMem ((UINT8*)RecoveryHob->Address, \
                             (UINT8*)Buffer + (j - FLASH_SIZE), \
                             FLASH_SIZE );

    // Invalidate PfatHob for disabling PFAT during DXE.
    (*PeiServices)->GetHobList(PeiServices, &PfatHob);
    Status = FindNextHobByGuid(&PfatHobGuid, &PfatHob);
    if(!EFI_ERROR(Status)) {
        PfatHob->EfiHobGuidType.Header.HobType = EFI_HOB_TYPE_UNUSED;
    }
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   LoadRecoveryCapsuleHook
//
// Description: 
//
// Input:       IN EFI_PEI_SERVICES             **PeiServices,
//              IN EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS 
LoadRecoveryCapsuleHook (
    IN EFI_PEI_SERVICES                   **PeiServices,
    IN EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *This,
    IN UINTN                              CapsuleInstance,
    OUT VOID                              *Buffer )
{
    UINT8               i = 0;
    RECOVERY_IMAGE_HOB  RecoveryHob;
    EFI_STATUS          Status;
    
    // All the LoadRecoveryCapsule calls come here
    for (i = 0; gDeviceRecoveryModuleInfo[i].pDRM_Ppi != NULL; i++) {
        // Check "This" for identfiy the LoadRecoveryCapsule call.
        if (This != gDeviceRecoveryModuleInfo[i].pDRM_Ppi) continue;

        // Invoke the Original LoadRecoveryCapsule procedure
        Status = gDeviceRecoveryModuleInfo[i].SavedLoadCapsule ( \
                       PeiServices, This, CapsuleInstance, Buffer );
        if (EFI_ERROR(Status)) return Status;

        // Recovery image loaded, check if PFAT image then reconstruct the
        // BIOS image.
        RecoveryHob.Address = (EFI_PHYSICAL_ADDRESS)Buffer;
        Status = PfatRecoveryFileLoaded (PeiServices, &RecoveryHob);
        break;
    }
    return EFI_SUCCESS;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   PfatRecoveryEntry
//
// Description: 
//
// Input:       EFI_HANDLE          - ImageHandle
//              EFI_SYSTEM_TABLE*   - SystemTable
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PfatRecoveryEntry (
    IN EFI_FFS_FILE_HEADER  *FfsHeader,
    IN EFI_PEI_SERVICES     **PeiServices
)
{
    UINTN           i = 0;
    EFI_STATUS      Status;
    EFI_PEI_DEVICE_RECOVERY_MODULE_PPI *pRecoveryDevice;
    EFI_GUID guidRecoveryDevice = EFI_PEI_DEVICE_RECOVERY_MODULE_PPI_GUID;
    EFI_PEI_PPI_DESCRIPTOR *pDummy;

    // Initialize gDeviceRecoveryModuleInfo structure
    for(i = 0; i < MAX_DEVICE_RECOVERY_MODULE; i++) {
        gDeviceRecoveryModuleInfo[i].pDRM_Ppi = NULL;
        gDeviceRecoveryModuleInfo[i].SavedLoadCapsule = NULL;
    }
    i = 0;
  	do {
        // Discover the Device Recovery Module PPIs for hooking the 
        // LoadRecoveryCapule procedure.
		Status = (*PeiServices)->LocatePpi(PeiServices, \
    		        &guidRecoveryDevice, i, &pDummy, &pRecoveryDevice);
    	if (!EFI_ERROR(Status)) {
    	    // Save Ppi pointer and LoadRecoveryCapsule procedure for Hook used.
    	    gDeviceRecoveryModuleInfo[i].pDRM_Ppi = pRecoveryDevice;
    	    gDeviceRecoveryModuleInfo[i++].SavedLoadCapsule = pRecoveryDevice->LoadRecoveryCapsule;
    	    // Hook the LaodRecoveryCapsule procedure.
    	    pRecoveryDevice->LoadRecoveryCapsule = LoadRecoveryCapsuleHook;
    	} 
    } while(!EFI_ERROR(Status));  
    return EFI_SUCCESS;
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