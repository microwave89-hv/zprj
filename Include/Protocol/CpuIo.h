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

//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/CpuIo.h 3     4/15/11 2:37p Artems $
//
// $Revision: 3 $
//
// $Date: 4/15/11 2:37p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Core/Include/Protocol/CpuIo.h $
// 
// 3     4/15/11 2:37p Artems
// EIP 56523: Added support for PI specification v 1.2
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     6/01/05 4:58p Markw
// 
//**********************************************************************
// $Header: /Alaska/BIN/Core/Include/Protocol/CpuIo.h 3     4/15/11 2:37p Artems $Revision: $
//
// $Date: 4/15/11 2:37p $
//**********************************************************************
// Revision History
// ----------------
// $Log:
// 
//**********************************************************************

//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    CpuIo.h
//
// Description: 
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __EFI_CPU_IO_PROTOCOL_H__
#define __EFI_CPU_IO_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <EFI.h>
#include <Protocol/CpuIo2.h>

#define EFI_CPU_IO_PROTOCOL_GUID  \
    { 0xB0732526, 0x38C8, 0x4b40, 0x88, 0x77, 0x61, 0xC7, 0xB0, 0x6A, 0xAC, 0x45 }

GUID_VARIABLE_DECLARATION(gEfiCpuIoProtocolGuid, EFI_CPU_IO_PROTOCOL_GUID);

typedef EFI_CPU_IO2_PROTOCOL EFI_CPU_IO_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

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
