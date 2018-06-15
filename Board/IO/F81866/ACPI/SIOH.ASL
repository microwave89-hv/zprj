// THIS FILE IS INCLUDED to South Bridge device scope
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
// $Header: /Alaska/BIN/IO/Fintek/F81866/F81866 Device ASL Files/SIOH.ASL 1     7/20/11 4:22a Kasalinyi $
//
// $Revision: 1 $
//
// $Date: 7/20/11 4:22a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/IO/Fintek/F81866/F81866 Device ASL Files/SIOH.ASL $
// 
// 1     7/20/11 4:22a Kasalinyi
// [Category]  	Improvement
// [Description]  	Initial Porting
// [Files]  		DeviceASL.cif
// FDC.ASL
// LPTE.ASL
// PS2kb.asl
// PS2ms.asl
// Uart1.ASL
// Uart2.ASL
// Uart3.ASL
// Uart4.ASL
// Uart5.ASL
// Uart6.ASL
// SIOH.ASL
// 
// 1     3/21/11 9:42p Mikes
// 
//*************************************************************************

//<AMI_FHDR_START>
//
// Name:  <SIOH.ASL>
//
// Description: Define event handler For Super IO
//
//<AMI_FHDR_END>
//*************************************************************************
//-----------------------------------------------------------------------
// SIOH - SIO event handler, to be called from correspondent _Lxx method
// in order to serve the SIO chipset side of wake up event
//-----------------------------------------------------------------------
// input  - nothing
// output - nothing
//-----------------------------------------------------------------------
    Method(SIOH, 0){
        If(And(PMFG, 0x08)){
                Notify(PS2K, 0x2)    //KBD Wake up
        }
        If(And(PMFG, 0x10)){
                Notify(PS2M, 0x2)    //MOUSE Wake up
        }
    }    //End Of _Lx PMEH
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


