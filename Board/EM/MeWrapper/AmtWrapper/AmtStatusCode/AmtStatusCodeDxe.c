//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCodeDxe.c 1     2/08/12 1:10a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:10a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCodeDxe.c $
// 
// 1     2/08/12 1:10a Klzhan
// Initial Check in 
// 
// 1     2/25/11 1:44a Klzhan
// Initial Check-in
// 
// 1     12/03/10 5:11a Klzhan
// Initial Check-in.
//
//**********************************************************************
//
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:		AMTStatusDxeCode.c
//
// Description:	Processes ASF messages for DXE.
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
/*++

Copyright (c)  2009 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  AmtStatusCodeDxe.c

Abstract:
  Processes ASF messages

--*/

#include "Tiano.h"
#include "Pei.h"
#include EFI_PPI_DEFINITION (StatusCode)

VOID AmtStatusCode(
    IN  EFI_PEI_SERVICES            **PeiServices,
    IN  EFI_STATUS_CODE_TYPE        Type,
    IN  EFI_STATUS_CODE_VALUE       Value,
    IN  UINT32                      Instance,
    IN  EFI_GUID                    *CallerId OPTIONAL,
    IN  EFI_STATUS_CODE_DATA        *Data OPTIONAL
)
/*++
Routine Description: 

  Provides an interface that a software module can call to report an ASF DXE status code.

Arguments:

  PeiServices - PeiServices pointer.

  Type     - Indicates the type of status code being reported.
  
  Value    - Describes the current status of a hardware or software entity.
             This included information about the class and subclass that is 
             used to classify the entity as well as an operation.
  
  Instance - The enumeration of a hardware or software entity within 
             the system. Valid instance numbers start with 1.
  
  CallerId - This optional parameter may be used to identify the caller.
             This parameter allows the status code driver to apply different 
             rules to different callers.
  
  Data     - This optional parameter may be used to pass additional data.

Returns: 
  
  None

--*/
{
    //
    // Do nothing, because AMT ASF driver will handle that.
    //
    return ;
}

EFI_STATUS
AmtStatusInit(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES **PeiServices
)
/*++
Routine Description: 

  Init routine for DXE ASF StatusCode.

Arguments:

  FfsHeader   - FfsHeader pointer.
  PeiServices - PeiServices pointer.

Returns: 
  
  EFI_SUCCESS      - The function completed successfully

--*/
{
    //
    // Do nothing, because AMT ASF driver will handle that.
    //
    return EFI_SUCCESS;
}
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************