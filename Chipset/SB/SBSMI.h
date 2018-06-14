//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB SMI/SBSMI.h 4     12/30/13 5:59a Barretlin $
//
// $Revision: 4 $
//
// $Date: 12/30/13 5:59a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SB SMI/SBSMI.h $
// 
// 4     12/30/13 5:59a Barretlin
// [TAG]  		EIP144559
// [Category]  	Improvement
// [Description]  	S3 can't resume via USB KB & MS under usb3.0 port in
// special case
// [Files]  		SBSMI.c SBSMI.h SBGeneric.c
// 
// 3     4/19/13 6:35a Wesleychen
// [TAG]           None
// [Category]      Improvement
// [Description]   Update GbES02SxWorkaround() and add 
//                 UsbS02SxWorkaround() for SBPwrBtnHandler().
// [Files]         SBSMI.c; SBSMI.h; SBGeneric.c; SBCspLib.h
// 
// 1     2/08/12 8:31a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//*************************************************************************
//
// Name:        SBSMI.h
//
// Description: This file contains all definitions for South Bridge SMI
//              driver 
//
//*************************************************************************
//<AMI_FHDR_END>

#ifndef _SBSMI_H_
#define _SBSMI_H_

// Type Definition(s)

// Prototypes
VOID SbSmiHandler ( VOID );

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
