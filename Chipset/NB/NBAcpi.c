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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBAcpi.c 2     7/03/12 6:39a Yurenlai $
//
// $Revision: 2 $
//
// $Date: 7/03/12 6:39a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NBAcpi.c $
// 
// 2     7/03/12 6:39a Yurenlai
// [TAG]         None
// [Severity]    Important
// [Description] Change the Save/Restore NB Registers position.
// [Files]       NB.ASL, NBAcpi.c, NBDxe.c
// 
// 1     2/08/12 4:34a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        NBACPI.c
//
// Description: This file contains 2 eLinks for all North Bridge ACPI
//              Enabled/Disabled events.
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Protocol\SmmSwDispatch.h>

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

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbAcpiEnabled
//
// Description: This routine will be called when ACPI enabled.
//
// Input:       DispatchHandle  - Handle to the Dispatcher
//              DispatchContext - SW SMM dispatcher context
//
// Output:      None
//
// Notes:       Porting if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbAcpiEnabled (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
{

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   NbAcpiDisabled
//
// Description: This routine will be called when ACPI disabled.
//
// Input:       DispatchHandle  - Handle to the Dispatcher
//              DispatchContext - SW SMM dispatcher context
//
// Output:      None
//
// Notes:       Porting if needed.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID NbAcpiDisabled (
    IN EFI_HANDLE                   DispatchHandle,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
{
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
