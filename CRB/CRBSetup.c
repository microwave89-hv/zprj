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
// $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBSetup.c 1     2/12/12 10:38p Victortu $
//
// $Revision: 1 $
//
// $Date: 2/12/12 10:38p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRBSetup.c $
// 
// 1     2/12/12 10:38p Victortu
// Intel SharkBay CRB initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        CRBSetup.c
//
// Description: Chipset Reference Board Setup Routines
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Protocol\PciIo.h>
#include <Protocol\DevicePath.h>
#include <Protocol\PciRootBridgeIo.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitCRBStrings
//
// Description: Initializes Demo Board Setup String.
//
// Input:       HiiHandle - Handle to HII database
//              Class     - Indicates the setup class
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitCRBStrings (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{
    EFI_STATUS          Status = EFI_SUCCESS;

    if (Class == ADVANCED_FORM_SET_CLASS) {
        
    }
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
