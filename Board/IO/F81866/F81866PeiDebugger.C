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
//
//*************************************************************************
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866PeiDebugger.C 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866PeiDebugger.C $
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting 
// [Files]  		F81866.CIF
// IO_F81866.SDL
// F81866.ASL
// F81866.MAK
// F81866.SD
// F81866.UNI
// F81866DXE.C
// F81866PEI.C
// F81866PeiDebugger.C
// F81866Setup.C
// F81866Setup.H
// History.txt
// F81866.chm
// 
// 2     3/21/11 9:41p Mikes
// seperate the core and oem job
// 
//*************************************************************************

//<AMI_FHDR_START>
//
// Name:  <F81866PeiDebugger.C>
//
// Description: The file contains PEI stage board component code for Template SB
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Efi.h>
#include <AmiLib.h>
#include <Token.h>
#include "AmiDebugPort.h"

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------
VOID    F81866_INIT();

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    SIOPEIDBG_Initialize
//
// Description:    
//  This eLink function is used to initialize the super I/O 
//  for PEI Debugger support
//
// Input:    
//  DebugPort -> Debug transport interface structure
//
// Output:    
//  EFI_STATUS
//
// Notes:    PORTING REQUIRED
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SIOPEIDBG_Initialize(
    IN    PEI_DBG_PORT_INFO    *DebugPort
) 
{
     F81866_INIT();

    #ifndef    USB_DEBUGGER
    DebugPort->SerialPort.COMBaseAddr = DEBUG_COM_PORT_ADDR;
    DebugPort->SerialPort.SIO_COM_LDN = DEBUG_LDN_UART;
    #endif

    return EFI_SUCCESS;
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

