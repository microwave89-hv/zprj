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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCodePei.c 1     2/08/12 1:10a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:10a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCodePei.c $
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
// Name:		AMTStatusCodePei.c
//
// Description:	Processes ASF messages for Pei.
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

  AmtStatusCodePei.c

Abstract:
  Processes ASF messages

--*/

#include "Tiano.h"
#include "Pei.h"
#include EFI_PPI_DEFINITION (StatusCode)

#include EFI_PPI_DEFINITION (AmtStatusCode)

EFI_GUID  mPeiAmtStatusCodePpiGuid = PEI_AMT_STATUS_CODE_PPI_GUID;
EFI_GUID  mAmtPETQueueHobGuid = AMT_PET_QUEUE_HOB_GUID;

EFI_STATUS
AmtQueuePetMessage (
    IN  EFI_PEI_SERVICES        **PeiServices,
    IN  EFI_STATUS_CODE_TYPE    Type,
    IN  EFI_STATUS_CODE_VALUE   Value
    )
/*++
Routine Description: 

  This routine puts PET message to MessageQueue, which will be sent later.

Arguments:

  PeiServices - PeiServices pointer.
  Type        - StatusCode message type.
  Value       - StatusCode message value.

Returns: 
  
  EFI_SUCCESS      - The function completed successfully

--*/
{
    AMT_PET_QUEUE_HOB     *PETQueueHob;
    EFI_STATUS            Status;

    // Create PET queue hob
    Status = (**PeiServices).CreateHob ( PeiServices, \
                                         EFI_HOB_TYPE_GUID_EXTENSION, \
                                         sizeof(AMT_PET_QUEUE_HOB), \
                                         &PETQueueHob );
    if (EFI_ERROR (Status)) {
        return Status;
    }
    PETQueueHob->EfiHobGuidType.Name = mAmtPETQueueHobGuid;
    PETQueueHob->Type = Type;
    PETQueueHob->Value = Value;

    return EFI_SUCCESS;
}

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

  Provides an interface that a software module can call to report an ASF PEI status code.

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
    PEI_AMT_STATUS_CODE_PPI         *AmtStatusCode;
    EFI_STATUS                      Status;

    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &mPeiAmtStatusCodePpiGuid, \
                                        0, \
                                        NULL, \
                                        &AmtStatusCode );
    if ( EFI_ERROR (Status) ) {
        if (((Type & EFI_STATUS_CODE_TYPE_MASK) != EFI_PROGRESS_CODE) &&
            ((Type & EFI_STATUS_CODE_TYPE_MASK) != EFI_ERROR_CODE)) {
            return ;
        }

        // Register to Hob

        // Create PET queue hob
        AmtQueuePetMessage (PeiServices, Type, Value);

        return ;
    }

    AmtStatusCode->ReportStatusCode (
                     PeiServices,
                     AmtStatusCode,
                     Type,
                     Value,
                     Instance,
                     CallerId,
                     Data
                     );

    return ;
}

EFI_STATUS
AmtStatusInit(
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES **PeiServices
)
/*++
Routine Description: 

  Init routine for PEI ASF StatusCode.

Arguments:

  FfsHeader   - FfsHeader pointer.
  PeiServices - PeiServices pointer.

Returns: 
  
  EFI_SUCCESS      - The function completed successfully

--*/
{
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