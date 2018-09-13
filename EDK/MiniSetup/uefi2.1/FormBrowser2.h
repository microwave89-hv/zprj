//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2004, American Megatrends, Inc.        **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**           6145-F Northbelt Pkwy, Norcross, GA 30071         **//
//**                                                             **//
//**                     Phone (770)-246-8600                    **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/FormBrowser2.h $
//
// $Author: Arunsb $
//
// $Revision: 9 $
//
// $Date: 10/18/12 6:04a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/FormBrowser2.h $
// 
// 9     10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 4     10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 8     9/17/12 6:22a Rajashakerg
// Updated EIP changes for 2.16 release.
// 
// 6     9/08/12 3:53p Premkumara
// [TAG]  		EIP 100546
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Old core(such as 4.6.4.0) is not building successfully with
// latest TSE
// [RootCause]  	BROWSER_ACTION related request macro are not defined in
// TSE
// [Solution]  	Defined BROWSER_ACTION related request macros in
// FormBrowser2.h
// [Files]  		FormBrowser2.h
// 
// 5     12/07/11 8:13a Rajashakerg
// [TAG]  		EIP75118 
// [Category]  	Improvement
// [Description]  	xtractConfig() fail since BrowserCallback() cannot find
// the variable to process
// [Files]  		FormBrowser2.c, FormBrowser2.h, HiiCallback.c,
// Uefi21Wapper.c, PopupSel.c
// 
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 8:50p Madhans
// 
// 1     7/24/09 6:54p Presannar
// 
// 2     4/14/09 12:36p Presannar
// Added Fn prototype FormBrowserLocateSetupHandles and
// FormBrowserHandleValid
// 
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
// 
// 1     12/29/08 4:46p Presannar
// FormBrowser2 protocol Send Form and BrowserCallback initial draft
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          FormBrowser2.h
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

//----------------------------------------------------------------------------
#ifndef _FORM_BROWSER2_H
#define _FORM_BROWSER2_H
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#include "Minisetup.h"
#include EFI_PROTOCOL_DEFINITION (FormBrowser2)
//----------------------------------------------------------------------------
//Added for UEFI spec. 2.3 compatibility- EIP-100546 Start
#ifndef EFI_BROWSER_ACTION_REQUEST_FORM_SUBMIT_EXIT
#define EFI_BROWSER_ACTION_REQUEST_FORM_SUBMIT_EXIT 	4
#endif

#ifndef EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD_EXIT
#define EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD_EXIT	5
#endif

#ifndef EFI_BROWSER_ACTION_REQUEST_FORM_APPLY
#define EFI_BROWSER_ACTION_REQUEST_FORM_APPLY	6
#endif

#ifndef EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD
#define EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD	7
#endif
//Added for UEFI spec. 2.3 compatibility- EIP-100546 End
VOID SetCallBackControlInfo(EFI_HANDLE VarHandle, UINT32 VarIndex);

EFI_STATUS  InstallFormBrowserProtocol(EFI_HANDLE Handle);
VOID UnInstallFormBrowserProtocol(EFI_HANDLE Handle);

EFI_STATUS
EFIAPI
SendForm (
  IN  CONST EFI_FORM_BROWSER2_PROTOCOL *This,
  IN  EFI_HII_HANDLE                   *Handles,
  IN  UINTN                            HandleCount,
  IN  EFI_GUID                         *FormSetGuid, OPTIONAL
  IN  UINT16                           FormId, OPTIONAL
  IN  CONST EFI_SCREEN_DESCRIPTOR      *ScreenDimensions, OPTIONAL
  OUT EFI_BROWSER_ACTION_REQUEST       *ActionRequest  OPTIONAL
  );

EFI_STATUS
EFIAPI
BrowserCallback (
  IN CONST EFI_FORM_BROWSER2_PROTOCOL  *This,
  IN OUT UINTN                         *ResultsDataSize,
  IN OUT EFI_STRING                    ResultsData,
  IN BOOLEAN                           RetrieveData,
  IN CONST EFI_GUID                    *VariableGuid, OPTIONAL
  IN CONST CHAR16                      *VariableName  OPTIONAL
  );

EFI_STATUS FormBrowserLocateSetupHandles(VOID*	**handleBuffer,UINT16 *count);
BOOLEAN FormBrowserHandleValid(VOID);

#endif /* #define _FORM_BROWSER2_H */
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**     5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
