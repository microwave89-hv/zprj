//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/BIN/Modules/StatusCode/StatusCodePei.c 3     6/23/11 6:09p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 6/23/11 6:09p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/StatusCode/StatusCodePei.c $
// 
// 3     6/23/11 6:09p Oleksiyy
// [TAG]  		EIP56644
// [Category]  	New Feature
// [Description]  	Implemented PPI and Protocols, described in a PI 1.2
// Report Status Code Router specification. 
// [Files]  		StatusCodePei.c, StatusCodeDxe.c, StatusCodeInt.h,
// StatusCodeCommon.c and StatusCodeRuntime.c
// 
// 2     7/09/09 5:18p Oleksiyy
// Files clean-up some headers added
//
// 1     3/05/09 1:40p Felixp
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    StatusCodePei.c
//
// Description:
//      File contains PEI specific status code routines such as
//      entry point of the StatusCode PEIM (PeiInitStatusCode) and
//      PEI implementation of some of the functions from the status code library.
//      (Status code library is a set of generic routines utilized throughout the component).
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiPeiLib.h>
#include <PPI/ProgressCode.h>
#include <PPI/Stall.h>
#include "StatusCodeInt.h"
#include <Token.h>

//--------------------To HEADER-----------------------------------------------
/** @file
  GUID used to identify HOB for pointers to callback functios registered on
  PEI report status code router.
  
Copyright (c) 2009 - 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under 
the terms and conditions of the BSD License that accompanies this distribution.  
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.                                            

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#if PI_SPECIFICATION_VERSION >= 0x00010014

#include <PPI/ReportStatusCodeHandler.h>
#define INITIAL_RSC_PEI_ENTRIES 8
#define STATUS_CODE_CALLBACK_GUID \
  { \
    0xe701458c, 0x4900, 0x4ca5, {0xb7, 0x72, 0x3d, 0x37, 0x94, 0x9f, 0x79, 0x27} \
  }

EFI_GUID gStatusCodeCallbackGuid = STATUS_CODE_CALLBACK_GUID;


BOOLEAN IsItRecursiveCall (
  IN OUT  BOOLEAN                   *Value,
  IN      BOOLEAN                   CompareWith,
  IN      BOOLEAN                   SvitchTo
  );


EFI_GUID gEfiPeiRscHandlerPpiGuid = EFI_PEI_RSC_HANDLER_PPI_GUID;

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Delay
//
// Description: Worker function to create one memory status code GUID'ed HOB
//
// Input:   None
//
// Output:
//     UINTN*  - Pointer to the NumberOfEntries field in Hob
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

UINTN*
CreateRscHandlerCallbackPacket ( 
  )
{
  UINTN  *NumberOfEntries;
  EFI_HOB_GUID_TYPE *Hob;
  EFI_STATUS        Status;
  EFI_PEI_SERVICES **PeiServices;

  PeiServices = GetPeiServicesTablePointer ();

  //
  // Build GUID'ed HOB with PCD defined size.
  //
  
  Status = (*PeiServices)->CreateHob (PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, 
                            (UINT16)(sizeof (EFI_PEI_RSC_HANDLER_CALLBACK) * INITIAL_RSC_PEI_ENTRIES 
                        + sizeof (UINTN)+ sizeof (EFI_HOB_GUID_TYPE)), &Hob);
  //ASSERT_PEI_ERROR(PeiServices,Status);
  if (EFI_ERROR(Status)) return NULL;
  MemCpy (&Hob->Name, &gStatusCodeCallbackGuid, sizeof (EFI_GUID));

  NumberOfEntries = (UINTN*)(Hob + 1);                    

  *NumberOfEntries = 0;

  return NumberOfEntries;
}


#define GET_GUID_HOB_DATA(HobStart) \
  (VOID*)((UINT8*)(HobStart) + sizeof (EFI_HOB_GUID_TYPE))

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   GetFirstGuidHob
//
// Description: Returns the first instance of the matched GUID HOB among the 
//              whole HOB list.
//
// Input:
//      IN EFI_GUID *Guid - The GUID to match with in the HOB list.
//
// Output:
//      VOID* Pointer po first matched Hob (NULL - if not found)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID *
GetFirstGuidHob (
  IN EFI_GUID         *Guid
  )
{

  VOID      *HobList = NULL;
  EFI_STATUS        Status;
  EFI_PEI_SERVICES **PeiServices;

  PeiServices = GetPeiServicesTablePointer ();
  
  Status = (*PeiServices)->GetHobList (PeiServices, &HobList);
  if (EFI_ERROR(Status)) return NULL;
  Status = FindNextHobByGuid (Guid, &HobList);
  if (EFI_ERROR(Status)) return NULL;
  else return HobList;
  
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PpiUnregister
//
// Description:  Remove a previously registered callback function from the notification list.
//
// Input:
//      IN EFI_PEI_RSC_HANDLER_CALLBACK Callback - A pointer to a function of type 
//                        EFI_PEI_RSC_HANDLER_CALLBACK that is to be unregistered.
//
// Output:
//      EFI_SUCCESS           The function was successfully unregistered.
//      EFI_INVALID_PARAMETER The callback function was NULL.
//      EFI_NOT_FOUND         The callback function was not found to be unregistered.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PpiUnregister (
  IN EFI_PEI_RSC_HANDLER_CALLBACK Callback
  )
{
  EFI_PEI_HOB_POINTERS            Hob;
  EFI_PEI_RSC_HANDLER_CALLBACK    *CallbackEntry;
  UINTN                           *NumberOfEntries;
  UINTN                           Index;
  EFI_STATUS                      Status;


  if (Callback == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Hob.Raw  = GetFirstGuidHob (&gStatusCodeCallbackGuid);
  while (Hob.Raw != NULL) {
    NumberOfEntries = GET_GUID_HOB_DATA (Hob.Raw);
    CallbackEntry   = (EFI_PEI_RSC_HANDLER_CALLBACK *) (NumberOfEntries + 1);
    for (Index = 0; Index < *NumberOfEntries; Index++) {
      if (CallbackEntry[Index] == Callback) {
        CallbackEntry[Index] = CallbackEntry[*NumberOfEntries - 1];
        *NumberOfEntries -= 1;
        return EFI_SUCCESS;
      }
    }
    Status = FindNextHobByGuid (&gStatusCodeCallbackGuid, &Hob.Raw);
    if (EFI_ERROR(Status)) Hob.Raw = NULL;
  }

  return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PpiRegister
//
// Description: Register the callback function for ReportStatusCode() notification.
//
// Input:
//      IN EFI_PEI_RSC_HANDLER_CALLBACK Callback - A pointer to a function of type 
//                        EFI_PEI_RSC_HANDLER_CALLBACK that is to be registered.
//
// Output:
//      EFI_SUCCESS           The function was successfully registered.
//      EFI_INVALID_PARAMETER The callback function was NULL.
//      EFI_OUT_OF_RESOURCES  The internal buffer ran out of space. No more functions can be
//                            registered.
//      EFI_ALREADY_STARTED   The function was already registered. It can't be registered again.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
PpiRegister (
  IN EFI_PEI_RSC_HANDLER_CALLBACK Callback
  )
{
  EFI_PEI_HOB_POINTERS          Hob;
  EFI_PEI_RSC_HANDLER_CALLBACK  *CallbackEntry;
  UINTN                         *NumberOfEntries;
  UINTN                         Index;
  UINTN                         *FreePacket;
  EFI_STATUS                    Status;

  if (Callback == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Hob.Raw  = GetFirstGuidHob (&gStatusCodeCallbackGuid);
  FreePacket = NULL;
  while (Hob.Raw != NULL) {
    NumberOfEntries = GET_GUID_HOB_DATA (Hob.Raw);
    CallbackEntry   = (EFI_PEI_RSC_HANDLER_CALLBACK *) (NumberOfEntries + 1);
    if (*NumberOfEntries < INITIAL_RSC_PEI_ENTRIES) {
      FreePacket = NumberOfEntries;
    }
    for (Index = 0; Index < *NumberOfEntries; Index++) {
      if (CallbackEntry[Index] == Callback) {
        //
        // If the function was already registered. It can't be registered again.
        //
        return EFI_ALREADY_STARTED;
      }
    }

    Status = FindNextHobByGuid (&gStatusCodeCallbackGuid, &Hob.Raw);
    if (EFI_ERROR(Status)) Hob.Raw = NULL;
  }

  if (FreePacket == NULL) {
    FreePacket = CreateRscHandlerCallbackPacket();
  }
  if (FreePacket == NULL) return EFI_OUT_OF_RESOURCES;  
  CallbackEntry = (EFI_PEI_RSC_HANDLER_CALLBACK *) (FreePacket + 1);
  CallbackEntry[*FreePacket] = Callback;
  *FreePacket += 1;

  return EFI_SUCCESS;
}


EFI_PEI_RSC_HANDLER_PPI     RscHandlerPpi = {
  PpiRegister,
  PpiUnregister
  };

EFI_PEI_PPI_DESCRIPTOR   RscHandlerPpiDescriptor[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiRscHandlerPpiGuid,
    &RscHandlerPpi
  }
};

#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReportStatusCodePei
//
// Description:
//  Top level status code reporting routine exposed by the status code protocol/PPI.
//  Calls the various types of status code handlers
//  (SimpleStatusReport, StringStatusReport, MiscStatusReport, PerformErrorCodeAction)
//  Generates string from the status code data to pass to StringStatusReport function.
//  Also pass all parameters to Registered Statuse Code Routers.
//
// Input:
//      IN VOID *PeiServices - pointer to the PEI Boot Services table
//      IN EFI_STATUS_CODE_TYPE Type - the type and severity of the error that occurred
//      IN EFI_STATUS_CODE_VALUE Value - the Class, subclass and Operation that caused the error
//      IN UINT32 Instance -
//      IN EFI_GUI *CallerId OPTIONAL - The GUID of the caller function
//      IN EFI_STATUS_CODE_DATA *Data OPTIONAL - the extended data field that contains additional info
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ReportStatusCodePei (
    IN VOID *PeiServices,
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
)
{

#if PI_SPECIFICATION_VERSION >= 0x00010014
    EFI_PEI_HOB_POINTERS            Hob;
    EFI_PEI_RSC_HANDLER_CALLBACK    *CallbackEntry;
    UINTN                           *NumberOfEntries;
    UINTN                           Index;
    EFI_STATUS                      Status;

    //if (IsItRecursiveCall(&PeiRouterRecurciveStatus, FALSE, TRUE) != TRUE) 
    //{    //return EFI_ACCESS_DENIED;
    Hob.Raw  = GetFirstGuidHob (&gStatusCodeCallbackGuid);
    while (Hob.Raw != NULL) 
    {
        NumberOfEntries = GET_GUID_HOB_DATA (Hob.Raw);
        CallbackEntry   = (EFI_PEI_RSC_HANDLER_CALLBACK *) (NumberOfEntries + 1);
        for (Index = 0; Index < *NumberOfEntries; Index++) 
        {
            CallbackEntry[Index](
            PeiServices,
            Type,
            Value,
            Instance,
            CallerId,
            Data
            );
        }

        Status = FindNextHobByGuid (&gStatusCodeCallbackGuid, &Hob.Raw);
        if (EFI_ERROR(Status)) Hob.Raw = NULL;
        
    }
//    }
//    IsItRecursiveCall (&PeiRouterRecurciveStatus, TRUE, FALSE);
#endif

    return ReportStatusCode (PeiServices,Type,Value,Instance,CallerId,Data);
}

// Status Code PPI
EFI_PEI_PROGRESS_CODE_PPI  StatusCodePpi = {ReportStatusCodePei};
// Status Code PPI Descriptor
EFI_PEI_PPI_DESCRIPTOR StatusCodePpiDescriptor[] =
{
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gPeiStatusCodePpiGuid, &StatusCodePpi
};



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PeiInitStatusCode
//
// Description: Pei "entry point" for this module, called by the Pei Core.
//    Conotol flow:
//     1. Creates a RSC Hob and installs RSC PPI.
//     2. Calls InitStatusCodeParts function.
//     3. Installs the Status Code PPI.
//    InitStatusCodeParts function calls initialization routines of status code subcomponents
//    registered under StatusCodeInitialize eLink.
//    Status Code PPI is initialized with the address of ReportStatusCode function.
//
// Input:
//      *FfsHeader - pointer to the header of the current firmware file system file
//      **PeiServices - pointer to the Pei Services table
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS PeiInitStatusCode(
    IN EFI_FFS_FILE_HEADER       *FfsHeader,
    IN EFI_PEI_SERVICES          **PeiServices
)
{
    EFI_STATUS  Status;
    InitStatusCodeParts(FfsHeader,PeiServices);

#if PI_SPECIFICATION_VERSION >= 0x00010014
    CreateRscHandlerCallbackPacket ();
    // First install Report Status Code Handler PPI
    Status = (*PeiServices)->InstallPpi(
                 PeiServices, &RscHandlerPpiDescriptor[0]
             );

#endif
    // And then install the Status Code PPI
    Status = (*PeiServices)->InstallPpi(
                 PeiServices, &StatusCodePpiDescriptor[0]
             );
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Delay
//
// Description: Stalls execution for a passed in number of microseconds
//
// Input:
//      EFI_PEI_SERVICES **PeiServices
//      UINT32 Microseconds - the number of microseconds to stall execution
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Delay(EFI_PEI_SERVICES **PeiServices, UINT32 Microseconds)
{
    EFI_PEI_STALL_PPI *Stall;
    EFI_STATUS Status = (*PeiServices)->LocatePpi(PeiServices,&gPeiStallPpiGuid,0,NULL,&Stall);
    
    if (EFI_ERROR(Status)) return;
    
    Stall->Stall(PeiServices, Stall, Microseconds);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ResetOrResume
//
// Description: Error Code Action.
//              Attempts to perform a system reset. If reset fails, returns.
//
// Input:
//      EFI_PEI_SERVICES **PeiServices
//      EFI_STATUS_CODE_VALUE Value - Value of the error code that triggered the action.
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ResetOrResume(
    IN EFI_PEI_SERVICES **PeiServices, IN EFI_STATUS_CODE_VALUE Value
)
{
    (*PeiServices)->ResetSystem(PeiServices);
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************