//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093              **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/KbcEmulation/SouthBridge/Intel/LynxPoint/KbcSbBoard.c 1     7/03/12 5:50a Rameshr $
//
// $Revision: 1 $
//
// $Date: 7/03/12 5:50a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/KbcEmulation/SouthBridge/Intel/LynxPoint/KbcSbBoard.c $
// 
// 1     7/03/12 5:50a Rameshr
// [TAG]  		EIP94194
// [Category]  	New Feature
// [Description]  	Initial Check-in for LynxPoint chipset.
// [Files]  		KbcSbBoard.cif
// KbcSbBoard.c
// 
// 
//****************************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    KbcSbboard.c
//
// Description: South Bridge Board module for KbcEmulation
//
//<AMI_FHDR_END>
//**********************************************************************
#include "KbcEmul.h"
#ifdef FRAMEWORK_AP4
#include "token.h"
#include "protocol/usbpolicy.h"
#else
#include "tokens.h"
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetRMhStatus
//
// Description: Returns the RMH status
//
// Input:       None
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN
GetRMhStatus ()
{

    //
    // For Intel 8 series (Lynx Point), return RMH is enabled by default .
    //

    return TRUE;

}


//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2012, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093              **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
