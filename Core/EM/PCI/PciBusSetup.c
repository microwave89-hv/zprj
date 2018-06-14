//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
// $Header: /Alaska/BIN/Core/Modules/PciBus/PciBusSetup.c 2     9/25/08 11:54a Yakovlevs $
//
// $Revision: 2 $
//
// $Date: 9/25/08 11:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Modules/PciBus/PciBusSetup.c $
// 
// 2     9/25/08 11:54a Yakovlevs
// Added PciBus Driver version display and Screen update routines.
// 
// 1     3/12/07 12:07p Yakovlevs
// 
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		PciBusSetup.c
//
// Description:	Pci Bus Setup Routines
//
// NOTE: Use this hook to dynamically change PCI BUS Driver Setup screen 
// Strings.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>
#include <Protocol\PciIo.h>
#include <Token.h>

// Function Definitions


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitBoardStrings
//
// Description:	This function initializes the board related setup option values
//
// Input:		HiiHandle	Handle to HII database
//				Class		Indicates the setup class
//
// Output:		None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID 
InitPciBusStrings(
	EFI_HII_HANDLE		HiiHandle, 
	UINT16				Class
)
{
   	if(Class == ADVANCED_FORM_SET_CLASS){
        InitString(HiiHandle, STRING_TOKEN(STR_PCI_DRIVER_VER), L"V %d.%02d.%02d", 
        PCI_BUS_MAJOR_VER, PCI_BUS_MINOR_VER, PCI_BUS_REVISION);
    }
	return;
}



//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
