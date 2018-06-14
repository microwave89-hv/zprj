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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmBase2.h 2     3/04/11 3:35p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmBase2.h $
// 
// 2     3/04/11 3:35p Markw
// Update headers.
// 
// 1     2/07/11 4:03p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		mm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmBase2.h
//
// Description:	PI Smm Base Protocol header file.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_BASE2_PROTOCOL_H__
#define __SMM_BASE2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#include <SmmPi.h>

#define EFI_SMM_BASE2_PROTOCOL_GUID \
    {0xf4ccbfb7,0xf6e0,0x47fd,0x9d,0xd4,0x10,0xa8,0xf1,0x50,0xc1,0x91} 

GUID_VARIABLE_DECLARATION(gEfiSmmBase2ProtocolGuid,EFI_SMM_BASE2_PROTOCOL_GUID);

typedef struct _EFI_SMM_BASE2_PROTOCOL  EFI_SMM_BASE2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_INSIDE_OUT2)(
    IN CONST EFI_SMM_BASE2_PROTOCOL  *This,
    OUT BOOLEAN                      *InSmram
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_GET_SMST_LOCATION2)(
    IN CONST EFI_SMM_BASE2_PROTOCOL  *This,
    IN OUT EFI_SMM_SYSTEM_TABLE2     **Smst
);

struct _EFI_SMM_BASE2_PROTOCOL {
    EFI_SMM_INSIDE_OUT2         InSmm;
    EFI_SMM_GET_SMST_LOCATION2  GetSmstLocation;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
