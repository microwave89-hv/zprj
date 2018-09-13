//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**         (C)Copyright 2010, American Megatrends, Inc.        **//
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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/ctrlcond.c $
//
// $Author: Arunsb $
//
// $Revision: 10 $
//
// $Date: 10/18/12 6:00a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/ctrlcond.c $
// 
// 10    10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 9     10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 9     11/01/11 10:54a Madhans
// [TAG]  		EIP51899
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Some Condition evaluation is broken.
// [RootCause]  	VAREQVAL is considering all the variable's size as UINTN.
// [Solution]  	It should based on the size of Variable.
// [Files]  		ctrlcond.c
// 
// 8     3/29/11 1:15p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 7     3/29/11 1:11p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 6     3/23/10 3:39p Blaines
// EIP-36010
// 
// Fix for suppressif used with grayout condition.
// 
// 
// 5     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 6     2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 5     1/09/10 7:26a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 4     6/24/09 6:11p Madhans
// Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
// 
// 3     6/23/09 6:51p Blaines
// Coding standard update, 
// Remove spaces from file header to allow proper chm function list
// creation.
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:08p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 4     4/28/09 9:40p Madhans
// Tse 2.0 Code complete Checkin.
// 
// 3     3/31/09 4:14p Madhans
// UEFI Wrapper improvments.
// 
// 2     1/30/09 6:06p Madhans
// Function headers added. 
// 
// 1     12/18/08 7:59p Madhans
// Intial version of TSE Lite sources
//*****************************************************************//
//*****************************************************************//

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:		ctrlcond.c
//
// Description:	This file contains code for control conditions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"
#include "ctrlcond.h"
#include EFI_PROTOCOL_DEFINITION(Hii)
#include EFI_PROTOCOL_DEFINITION(FormCallback)
extern EFI_HII_PROTOCOL	*gHiiProtocol;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetVarNumFromID
//
// Description: To get var number from ID
//
// Input:		unsigned int ID
//
// Output:		VarCount
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
int GetVarNumFromID(unsigned int ID)
{
    unsigned int i=0;

	while( ( ((VARIABLE_INFO *)((UINT8 *)gVariables + gVariables->VariableList[i]))->VariableID != ID) && (i < gVariables->VariableCount))
		i++;

	return i;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckControlAccess
//
// Description:	To check control flags
//
// Input:		UINT32 ControlAccess
//
// Output:		Condition
//
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
// Procedure:	UpdateFinalCondition
//
// Description:	To finalize the codition flag
//
// Input:		UINT8 FinalCond, UINT8 Cond
//
// Output:		Condition
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 UpdateFinalCondition(UINT8 FinalCond, UINT8 Cond)
{
	switch(FinalCond)
	{
        case COND_NONE:
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
//check condition
#if TSE_SUPPORT_VFRCOMPILE_1_88

static UINT8 Operands[10], StackPos;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	EvaluateOpcode
//
// Description:	To perform the stack operations based on the opcode
//
// Input:		UINT8 OpCode
//
// Output:		void
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID EvaluateOpcode(UINT8 OpCode)
{
    switch(OpCode)
    {
        case EFI_IFR_NOT_OP:
            if(StackPos >= 1) //atleast one operand should be there
            {
                Operands[StackPos-1] = (Operands[StackPos-1] == 0) ? 1:0;
                //No need to change the stack position because the
                //result goes in the operands position
            }
        break;
        case EFI_IFR_AND_OP:
            if(StackPos >= 2)//atleast two oprerands should be there
            {
                Operands[StackPos-2] &= (Operands[StackPos-1]);
                //Move stack position only one down. Result takes the
                //second operands position
                StackPos--;
            }
        break;
        case EFI_IFR_OR_OP:
            if(StackPos >= 2)//atleast two oprerands should be there
            {
                Operands[StackPos-2] |= (Operands[StackPos-1]);
                //Move stack position only one down. Result takes the
                //second operands position
                StackPos--;
            }
        break;
    }
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	GetExpResult
//
// Description: Function to get exp result
//
// Input:	nil
//
// Output:	result
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 GetExpResult()
{
    UINT8 result = 0;

    if(StackPos)
    {
        if(StackPos == 1)
        {
            result = Operands[0];
        }
        else
        {
            //Error condition!!!
        }
    }

    StackPos = 0;

    return result;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckControlCondition
//
// Description:	This function eveluates the condition and retuns the result
//
// Input:		Control Info
//
// Output:		COND_NONE 		- Condition failed.
//				COND_SUPPRESS	- Condition matchs suppress
//				COND_GRAYOUT	- Condition matchs Grayout
//				COND_HIDDEN		- Condition matchs and Hide
//				COND_INCONSISTENT - Inconsistent Condition matchs 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CheckControlCondition( CONTROL_INFO *controlInfo )
{
	// Used to be a long list of parameters
	UINT32 CtrlAccess;
    UINT8 *CondPtr;
    UINT32 i=0;
	UINT32 VarId1, VarId2;
	UINT8 Cond = COND_NONE, FinalCond = COND_NONE;

	UINT32 Val1 = 0, Val2 = 0;
	BOOLEAN Inside = TRUE;

    EFI_IFR_EQ_ID_VAL *IDValPtr;
	EFI_IFR_EQ_ID_LIST *IDListPtr;
	EFI_IFR_EQ_VAR_VAL *VarValPtr;
	EFI_IFR_EQ_ID_ID *IDIDPtr;

	CondPtr    = (UINT8 *)controlInfo->ControlConditionalPtr;
   	CtrlAccess = controlInfo->ControlFlags.ControlAccess;

	if ( CondPtr == NULL )
		return ( CheckControlAccess(CtrlAccess) );

   	VarId1   = controlInfo->ControlConditionalVariable[0];
	VarId2  = controlInfo->ControlConditionalVariable[1];


	while( Inside )
	{
		switch(*(CondPtr+i))
		{
			case EFI_IFR_SUPPRESS_IF_OP:
				if(GetExpResult())
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
				}
				Cond = COND_SUPPRESS;
				break;

			case EFI_IFR_GRAYOUT_IF_OP:
				if(GetExpResult())
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
				}
				Cond = COND_GRAYOUT;
				break;

			case EFI_IFR_HIDDEN_OP:
				if(GetExpResult())
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
				}                 
				Cond =  COND_HIDDEN;
				break;

            case EFI_IFR_INCONSISTENT_IF_OP:
				if(GetExpResult())
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
				}
				Cond = COND_INCONSISTENT;
				break;

			case EFI_IFR_NOT_OP:
			case EFI_IFR_AND_OP:
			case EFI_IFR_OR_OP:
                EvaluateOpcode(*(CondPtr+i));
				break;

			case EFI_IFR_EQ_ID_VAL_OP:
				IDValPtr = (VOID*)(CondPtr+i);
//EIP:36010 - Start
				Val1 = 0;
//EIP:36010 - End
				VarGetValue( VarId1, IDValPtr->QuestionId, IDValPtr->Width, &Val1 );
				Operands[StackPos] = ( (UINT16)Val1 == IDValPtr->Value ) ? 1 : 0 ;
				StackPos++;
				break;

			case EFI_IFR_EQ_ID_LIST_OP:
				IDListPtr = (VOID*)(CondPtr+i);
//EIP:36010 - Start
				Val1 =0;
//EIP:36010 - End
				VarGetValue( VarId1, IDListPtr->QuestionId, IDListPtr->Width, &Val1 );
				for ( Val2 = 0; Val2 < IDListPtr->ListLength; Val2++ )
				{
					if ( IDListPtr->ValueList[Val2] == Val1 )
                    {
                        Operands[StackPos] = 1;//Found a match in the list
						break;
                    }
				}
                if(Val2 >= IDListPtr->ListLength)//Did not find a match
                    Operands[StackPos] = 0;
                StackPos++;
				break;

			case EFI_IFR_EQ_ID_ID_OP:
				IDIDPtr = (VOID*)(CondPtr+i);
//EIP:36010 - Start
				Val1 =0;
				Val2 =0;
//EIP:36010 - End
				VarGetValue( VarId1, IDIDPtr->QuestionId1, IDIDPtr->Width, &Val1 );
				VarGetValue( VarId2, IDIDPtr->QuestionId2, IDIDPtr->Width, &Val2 );
				Operands[StackPos] = (UINT8)(( Val1 == Val2 ) ? 1 : 0);
                StackPos++;
				break;

			case EFI_IFR_EQ_VAR_VAL_OP:
                {
                    CHAR16 VarName[VARIABLE_NAME_LENGTH];
                    UINTN size, *VarVal, Value;
                    EFI_GUID *VarGuid;
                    PAGE_INFO *pageInfo;

    				VarValPtr = (VOID*)(CondPtr+i);

                    //Get the variable name
                    SPrint(VarName, sizeof(VarName), L"%d",VarValPtr->VariableId);

                    //Get the guid
                    pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[controlInfo->ControlPageID]);
                    VarGuid = &(gPageIdInfo[pageInfo->PageIdIndex].PageGuid);

                    //Get the value
                    size = 0;
                    VarVal = (UINTN *)VarGetNvramName(VarName,VarGuid,NULL,&size);
// EIP51899 +>>
                    Value = 0;                    
                    if (VarVal != 0)
                        MemCopy(&Value, VarVal, size);
                    else
                        VarVal = 0;
// EIP51899 <<+
                    // Value = VarVal ? *VarVal : 0;    // EIP51899 -

    				Operands[StackPos] = (UINT8)(( (UINT16)Value == VarValPtr->Value ) ? 1 : 0) ;
                    StackPos++;

                    //Free variable memory
                    MemFreePointer((VOID **)&VarVal);
                }
				break;

			case  EFI_IFR_VARSTORE_SELECT_OP:
				VarId1 = VarId2= GetVarNumFromID(((EFI_IFR_VARSTORE_SELECT*)((char*)CondPtr +i))->VarId);
				break;

			case  EFI_IFR_VARSTORE_SELECT_PAIR_OP:
				VarId1 =  GetVarNumFromID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)CondPtr +i))->VarId);
				VarId2 = GetVarNumFromID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)CondPtr +i))->SecondaryVarId);
				break;

			case EFI_IFR_END_IF_OP:
			default:
				Inside = FALSE;
				break;
		}

		// go to next opcode
		i +=(UINT32)*(CondPtr+i+1);
	}

	if(GetExpResult())
	     FinalCond = UpdateFinalCondition(FinalCond,Cond);

	// if CtrlAccess is CONTROL_ACCESS_DEFAULT then do not override VFR conditions
	if(CONTROL_ACCESS_DEFAULT != CtrlAccess)
	{
		FinalCond = CheckControlAccess(CtrlAccess);
	}

    return FinalCond;
}
#else
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckControlCondition
//
// Description:	This function eveluates the condition and retuns the result
//
// Input:		Control Info
//
// Output:		COND_NONE 		- Condition failed.
//				COND_SUPPRESS	- Condition matchs suppress
//				COND_GRAYOUT	- Condition matchs Grayout
//				COND_HIDDEN		- Condition matchs and Hide
//				COND_INCONSISTENT - Inconsistent Condition matchs 
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINT8 CheckControlCondition( CONTROL_INFO *controlInfo )
{
	// Used to be a long list of parameters
	UINT32 CtrlAccess;
	UINT8 *CtrlPtr;
	UINT32 CtrlVar, CtrlVar2;
	UINT8 *CondPtr;

	UINT8 Cond = COND_NONE, FinalCond = COND_NONE,	tempresult = FALSE, result = FALSE, x;
	UINT8 OpStack[5], StackPos = 0;
	UINT32 i=0,Var = 0, Var2 = 0;
	EFI_IFR_EQ_ID_VAL *IDValPtr;
	EFI_IFR_EQ_ID_LIST *IDListPtr;
	EFI_IFR_EQ_VAR_VAL *VarValPtr;
	EFI_IFR_EQ_ID_ID *IDIDPtr;

	BOOLEAN Inside = TRUE;

	UINT32 tCtrlVar, tCtrlVar2;

	CtrlAccess = controlInfo->ControlFlags.ControlAccess;
	CtrlPtr    = (UINT8 *)controlInfo->ControlPtr;
	tCtrlVar   =
	CtrlVar    = controlInfo->ControlConditionalVariable[0];
	tCtrlVar2  =
	CtrlVar2   = controlInfo->ControlConditionalVariable[1];
	CondPtr    = (UINT8 *)controlInfo->ControlConditionalPtr;

	if ( CondPtr == NULL )
		return ( CheckControlAccess(CtrlAccess) );


	while( Inside )
	{
		Var = 0 ;

		switch(*(CondPtr+i))
		{
			// note: (size matters!!!!) this code is done before the while loop  
			case EFI_IFR_SUPPRESS_IF_OP:     // supress_if
				if(result)
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
					result = COND_NONE;
				}

				Cond = COND_SUPPRESS;
				break;

			case EFI_IFR_GRAYOUT_IF_OP:     // grayout_if
				if(result)
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
					result = COND_NONE;
				}
				Cond = COND_GRAYOUT;
				break;

			case EFI_IFR_HIDDEN_OP:    // hidden _if
				if(result)
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
					result = COND_NONE;
				}                 
				Cond =  COND_HIDDEN;
				break;

			case EFI_IFR_NOT_OP:
				/*StackPos++;               
				  OpStack[StackPos] = EFI_IFR_NOT_OP ;
				  continue;
				 */
				//break; // on purpose to go on code below (size matters)

			case EFI_IFR_AND_OP:
				/*StackPos++;
				  OpStack[StackPos] = EFI_IFR_AND_OP ;
				  tempresult = result;
				  continue;
				 */
				//break;  // on purpose to go on code below (size matters)

			case EFI_IFR_OR_OP:
				StackPos++;
				OpStack[StackPos] =  *(CondPtr+i) ;//EFI_IFR_OR_OP;
				tempresult = result;
				i +=(UINT32)*(CondPtr+i+1);
				continue;
				break;

			case EFI_IFR_EQ_ID_VAL_OP:
				IDValPtr = (VOID*)(CondPtr+i);
				VarGetValue( tCtrlVar, IDValPtr->QuestionId, IDValPtr->Width, &Var );
				result = ( (UINT16)Var == IDValPtr->Value ) ? 1 : 0 ;
				break;

			case EFI_IFR_EQ_ID_LIST_OP:
				IDListPtr = (VOID*)(CondPtr+i);
				VarGetValue( tCtrlVar, IDListPtr->QuestionId, IDListPtr->Width, &Var );
				for ( Var2 = 0; Var2 < IDListPtr->ListLength; Var2++ )
				{
					result = (UINT8)( IDListPtr->ValueList[Var2] == Var );
					if ( result )
						break;
				}
				break;

			case EFI_IFR_EQ_ID_ID_OP:
				IDIDPtr = (VOID*)(CondPtr+i);
				VarGetValue( tCtrlVar, IDIDPtr->QuestionId1, IDIDPtr->Width, &Var );
				VarGetValue( tCtrlVar2, IDIDPtr->QuestionId2, IDIDPtr->Width, &Var2 );
				result = (UINT8)(( Var == Var2 ) ? TRUE : FALSE); //WARN FIX

				//result = ; 
				break;

			case EFI_IFR_EQ_VAR_VAL_OP:
                {
                    CHAR16 VarName[VARIABLE_NAME_LENGTH];
                    UINTN size, *VarVal, Value;
                    EFI_GUID *VarGuid;
                    PAGE_INFO *pageInfo;

    				VarValPtr = (VOID*)(CondPtr+i);

                    //Get the variable name
                    SPrint(VarName, sizeof(VarName), L"%d",VarValPtr->VariableId);

                    //Get the guid
                    pageInfo = (PAGE_INFO *)((UINTN)gApplicationData + gPages->PageList[controlInfo->ControlPageID]);
                    VarGuid = &(gPageIdInfo[pageInfo->PageIdIndex].PageGuid);

                    //Get the value
                    size = 0;
                    VarVal = (UINTN *)VarGetNvramName(VarName,VarGuid,NULL,&size);
                    Value = VarVal ? *VarVal : 0;

    				result = (UINT8)(( (UINT16)Value == VarValPtr->Value ) ? TRUE : FALSE) ; //WARN FIX

                    //Free variable memory
                    MemFreePointer((VOID **)&VarVal);
                }
				break;

			case  EFI_IFR_VARSTORE_SELECT_OP:
				tCtrlVar = tCtrlVar2= GetVarNumFromID(((EFI_IFR_VARSTORE_SELECT*)((char*)CondPtr +i))->VarId);
				// franklyn added next two lines for testing 1/10/2006
				i +=(UINT32)*(CondPtr+i+1);
				continue;
				break;

			case  EFI_IFR_VARSTORE_SELECT_PAIR_OP:
				tCtrlVar =  GetVarNumFromID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)CondPtr +i))->VarId);
				tCtrlVar2 = GetVarNumFromID(((EFI_IFR_VARSTORE_SELECT_PAIR*)((char*)CondPtr +i))->SecondaryVarId);
				// franklyn added next two lines for testing 1/10/2006
				i +=(UINT32)*(CondPtr+i+1);
				continue;
				break;

			case EFI_IFR_INCONSISTENT_IF_OP:     // grayout_if
				if(result)
				{
					FinalCond = UpdateFinalCondition(FinalCond,Cond);
					result = COND_NONE;
				}
				Cond = COND_INCONSISTENT;
				break;

			case EFI_IFR_END_IF_OP:
			default:
				Inside = FALSE;
				break;
		}

		// go to next opcode
		i +=(UINT32)*(CondPtr+i+1);

		if(StackPos !=0)
		{  
			// process stack operation with result and, if necessary, tempresult
			switch(OpStack[StackPos])
			{
				case EFI_IFR_AND_OP:
					result = tempresult & result; 
					break;

				case EFI_IFR_OR_OP:
					result = tempresult | result;
					break;

				case EFI_IFR_NOT_OP:
					result = !result;
					if(StackPos !=1)
					{
						x =result;
						result = tempresult; 
						tempresult = x;
					}
					break;

				default :
					// wrong opcode!!!  abort parsing and return condition false
					return COND_NONE;
					break;
			}

			StackPos--;
		}		   
	}

	if(result)
	     FinalCond = UpdateFinalCondition(FinalCond,Cond);

	// if CtrlAccess is CONTROL_ACCESS_DEFAULT then do not override VFR conditions
	if(CONTROL_ACCESS_DEFAULT != CtrlAccess)
	{
		FinalCond = CheckControlAccess(CtrlAccess);
	}

		return FinalCond;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	CheckInconsistence
//
// Description:	check for inconsistancy
//
// Input:	PAGE_INFO *pPageInfo
//
// Output:	TRUE/FALSE
//
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
			{
				//Draw message box
				EFI_STATUS Status;
				MSGBOX_DATA *msgbox = NULL;
				CONTROL_INFO dummy;
				AMI_IFR_MSGBOX MsgData;
				ACTION_DATA *action = gApp->Action;

				Status = gMsgBox.Create( &msgbox );
				if ( EFI_ERROR( Status ) )
					return TRUE; // Not able to draw msg box but thats ok dont allow a page switch

				MemSet( &dummy, sizeof(dummy), 0 );
				dummy.ControlHandle = (VOID*)(UINTN)INVALID_HANDLE;

				MsgData.Opcode = 0;
				MsgData.Length = 0;
				MsgData.Title =  STRING_TOKEN(STR_INCONSISTENT_MSG_TITLE);
				MsgData.TextHandle = pControlInfo->ControlHandle; 
				MsgData.Text = ((EFI_IFR_INCONSISTENT*)pControlInfo->ControlConditionalPtr)->Popup ; //pControlInfo->ControlHelp;

				dummy.ControlPtr = (VOID*) (&MsgData);
				dummy.ControlFlags.ControlVisible = TRUE;

				Status = gMsgBox.Initialize( msgbox, &dummy );
				if ( EFI_ERROR( Status ) )
				{
					gMsgBox.Destroy( msgbox, TRUE );;
					return TRUE; // Not able to draw msg box but thats ok dont allow a page switch
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
					DoRealFlushLines();
				}while(1);

				gMsgBox.Destroy( msgbox, TRUE );
				
				return TRUE;
			}
		}
	}
	return FALSE;
}
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	   CheckNoSubmitIf
//
// Description:   checks NoSubmitIf
//
// Parameter:	    VOID
//
// Return value:  	BOOLEAN
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
BOOLEAN CheckNoSubmitIf( VOID)
{
	//NO_SUBMIT_IF is Unsupport in 2.0
    return FALSE;
}

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
