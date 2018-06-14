//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-20011 American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBase2.c 1     2/07/11 3:35p Markw $
//
// $Revision: 1 $
//
// $Date: 2/07/11 3:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SMMBase/SmmBase2.c $
// 
// 1     2/07/11 3:35p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:		SmmBase2.c
//
// Description:	SmmBase2 Protocol
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "SmmPrivateShared.h"
#if SMM_USE_PI
#include <SmmPi.h>
#include <Protocol\SmmBase2.h>
#include <AmiDxeLib.h>

EFI_SMM_SYSTEM_TABLE2           *gSmstTable2;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure: EfiSmmGetSmstLocation2
//
// Description:	Retruns a pointer to the Smst.
//
// Input: 
//	IN EFI_SMM_BASE_PROTOCOL	*This
//	IN OUT EFI_SMM_SYSTEM_TABLE	**Smst
//
// Output:
//	EFI_STATUS
//		* EFI_SUCCESS - SMST address saved in *Smst.
//		* EFI_INVALID_PARAMETER - Smst = NULL.
//		* EFI_UNSUPPORTED - Not in SMM.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS EfiSmmGetSmstLocation2(
	IN CONST EFI_SMM_BASE2_PROTOCOL	*This,
	IN OUT EFI_SMM_SYSTEM_TABLE2    **Smst
	)
{
	*Smst = gSmstTable2;
	return EFI_SUCCESS;
}

EFI_SMM_BASE2_PROTOCOL gEfiSmmBase2 = {
    NULL,   //This will be updated dynamically.
    EfiSmmGetSmstLocation2
};
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
