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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Capsule2_0/Capsule2_0Runtime.c 1     10/02/15 4:32a Chienhsieh $
//
// $Revision: 1 $
//
// $Date: 10/02/15 4:32a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/Capsule2_0/Capsule2_0Runtime.c $
// 
// 1     10/02/15 4:32a Chienhsieh
// Update EIP225308
// 
// 2     7/14/15 4:31p Artems
// [TAG]  		EIP225308
// [Category]  	Improvement
// [Description]  	CAPSULE_UPDATE_VAR is not clear after WIN10 BSOD issue
// capsule requriement.
// [Files]  		Capsule2_0Runtime.c
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
// Name:    Capsule2_0Runtime.c
//
// Description: Capsule runtime services implementation
//
//----------------------------------------------------------------------
//<AMI_FHDR_END>

//----------------------------------------------------------------------

#include <Token.h>
#include <Protocol/LoadedImage.h>
#include <AmiDxeLib.h>
#include <Capsule.h>
#include <Protocol/Capsule.h>

//----------------------------------------------------------------------
#ifndef MAX_CAPSULE_ADDRESS
#define MAX_CAPSULE_ADDRESS 0x100000000 //4GB
#endif

static EFI_CAPSULE_RUNTIME_DATA mCapsuleRuntimeData = { NULL, FALSE };

static EFI_GUID gCapsuleVendorGuid    = EFI_CAPSULE_AMI_GUID;
static EFI_GUID gDxeServicesTableGuid = DXE_SERVICES_TABLE_GUID;

EFI_STATUS UpdateCapsule(
  IN EFI_CAPSULE_HEADER    **CapsuleHeaderArray,
  IN UINTN                 CapsuleCount,
  IN EFI_PHYSICAL_ADDRESS  ScatterGatherList OPTIONAL
);

EFI_STATUS QueryCapsuleCapabilities(
  IN  EFI_CAPSULE_HEADER **CapsuleHeaderArray,
  IN  UINTN              CapsuleCount,
  OUT UINT64             *MaximumCapsuleSize,
  OUT EFI_RESET_TYPE     *ResetType
);

BOOLEAN SupportUpdateCapsuleReset (
    VOID
);

VOID SupportCapsuleSize (
    IN OUT UINT32 *MaxSizePopulate,
    IN OUT UINT32 *MaxSizeNonPopulate
);

VOID CapsuleExitBootServices (
    IN EFI_EVENT Event,
    IN VOID      *Context
);

BOOLEAN ValidateSgl (
    IN EFI_PHYSICAL_ADDRESS MailBox
);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Capsule20RuntimeInit
//
// Description: Capsule runtime driver entry point
//
// Input:       
//  IN EFI_HANDLE ImageHandle - Image handle
//  IN EFI_SYSTEM_TABLE *SystemTable - pointer to system table
//
// Output:      EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Capsule20RuntimeInit(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_HANDLE Handle = NULL;
    EFI_STATUS Status;

    InitAmiLib(ImageHandle, SystemTable);

    pRS->UpdateCapsule = UpdateCapsule;
    pRS->QueryCapsuleCapabilities = QueryCapsuleCapabilities;

    Status = pBS->CreateEvent (
                  EFI_EVENT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_NOTIFY,
                  CapsuleExitBootServices,
                  &mCapsuleRuntimeData,
                  &(mCapsuleRuntimeData.CapsuleExitBootServiceEvent) );

    pBS->InstallMultipleProtocolInterfaces (
            &Handle, 
            &gEfiCapsuleArchProtocolGuid, 
            NULL,
            NULL );
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   UpdateCapsule
//
// Description: This code finds if the capsule needs reset to update, if no, update immediately.
//
// Input:       
//  IN EFI_CAPSULE_HEADER **CapsuleHeaderArray - array of pointers to capsule headers passed in
//  IN UINTN CapsuleCount - number of capsule
//  IN EFI_PHYSICAL_ADDRESS ScatterGatherList - physical address of datablock list points to capsule
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_INVALID_PARAMETER - CapsuleCount is less than 1,CapsuleGuid is not supported
//              EFI_DEVICE_ERROR - capsule processing failed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS UpdateCapsule (
    IN EFI_CAPSULE_HEADER   **CapsuleHeaderArray,
    IN UINTN                CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL
)
{
    UINTN               ArrayNumber;
    VOID                *BufferPtr;
    EFI_STATUS          Status;
    EFI_CAPSULE_HEADER  *CapsuleHeader;

    if ((CapsuleCount < 1) || (CapsuleCount > MAX_SUPPORT_CAPSULE_NUM)){
        return EFI_INVALID_PARAMETER;
    }

    BufferPtr       = NULL;
    CapsuleHeader   = NULL;

    //
    //Compare GUIDs with EFI_CAPSULE_GUID, if capsule header contains CAPSULE_FLAGS_PERSIST_ACROSS_RESET
    //and CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE flags,whatever the GUID is, the service supports.
    //

    for (ArrayNumber = 0; ArrayNumber < CapsuleCount; ArrayNumber++) {
        CapsuleHeader = CapsuleHeaderArray[ArrayNumber];
        if ((CapsuleHeader->Flags & CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE) && 
            !(CapsuleHeader->Flags & CAPSULE_FLAGS_PERSIST_ACROSS_RESET)) {
            return EFI_INVALID_PARAMETER;      
        }

        if ((CapsuleHeader->Flags & CAPSULE_FLAGS_INITIATE_RESET) && 
            !(CapsuleHeader->Flags & CAPSULE_FLAGS_PERSIST_ACROSS_RESET)) {
            return EFI_INVALID_PARAMETER;      
        }

// TODO: Add Oem porting hook to handle OEM-specific capsule
    }

    //
    //Assume that capsules have the same flags on reseting or not. 
    //
    CapsuleHeader = CapsuleHeaderArray[0];

    if ((CapsuleHeader->Flags & CAPSULE_FLAGS_PERSIST_ACROSS_RESET) != 0) {
        //
        //Check if the platform supports update capsule across a system reset
        //
        if (!SupportUpdateCapsuleReset()) {
            return EFI_UNSUPPORTED;
        }
    
        if (!ValidateSgl(ScatterGatherList)) {
            return EFI_INVALID_PARAMETER;
        } else {
            Status = pRS->SetVariable (
                 CAPSULE_UPDATE_VAR,  
                 &gCapsuleVendorGuid,     
                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS,  
                 sizeof (EFI_PHYSICAL_ADDRESS), 
                 (VOID *) &ScatterGatherList );
            if (Status != EFI_SUCCESS) { 
                return EFI_DEVICE_ERROR;
            }
        }

        if ((CapsuleHeader->Flags & CAPSULE_FLAGS_INITIATE_RESET) != 0) {
            pRS->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
            EFI_DEADLOOP();
        }

        return EFI_SUCCESS;
    }

// TODO: Add Oem porting hook to handle OEM-specific capsule

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   QueryCapsuleCapabilities
//
// Description: This code is query about capsule capability
//
// Input:       
//  IN EFI_CAPSULE_HEADER **CapsuleHeaderArray - array of pointers to capsule headers passed in
//  IN UINTN CapsuleCount - number of capsule
//  OUT UINT64 *MaximumCapsuleSize - pointer to store maximum supported capsule size
//  OUT EFI_RESET_TYPE *ResetType - reset type required by capsule
//
// Output:      EFI_SUCCESS - capsule processed successfully
//              EFI_INVALID_PARAMETER - CapsuleCount is less than 1,CapsuleGuid is not supported, 
//                                      MaximumCapsuleSize or ResetType are NULL
//              EFI_UNSUPPORTED - capsule type is not supported
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS QueryCapsuleCapabilities(
    IN  EFI_CAPSULE_HEADER  **CapsuleHeaderArray,
    IN  UINTN                CapsuleCount,
    OUT UINT64              *MaximumCapsuleSize,
    OUT EFI_RESET_TYPE      *ResetType
)
{
    UINTN              ArrayNumber;
    EFI_CAPSULE_HEADER *CapsuleHeader;
    UINT32             MaxSizePopulate;
    UINT32             MaxSizeNonPopulate;


    if ((CapsuleCount < 1) || (CapsuleCount > MAX_SUPPORT_CAPSULE_NUM)){
        return EFI_INVALID_PARAMETER;
    }

    if ((MaximumCapsuleSize == NULL) ||(ResetType == NULL)) {
        return EFI_INVALID_PARAMETER;
    }  

    CapsuleHeader = NULL;
  
    //
    //Compare GUIDs with EFI_CAPSULE_GUID, if capsule header contains CAPSULE_FLAGS_PERSIST_ACROSS_RESET
    //and CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE flags,whatever the GUID is ,the service supports.
    //
    for (ArrayNumber = 0; ArrayNumber < CapsuleCount; ArrayNumber++) {
        CapsuleHeader = CapsuleHeaderArray[ArrayNumber];
        if ((CapsuleHeader->Flags & CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE) && 
            !(CapsuleHeader->Flags & CAPSULE_FLAGS_PERSIST_ACROSS_RESET)) {
            return EFI_INVALID_PARAMETER;      
        }

//TODO add OEM hook to support OEM defined capsules
    }

    SupportCapsuleSize(&MaxSizePopulate,&MaxSizeNonPopulate);
    //
    //Assume that capsules have the same flags on reseting or not. 
    //
    CapsuleHeader = CapsuleHeaderArray[0];  
    if ((CapsuleHeader->Flags & CAPSULE_FLAGS_PERSIST_ACROSS_RESET) != 0) {
    //
    //Check if the platform supports update capsule across a system reset
    //
        if (!SupportUpdateCapsuleReset()) {
            return EFI_UNSUPPORTED;
        }
        *ResetType = EfiResetWarm;
        *MaximumCapsuleSize = MaxSizePopulate;    
    } else {
        *ResetType = EfiResetCold;
        *MaximumCapsuleSize = MaxSizeNonPopulate;
    }  
    return EFI_SUCCESS;
} 

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SupportUpdateCapsuleReset
//
// Description: This function returns if the platform supports update capsule across a system reset.
//
// Input:       None
//
// Output:      TRUE - memory can be preserved across reset
//              FALSE - memory integrity across reset is not guaranteed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN SupportUpdateCapsuleReset (
    VOID
)
{
    return SUPPORT_UPDATE_CAPSULE_RESET;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SupportCapsuleSize
//
// Description: This code returns the max size capsule the platform supports.
//
// Input:       
//  IN OUT UINT32 *MaxSizePopulate - max supported capsule size, that updated across reset
//  IN OUT UINT32 *MaxSizeNonPopulate - max supported capsule size for immediate update
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID SupportCapsuleSize (
    IN OUT UINT32 *MaxSizePopulate,
    IN OUT UINT32 *MaxSizeNonPopulate
)
{
    //
    //Here is a sample size, different platforms have different sizes.
    //
    *MaxSizePopulate    = MAX_CAPSULE_SIZE;
    *MaxSizeNonPopulate = MAX_CAPSULE_SIZE;
    return; 
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   CapsuleExitBootServices
//
// Description: Exit boot services event callback
//
// Input:       
//  IN EFI_EVENT  Event - Exit boot services event
//  IN VOID *Context - pointer to event context
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID CapsuleExitBootServices (
    IN EFI_EVENT  Event,
    IN VOID       *Context
)
{
    EFI_CAPSULE_RUNTIME_DATA        *pCapsuleRuntimeData;
    //
    // Get our context
    //
    pCapsuleRuntimeData = (EFI_CAPSULE_RUNTIME_DATA *) Context;
    pCapsuleRuntimeData->IsRuntimeMode = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//  Procedure:   ValidateSgl
//
//  Description:
//  This function validates ScatterGatherList
//
//  Input:
//  IN EFI_PHYSICAL_ADDRESS MailBox - address of the capsule mailbox
//
//  Output:
//  TRUE - ScatterGatherList is valid, FALSE otherwise
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN ValidateSgl (
    IN EFI_PHYSICAL_ADDRESS Mailbox
)
{
    EFI_CAPSULE_BLOCK_DESCRIPTOR *Ptr;
    UINTN Chunks = 0;
    UINT64 Result = 0;

    if (Mailbox >= MAX_CAPSULE_ADDRESS || Mailbox == 0)
        return FALSE;

    Ptr = (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)Mailbox;

    do {
        if(Ptr->DataBlock >= MAX_CAPSULE_ADDRESS)   //pointer above 4GB
            return FALSE;

        if(Ptr->Length != 0) {
            if(Ptr->Length > MAX_CAPSULE_SIZE - Result)
                return FALSE;
            Result += Ptr->Length;
            Chunks++;
            Ptr++;
        } else if (Ptr->DataBlock != NULL) {
            if(Ptr == (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer))
            //when continuation pointer points to itself it's either error or malicious capsule, we won't process it
                return FALSE;
            Ptr = (EFI_CAPSULE_BLOCK_DESCRIPTOR *)(UINTN)(Ptr->ContinuationPointer);
        } else {
            break;
        }
    } while(Chunks <= MAX_CAPSULE_BLOCK_DESCRIPTOR_COUNT);

    return (Chunks <= MAX_CAPSULE_BLOCK_DESCRIPTOR_COUNT) ? TRUE : FALSE;
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