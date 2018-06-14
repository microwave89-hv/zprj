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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBSmm.c 1     2/08/12 4:34a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 4:34a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBSmm.c $
// 
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBSMM.C
//
// Description: This file contains code for SMM access and control (both the
//              protocol defined by Framework
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Efi.h>
#include <token.h>
#include <HOB.h>
#include <DXE.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>

// Used Protocols
#include <Protocol\PciRootBridgeIo.h>
// Produced Protocols
#include <Protocol\SmmAccess.h>
#if PI_SPECIFICATION_VERSION >= 0x0001000A
#include <Protocol\SmmAccess2.h>
#endif

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

EFI_HOB_HANDOFF_INFO_TABLE *pHIT;

static EFI_SMRAM_DESCRIPTOR gSmramMap[] = {
    {
        0xA0000,                            // PhysicalStart
        0xA0000,                            // CpuStart
        128*1024,                           // PhysicalSize
        EFI_ALLOCATED | EFI_SMRAM_CLOSED    // RegionState
    },
    {
        0,                                  // PhysicalStart
        0,                                  // CputStart
        TSEG_SIZE,                          // PhysicalSize
        EFI_ALLOCATED | EFI_SMRAM_CLOSED    // RegionState
    }
};

#define SMRAM_MAP_NUM_DESCRIPTORS (sizeof(gSmramMap)/sizeof(EFI_SMRAM_DESCRIPTOR))
static UINTN SmramMapNumDescriptors = SMRAM_MAP_NUM_DESCRIPTORS;

// GUID Definition(s)

EFI_GUID gGuidHobList = HOB_LIST_GUID;
EFI_GUID gEfiSmmAccessProtocolGuid = EFI_SMM_ACCESS_PROTOCOL_GUID;

// Protocol Definition(s)

// External Declaration(s)

//#### extern EFI_GUID  gEfiBootScriptSaveGuid;
//#### extern EFI_GUID  gEfiPciRootBridgeIoProtocolGuid;
//#### extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *gPciRootBridgeIo;
//#### extern EFI_BOOT_SCRIPT_SAVE_PROTOCOL *gBootScriptSave;

// Function Definition(s)

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBSMM_EnableSMMAddress
//
// Description: This function programs the NB chipset registers to enable
//              appropriate SMRAM area.  
//
// Input:       None
//
// Output:      EFI_SUCCESS     Always
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBSMM_EnableSMMAddress (VOID)
{
    UINT64          qTsegAddress;

    // Currently TSEG address is assumed to be TOM - TSEG_SIZE
    // THIS CODE SHOULD BE CHANGED TO GET THE TSEG LOCATION FROM CPU INFO HOB
    qTsegAddress = pHIT->EfiMemoryTop;
#if NB_DEBUG_MESSAGE
    TRACE((TRACE_ALWAYS, "TSEG Address %x.\n", qTsegAddress));
#endif
    gSmramMap[1].PhysicalStart  = gSmramMap[1].CpuStart = qTsegAddress;
    gSmramMap[1].PhysicalSize   = TSEG_SIZE;

// Porting Required - Enable SMM area in Chipset (both TSEG & 0xA0000)  
// TSEG & 0xA0000 had been enabled at PEI phase.
// Porting ENDS

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBSMM_OpenSmram
//
// Description: This function programs the NB chipset registers to open
//              the SMRAM area.
//
// Input:       *This           - Pointer to the SMM access protocol
//              DescriptorIndex - Index of SMM Descriptor
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS             Opened the SMM area.
//                  EFI_INVALID_PARAMETER   Descriptor doesn't exist.
//                  EFI_ACCESS_DENIED       SMM area locked
//
// Modified:    gSmramMap[DescriptorIndex].RegionState to EFI_SMRAM_OPEN.
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              Here is the control flow of this function:
//                  1. If invalid Descriptor return EFI_INVALID_PARAMETER.
//                  2. Read NB SMM register.
//                  3. If locked, return EFI_ACCESS_DENIED
//                  4. Set Value for register to Open SMM area (0a0000-bffff)
//                  5. Write Register.
//                  6. Set OpenState to TRUE.
//                  7. Set the RegionState to EFI_SMRAM_OPEN.
//                  8. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBSMM_OpenSmram (
    IN EFI_SMM_ACCESS_PROTOCOL      *This,
    IN UINTN                        DescriptorIndex )
{
    //-UINT8 SmramControl;

    if (DescriptorIndex >= SmramMapNumDescriptors)
        return EFI_INVALID_PARAMETER;

// Porting Required - Open SMM area in Chipset (both TSEG & 0xA0000)    
    if (gSmramMap[0].RegionState == EFI_SMRAM_LOCKED ) 
            /* Write code to check SMM lock */
        return EFI_ACCESS_DENIED;   //If device is locked, return error.

/*
    SmramControl = MmPci8(MC_BUS, MC_DEV, MC_FUN, SMRAMC);

    if ((SmramControl & SMRAMC_D_LCK_MASK) != 0)
    {
        gSmramMap[0].RegionState = EFI_SMRAM_LOCKED;
        gSmramMap[1].RegionState = EFI_SMRAM_LOCKED;
        return EFI_DEVICE_ERROR;
    }

    SmramControl |= SMRAMC_D_OPEN_MASK;
    SmramControl &= ~(SMRAMC_D_CLS_MASK);

    MmPci8(MC_BUS, MC_DEV, MC_FUN, SMRAMC) = SmramControl;
*/
// Porting ENDS

    // Update appropriate flags
    This->OpenState = TRUE;
    gSmramMap[0].RegionState = EFI_SMRAM_OPEN;
    gSmramMap[1].RegionState = EFI_SMRAM_OPEN;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBSMM_CloseSmram
//
// Description: This function programs the NB chipset registers to close
//              the SMRAM area.
//
// Input:       *This               Pointer to the SMM access protocol
//              DescriptorIndex     Index of SMM Descriptor
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS             Closed the SMM area.
//                  EFI_INVALID_PARAMETER   Descriptor doesn't exist.
//                  EFI_ACCESS_DENIED       SMM area locked
//
// Modified:    gSmramMap[DescriptorIndex].RegionState to EFI_SMRAM_CLOSED &
//              EFI_ALLOCATED
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              Here is the control flow of this function:
//                  1. If invalid Descriptor return EFI_INVALID_PARAMETER.
//                  2. Read NB SMM register.
//                  3. If locked, return EFI_ACCESS_DENIED
//                  4. Set Value for register to close SMM area (0a0000-bffff)
//                  5. Write Register.
//                  6. Set OpenState to FALSE.
//                  7. Set the RegionState to EFI_SMRAM_CLOSED & EFI_ALLOCATED
//                  8. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBSMM_CloseSmram (
    IN EFI_SMM_ACCESS_PROTOCOL      *This,
    IN UINTN                        DescriptorIndex )
{
    //-UINT8 SmramControl;

    if (DescriptorIndex >= SmramMapNumDescriptors)
        return EFI_INVALID_PARAMETER;

// Porting Required - Close SMM area in Chipset (both TSEG & 0xA0000)   
    if (gSmramMap[0].RegionState == EFI_SMRAM_LOCKED ) 
            /* Write code to check SMM lock */
        return EFI_ACCESS_DENIED;   //If device is locked, return error.

/*
    SmramControl = MmPci8(MC_BUS, MC_DEV, MC_FUN, SMRAMC);

    if ((SmramControl & SMRAMC_D_LCK_MASK) != 0)
    {
        gSmramMap[0].RegionState = EFI_SMRAM_LOCKED;
        gSmramMap[1].RegionState = EFI_SMRAM_LOCKED;
        return EFI_DEVICE_ERROR;
    }

    SmramControl &= ~(SMRAMC_D_OPEN_MASK);

    MmPci8(MC_BUS, MC_DEV, MC_FUN, SMRAMC) = SmramControl;
*/
// Porting ENDS

    // Update appropriate flags
    This->OpenState = FALSE;
    gSmramMap[0].RegionState = EFI_SMRAM_CLOSED | EFI_ALLOCATED;
    gSmramMap[1].RegionState = EFI_SMRAM_CLOSED | EFI_ALLOCATED;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBSMM_LockSmram
//
// Description: This function programs the NB chipset registers to lock
//              the SMRAM area from opening/closing.  Only system level reset
//              can unlock the SMRAM lock.
//
// Input:       *This               Pointer to the SMM access protocol
//              DescriptorIndex     Index of SMM Descriptor
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS             Locked the SMM area.
//                  EFI_INVALID_PARAMETER   Descriptor doesn't exist.
//                  EFI_DEVICE_ERROR        SMM area is opened, need to be
//                                          closed first before locking
//
// Modified:    gSmramMap[DescriptorIndex].RegionState to EFI_SMRAM_LOCKED.
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              Here is the control flow of this function:
//                  1. If invalid Descriptor return EFI_INVALID_PARAMETER.
//                  2. Read NB SMM register.
//                  3. If opened, return EFI_ACCESS_DENIED
//                  4. Set Value for register to lock SMM area (0a0000-bffff)
//                  5. Write Register.
//                  6. Set the RegionState to EFI_SMRAM_CLOSED & EFI_ALLOCATED
//                  7. Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBSMM_LockSmram (
    IN EFI_SMM_ACCESS_PROTOCOL      *This,
    IN UINTN                        DescriptorIndex )
{
    //-UINT8 SmramControl;

    //Both regions must open and close at the same time.
    if (DescriptorIndex >= SmramMapNumDescriptors)
        return EFI_INVALID_PARAMETER;

// Porting Required - Lock SMM area in Chipset (both TSEG & 0xA0000)    
    if (gSmramMap[0].RegionState == EFI_SMRAM_OPEN)
    {
        /* Write code to check SMM lock */
        return EFI_ACCESS_DENIED;   //If SMM is opened, return error.
    }

/*
    SmramControl = MmPci8(MC_BUS, MC_DEV, MC_FUN, SMRAMC);

    SmramControl &= ~(SMRAMC_D_OPEN_MASK);
    SmramControl |= (SMRAMC_D_LCK_MASK);

    MmPci8(MC_BUS, MC_DEV, MC_FUN, SMRAMC) = SmramControl;
*/
// Porting ENDS

    // Update appropriate flags
    This->LockState = TRUE;
    gSmramMap[0].RegionState = EFI_SMRAM_LOCKED;
    gSmramMap[1].RegionState = EFI_SMRAM_LOCKED;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBSMM_GetCapabilities
//
// Description: This function returns the current SMRAM area map information
//              such as number of regions and its start address and size
//
// Input:       *This               Pointer to the SMM access protocol
//              *SmramMapSize       Size of the SMRAM map buffer provided
//              *SmramMap           Buffer to copy the SMRAM map information
//
// Output:      EFI_STATUS
//                  EFI_SUCCESS             Smram Map copied into buffer
//                  EFI_BUFFER_TOO_SMALL    Indicates that provided buffer is
//                                          not enough
//              *SmramMapSize       Filled with required/updated size
//
// Notes:       CHIPSET AND/OR BOARD PORTING NEEDED
//              Here is the control flow of this function:
//                  1.If Smram Map Size less than the actual map size, set 
//                    the map size and return EFI_BUFFER_TOO_SMALL.
//                  2.Copy the Smram Map descriptors into the supplied buffer.
//                  3.Set the map size in *SmramMapSize, just in case is
//                    larger than the actual buffer.
//                  4.Return EFI_SUCCESS.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NBSMM_GetCapabilities (
    IN EFI_SMM_ACCESS_PROTOCOL      *This,
    IN OUT UINTN                    *SmramMapSize,
    OUT EFI_SMRAM_DESCRIPTOR        *SmramMap )
{
    UINTN       i;

    if (*SmramMapSize < sizeof(gSmramMap))
    {
        // If input map size to small,
        // report the correct map size and return error.
        *SmramMapSize = sizeof(gSmramMap);
        return EFI_BUFFER_TOO_SMALL;
    }

    for(i=0; i < SmramMapNumDescriptors; ++i) 
        SmramMap[i] = gSmramMap[i];

    *SmramMapSize = sizeof(gSmramMap);      // Set the correct map size

    return EFI_SUCCESS;
}

EFI_SMM_ACCESS_PROTOCOL mSmmAccess = {
    NBSMM_OpenSmram,
    NBSMM_CloseSmram,
    NBSMM_LockSmram,
    NBSMM_GetCapabilities,
    FALSE,
    FALSE
};

EFI_SMM_ACCESS_PROTOCOL *gSmmAccess = NULL;

#if PI_SPECIFICATION_VERSION >= 0x0001000A
EFI_STATUS OpenSmram2(IN EFI_SMM_ACCESS2_PROTOCOL *This)
{
    EFI_STATUS Status;
    UINTN i;

    if ((This->LockState != gSmmAccess->LockState) ||
        (This->OpenState != gSmmAccess->OpenState))
    {
        This->LockState = gSmmAccess->LockState;
        This->OpenState = gSmmAccess->OpenState;
    }

// Porting Required - Open SMM area in Chipset (both TSEG & 0xA0000)    
    if (gSmramMap[0].RegionState == EFI_SMRAM_LOCKED) 
    {
        /* Write code to check SMM lock */

        //If device is locked, return error.
        return EFI_ACCESS_DENIED;
    }

    for(i=0; i < SmramMapNumDescriptors; ++i)
    {
        Status = gSmmAccess->Open(gSmmAccess, i);
        if (Status != EFI_SUCCESS)
            return Status;
    }
// Porting ENDS

    // Update appropriate flags
    This->OpenState = TRUE;

    return EFI_SUCCESS;
}

EFI_STATUS CloseSmram2(IN EFI_SMM_ACCESS2_PROTOCOL *This)
{
    EFI_STATUS Status;
    UINTN i;

    if ((This->LockState != gSmmAccess->LockState) ||
        (This->OpenState != gSmmAccess->OpenState))
    {
        This->LockState = gSmmAccess->LockState;
        This->OpenState = gSmmAccess->OpenState;
    }

// Porting Required - Close SMM area in Chipset (both TSEG & 0xA0000)   
    if (gSmramMap[0].RegionState == EFI_SMRAM_LOCKED) 
    {
        /* Write code to check SMM lock */

        //If device is locked, return error.
        return EFI_ACCESS_DENIED;
    }

    for(i=0; i < SmramMapNumDescriptors; ++i)
    {
        Status = gSmmAccess->Close(gSmmAccess, i);
        if (Status != EFI_SUCCESS)
            return Status;
    }
// Porting ENDS

    // Update appropriate flags
    This->OpenState = FALSE;

    return EFI_SUCCESS;
}

EFI_STATUS LockSmram2(IN EFI_SMM_ACCESS2_PROTOCOL *This)
{
    EFI_STATUS Status;
    UINTN i;

    if ((This->LockState != gSmmAccess->LockState) ||
        (This->OpenState != gSmmAccess->OpenState))
    {
        This->LockState = gSmmAccess->LockState;
        This->OpenState = gSmmAccess->OpenState;
    }

// Porting Required - Lock SMM area in Chipset (both TSEG & 0xA0000)    
    if (gSmramMap[0].RegionState == EFI_SMRAM_OPEN) 
    {
        /* Write code to check SMM lock */
        return EFI_ACCESS_DENIED;   //If SMM is opened, return error.
    }

    for(i=0; i < SmramMapNumDescriptors; ++i)
    {
        Status = gSmmAccess->Lock(gSmmAccess, i);
        if (Status != EFI_SUCCESS)
            return Status;
    }
// Porting ENDS

    // Update appropriate flags
    This->LockState = TRUE;

    return EFI_SUCCESS;
}

EFI_STATUS GetCapabilities2(
    IN CONST EFI_SMM_ACCESS2_PROTOCOL  *This,
    IN OUT UINTN                       *SmramMapSize,
    IN OUT EFI_SMRAM_DESCRIPTOR        *SmramMap
)
{
    EFI_STATUS Status;

    Status = gSmmAccess->GetCapabilities(gSmmAccess, SmramMapSize, SmramMap);

    return Status;
}

EFI_SMM_ACCESS2_PROTOCOL gSmmAccess2 = {
    OpenSmram2,
    CloseSmram2,
    LockSmram2,
    GetCapabilities2,
    FALSE,
    FALSE
};
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NBSMM_Init
//
// Description: This function is invoked from NB DXE to initialize SMM
//              related stuff in NorthBridge and install appropriate
//              SMM protocols such as SMM Access & SMM Control
//
// Input:       ImageHandle Image handle
//              SystemTable Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS NbSmmInit (
    IN EFI_EVENT        Event,
    IN VOID             *Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN SmramMapSize = sizeof(gSmramMap);

    PROGRESS_CODE (DXE_NB_SMM_INIT);

    Status = pBS->LocateProtocol(&gEfiSmmAccessProtocolGuid, NULL, &gSmmAccess);
    if (EFI_ERROR(Status))
    {
        pHIT = GetEfiConfigurationTable(pST, &gGuidHobList);

        // Enable SMM address range by programming appropriate chipset registers
        NBSMM_EnableSMMAddress ();

        Status = pBS->InstallMultipleProtocolInterfaces(&TheImageHandle,
                                                       &gEfiSmmAccessProtocolGuid,
                                                       &mSmmAccess,
#if PI_SPECIFICATION_VERSION >= 0x0001000A
                                                       &gEfiSmmAccess2ProtocolGuid,
                                                       &gSmmAccess2,
#endif
                                                       NULL,
                                                       NULL );
        ASSERT_EFI_ERROR(Status);
    }
    else
    {
        Status = gSmmAccess->GetCapabilities(gSmmAccess, &SmramMapSize, gSmramMap);
        ASSERT_EFI_ERROR(Status);

        SmramMapNumDescriptors = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);

#if PI_SPECIFICATION_VERSION >= 0x0001000A
        Status = pBS->InstallMultipleProtocolInterfaces(&TheImageHandle,
                                                   &gEfiSmmAccess2ProtocolGuid,
                                                   &gSmmAccess2,
                                                   NULL,
                                                   NULL );
        ASSERT_EFI_ERROR(Status);
#endif
    }

    return Status;
}

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
