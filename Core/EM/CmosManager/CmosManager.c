//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Source/CmosManager.c 22    6/15/10 2:24p Michaela $
//
// $Revision: 22 $
//
// $Date: 6/15/10 2:24p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Source/CmosManager.c $
// 
// 22    6/15/10 2:24p Michaela
// 
// 21    3/08/10 5:40p Michaela
// 
// 20    3/05/10 4:55p Michaela
// 
// 19    12/04/09 7:32p Michaela
// 
// 18    12/03/09 6:31p Michaela
// 1. Moved gIsBsp here and added gIsColdBoot definition
// 
// 2. Updated CmosConfigureManager() to force calculation of
//    checksum after enabling the Optimal Defaults buffer.
//    
// 3. Updated NewCmosManagerInterface() to update first boot,
//    BSP detected and incoherency policy settings bits prior to
//    calculating the checksum and getting the battery status.
// 
// 17    11/10/09 9:14p Michaela
// 
// 16    7/29/09 9:59a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 15    6/15/09 5:11p Michaela
// 
// 14    6/02/09 3:27p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 13    3/11/09 3:38p Michaela
// 
// 12    2/16/09 10:26p Michaela
// Rename CmosManagerAsm to gCmosManagerAsm
// 
// 11    2/06/09 2:02p Michaela
// removed hard-coded FIRST_CMOS_REGISTER value
// 
// 10    11/25/08 3:20p Michaela
// Updates for Label 4.6.3_CMOSMGR_08
// - Assembly macro fixes
// - Added assembly macros
// - Moved loading defaults into DXE phase
// - Updated help file example
// 
// 9     11/17/08 4:41p Michaela
// --Removed Token Name strings in debug development code
// 
// 8     11/17/08 3:33p Michaela
// -added CMOS_ACCESS_TYPE typedef for client code usage
// -CMOS Buffer feature is depreciated
// -Removed debug code
// -SaveApiPointerToCmos & GetApiPointerFromCmos are now
//  directly calling CmosPhysicalReadWrite to avoid error if using
//  Optimal Defaults buffer for Reads/Writes
// -ABORT_ERROR_STATUS replaced with EFI_ERROR macro
//  usage
// 
// 7     11/14/08 9:07a Michaela
// CMOS register variables changed from UINT8 to UINT16
// 
// 6     11/07/08 5:13p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 5     3/25/08 3:00p Michaela
// Modified call to SynchronizeLegacyStatusRegisters
// 
// 4     3/07/08 4:07p Michaela
// Label 4.6.3_CMOSMGR_05 fixes:
// -- write errors to Optimal Defaults buffer before memory detection
// -- CMOS Token table corruption when name strings are disabled
// 
// 3     2/29/08 9:35p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 2     2/26/08 12:48p Michaela
// Added/modified Helpbuilder headers
// 
// 1     2/22/08 2:29p Michaela
// 
// 1     2/04/08 6:00p MichaelA
// Created
// 
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:    CmosManager.c
//
// Description: Contains the routines that constitute the CMOS manager
//              implementation.  This files is used to create object code
//              for both PEI and DXE phases, based upon the build
//              macro PEI_COMPILE.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Efi.h>
#ifdef PEI_COMPILE
    #include <Pei.h>
    #include <AmiPeiLib.h>
#else
    #include <AmiDxeLib.h>
#endif
#ifdef SMM_COMPILE
    #include <Protocol\SmmBase.h>
#endif
#include <CmosAccess.h>
#include "CmosManager.h"
#include "CmosManagerHob.h"
#include "SspTokens.h"
#include "CmosBoard.h"

//---------------------------------------------------------------------------
// These functions are originally defined in CmosAccess.c
//---------------------------------------------------------------------------
extern EFI_STATUS CmosRead(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken,
    OUT UINT8                       *CmosValue );
extern EFI_STATUS CmosWrite(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosToken,
    IN  UINT8                       CmosValue );
extern UINT16 CmosGetTokenFromRegister(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  UINT16                      CmosRegister );
extern EFI_STATUS CalculateChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      *ChecksumValue );
extern EFI_STATUS LoadOptimalDefaults(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager );
extern EFI_STATUS WriteChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      ChecksumValue );
extern EFI_STATUS ReadChecksum(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    OUT UINT16                      *ChecksumValue );
extern EFI_STATUS ReadCmosStatusBytes(
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    OUT CMOS_STATUS_BYTES           *StatusBytes );
extern EFI_STATUS SynchronizeLegacyStatusRegisters(
    IN  EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN CMOS_MANAGER_STATUS          BitMap,
    IN CMOS_BIT_ACCESS_TYPE         AccessType );
extern EFI_STATUS CmosPhysicalReadWrite(
    IN      EFI_CMOS_MANAGER_INTERFACE  *Manager,
    IN      CMOS_ACCESS_TYPE            AccessType,
    IN      UINT16                      CmosAddress,
    IN      UINT8                       BitsToWrite,  
    IN OUT  UINT8                       *CmosParameterValue );
    
extern EFI_STATUS CmosGetDateTime (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    OUT EFI_TIME                    *Time );

extern EFI_STATUS CmosSetDateTime (
    IN  EFI_CMOS_ACCESS_INTERFACE   *Cmos,
    IN  EFI_TIME                    *Time );

EFI_STATUS UpdateBatteryStatus (
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager );   

// porting functions

EFI_CMOS_IS_FIRST_BOOT  gIsFirstBoot  = CMOS_IS_FIRST_BOOT_MAPPING; 
EFI_CMOS_IS_BSP         gIsBsp        = CMOS_IS_BSP_MAPPING;
EFI_CMOS_IS_COLD_BOOT   gIsColdBoot   = CMOS_IS_COLD_BOOT_MAPPING;
EFI_CMOS_IS_CMOS_USABLE gCmosIsUsable = CMOS_IS_USABLE_MAPPING;


#if  defined( PEI_COMPILE ) || defined( SMM_COMPILE ) 

    // In early PEI, these data items are accessed in ROM.

    // In SMM, the gCmosOptimalDefaultTable structure is
    // read/write.

    extern CONST CMOS_TOKEN       gCmosTokenTable[];
    extern CONST UINT16           gCmosTokenTableSize;
    extern CONST CMOS_REGISTER    gCmosNoCheckSumTable[];
    extern CONST UINT16           gCmosNoCheckSumTableSize;
    extern CONST CMOS_REGISTER    gUnmanagedTable[];
    extern CONST UINT16           gUnmanagedTableSize;
    extern CMOS_REGISTER          gCmosOptimalDefaultTable[];
    extern CONST UINT16           gCmosOptimalDefaultTableSize;
    extern CONST UINT8            gFirstManagedRegister;
    extern CONST UINT8            gLastManagedRegister;
#endif


#ifdef PEI_COMPILE // PEI phase-specific declarations
    extern EFI_STATUS SaveCmosDataTablesToHob(
        EFI_PEI_SERVICES                **PeiServices, 
        EFI_CMOS_MANAGER_INTERFACE      *Manager );
    extern VOID CmosSynchronizeHobManagerStatus(
        IN EFI_CMOS_MANAGER_INTERFACE   *Manager );    
#endif


// DXE phase-specific declarations

#if !defined(PEI_COMPILE) && !defined(SMM_COMPILE)   
    extern EFI_STATUS InitializeCmosTablesFromHob(
        EFI_CMOS_MANAGER_INTERFACE  *Manager );
        
#endif


#ifdef PEI_COMPILE // PEI phase-specific globals
  EFI_GUID gCmosAccessGuid = EFI_PEI_CMOS_ACCESS_GUID;
  EFI_GUID gMemoryInstalledGuid = 
                        EFI_PEI_PERMANENT_MEMORY_INSTALLED_PPI;

#elif defined(SMM_COMPILE) // SMM-specific globals
  EFI_GUID gCmosAccessGuid = EFI_SMM_CMOS_ACCESS_GUID;

#else   // default is DXE phase-specific globals
  EFI_GUID  gCmosAccessGuid = EFI_DXE_CMOS_ACCESS_GUID;

#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerAllocatePool
//
// Description:
//      This function allocates memory for all boot phases.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  -- PEI Services table (NULL in DXE phase)
//      IN UINTN Size
//                  -- Number of bytes to allocate
//      OUT VOID **Buffer
//                  -- Pointer to buffer for which memory is allocated
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosManagerAllocatePool(
    IN EFI_PEI_SERVICES   **PeiServices,
    IN UINTN              Size,
    OUT VOID              **Buffer )
{
#ifdef PEI_COMPILE
    return (*PeiServices)->AllocatePool( PeiServices, 
            Size, Buffer);
#elif defined(SMM_COMPILE)
    return pSmst->SmmAllocatePool(0, Size, Buffer);
#else // DXE
    return pBS->AllocatePool( EfiBootServicesData, Size, Buffer);
#endif

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosGetMangerInterface
//
// Description:
//      Gets the EFI_CMOS_MANAGER_INTERFACE for the current access
//      interface.
//
// Input:
//      IN  EFI_CMOS_ACCESS_INTERFACE *Cmos
//                  -- This is the access interface pointer.
//
// Output:
//      EFI_CMOS_MANAGER_INTERFACE * (Return Value)
//                  -- If successful, the CMOS manager interface is returned.
//                  -- Otherwise, a valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_CMOS_MANAGER_INTERFACE *GetCmosMangerInterface(
    IN EFI_CMOS_ACCESS_INTERFACE   *Cmos )
{
    // The installed Protocol type will be EFI_CMOS_ACCESS_INTERFACE
    // (converted as needed by the CMOS manager)

    EFI_CMOS_MANAGER_INTERFACE *Interface = (EFI_CMOS_MANAGER_INTERFACE*) Cmos;
    return Interface;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetCmosAccessInterface
//
// Description:
//      Gets the EFI_CMOS_ACCESS_INTERFACE for the current manager
//      interface.
//
// Input:
//      IN  EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- This is the manager interface pointer.
//
// Output:
//      EFI_CMOS_ACCESS_INTERFACE * (Return Value)
//                  -- If successful, the CMOS access interface is returned.
//                  -- Otherwise, NULL is returned.
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_CMOS_ACCESS_INTERFACE *GetCmosAccessInterface(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager )
{
    EFI_CMOS_ACCESS_INTERFACE *Interface = NULL;
    
    // The installed Protocol type will be EFI_CMOS_ACCESS_INTERFACE
    // (converted as needed by the CMOS manager)
    if (Manager != NULL &&
        Manager->CheckStatus(Manager, CMOS_VALID_INTERFACE))
            Interface = (EFI_CMOS_ACCESS_INTERFACE*) Manager;
        
    return Interface;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerCheckStatus
//
// Description:
//      This function returns true if all the status bits are set as 
//      specified by the BitMap.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE   *Manager
//                  -- Pointer to the Manager's interface
//      IN CMOS_MANAGER_STATUS          BitMap 
//                  -- Bits to check
//
//
// Output:
//      BOOLEAN (Return value)
//               = TRUE, if all bits in ManagerStatus specified by 
//                 BitMap are set.
//
//               = FALSE, otherwise.
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CmosManagerCheckStatus(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap )
{
    if ((Manager->ManagerStatus & BitMap) == BitMap)
        return TRUE;
    else
        return FALSE;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerCheckAnyStatus
//
// Description:
//      This function returns true if any of the status bits are set as 
//      specified by the BitMap.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE   *Manager
//                  -- Pointer to the Manager's interface
//      IN CMOS_MANAGER_STATUS          BitMap 
//                  -- Bits to check
//
//
// Output:
//      BOOLEAN (Return value)
//               = TRUE, if one or more of the bits in ManagerStatus 
//                 specified by BitMap are set.
//
//               = FALSE, otherwise.
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN CmosManagerCheckAnyStatus(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap )
{
    if ((Manager->ManagerStatus & BitMap) != 0)
        return TRUE;
    else
        return FALSE;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerSetClearStatus
//
// Description:
//      This function provides a single entry point into the code that
//      actually updates status values.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//      IN CMOS_MANAGER_STATUS BitMap 
//                  -- Bits to set or clear
//      IN CMOS_BIT_ACCESS_TYPE AccessType
//                  -- SetType or ClearType depending upon whether
//                     setting or clearing bits
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CmosManagerSetClearStatus(
    IN EFI_CMOS_MANAGER_INTERFACE   *Mgr,
    IN CMOS_MANAGER_STATUS          BitMap,
    IN CMOS_BIT_ACCESS_TYPE         AccessType )
{
    if (AccessType == SetType){
        Mgr->ManagerStatus = Mgr->ManagerStatus | BitMap;

        // A boot/setup event callback explicitly clears these bits each boot

        if ( Mgr->CheckStatus(Mgr, CMOS_IS_USABLE) ){
            if ( BitMap & CMOS_BAD_BATTERY )
                Mgr->Access.Write(&Mgr->Access, CMOS_MGR_BATTERY_BAD, 1);
            if ( BitMap & CMOS_BAD_CHECKSUM )
                Mgr->Access.Write(&Mgr->Access, CMOS_MGR_CHECKSUM_BAD, 1);
            if ( BitMap & CMOS_DEFAULTS_LOADED )
                Mgr->Access.Write(&Mgr->Access, CMOS_MGR_DEFAULTS_LOADED, 1);
            if ( BitMap & CMOS_FIRST_BOOT_DETECTED )
                Mgr->Access.Write(&Mgr->Access, CMOS_MGR_FIRST_BOOT_DETECTED, 1);
        }

    }
    else
        Mgr->ManagerStatus = Mgr->ManagerStatus & ~BitMap;

#ifdef PEI_COMPILE  // In PEI, update ManagerStatus for DXE
    CmosSynchronizeHobManagerStatus(Mgr);
#endif

    // if the Checksum or Battery status is being modified, then 
    // update the legacy status registers
    if ( (BitMap & (CMOS_BAD_CHECKSUM | CMOS_BAD_BATTERY)) != 0  ){
        SynchronizeLegacyStatusRegisters(Mgr, BitMap, AccessType);
    }

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerSetStatus
//
// Description:
//      This function sets status bits according to the specified bitmap.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//      IN CMOS_MANAGER_STATUS BitMap 
//                  -- Bits to set
//
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CmosManagerSetStatus(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap )
{
    CmosManagerSetClearStatus(Manager, BitMap, SetType);
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerClearStatus
//
// Description:
//      This function clears status bits according to the specified bitmap.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//      IN CMOS_MANAGER_STATUS BitMap 
//                  -- Bits to clear
//
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CmosManagerClearStatus(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager,
    IN CMOS_MANAGER_STATUS          BitMap )
{
    CmosManagerSetClearStatus(Manager, BitMap, ClearType);
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosUpdateMemoryStatus
//
// Description:
//      This function is used in the PEI phase to set/clear the 
//      CMOS_EXECUTING_IN_MEMORY depending on whether or not the manager
//      is executing after permanent memory has been initialized.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef PEI_COMPILE
VOID CmosUpdateMemoryStatus (
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager )
{
    EFI_STATUS      Status = EFI_SUCCESS;
    VOID            *InterfacePtr;
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);
    
    CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, "CmosUpdateMemoryStatus Entry\n"));
    
    Status = (*PeiServices)->LocatePpi( PeiServices, &gMemoryInstalledGuid, 
                                        0, NULL, &InterfacePtr);
    if ( EFI_ERROR(Status) ) 
        Manager->ClearStatus(Manager, CMOS_EXECUTING_IN_MEMORY); 
    else
        Manager->SetStatus(Manager, CMOS_EXECUTING_IN_MEMORY); 

}
#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosConfigureManager
//
// Description:
//      This function configures the CMOS Manager.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Pointer to the Manager's interface
//      IN CMOS_CONFIGURATION_SETTING Setting
//                  -- Configuration setting to invoke.
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosConfigureManager(
    IN EFI_CMOS_MANAGER_INTERFACE   *Mgr,
    IN CMOS_CONFIGURATION_SETTING   Setting )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

#define Request(x) ((Setting & (x)) != 0)

    // Basic error checking

    if (    Request(CMOS_OPTIMAL_DEFAULTS_ON) 
         && Request(CMOS_OPTIMAL_DEFAULTS_OFF) )
    {
        return Status = EFI_INVALID_PARAMETER;
    }

    //-----------------------------------------------------------------------
    // CMOS_OPTIMAL_DEFAULTS_ON
    //-----------------------------------------------------------------------
    // If configuring usage of the optimal defaults buffer and it's already 
    // enabled, simply return.  Otherwise...
    //
    //  *  If executing in memory, enable the optimal defaults buffer
    //     and update the checksum.
    //  *  If not executing in memory, allocate the optimal defaults buffer,
    //     copy the values into it, and update the 
    //     Manager->OptimalDefaultTable pointer to point to the read/write
    //     buffer.
    //  *  Set the manager status bit to indicate usage of the optimal
    //     defaults buffer.

    if ( Request( CMOS_OPTIMAL_DEFAULTS_ON ) )
    {
        if (Mgr->CheckStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED))
            return EFI_SUCCESS;  // already configured
            
        // This will only occur in PEI phase!!

        if (!Mgr->CheckStatus(Mgr, CMOS_EXECUTING_IN_MEMORY)) {
            VOID *Temp;
            CmosManagerAllocatePool( PeiServices,
                Mgr->OptimalDefaultCount * sizeof(CMOS_REGISTER), 
                &Temp);
            MemCpy( Temp , Mgr->OptimalDefaultTable,
                Mgr->OptimalDefaultCount * sizeof(CMOS_REGISTER) );
            Mgr->OptimalDefaultTable = Temp;
        }
        
        Mgr->SetStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED);
        Mgr->CalculateChecksum(Mgr, &Mgr->Checksum);
        Mgr->WriteChecksum(Mgr, Mgr->Checksum);

    }
    
    //-----------------------------------------------------------------------
    // CMOS_OPTIMAL_DEFAULTS_OFF
    //-----------------------------------------------------------------------
    //
    // Clear the status bit, and let the Manager interface user must decide
    // what to do next ...call LoadOptimalDefaults, enable buffered CMOS 
    // mode, ....

    if ( Request( CMOS_OPTIMAL_DEFAULTS_OFF ) ){
        Mgr->ClearStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED);
    }

#undef Request

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: SaveApiPointerToCmos
//
// Description:
//      This function saves the specified pointer to a predefined 4-byte
//      CMOS location.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *CmosManager
//                  - Pointer to the manager's interface
//      IN EFI_CMOS_ACCESS_INTERFACE *ApiPointer
//                  - API address
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SaveApiPointerToCmos( 
    IN EFI_CMOS_MANAGER_INTERFACE      *Mgr,
    IN EFI_CMOS_ACCESS_INTERFACE       *ApiPointer )
{
    UINT32   Offset;
    UINT8    Byte;  // Only used in PEI
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    if (ApiPointer == NULL)
        ApiPointer = Mgr->GetAccessInterface(Mgr);

    if ( !Mgr->CheckAnyStatus(Mgr, CMOS_IS_USABLE ) ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "CMOS Not Usable: Could not save API pointer.\n"));
        return EFI_DEVICE_ERROR;
    }

    for (Offset = 0; Offset < 4; Offset++){
        Byte = (UINT8)((UINT32)ApiPointer >> (24 - (Offset * 8))) & 0xff;
        CmosPhysicalReadWrite(  Mgr, 
                                WriteType, 
                                CMOS_ACCESS_API_BYTE3 + Offset,
                                ALL_BITS, 
                                &Byte );
    }

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: GetApiPointerFromCmos
//
// Description:
//      This function get the CMOS API pointer from a predefined 4-byte
//      CMOS location and updates the output parameter with the pointer.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *CmosManager
//                  - Pointer to the manager's interface to be installed
//      OUT EFI_CMOS_ACCESS_INTERFACE **ApiPointer
//                  - Address of the API pointer
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS GetApiPointerFromCmos( 
    IN EFI_CMOS_MANAGER_INTERFACE   *Mgr,
    EFI_CMOS_ACCESS_INTERFACE       **ApiPointer )
{
    UINT8   Temp; 
    UINT32  Ptr = 0;
    UINT8   Offset;
    DEFINE_PEI_SERVICES(Mgr->Access.PeiServices);

    if ( !Mgr->CheckAnyStatus(Mgr, CMOS_IS_USABLE ) ){
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
            "CMOS Not Usable: Could not read API pointer.\n"));
        return EFI_DEVICE_ERROR;
    }

    for (Offset = 0; Offset < 4; Offset++){
        CmosPhysicalReadWrite(  Mgr, 
                                ReadType, 
                                CMOS_ACCESS_API_BYTE3 + Offset,
                                0, 
                                &Temp );
        Ptr =  (Ptr << 8) | Temp;
    }
        
    *ApiPointer = (EFI_CMOS_ACCESS_INTERFACE*) Ptr;

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InstallCmosAccessInterface
//
// Description:
//      This function installs either the PEI or DXE phase interface
//      (PPI or Protocol) for accessing CMOS.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE      *CmosManager
//                  - Pointer to the interface to be installed
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//      CmosManager->ManagerStatus 
//                  = CMOS_VALID_MANAGER indicates successful
//                    installation of interface.
//
// Notes:
//      This function is used for both PEI and DXE phase.  The build
//      macro PEI_COMPILE will determine how the object code is
//      created/linked.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS InstallCmosAccessInterface( 
    IN EFI_CMOS_MANAGER_INTERFACE      *CmosManager )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    EFI_HANDLE          Handle = 0;
    DEFINE_PEI_SERVICES(CmosManager->Access.PeiServices);

#ifdef PEI_COMPILE
    Status = (*PeiServices)->InstallPpi( 
            PeiServices, &CmosManager->Ppi[CMOS_ACCESS_PPI_TYPE]);
#else
    Status = pBS->InstallMultipleProtocolInterfaces(
            &Handle, &CmosManager->AccessGuid, CmosManager, NULL);
#endif

    if (!EFI_ERROR(Status)) 
        CmosManager->SetStatus(CmosManager, CMOS_VALID_MANAGER);
    else {
        CmosManager->SetStatus(CmosManager, CMOS_INSTALL_FAILED);
        CmosManager->ClearStatus(CmosManager, CMOS_VALID_MANAGER);
    }
    
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitializeCmosManagerInterface
//
// Description:
//      This function initializes structure data and function pointer  
//      elements for a EFI_CMOS_MANAGER_INTERFACE.  
//
// Input:
//      IN  EFI_PEI_SERVICES **PeiServices
//                  - This parameter will be NULL in the DXE phase
//      OUT EFI_CMOS_MANAGER_INTERFACE *CmosManager
//                  - Pointer to the interface to be initialized
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS or valid EFI error code
//      CmosManager->ManagerStatus 
//                  = CMOS_VALID_INTERFACE indicates successful
//                      initialization of the structure.
//
// Notes:
//      This function is used for both PEI and DXE phase.  The build
//      macro PEI_COMPILE will determine how the object code is
//      created.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>


EFI_STATUS InitializeCmosManagerInterface( 
    IN  EFI_PEI_SERVICES                **PeiServices,
    OUT EFI_CMOS_MANAGER_INTERFACE      *CmosManager )
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
        "InitializeCmosManagerInterface Entry\n"));

    // Note: all pointers/values are already NULL/Zero
    
    // Not using an initializer list in order to avoid problems
    // if/when the interface declarations are modified.

    //-----------------------------------------------------------------------
    // Phase-independent initialization
    //-----------------------------------------------------------------------
    CmosManager->AccessGuid = gCmosAccessGuid;
    CmosManager->Access.PeiServices = PeiServices;  // ensure NULL in DXE
    CmosManager->Access.Read = CmosRead;
    CmosManager->Access.Write = CmosWrite;
    CmosManager->Access.GetTokenFromRegister = CmosGetTokenFromRegister;
    CmosManager->Access.ReadCmosStatusBytes = ReadCmosStatusBytes;
    CmosManager->Access.GetTime = CmosGetDateTime;
    CmosManager->Access.SetTime = CmosSetDateTime;
    CmosManager->GetAccessInterface = GetCmosAccessInterface;
    CmosManager->InstallAccessInterface = InstallCmosAccessInterface;
    CmosManager->CalculateChecksum = CalculateChecksum;
    CmosManager->ReadChecksum = ReadChecksum;
    CmosManager->WriteChecksum = WriteChecksum;
    CmosManager->ConfigureManager = CmosConfigureManager;
    CmosManager->CheckStatus = CmosManagerCheckStatus;
    CmosManager->CheckAnyStatus = CmosManagerCheckAnyStatus;
    CmosManager->SetStatus = CmosManagerSetStatus;
    CmosManager->ClearStatus = CmosManagerClearStatus;
    CmosManager->LoadOptimalDefaults = LoadOptimalDefaults;
    CmosManager->SaveApiPointerToCmos = SaveApiPointerToCmos;
    CmosManager->GetApiPointerFromCmos = GetApiPointerFromCmos;
    
    //-----------------------------------------------------------------------
    // Phase-specific initialization
    //-----------------------------------------------------------------------
    // update the access PPI descriptor and CMOS data table pointers.
    //
    // Note:
    //        Before memory detection, the tables to which these pointers refer
    //        will reside in ROM.  At runtime, these tables will reside in
    //        SMRAM and boot updates will be copied into them.
    //-----------------------------------------------------------------------

#if defined(PEI_COMPILE) || defined(SMM_COMPILE)
    CmosManager->FirstManagedRegister = gFirstManagedRegister;
    CmosManager->LastManagedRegister = gLastManagedRegister;
    CmosManager->TokenTable = (CMOS_TOKEN*) gCmosTokenTable; 
    CmosManager->TokenCount = gCmosTokenTableSize;
    CmosManager->NoChecksumTable = (CMOS_REGISTER*) gCmosNoCheckSumTable;
    CmosManager->NoChecksumCount = gCmosNoCheckSumTableSize;
    CmosManager->UnmanagedTable = (CMOS_REGISTER*) gUnmanagedTable;
    CmosManager->UnmanagedTableCount = gUnmanagedTableSize;
    CmosManager->OptimalDefaultTable = 
        (CMOS_REGISTER*) gCmosOptimalDefaultTable;
    CmosManager->OptimalDefaultCount = gCmosOptimalDefaultTableSize;
#endif

#if defined(PEI_COMPILE)
    CmosManager->Ppi[CMOS_ACCESS_PPI_TYPE].Flags = 
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    CmosManager->Ppi[CMOS_ACCESS_PPI_TYPE].Guid = &gCmosAccessGuid;
    CmosManager->Ppi[CMOS_ACCESS_PPI_TYPE].Ppi = (VOID*)CmosManager;
#endif
   
    CmosManager->SetStatus(CmosManager, CMOS_VALID_INTERFACE);
  
    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: NewCmosManagerInterface
//
// Description:
//      This function locates (or allocates memory for) the
//      EFI_CMOS_MANAGER_INTERFACE, calculates the checksum, checks the
//      battery condition and updates the Manager's status bits.  
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  - This parameter will be NULL in the DXE phase
//
// Output:
//      EFI_CMOS_MANAGER_INTERFACE* (Return Value)
//                  =  If successful, a pointer to the allocated/found
//                     structure is returned.
//                  =  NULL is returned on failure to allocate
//
//      NewManager->ManagerStatus
//                  =  CMOS_INTERFACE_ALREADY_INSTALLED, if the interface is 
//                     found prior to allocating
//                  =  CMOS_VALID_INTERFACE, on successful initialization
//                     of the access interface.
//
// Notes:
//      This function is used for PEI, DXE and SMM interface initialization.  
//      The build macros PEI_COMPILE and SMM_COMPILE will determine how the 
//      object code is compiled.
//
//      See CMOS_MANAGER_STATUS enum type for more information on manager 
//      status bits.
//
//      Assumptions: 
//
//               1) This function should only be called once for each 
//                  entrypoint.
//
//               2) It is up to the user of the Manager interface to determine
//                  how to use the CMOS_MANAGER_STATUS bits upon return from
//                  this function.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_CMOS_MANAGER_INTERFACE* NewCmosManagerInterface( 
    IN EFI_PEI_SERVICES        **PeiServices )
{
    EFI_CMOS_MANAGER_INTERFACE    *NewManager;
    EFI_STATUS                    Status;
    
    //-----------------------------------------------------------------------
    // If the interface is found then no initialization is done.
    //-----------------------------------------------------------------------

#ifdef PEI_COMPILE
    LOCATE_CMOS_ACCESS_PPI(Status, NewManager);
#elif defined (SMM_COMPILE)
    LOCATE_CMOS_ACCESS_SMM_PROTOCOL(Status, NewManager)
#else
    LOCATE_CMOS_ACCESS_PROTOCOL(Status, NewManager)
#endif    
    if (Status == EFI_SUCCESS)
    { 
        NewManager->SetStatus(NewManager, CMOS_INTERFACE_ALREADY_INSTALLED);
        return NewManager;
    }
    
    //-----------------------------------------------------------------------
    // Return NULL on allocation error.
    //-----------------------------------------------------------------------

    if (EFI_ERROR(CmosManagerAllocatePool( PeiServices, 
                                           sizeof(EFI_CMOS_MANAGER_INTERFACE),
                                           (VOID**)&NewManager ) )){
        return NULL;
    }

    //-----------------------------------------------------------------------
    // Zero the interface buffer (also ensures ManagerStatus bits are clear 
    // and ensures pointers are NULL)
    //-----------------------------------------------------------------------

    MemSet( (void*)NewManager, sizeof(EFI_CMOS_MANAGER_INTERFACE), 0);
    
    //-----------------------------------------------------------------------
    // Initialize general structures and function pointers
    //-----------------------------------------------------------------------

    InitializeCmosManagerInterface(PeiServices, NewManager);

    //-----------------------------------------------------------------------
    // Initialize pointers to/from data structures in the HOB or DXE Buffer
    // updates
    //-----------------------------------------------------------------------
    // In PEI phase: 
    //      1.  Update memory status
    //
    // In DXE phase: 
    //      1.  Get the HOB and complete the initialization of the Manager 
    //          interface data structure pointers.
    //
    // In SMM registration: 
    //      1.  Use the original optimal defaults buffer, as the DXE buffer
    //          has already by flushed to the physical registers if the battery
    //          is good.  (If the battery is bad, it is unlikely CMOS is of
    //          any use in SMM.)

#ifdef PEI_COMPILE
    CmosUpdateMemoryStatus( NewManager );
#elif !defined(SMM_COMPILE)
    if (EFI_ERROR( InitializeCmosTablesFromHob(NewManager) ))
        return NULL;
#endif

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Call CmosIsUsable: " ));
    if ( gCmosIsUsable( NewManager->Access.PeiServices ) ){
        NewManager->SetStatus(NewManager, CMOS_IS_USABLE);
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CMOS is usable\n" ));
    }
    else {
        NewManager->ClearStatus(NewManager, CMOS_IS_USABLE);
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CMOS is not usable\n" ));
    }

    //-----------------------------------------------------------------------
    // Update CMOS_FIRST_BOOT_DETECTED status bit before calculating
    // the checksum or determining the battery status.
    //-----------------------------------------------------------------------

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Call gIsFirstBoot: " ));
    if ( gIsFirstBoot( NewManager->Access.PeiServices ) ){
        NewManager->SetStatus(NewManager, CMOS_FIRST_BOOT_DETECTED);
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "First boot detected\n" ));
    }
    else {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "First boot NOT detected\n" ));
    }

    // Update CMOS_COLD_BOOT_DETECTED status bit.

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Call gIsColdBoot: " ));
    if ( gIsColdBoot( NewManager->Access.PeiServices ) ){
        NewManager->SetStatus(NewManager, CMOS_COLD_BOOT_DETECTED);
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Cold boot detected\n" ));
    }
    else {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Cold boot NOT detected\n" ));
    }

    // Update CMOS_BSP_IS_EXECUTING status bit.

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Call gIsBsp: " ));
    if ( gIsBsp( NewManager->Access.PeiServices ) ){
        NewManager->SetStatus(NewManager, CMOS_BSP_IS_EXECUTING);
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "BSP is executing\n" ));
    }
    else {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "BSP is NOT executing\n" ));
    }

    // Configure incoherency recovery policy

#if CMOS_MGR_RECOVER_ONLY_CHECKUMMED
    NewManager->SetStatus(NewManager, CMOS_RECOVER_ONLY_CHECKSUMMED);
#endif

#if CMOS_MGR_RECOVER_IN_PEI
    NewManager->SetStatus(NewManager, CMOS_RECOVER_IN_PEI);
#endif


    //-----------------------------------------------------------------------
    // Update the NewManager->Checksum
    //
    // Note: This call only calculates and updates the checksum in
    //       the manager interface structure.  The CMOS_BAD_CHECKSUM bit
    //       is set in NewManager->ManagerStatus, if the calculated checksum 
    //       does not match the current checksum in CMOS.
    //
    //       The user of the Manager interface will decide how to handle
    //       a bad checksum.
    //-----------------------------------------------------------------------

    NewManager->CalculateChecksum(NewManager, &NewManager->Checksum);
    
    UpdateBatteryStatus(NewManager);

    return NewManager;
}



//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
