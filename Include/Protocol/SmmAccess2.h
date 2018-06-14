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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmAccess2.h 2     3/04/11 3:35p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:35p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmAccess2.h $
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
// 
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmAccess2.h
//
// Description:
//  This provides north bridge functions to open, close, lock, and describe SMM space.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_ACCESS2_PROTOCOL_H__
#define __SMM_ACCESS2_PROTOCOL_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_ACCESS2_PROTOCOL_GUID \
    {0xc2702b74,0x800c,0x4131,0x87,0x46,0x8f,0xb5,0xb8,0x9c,0xe4,0xac}

GUID_VARIABLE_DECLARATION(gEfiSmmAccess2ProtocolGuid,EFI_SMM_ACCESS2_PROTOCOL_GUID);

//Forward Declaration
typedef struct _EFI_SMM_ACCESS2_PROTOCOL  EFI_SMM_ACCESS2_PROTOCOL;

#ifndef SMM_ACCESS_DEF
#define SMM_ACCESS_DEF

#define EFI_SMRAM_OPEN                  0x00000001
#define EFI_SMRAM_CLOSED                0x00000002
#define EFI_SMRAM_LOCKED                0x00000004
#define EFI_CACHEABLE                   0x00000008
#define EFI_ALLOCATED                   0x00000010
#define EFI_NEEDS_TESTING               0x00000020
#define EFI_NEEDS_ECC_INITIALIZATION    0x00000040

typedef struct _EFI_SMRAM_DESCRIPTOR {
    EFI_PHYSICAL_ADDRESS    PhysicalStart;
    EFI_PHYSICAL_ADDRESS    CpuStart;
    UINT64                  PhysicalSize;
    UINT64                  RegionState;
} EFI_SMRAM_DESCRIPTOR;

#endif

typedef EFI_STATUS (EFIAPI *EFI_SMM_OPEN2)(
    IN EFI_SMM_ACCESS2_PROTOCOL *This
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_CLOSE2)(
    IN EFI_SMM_ACCESS2_PROTOCOL *This
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_LOCK2)(
    IN EFI_SMM_ACCESS2_PROTOCOL *This
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_CAPABILITIES2)(
    IN CONST EFI_SMM_ACCESS2_PROTOCOL  *This,
    IN OUT UINTN                       *SmramMapSize,
    IN OUT EFI_SMRAM_DESCRIPTOR        *SmramMap
);

struct _EFI_SMM_ACCESS2_PROTOCOL {
    EFI_SMM_OPEN2          Open;
    EFI_SMM_CLOSE2         Close;
    EFI_SMM_LOCK2          Lock;
    EFI_SMM_CAPABILITIES2  GetCapabilities;   //Current state of the SMRAM. TRUE if locked.
    BOOLEAN                LockState;         //Current state of the SMRAM. TRUE if open.
    BOOLEAN                OpenState;
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
