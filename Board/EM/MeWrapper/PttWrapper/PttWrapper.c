//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
//
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/PttWrapper/PttWrapper.c 4     11/05/14 6:00a Tristinchou $
//
// $Revision: 4 $
//
// $Date: 11/05/14 6:00a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/PttWrapper/PttWrapper.c $
// 
// 4     11/05/14 6:00a Tristinchou
// [TAG]  		EIP190594
// [Description]  	Avoid install smm protocol with bootservice
// InstallProtocol()
// 
// 3     1/18/13 12:20a Klzhan
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Fix SMM Variable protocol fail.
// [Files]  		PttWrapper.dxs
// PttWrapper.c
// PttWrapper.mak
// PttWrapper.sdl
// PttWrapper.cif
// 
// 2     11/20/12 3:35a Klzhan
// [TAG]  		EIPNone
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	Smm Variable Protocol not installed
// 
// 1     11/07/12 6:21a Klzhan
// 
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:            PttWrapper.c
//
// Description:     Setup Hooks for Tdt.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <EFI.h>
#include <AmiDxeLib.h>
#include <ReferenceCode\ME\SampleCode\Protocol\SmmVariable\SmmVariable.h>


#define EFI_SMM_RUNTIME_SERVICES_TABLE_GUID \
    { 0x395c33fe, 0x287f, 0x413e, { 0xa0, 0x55, 0x80, 0x88, 0xc0, 0xe1, 0xd4, 0x3e } }

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: InSmmFunction
//
// Description: InSmmFunction
//
// Input:      
//
// Output: 
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
InSmmFunction 
(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable 
)
{
    //Modification in PttHciSmm.c uses RuntimeServices' variable service
    //directly, so we don't need to install SmmVariableProtocol in gBS.

    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: PttWrapperEntryPoint
//
// Description: Driver EntryPoint
//
// Input:      
//
// Output: 
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
EFIAPI
PttWrapperEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle, SystemTable);
    InitSmmHandlerEx(ImageHandle, SystemTable, InSmmFunction, NULL);

    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************