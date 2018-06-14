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
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG2/Common/TCGSmm/TCGSmm.h 1     4/21/14 2:18p Fredericko $
//
// $Revision: 1 $
//
// $Date: 4/21/14 2:18p $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG2/Common/TCGSmm/TCGSmm.h $
// 
// 1     4/21/14 2:18p Fredericko
// 
// 1     10/08/13 12:05p Fredericko
// Initial Check-In for Tpm-Next module
// 
// 1     7/10/13 5:57p Fredericko
// [TAG]  		EIP120969
// [Category]  	New Feature
// [Description]  	TCG (TPM20)
// 
// 5     8/09/11 6:28p Fredericko
// [TAG]  		EIP66468
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	1. Changes for Tcg Ppi 1.2 support. 
// [Files]  		1 TcgSmm.h
// 2.TcgSmm.c
// 3.Tcg_ppi1_2.asl
// 4. AmiTcgNvflagsSample.c
// 5. AmiTcgPlatformPeiLib.c
// 6. AmiTcgPlatformDxe.sdl
// 7. AmiTcgPlatformDxe.c
// 
// 4     7/25/11 3:18a Fredericko
// [TAG]  		EIP65177
// [Category]  	Spec Update
// [Severity]  	Minor
// [Description]  	TCG Ppi Sec ver 1.2 update
// 
// 3     8/04/10 5:08p Fredericko
// 
// 2     5/20/10 8:52a Fredericko
// Added Header defined switches
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: TCGSmm.h
//
// Description:
// Header file for TCGSMM subcomponent
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _TCGSMM_H_
#define _TCGSMM_H_

#include <AmiDxeLib.h>
#include <Protocol\SmmThunk.h>
#include <Protocol\SmmBase.h>
#include <Protocol\DevicePath.h>
#include <Protocol\LoadedImage.h>
#include <Protocol\SmmSwDispatch.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <HOB.h>
#include "..\TCGMisc.h"


#define AMI_TCG_PLATFORM_PROTOCOL_GUID\
    {0x8c939604, 0x700, 0x4415, 0x9d, 0x62, 0x11, 0x61, 0xdb, 0x81, 0x64, 0xa6}

EFI_GUID        SwDispatchProtocolGuid     = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
EFI_GUID        SmmtcgefiOsVariableGuid    = AMI_TCG_EFI_OS_VARIABLE_GUID;
EFI_GUID        SmmFlagsStatusguid         = AMI_TCG_CONFIRMATION_FLAGS_GUID;
extern EFI_GUID gEfiSmmBaseProtocolGuid;
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
