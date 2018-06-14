//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportSetupHook.c 1     11/02/14 9:43p Tristinchou $
//
// $Revision: 1 $
//
// $Date: 11/02/14 9:43p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportSetupHook.c $
// 
// 1     11/02/14 9:43p Tristinchou
// [TAG]  		EIP189985
// [Category]  	Improvement
// [Description]  	For ME 9.1.20.1035, add NFC related option in setup
// [Files]  		NfcSupportSetupHook.cif
// NfcSupportSetupHook.c
// 
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            NfcSupportSetupHook.c
//
// Description:     Setup hooks for NfcSupportDxe module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <Token.h>
#include <Setup.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "NfcSupportDxe.h"

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
static NFC_SUPPORT_DATA     gNewNfcSupportData;
static NFC_SUPPORT_DATA     gOldNfcSupportData;

// GUID Definition(s)
static EFI_GUID             gNfcSupportDataGuid = NFC_SUPPORT_DATA_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	NfcSupportEnterSetup
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
NfcSupportEnterSetup(
    VOID
)
{
    EFI_STATUS            Status;
    UINT32                VarAttr;
    UINTN                 VariableSize;

    VariableSize = sizeof(NFC_SUPPORT_DATA);
    Status = pRS->GetVariable(
                    L"NfcSupportData",
                    &gNfcSupportDataGuid,
                    &VarAttr,
                    &VariableSize,
                    &gOldNfcSupportData );
    return;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: NfcSupportResetHook
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
NfcSupportResetHook(
    VOID
)
{
    EFI_STATUS            Status;
    UINT32                VarAttr;
    UINTN                 VariableSize;

    VariableSize = sizeof(NFC_SUPPORT_DATA);
    Status = pRS->GetVariable(
                    L"NfcSupportData",
                    &gNfcSupportDataGuid,
                    &VarAttr,
                    &VariableSize,
                    &gNewNfcSupportData );
    if ( !EFI_ERROR (Status) )
    {
        if( gNewNfcSupportData.NFCEnable != gOldNfcSupportData.NFCEnable )
        {
            gNewNfcSupportData.NFCEnableUpdate = 1;

            Status = pRS->SetVariable (
                            L"NfcSupportData",
                            &gNfcSupportDataGuid,
                            VarAttr,
                            VariableSize,
                            &gNewNfcSupportData );
        }
    }

    return;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************