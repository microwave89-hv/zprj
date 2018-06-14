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
// $Header: /Alaska/BIN/Modules/StatusCode/StatusCodeInt.h 3     6/23/11 6:10p Oleksiyy $
//
// $Revision: 3 $
//
// $Date: 6/23/11 6:10p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Modules/StatusCode/StatusCodeInt.h $
// 
// 3     6/23/11 6:10p Oleksiyy
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
// Name:    StatusCodeInt.c
//
// Description: Header file containing declarations of functions, macros, and types shared across status code module files.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef __STATUS_CODE_INT__H__
#define __STATUS_CODE_INT__H__
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        EFI_STATUS_CODE_VALUE Value;
        UINT8 Byte;
    } STATUS_CODE_TO_BYTE_MAP;
    
    typedef VOID (ERROR_CODE_ACTION)(
        IN VOID *PeiServices, IN EFI_STATUS_CODE_VALUE Value
    );
    
    typedef struct
    {
        EFI_STATUS_CODE_VALUE Value;
        ERROR_CODE_ACTION *Action;
    } ERROR_CODE_ACTION_MAP;
    
#define STATUS_CODE_TYPE(Type) ((Type)&EFI_STATUS_CODE_TYPE_MASK)
    
    UINT8 FindByteCode(STATUS_CODE_TO_BYTE_MAP *Map, EFI_STATUS_CODE_VALUE Value);
    VOID Delay(VOID **PeiServices, UINT32 Microseconds);
    EFI_STATUS ReportStatusCode (
        IN VOID *PeiServices,
        IN EFI_STATUS_CODE_TYPE Type, IN EFI_STATUS_CODE_VALUE Value,
        IN UINT32 Instance, IN EFI_GUID *CallerId OPTIONAL,
        IN EFI_STATUS_CODE_DATA *Data OPTIONAL
    );
    VOID InitStatusCodeParts(IN VOID *ImageHandler, IN VOID *ServicesTable);
    VOID ResetOrResume(IN VOID *PeiServices, IN EFI_STATUS_CODE_VALUE Value);
#if PI_SPECIFICATION_VERSION >= 0x00010014
#include <Protocol/ReportStatusCodeHandler.h>
typedef struct {
  EFI_STATUS_CODE_TYPE      Type;
  EFI_STATUS_CODE_VALUE     Value;
  UINT32                    Instance;
  UINT32                    Reserved;
  EFI_GUID                  CallerId;
  EFI_STATUS_CODE_DATA      Data;
} RSC_DATA_ENTRY;

typedef struct {
  EFI_RSC_HANDLER_CALLBACK  RscHandlerCallback;
  EFI_TPL                   Tpl;
  EFI_EVENT                 Event;
  EFI_PHYSICAL_ADDRESS      StatusCodeDataBuffer;
  UINTN                     BufferSize;
  EFI_PHYSICAL_ADDRESS      EndPointer;
} RSC_HANDLER_CALLBACK_ENTRY;

typedef struct {
  UINT32  RegisteredEntries;
  UINT32  TotalEntries;
} ROUTER_STRUCT_HEADER;
#endif
    /****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
