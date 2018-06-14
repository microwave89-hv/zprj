//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Template/CSPLibrary/AMICSPLib.h 5     2/22/11 4:25p Artems $
//
// $Revision: 5 $
//
// $Date: 2/22/11 4:25p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Template/CSPLibrary/AMICSPLib.h $
// 
// 5     2/22/11 4:25p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 4     2/22/11 4:22p Artems
// EIP 51548 - Added AMI copyright headers, replaced TABs with spaces
// 
// 3     6/11/09 5:55p Robert
// CHM and coding standard update
// 
// 2     9/27/05 3:20p Sivagarn
// Included the macro "CSP_PCI_CFG_ADDRESS"
// 
// 1     1/21/05 12:46p Sivagarn
// Initial Checkin - Version 0.05
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: AmiCspLib.h
//
// Description: 
//  This file contains generic code to add functionality that can be used 
//  by any module.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __AMICSPLIB__H__
#define __AMICSPLIB__H__

#include <AmiCSPLibInc.H>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Name: CSP_PCI_CFG_ADDRESS
//
// Description:
//  This MACRO Converts bus, device function and register number into 64bit 
//  PCI configuration address
//
// Input:
//  bus - PCI bus where the device resides
//  dev - PCI device number to access
//  func - function number of the device being accessed
//  reg - PCI register of the function being accessed
//
// Notes:
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#define CSP_PCI_CFG_ADDRESS(bus,dev,func,reg)   \
 ((UINT64) ( (((UINTN)bus) <<   24) +   (((UINTN)dev)   << 16) + (((UINTN)func) << 8)   +   ((UINTN)reg) ))& 0x00000000ffffffff



#endif      // __AMICSPLIB__H__

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************