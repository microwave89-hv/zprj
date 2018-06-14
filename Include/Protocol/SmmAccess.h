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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmAccess.h 3     2/07/11 3:37p Markw $
//
// $Revision: 3 $
//
// $Date: 2/07/11 3:37p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmAccess.h $
// 
// 3     2/07/11 3:37p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 2     7/08/09 8:01p Markw
// Update headers.
// 
// 1     3/18/07 1:54p Markw
// 
// 2     3/13/06 1:40a Felixp
// 
// 1     1/28/05 12:44p Felixp
// 
// 2     1/18/05 3:22p Felixp
// PrintDebugMessage renamed to Trace
// 
// 1     12/23/04 9:41a Felixp
// 
// 1     1/30/04 10:26a Markw
// 
// 1     1/26/04 3:25p Markw
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name: SmmAccess_h
//
// Description:	This provides north bridge functions to open, close, lock,
//              and describe SMM space.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __SMM_ACCESS_PROTOCOL_H__
#define __SMM_ACCESS_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_ACCESS_PROTOCOL_GUID \
    {0x3792095a,0xe309,0x4c1e,0xaa,0x01,0x85,0xf5,0x65,0x5a,0x17,0xf1}

GUID_VARIABLE_DECLARATION(gEfiSmmAccessProtocolGuid,EFI_SMM_ACCESS_PROTOCOL_GUID);

//Forward Declaration
typedef struct _EFI_SMM_ACCESS_PROTOCOL  EFI_SMM_ACCESS_PROTOCOL;

#ifndef SMM_ACCESS_DEF
#define SMM_ACCESS_DEF

//*******************************************************
//EFI_SMRAM_STATE
//*******************************************************
#define EFI_SMRAM_OPEN      0x00000001
#define EFI_SMRAM_CLOSED    0x00000002
#define EFI_SMRAM_LOCKED    0x00000004
#define EFI_CACHEABLE       0x00000008
#define EFI_ALLOCATED       0x00000010
#define EFI_NEEDS_TESTING               0x00000020
#define EFI_NEEDS_ECC_INITIALIZATION    0x00000040

typedef struct _EFI_SMRAM_DESCRIPTOR {
    EFI_PHYSICAL_ADDRESS    PhysicalStart;
    EFI_PHYSICAL_ADDRESS    CpuStart;
    UINT64                  PhysicalSize;
    UINT64                  RegionState;
} EFI_SMRAM_DESCRIPTOR;

#endif


typedef EFI_STATUS (EFIAPI *EFI_SMM_OPEN) (
    IN EFI_SMM_ACCESS_PROTOCOL  *This,
    IN UINTN                    DescriptorIndex
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_CLOSE) (
    IN EFI_SMM_ACCESS_PROTOCOL  *This,
    IN UINTN                    DescriptorIndex
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_LOCK) (
    IN EFI_SMM_ACCESS_PROTOCOL  *This,
    IN UINTN                    DescriptorIndex
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_CAPABILITIES) (
    IN EFI_SMM_ACCESS_PROTOCOL  *This,
    IN OUT UINTN                *SmramMapSize,
    IN OUT EFI_SMRAM_DESCRIPTOR *SmramMap
);

//**********************************************************************
//<AMI_THDR_START>
//
// Name:        EFI_SMM_ACCESS_PROTOCOL
//
// Description: This provides north bridge functions to open, close, lock,
//              and describe SMM space.
//
// Fields:     Name        Type					Description
//        ------------------------------------------------------------
//        Open			  EFI_SMM_OPEN          Access SMM space when in non-SMM mode.  
//        Close			  EFI_SMM_CLOSE         Close SMM space when in non-SMM mode.
//        Lock			  EFI_SMM_LOCK          Do not allow access to SMM when in non-SMM Mode.
//        GetCapabilities EFI_SMM_CAPABILITIES  Provide information for SMM memory areas.
//        LockState		  BOOLEAN               TRUE if SMM memory is locked.
//        OpenState		  BOOLEAN               TRUE if any SMM memory is opened.
//
//<AMI_THDR_END>
//**********************************************************************
struct _EFI_SMM_ACCESS_PROTOCOL {
    EFI_SMM_OPEN            Open;
    EFI_SMM_CLOSE           Close;
    EFI_SMM_LOCK            Lock;
    EFI_SMM_CAPABILITIES    GetCapabilities;
    BOOLEAN                 LockState;
    BOOLEAN                 OpenState;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
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
