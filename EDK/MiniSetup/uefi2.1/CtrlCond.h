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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/CtrlCond.h $
//
// $Author: Arunsb $
//
// $Revision: 8 $
//
// $Date: 10/18/12 6:04a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/CtrlCond.h $
// 
// 8     10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 5     10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 7     2/01/12 4:59a Rajashakerg
// [TAG]  		EIP77256 
// [Category]  	Improvement
// [Description]  	Provide the Support to override the control Condition
// checking() generically. And provide customization to supress the
// controls with Security GUIDed opcode.
// [Files]  		AMITSE.sdl, CommonHelper.c, CtrlCond.c and CtrlCond.h
// 
// 6     3/28/11 11:03p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 5     12/02/10 5:34p Madhans
// [TAG] - EIP 49559   
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- OneOption contols works ok if it stores the values in BYTE
// and Does not contain any suppressif for options.
// But it has issues in supporting UINT16, UINT32 and UINT64 storage.
// [Rootcause] - The Type is not checked for Storeage and issues with
// condition check for options.
// [Solution]- Fix done ctrlcond.c and uefi21wrapper.c 
// [Files] - CtrlCond.h, ctrlcond.c and uefi21wrapper.c 
// 
// 4     4/16/10 5:13p Madhans
// Changes for Tse 2.02. Please see Changelog.log for more details.
// 
// 3     2/19/10 8:50p Madhans
// 
// 1     7/24/09 6:54p Presannar
// 
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
// 
// 6     9/17/08 7:44p Madhans
// For Boot only Driver file split changes.
// 
// 5     2/14/06 1:02p Arunkumars
// 1. Added Inconsistentif feature
// 2. We publish two events before and after asking for password (see
// postmgt.c and minisetup.h)
// 
// 4     7/19/05 3:40p Jerryp
// Reduced number of parameters.
// Code spacing cleanup
// 
// 3     5/16/05 5:09p Franklynd
// 1-Support for multivariable (varstore, varstore_select,
// varstore_select_pair)
// 2-Support of optimal and failsafe defaults.
// 3- support of refresh of controls using their flag information.
// 4- added ORDERED_LIST control/
//
// 2     2/24/05 5:14p Franklynd
// 1- adding number of control after a label in control_info structure.
// 2- adding check of access flags in control (password)
// 3- color schema code moved to styles area.
//
// 1     2/16/05 7:09p Franklynd
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:          CtrlCond.h
//
// Description:	  Header File
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
#include "minisetup.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#define COND_NONE			0x0
#define COND_SUPPRESS		0x1
#define COND_HIDDEN			0x2
#define COND_GRAYOUT		0x3
#define COND_INCONSISTENT	0x4
#define COND_NOSUBMIT		0x5
//---------------------------------------------------------------------------


// functions
//UINT8 CheckControlCondition(UINT32 ControlAccess, UINT8  *CtrlPtr, UINT32 CtrlVar, UINT32 CtrlVar2, UINT8 *CondPtr);
UINT8 CheckControlCondition( CONTROL_INFO *controlInfo );
BOOLEAN CheckInconsistence( PAGE_INFO *pPageInfo );
UINT8 CheckOneOfOptionSuppressIf(CONTROL_INFO *ParentCtrlInfo, UINT8* CtrlCondPtr, UINT8* CtrlPtr);
//Start EIP : NO_SUBMIT_IF
BOOLEAN CheckNoSubmitIf( VOID );
BOOLEAN DrawMessageBox(CONTROL_INFO *pControlInfo, UINT16 Title, EFI_STRING_ID  Error);
UINT8 OEMCheckControlCondition(UINT8 FinalCond, CONTROL_INFO *controlInfo);//EIP 77256 : Provide the Support to override the control Condition checking() generically. And provide customization to supress the controls with Security GUIDed opcode.

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
