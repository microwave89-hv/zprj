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

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB PPI/BaseMemoryTest.h 1     2/08/12 4:35a Yurenlai $
//
// $Revision: 1 $
//
// $Date: 2/08/12 4:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB PPI/BaseMemoryTest.h $
// 
// 1     2/08/12 4:35a Yurenlai
// Intel Haswell/NB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        BaseMemoryTest.h
//
// Description: This header file contains the PPI definition for the Base
//              Memory Test,
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef _BASE_MEMORY_TEST_H_
#define _BASE_MEMORY_TEST_H_

#define PEI_BASE_MEMORY_TEST_GUID \
  {0xb6ec423c, 0x21d2, 0x490d, 0x85, 0xc6, 0xdd, 0x58, 0x64, 0xea, 0xa6, 0x74}

typedef struct _PEI_BASE_MEMORY_TEST_PPI  PEI_BASE_MEMORY_TEST_PPI;

typedef enum {
    Ignore,
    Quick,
    Sparse,
    Extensive
} PEI_MEMORY_TEST_OP;

typedef EFI_STATUS (EFIAPI *PEI_BASE_MEMORY_TEST) (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN PEI_BASE_MEMORY_TEST_PPI     *This,
    IN EFI_PHYSICAL_ADDRESS         BeginAddress,
    IN UINT64                       MemoryLength,
    IN PEI_MEMORY_TEST_OP           Operation,
    OUT EFI_PHYSICAL_ADDRESS        *ErrorAddress
  );

typedef struct _PEI_BASE_MEMORY_TEST_PPI {
    PEI_BASE_MEMORY_TEST            BaseMemoryTest;
} PEI_BASE_MEMORY_TEST_PPI;

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
