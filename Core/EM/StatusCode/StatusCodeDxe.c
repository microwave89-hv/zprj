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
// $Header: /Alaska/BIN/Modules/StatusCode/StatusCodeDxe.c 8     11/13/12 6:21p Oleksiyy $
//
// $Revision: 8 $
//
// $Date: 11/13/12 6:21p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/StatusCode/StatusCodeDxe.c $
// 
// 8     11/13/12 6:21p Oleksiyy
// [TAG]  		EIP106198
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Memory leak in DataHubStatusCode function of
// StatusCodeDxe.c
// [RootCause]  	Memory allocated for the Record was newer released.
// [Solution]  	FreePool operation added.
// [Files]  		StatusCodeDxe.c
// 
// 7     6/12/12 3:50p Oleksiyy
// [TAG]  		EIP90338
// [Category]  	Improvement
// [Description] 	Extern declaradion of gAmiGlobalVariableGuid moved to
// AmiLib.h.
// [Files]  		AmiLib.h, StatusCodeDxe.c and StatusCoderuntime.c
// 
// 6     5/22/12 5:31p Oleksiyy
// [TAG]  		EIP90338
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	ChiefRiver SCT Fail on item Generic Test\EFI Compliant Test
// [RootCause]  	EFI_GLOBAL_VARIABLE guid is used in non EFI defined
// variable.
// [Solution]  	New guig AMI_GLOBAL_VARIABLE_GUID is created and used.
// [Files]  		AmiLib.h, Misc.c, StatusCodeDxe.c and StatusCoderuntime.c
// 
// 5     6/23/11 6:09p Oleksiyy
// [TAG]  		EIP56644
// [Category]  	New Feature
// [Description]  	Implemented PPI and Protocols, described in a PI 1.2
// Report Status Code Router specification. 
// [Files]  		StatusCodePei.c, StatusCodeDxe.c, StatusCodeInt.h,
// StatusCodeCommon.c and StatusCodeRuntime.c
// 
// 4     2/25/11 11:12a Oleksiyy
// [TAG]  		EIP54703 
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Disabling "CON_OUT_CHECKPOINTS_IN_QUIET_MODE" token, ends
// with build error
// [RootCause]  	Wrong dependency from CON_OUT_CHECKPOINTS_IN_QUIET_MODE
// [Solution]  	Declaration of Foreground and Background variables now
// also depend from CON_OUT_CHECKPOINTS_IN_QUIET_MODE value. 
// [Files]  		StatusCodeDxe.c
// 
// 3     11/17/10 6:02p Oleksiyy
// [TAG]  		EIP39752 
// [Category]  	Improvement
// [Description]  	Bug fix. Status code moved to EfiRuntimeServicesData
// memory.
// [Files]  		StatusCodeDxe.c
// 
// 2     7/09/09 5:18p Oleksiyy
// Files clean-up some headers added
//
// 1     3/05/09 1:40p Felixp
//
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    StatusCodeDxe.c
//
// Description:
//  File contains DXE specific status code routines such as:
//    - Entry point of the StatusCode DXE driver
//    DXE implementation of some of the functions from the status code library.
//    Implementation of the data hub logger (status code subcomponent that logs status codes into the data hub)
//    Implementation of the ConOut checkpoints (status code subcomponent that displays checkpoints on all ConOut devices).
//    (Status code library is a set of generic routines utilized throughout the component).
//
//<AMI_FHDR_END>
//**********************************************************************
#include <AmiDxeLib.h>
#include <StatusCodes.h>
#include <Token.h>
#include <Protocol/StatusCode.h>
#include <Protocol/DataHub.h>
#if CON_OUT_CHECKPOINTS_IN_QUIET_MODE
#include <Protocol/AmiPostMgr.h>
#endif
#include <Protocol/ConsoleControl.h>
#include <Protocol/SimpleTextOut.h>
#include "StatusCodeInt.h"

EFI_DATA_HUB_PROTOCOL *DataHub = NULL;
EFI_CONSOLE_CONTROL_PROTOCOL *ConsoleControl = NULL;
#if CON_OUT_CHECKPOINTS_IN_QUIET_MODE
AMI_POST_MANAGER_PROTOCOL *PostManager = NULL;
EFI_GRAPHICS_OUTPUT_BLT_PIXEL Foreground = {0xFF,0xFF,0xFF,0};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL Background = {0,0,0,0};
static EFI_GUID gAmiPostManagerProtocolGuid = AMI_POST_MANAGER_PROTOCOL_GUID;
#endif
#if PI_SPECIFICATION_VERSION >= 0x00010014
//----Router------------------------------------
#include <Protocol/Variable.h>
#include <Protocol/ReportStatusCodeHandler.h>

extern ROUTER_STRUCT_HEADER *RouterCallbackStr;
#define SC_ROUTER_ENTRIES 0xF

//----Router End---------------------------------
#endif
extern BOOLEAN StatusRuntime;

#define EFI_STANDARD_CALLER_ID_GUID \
  {0xC9DCF469, 0xA7C4, 0x11D5, 0x87, 0xDA, 0x00, 0x06, 0x29, 0x45, 0xC3, 0xB9}

#define EFI_STATUS_CODE_GUID \
  {0xd083e94c, 0x6560, 0x42e4, 0xb6, 0xd4, 0x2d, 0xf7, 0x5a, 0xdf, 0x6a, 0x2a}

#if PI_SPECIFICATION_VERSION >= 0x00010014
BOOLEAN InRscHandlerNotification = FALSE;
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RscHandlerNotification
//
// Description:
//      Executes delayed calls (when current TPL is higher that one router was 
//      registered with) to registered status code routers.
//
// Input:
//      N EFI_EVENT        Event - signaled event.
//      IN VOID            *Context - pointer to structure with parameters.
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RscHandlerNotification (
    IN EFI_EVENT        Event,
    IN VOID             *Context
    )
{
    RSC_HANDLER_CALLBACK_ENTRY  *CallbackEntry;
    EFI_PHYSICAL_ADDRESS        Address;
    RSC_DATA_ENTRY              *RscData;

    CallbackEntry = (RSC_HANDLER_CALLBACK_ENTRY *) Context;


    // Traverse the status code data buffer to parse all data to report.

    Address = CallbackEntry->StatusCodeDataBuffer;
    InRscHandlerNotification = TRUE;
    while (Address < CallbackEntry->EndPointer) 
    {
        RscData = (RSC_DATA_ENTRY *) (UINTN) Address;
        CallbackEntry->RscHandlerCallback (
                        RscData->Type,
                        RscData->Value,
                        RscData->Instance,
                        &RscData->CallerId,
                        &RscData->Data
                        );

        Address += (sizeof (RSC_DATA_ENTRY) + RscData->Data.Size);
    }

    CallbackEntry->EndPointer = CallbackEntry->StatusCodeDataBuffer;
    InRscHandlerNotification = FALSE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RouterRegister
//
// Description: Register the callback function for ReportStatusCode() notification 
//              in DXE and Runtime.
//
// Input:
//      IN EFI_RSC_HANDLER_CALLBACK Callback - A pointer to a function of type 
//                        EFI_RSC_HANDLER_CALLBACK that is to be registered.
//      IN EFI_TPL Tpl -  TPL at which callback can be safely invoked.
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
EFI_STATUS RouterRegister (
    IN EFI_RSC_HANDLER_CALLBACK   Callback,
    IN EFI_TPL                    Tpl
    )
{
    EFI_STATUS                    Status;
    RSC_HANDLER_CALLBACK_ENTRY    *CallbackEntry;
    UINT32                        i;
    VOID                          *Ptr, *UnregisteredPtr=NULL;

    if (Callback == NULL) 
        return EFI_INVALID_PARAMETER;
    if (RouterCallbackStr == NULL)
        return EFI_OUT_OF_RESOURCES;
  
    Ptr = (UINT8*) RouterCallbackStr + sizeof (ROUTER_STRUCT_HEADER);

    for (i = 0; i != RouterCallbackStr->RegisteredEntries; i++) 
    {
        CallbackEntry = Ptr;

        if (CallbackEntry->RscHandlerCallback == NULL) 
        {
            UnregisteredPtr = Ptr;
        }
        else 
        {
            if (CallbackEntry->RscHandlerCallback == Callback) 
            // If the function was already registered. It can't be registered again.
                return EFI_ALREADY_STARTED;
        }
        Ptr = (UINT8*) Ptr + sizeof (RSC_HANDLER_CALLBACK_ENTRY);
    }
    if (UnregisteredPtr == NULL) //No Unregistered entries
    {
        if (RouterCallbackStr->RegisteredEntries == RouterCallbackStr->TotalEntries)
            return EFI_OUT_OF_RESOURCES; // And all entries are taken already - exit
        CallbackEntry = Ptr;
        RouterCallbackStr->RegisteredEntries++;
    }
    else
        CallbackEntry = UnregisteredPtr; // Will fill uregistered entry
    
    CallbackEntry->RscHandlerCallback = Callback;
    CallbackEntry->Tpl                = Tpl;

    // If TPL of registered callback funtion is not TPL_HIGH_LEVEL, then event should be created
    // for it, and related buffer for status code data should be prepared.
    // Here the data buffer must be prepared in advance, because Report Status Code Protocol might
    // be invoked under TPL_HIGH_LEVEL and no memory allocation is allowed then.
    // If TPL is TPL_HIGH_LEVEL, then all status code will be reported immediately, without data
    // buffer and event trigger.
    if ((Tpl != TPL_HIGH_LEVEL) && !StatusRuntime) 
    {
        VOID     *StatusCodeDataBuff;
        Status = pBS->AllocatePool (EfiRuntimeServicesData, EFI_PAGE_SIZE, &StatusCodeDataBuff);
        CallbackEntry->StatusCodeDataBuffer = (EFI_PHYSICAL_ADDRESS) (UINTN) StatusCodeDataBuff;
        CallbackEntry->BufferSize = EFI_PAGE_SIZE;
        CallbackEntry->EndPointer = CallbackEntry->StatusCodeDataBuffer;
        Status = pBS->CreateEvent (
                        EVT_NOTIFY_SIGNAL,
                        Tpl,
                        RscHandlerNotification,
                        CallbackEntry,
                        &CallbackEntry->Event
                        );
        ASSERT_EFI_ERROR (Status);
    }

    return EFI_SUCCESS;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RouterUnregister
//
// Description:  Remove a previously registered callback function from the notification list.
//
// Input:
//      IN EFI_RSC_HANDLER_CALLBACK Callback - A pointer to a function of type 
//                                  EFI_RSC_HANDLER_CALLBACK that is to be unregistered.
//
// Output:
//      EFI_SUCCESS           The function was successfully unregistered.
//      EFI_INVALID_PARAMETER The callback function was NULL.
//      EFI_NOT_FOUND         The callback function was not found to be unregistered.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS RouterUnregister (IN EFI_RSC_HANDLER_CALLBACK Callback)
{
    RSC_HANDLER_CALLBACK_ENTRY    *CallbackEntry;
    UINT32                        i;
    VOID                          *Ptr;

    if (Callback == NULL) 
        return EFI_INVALID_PARAMETER;
    if (RouterCallbackStr == NULL)
        return EFI_NOT_FOUND;

    Ptr = (UINT8*) RouterCallbackStr + sizeof (ROUTER_STRUCT_HEADER);

    for (i = 0; i != RouterCallbackStr->RegisteredEntries; i++) 
    {
        CallbackEntry = Ptr;

        if (CallbackEntry->RscHandlerCallback == Callback) 
        {
      
         // If the function is found in list, delete it and return.

            if ((CallbackEntry->Tpl != TPL_HIGH_LEVEL) && (CallbackEntry->StatusCodeDataBuffer != 0))
            {
                pBS->FreePool ((VOID *) (UINTN) CallbackEntry->StatusCodeDataBuffer);
                pBS->CloseEvent (CallbackEntry->Event);
            }
        pBS->SetMem(Ptr, sizeof(RSC_HANDLER_CALLBACK_ENTRY), 0);//Clear all data in entry
        return EFI_SUCCESS;
        }
        Ptr = (UINT8*) Ptr + sizeof (RSC_HANDLER_CALLBACK_ENTRY);
    }

  return EFI_NOT_FOUND;
}

EFI_RSC_HANDLER_PROTOCOL  RscHandlerProtocol = {
  RouterRegister,
  RouterUnregister
  };

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PassRouterAdress
//
// Description:  Sets variable with the address of RSC Info structure.
//
// Input:
//      IN EFI_EVENT Event
//      IN VOID *Context
//
// Output:
//      VOID         
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID PassRouterAdress(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_PHYSICAL_ADDRESS RSCInfoAddresss = (EFI_PHYSICAL_ADDRESS) (UINTN) RouterCallbackStr;
    

    if (RouterCallbackStr == NULL)
        return;
    pRS->SetVariable(
        L"RSCInfoAddresss",
        &gAmiGlobalVariableGuid,
        EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
        sizeof(EFI_PHYSICAL_ADDRESS),
        &RSCInfoAddresss
    );

}
#endif
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   Delay
//
// Description: Stalls execution for a passed in number of microseconds
//
// Input:
//      VOID *PeiServices - not used
//      UINT32 Microseconds - the number of microseconds to stall execution
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID Delay(VOID **PeiServices, UINT32 Microseconds)
{
    pBS->Stall(Microseconds);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DxeReportStatusCode
//
// Description: DXE Status Code Reporting function.
//  A wrapper around phase independent ReportStatucCode
//  function defined in StatusCodeCommon.c.
//
// Input:
//      IN EFI_STATUS_CODE_TYPE Type - the type and severity of the error that occurred
//      IN EFI_STATUS_CODE_VALUE Value - the Class, subclass and Operation that caused the error
//      IN UINT32 Instance Instance - Instance
//      *CallerId OPTIONAL - The GUID of the caller function
//      *Data OPTIONAL - the extended data field that contains additional info
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DxeReportStatusCode (
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
)
{
    //If we are in runtime don't do anything.
    //Port this code if runtime status code is required.
    if (StatusRuntime) return EFI_SUCCESS;
    
    return ( ReportStatusCode( NULL, Type, Value, Instance, CallerId, Data));
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StatusCodeExitBS
//
// Description: Exit Boot Services event handler.
//  Terminates boot time status code processing
//
// Input:
//      IN EFI_EVENT Event - not used
//      IN VOID *Context - not used
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StatusCodeExitBS (IN EFI_EVENT Event, IN VOID *Context)
{
    StatusRuntime = TRUE;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DxeInitStatusCode
//
// Description:
//  Entry point of the StatusCode Driver.
//  Calls InitStatusCodeParts function, installs the Status Code Protocol,
//  and registers event handlers for the legacy boot and exit boot services events.
//  DxeInitStatusCode installs different protocol based on value of the
//  EFI_SPECIFICATION_VERSION SDL token (defined in Core.sdl).
//  If value of the EFI_SPECIFICATION_VERSION constant is less than 0x20000,
//  framework EFI_STATUS_CODE_ARCH_PROTOCOL_GUID protocol is installed;
//  otherwise, PI EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID protocol is installed.
//  PI Status Code Protocol is initialized with the address of DxeReportStatusCode function.
//
// Input:
//      *ImageHandle - The firmware allocate handle for the EFI image
//      *SystemTable - pointer to the EFI System Table
//
// Output: EFI_STATUS
//
// Modified: StatusCode Arch Protocol- now published
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DxeInitStatusCode(
    IN EFI_HANDLE         *ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_HANDLE              StatusCodeHandle = NULL;
    EFI_EVENT               Event;
#if PI_SPECIFICATION_VERSION >= 0x00010014
    EFI_EVENT               VarEvent = NULL;
    VOID                    *VarReg;
#endif    
#if EFI_SPECIFICATION_VERSION >= 0x20000
    static EFI_STATUS_CODE_PROTOCOL *StatusCode;
#endif    
    InitStatusCodeParts(ImageHandle,SystemTable);

#if EFI_SPECIFICATION_VERSION >= 0x20000    
    Status = pBS->AllocatePool (
        EfiRuntimeServicesData, sizeof(EFI_STATUS_CODE_PROTOCOL), &StatusCode
    );
    if (EFI_ERROR(Status)) return Status;
    StatusCode->ReportStatusCode = DxeReportStatusCode;
#endif
#if EFI_SPECIFICATION_VERSION < 0x20000
    SystemTable->RuntimeServices->ReportStatusCode = DxeReportStatusCode;
#endif
    Status = SystemTable->BootServices->InstallProtocolInterface(
                 &StatusCodeHandle,
#if EFI_SPECIFICATION_VERSION < 0x20000
                 &gEfiStatusCodeArchProtocolGuid,
#else
                 &gEfiStatusCodeRuntimeProtocolGuid,
#endif
                 EFI_NATIVE_INTERFACE, 
#if EFI_SPECIFICATION_VERSION < 0x20000
                 NULL
#else
                 StatusCode
#endif
             );
    //Register Exit Boot Services Callback
    pBS->CreateEvent(
        EVT_SIGNAL_EXIT_BOOT_SERVICES,TPL_CALLBACK,
        &StatusCodeExitBS, NULL, &Event
    );
    CreateLegacyBootEvent(TPL_CALLBACK, &StatusCodeExitBS, NULL, &Event);
#if PI_SPECIFICATION_VERSION >= 0x00010014
    //Allocate memory for Status Code Router inforstructure
    Status = pBS->AllocatePool (EfiRuntimeServicesData, 
                     sizeof(ROUTER_STRUCT_HEADER) + (sizeof(RSC_HANDLER_CALLBACK_ENTRY) * SC_ROUTER_ENTRIES), 
                                    &RouterCallbackStr);
    if (EFI_ERROR(Status)) return Status;
    pBS->SetMem(RouterCallbackStr, sizeof(ROUTER_STRUCT_HEADER) + 
                     (sizeof(RSC_HANDLER_CALLBACK_ENTRY) * SC_ROUTER_ENTRIES), 0);
    RouterCallbackStr->TotalEntries = SC_ROUTER_ENTRIES;
    Status = pBS->InstallMultipleProtocolInterfaces (
                  &StatusCodeHandle,
                  &gEfiRscHandlerProtocolGuid,
                  &RscHandlerProtocol,
                  NULL
                  );
    ASSERT_EFI_ERROR (Status);

    Status = RegisterProtocolCallback(&gEfiVariableArchProtocolGuid,PassRouterAdress,NULL,&VarEvent,&VarReg);

    ASSERT_EFI_ERROR(Status);
#endif
    return Status;
}

//<AMI_GHDR_START>
//----------------------------------------------------------------------------
// Name:    Data_Hub_Logging
//
// Description:
//  DataHub Logging Functions:
//   - DataHubInint
//   - DataHubInstalled
//   - DataHubStatusCode
//----------------------------------------------------------------------------
//<AMI_GHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DataHubStatusCode
//
// Description: Logs status code data into the data hub
//
// Input:
//  IN  EFI_STATUS_CODE_TYPE        Type
//  IN  EFI_STATUS_CODE_VALUE       Value
//  IN  UINT32                      Instance
//  IN  EFI_GUID                    *CallerId OPTIONAL
//  IN  EFI_STATUS_CODE_DATA        *Data OPTIONAL
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DataHubStatusCode (
    IN VOID **Dummy, //dummy parameter for compatibility with PEI callback interface
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
)
{
    EFI_STATUS Status;
    DATA_HUB_STATUS_CODE_DATA_RECORD *Record;
    UINT32 Size;
    UINT8 CodeType = STATUS_CODE_TYPE(Type);
    
    static EFI_GUID gEfiCallerIdGuid = EFI_STANDARD_CALLER_ID_GUID;
    static EFI_GUID gEfiStatusCodeGuid = EFI_STATUS_CODE_GUID;
    static EFI_GUID gEfiStatusCodeRuntimeProtocolGuid = EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID;
    static UINT8 DataHubClasses[] = {EFI_DATA_CLASS_PROGRESS_CODE,EFI_DATA_CLASS_ERROR,EFI_DATA_CLASS_DEBUG};
    
    if (DataHub == NULL) return EFI_NOT_AVAILABLE_YET;
    
    //Do not log debug codes
    if (CodeType==EFI_DEBUG_CODE) return EFI_SUCCESS;
    
    if (CodeType > sizeof(DataHubClasses)) return EFI_INVALID_PARAMETER;
    
    if (Data!=NULL)
        Size =  EFI_FIELD_OFFSET(DATA_HUB_STATUS_CODE_DATA_RECORD,Data)
                +Data->HeaderSize+Data->Size;
    else
        Size = sizeof(DATA_HUB_STATUS_CODE_DATA_RECORD);
        
    pBS->AllocatePool(EfiBootServicesData,Size,&Record);
    //---Fill Record structure--------
    Record->CodeType = Type;
    Record->Value = Value;
    Record->Instance = Instance;
    
    if (CallerId==NULL)  Record->CallerId = gEfiCallerIdGuid;
    else Record->CallerId = *CallerId;
    
    if (Data==NULL)
        pBS->SetMem(&Record->Data,sizeof(EFI_STATUS_CODE_DATA),0);
    else
        pBS->CopyMem(&Record->Data,Data,Data->HeaderSize+Data->Size);
        
    Status = DataHub->LogData(
                 DataHub,
                 &gEfiStatusCodeGuid,
                 &gEfiStatusCodeRuntimeProtocolGuid,
                 DataHubClasses[CodeType-1],
                 Record,
                 Size
             );
    pBS->FreePool(Record);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DataHubInstalled
//
// Description: Callback routine. Activates data hub status code logging once DataHub protocol is installed.
//
// Input:
//      IN EFI_EVENT Event - Signalled Event
//      IN VOID *Context - calling context
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID DataHubInstalled (IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS Status;
    
    if (DataHub!=NULL) return;
    
    Status = pBS->LocateProtocol(&gEfiDataHubProtocolGuid,NULL,&DataHub);
    
    if (EFI_ERROR(Status)) DataHub=NULL;
    else pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   DataHubInit
//
// Description: Initializes data hub error logging infrastructure.
//  This function is called from InitStatusCodeParts function (in DXE only).
//
// Input:
//      IN EFI_HANDLE *ImageHandle
//      IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS DataHubInit(
    IN EFI_HANDLE *ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_EVENT Event;
    VOID *Registration;
    //Register Data Hub Callback
    EFI_STATUS Status = RegisterProtocolCallback(
                            &gEfiDataHubProtocolGuid, DataHubInstalled, NULL,
                            &Event, &Registration
                        );
                        
    if (EFI_ERROR(Status)) return Status;
    
    pBS->SignalEvent(Event);
    return Status;
}

//<AMI_GHDR_START>
//----------------------------------------------------------------------------
// Name:    Con_Out_Checkpoints
//
// Description:
//  ConOut checkpoints functions:
//   - ConOutCpInit
//   - ConOutInstalled
//   - StopConOutCheckpoints
//   - ConOutCheckpoint
//----------------------------------------------------------------------------
//<AMI_GHDR_END>

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConOutCheckpoint
//
// Description: Displays checkpoints at the right bottom corner or the ConOut devices.
//
// Input:
//  IN VOID *Dummy - not used. Dummy parameter for compatibility with PEI callback interface.
//  IN UINT8 Checkpoint  - checkpoint to display
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConOutCheckpoint (
    IN VOID *Dummy,
    IN UINT8 Checkpoint
)
{
    EFI_STATUS Status;
    EFI_CONSOLE_CONTROL_SCREEN_MODE Mode;
    CHAR16 s[10];
    
    if (ConsoleControl==NULL || pST->ConOut==NULL
#if CON_OUT_CHECKPOINTS_IN_QUIET_MODE
            || PostManager == NULL
#endif
       ) return EFI_NOT_AVAILABLE_YET;
       
    Status = ConsoleControl->GetMode(ConsoleControl,&Mode,NULL,NULL);
    
    if (EFI_ERROR(Status)) return Status;
    
    //TODO: try Sprintf and convert
    Swprintf(s, L"%X",Checkpoint);
    
    if (Mode==EfiConsoleControlScreenText)
    {
        UINTN X,Y, MaxX, MaxY;
        pST->ConOut->QueryMode(pST->ConOut,pST->ConOut->Mode->Mode, &MaxX, &MaxY);
        //Get cursor position
        X = pST->ConOut->Mode->CursorColumn;
        Y = pST->ConOut->Mode->CursorRow;
        //Set cursor and print string
        pST->ConOut->SetCursorPosition(pST->ConOut, MaxX-3, MaxY-1);
        pST->ConOut->OutputString(pST->ConOut, s);
        //Restore cursor position
        pST->ConOut->SetCursorPosition(pST->ConOut, X, Y);
    }
    
#if CON_OUT_CHECKPOINTS_IN_QUIET_MODE
    else  // EfiConsoleControlScreenGraphics
    {
        PostManager->DisplayQuietBootMessage(
            s, 0, 0, CA_AttributeRightBottom,
            Foreground, Background
        );
    }
    
#endif
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   StopConOutCheckpoints
//
// Description: Read To Boot Callback routine. Terminates ConOut checkpoint display.
//
// Input:
//      IN EFI_EVENT Event - Signalled Event
//      IN VOID *Context - calling context
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID StopConOutCheckpoints (IN EFI_EVENT Event, IN VOID *Context)
{
    ConsoleControl=NULL;
    pBS->CloseEvent(Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConOutInstalled
//
// Description: Callback routine. Activates ConOut checkpoint display once
//  ConOut field in the UEFI ststem table is populated.
//
// Input:
//      IN EFI_EVENT Event - Signalled Event
//      IN VOID *Context - calling context
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ConOutInstalled (IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS Status;
    
    if (ConsoleControl!=NULL) return;
    
#if CON_OUT_CHECKPOINTS_IN_QUIET_MODE
    Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid,NULL,&PostManager);
    
    if (EFI_ERROR(Status)) PostManager=NULL;
    
#endif
    Status = pBS->LocateProtocol(&gEfiConsoleControlProtocolGuid,NULL,&ConsoleControl);
    
    if (EFI_ERROR(Status)) ConsoleControl=NULL;
    else pBS->CloseEvent(Event);
    
    CreateReadyToBootEvent(TPL_CALLBACK, &StopConOutCheckpoints, NULL, &Event);
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ConOutCpInit
//
// Description: Initializes ConOut checkpoint display code.
//  This function is called from InitStatusCodeParts function (in DXE only).
//
// Input:
//      IN EFI_HANDLE *ImageHandle
//      IN EFI_SYSTEM_TABLE *SystemTable
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS ConOutCpInit (
    IN EFI_HANDLE *ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_EVENT Event;
    VOID *Registration;
    //Register Data Hub Callback
    EFI_STATUS Status = RegisterProtocolCallback(
                            &gEfiConsoleControlProtocolGuid, ConOutInstalled, NULL,
                            &Event, &Registration
                        );
                        
    if (EFI_ERROR(Status)) return Status;
    
    pBS->SignalEvent(Event);
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ResetOrResume
//
// Description: Error Code Action.
//              Attempts to perform a system reset. If reset fails, returns.
//
// Input:
//      VOID *PeiServices - not used
//      EFI_STATUS_CODE_VALUE Value - Value of the error code that triggered the action.
//
// Output:
//      VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ResetOrResume(
    IN VOID *PeiServices, IN EFI_STATUS_CODE_VALUE Value
)
{
    pRS->ResetSystem(EfiResetCold,0,0,NULL);
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