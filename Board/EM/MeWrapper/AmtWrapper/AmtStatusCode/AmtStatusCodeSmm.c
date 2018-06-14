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
// $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCodeSmm.c 1     2/08/12 1:10a Klzhan $
//
// $Revision: 1 $
//
// $Date: 2/08/12 1:10a $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCodeSmm.c $
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

  AmtStatusCodeSmm.c

Abstract:
  Processes ASF messages

--*/

#include "Tiano.h"
#include "Pei.h"
#include EFI_PROTOCOL_DEFINITION (SmmBase)
#include EFI_PROTOCOL_DEFINITION (SmmStatusCode)
#include "Protocol/AmtStatusCodeSmm/AmtStatusCodeSmm.h"
//#include EFI_PROTOCOL_DEFINITION (AmtStatusCodeSmm)

EFI_GUID  mAmtSmmStatusCodeProtocolGuid = AMT_SMM_STATUS_CODE_PROTOCOL_GUID;
EFI_GUID  gAmtSmmPETQueueProtocolGuid = AMT_SMM_PET_QUEUE_PROTOCOL_GUID;

AMT_SMM_PET_QUEUE_PROTOCOL  gAmtSmmPETQueue;
AMT_SMM_PET_QUEUE_PROTOCOL  *gAmtSmmPETQueueProtocol;

AMT_SMM_STATUS_CODE_PROTOCOL *mAmtSmmStatusCode;

EFI_SYSTEM_TABLE 		*pST;
EFI_BOOT_SERVICES 		*pBS;
EFI_RUNTIME_SERVICES 	*pRS;
EFI_SMM_BASE_PROTOCOL	*pSmmBase;
EFI_SMM_SYSTEM_TABLE	*pSmst;

VOID
AmtInitializeListHead (
  EFI_LIST_ENTRY       *List
  )
{
  List->ForwardLink = List;
  List->BackLink    = List;
}

VOID
AmtInsertTailList (
  EFI_LIST_ENTRY  *ListHead,
  EFI_LIST_ENTRY  *Entry
  )
{
  EFI_LIST_ENTRY *_ListHead;
  EFI_LIST_ENTRY *_BackLink;

  _ListHead              = ListHead;              
  _BackLink              = _ListHead->BackLink;     
  Entry->ForwardLink     = _ListHead;    
  Entry->BackLink        = _BackLink;       
  _BackLink->ForwardLink = Entry;    
  _ListHead->BackLink    = Entry;       
}

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
    AMT_SMM_PET_QUEUE_NODE   *NewNode;
    EFI_STATUS               Status;

    Status = pSmmBase->SmmAllocatePool (
                      pSmmBase,
                      EfiRuntimeServicesData,
                      sizeof (AMT_SMM_PET_QUEUE_NODE),
                      &NewNode
                      );
    if (EFI_ERROR (Status)) {
        return Status;
    }

    NewNode->Signature   = AMT_SMM_PET_QUEUE_NODE_SIGNATURE;
    NewNode->Type = Type;
    NewNode->Value = Value;
    AmtInsertTailList (&gAmtSmmPETQueueProtocol->MessageList, &NewNode->Link);

    return EFI_SUCCESS;
}

VOID SmmAmtStatusCode(
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
    if (mAmtSmmStatusCode == NULL) {
        if (((Type & EFI_STATUS_CODE_TYPE_MASK) != EFI_PROGRESS_CODE) &&
            ((Type & EFI_STATUS_CODE_TYPE_MASK) != EFI_ERROR_CODE)) {
            return ;
        }

        // Register to Queue
        AmtQueuePetMessage (PeiServices, Type, Value);

        return ;
    }

    mAmtSmmStatusCode->ReportStatusCode (
                         mAmtSmmStatusCode,
                         Type,
                         Value,
                         Instance,
                         CallerId,
                         Data
                         );

    return ;
}

VOID
EFIAPI
AmtCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
/*++
Routine Description: 

  ASF SMM StatusCode Callback.

Arguments:

  Event     - ASF StatusCode Callback Event.
  
  Context   - ASF StatusCode Callback Context.

Returns: 
  
  None

--*/
{
    pBS->LocateProtocol ( &mAmtSmmStatusCodeProtocolGuid, NULL, &mAmtSmmStatusCode );

    return;
}

EFI_STATUS
AmtCreateMessageQueue (
    VOID
    )
/*++
Routine Description: 

  This routine creats PET MessageQueue.

Arguments:

  None

Returns: 
  
  EFI_SUCCESS      - The function completed successfully

--*/
{
    EFI_STATUS    Status;
    EFI_HANDLE    Handle;

    Status = pBS->LocateProtocol (
                        &gAmtSmmPETQueueProtocolGuid,
                        NULL,
                        &gAmtSmmPETQueueProtocol
                        );
    if (!EFI_ERROR (Status)) {
        return EFI_SUCCESS;
    }

    //
    // Create Queue for later usage
    //
    gAmtSmmPETQueueProtocol = &gAmtSmmPETQueue;

    AmtInitializeListHead (&gAmtSmmPETQueueProtocol->MessageList);
    Handle = NULL;
    Status = pBS->InstallProtocolInterface (
                            &Handle,
                            &gAmtSmmPETQueueProtocolGuid,
                            EFI_NATIVE_INTERFACE,
                            &gAmtSmmPETQueue
                            );

    return EFI_SUCCESS;
}

EFI_STATUS
SmmAmtStatusInit(
    IN EFI_HANDLE               ImageHandle,
    IN EFI_SYSTEM_TABLE 		*SystemTable
)
/*++
Routine Description: 

  Init routine for SMM ASF StatusCode.

Arguments:

  FfsHeader   - FfsHeader pointer.
  PeiServices - PeiServices pointer.

Returns: 
  
  EFI_SUCCESS      - The function completed successfully

--*/
{
    EFI_STATUS                      Status;
    VOID                            *AmtRegistration;
    EFI_EVENT                       Event;

    pST=SystemTable;
    pBS=SystemTable->BootServices;
    pRS=SystemTable->RuntimeServices;
	Status = pBS->LocateProtocol(&gEfiSmmBaseProtocolGuid, NULL, &pSmmBase);
	Status = pSmmBase->GetSmstLocation(pSmmBase,&pSmst);

    AmtCreateMessageQueue ();

    Status = pBS->LocateProtocol ( &mAmtSmmStatusCodeProtocolGuid, NULL, &mAmtSmmStatusCode );
    if ( !EFI_ERROR (Status) ) return EFI_SUCCESS;

    //
    // Create the event
    //
    Status = pBS->CreateEvent (
                    EFI_EVENT_NOTIFY_SIGNAL,
                    EFI_TPL_CALLBACK,
                    AmtCallback,
                    NULL,
                    &Event
                    );
    if (EFI_ERROR (Status))  return Status;

    //
    // Register for protocol notifactions on this event
    // NOTE: Because this protocol will be installed in SMM, it is safety to
    // register ProtocolNotify here. This event will be triggered in SMM later.
    //
    Status = pBS->RegisterProtocolNotify (
                    &mAmtSmmStatusCodeProtocolGuid,
                    Event,
                    &AmtRegistration
                    );
    if (EFI_ERROR (Status))  return Status;

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