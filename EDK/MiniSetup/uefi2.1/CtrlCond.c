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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/CtrlCond.c $
//
// $Author: Premkumara $
//
// $Revision: 21 $
//
// $Date: 8/28/14 6:16a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/CtrlCond.c $
// 
// 21    8/28/14 6:16a Premkumara
// EIP-135253 Updating file name proper in #include
// 
// 20    2/11/14 8:49p Arunsb
// Changes reverted for 2.16.1243 label
// 
// 18    6/10/13 1:19p Arunsb
// Parameters passed properly in GetDefaultValue
// 
// 17    6/10/13 10:53a Arunsb
// Argument added in GetDefaultValue for EFI_IFR_TYPE_OTHER support in
// default retrieval.
// 
// 16    5/22/13 10:52a Arunsb
// Fixed the issue in read write opcode
// 
// 15    4/02/13 8:04a Arunsb
// [TAG]  		EIP113919, EIP114842
// [Category]  	Improvement
// [Description]  	Provide support for EFI_IFR_WRITE, EFI_IFR_READ,
// EFI_IFR_GET, EFI_IFR_SET and EFI_IFR_MAP_OP.
// [Files]  		Setupdata.h, ctrlcond.c, expression.c, hii.c and parse.c
// 
// 14    10/18/12 6:04a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 12    10/10/12 12:41p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 13    2/02/12 2:59a Premkumara
// [TAG]  		EIP75066 
// [Category]  	Improvement
// [Description]  	Support loading defaults for Ordelist controls
// [Files]  		Ordlistbox.c, Uefi21Wapper.c, CtrlCond.c, HiiCallback.c,
// Parse.c, Uefi20Wapper.c, TseUefihiil.h
// 
// 12    2/01/12 4:57a Rajashakerg
// [TAG]  		EIP77256 
// [Category]  	Improvement
// [Description]  	Provide the Support to override the control Condition
// checking() generically. And provide customization to supress the
// controls with Security GUIDed opcode.
// [Files]  		AMITSE.sdl, CommonHelper.c, CtrlCond.c and CtrlCond.h
// 
// 11    11/28/11 2:30a Premkumara
// [TAG]  		EIP75384 
// [Category]  	Improvement
// [Description]  	Suppress the warnings from static code analyzer
// [Files]  		UefiWapper.c, Hii.c, Expression.c, CtrlCond.c, PopupSel.c,
// Minisetupext.c, Menu.c, Date.c, Ezport\Stylecommon.c,
// EzportPlus\StyleCommon.c,
// 
// 10    11/14/11 6:55p Blaines
// [TAG] - EIP 75486 
// [Category]- Function Request
// [Synopsis]- Support grayout condition for readonly controls.
// [Description] - Display readonly controls as grayout, non-selectable.
// [Files]
// AMITSE.sdl, CommonHelper.c, Minisetupext.h, stylecommon.c, Legacy.c,
// date.c, edit.c, label.c, memo.c, menu.c,, numeric.c, ordlistbox.c,
// PopupPassword.c, 
// PopupSel.c, PopupString.c, ResetButton.c, SubMenu.c, Text.c, Time.c,
// UefiAction.c, ctrlcond.c,   
// 
// 9     3/28/11 11:03p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 8     2/03/11 8:19p Madhans
// [TAG] - EIP 50956   
// [Category]- defect
// [Severity]- Mordarate
// [Symptom]- If we leave the Setup page for 2 or more days. The system
// may hang/Crash.
// [Rootcause] - Memory leaks
// [Solution]- Memeory freed.
// [Files] - ctrlcond.c, memo.c and expression.c 
// 
// 7     12/02/10 5:34p Madhans
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
// 6     9/16/10 8:38p Madhans
// Update for TSE 2.10. Refer Changelog.log for more details.
// 
// 8     7/07/10 7:45p Madhans
// Changes to Support Adding Conditions to Suppress or Grayout the Special
// controls.
// 
// 7     6/14/10 7:11p Madhans
// to fix parsing issues.
// 
// 6     3/11/10 5:41p Madhans
// Coding Standards Update
//
// 5     2/19/10 8:38p Madhans
//
// 4     2/19/10 8:35p Madhans
// Function header fix
//
// 3     11/19/09 5:28p Presannar
// Updated TSE include file name to not clash with CORE file
//
// 2     8/11/09 2:27p Presannar
// Added fn EvaluateControlDefault to evaluate the default expression.
//
// 1     7/24/09 6:54p Presannar
//
// 2     3/31/09 4:15p Madhans
// UEFI Wrapper improvments.
//
// 1     1/09/09 2:38p Presannar
// UEFI 2.1 Hii Related Code - Initial Drop
//
// 24    6/03/08 10:25a Madhans
// Boot Only driver and Add/remove TSE CSM support added.
//
// 23    5/15/08 11:30a Madhans
// Rolled back the Control Condition changes regarding the VarGetValue.
// Will be taken care differently.
//
// 21    8/15/07 2:48p Arunkumars
// Added support for vfr compiler 1.88
//
// 20    5/22/07 9:17a Arunkumars
// Added support for vareq
//
// 19    12/04/06 3:13p Arunkumars
// Fix for behaviour of control access field in CONTOL_INFO
//
// 18    7/06/06 6:38p Arunkumars
// Warn fixes
//
// 17    6/15/06 9:34a Arunkumars
// Support to show new pages added at runtime
//
// 16    2/14/06 1:02p Arunkumars
// 1. Added Inconsistentif feature
// 2. We publish two events before and after asking for password (see
// postmgt.c and minisetup.h)
//
// 15    1/23/06 11:16p Stefanor
// Fixed a problem reported by Intel: if the setup question have more than
// one boolean condition for grayoutif,setup question is not behaving
// properly. (If the setup question is under multiple condition of
// suppressif and grayoutif, setup question is working with TSE 1.17.1050)
//
// 14    11/22/05 1:48p Franklynd
// two conditional one after the other where not processed properly. The
// last conditional was always returned.
//
// 13    7/19/05 3:40p Jerryp
// Reduced number of parameters.
// Code spacing cleanup
//
// 12    6/23/05 4:40p Franklynd
// Initializing local variable.
//
// 11    5/27/05 10:12a Jerryp
// Changed exit comparison of while loop
//
// 10    5/25/05 1:41a Jerryp
// Added support for ideqvallist
//
// 9     5/24/05 5:28p Stefanor
// fixed conditional problem for boot manager page (and, or condition)
//
// 8     5/18/05 11:55a Franklynd
// Using variable number , not ID
//
// 7     5/18/05 10:51a Franklynd
// updating variables on the fly from varstore_select and
// varstore_select_pair within the conditional expression
//
// 6     5/16/05 5:09p Franklynd
// 1-Support for multivariable (varstore, varstore_select,
// varstore_select_pair)
// 2-Support of optimal and failsafe defaults.
// 3- support of refresh of controls using their flag information.
// 4- added ORDERED_LIST control/
//
// 5     3/18/05 2:52p Jerryp
// Fixed bug in conditional evaluation expression
//
// 4     3/01/05 3:33p Franklynd
// adding parse of multiple conditions for control.
//
// 3     3/01/05 12:01p Franklynd
// chack password control only if a regular user is loggd in.
// If an admin user is logged in, then don't check password control flags
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
// Name:          CtrlCond.C
//
// Description:
//
//<AMI_FHDR_END>
//*************************************************************************

//---------------------------------------------------------------------------
#include "minisetup.h"
#include "CtrlCond.h"
#include "TseUefiHii.h"
//---------------------------------------------------------------------------

extern VOID EvaluateReadWrite(UINT8 *buf,CONTROL_INFO *ControlInfo,EFI_HII_VALUE *);

UINTN _SkipExpression(UINT8 *ControlCondPtr);

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    CheckControlAccess
//
// Description:   check control flags
//
// Parameter:	    UINT32 ControlAccess
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CheckControlAccess(UINT32 ControlAccess)
{
  UINT8 Cond = COND_NONE;

  if(gPasswordType  == AMI_PASSWORD_USER)
  {
    switch(ControlAccess)
    {
    case CONTROL_ACCESS_ADMIN:  // suppress
      Cond = COND_SUPPRESS;
      break;
    case CONTROL_ACCESS_USER: // grayout (read-only)
      Cond = COND_GRAYOUT;
      break;
    default:
      break;
    }
  }

  return Cond;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    UpdateFinalCondition
//
// Description:
//
// Parameter:	    UINT8 FinalCond, UINT8 Cond
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UpdateFinalCondition(UINT8 FinalCond, UINT8 Cond)
{
  switch(FinalCond)
  {
  case COND_NONE:
    return(Cond);
    break;

  case COND_NOSUBMIT:    
	return(Cond);
	break;
  case COND_SUPPRESS:
  case COND_HIDDEN:
    return(FinalCond);
    break;

  case COND_GRAYOUT:
    if(Cond != COND_NONE)
      return(Cond);
    break;

  case COND_INCONSISTENT:
    return(Cond);
    break;

  }
  return(FinalCond);
}
extern EFI_STATUS _SetValueFromQuestionId(UINT16 QuestionId, UINT16 PageId, EFI_HII_VALUE *Value);
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    CheckControlCondition
//
// Description:
//
// Parameter:	    CONTROL_INFO *controlInfo
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CheckControlCondition( CONTROL_INFO *controlInfo )
{
  EFI_STATUS status = EFI_SUCCESS;
  CONTROL_INFO *tempControlInfo = NULL;
  UINT32 CtrlAccess;
  UINT8 *CondPtr;
  UINT8 *CtrlPtr;
  UINT8 Cond = COND_NONE, FinalCond = COND_NONE;
  UINTN controlInfoLength = 0;
  UINTN offset = 0;
  UINTN	i = 0;
  UINTN ScopeCount = 0;
  EFI_IFR_OP_HEADER *opHeader= (EFI_IFR_OP_HEADER *) NULL;
  EFI_IFR_DEFAULT *Default = (EFI_IFR_DEFAULT *) NULL;

  UINT8 condStack[50];
  UINT8 opcodeStack[50];

  INTN stackIndex = 0;
  INTN inScope = 0;
  EFI_HII_VALUE Value;
  EFI_HII_VALUE Value1;

  BOOLEAN Inside = TRUE;

  CondPtr    = (UINT8 *)controlInfo->ControlConditionalPtr;
  CtrlAccess = controlInfo->ControlFlags.ControlAccess;

  CtrlPtr = (UINT8 *)controlInfo->ControlPtr;
  EfiZeroMem (&Value1, sizeof (EFI_HII_VALUE));
//  EfiZeroMem (&Value, sizeof (EFI_HII_VALUE));
  if(controlInfo->ControlFlags.ControlRWEvaluate)
  {
      do
      {
       opHeader = (EFI_IFR_OP_HEADER*)(CtrlPtr + i);
        switch(opHeader->OpCode)
        {
            case EFI_IFR_READ_OP:
                  EvaluateReadWrite((CtrlPtr + i + opHeader->Length),controlInfo,&Value1);
                  if(Value1.Type != EFI_IFR_TYPE_UNDEFINED){
                     _SetValueFromQuestionId(controlInfo->ControlKey,controlInfo->ControlPageID,&Value1);
                  }
                  break;
            case EFI_IFR_WRITE_OP:
                 EvaluateReadWrite((CtrlPtr + i + opHeader->Length),controlInfo,&Value1);
                break;
            case EFI_IFR_DEFAULT_OP:
                 Default =(EFI_IFR_DEFAULT*)opHeader;
                 if(((EFI_IFR_OP_HEADER*)(CtrlPtr + i + opHeader->Length))->OpCode == EFI_IFR_VALUE_OP){
                    i += opHeader->Length;
                    opHeader = (EFI_IFR_OP_HEADER*)(CtrlPtr + i);
                    EvaluateReadWrite((CtrlPtr + i + opHeader->Length),controlInfo,&Value1);
                 }
                break;
            case EFI_IFR_END_OP:
			    if(ScopeCount)
			    {
				    ScopeCount--;
			    }
			    break;
        }
        if(opHeader->Scope)
	    {
		    ScopeCount++;
        }
        i += opHeader->Length ;
      }while( ScopeCount);
  }
  if ( CondPtr == NULL )
  {  
    FinalCond = CheckControlAccess(CtrlAccess) ;
    if(FinalCond != COND_NONE)
        return FinalCond ;
    goto DONE ;
  }  

  MemSet(&Value, sizeof(EFI_HII_VALUE),0);
  MemSet(&condStack, 50, 0);
  MemSet(&opcodeStack, 50, 0);

  controlInfoLength = sizeof(CONTROL_INFO);
  tempControlInfo = (CONTROL_INFO*)EfiLibAllocateZeroPool(controlInfoLength);
  if (NULL == tempControlInfo) //EIP-75384 Static code
    return FinalCond;

  MemCopy(tempControlInfo, controlInfo, controlInfoLength);

  status = EvaluateExpression(tempControlInfo, &Value, &offset);
  if(EFI_ERROR(status))
  {
	offset = _SkipExpression(tempControlInfo->ControlConditionalPtr);
    FinalCond = COND_NONE;
	Value.Value.b = FALSE;
  }
  if(Value.Value.b)
  {
    if((((EFI_IFR_OP_HEADER*)CondPtr)->OpCode == EFI_IFR_SUPPRESS_IF_OP) ||
       (((EFI_IFR_OP_HEADER*)CondPtr)->OpCode == EFI_IFR_DISABLE_IF_OP))
    {
      FinalCond = COND_SUPPRESS;
      Inside = FALSE;
    }
    if(((EFI_IFR_OP_HEADER*)CondPtr)->OpCode == EFI_IFR_INCONSISTENT_IF_OP)
    {
      FinalCond = COND_INCONSISTENT;
      Inside = FALSE;
    }
		if(((EFI_IFR_OP_HEADER*)CondPtr)->OpCode == EFI_IFR_NO_SUBMIT_IF_OP)
		{
			FinalCond = COND_NOSUBMIT;
			Inside = FALSE;
		}
  }

  while( Inside )
  {
    switch(*(CondPtr))
    {
    case EFI_IFR_DISABLE_IF_OP:
    case EFI_IFR_SUPPRESS_IF_OP:
      Cond = COND_SUPPRESS;
      break;

    case EFI_IFR_GRAY_OUT_IF_OP:
      Cond = COND_GRAYOUT;
      break;

    case EFI_IFR_INCONSISTENT_IF_OP:
      Cond = COND_INCONSISTENT;
	  Inside = FALSE;
      break;
	case EFI_IFR_NO_SUBMIT_IF_OP:
	  Cond = COND_NOSUBMIT;
	  Inside = FALSE;
      break;
    case EFI_IFR_END_OP:
      if(stackIndex)
      {
        condStack[--stackIndex] = 0;
        opcodeStack[stackIndex] = 0;
      }
      offset = ((EFI_IFR_OP_HEADER*)CondPtr)->Length;
      break;
    case EFI_IFR_FORM_OP:
    case EFI_IFR_FORM_MAP_OP:
	offset += ((EFI_IFR_OP_HEADER*)CondPtr)->Length;
	break;
    default:
      if(CondPtr == (UINT8*)controlInfo->ControlPtr)
      {
        Inside = FALSE;
      }else if(((EFI_IFR_OP_HEADER*)CondPtr)->OpCode != EFI_IFR_END_OP)
      {
        //Skip this Control
        inScope = 0;
        do
        {
          if(((EFI_IFR_OP_HEADER*)((UINT8*)CondPtr + offset))->Scope)
            inScope++;
          offset += ((EFI_IFR_OP_HEADER*)((UINT8*)CondPtr + offset))->Length;
          if(((EFI_IFR_OP_HEADER*)((UINT8*)CondPtr + offset))->OpCode == EFI_IFR_END_OP)
            inScope--;
        }while(inScope > 0);
      }
      break;
    }
    if(((EFI_IFR_OP_HEADER*)CondPtr)->Scope)
    {
      if(Value.Value.b)
      {
        condStack[stackIndex] = Cond;
      }else
      {
        condStack[stackIndex] = COND_NONE;
      }
      opcodeStack[stackIndex++] = ((EFI_IFR_OP_HEADER*)CondPtr)->OpCode;
    }

    tempControlInfo->ControlConditionalPtr = (VOID *)((UINT8 *)tempControlInfo->ControlConditionalPtr + offset);
    CondPtr = (UINT8*)tempControlInfo->ControlConditionalPtr;
    offset = 0;
    Value.Value.b = 0;
    status = EvaluateExpression(tempControlInfo, &Value, &offset);
    if(EFI_ERROR(status))
    {
	  offset = _SkipExpression(tempControlInfo->ControlConditionalPtr);
      FinalCond = COND_NONE;
	  Value.Value.b = FALSE;
    }
  }

  while(stackIndex--)
  {
    Cond = condStack[stackIndex];
    FinalCond = UpdateFinalCondition(FinalCond,Cond);
  }

  // if CtrlAccess is CONTROL_ACCESS_DEFAULT then do not override VFR conditions
  if(CONTROL_ACCESS_DEFAULT != CtrlAccess)
  {
    FinalCond = CheckControlAccess(CtrlAccess);
  }

  if(tempControlInfo)
  {
    MemFreePointer(&tempControlInfo);
  }

DONE:

  if( (FinalCond == COND_NONE) && 
      (controlInfo->ControlFlags.ControlReadOnly == 1) && 
      IsReadOnlyGrayout() )
    {
        FinalCond = COND_GRAYOUT ;
    } 
	
	FinalCond = OEMCheckControlCondition(FinalCond,controlInfo);//EIP 77256 : provide the Support to override the control Condition checking() generically. And provide customization to supress the controls with Security GUIDed opcode.
  return FinalCond;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  CheckInconsistence
//
// Description:   checks Inconsistence
//
// Parameter:	  PAGE_INFO
//
// Return value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckInconsistence( PAGE_INFO *pPageInfo )
{
  CONTROL_INFO *pControlInfo;
  UINTN i;

  //Find out if there is inconsistent value in any of the controls
  for(i=0; i < pPageInfo->PageControls.ControlCount; i++)
  {
    pControlInfo = (CONTROL_INFO*)((UINT8 *)(gControlInfo) + pPageInfo->PageControls.ControlList[i]);
    //Check if there is a CONTROL_TYPE_MSGBOX in this page
    if(pControlInfo->ControlType == CONTROL_TYPE_MSGBOX)
    {
      if(CheckControlCondition(pControlInfo) == COND_INCONSISTENT)
		return DrawMessageBox(pControlInfo, STRING_TOKEN(STR_INCONSISTENT_MSG_TITLE), ((EFI_IFR_INCONSISTENT_IF*)pControlInfo->ControlConditionalPtr)->Error);	      			
    }
  }
  return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	  CheckNoSubmitIf
//
// Description:   checks NoSubmitIf
//
// Parameter:	  VOID
//
// Return value:  BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckNoSubmitIf( VOID)
{
	UINT32 index = 0;

	// Get the Forms
	for ( index = 0; index < gPages->PageCount; index++ )
	{
		PAGE_INFO *pageInfo = (PAGE_INFO*)((UINT8 *)gPages + gPages->PageList[index]);
		UINTN control = 0;

		if(pageInfo->PageHandle == NULL)
		{
			continue;
		}	
			// Get the Controls in each Page
		for(control = 0; control < pageInfo->PageControls.ControlCount; control++)
		{
			CONTROL_INFO *pControlInfo = (CONTROL_INFO *)((UINTN)gControlInfo + pageInfo->PageControls.ControlList[control]);			
		
			if(pControlInfo->ControlType == NO_SUBMIT_IF)			
			{
				if(CheckControlCondition(pControlInfo) == COND_NOSUBMIT)
					return DrawMessageBox(pControlInfo, STRING_TOKEN(STR_NOSUBMITIF_MSG_TITLE), ((EFI_IFR_NO_SUBMIT_IF*)pControlInfo->ControlConditionalPtr)->Error);							
			}
		}		
	}
	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	   DrawMessageBox
//
// Description:   Draw MessageBox 
//
// Parameter:	  CONTROL_INFO, UINT16, EFI_STRING_ID
//		  
// Return value:  	BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN DrawMessageBox(CONTROL_INFO *pControlInfo, UINT16 Title,  EFI_STRING_ID  Error)
{	
        EFI_STATUS Status;
        MSGBOX_DATA *msgbox = NULL;
        CONTROL_INFO dummy;
        AMI_IFR_MSGBOX MsgData;
        ACTION_DATA *action = gApp->Action;

        Status = gMsgBox.Create( &msgbox );
        if ( EFI_ERROR( Status ) )
          return TRUE; // Not able to draw msg box but thats ok dont allow a page switch

        MemSet( &dummy, sizeof(dummy), 0 );
        dummy.ControlHandle = INVALID_HANDLE;

        MsgData.Opcode = 0;
        MsgData.Length = 0;
        MsgData.Title =  Title;
        MsgData.TextHandle = pControlInfo->ControlHandle;
		MsgData.Text = Error;
        dummy.ControlPtr = (VOID *) (&MsgData);
        dummy.ControlFlags.ControlVisible = TRUE;

        Status = gMsgBox.Initialize( msgbox, &dummy );
        if ( EFI_ERROR( Status ) )
        {
          // Not able to draw msg box but thats ok dont allow a page switch
          gMsgBox.Destroy( msgbox, TRUE );;
          return TRUE;
        }

        gMsgBox.SetType( msgbox, MSGBOX_TYPE_OK | MSGBOX_STYLE_LEFT );

        do
        {
          if ( action->Input.Type != ACTION_TYPE_NULL )
            gAction.ClearAction( action );

          gMsgBox.Draw( msgbox );

          if ( gAction.GetAction( action ) != EFI_SUCCESS )
            continue;

          if(gMsgBox.HandleAction( msgbox, action ) == EFI_SUCCESS)
            break;
        }while(1);

        gMsgBox.Destroy( msgbox, TRUE );   
	return TRUE;    
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    CheckOneOfOptionSuppressIf
//
// Description:
//
// Parameter:	    CONTROL_INFO *ParentCtrlInfo, UINT8* CtrlCondPtr
//
// Return value:  UINT8
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CheckOneOfOptionSuppressIf(CONTROL_INFO *ParentCtrlInfo, UINT8* CtrlCondPtr, UINT8* CtrlPtr)
{
  CONTROL_INFO *newCtrlInfo = NULL;
  UINT8 condition = COND_NONE;

  newCtrlInfo = (CONTROL_INFO*)EfiLibAllocateZeroPool(sizeof(CONTROL_INFO));
  if(newCtrlInfo == NULL)
  {
    goto DONE;
  }

  newCtrlInfo->ControlHandle = ParentCtrlInfo->ControlHandle;
  newCtrlInfo->ControlPageID = ParentCtrlInfo->ControlPageID;
  newCtrlInfo->ControlKey = ParentCtrlInfo->ControlKey;
  newCtrlInfo->ControlConditionalPtr = (VOID *)CtrlCondPtr;
  newCtrlInfo->ControlPtr = (VOID *)CtrlPtr;
  condition = CheckControlCondition(newCtrlInfo);
  MemFreePointer(&newCtrlInfo);

DONE:

  return condition;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	    EvaluateControlDefault
//
// Description:
//
// Parameter:	    CONTROL_INFO *CtrlInfo
//
// Return value:  UINT64
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT16 EvaluateControlDefault(CONTROL_INFO *CtrlInfo, UINT64 *Defaults)
{
  CONTROL_INFO *newCtrlInfo = NULL;
  EFI_IFR_OP_HEADER *header = (EFI_IFR_OP_HEADER*)CtrlInfo->ControlPtr;
  EFI_HII_VALUE value;
  UINT16 size = 0;
  UINT32 scope = 0;
  UINTN i = 0;
  UINTN offset = 0;

  newCtrlInfo = (CONTROL_INFO*)EfiLibAllocateZeroPool(sizeof(CONTROL_INFO));
  if(newCtrlInfo == NULL)
  {
    goto DONE;
  }

  newCtrlInfo->ControlHandle = CtrlInfo->ControlHandle;
  newCtrlInfo->ControlPageID = CtrlInfo->ControlPageID;
  newCtrlInfo->ControlKey = CtrlInfo->ControlKey;

  while(header->OpCode != EFI_IFR_DEFAULT_OP)
  {
    i += header->Length;
    header = (EFI_IFR_OP_HEADER*)((UINT8*)header + i);
  }

  newCtrlInfo->ControlConditionalPtr = (VOID *)((UINT8 *)header + header->Length);
  // Set End of Default Scope as ControlPtr
  do
  {
    switch(header->OpCode)
    {
    case EFI_IFR_END_OP:
      scope = scope? --scope : 0;
      break;
    default:
      break;
    }
    scope = header->Scope? ++scope : scope;
    header = (EFI_IFR_OP_HEADER*)((UINT8*)header + header->Length);
  }while(scope > 0);

  newCtrlInfo->ControlPtr = (VOID *)header;
  EvaluateExpression(newCtrlInfo, &value, &offset);
  MemFreePointer(&newCtrlInfo);

  size = (UINT16)GetControlDataLength(CtrlInfo);
  GetDefaultValue(value.Type, &(value.Value), &size, Defaults, (UINT8*)header);//EIP-Support Default in Orderlist

DONE:
  return size;
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
