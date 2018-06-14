//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Board/OemSetup.c 2     6/25/09 6:09p Robert $
//
// $Revision: 2 $
//
// $Date: 6/25/09 6:09p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Board/OemSetup.c $
// 
// 2     6/25/09 6:09p Robert
// Updated Comments and function headers
//
// 1     6/13/06 4:53p Sivagarn
// Initial Checkin
//
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        OemSetup.c
//
// Description: OEM Template Setup Routines
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Protocol\PciIo.h>


// Function Definitions


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InitBoardStrings
//
// Description:
//  This function initializes the board related setup option values
//
// Input:
//  HiiHandle - Handle to HII database
//  Class - Indicates the setup class
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID
InitBoardStrings(
    EFI_HII_HANDLE      HiiHandle,
    UINT16              Class
)
{

    return;
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
