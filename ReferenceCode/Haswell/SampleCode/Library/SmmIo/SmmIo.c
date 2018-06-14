/** @file
  SMM I/O access utility implementation file, for Ia32

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

///
/// Include files
///
#include "SmmIoLib.h"

/**
  Do a one byte IO read

  @param[in] Address - IO address to read

  @retval Data read
**/
UINT8
SmmIoRead8 (
  IN UINT16 Address
  )
{
  UINT8 Buffer;

  ASSERT (mSmst);

  mSmst->SmmIo.Io.Read (
          &mSmst->SmmIo,
          SMM_IO_UINT8,
          Address,
          1,
          &Buffer
          );
  return Buffer;
}

/**
  Do a one byte IO write

  @param[in] Address - IO address to write
  @param[in] Data    - Data to write
**/
VOID
SmmIoWrite8 (
  IN UINT16 Address,
  IN UINT8  Data
  )
{
  ASSERT (mSmst);

  mSmst->SmmIo.Io.Write (
          &mSmst->SmmIo,
          SMM_IO_UINT8,
          Address,
          1,
          &Data
          );
}

/**
  Do a two byte IO read

  @param[in] Address - IO address to read

  @retval Data read
**/
UINT16
SmmIoRead16 (
  IN UINT16 Address
  )
{
  UINT16 Buffer;

  ASSERT (mSmst);

  mSmst->SmmIo.Io.Read (
          &mSmst->SmmIo,
          SMM_IO_UINT16,
          Address,
          1,
          &Buffer
          );
  return Buffer;
}

/**
  Do a two byte IO write

  @param[in] Address - IO address to write
  @param[in] Data    - Data to write
**/
VOID
SmmIoWrite16 (
  IN UINT16 Address,
  IN UINT16 Data
  )
{
  ASSERT (mSmst);

  mSmst->SmmIo.Io.Write (
          &mSmst->SmmIo,
          SMM_IO_UINT16,
          Address,
          1,
          &Data
          );
}

/**
  Do a four byte IO read

  @param[in] Address - IO address to read

  @retval Data read
**/
UINT32
SmmIoRead32 (
  IN UINT16 Address
  )
{
  UINT32 Buffer;

  ASSERT (mSmst);

  mSmst->SmmIo.Io.Read (
          &mSmst->SmmIo,
          SMM_IO_UINT32,
          Address,
          1,
          &Buffer
          );
  return Buffer;
}

/**
  Do a four byte IO write

  @param[in] Address - IO address to write
  @param[in] Data    - Data to write
**/
VOID
SmmIoWrite32 (
  IN UINT16 Address,
  IN UINT32 Data
  )
{
  ASSERT (mSmst);

  mSmst->SmmIo.Io.Write (
          &mSmst->SmmIo,
          SMM_IO_UINT32,
          Address,
          1,
          &Data
          );
}
