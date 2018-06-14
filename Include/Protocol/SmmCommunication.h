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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmCommunication.h 3     4/15/11 4:44p Markw $
//
// $Revision: 3 $
//
// $Date: 4/15/11 4:44p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmCommunication.h $
// 
// 3     4/15/11 4:44p Markw
// Add Inclusion Guards.
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
// Name: SmmCommunicate.h
//
// Description: PI Smm Base Protocol header file.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_COMMUNICATE_PROTOCOL_H__
#define __SMM_COMMUNICATE_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_COMMUNICATION_PROTOCOL_GUID \
    {0xc68ed8e2, 0x9dc6, 0x4cbd, 0x9d, 0x94, 0xdb, 0x65, 0xac, 0xc5, 0xc3, 0x32}

GUID_VARIABLE_DECLARATION(gEfiSmmCommunicationProtocolGuid,EFI_SMM_COMMUNICATION_PROTOCOL_GUID);


#ifndef EFI_SMM_COMM_HDR_DEF
#define EFI_SMM_COMM_HDR_DEF

typedef struct {
    EFI_GUID    HeaderGuid;
    UINTN       MessageLength;
    UINT8       Data[1];
} EFI_SMM_COMMUNICATE_HEADER;

#endif

typedef struct _EFI_SMM_COMMUNICATION_PROTOCOL EFI_SMM_COMMUNICATION_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_SMM_COMMUNICATE2) (
    IN CONST EFI_SMM_COMMUNICATION_PROTOCOL *This,
    IN OUT VOID     *CommBuffer,
    IN OUT UINTN    *CommSize
);

struct _EFI_SMM_COMMUNICATION_PROTOCOL {
    EFI_SMM_COMMUNICATE2 Communicate;
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
