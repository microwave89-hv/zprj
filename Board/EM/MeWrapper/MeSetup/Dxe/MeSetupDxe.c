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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/Dxe/MeSetupDxe.c 5     5/14/14 10:01p Tristinchou $
//
// $Revision: 5 $
//
// $Date: 5/14/14 10:01p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/Dxe/MeSetupDxe.c $
// 
// 5     5/14/14 10:01p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 4     3/14/13 2:39a Klzhan
// Modify for PTT check
// 
// 2     2/23/13 1:27a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Return SUCCESS in entry point.
// 
// 1     2/07/13 2:04a Klzhan
// [TAG]  		EIP114344
// [Category]  	Improvement
// [Description]  	Create a setup item for TPM Device Selection
// [Files]  		MeSetupDxe.cif
// MeSetupDxe.c
// MeSetupDxe.h
// MeSetupDxe.sdl
// MeSetupDxe.dxs
// MeSetupDxe.mak
// 
//
//**********************************************************************
#include "MeSetupDxe.h"

EFI_STATUS
MeSetupDxeEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                  Status;
    UINT32                      SetupVarAttr;
    UINT32                      PttInfoVarAttr;
    UINTN                       VariableSize;
    EFI_GUID                    SetupGuid = SYSTEM_CONFIGURATION_GUID;
    EFI_GUID                    PttInfoVariableGuid = PTT_INFO_VARIABLE_GUID;
    SETUP_DATA                  gSetupData;
    PTT_INFO_VARIABLE_DATA      gPttInfoVariable;
    PCH_SERIES                  PchSeries = GetPchSeries();

    DEBUG ((EFI_D_INFO, "[MeSetupDxe.c] : Entry Point...\n"));

    if ( PchSeries != PchLp ) {
        return   EFI_SUCCESS;
    }

    PttInfoVarAttr = 0;
    VariableSize = sizeof (PTT_INFO_VARIABLE_DATA);
    Status = gRT->GetVariable (
                 L"PttInfoVariable",
                 &PttInfoVariableGuid,
                 &PttInfoVarAttr,
                 &VariableSize,
                 &gPttInfoVariable );
    if( EFI_ERROR(Status) )
        PttInfoVarAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS;

    PttHeciGetCapability(&gPttInfoVariable.PTTCapability);
    PttHeciGetState(&gPttInfoVariable.PTTState);

    Status = gRT->SetVariable (
                 L"PttInfoVariable",
                 &PttInfoVariableGuid,
                 PttInfoVarAttr,
                 VariableSize,
                 &gPttInfoVariable
             );

    if ( EFI_ERROR (Status) ) {
        DEBUG((EFI_D_INFO, "[MeSetupDxe.c] : Failed to Set PttInfoVariable Status = %x\n", Status));
        return   EFI_SUCCESS;
    }

    SetupVarAttr = 0;
    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable(
                 L"Setup",
                 &SetupGuid,
                 &SetupVarAttr,
                 &VariableSize,
                 &gSetupData );

    if ( gPttInfoVariable.PTTCapability ) {
         if ( (gSetupData.TpmDeviceSelectionUpdate == 1) && (gPttInfoVariable.PTTState != gSetupData.TpmDeviceSelection) ) {
            if ( gSetupData.TpmDeviceSelection == 1 ) {
                PttHeciSetState(TRUE);
            } else {
                PttHeciSetState(FALSE);
            }
            gSetupData.TpmDeviceSelectionUpdate = 0;

            Status = gRT->SetVariable(
                         L"Setup",
                         &SetupGuid,
                         SetupVarAttr,
                         VariableSize,
                         &gSetupData );

            Status = HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
            if( !EFI_ERROR(Status) ) {
                EFI_DEADLOOP();
            }
        }
    }

    if ( gPttInfoVariable.PTTState ) {
        gSetupData.TpmDeviceSelection = 1;
    } else {
        gSetupData.TpmDeviceSelection = 0;
    }

    Status = gRT->SetVariable(
                 L"Setup",
                 &SetupGuid,
                 SetupVarAttr,
                 VariableSize,
                 &gSetupData );

    if ( EFI_ERROR (Status) ) {
        DEBUG((EFI_D_INFO, "[MeSetupDxe.c] : Failed to Set SetupVariable Status = %x\n", Status));
        return   EFI_SUCCESS;
    }

    DEBUG ((EFI_D_INFO, "[MeSetupDxe.c] : Entry End...\n"));

    return   EFI_SUCCESS;
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