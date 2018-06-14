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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS PEI/CmosManagerPei.c 17    6/15/10 2:23p Michaela $
//
// $Revision: 17 $
//
// $Date: 6/15/10 2:23p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS PEI/CmosManagerPei.c $
// 
// 17    6/15/10 2:23p Michaela
// 
// 16    3/05/10 4:53p Michaela
// 
// 15    12/04/09 7:30p Michaela
// 
// 14    12/03/09 6:19p Michaela
// 1. CMOS_BSP_IS_EXECUTING status bit 
//    is used instead of gIsBsp
// 
// 2. Loading of Optimal Defaults on bad checksum
//    is done earlier by default and is enabled/disabled
//    by CMOS_RECOVER_IN_PEI SDL token.
//    
//    Note: the bad checksum bit is not cleared until DXE.
//    
// 3. The CMOS_USE_OPTIMAL_DEFAULTS enum is replaced with
//    CMOS_OPTIMAL_DEFAULTS_ON.
// 
// 13    11/10/09 9:13p Michaela
// 
// 12    7/29/09 9:56a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 11    6/15/09 5:10p Michaela
// 
// 10    6/02/09 4:38p Michaela
// 
// 9     6/02/09 3:26p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 8     3/11/09 3:37p Michaela
// 
// 7     11/25/08 3:15p Michaela
// Updates for Label 4.6.3_CMOSMGR_08
// - Assembly macro fixes
// - Added assembly macros
// - Moved loading defaults into DXE phase
// - Updated help file example
// 
// 6     11/17/08 4:03p Michaela
// --Removed development degugging code
// 
// 5     11/07/08 5:14p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 4     3/07/08 4:06p Michaela
// Label 4.6.3_CMOSMGR_05 fixes:
// -- write errors to Optimal Defaults buffer before memory detection
// -- CMOS Token table corruption when name strings are disabled
// 
// 3     2/29/08 9:33p Michaela
// - Added recovery path policy
// - fixed other minor bugs
// 
// 2     2/26/08 12:52p Michaela
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
// Name:    CmosManagerPei.c
//
// Description:     Contains the routines that constitute the CMOS manager's
//                  PEI phase entry.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <Token.h>
#include "CmosManagerPei.h"

#define LOCATE_READ_ONLY_VARIABLE_PPI(Status, InterfacePtr) { \
    EFI_GUID Guid = EFI_PEI_READ_ONLY_VARIABLE_PPI_GUID; \
    Status = (*PeiServices)->LocatePpi( PeiServices, &Guid, \
        0, NULL, &InterfacePtr); }
        

//---------------------------------------------------------------------------
//  PEI entry point function
//
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerPeiEntry
//
// Description:
//      This function is the main PEI phase entry point for the CMOS
//      manager module.
//
// Input:
//      IN EFI_FFS_FILE_HEADER *FfsHeader
//                  -- FFS file header pointer
//      IN EFI_PEI_SERVICES **PeiServices
//                  -- PEI Services table pointer
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//      Execution Sequence:
//                  1)  Initialize CMOS Manager interface
//                  2)  Load default values into CMOS registers if
//                      this is the first boot.
//                  3)  Configure usage of the Optimal Defaults table if
//                      the battery or checksum is bad.
//                  4)  Update the CMOS-based API/PPI pointer.
//                  5)  Install the EFI_CMOS_ACCESS_INTERFACE PPI
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosManagerPeiEntry (
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices )
{
    EFI_STATUS                  Status;
    EFI_CMOS_MANAGER_INTERFACE  *Mgr;
    UINT8                       CmosValue = 0;


    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CmosManagerPeiEntry Entry\n" ));

    //-----------------------------------------------------------------------
    // Initialize the manager interface and, at this point, only check for  
    // interface initialization errors.
    //-----------------------------------------------------------------------

    Mgr = NewCmosManagerInterface(PeiServices);
    if ( Mgr == NULL || !Mgr->CheckStatus(Mgr, CMOS_VALID_INTERFACE) )
        return  Status = EFI_UNSUPPORTED;
    if ( Mgr->CheckStatus( Mgr, CMOS_INTERFACE_ALREADY_INSTALLED) )
        return  Status = EFI_SUCCESS;
    
    //-----------------------------------------------------------------------
    // Handle specific internally-reported conditions.
    //-----------------------------------------------------------------------

    if (    Mgr->CheckStatus(Mgr, CMOS_IS_USABLE )
         && Mgr->CheckStatus(Mgr, CMOS_BSP_IS_EXECUTING ) )
    {
        // Load optimal defaults on first boot after programming
        // boot device.

        if  (    Mgr->CheckStatus(Mgr, CMOS_FIRST_BOOT_DETECTED )
              && Mgr->CheckStatus(Mgr, CMOS_COLD_BOOT_DETECTED )  )
        {
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "First boot detected ...\n" ));
            Mgr->LoadOptimalDefaults(Mgr);
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "...Defaults loaded\n" ));
        }

        // Save CMOS-based PPI pointer

        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Saving PPI pointer to CMOS\n" ));
        Mgr->SaveApiPointerToCmos(Mgr, NULL);
    }
    else {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Defaults were not loaded\n" ));
    }

    //-----------------------------------------------------------------------
    // If the CMOS hardware is not usable, configure CMOS Manager to use the
    // read/write Optimal Defaults buffer for Managed Region access. 
    //-----------------------------------------------------------------------

    if ( Mgr->CheckAnyStatus( Mgr, CMOS_BAD_CHECKSUM | CMOS_BAD_BATTERY ) ){
        if ( Mgr->CheckStatus( Mgr, CMOS_BAD_CHECKSUM) )
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "Bad Checksum:\n" ));

        if ( Mgr->CheckStatus( Mgr, CMOS_BAD_BATTERY) )
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "Bad Battery:\n" ));

        if (    Mgr->CheckStatus(Mgr, CMOS_IS_USABLE )
             && Mgr->CheckStatus(Mgr, CMOS_RECOVER_IN_PEI ) )
        {
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "  Loading Optimal Defaults\n"));
            Mgr->LoadOptimalDefaults( Mgr );
            Mgr->ConfigureManager( Mgr, CMOS_OPTIMAL_DEFAULTS_OFF );
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "...Defaults loaded\n" ));
        }
        else {
            CMOS_TRACE((CMOS_TRACE_ALWAYS, "  Using Optimal Defaults.\n"));
            Mgr->ConfigureManager( Mgr, CMOS_OPTIMAL_DEFAULTS_ON );
        }

    }    

   
    //-----------------------------------------------------------------------
    // Install the CMOS Access PPI
    //-----------------------------------------------------------------------

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "Installing CMOS Access PPI\n" ));
    Mgr->InstallAccessInterface(Mgr);
    if ( !Mgr->CheckStatus(Mgr, CMOS_VALID_MANAGER ) ){
        CMOS_TRACE((CMOS_TRACE_ALWAYS, 
            "Invalid interface ... Access PPI not installed\n" ));
        return Status = EFI_UNSUPPORTED;
    }


    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "CmosManagerPeiEntry successful exit\n" ));

    return Status = EFI_SUCCESS;
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
