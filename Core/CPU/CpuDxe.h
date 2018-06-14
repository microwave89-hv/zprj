//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuDxe.h 2     1/14/13 1:54a Crystallee $
//
// $Revision: 2 $
//
// $Date: 1/14/13 1:54a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuDxe.h $
// 
// 2     1/14/13 1:54a Crystallee
// [TAG]  		EIP111199
// [Category]  	Improvement
// [Description]  	Provide variable data which constains number of P
// states support.
// 
// 1     2/07/12 3:58a Davidhsieh
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	CpuDxe.h
//
// Description:	Cpu Dxe header file.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __CPU_DXE_H__
#define __CPU_DXE_H__

#include <AmiHobs.h>
#include <Protocol\Cpu.h>
#include <Protocol\MpService\MpService.h>
#include <Protocol\AmiCpuInfo2.h>
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

// Define structures used and referenced in this file
typedef struct{
	UINT16 NumberOfPStates;
} P_STATES_DATA;

typedef struct{
	UINT32 MemAddress, MemLength;
} system_memory_struc;

EFI_STATUS EfiCpuFlushDataCache (
    IN EFI_CPU_ARCH_PROTOCOL    *This,
    IN EFI_PHYSICAL_ADDRESS     Start,
    IN UINT64                   Length,
    IN EFI_CPU_FLUSH_TYPE       FlushType);

EFI_STATUS EfiCpuSetMemoryAttributes (
    IN EFI_CPU_ARCH_PROTOCOL    *This,
    IN EFI_PHYSICAL_ADDRESS     BaseAddress,
    IN UINT64                   Length,
    IN UINT64                   Attributes);

extern EFI_MP_SERVICES_PROTOCOL *gEfiMpServicesProtocol;

//APIC ID
//CPU NUM
#define PRIVATE_INFO_NUM_OF_CPU_DATA 2

typedef struct {
    AMI_CPU_INFO_2_PROTOCOL AmiCpuInfo2;
//??? Determine max structure size of UINT32s
    //  UINT32 # of populated Sockets 0
    //  ---------------------
    //  ---------------------
    //  ---Socket #0---
    //  UINT32 # of Cores
    //   ---Core #0---
    //  UINT32 # of Threads
    //   ---Thread #0---
    //  UINT32 APIC ID
    //  UINT32 CPU Num
    //   ---Thread #1---
    //  UINT32 APIC ID
    //  UINT32 CPU Num
    //  ---Core #1---
    //  ....
    //  ---------------------
    //  ---------------------
    //  ---Socket #1---
    //  UINT32 # of Cores
    //  ---Core # 0---
    //  UINT32 # of Threads
    //  ---Thread #0---
    //  ....
} PRIVATE_AMI_CPU_INFO_2_PROTOCOL;

extern PRIVATE_AMI_CPU_INFO_2_PROTOCOL *gPrivateAmiCpuInfo2;

typedef struct _AMI_BEFORE_CPU_RC_PROTOCOL AMI_BEFORE_CPU_RC_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *PLATFORM_CPU_DXE_POLICY_OVERWRITE) (
  IN AMI_BEFORE_CPU_RC_PROTOCOL    *This
  
  );

typedef struct _AMI_BEFORE_CPU_RC_PROTOCOL {
	PLATFORM_CPU_DXE_POLICY_OVERWRITE		PlatformCpuDxePolicyOverwrite;
};

VOID CpuDxeMiscFuncs(VOID);

#if PERF_TUNE_SUPPORT == 1

EFI_STATUS IntelXtuFillCpuDataCallBack(
    IN EFI_EVENT    Event,
    IN VOID         *Context
);

#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
