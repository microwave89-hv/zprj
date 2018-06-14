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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetupReset.c 2     5/14/14 10:02p Tristinchou $
//
// $Revision: 2 $
//
// $Date: 5/14/14 10:02p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetupReset.c $
// 
// 2     5/14/14 10:02p Tristinchou
// [TAG]  		EIP167030
// [Category]  	Improvement
// [Description]  	Remove the variable runtime attribute and keep original
// attributes.
// 
// 1     2/07/13 1:59a Klzhan
// [TAG]  		EIP114334
// [Category]  	Improvement
// [Description]  	Create a setup item for TPM Device Selection
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            MeSetupReset.c
//
// Description:     Setup hooks for MeSetup module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <Token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <AmiCSPLib.h>

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
static SETUP_DATA            gNewSetupData;
static SETUP_DATA            gOldSetupData;

// GUID Definition(s)
static EFI_GUID              gEfiSetupGuid = SETUP_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MeSetupProcessEnterSetupForPTT
//
// Description:	This function is a hook called when TSE determines
//              that it has to load the boot options in the boot
//              order. This function is available as ELINK.
//
// Input:               VOID
//
// Output:              VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MeSetupProcessEnterSetupForPTT (
    VOID
)
{
    EFI_STATUS            Status;
    UINT32                VarAttr;
    UINTN                 VariableSize;

    VariableSize = sizeof (SETUP_DATA);
    Status = pRS->GetVariable(
                    L"Setup",
                    &gEfiSetupGuid,
                    &VarAttr,
                    &VariableSize,
                    &gOldSetupData );
    return;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: MeSetupResetHookForPTT
//
// Description:	This function is a hook called after some control
//              modified in the setup utility by user. This
//              function is available as ELINK.
//
// Input:               VOID
//
// Output:              VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
MeSetupResetHookForPTT (
    VOID
)
{
    EFI_STATUS            Status;
    UINT32                VarAttr;
    UINTN                 VariableSize;

    VariableSize = sizeof (SETUP_DATA);
    Status = pRS->GetVariable(
                    L"Setup",
                    &gEfiSetupGuid,
                    &VarAttr,
                    &VariableSize,
                    &gNewSetupData );

    if ( !EFI_ERROR (Status) ) {
        if (gNewSetupData.TpmDeviceSelection != gOldSetupData.TpmDeviceSelection) {
             gNewSetupData.TpmDeviceSelectionUpdate = 1;

                Status = pRS->SetVariable (
                                L"Setup",
                                &gEfiSetupGuid,
                                VarAttr,
                                VariableSize,
                                &gNewSetupData );
        }
    }

    return;
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