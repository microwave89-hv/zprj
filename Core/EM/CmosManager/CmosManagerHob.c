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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Source/CmosManagerHob.c 13    6/15/10 2:24p Michaela $
//
// $Revision: 13 $
//
// $Date: 6/15/10 2:24p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Source/CmosManagerHob.c $
// 
// 13    6/15/10 2:24p Michaela
// 
// 12    12/04/09 7:32p Michaela
// 
// 11    12/03/09 6:43p Michaela
// changed CmosManagerAfterMemoryEntry() to update
// the PEI Services table earlier.
// 
// 10    7/29/09 9:59a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 9     6/15/09 5:11p Michaela
// 
// 8     6/02/09 3:27p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 7     11/17/08 3:42p Michaela
// --Removed development debugging code
// --ABORT_ERROR macro replaced with EFI_ERROR macro usage
// 
// 6     11/07/08 5:13p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 5     3/07/08 4:07p Michaela
// Label 4.6.3_CMOSMGR_05 fixes:
// -- write errors to Optimal Defaults buffer before memory detection
// -- CMOS Token table corruption when name strings are disabled
// 
// 4     2/29/08 9:35p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 3     2/26/08 12:49p Michaela
// Added/modified Helpbuilder headers
// 
// 2     2/22/08 5:08p Michaela
// update EFI_PEI_SERVICES pointer on ppi callback
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
// Name:    CmosManagerHob.c
//
// Description: Contains the routines that are used to access the 
//              HOB data structure.
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
#include "CmosManager.h"
#include "CmosManagerHob.h"

#ifdef PEI_COMPILE

    //-----------------------------------------------------------------------
    // Data originally defined in CmosTables.c
    //-----------------------------------------------------------------------

    extern CMOS_TOKEN  gCmosTokenTable[];
    extern UINT16 gCmosTokenTableSize;
    extern CMOS_REGISTER  gCmosOptimalDefaultTable[];
    extern UINT16 gCmosOptimalDefaultTableSize;
    extern CMOS_REGISTER  gCmosNoCheckSumTable[];
    extern UINT16 gCmosNoCheckSumTableSize;
    extern CMOS_REGISTER gUnmanagedTable[];
    extern UINT16 gUnmanagedTableSize;

    EFI_GUID gCmosDataHobInstalledGuid = 
                            EFI_CMOS_DATA_HOB_INSTALLED_GUID;
#endif

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosSynchronizeHobManagerStatus
//
// Description:
//      This function synchronizes the ManagerStatus information in
//      the CMOS data HOB to be passed to DXE.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE   *Manager
//                  -- Manager interface pointer
//
// Output:
//      VOID (Return value)
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef PEI_COMPILE
VOID CmosSynchronizeHobManagerStatus(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager )
{
    if (Manager->ManagerHob != NULL)
        Manager->ManagerHob->ManagerStatus = Manager->ManagerStatus;
}
#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosSynchronizeHobChecksum
//
// Description:
//      This function synchronizes the Checksum information in
//      the CMOS data HOB to be passed to DXE.
//
// Input:
//      OUT EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manager->ManagerHob->CheckSum = Manager->CheckSum
//
// Output:
//      VOID (Return value)
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef PEI_COMPILE
VOID CmosSynchronizeHobChecksum(
    OUT EFI_CMOS_MANAGER_INTERFACE   *Manager )
{
    if (Manager->ManagerHob != NULL)
        Manager->ManagerHob->Checksum = Manager->Checksum;

}
#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CreateCmosDataHob
//
// Description:
//      This function creates the CMOS data HOB, when memory is available.
//
// Input:
//      IN EFI_CMOS_MANAGER_INTERFACE *Manager
//                  -- Manager interface pointer
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      This function is used only in PEI phase, included by the build
//      macro PEI_COMPILE.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef PEI_COMPILE
EFI_STATUS CreateCmosDataHob(
    IN EFI_CMOS_MANAGER_INTERFACE   *Manager )
{
    UINT16              TokenIndex = 0; // First valid token table index is 1
    EFI_STATUS          Status;
    UINT16              HobSize = sizeof(CMOS_MANAGER_HOB);
    EFI_GUID            CmosManagerHobGuid = CMOS_MANAGER_HOB_GUID;
    CMOS_MANAGER_HOB    *CmosManagerHob;
    DEFINE_PEI_SERVICES(Manager->Access.PeiServices);

    Status = (*PeiServices)->CreateHob( PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        HobSize,
                                        &CmosManagerHob);
                                          
    CmosManagerHob->Header.Name = CmosManagerHobGuid;
    CmosManagerHob->FirstManagedRegister = Manager->FirstManagedRegister;
    CmosManagerHob->LastManagedRegister = Manager->LastManagedRegister;
    CmosManagerHob->TokenCount = Manager->TokenCount;
    CmosManagerHob->OptimalDefaultCount = Manager->OptimalDefaultCount;
    CmosManagerHob->NoChecksumCount = Manager->NoChecksumCount;
    CmosManagerHob->UnmanagedTableCount = Manager->UnmanagedTableCount;
    CmosManagerHob->Checksum = Manager->Checksum;
    CmosManagerHob->ManagerStatus = Manager->ManagerStatus;
    Manager->ManagerHob = CmosManagerHob;

    // Use a raw copy to initialize the tables in the HOB 
    // from global arrays 

    if ( EFI_ERROR(Status) ) 
        return Status;
    else {
        MemCpy( CmosManagerHob->TokenTable,
                Manager->TokenTable,
                Manager->TokenCount * sizeof(CMOS_TOKEN)
        );
        MemCpy( CmosManagerHob->OptimalDefaultTable ,
                Manager->OptimalDefaultTable,
                Manager->OptimalDefaultCount * sizeof(CMOS_REGISTER)
        );
        MemCpy( CmosManagerHob->NoChecksumTable ,
                Manager->NoChecksumTable,
                Manager->NoChecksumCount * sizeof(CMOS_REGISTER)
        );
        MemCpy( CmosManagerHob->UnmanagedTable ,
                Manager->UnmanagedTable,
                Manager->UnmanagedTableCount * sizeof(CMOS_REGISTER)
        );
    }

    //-----------------------------------------------------------------------
    // The Manager will now use the HOB versions of the tables for
    // faster access and to ensure proper updating of the optimal defaults 
    // buffer.
    //-----------------------------------------------------------------------

    Manager->TokenTable = CmosManagerHob->TokenTable;
    Manager->OptimalDefaultTable = CmosManagerHob->OptimalDefaultTable;
    Manager->NoChecksumTable = CmosManagerHob->NoChecksumTable;
    Manager->UnmanagedTable = CmosManagerHob->UnmanagedTable;

    //-----------------------------------------------------------------------
    // Install a notification PPI to inform that the CMOS data HOB is 
    // installed.
    //
    // Note:    The current routine is executed from within a notification, 
    //          so any PPI waiting on the install notification PPI must 
    //          use the EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK Flag.
    //-----------------------------------------------------------------------

    Manager->Ppi[CMOS_DATA_HOB_INSTALLED_PPI_TYPE].Flags = 
        EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    Manager->Ppi[CMOS_DATA_HOB_INSTALLED_PPI_TYPE].Guid = 
        &gCmosDataHobInstalledGuid;
    Manager->Ppi[CMOS_DATA_HOB_INSTALLED_PPI_TYPE].Ppi = NULL;
    Status = (*PeiServices)->InstallPpi( 
            PeiServices, &Manager->Ppi[CMOS_DATA_HOB_INSTALLED_PPI_TYPE]);
    
    return Status;
}
#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerAfterMemoryEntry
//
// Description:
//      This function calls CreateCmosDataHob to create the DXE data HOB
//      after permanent memory has been installed, and updates the new CMOS 
//      Access Interface Address, as well as the CMOS-based API pointer.
//
// Input:
//      IN EFI_FFS_FILE_HEADER *FfsHeader
//                  -- EFI_FFS_FILE_HEADER pointer
//      IN EFI_PEI_SERVICES **PeiServices
//                  -- PEI Services table pointer
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      This function is used only in PEI phase, included by the build
//      macro PEI_COMPILE.
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifdef PEI_COMPILE
EFI_STATUS CmosManagerAfterMemoryEntry (
	IN EFI_FFS_FILE_HEADER       *FfsHeader,
	IN EFI_PEI_SERVICES          **PeiServices )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_CMOS_ACCESS_INTERFACE   *Cmos;
    EFI_CMOS_MANAGER_INTERFACE  *Manager;
    
    extern EFI_CMOS_MANAGER_INTERFACE *GetCmosMangerInterface(
        IN EFI_CMOS_ACCESS_INTERFACE   *Cmos );

    LOCATE_CMOS_ACCESS_PPI(Status, Cmos);       // get Manager's interface
    if (EFI_ERROR(Status))
        return Status;

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CmosManagerAfterMemoryEntry...\n" ));

    Manager = GetCmosMangerInterface(Cmos);
    
    // Update PeiServices first

    Manager->Access.PeiServices = PeiServices;

    // Update the API pointer in CMOS

    Manager->SaveApiPointerToCmos(Manager, Cmos);
    
    // Indicate that manager is now executing in memory

    Manager->SetStatus(Manager, CMOS_EXECUTING_IN_MEMORY);

    // Create the HOB

    CreateCmosDataHob(Manager);
    
    return Status;
}
#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: InitializeCmosDataTablesFromHob
//
// Description:
//      This function locates the HOB containing the table of CMOS tokens
//      and initializes token table information in the CMOS manager's
//      interface.
//
// Input:
//      OUT EFI_CMOS_MANAGER_INTERFACE  *Manager
//                  - The CMOS manager interface to initialize.
//
// Output:
//      EFI_STATUS (Return value)
//                  = EFI_SUCCESS or valid EFI error code
//
// Notes:
//      This function is used only in DXE phase, included by the build
//      process via the absence of the macro PEI_COMPILE.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#ifndef PEI_COMPILE
EFI_STATUS InitializeCmosTablesFromHob(
    OUT EFI_CMOS_MANAGER_INTERFACE  *Manager )
{
    EFI_STATUS          Status;
    EFI_GUID            HobListGuid = HOB_LIST_GUID;
    EFI_GUID            CmosManagerHobGuid = CMOS_MANAGER_HOB_GUID;
    CMOS_MANAGER_HOB    *CmosManagerHob;

    CmosManagerHob = 
        (CMOS_MANAGER_HOB*)GetEfiConfigurationTable(pST,&HobListGuid);
    if ( CmosManagerHob == NULL )
        return Status = EFI_UNSUPPORTED;

    Status = FindNextHobByGuid( &CmosManagerHobGuid, (VOID**)&CmosManagerHob);
    if (EFI_ERROR( Status ))
        return Status;
 
    Manager->ManagerHob = CmosManagerHob;      // for completeness
    Manager->FirstManagedRegister = CmosManagerHob->FirstManagedRegister;
    Manager->LastManagedRegister = CmosManagerHob->LastManagedRegister;
    Manager->TokenTable = CmosManagerHob->TokenTable;
    Manager->TokenCount = CmosManagerHob->TokenCount;
    Manager->OptimalDefaultTable = CmosManagerHob->OptimalDefaultTable;
    Manager->OptimalDefaultCount = CmosManagerHob->OptimalDefaultCount;
    Manager->NoChecksumTable = CmosManagerHob->NoChecksumTable;
    Manager->NoChecksumCount = CmosManagerHob->NoChecksumCount;
    Manager->UnmanagedTable = CmosManagerHob->UnmanagedTable;
    Manager->UnmanagedTableCount = CmosManagerHob->UnmanagedTableCount;
    Manager->Checksum = CmosManagerHob->Checksum;
    Manager->ManagerStatus = CmosManagerHob->ManagerStatus;
    
    return Status = EFI_SUCCESS;
}
#endif


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
