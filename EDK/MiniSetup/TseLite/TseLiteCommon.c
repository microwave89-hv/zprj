//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2012, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/TseLiteCommon.c $
//
// $Author: Premkumara $
//
// $Revision: 16 $
//
// $Date: 8/28/14 9:11a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/TseLiteCommon.c $
// 
// 16    8/28/14 9:11a Premkumara
// [TAG] 		EIP168489
// [Category] 	Bug Fix
// [Severity:]		Normal
// [Symptom:] 	System will display blue screen after use OEM command to
// boot to BIOS Setup Utility from Built-in EFI Shell
// [Files] 		TseliteCommon.c
// 
// 15    2/11/14 8:47p Arunsb
// [TAG]	EIP148693
// [Category]	Bug Fix
// [Severity:]	Important
// [Symptom:]	Slowness in shell performance
// [Root Cause]	Memory fragmentation
// [Solution]	Controlled the TSE destructor with token from sdl file
// [Files]	amitse.sdl, tselitecommon.c
// 
// 14    6/10/13 10:03a Arunsb
// gRefreshIdCount made as 0 bcoz exiting from setup and coming back wont
// reinit it
// 
// 13    4/18/13 9:31a Arunsb
// Function moved to avoid build error in 2.0
// 
// 12    4/15/13 5:40a Arunsb
// gRefreshIdInfo check added
// 
// 11    10/18/12 6:02a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:38p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 9     9/14/12 12:59p Madhans
// [TAG]  		EIP101218
// [Category]  	Bug Fix
// [Severity]  	Critical
// [Symptom]  	If Sendform is called more than once from DHP
// (DriverHealthprotocol Module). It does not enter.
// [RootCause]  	SendForm called before postmanagerhandsake was not
// cleaned gApp correctly.
// [Solution]  	Fix to do the cleanup
// [Files]  		tselitecommon.c
// 
// 8     5/28/12 7:29a Rajashakerg
// [TAG]  		EIP85564
// [Category]  	Improvement
// [Description]  	UefiHiiTestPrintLength function needs optimization
// [Files]  		TseLiteCommon.c, hiistring21.c
// 
// 7     4/27/12 7:28a Arunsb
// [TAG]  		EIP88449 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	SUT hangs when "Exit Without Saving" prompt is select as
// 'yes' in setup.
// [RootCause]  	gVariablelist freed before calling callback
// [Solution]  	gVariablelist freed after calling callback
// [Files]  		TseLiteCommon.c
// 
// 6     3/28/11 9:25p Madhans
// [TAG]  		EIP41744 
// [Category]  	Improvement
// [Description]  	SoftKeyBoard Support in TSE. and Support to Work with
// new mouse driver(Label 07).
// [Files]  		HookAnchor.h
// AMITSE.sdl
// CommonHelper.c
// commonoem.c
// commonoem.h
// HookList.c
// HookAnchor.c
// Mouse.c
// minisetupext.c
// postmgmtext.c
// minisetupext.h
// PopupPassword.c
// PopupString.c
// TseLiteCommon.c
// 
// 5     3/21/11 12:46a Rajashakerg
// [TAG]  		EIP53480
// [Category]  	Improvement
// [Description]  	FormBrowser extended actions support
// [Files]  		callback.c, minisetupext.c, minisetupext.h, numeric.c,
// PopupSel.c, PopupString.c, SubMenu.c, TseLiteCommon.c, UefiAction.c,
// Hiicallback.c, TseUefiHii.h, Uefi21Wapper.c, HiiCallback.c
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:19a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 7:13a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     8/13/09 1:21p Blaines
// EIP #24980 Fix to properly display right area text
// 
// 3     6/23/09 6:53p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 2     5/07/09 10:36a Madhans
// Changes after Bin module
// 
// 1     4/28/09 11:07p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
// 
//
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		TseLiteCommon.c
//
// Description:	This file contains code for the TSE Lite common functions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"


SETUP_PKG		*gSetupPkg;
SCREEN_INFO		*gScreen;
PAGE_LIST		*gToolPages;
PAGE_LIST		*gPages;
CONTROL_INFO	*gToolControlInfo;
CONTROL_INFO	*gControlInfo;
VARIABLE_LIST	*gToolVariables;
VARIABLE_LIST	*gVariables;
HPK_INFO		*gHpkInfo;
GUID_LIST		*gGuidList;
PAGE_ID_LIST	*gPageIdList;
PAGE_ID_LIST	*gToolPageIdList;
PAGE_ID_INFO	*gPageIdInfo;
PAGE_ID_INFO	*gToolPageIdInfo;
FRAME_DATA		*gActiveFrame = NULL;

UINT16	gCheckboxTokens[] =
{
	STRING_TOKEN(STR_CTRL_CHKBOX_DISABLE),
	STRING_TOKEN(STR_CTRL_CHKBOX_ENABLE)
};

UINTN gLabelLeftMargin = 2 ;
UINTN gControlLeftMargin = 24;
UINTN gControlLeftPad = 2 ;
UINTN gControlRightAreaWidth = 27 ;
BOOLEAN	gVariableChanged = FALSE;
BOOLEAN	gResetRequired = FALSE;
UINT32 gStartPage = 0;

APPLICATION_DATA	*gApp = NULL;
UINTN           gHpkInfoLength;
UINT32 GetControlConditionVarId(CONTROL_INFO *control);

extern CHAR8 *GlyphWidthCache;//EIP 85564 : UefiHiiTestPrintLength function needs optimization
extern UINT32 gRefreshIdCount;
extern REFRESH_ID_INFO *gRefreshIdInfo;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	MiniSetupUIExit
//
// Description:	Freesup UI related resources.
//
// Input:		none
//
// Output:		none
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN TseDebugDisableApplicationDestructor (VOID);
VOID MiniSetupUIExit(VOID)
{
    EFI_STATUS Status = EFI_SUCCESS;
	UINTN index;

	// Don't do the MiniSetupExit if it is not a first call to PostManagerHandshake.
	if(gPostManagerHandshakeCallIndex>2) //gApp should be preserved when it is not freed.
	{
		// to Let Next call not quit.
		gApp->Quit=FALSE;
		goto Done;
	}
	
	if ( gApp != NULL )
	{
		if (!TseDebugDisableApplicationDestructor ())
		{
			gApplication.Destroy( gApp, TRUE );
		}
		gApp = NULL;

		MouseDestroy();
	}

Done:
    //Close the Event and Free the NotifyContext created for Controls with Refresh Id.
    if(gRefreshIdInfo) {
        for(index = 0; index < gRefreshIdCount; index++) 
        {
            if(gRefreshIdInfo[index].pEvent)//Close the event
            {
	            Status = gBS->CloseEvent(gRefreshIdInfo[index].pEvent);
	            if(Status == EFI_SUCCESS)
                {
		            gRefreshIdInfo[index].pEvent = NULL;
	            }		
            }
            
            MemFreePointer( (VOID **)&gRefreshIdInfo[index].pNotifyContext );
        }
        MemFreePointer( (VOID **)&gRefreshIdInfo );
        gRefreshIdCount = 0;
    }

    UEFICallSetupFormCallBack(AMI_CALLBACK_FORM_CLOSE);//EIP-53480: Calling the Wrapper function with AMI_CALLBACK_FORM_CLOSE action before HiiExit() 
    if ( gVariableList != NULL )
    {
	    for ( index = 0; index < gVariables->VariableCount; index++ )
		    MemFreePointer( (VOID **)&gVariableList[index] );

	    MemFreePointer( (VOID **)&gVariableList );
    }
    //Commented and moved above for EIP88449
    //UEFICallSetupFormCallBack(AMI_CALLBACK_FORM_CLOSE);//EIP-53480: Calling the Wrapper function with AMI_CALLBACK_FORM_CLOSE action before HiiExit() 
    HiiExit( );


    if(GlyphWidthCache) {
        MemFreePointer((VOID **)&GlyphWidthCache);// EIP 85564 :free the memory which was used to store the widths of each possible CHAR16 glyph.
    }

}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetBootTimeOut
//
// Description:	Timeout value from the variable.
//
// Input:		DefaultValue
//
// Output:		Timeout value
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 GetBootTimeOutLocal(UINT16 DefaultValue)
{
	UINT16 *TimeOut=NULL, Value = 0;
	UINTN size = 0;

	// Install boot timeout
	TimeOut = VarGetNvram( VARIABLE_ID_BOOT_TIMEOUT, &size );

	if ( TimeOut != NULL )
	{
		Value = *TimeOut;
	}
	else
	{
		Value = DefaultValue;
		VarSetNvram( VARIABLE_ID_BOOT_TIMEOUT, &Value, sizeof(UINT16) );
	}

	return Value;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	_GetControlVariable
//
// Description:	Function to get control variable.
//
// Input:		CONTROL_INFO *control
//
// Output:		UINT32
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT32 _GetControlVariable(CONTROL_INFO *control)
{
	return control->ControlVariable;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
// Procedure:   _GetPageInfo
//
// Description: Returns pointer to the PAGE_INFO struct of given PgIndex
//
// Input:	UINT32 PgIndex - Page index
//			PAGE_INFO **PageInfo - Pointer to the page information struct
//
// Output:	EFI_STATUS status - EFI_SUCCESS if successful, else EFI_ERROR
//---------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS _GetPageInfo(UINT32 PgIndex, PAGE_INFO **PageInfo)
{
  EFI_STATUS status = EFI_SUCCESS;

  if((gApplicationData == NULL) || (gPages == NULL))
  {
    status = EFI_NOT_READY;
    goto DONE;
  }

  if(PgIndex > gPages->PageCount)
  {
    status = EFI_INVALID_PARAMETER;
    goto DONE;
  }

  *PageInfo = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[PgIndex]);

DONE:
  return status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:     IsPageModal
//
// Description:   Is this a modal page 
//
// Parameter:     IN  UINT32 PgIndex
//
// Return Value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
#define ASSERT_ERROR_STATUS(assertion)		if(EFI_ERROR(assertion)) goto DONE
BOOLEAN IsPageModal(UINT32 PgIndex)
{
  EFI_STATUS status = EFI_SUCCESS;
  BOOLEAN isTrue = FALSE;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);
  isTrue = pageInfo->PageFlags.PageModal ? TRUE : FALSE;

DONE:
  return isTrue;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:     GetPageSubTitle
//
// Description:   Get the Page Subtitle String Index
//
// Parameter:     IN  UINTN  PgIndex
//                OUT UINT16 *subtitleToken
//
// Return Value:  EFI_STATUS
//                    EFI_SUCCESS
//                    EFI_NOT_READY
//                    EFI_INVALID_PARAMETER
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS GetPageSubTitle(UINT32 PgIndex, UINT16 *SubtitleToken)
{
  EFI_STATUS status = EFI_SUCCESS;
  PAGE_INFO *pageInfo = NULL;

  status = _GetPageInfo(PgIndex, &pageInfo);
  ASSERT_ERROR_STATUS(status);

  *SubtitleToken = pageInfo->PageSubTitle;

DONE:
  return status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
