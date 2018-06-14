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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPei.h 4     8/05/14 2:21a Crystallee $
//
// $Revision: 4 $
//
// $Date: 8/05/14 2:21a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/CPU Core/CpuPei.h $
// 
// 4     8/05/14 2:21a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	For backward compatible, add old MTRR setting method
// back. Change new MTRR setting method to Policy2.
// 
// 3     7/08/14 3:35a Crystallee
// [TAG]  		EIPNone
// [Category]  	Improvement
// [Description]  	Add all the possible methods to describing memory in
// MTRRS.
// [Files]  		CpuPei.c, CpuPei.h, CpuPeiFuncs.c
// 
// 2     9/05/12 1:40a Davidhsieh
// Rename PEI_IFFS_TRANSITION_START_PPI_GUID to
// PEI_RAPID_START_TRANSITION_START_PPI_GUID
// 
// 1     2/07/12 3:58a Davidhsieh
//
//
//**********************************************************************

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
// Name:	CpuPei.h
//
// Description:	Cpu PEI header file.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __CPU_PEI_H__
#define __CPU_PEI_H__

#ifdef __cplusplus
extern "C" {
#endif

#define IED_SIZE	0x400000
#define VariableMtrrCount 10

#define SIZE_1M        0x100000
#define SIZE_64M      0x4000000
#define SIZE_128M     0x8000000
#define SIZE_256M    0x10000000
#define SIZE_512M    0x20000000
#define SIZE_1G      0x40000000
#define SIZE_2G      0x80000000
#define SIZE_4G     0x100000000
#define SIZE_8G     0x200000000
#define SIZE_16G    0x400000000

//Chagned in IvyBridge RC 0.8
//#define PEI_CACHE_PPI_GUID \
//  {0xc153205a, 0xe898, 0x4c24, 0x86, 0x89, 0xa4, 0xb4, 0xbc, 0xc5, 0xc8, 0xa2}
#define PEI_CACHE_PPI_GUID \
  {0x9be4bc2, 0x790e, 0x4dea, 0x8b, 0xdc, 0x38, 0x5, 0x16, 0x98, 0x39, 0x44}

#define AMI_INTERNAL_UCODE_HOB_GUID \
    {0x94567c6f, 0xf7a9, 0x4229, 0x13, 0x30, 0xfe, 0x11, 0xcc, 0xab, 0x3a, 0x11}

#define PEI_RAPID_START_TRANSITION_START_PPI_GUID \
  { \
    0xde8f2878, 0x36d5, 0x498e, 0xba, 0x59, 0x16, 0x8c, 0x26, 0x47, 0xb3, 0x35 \
  }

typedef struct {
    EFI_HOB_GUID_TYPE   EfiHobGuidType;    
	UINT32  uCodeAddr;
} AMI_INTERNAL_UCODE_HOB;

typedef enum _EFI_MEMORY_CACHE_TYPE
{
  EfiCacheTypeUncacheable   = 0,
  EfiCacheTypeWriteCombining= 1,
  EfiCacheTypeReserved2     = 2,
  EfiCacheTypeReserved3     = 3,
  EfiCacheTypeWriteThrough  = 4,
  EfiCacheTypeWriteProtected= 5,
  EfiCacheTypeWriteBack     = 6,
  EfiCacheTypeMaximumType   = 7
} EFI_MEMORY_CACHE_TYPE;


typedef struct _PEI_CACHE_PPI PEI_CACHE_PPI;

//
// *******************************************************
// PEI_SET_CACHE_PPI
// *******************************************************
//
typedef
EFI_STATUS
(EFIAPI *PEI_SET_CACHE_PPI) (
  IN  EFI_PEI_SERVICES                  **PeiServices,
  IN  PEI_CACHE_PPI                     * This,
  IN  EFI_PHYSICAL_ADDRESS              MemoryAddress,
  IN  UINT64                            MemoryLength,
  IN  EFI_MEMORY_CACHE_TYPE             MemoryCacheType
  );

//
// *******************************************************
// PEI_RESET_CACHE_PPI
// *******************************************************
//
typedef
EFI_STATUS
(EFIAPI *PEI_RESET_CACHE_PPI) (
  IN  EFI_PEI_SERVICES                  **PeiServices,
  IN PEI_CACHE_PPI                      * This
  );

//
// *******************************************************
// PEI_ACTIVATE_CACHE_PPI
// *******************************************************
//  
typedef
EFI_STATUS
(EFIAPI *PEI_ACTIVATE_CACHE_PPI) (
  IN  EFI_PEI_SERVICES                  **PeiServices,
  IN PEI_CACHE_PPI                      * This
  );
  
//
// *******************************************************
// PEI_CACHE_PPI
// *******************************************************
//
typedef struct _PEI_CACHE_PPI {
  PEI_SET_CACHE_PPI   SetCache;
  PEI_RESET_CACHE_PPI ResetCache;
  PEI_ACTIVATE_CACHE_PPI ActivateCache;
} PEI_CACHE_PPI;
  
typedef struct {
    UINT64  Base;
    UINT64  Len;
} MEMORY_MAP;

EFI_STATUS InitMtrrPolicy1 (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN MEMORY_MAP                   *WbMap,
    IN MEMORY_MAP                   *UcMap,
    IN UINT64                       Above4GMemoryLength
);

EFI_STATUS InitMtrrPolicy2 (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN MEMORY_MAP                   *WbMap,
    IN MEMORY_MAP                   *UcMap,
    IN UINT64                       Above4GMemoryLength
);

VOID CpuPeiMiscFuncs (
    IN EFI_PEI_SERVICES                 **PeiServices,
    IN EFI_PEI_READ_ONLY_VARIABLE_PPI   *ReadOnlyVariablePpi,
    IN EFI_BOOT_MODE                    BootMode
);    

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
