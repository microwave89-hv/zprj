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
// $Header: /Alaska/BIN/Modules/StatusCode/StatusCodeRuntime.c 9     12/13/12 3:59p Oleksiyy $
//
// $Revision: 9 $
//
// $Date: 12/13/12 3:59p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/StatusCode/StatusCodeRuntime.c $
// 
// 9     12/13/12 3:59p Oleksiyy
// [TAG]  		EIP109426
// [Category]  	Improvement
// [Description]  	Issues found by CppCheck in StatusCode eModule.
// [Files]  		StatuseCodeRuntime.c
// 
// 8     8/09/12 5:27p Oleksiyy
// [TAG]  		EIP97932
// [Category]  	Improvement
// [Description]  	StatusCode Router RT init fix
// [Files]  		StatusCodeRuntime.c
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
// 5     10/20/11 5:22p Oleksiyy
// [TAG]  		EIP72806 
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Runtime status code hangs
// [RootCause]  	Not converting actual status code functions addresses on
// Virtual Address Change event.
// [Solution]  	Status code functions converted.
// [Files]  		EfiLib.c, StatusCode.sdl and StatusCodeRuntime.c
// 
// 4     6/23/11 6:10p Oleksiyy
// [TAG]  		EIP56644
// [Category]  	New Feature
// [Description]  	Implemented PPI and Protocols, described in a PI 1.2
// Report Status Code Router specification. 
// [Files]  		StatusCodePei.c, StatusCodeDxe.c, StatusCodeInt.h,
// StatusCodeCommon.c and StatusCodeRuntime.c
// 
// 3     11/18/10 4:00p Oleksiyy
// [TAG]  		EIP46589 
// [Category]  	Improvement
// [Description]  	All StatusCode listeners not marked as RUNTIME removed
// from runtime instance.
// [Files]  		StatusCodeRuntime.c
// 
// 2     10/06/10 4:50p Oleksiyy
// Issue Number:  39752 
// 
// Category:  New Feature
// 
// Description:  Runtime Staus Code support is added.
// 
// Files:  Uart1.asl, Tokens.c, Runtime.c, GenericSio.c, EfiLib.c,
// CsmLib.c, AmiDxeLib.h and StatusCode eModule.
// 
// 1     10/04/10 5:49p Oleksiyy
// Issue Number:  39752 and 29307
// 
// Category:  New Feature
// 
// Description:  Support of Status Code in Runtime is added. Trace API
// keeps working after handing off control to OS. New instances of
// StatusCode services in runtime and SMM are now available.
// 
// Files:  Uart1.asl, Tokens.c, Runtime.c, GenericSio.c, EfiLib.c,
// CsmLib.c, AmiDxeLib.h and StatusCode eModule.
// 
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:    StatusCodeRuntime.c
//
// Description:
//  File contains Runtime specific status code routines such as:
//    - Entry point of the StatusCode Runtime driver
//    Runtime implementation of some of the functions from the status code library.
//    (Status code library is a set of generic routines utilized throughout the component).
//
//<AMI_FHDR_END>
//**********************************************************************

#include <AmiDxeLib.h>
#include <StatusCodes.h>
#include <Protocol/StatusCode.h>
#include <Protocol/SmmStatusCode.h>
#include <StatusCodeELinks.h>
#include "StatusCodeInt.h"

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}
#if PI_SPECIFICATION_VERSION >= 0x00010014
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmReportStatusCodeHandler.h>
#include <Protocol/ReportStatusCodeHandler.h>
//----Router-----------------------------------

#define SMM_CALLBACK_NUMBER 10

typedef struct {
    UINT32 RegisteredSmmEntries;
    EFI_SMM_RSC_HANDLER_CALLBACK  RscSmmHandlerCallback[SMM_CALLBACK_NUMBER];
} SMM_ROUTER_STRUCT;
extern BOOLEAN SmmRouter;
extern ROUTER_STRUCT_HEADER *RouterCallbackStr;
SMM_ROUTER_STRUCT SmmRouterCallbackStr;
//----Router End---------------------------------
#endif
extern BOOLEAN StatusRuntime;
EFI_STATUS_CODE_PROTOCOL    *gStatusCode = NULL;
EFI_REPORT_STATUS_CODE gOldStatusCode = NULL;


typedef EFI_STATUS (STRING_FUNCTION)(IN VOID *PeiServices, IN CHAR8 *String);
typedef EFI_STATUS (MY_STRING_FUNCTION)(IN VOID *PeiServices, IN CHAR8 *String);
typedef EFI_STATUS (SIMPLE_FUNCTION)(
    IN VOID *PeiServices,
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value
);
typedef EFI_STATUS (MISC_FUNCTION)(
    IN VOID *PeiServices,
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
);
typedef VOID (CHECKPOINT_FUNCTION)(IN VOID *PeiServices, IN UINT8 Checkpoint);


extern EFI_STATUS DummyStringHandler(IN VOID *PeiServices, IN CHAR8 *String);
extern EFI_STATUS DummySimpleHandler(
    IN VOID *PeiServices,
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value
);
extern EFI_STATUS DummyMiscHandler(
    IN VOID *PeiServices,
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
);


extern VOID DummyCheckpointHandler(IN VOID *PeiServices, IN UINT8 Checkpoint);

extern SIMPLE_FUNCTION*         SimpleList[];
extern STRING_FUNCTION*         StringList[];
extern MISC_FUNCTION*           MiscList[];
extern CHECKPOINT_FUNCTION*     CheckpointList[];

#define PEI(x) DUMMY_HANDLER
#define DXE(x) DUMMY_HANDLER
#define RUNTIME(x) x

#define DUMMY_HANDLER DummyStringHandler
extern STRING_FUNCTION STRING_LIST EndOfStringList;
STRING_FUNCTION*        MyStringList[] = {STRING_LIST NULL};
#undef DUMMY_HANDLER

#define DUMMY_HANDLER DummySimpleHandler
extern SIMPLE_FUNCTION SIMPLE_LIST EndOfSimpleList;
SIMPLE_FUNCTION*        MySimpleList[] = {SIMPLE_LIST NULL};
#undef DUMMY_HANDLER

#define DUMMY_HANDLER DummyMiscHandler
extern MISC_FUNCTION MISC_LIST EndOfMiscList;
MISC_FUNCTION*          MyMiscList[] = {MISC_LIST NULL};
#undef DUMMY_HANDLER

#define DUMMY_HANDLER DummyCheckpointHandler
extern CHECKPOINT_FUNCTION CHECKPOINT_LIST EndOfCheckpointList;
CHECKPOINT_FUNCTION*    MyCheckpointList[] = {CHECKPOINT_LIST NULL};
#undef DUMMY_HANDLER

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitElinks
//
// Description: This function inits all Statuse code E-links that dose not have RUNTIME mark
//              as dummy. While leaving only RUNTIME marked E-links .
//
// Input:  None
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitElinks ()
{
    UINTN i;

    for (i=0; SimpleList[i]; i++){
        if (MySimpleList[i]== SimpleList[i]) 
            SimpleList[i]= DummySimpleHandler;
        else
            SimpleList[i]= MySimpleList[i];
    }
    for (i=0; StringList[i]; i++){
        if (MyStringList[i]== StringList[i]) 
            StringList[i]= DummyStringHandler;
        else
            StringList[i]= MyStringList[i];
    }
    for (i=0; MiscList[i]; i++){
        if (MyMiscList[i]== MiscList[i]) 
            MiscList[i]= DummyMiscHandler;
        else
            MiscList[i]= MyMiscList[i];
    }
    for (i=0; CheckpointList[i]; i++){
        if (MyCheckpointList[i]== CheckpointList[i]) 
            CheckpointList[i]= DummyCheckpointHandler;
        else
            CheckpointList[i]= MyCheckpointList[i];
    }
    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RuntimeReportStatusCode
//
// Description: Runtime Status Code Reporting function.
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
EFI_STATUS RuntimeReportStatusCode (
    IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
)
{
    //If we are not in runtime call old function.

    if (!StatusRuntime) return ( gOldStatusCode( Type, Value, Instance, CallerId, Data));

    return ( ReportStatusCode( NULL, Type, Value, Instance, CallerId, Data));
}

#if PI_SPECIFICATION_VERSION >= 0x00010014
extern BOOLEAN RouterRecurciveStatus;
BOOLEAN IsItRecursiveCall (
  IN OUT  BOOLEAN                   *Value,
  IN      BOOLEAN                   CompareWith,
  IN      BOOLEAN                   SvitchTo
  );

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ReportStatusCodePei
//
// Description:
//          Pass all parameters to Registered Statuse Code Routers.
//
// Input:
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
EFI_STATUS ReportSmmRouter (
    IN EFI_STATUS_CODE_TYPE     Type,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN EFI_GUID                 *CallerId  OPTIONAL,
    IN EFI_STATUS_CODE_DATA     *Data      OPTIONAL
    )
{

    UINT32                        i;
 
    if ((SmmRouterCallbackStr.RegisteredSmmEntries == 0) || (IsItRecursiveCall (&RouterRecurciveStatus, FALSE, TRUE) == TRUE)) 
        return EFI_ACCESS_DENIED;
    for (i = 0; i != SmmRouterCallbackStr.RegisteredSmmEntries; i++) 
    {
        if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == NULL) 
            continue;//Unregistered function
        else
            SmmRouterCallbackStr.RscSmmHandlerCallback[i] (Type, Value, Instance, CallerId, Data);
    }
    // Restore the Recursive status of report

    IsItRecursiveCall (&RouterRecurciveStatus, TRUE, FALSE);
    return EFI_SUCCESS;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmmRegister
//
// Description:  Remove a previously registered callback function from the notification list.
//
// Input: 
//      IN EFI_SMM_RSC_HANDLER_CALLBACK Callback -  A pointer to a function that 
//                                                  that is to be unregistered.
//      
// Output:
//      EFI_SUCCESS           Function was successfully unregistered.
//      EFI_INVALID_PARAMETER The callback function was NULL.
//      EFI_NOT_FOUND         The callback function was not found to be unregistered. 
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS
SmmUnregister (
  IN EFI_SMM_RSC_HANDLER_CALLBACK Callback
  )
{
    UINT32                        i;

    if (Callback == NULL) return EFI_INVALID_PARAMETER;

    for (i = 0; i != SmmRouterCallbackStr.RegisteredSmmEntries; i++) 
    {
        if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == Callback) 
        {
            SmmRouterCallbackStr.RscSmmHandlerCallback[i] = NULL;
            return EFI_SUCCESS; //Function Unregistered 
        }
    }

    return EFI_NOT_FOUND;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmmRegister
//
// Description:  When this function is called the function pointer is added to an 
//               internal list and any future calls to ReportStatusCode() will be
//               forwarded to the Callback function.
//
// Input: 
//      IN EFI_SMM_RSC_HANDLER_CALLBACK Callback -  A pointer to a function that 
//                              is called when a call to ReportStatusCode() occurs.
//      
// Output:
//      EFI_SUCCESS           Function was successfully registered.
//      EFI_INVALID_PARAMETER The callback function was NULL.
//      EFI_OUT_OF_RESOURCES  The internal buffer ran out of space. No more functions 
//                            can be registered.
//      EFI_ALREADY_STARTED   The function was already registered. It can't be 
//                            registered again.   
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS

SmmRegister (
  IN EFI_SMM_RSC_HANDLER_CALLBACK Callback
  )
{
    UINT32                        i=0, FreeEntry = -1;

    if (Callback == NULL) 
        return EFI_INVALID_PARAMETER;
    if (SmmRouterCallbackStr.RegisteredSmmEntries != 0)
    {
        for (i = 0; i != SmmRouterCallbackStr.RegisteredSmmEntries; i++) 
        {
            if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == Callback)
                return EFI_ALREADY_STARTED; //Function already registered 
            if (SmmRouterCallbackStr.RscSmmHandlerCallback[i] == NULL)
                FreeEntry = i; 
        }
        if (FreeEntry = -1) //No Unregistered entries
        {
            if (SmmRouterCallbackStr.RegisteredSmmEntries == SMM_CALLBACK_NUMBER - 1)
                return EFI_OUT_OF_RESOURCES; // And all entries are taken already - exit
            FreeEntry = i;
            SmmRouterCallbackStr.RegisteredSmmEntries++;
        }
    }
    else 
    {
        SmmRouterCallbackStr.RegisteredSmmEntries++;
        FreeEntry = 0;
    }
    SmmRouterCallbackStr.RscSmmHandlerCallback[FreeEntry] = Callback;

    return EFI_SUCCESS;
}

EFI_SMM_RSC_HANDLER_PROTOCOL  mSmmRscHandlerProtocol = {
    SmmRegister,
    SmmUnregister
    };


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   InitRouterAdress
//
// Description:  Reads variable with the address of RSC Info structure and 
//               initialize global variable with it.
//
// Input: None
//
// Output:
//      VOID         
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID InitRouterAdress()
{
    EFI_PHYSICAL_ADDRESS RSCInfoAddresss;
    UINTN SizeOfRCInfo = sizeof(EFI_PHYSICAL_ADDRESS);
    EFI_STATUS  Status;
    
    if (RouterCallbackStr == NULL)
    {
        Status = pRS->GetVariable(
            L"RSCInfoAddresss",
            &gAmiGlobalVariableGuid,
            NULL,
            &SizeOfRCInfo,
            &RSCInfoAddresss
        );
        if (!EFI_ERROR(Status)) 
        RouterCallbackStr = (ROUTER_STRUCT_HEADER*) RSCInfoAddresss;
    }
    
}
//----Router End--------------------------------

#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ScRuntimeVirtualAddressChange
//
// Description:
//      Updates pointers to RSC structure and to callback functions inside structure.
//
// Input:
//      N EFI_EVENT        Event - signaled event.
//      IN VOID            *Context - Context
//
// Output: VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID ScRuntimeVirtualAddressChange (IN EFI_EVENT Event, IN VOID *Context)
{
#if PI_SPECIFICATION_VERSION >= 0x00010014
    RSC_HANDLER_CALLBACK_ENTRY      *CallbackEntry;
    VOID                            *Ptr;
#endif
    UINTN i;

    for (i=0; SimpleList[i]; i++){
    pRS->ConvertPointer(0,(VOID**)&(SimpleList[i]));
    }

    for (i=0; StringList[i]; i++){
    pRS->ConvertPointer(0,(VOID**)&(StringList[i]));
    }
  
    for (i=0; MiscList[i]; i++){
    pRS->ConvertPointer(0,(VOID**)&(MiscList[i]));
    }

    for (i=0; CheckpointList[i]; i++){
    pRS->ConvertPointer(0,(VOID**)&(CheckpointList[i]));
    }
    pRS->ConvertPointer(0,(VOID**)&(gStatusCode->ReportStatusCode));
#if PI_SPECIFICATION_VERSION >= 0x00010014
    if (RouterCallbackStr == NULL)
        InitRouterAdress();
    if (RouterCallbackStr == NULL)
        return;
    for (i = 0; i != RouterCallbackStr->RegisteredEntries; i++) 
    {
    
        if (i == 0)  
            Ptr = (UINT8*) RouterCallbackStr + sizeof (ROUTER_STRUCT_HEADER);
        else
            Ptr = (UINT8*) Ptr + sizeof (RSC_HANDLER_CALLBACK_ENTRY);
        CallbackEntry = Ptr;

        if (CallbackEntry->RscHandlerCallback == NULL) continue;//Unregistered function
        else pRS->ConvertPointer(0,(VOID**)&(CallbackEntry->RscHandlerCallback));
    
    }

    pRS->ConvertPointer(0,(VOID**)&RouterCallbackStr);
#endif
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmmReportStatusCode
//
// Description: SMM Status Code Reporting function.
//  A wrapper around phase independent ReportStatucCode
//  function defined in StatusCodeCommon.c.
//
// Input:
//      IN CONST EFI_SMM_STATUS_CODE_PROTOCOL *This - 
//                      Points to this instance of the EFI_SMM_STATUS_CODE_PROTOCOL.
//      IN EFI_STATUS_CODE_VALUE Value - the Class, subclass and Operation that caused the error
//      IN UINT32 Instance Instance - Instance
//      *CallerId OPTIONAL - The GUID of the caller function
//      *Data OPTIONAL - the extended data field that contains additional info
//
// Output: EFI_STATUS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS SmmReportStatusCode (
    IN CONST EFI_SMM_STATUS_CODE_PROTOCOL *This, IN EFI_STATUS_CODE_TYPE Type,
    IN EFI_STATUS_CODE_VALUE Value,
    IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
    IN EFI_STATUS_CODE_DATA *Data OPTIONAL
)
{   
    EFI_STATUS Status;

#if PI_SPECIFICATION_VERSION >= 0x00010014
    SmmRouter = TRUE;
    ReportSmmRouter (Type, Value, Instance, CallerId, Data);
#endif
    Status = ReportStatusCode( NULL, Type, Value, Instance, CallerId, Data);
#if PI_SPECIFICATION_VERSION >= 0x00010014
    SmmRouter = FALSE;
#endif
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RuntimeStatusCodeExitBS
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
VOID RuntimeStatusCodeExitBS (IN EFI_EVENT Event, IN VOID *Context)
{
#if PI_SPECIFICATION_VERSION >= 0x00010014
    InitRouterAdress();
#endif
    StatusRuntime = TRUE;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   RuntimeInitStatusCode
//
// Description:
//  Entry point of the StatusCode Runtime Driver.
//  Calls InitStatusCodeParts function, installs the Status Code Protocol,
//  and registers event handlers for the legacy boot and exit boot services events.
//  RuntimeInitStatusCode installs different protocol based on value of the
//  EFI_SPECIFICATION_VERSION SDL token (defined in Core.sdl).
//  If value of the EFI_SPECIFICATION_VERSION constant is less than 0x20000,
//  framework EFI_STATUS_CODE_ARCH_PROTOCOL_GUID protocol is installed;
//  otherwise, PI EFI_STATUS_CODE_RUNTIME_PROTOCOL_GUID protocol is installed.
//  PI Status Code Protocol is initialized with the address of RuntimeReportStatusCode function.
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
EFI_STATUS RuntimeInitStatusCode(
    IN EFI_HANDLE         *ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS                  Status;
    EFI_EVENT                   Event;

    InitAmiRuntimeLib(
        ImageHandle, SystemTable, RuntimeStatusCodeExitBS, ScRuntimeVirtualAddressChange
    );

    InitElinks();
    Status = SystemTable->BootServices->LocateProtocol( 
#if EFI_SPECIFICATION_VERSION < 0x20000
                 &gEfiStatusCodeArchProtocolGuid,
#else
                 &gEfiStatusCodeRuntimeProtocolGuid,
#endif
                NULL, &gStatusCode
             );
    gOldStatusCode = gStatusCode->ReportStatusCode;
    gStatusCode->ReportStatusCode = RuntimeReportStatusCode;
#if EFI_SPECIFICATION_VERSION < 0x20000
    SystemTable->RuntimeServices->ReportStatusCode = RuntimeReportStatusCode;
#endif
    
    //Register Exit Boot Services Callback

    CreateLegacyBootEvent(TPL_CALLBACK, &RuntimeStatusCodeExitBS, NULL, &Event);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   SmmInitStatusCode
//
// Description:
//  Entry point of the StatusCode SMM Driver.
//  
// Input:
//      IN EFI_HANDLE *ImageHandle - The firmware allocate handle for the EFI image
//      IN EFI_SYSTEM_TABLE *SystemTable - pointer to the EFI System Table
//
// Output: EFI_STATUS
//
// Modified: StatusCode Arch Protocol- now published
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>


EFI_STATUS SmmInitStatusCode(
    IN EFI_HANDLE         *ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
)
{
    EFI_STATUS              Status;
    EFI_HANDLE  StatusCodeHandle = NULL;
    static EFI_SMM_STATUS_CODE_PROTOCOL StatusCode = {SmmReportStatusCode};

#if PI_SPECIFICATION_VERSION >= 0x00010014
    EFI_HANDLE  SmmRscHandle = NULL;
    EFI_GUID    gEfiSmmRscHandlerProtocolGuid = EFI_SMM_RSC_HANDLER_PROTOCOL_GUID;
    EFI_SMM_SYSTEM_TABLE2       *pSmst2             = NULL;
    EFI_SMM_BASE2_PROTOCOL      *mInternalSmmBase2  = NULL;

    SmmRouterCallbackStr.RegisteredSmmEntries = 0;

    Status = SystemTable->BootServices->LocateProtocol (
                                        &gEfiSmmBase2ProtocolGuid,
                                        NULL,
                                        (VOID **)&mInternalSmmBase2
                                        );

    Status=mInternalSmmBase2->GetSmstLocation (mInternalSmmBase2, &pSmst2);
    ASSERT (pSmst2 != NULL);
    Status = pSmst2->SmmInstallProtocolInterface(
                    &SmmRscHandle,
                    &gEfiSmmRscHandlerProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mSmmRscHandlerProtocol
                    );
    ASSERT_EFI_ERROR (Status);
#endif

    InitElinks ();
    Status = SystemTable->BootServices->InstallProtocolInterface(
                 &StatusCodeHandle,
                 &gEfiSmmStatusCodeProtocolGuid,
                 EFI_NATIVE_INTERFACE, &StatusCode
             );
#if PI_SPECIFICATION_VERSION >= 0x00010014
    Status = pSmst2->SmmInstallProtocolInterface(
                 &StatusCodeHandle,
                 &gEfiSmmStatusCodeProtocolGuid,
                 EFI_NATIVE_INTERFACE, &StatusCode
    );

#endif
    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:	StatusCodeSmmEntry
//
// Description:	This function is the entry point for this file. This function
//				installs  services in and outside SMM.
//
// Input:		IN EFI_HANDLE ImageHandle -	Image handle
//				IN EFI_SYSTEM_TABLE *SystemTable -	Pointer to the system table
//
// Output:		EFI_STATUS - Status based on errors that occurred while waiting for
//				time to expire.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
EFI_STATUS StatusCodeSmmEntry(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitAmiLib(ImageHandle,SystemTable);
    return InitSmmHandlerEx(
               ImageHandle, SystemTable, SmmInitStatusCode, RuntimeInitStatusCode
           );
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