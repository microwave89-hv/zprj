/** @file
  This library provides SMM functions for IO and PCI IO access.
  These can be used to save size and simplify code.
  All contents must be runtime and SMM safe.

@copyright
  Copyright (c) 1999 - 2013 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#ifndef _SMM_IO_LIB_H_
#define _SMM_IO_LIB_H_

#include "EdkIIGlueDxe.h"
#include "Pci22.h"

///
/// Utility consumed protocols
///
#include EFI_PROTOCOL_DEFINITION (SmmBase)

///
/// Global variables that must be defined and initialized to use this library
///
extern EFI_SMM_SYSTEM_TABLE *mSmst;

///
/// Definitions
///
#define ICH_ACPI_TIMER_MAX_VALUE  0x1000000 ///< The timer is 24 bit overflow
///
/// Pci I/O related data structure deifinition
///
typedef enum {
  SmmPciWidthUint8  = 0,
  SmmPciWidthUint16 = 1,
  SmmPciWidthUint32 = 2,
  SmmPciWidthUint64 = 3,
  SmmPciWidthMaximum
} SMM_PCI_IO_WIDTH;

#define SMM_PCI_ADDRESS(bus, dev, func, reg) \
        ((UINT64) ((((UINT32) bus) << 24) + (((UINT32) dev) << 16) + (((UINT32) func) << 8) + ((UINT32) reg)))

typedef struct {
  UINT8  Register;
  UINT8  Function;
  UINT8  Device;
  UINT8  Bus;
  UINT32 ExtendedRegister;
} SMM_PCI_IO_ADDRESS;

///
/// CPU I/O Access Functions
///
/**
  Do a one byte IO read

  @param[in] Address - IO address to read

  @retval Data read
**/
UINT8
SmmIoRead8 (
  IN UINT16 Address
  );

/**
  Do a one byte IO write

  @param[in] Address - IO address to write
  @param[in] Data    - Data to write
**/
VOID
SmmIoWrite8 (
  IN UINT16 Address,
  IN UINT8  Data
  );

/**
  Do a two byte IO read

  @param[in] Address - IO address to read

  @retval Data read
**/
UINT16
SmmIoRead16 (
  IN UINT16 Address
  );

/**
  Do a two byte IO write

  @param[in] Address - IO address to write
  @param[in] Data    - Data to write
**/
VOID
SmmIoWrite16 (
  IN UINT16 Address,
  IN UINT16 Data
  );

/**
  Do a four byte IO read

  @param[in] Address - IO address to read

  @retval Data read
**/
UINT32
SmmIoRead32 (
  IN UINT16 Address
  );

/**
  Do a four byte IO write

  @param[in] Address - IO address to write
  @param[in] Data    - Data to write
**/
VOID
SmmIoWrite32 (
  IN UINT16 Address,
  IN UINT32 Data
  );

/**
  Do a one byte Memory write

  @param[in] Dest - Memory address to write
  @param[in] Data - Data to write

  @retval None
**/
VOID
SmmMemWrite8 (
  IN UINT64 Dest,
  IN UINT8  Data
  );

/**
  Do a one byte Memory read

  @param[in] Dest - Memory address to read

  @retval Data read
**/
UINT8
SmmMemRead8 (
  IN UINT64 Dest
  );

/**
  Do a two bytes Memory write

  @param[in] Dest - Memory address to write
  @param[in] Data - Data to write

  @retval None
**/
VOID
SmmMemWrite16 (
  IN UINT64 Dest,
  IN UINT16 Data
  );

/**
  Do a two bytes Memory read

  @param[in]  Dest - Memory address to read

  @retval Data read
**/
UINT16
SmmMemRead16 (
  IN UINT64 Dest
  );

/**
  Do a four bytes Memory write

  @param[in] Dest - Memory address to write
  @param[in] Data - Data to write

  @retval None
**/
VOID
SmmMemWrite32 (
  IN UINT64 Dest,
  IN UINT32 Data
  );

/**
  Do a four bytes Memory read

  @param[in] Dest - Memory address to read

  @retval Data read
**/
UINT32
SmmMemRead32 (
  IN UINT64 Dest
  );

/**
  Do a four bytes Memory read, then AND with Data, then write back to the same address

  @param[in] Dest - Memory address to write
  @param[in] Data - Data to do AND

  @retval None
**/
VOID
SmmMemAnd32 (
  IN UINT64 Dest,
  IN UINT32 Data
  );
///
/// Pci Configuration Space access functions definition
///
/**
  Read value from the specified PCI config space register

  @param[in] Width   - The width (8, 16 or 32 bits) of accessed pci config space register
  @param[in] Address - The address of the accessed pci register (bus, dev, func, offset)
  @param[in] Buffer  - The returned value

  @retval EFI_SUCCESS           - All operations successfully
  @retval EFI_INVALID_PARAMETER - Width is not valid or dosn't match register address
  @retval Other error code      - If any error occured when calling libiary functions
**/
EFI_STATUS
SmmPciCfgRead (
  IN SMM_PCI_IO_WIDTH   Width,
  IN SMM_PCI_IO_ADDRESS *Address,
  IN OUT VOID           *Buffer
  );
/**
  Write value into the specified PCI config space register

  @param[in] Width   - The width (8, 16 or 32 bits) of accessed pci config space register
  @param[in] Address - The address of the accessed pci register (bus, dev, func, offset)
  @param[in] Buffer  - The returned value

  @retval EFI_SUCCESS           - All operations successfully
  @retval EFI_INVALID_PARAMETER - Width is not valid or dosn't match register address
  @retval Other error code      - If any error occured when calling libiary functions
**/
EFI_STATUS
SmmPciCfgWrite (
  IN SMM_PCI_IO_WIDTH   Width,
  IN SMM_PCI_IO_ADDRESS *Address,
  IN OUT VOID           *Buffer
  );
#endif
