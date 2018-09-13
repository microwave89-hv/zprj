//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.    **//
//**                                                             **//
//**                     All Rights Reserved.                    **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                       Phone: (770)-246-8600                 **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
//*****************************************************************//
// $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/StyleHook/styleHook3.c $
//
// $Author: Arunsb $
//
// $Revision: 2 $
//
// $Date: 10/18/12 6:20a $
//
//*****************************************************************//
//*****************************************************************//
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/StyleHook/styleHook3.c $
// 
// 2     10/18/12 6:20a Arunsb
// Updated for 2.16.1235 QA submission
// 
// 3     10/10/12 12:40p Arunsb
// Synched the source for v2.16.1232, backup with Aptio
// 
// 1     1/06/11 7:35p Madhans
// [TAG] - EIP 51678 
// [Category]- Enhancment
// [Severity]- Mordarate
// [Symptom]-  If OEMs override the style module parts, If new tse adds
// new style hook then 
// if the OEM has different style module, even if they don't need use the
// hook to avoid 
// compilation issue they need touch their style module to add the new
// hook.
// [RootCause] - The Original Style Hooks are part of Style module itself.
// [Solution]- To create Empty style Hook List in TSE core. This will
// allows the OEM not 
// to change their style module to update newer TSE.
// [Files] - StyleHook Module Part under TSE lite sources. StyleHook.lib
// StyleHookx64.lib tselitebin.sdl
// 
//*****************************************************************//
//*****************************************************************//
//<AMI_FHDR_START>
//
// Name:		StyleHook3.c
//
// Description:	Contains generic or default style functions.
//
//<AMI_FHDR_END>
//**********************************************************************
#include "minisetup.h"


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StyleGetClearScreenColor	
//
// Description:	Function to Get Clear Screen Color
//
// Input:		VOID
//
// Output:		STYLE_CLEAR_SCREEN_COLOR
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN StyleGetClearScreenColor(VOID)
{
	return (EFI_BACKGROUND_BLUE|EFI_WHITE);
}







//*****************************************************************//
//*****************************************************************//
//**                                                             **//
//**        (C)Copyright 1985-2010, American Megatrends, Inc.    **//
//**                                                             **//
//**                       All Rights Reserved.                  **//
//**                                                             **//
//**             5555 Oakbrook Pkwy   , Norcross, GA 30071       **//
//**                                                             **//
//**                       Phone: (770)-246-8600                 **//
//**                                                             **//
//*****************************************************************//
//*****************************************************************//
