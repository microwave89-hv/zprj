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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmCpuIo2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmCpuIo2.h $
// 
// 2     3/04/11 3:36p Markw
// Update headers.
// 
// 1     2/07/11 4:04p Markw
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
// Name: SmmCpuIo2.h
//
// Description:	Smm CPU IO Protocol
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _SMM_CPU_IO2_H_
#define _SMM_CPU_IO2_H_
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_CPU_IO2_PROTOCOL_GUID \
  { 0x3242A9D8, 0xCE70, 0x4AA0, 0x95, 0x5D, 0x5E, 0x7B, 0x14, 0x0D, 0xE4, 0xD2 }

GUID_VARIABLE_DECLARATION(gEfiSmmCpuIo2ProtocolGuid, EFI_SMM_CPU_IO2_PROTOCOL_GUID);

typedef struct _EFI_SMM_CPU_IO2_PROTOCOL  EFI_SMM_CPU_IO2_PROTOCOL;

#ifndef EFI_SMM_IO_WIDTH_DEF
#define EFI_SMM_IO_WIDTH_DEF
typedef enum {
    SMM_IO_UINT8 = 0,
    SMM_IO_UINT16 = 1,
    SMM_IO_UINT32 = 2,
    SMM_IO_UINT64 = 3
} EFI_SMM_IO_WIDTH;
#endif

typedef EFI_STATUS (EFIAPI *EFI_SMM_CPU_IO2)(
    IN     CONST EFI_SMM_CPU_IO2_PROTOCOL  *This,
    IN     EFI_SMM_IO_WIDTH                Width,
    IN     UINT64                          Address,
    IN     UINTN                           Count,
    IN OUT VOID                            *Buffer
    );

typedef struct {
    EFI_SMM_CPU_IO2  Read;
    EFI_SMM_CPU_IO2  Write;
} EFI_SMM_IO_ACCESS2;

struct _EFI_SMM_CPU_IO2_PROTOCOL {
    EFI_SMM_IO_ACCESS2 Mem;
    EFI_SMM_IO_ACCESS2 Io;
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
