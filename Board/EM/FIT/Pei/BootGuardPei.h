//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardPei.h 2     3/07/13 5:43a Bensonlai $
//
// $Revision: 2 $
//
// $Date: 3/07/13 5:43a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardPei.h $
// 
// 2     3/07/13 5:43a Bensonlai
// [TAG]  		EIP117307
// [Category]  	Improvement
// [Description]  	[Boot Guard] Implementation of speed up the post time
// for Chain of Trust
// [Files]  		BootGuardDxe.h, BootGuardPei.c, BootGuardPei.h,
// BpmKmGen.exe, ReserveBootGuardFvMainHashKey.bin
// 
// 1     2/25/13 1:15a Bensonlai
// [TAG]  		EIP114386
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
// for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
// BIOS Writer's Guide - Rev 0.8.1
// [Files]  		BootGuardPei.cif
// BootGuardPei.c
// BootGuardPei.h
// BootGuardPei.dxs
// BootGuardPei.sdl
// BootGuardPei.mak
// PeiCryptLib.lib
// OpensslLib.lib
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name: BootGuardPei.h
//
// Description: Header file for BootGuardPei
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _BOOT_GUARD_PEI_H_
#define _BOOT_GUARD_PEI_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"
#include "CpuAccess.h"
#include "PchAccess.h"
#include "PchPlatformLib.h"
#include "BootGuardLibrary.h"
#include <Token.h>
#endif

#define RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY_FFS_FILE_RAW_GUID \
    {0xcbc91f44, 0xa4bc, 0x4a5b, 0x86, 0x96, 0x70, 0x34, 0x51, 0xd0, 0xb0, 0x53}

#if defined(BUILD_WITH_GLUELIB)
#undef SetMem
VOID *
SetMem (
    OUT VOID *Buffer,
    IN UINTN Length,
    IN UINT8 Value
)
{
    return GlueSetMem (Buffer, Length, Value);
}

#undef CopyMem
VOID *
EFIAPI
CopyMem (
    OUT VOID       *DestinationBuffer,
    IN CONST VOID  *SourceBuffer,
    IN UINTN       Length
)
{
    return GlueCopyMem (DestinationBuffer, SourceBuffer, Length);
}
#endif

//
// Hash functions definitionS
//
UINTN
EFIAPI
Sha256GetContextSize (
    VOID
);

BOOLEAN
EFIAPI
Sha256Init (
    IN OUT  VOID  *Sha256Context
);

BOOLEAN
EFIAPI
Sha256Update (
    IN OUT  VOID        *Sha256Context,
    IN      CONST VOID  *Data,
    IN      UINTN       DataLength
);

BOOLEAN
EFIAPI
Sha256Final (
    IN OUT  VOID   *Sha256Context,
    OUT     UINT8  *HashValue
);

STATIC
EFI_STATUS
BootGuardVerificationForPeiToDxeHandoffEndOfPei (
    IN      EFI_PEI_SERVICES          **PeiServices,
    IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN      VOID                      *Ppi
);

//
// GUID to AMI_BOOT_GUARD Module
//
#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#define AMI_BOOT_GUARD_HOB_GUID \
  { \
    0xb60ab175, 0x498d, 0x429d, 0xad, 0xba, 0xa, 0x62, 0x2c, 0x58, 0x16, 0xe2 \
  }
#else
#define AMI_BOOT_GUARD_HOB_GUID \
  { \
    0xb60ab175, 0x498d, 0x429d, \
    { \
      0xad, 0xba, 0xa, 0x62, 0x2c, 0x58, 0x16, 0xe2 \
    } \
  }
#endif

#pragma pack (1)

typedef struct {
    EFI_HOB_GUID_TYPE EfiHobGuidType;
    UINT8             AmiBootGuardVerificationforPEItoDXEFlag;
} AMI_BOOT_GUARD_HOB;

typedef struct {
    UINT8             BootGuardFvMainHashKey[32];
    UINT32            BootGuardFvMainUsedLength;
} RESERVE_BOOT_GUARD_FV_MAIN_HASH_KEY;

#pragma pack ()

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
