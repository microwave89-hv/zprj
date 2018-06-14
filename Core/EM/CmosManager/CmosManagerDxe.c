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
// $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS DXE/CmosManagerDxe.c 16    6/15/10 2:24p Michaela $
//
// $Revision: 16 $
//
// $Date: 6/15/10 2:24p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS DXE/CmosManagerDxe.c $
// 
// 16    6/15/10 2:24p Michaela
// 
// 15    3/05/10 4:54p Michaela
// 
// 14    12/04/09 7:31p Michaela
// 
// 13    12/03/09 6:22p Michaela
// 1. CMOS_DISCONTINUE_OPTIMAL_DEFAULTS is replace with
//    CMOS_OPTIMAL_DEFAULTS_OFF.
// 
// 2. Loading of Optimal Defaults depends only on
//    wether or not the buffer is enabled.
// 
// 12    11/10/09 9:13p Michaela
// 
// 11    7/29/09 9:56a Michaela
// updates Aptio Enhancement EIP 22205
// (no code changes)
// 
// 10    6/15/09 5:11p Michaela
// 
// 9     6/02/09 3:26p Michaela
// For label: 4.6.3_CMOSMGR_11
// 
// 8     3/11/09 3:39p Michaela
// 
// 7     11/25/08 3:15p Michaela
// Updates for Label 4.6.3_CMOSMGR_08
// - Assembly macro fixes
// - Added assembly macros
// - Moved loading defaults into DXE phase
// - Updated help file example
// 
// 6     11/17/08 4:05p Michaela
// --Removed development debugging code
// 
// 5     11/07/08 5:15p Michaela
// Updated to make CMOS manager available in all phases 
// of the boot process:
// 
// A CMOS API Pointer is maintained in CMOS and accessible
// via provided macros in C and assembly source.
// 
// 4     3/07/08 4:05p Michaela
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
// Name:    CmosManagerDxe.c
//
// Description: Contains the routines that constitute the CMOS manager's
//              DXE phase entry.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "CmosManagerDxe.h"
#include <Protocol\Reset.h>
#include <Setup.h>

static EFI_EVENT  gSetupEnterEvent;
static EFI_EVENT  gBootEvent;


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: ClearCmosBasedStatus
//
// Description:
//      This function uses the CMOS Manager interface to clear the un-managed
//      private status bits upon boot or setup entry.
//
// Input:
//      IN EFI_EVENT Event
//                  - Event handle
//      IN VOID *Context
//                  - Not used
//
// Output:
//      None
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ClearCmosBasedStatus(
    IN EFI_EVENT    Event,
    IN VOID         *Context )
{
    EFI_CMOS_ACCESS_INTERFACE   *Cmos;
    EFI_STATUS                  Status;
    CMOS_STATUS_BYTES           CmosInfo;
    BOOLEAN                     Usable;

    LOCATE_CMOS_ACCESS_PROTOCOL(Status, Cmos);

    if ( !EFI_ERROR(Status) ){

        // get CMOS-based info
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                            "Clear CMOS-based status values.\n" ));

        Cmos->ReadCmosStatusBytes(Cmos, &CmosInfo);
        Usable = CmosInfo.ConfigurationStatus.NotUsable == 1 ? FALSE : TRUE;

        // clear status values for next boot

        if ( Usable ){
            Cmos->Write(Cmos, CMOS_MGR_BATTERY_BAD,         0);
            Cmos->Write(Cmos, CMOS_MGR_CHECKSUM_BAD,        0);
            Cmos->Write(Cmos, CMOS_MGR_DEFAULTS_LOADED,     0);
            Cmos->Write(Cmos, CMOS_MGR_FIRST_BOOT_DETECTED, 0);
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "...Done\n" ));
        }

    }
    else
        CMOS_TRACE((CMOS_TRACE_ALWAYS, "ClearCmosBasedStatus...Failed\n" ));


    // This function only needs to be called one time to 
    // get proper updates in setup and to clear the CMOS values.

#if CMOS_SETUP_SUPPORT
    pBS->CloseEvent(gSetupEnterEvent);
#endif
    pBS->CloseEvent(gBootEvent);

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: UpdateCmosSetupVariable
//
// Description:
//      This function updates the CMOS setup variable using information
//      from the CMOS-based status bits.
//
// Input:
//      IN EFI_EVENT Event
//                  - Event handle
//      IN VOID *Context
//                  - Not used
//
// Output:
//      None
//
// Notes:
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

#if CMOS_SETUP_SUPPORT
VOID UpdateCmosSetupVariable(
    IN EFI_EVENT    Event,
    IN VOID         *Context )
{
    EFI_CMOS_ACCESS_INTERFACE   *Cmos;
    EFI_STATUS                  Status;
    CMOS_STATUS_BYTES           CmosInfo;
    EFI_GUID                    SetupGuid = SETUP_GUID;
    UINTN                       VariableSize = sizeof(SETUP_DATA);
    UINT32                      Attributes;
    SETUP_DATA                  Sd;
    EFI_GUID                    CmosGuid = EFI_DXE_CMOS_ACCESS_GUID;
    BOOLEAN                     NotUsable;
    BOOLEAN                     BadBattery;
    BOOLEAN                     DefaultsLoaded;
    BOOLEAN                     FirstBoot;
    BOOLEAN                     BadChecksum;

    CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
                      "Locate CMOS Manager interface...\n" ));
    Status = pBS->LocateProtocol( &CmosGuid, NULL, &Cmos);
    if (!EFI_ERROR (Status)) {
        Status = Cmos->ReadCmosStatusBytes(Cmos, &CmosInfo);
        if (EFI_ERROR(Status)){
            ASSERT_EFI_ERROR(EFI_NOT_FOUND);
            return;
        }
        NotUsable = (BOOLEAN)CmosInfo.ConfigurationStatus.NotUsable;
    }
    else {
        ASSERT_EFI_ERROR(Status);
        return;        
    }

    // update setup data

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                        "Updating setup data.\n" ));
    Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attributes, 
                               &VariableSize, &Sd );
    if (EFI_ERROR(Status)){
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                        "Could not locate Setup variable.\n" ));
    }
    else {
        if ( NotUsable ) {
            CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
                        "  Status: Cannot use CMOS-based status\n"));
            Sd.CmosBatteryIsBad = CmosInfo.Battery.Field.IsGood == 0 ? 
                                      TRUE : FALSE;
            Sd.CmosNotUsable = TRUE;
        }
        else {
            Cmos->Read(Cmos, CMOS_MGR_BATTERY_BAD,         &BadBattery);
            Cmos->Read(Cmos, CMOS_MGR_CHECKSUM_BAD,        &BadChecksum);
            Cmos->Read(Cmos, CMOS_MGR_DEFAULTS_LOADED,     &DefaultsLoaded);
            Cmos->Read(Cmos, CMOS_MGR_FIRST_BOOT_DETECTED, &FirstBoot);

            Sd.CmosDefaultsLoaded = DefaultsLoaded;
            Sd.CmosFirstBootDetected = FirstBoot;
            Sd.CmosBatteryIsBad = BadBattery;
            Sd.CmosCheckSumIsBad = BadChecksum;
            Sd.CmosNotUsable = FALSE;
        }
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
                "  Status: DefaultsLoaded=%X, FirstBoot=%X, BatteryBad=%X\n",
                Sd.CmosDefaultsLoaded, Sd.CmosFirstBootDetected,
                Sd.CmosBatteryIsBad ));
        CMOS_TRACE_FULL(( CMOS_TRACE_ALWAYS, 
                "          BadChecksum=%X, CmosNotUsable=%X\n",
                Sd.CmosCheckSumIsBad, Sd.CmosNotUsable ));
        Status = pRS->SetVariable( L"Setup", &SetupGuid, Attributes, 
                                   VariableSize, &Sd );
    }

    // Clear the CMOS-based status bits after updating the setup variable

    ClearCmosBasedStatus(Event, Context);

    return;
}
#endif


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CreateEventHandlers
//
// Description:
//      This function creates a callback on the setup entry event and boot 
//      event to (respectively) update the CMOS setup variable and clear
//      the CMOS-based status bits.
//
// Input:
//      None
//
// Output:
//      None
//
// Notes:
//      None
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID CreateEventHandlers( VOID )
{
    EFI_STATUS  Status;

#if CMOS_SETUP_SUPPORT
    EFI_GUID    SetupEnterProtocolGuid = AMITSE_SETUP_ENTER_GUID;
    VOID        *Registration;

    Status = RegisterProtocolCallback( &SetupEnterProtocolGuid, 
        UpdateCmosSetupVariable, NULL, &gSetupEnterEvent, &Registration );
    ASSERT_EFI_ERROR(Status);
#endif

    Status = CreateReadyToBootEvent( TPL_CALLBACK, ClearCmosBasedStatus, NULL, 
        &gBootEvent );
    ASSERT_EFI_ERROR(Status);


}

//---------------------------------------------------------------------------
//  DXE entry point function
//
//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure: CmosManagerDxeEntry
//
// Description:
//      This function is the main DXE phase entry point for the CMOS
//      manager module.
//
// Input:
//      IN EFI_HANDLE ImageHandle
//                  - Image handle
//      IN EFI_SYSTEM_TABLE *SystemTable
//                  - System table pointer
//
// Output:
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS if successful
//                  = or other valid EFI error code
//
// Notes:
//               *  Initializes/Installs the EFI_CMOS_ACCESS_INTERFACE 
//                  Protocol.
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS CmosManagerDxeEntry (
    IN  EFI_HANDLE              ImageHandle,
    IN  EFI_SYSTEM_TABLE        *SystemTable )
{
    EFI_STATUS                  Status;
    EFI_CMOS_MANAGER_INTERFACE  *Mgr;
    
	InitAmiLib(ImageHandle, SystemTable);


    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, "CmosManagerDXE Entry\n" ));
 
    //-----------------------------------------------------------------------
    // Initialize the manager interface and, at this point, only check for  
    // interface initialization errors.
    //-----------------------------------------------------------------------

    Mgr = NewCmosManagerInterface(NULL);
    if ( Mgr == NULL || !Mgr->CheckStatus(Mgr, CMOS_VALID_INTERFACE) ) {
        return  Status = EFI_UNSUPPORTED;
    }
    if ( Mgr->CheckStatus( Mgr, CMOS_INTERFACE_ALREADY_INSTALLED) )
        return  Status = EFI_SUCCESS;


    //-----------------------------------------------------------------------
    // Handle specific reported errors.
    //
    // If there is a bad battery, continue using the Optimal Defaults Table.
    //
    // Otherwise, if there is a bad checksum or the Optimal Defaults table
    // is in use from PEI, then flush the table to physical CMOS and
    // discontinue its use.
    //
    // Note: the Optimal Defaults Table is enabled only in PEI
    //-----------------------------------------------------------------------

    if (  !Mgr->CheckStatus(Mgr, CMOS_IS_USABLE) ) {
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "CmosManagerDXE: CMOS_IS_USABLE = FALSE\n" ));

        // Default handler is to continue using the Optimal Defaluts Table
        // if the CMOS is unusable.
    }
    else if ( Mgr->CheckStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED) )
    {
#if (FULL_CMOS_MANAGER_DEBUG)
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "CmosManagerDXE: CMOS_OPTIMAL_DEFAULTS_ENABLED = TRUE\n" ));
        if (  Mgr->CheckStatus(Mgr, CMOS_BAD_CHECKSUM) ) {
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "CmosManagerDXE: CMOS_BAD_CHECKSUM = TRUE\n" ));
        }
#endif
        CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
            "CmosManagerDXE: Calling LoadOptimalDefaults()\n" ));
        Mgr->LoadOptimalDefaults(Mgr);
        if ( Mgr->CheckStatus(Mgr, CMOS_OPTIMAL_DEFAULTS_ENABLED) ) {
            CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
                "CmosManagerDXE: CMOS_OPTIMAL_DEFAULTS_OFF\n" ));
            Mgr->ConfigureManager( Mgr, CMOS_OPTIMAL_DEFAULTS_OFF );
        }
    }


    //-----------------------------------------------------------------------
    // Create handlers for CMOS Manager
    //-----------------------------------------------------------------------
    CreateEventHandlers();

    //-----------------------------------------------------------------------
    // Install the CMOS Access interface
    //-----------------------------------------------------------------------

    CMOS_TRACE_FULL((CMOS_TRACE_ALWAYS, 
        "CmosManagerDXE: Installing CMOS Access Protocol\n" ));
    Mgr->InstallAccessInterface(Mgr);
    if ( !Mgr->CheckStatus(Mgr, CMOS_VALID_MANAGER) ){
        CMOS_TRACE((CMOS_TRACE_ALWAYS, 
            "CmosManagerDXE: Invalid interface\n" ));
        return Status = EFI_UNSUPPORTED;
    }

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
