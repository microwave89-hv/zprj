//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
//*************************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatCpuPolicyOverride/PfatCpuPolicyOverride.h 1     9/17/12 4:47p Fredericko $
//
// $Revision: 1 $
//
// $Date: 9/17/12 4:47p $
// 
//
//
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:   PfatCpuPolicyOverride.h
//
// Description: Header file for PfatCpuPolicyOverride sub-component
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _PFAT_CPU_POLICY_OVERRIDE_H_
#define _PFAT_CPU_POLICY_OVERRIDE_H_

#if !defined(EDK_RELEASE_VERSION) || (EDK_RELEASE_VERSION < 0x00020000)
#include "EdkIIGluePeim.h"

#include <Token.h>
#include <SetupDataDefinition.h>
#include "PchRegs.h"
#include EFI_PPI_PRODUCER (CpuPlatformPolicy)
#endif

#define SYSTEM_CONFIGURATION_GUID { 0xEC87D643, 0xEBA4, 0x4BB5, 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }

#define PFAT_PUB_KEY_FFS_FILE_RAW_GUID \
    {0x8e295870, 0xd377, 0x4b75, 0xbf, 0xdc, 0x9a, 0xe2, 0xf6, 0xdb, 0xde, 0x22}

#define  KBShift  10
#define  MBShift  20
#define  Disable  0
#define  Enable   1

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

STATIC
EFI_STATUS
PfatCpuPolicyOverrideEndOfPeiCpuPlatformPolicy (
    IN      EFI_PEI_SERVICES          **PeiServices,
    IN      EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN      VOID                      *Ppi
);

//
// Hash functions definitions for pfat
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

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************