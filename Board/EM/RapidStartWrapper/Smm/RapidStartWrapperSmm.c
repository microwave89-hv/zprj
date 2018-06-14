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
// $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartWrapperSmm.c 3     5/13/14 4:56a Joshchou $
//
// $Revision: 3 $
//
// $Date: 5/13/14 4:56a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartWrapperSmm.c $
// 
// 3     5/13/14 4:56a Joshchou
// [TAG]  		EIP167032
// [Category]  	Improvement
// [Description]  	Review the variable's attribute, we shouldn't use
// runtime attribute with setup variable.
// [Files]  		RapidStartWrapperSmm.c
// RapidStartWrapperSmm.h
// RapidStartWrapperSmm.cif
// 
// 2     4/15/13 2:36a Bensonlai
// [TAG]  		None
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	If users change any item from driver then restore to boot
// setting, our SMI can't distinguish between user's and driver's event.
// [RootCause]  	It's an Intel driver issue.
// [Solution]  	1. Removing the sync up with Rapid Start driver and BIOS
// variable as default.
// 2. Remove our BIOS workaround.
// [Files]  		RapidStartWrapperSmm.sdl, RapidStartWrapperSmm.h,
// RapidStartWrapperSmm.sdl, RapidStartWrapperAcpiTables.sdl,
// RapidStartWrapper.sdl
// 
// 1     12/27/12 2:23a Bensonlai
// [TAG]  		EIP110680
// [Category]  	New Feature
// [Description]  	When iRST application is run under OS, and change
// timer.
// BIOS should update the changed to Setup option as well.
// [Files]  		Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.c
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.h
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.mak
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.dxs
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.sdl
// Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.cif
// Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.cif
// Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.sdl
// Board\EM\RapidStartWrapper\AcpiTables\Ssdt\RapidStartWrapper.asl
// Board\EM\RapidStartWrapper\RapidStartSetup\RapidStartSetup.sd
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: RapidStartWrapperSmm.c
//
// Description: Sw SMI for RapidStart Wrapper
//
//<AMI_FHDR_END>
//**********************************************************************

#include "RapidStartWrapperSmm.h"

VOID* InternalGetSmstConfigurationTable(IN EFI_GUID *TableGuid) {
    EFI_CONFIGURATION_TABLE	    *Table;
    UINTN                        i;
    EFI_STATUS                   Status;

    if (mSmmBase == NULL) {
        Status = gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, &mSmmBase);
        if (EFI_ERROR(Status) || mSmmBase == NULL)return NULL;
    }

    if (mSmst == NULL ) {
        if (mSmmBase!=NULL) {
            Status = mSmmBase->GetSmstLocation (mSmmBase, &mSmst);
            if (EFI_ERROR(Status) || mSmst == NULL)return NULL;
        }
    }

    if (mSmst != NULL) {
        Table = mSmst->SmmConfigurationTable;
        i = mSmst->NumberOfTableEntries;

        for (; i; --i,++Table)
        {
            if (CompareGuid(&Table->VendorGuid,TableGuid))
                return Table->VendorTable;
        }
    }
    return NULL;
}

VOID
RapidStartSyncVariable (
    VOID
)
{
    EFI_STATUS       Status;
    RAPID_START_WRAPPER_SMM_DATA  RapidStartWrapperSmmData;
    RapidStartWrapperSmmData.S3WakeTimerMin = mRapidStartGlobalNvs->WakeTimerMin;

    if ( (mRapidStartGlobalNvs->EventsEnabled & RAPID_START_ACPI_RTC_WAKE) != 0) {
        RapidStartWrapperSmmData.EntryOnS3RtcWake = 1;
    } else {
        RapidStartWrapperSmmData.EntryOnS3RtcWake = 0;
    }

    if ( (mRapidStartGlobalNvs->EventsEnabled & RAPID_START_ACPI_BATT_WAKE) != 0) {
        RapidStartWrapperSmmData.EntryOnS3CritBattWake = 1;
    } else {
        RapidStartWrapperSmmData.EntryOnS3CritBattWake = 0;
    }

    Status = mySMMgRT->SetVariable( L"RstWrapVar", \
                                    &RapidStartWrapperSmmDataGuid, \
                                    EFI_VARIABLE_NON_VOLATILE | \
                                    EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                                    EFI_VARIABLE_RUNTIME_ACCESS, \
                                    sizeof (RAPID_START_WRAPPER_SMM_DATA), \
                                    &RapidStartWrapperSmmData
                                  );

    if ( EFI_ERROR(Status) ) {
        return;
    }

    return;
}

VOID
RapidStartWrapperSwSmiCallback (
    IN  EFI_HANDLE                    DispatchHandle,
    IN  EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext
)
{
    UINT8            WrapperFunctionIndex;

    WrapperFunctionIndex = IoRead8(SW_SMI_IO_DATA_ADDRESS);     // Get Wrapper Function Index
    IoWrite8(SW_SMI_IO_DATA_ADDRESS, 0x00);                     // Clear data

    switch ( WrapperFunctionIndex ) {
    case AMI_RAPID_START_SYNC_VARIABLE_FUNCTION:
        RapidStartSyncVariable();
        break;

    default :
        break;
    }

    return;
}

EFI_STATUS
RapidStartWrapperSmmEntryPoint (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
)
{
    RAPID_START_GLOBAL_NVS_AREA_PROTOCOL  *RapidStartGlobalNvsAreaProtocol;
    EFI_SMM_SW_DISPATCH_PROTOCOL          *SwDispatch;
    EFI_SMM_SW_DISPATCH_CONTEXT           SwContext;
    EFI_HANDLE                            DispatchHandle;
    EFI_STATUS                            Status;
    VOID                                  *ptrRs;

    ptrRs = InternalGetSmstConfigurationTable(&SmmRtServTableGuid);
    if (ptrRs!=NULL) mySMMgRT = ptrRs;

    DEBUG ((EFI_D_INFO, "RapidStartWrapperSmmEntryPoint()\n"));

    Status = gBS->LocateProtocol (
                 &gRapidStartGlobalNvsAreaProtocolGuid,
                 NULL,
                 (VOID **) &RapidStartGlobalNvsAreaProtocol
             );

    if ( EFI_ERROR (Status) ) {
        DEBUG ((EFI_D_INFO, "No RapidStart info protocol available\n"));
        return Status;
    }

    mRapidStartGlobalNvs      = RapidStartGlobalNvsAreaProtocol->Area;
    DEBUG ((EFI_D_INFO, "RapidStartGlobalNvs:      %x\n", mRapidStartGlobalNvs));

    ///
    /// Locate the SMM SW dispatch protocol
    ///
    Status = gBS->LocateProtocol (&gEfiSmmSwDispatchProtocolGuid, NULL, &SwDispatch);
    if ( EFI_ERROR (Status) ) {
        return Status;
    }

    ///
    /// Register SWSMI handler
    ///
    DEBUG ((EFI_D_INFO, "Register SW_SMI_RAPID_START_WRAPPER: %x\n", SW_SMI_RAPID_START_WRAPPER));
    SwContext.SwSmiInputValue = SW_SMI_RAPID_START_WRAPPER;
    Status = SwDispatch->Register (
                 SwDispatch,
                 RapidStartWrapperSwSmiCallback,
                 &SwContext,
                 &DispatchHandle
             );
    if ( EFI_ERROR (Status) ) {
        return Status;
    }

    return EFI_SUCCESS;
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
