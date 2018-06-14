/*++
  This file contains 'Framework Code' and is licensed as such   
  under the terms of your license agreement with Intel or your  
  vendor.  This file may not be modified, except as allowed by  
  additional terms of your license agreement.                   
--*/
/*++

Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  Debug.c

Abstract:

  Support for Debug primatives. 

--*/

#include "Tiano.h"
#include "EfiCommonLib.h"
#include "EfiSmmDriverLib.h"
#include EFI_GUID_DEFINITION (StatusCodeCallerId)
#include EFI_GUID_DEFINITION (StatusCodeDataTypeId)

#define EFI_STATUS_CODE_DATA_MAX_SIZE64 (EFI_STATUS_CODE_DATA_MAX_SIZE / 8)

VOID
EfiDebugAssert (
  IN CHAR8    *FileName,
  IN INTN     LineNumber,
  IN CHAR8    *Description
  )
/*++

Routine Description:

  Worker function for ASSERT (). If Error Logging hub is loaded log ASSERT
  information. If Error Logging hub is not loaded DEADLOOP ().
  
Arguments:

  FileName    - File name of failing routine.

  LineNumber  - Line number of failing ASSERT().

  Description - Description, usually the assertion,
  
Returns:
  
  None

--*/
{

  UINT64  Buffer[EFI_STATUS_CODE_DATA_MAX_SIZE64];

  if (mSmmDebug != NULL) {
    EfiDebugAssertWorker (FileName, LineNumber, Description, sizeof (Buffer), Buffer);
    mSmmDebug->ReportStatusCode (
                mSmmDebug,
                (EFI_ERROR_CODE | EFI_ERROR_UNRECOVERED),
                (EFI_SOFTWARE_SMM_DRIVER | EFI_SW_EC_ILLEGAL_SOFTWARE_STATE),
                0,
                &gEfiCallerIdGuid,
                (EFI_STATUS_CODE_DATA *) Buffer
                );
  }
  //
  // don't return, this is an assert.
  //
  EFI_DEADLOOP ();
}

VOID
EfiDebugVPrint (
  IN  UINTN   ErrorLevel,
  IN  CHAR8   *Format,
  IN  VA_LIST Marker
  )
/*++

Routine Description:

  Worker function for DEBUG(). If Error Logging hub is loaded log ASSERT
  information. If Error Logging hub is not loaded do nothing.
  
Arguments:

  ErrorLevel - If error level is set do the debug print.

  Format     - String to use for the print, followed by Print arguments.

  Marker     - VarArgs
  
Returns:
  
  None

--*/
{
  UINT64  Buffer[EFI_STATUS_CODE_DATA_MAX_SIZE64];

  if (!(gErrorLevel & ErrorLevel)) {
    return ;
  }

  EfiDebugVPrintWorker (ErrorLevel, Format, Marker, sizeof (Buffer), Buffer);

  if (mSmmDebug != NULL) {
    mSmmDebug->ReportStatusCode (
                mSmmDebug,
                EFI_DEBUG_CODE,
                (EFI_SOFTWARE_SMM_DRIVER | EFI_DC_UNSPECIFIED),
                0,
                &gEfiCallerIdGuid,
                (EFI_STATUS_CODE_DATA *) Buffer
                );
  }

  return ;
}

VOID
EfiDebugPrint (
  IN  UINTN                   ErrorLevel,
  IN  CHAR8                   *Format,
  ...
  )
/*++

Routine Description:

  Worker function for DEBUG(). If Error Logging hub is loaded log ASSERT
  information. If Error Logging hub is not loaded do nothing.

  We use UINT64 buffers due to IPF alignment concerns.

Arguments:

  ErrorLevel - If error level is set do the debug print.

  Format     - String to use for the print, followed by Print arguments.

  ...        - VAR args for Format
  
Returns:
  
  None

--*/
{
  VA_LIST Marker;

  VA_START (Marker, Format);

  EfiDebugVPrint (ErrorLevel, Format, Marker);

  VA_END (Marker);
}
