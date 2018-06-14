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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBDXEBoard.c 1     2/08/12 8:22a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 8:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBDXEBoard.c $
// 
// 1     2/08/12 8:22a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SBDxeBoard.C
//
// Description: This file contains DXE stage board component code for
//              South Bridge.
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Efi.h>
#include <DXE.h>
#include <token.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <setup.h>
#include <AmiCspLib.h>

// Produced Protocols

// Consumed Protocols
#include <Protocol\PciIO.h>
#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\BootScriptSave.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef VOID (SAVE_RESTORE_CALLBACK)( BOOLEAN Save );

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

SAVE_RESTORE_CALLBACK* SaveRestoreCallbackList[] = \
                                          { SAVE_RESTORE_CALLBACK_LIST NULL };

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

extern SAVE_RESTORE_CALLBACK SAVE_RESTORE_CALLBACK_LIST EndOfList;

// Function Definition(s)

//---------------------------------------------------------------------------

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SBDXE_BoardInit
//
// Description: This function initializes the board specific component in
//              in the chipset South bridge
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      Return Status based on errors that occurred while waiting for
//              time to expire.
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS SBDXE_BoardInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    InitAmiLib( ImageHandle, SystemTable );

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   SaveRestoreRegisters
//
// Description: This function calls registered callbacks to save/restore
//              registers value in timer interrupt routine
//
// Input:       BOOLEAN Save - if TRUE - save registers, FALSE - restore back
//
// Output:      None
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID SaveRestoreRegisters (
    IN BOOLEAN              Save )
{
    UINTN   i;

    for (i = 0; SaveRestoreCallbackList[i] != NULL; i++) 
        SaveRestoreCallbackList[i]( Save );
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
