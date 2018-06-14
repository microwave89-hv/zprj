//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CpuSp SMI/CpuSpSmi.h 1     2/07/12 4:00a Davidhsieh $
//
// $Revision: 1 $
//
// $Date: 2/07/12 4:00a $
//
//*********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CpuSp SMI/CpuSpSmi.h $
// 
// 1     2/07/12 4:00a Davidhsieh
//
//*********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:	<CpuSpSmi.h>
//
// Description:	This file contains the Includes, Definitions, typedefs,
//		        Variable and External Declarations, Structure and
//              function prototypes needed for the CpuSpSMI Component
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _CPUSPSMI_H_
#define _CPUSPSMI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <AmiDxeLib.h>
#include <Protocol\SmmBase.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\DevicePath.h>
#include <Protocol\LoadedImage.h>
#include <Token.h>

#define NUM_OF_FIXED_MTRRS      11

#define MSR_IA32_MTRR_CAP       0xFE
  #define VCNT_MASK		        0xFF

#define	MTRR_PHYS_BASE_0		0x200
#define	MTRR_PHYS_MASK_0		0x201
#define	MTRR_PHYS_BASE_1		0x202
#define	MTRR_PHYS_MASK_1		0x203
#define	MTRR_PHYS_BASE_2		0x204
#define	MTRR_PHYS_MASK_2		0x205
#define	MTRR_PHYS_BASE_3		0x206
#define	MTRR_PHYS_MASK_3		0x207
#define	MTRR_PHYS_BASE_4		0x208
#define	MTRR_PHYS_MASK_4		0x209
#define	MTRR_PHYS_BASE_5		0x20a
#define	MTRR_PHYS_MASK_5		0x20b
#define	MTRR_PHYS_BASE_6		0x20c
#define	MTRR_PHYS_MASK_6		0x20d
#define	MTRR_PHYS_BASE_7		0x20e
#define	MTRR_PHYS_MASK_7		0x20f
#define	MTRR_PHYS_BASE_8		0x210
#define	MTRR_PHYS_MASK_8		0x211
#define	MTRR_PHYS_BASE_9		0x212
#define	MTRR_PHYS_MASK_9		0x213
#define	MTRR_FIX_64K_00000		0x250
#define	MTRR_FIX_16K_80000		0x258
#define	MTRR_FIX_16K_A0000		0x259
#define	MTRR_FIX_4K_C0000		0x268
#define	MTRR_FIX_4K_C8000		0x269
#define	MTRR_FIX_4K_D0000		0x26a
#define	MTRR_FIX_4K_D8000		0x26b
#define	MTRR_FIX_4K_E0000		0x26c
#define	MTRR_FIX_4K_E8000		0x26d
#define	MTRR_FIX_4K_F0000		0x26e
#define	MTRR_FIX_4K_F8000		0x26f

typedef struct _EFI_MSR_VALUES {
  UINT16  Index;
  UINT64  Value;
} EFI_MSR_VALUES;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif  // _IDESMM_H_

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
