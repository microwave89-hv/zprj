//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/CSM/Generic/csmsetup.c 4     1/12/10 11:52a Olegi $
//
// $Revision: 4 $
//
// $Date: 1/12/10 11:52a $
//
//****************************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:        CSMSETUP.C
//
// Description: CSM Setup related functions
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SetupStrTokens.h>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	InitCsmStrings
//
// Description:	This function is eLink'ed with the chain executed right before
//				the Setup.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID InitCsmStrings(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
    UINT8 MjCsmVer = *(UINT8*)0xF0018;
    UINT8 MnCsmVer = *(UINT8*)0xF0019;

	//example: InitString(HiiHandle, STRING_TOKEN(STR_USB_MODULE_VERSION_VALUE), L"%d", 25);
	// Module version

	InitString(HiiHandle, STRING_TOKEN(STR_CSM_MODULE_VERSION_VALUE),
                L"%02x.%02x", MjCsmVer, MnCsmVer);

}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
