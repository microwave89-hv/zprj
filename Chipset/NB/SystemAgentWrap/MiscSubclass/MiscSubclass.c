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
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/MiscSubclass/MiscSubclass.c 1     2/08/12 4:36a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 4:36a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/MiscSubclass/MiscSubclass.c $
// 
// 1     2/08/12 4:36a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  MiscSubclass.c
//
// Description: This file for BIOS id Build in to Hii data base.
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InitiMiscStrings
//
// Description: Create BIOS id string.
//
// Input:       HiiHandle - Handle to HII database
//              Class - Indicates the setup class
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID
InitiMiscStrings (
    IN EFI_HII_HANDLE    HiiHandle, 
    IN UINT16            Class
)
{
    STRING_REF                      Dummy [] = { STRING_TOKEN (STR_BIOS_ID)}
    return;
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