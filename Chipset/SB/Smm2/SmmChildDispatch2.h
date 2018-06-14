//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2.h 3     3/25/13 5:00a Wesleychen $
//
// $Revision: 3 $
//
// $Date: 3/25/13 5:00a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatch2.h $
// 
// 3     3/25/13 5:00a Wesleychen
// [TAG]          None
// [Category]     Improvement
// [Description]  Refine GPI SMM2 related routines.
// [Files]        SmiHandlerGeneric2.c; SmiHandlerPorting2.c;
//                SmmChildDispatch2.h
// 
// 2     10/19/12 2:52a Scottyang
// [TAG]       EIP93461
// [Category]  Bug Fix
// [Severity]  Normal
// [Symptom]   System halt when AFUDOS is running with /N /ME command.
// [RootCause] An unexpected BIOSWR_STS is set, it causes BIOS stuck
//             at SMM dispatcher.
// [Solution]  Clear BIOSWR_STS if BIOS Lock Enable is not set.
// [Files]     SmiHandlerPorting2.c; SmmChildDispatch2Main.c
//             SmmChildDispatcher2.sdl; SmmChildDispatch2.h
//             SB\SBGeneric.c
// 
// 1     2/08/12 8:28a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmChildDispatch2.h
//
// Description: SMM Child dispatcher II functions and data structures
//              definition.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SMM_CHILD_DISPATCH2__H__
#define __SMM_CHILD_DISPATCH2__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <AmiDxeLib.h>

#include <Protocol\SmmSwDispatch2.h>
#include <Protocol\SmmSxDispatch2.h>
#include <Protocol\SmmPeriodicTimerDispatch2.h>
#include <Protocol\SmmUsbDispatch2.h>
#include <Protocol\SmmGpiDispatch2.h>
#include <Protocol\SmmStandbyButtonDispatch2.h>
#include <Protocol\SmmPowerButtonDispatch2.h>
#include <Protocol\SmmIoTrapDispatch2.h>

#define SMM_CHILD_DISPATCHER2_GUID \
    {0x950c3a26, 0xe0c2, 0x491c, 0xb6, 0xb2, 0x3, 0x74, 0xf5, 0xc7, 0x3b, 0x96}

#pragma pack(push, 1)

typedef enum {
    EfiSmmSwSmi2,
    EfiSmmSxSmi2,
    EfiSmmPeriodicTimerSmi2,
    EfiSmmUsbSmi2,
    EfiSmmGpiSmi2,
    EfiSmmStandbyButtonSmi2,
    EfiSmmPowerButtonSmi2,
    EfiSmmIoTrapSmi2,
    EfiSmmMaxSmi2
} EFI_SMM_SMI2;

typedef struct {
    EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT     OrgContext;
    UINT64                                      ElapsedTime;
} EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT;

typedef union {
    EFI_SMM_SW_REGISTER_CONTEXT                 SwContext;
    EFI_SMM_SX_REGISTER_CONTEXT                 SxContext;
    EFI_SMM_PERIODIC_TIMER_EXT_REGISTER_CONTEXT TimerContext;
    EFI_SMM_USB_REGISTER_CONTEXT                UsbContext;
    EFI_SMM_GPI_REGISTER_CONTEXT                GpiContext;
    EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT     SBtnContext;
    EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT       PBtnContext;
    EFI_SMM_IO_TRAP_REGISTER_CONTEXT            IoTrapContext;
} EFI_SMM_SMI_CONTEXT2;

typedef EFI_STATUS ( *SMI_GENERIC_CALLBACK2 ) (
    IN EFI_HANDLE           DispatchHandle,
    IN CONST VOID           *DispatchContext OPTIONAL,
    IN OUT VOID             *CommBuffer OPTIONAL,
    IN OUT UINTN            *CommBufferSize OPTIONAL
);

typedef struct {
    DLINK                   Link;
    UINT32                  Signature;
    SMI_GENERIC_CALLBACK2   Callback;
    UINT8                   Context[1];
} HANDLER_LINK2;

//---------------------------------------------------------------------------
//                SMI Handler protocol functions prototypes
//---------------------------------------------------------------------------

typedef EFI_STATUS ( *ADD_HANDLER2 ) (
    IN VOID                 *Context
);

typedef EFI_STATUS ( *REMOVE_HANDLER2 ) (
    IN VOID                 *Context
);

typedef EFI_STATUS ( *VERIFY_CONTEXT2) (
    IN VOID                 *Context
);

typedef BOOLEAN ( *GET_CONTEXT2 ) (
    VOID
);

typedef EFI_STATUS ( *DISPATCH_SMI2 ) (
    VOID
);

typedef struct {
    ADD_HANDLER2            AddHandler;
    REMOVE_HANDLER2         RemoveHandler;
    VERIFY_CONTEXT2         VerifyContext;
    GET_CONTEXT2            GetContext;
    DISPATCH_SMI2           DispatchSmi;
} SMI_HANDLER_PROTOCOL2;

typedef struct {
    EFI_SMM_SMI2            SmiType;
    SMI_HANDLER_PROTOCOL2   HandlerProtocol;
    DLIST                   RegisteredCallbacks;
} SMM_CHILD_DISPATCHER2;

#pragma pack(pop)

//---------------------------------------------------------------------------
//                         SW SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmSwAddHandler2( IN VOID *Context );
EFI_STATUS  SmmSwRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmSwVerifyContext2( IN VOID *Context );
BOOLEAN     SmmSwGetContext2( VOID );
EFI_STATUS  SmmSwDispatchSmi2( VOID );

//---------------------- SW SMI Handler Porting hooks -----------------------

VOID        SwSmiEnable( VOID );
VOID        SwSmiDisable( VOID );
VOID        SwSmiClear( VOID );
BOOLEAN     SwSmiDetect( OUT UINT16 *Type );
UINTN       GetEAX( VOID );

//---------------------------------------------------------------------------
//                         SX SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmSxAddHandler2( IN VOID *Context );
EFI_STATUS  SmmSxRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmSxVerifyContext2( IN VOID *Context );
BOOLEAN     SmmSxGetContext2( VOID );
EFI_STATUS  SmmSxDispatchSmi2( VOID );

//---------------------- SX SMI Handler Porting hooks -----------------------

VOID        SxSmiEnable( VOID );
VOID        SxSmiDisable( VOID );
VOID        SxSmiClear( VOID );
VOID        PutToSleep( IN VOID *Context );
BOOLEAN     SxSmiDetect( OUT UINT16 *Type );

//---------------------------------------------------------------------------
//                   Periodic timer SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmTimerAddHandler2( IN VOID *Context );
EFI_STATUS  SmmTimerRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmTimerVerifyContext2( IN VOID *Context );
BOOLEAN     SmmTimerGetContext2( VOID );
EFI_STATUS  SmmTimerDispatchSmi2( VOID );

//---------------- Periodic timer SMI Handler Porting hooks -----------------

VOID        TimerSmiEnable2( VOID );
VOID        TimerSmiDisable2( VOID );
VOID        TimerSmiClear2( VOID );
BOOLEAN     TimerSmiDetect2( OUT UINT16 *Type );
VOID        TimerSetInterval2( IN UINT64 Interval);

//---------------------------------------------------------------------------
//                         USB SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmUsbAddHandler2( IN VOID *Context );
EFI_STATUS  SmmUsbRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmUsbVerifyContext2( IN VOID *Context );
BOOLEAN     SmmUsbGetContext2( VOID );
EFI_STATUS  SmmUsbDispatchSmi2( VOID );

//---------------------- USB SMI Handler Porting hooks ----------------------

VOID        UsbSmiSet( IN UINT16 ControllerType );
VOID        UsbSmiClear( IN UINT16 ControllerType );
BOOLEAN     UsbSmiDetect( OUT UINT16 *Type );
UINT16      GetControllerType( OUT EFI_DEVICE_PATH_PROTOCOL *Device );

//---------------------------------------------------------------------------
//                         GPI SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmGpiAddHandler2( IN VOID *Context );
EFI_STATUS  SmmGpiRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmGpiVerifyContext2( IN VOID *Context );
BOOLEAN     SmmGpiGetContext2( VOID );
EFI_STATUS  SmmGpiDispatchSmi2( VOID );

//---------------------- GPI SMI Handler Porting hooks ----------------------

VOID        GpiSmiSet( IN UINT32 GpiEnableBit );
VOID        GpiSmiReset( IN UINT32 GpiDisableBit );
VOID        GpiSmiClear( IN UINT32 GpiClearBit );
BOOLEAN     GpiSmiDetect( OUT UINT32 *Gpi );
UINT32      ConvertGpi ( IN UINTN Gpi );

//---------------------------------------------------------------------------
//                  Standby button SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmSButtonAddHandler2( IN VOID *Context );
EFI_STATUS  SmmSButtonRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmSButtonVerifyContext2( IN VOID *Context );
BOOLEAN     SmmSButtonGetContext2( VOID );
EFI_STATUS  SmmSButtonDispatchSmi2( VOID );

//---------------- Standby button SMI Handler Porting hooks -----------------

VOID        SButtonSmiEnable( VOID );
VOID        SButtonSmiDisable( VOID );
VOID        SButtonSmiClear( VOID );
BOOLEAN     SButtonSmiDetect( OUT UINT16 *Type );

//---------------------------------------------------------------------------
//                   Power button SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmPButtonAddHandler2( IN VOID *Context );
EFI_STATUS  SmmPButtonRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmPButtonVerifyContext2( IN VOID *Context );
BOOLEAN     SmmPButtonGetContext2( VOID );
EFI_STATUS  SmmPButtonDispatchSmi2( VOID );

//---------------- Power button SMI Handler Porting hooks -------------------

VOID        PButtonSmiEnable( VOID );
VOID        PButtonSmiDisable( VOID );
VOID        PButtonSmiClear( VOID );
BOOLEAN     PButtonSmiDetect( OUT UINT16 *Type );

//---------------------------------------------------------------------------
//                     I/O Trap SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmIoTrapAddHandler2( IN VOID *Context );
EFI_STATUS  SmmIoTrapRemoveHandler2( IN VOID *Context );
EFI_STATUS  SmmIoTrapVerifyContext2( IN VOID *Context );
BOOLEAN     SmmIoTrapGetContext2( VOID );
EFI_STATUS  SmmIoTrapDispatchSmi2( VOID );

//------------------ I/O Trap SMI Handler Porting hooks ---------------------

VOID        IoTrapSmiSet2( IN EFI_SMM_IO_TRAP_REGISTER_CONTEXT *Context, \
                          OUT UINT32                         *TrapRegIndex );
VOID        IoTrapSmiReset2( IN EFI_SMM_IO_TRAP_REGISTER_CONTEXT *Context, \
                            OUT UINT32                       *TrapRegIndex );
VOID        IoTrapSmiEnable2( VOID );
VOID        IoTrapSmiDisable2( VOID );
VOID        IoTrapSmiClear2( VOID );
BOOLEAN     IoTrapSmiDetect2( OUT EFI_SMM_IO_TRAP_REGISTER_CONTEXT *Context, \
                             OUT UINT32                   *IoTrapWriteDara );

//---------------------------------------------------------------------------
//                      All purpose SMI Porting hooks
//---------------------------------------------------------------------------
VOID        ClearAllSmi( VOID );
                                        // [EIP93461]>
VOID        SbSmiWorkaround2( VOID );
                                        // <[EIP93461]
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
