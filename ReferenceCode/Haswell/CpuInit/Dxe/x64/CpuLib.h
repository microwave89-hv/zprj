/** @file
  Library functions that can be called in both PEI and DXE phase

@copyright
  Copyright (c) 2004 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _CPU_LIB_H_
#define _CPU_LIB_H_

#if 0
UINTN
CpuReadCr0 (
  VOID
  )
/**
@brief
  Get CR0 value

  @param[in] None

  @retval CR0 value
**/
;

VOID
CpuWriteCr0 (
  UINTN   Value
  )
/**
@brief
  Write CR0 register

  @param[in] Value - Value that will be written into CR0 register
**/
;

UINTN
CpuReadCr3 (
  VOID
  )
/**
@brief
  Get CR3 register value

  @param[in] None

  @retval CR3 register value
**/
;

VOID
CpuWriteCr3 (
  UINTN   Value
  )
/**
@brief
  Write CR3 register

  @param[in] Value - Value that will be written to CR3 register
**/
;

UINTN
CpuSetPower2 (
  IN  UINTN   Input
  )
/**
@brief
  Calculate the power 2 value from the Input value

  @param[in] Input - The number that will be calculated

  @retval Power 2 value after calculated
**/
;

UINT64
CpuReadTsc (
  VOID
  )
/**
@brief
  Read CPU TSC value

  @param[in] None

  @retval TSC value
**/
;

VOID
CpuBreak (
  VOID
  )
/**
@brief
  Break by INT3

  @param[in] None
**/
;

VOID
CpuInitSelectors (
  VOID
  )
/**
@brief
  Initialize selectors by calling INT 68

  @param[in] None
**/
;

#endif

UINT16
CpuCodeSegment (
  VOID
  )
/**
@brief
  Return code segment address - CS

  @param[in] None

  @retval Code segment address
**/
;

VOID
CpuLoadGlobalDescriptorTable (
  VOID  *Table16ByteAligned
  )
/**
@brief
  Get current GDT descriptor

  @param[in] Table16ByteAligned  - the table buffer that will store current GDT table descriptor
**/
;

VOID
CpuLoadInterruptDescriptorTable (
  VOID  *Table16ByteAligned
  )
/**
@brief
  Get current IDT descriptor

  @param[in] Table16ByteAligned  - the table buffer that will store current GDT table descriptor
**/
;

#endif
