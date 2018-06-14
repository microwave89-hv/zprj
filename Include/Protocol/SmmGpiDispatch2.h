//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmGpiDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmGpiDispatch2.h $
// 
// 2     3/04/11 3:36p Markw
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
// Name: SmmGpiDispatch2.h
//
// Description:	SMM GPI Dispatch Protocol header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_GPI_DISPATCH2_PROTOCOL_H__
#define __SMM_GPI_DISPATCH2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <SmmPi.h>

#define EFI_SMM_GPI_DISPATCH2_PROTOCOL_GUID \
    {0x25566b03, 0xb577, 0x4cbf, 0x95, 0x8c, 0xed, 0x66, 0x3e, 0xa2, 0x43, 0x80}

GUID_VARIABLE_DECLARATION(gEfiSmmGpiDispatch2ProtocolGuid,EFI_SMM_GPI_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_GPI_DISPATCH_PROTOCOL EFI_SMM_GPI_DISPATCH_PROTOCOL;

typedef struct {
    //A bit mask of 64 possible GPIs that can generate an SMI.  Bit 0 corresponds to logical 
    //GPI[0], 1 corresponds to logical GPI[1], and so on.
    UINT64 GpiNum;
} EFI_SMM_GPI_REGISTER_CONTEXT;

typedef struct _EFI_SMM_GPI_DISPATCH2_PROTOCOL EFI_SMM_GPI_DISPATCH2_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_GPI_REGISTER2)(
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL  *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2    DispatchFunction,
    IN CONST EFI_SMM_GPI_REGISTER_CONTEXT    *RegisterContext,
    OUT      EFI_HANDLE                      *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_GPI_UNREGISTER2)(
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                      DispatchHandle
);

struct _EFI_SMM_GPI_DISPATCH2_PROTOCOL {
    EFI_SMM_GPI_REGISTER2    Register;
    EFI_SMM_GPI_UNREGISTER2  UnRegister;
    UINTN                   NumSupportedGpis;
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
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
