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
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/ctrlcond.h $
//
// $Author: Arunsb $
//
// $Revision: 7 $
//
// $Date: 10/18/12 6:00a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/ctrlcond.h $
// 
// 7     10/18/12 6:00a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 7     10/10/12 12:39p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 6     3/29/11 1:15p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 5     3/29/11 1:13p Madhans
// [TAG]  		EIP56414 
// [Category]  	Improvement
// [Description]  	TSE: Support for EFI_IFR_NO_SUBMIT_IF opcode
// [Files]  		Callback.c, FakeToken.c, AMITSEstr.uni, Parse.c, CtrlCond.c,
// CtrlCond.h, ctrlcond.h, ctrlcond.c
// 
// 4     2/19/10 1:04p Madhans
// Updated for TSE 2.01. Refer Changelog.log for File change history.
// 
// 5     2/19/10 8:20a Mallikarjunanv
// updated year in copyright message
// 
// 4     1/09/10 7:25a Mallikarjunanv
// Updated TSE2.01 Release sources with coding standards
// 
// 3     6/16/09 2:16p Presannar
// Added File Headers for Header Files
// 
// 2     6/12/09 7:44p Presannar
// Initial implementation of coding standards for AMITSE2.0
// 
// 1     6/04/09 8:05p Madhans
// 
// 1     4/28/09 11:08p Madhans
// Tse 2.0 Code complete Checkin.
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
// Name:		ctrlcond.h
//
// Description:	Header file for control conditions 
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "minisetup.h"

//definitions
#define COND_NONE			0x0
#define COND_SUPPRESS		0x1
#define COND_HIDDEN			0x2
#define COND_GRAYOUT		0x3
#define COND_INCONSISTENT	0x4

// functions
UINT8 CheckControlCondition( CONTROL_INFO *controlInfo );
BOOLEAN CheckInconsistence( PAGE_INFO *pPageInfo );
BOOLEAN CheckNoSubmitIf( VOID); // EIP : NO_SUBMIT_IF

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
