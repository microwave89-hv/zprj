//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
// $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatch.h 2     4/25/12 9:35a Victortu $
//
// $Revision: 2 $
//
// $Date: 4/25/12 9:35a $
//*************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatch.h $
// 
// 2     4/25/12 9:35a Victortu
// [TAG]         None
// [Category]    Improvement
// [Description] Reprogram SMM ChildDispatcher drivers.
// [Files]       SmiHandlerGeneric.c; SmiHandlerPorting.c;
// SmiHandlerGeneric2.c; SmmChildDispatch2Main.c; SmmChildDispatcher2.mak;
// SmmChildDispatcher2.sdl; SmmChildDispatch.h; SmmChildDispatchMain.c;
// SmmChildDispatchProtocol.c; SmmChildDispatcher.dxs;
// PchSmiDispatcher.sdl
// 
// 1     2/08/12 8:27a Yurenlai
// Intel Lynx Point/SB eChipset initially releases.
// 
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        SmmChildDispatch.h
//
// Description: SMM Child dispatcher functions and data structures
//              definition.
//
//<AMI_FHDR_END>
//*************************************************************************

#ifndef __SMM_CHILD_DISPATCH__H__
#define __SMM_CHILD_DISPATCH__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <AmiDxeLib.h>
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmSxDispatch.h>
#include <Protocol\SmmPeriodicTimerDispatch.h>
#include <Protocol\SmmUsbDispatch.h>
#include <Protocol\SmmGpiDispatch.h>
#include <Protocol\SmmStandbyButtonDispatch.h>
#include <Protocol\SmmPowerButtonDispatch.h>
#include <Protocol\SmmTcoDispatch.h>
#include <Protocol\SmmIoTrapDispatch.h>

#include <Protocol\SmmBiosWriteDispatch.h>

#ifndef INTEL_RC_SMI_DISPATCHER_SUPPORT
#define INTEL_RC_SMI_DISPATCHER_SUPPORT 0
#endif

#pragma pack(push, 1)

typedef enum {
    EfiSmmSwSmi,
    EfiSmmSxSmi,
    EfiSmmPeriodicTimerSmi,
    EfiSmmUsbSmi,
    EfiSmmGpiSmi,
    EfiSmmStandbyButtonSmi,
    EfiSmmPowerButtonSmi,
    EfiSmmTcoSmi,
    EfiSmmIoTrapSmi,
    EfiSmmMaxSmi
} EFI_SMM_SMI;

typedef union {
    EFI_SMM_SW_DISPATCH_CONTEXT             SwContext;
    EFI_SMM_SX_DISPATCH_CONTEXT             SxContext;
    EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT TimerContext;
    EFI_SMM_USB_DISPATCH_CONTEXT            UsbContext;
    EFI_SMM_GPI_DISPATCH_CONTEXT            GpiContext;
    EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT SBtnContext;
    EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT   PBtnContext;
    EFI_SMM_TCO_DISPATCH_CONTEXT            TcoContext;
    EFI_SMM_IO_TRAP_DISPATCH_CONTEXT        IoTrapContext;
} EFI_SMM_SMI_CONTEXT;

typedef VOID ( *SMI_GENERIC_CALLBACK ) (
    IN EFI_HANDLE           DispatchHandle,
    IN VOID                 *DispatchContext
);

typedef struct {
    DLINK                   Link;
    UINT32                  Signature;
    SMI_GENERIC_CALLBACK    Callback;
    UINT8                   Context[1];
} HANDLER_LINK;

typedef VOID ( *SMI_GENERIC_NEW_CALLBACK ) (
	IN EFI_HANDLE           DispatchHandle,
	IN VOID                 *DispatchContext,
	IN OUT VOID             *CommBuffer,
	IN OUT UINTN            *CommBufferSize	
);


typedef struct {
    DLINK                           Link;
    UINT32                          Signature;
    SMI_GENERIC_NEW_CALLBACK        Callback;
    UINT8                           Context[1];
} HANDLER_NEW_LINK;

//---------------------------------------------------------------------------
//                SMI Handler protocol functions prototypes
//---------------------------------------------------------------------------

typedef EFI_STATUS ( *ADD_HANDLER ) (
    IN VOID                 *Context
);

typedef EFI_STATUS ( *REMOVE_HANDLER ) (
    IN VOID                 *Context
);

typedef EFI_STATUS ( *VERIFY_CONTEXT) (
    IN VOID                 *Context
);

typedef BOOLEAN ( *GET_CONTEXT ) (
    VOID
);

typedef VOID ( *DISPATCH_SMI ) (
    VOID
);

typedef struct {
    ADD_HANDLER             AddHandler;
    REMOVE_HANDLER          RemoveHandler;
    VERIFY_CONTEXT          VerifyContext;
    GET_CONTEXT             GetContext;
    DISPATCH_SMI            DispatchSmi;
} SMI_HANDLER_PROTOCOL;

typedef struct {
    EFI_SMM_SMI             SmiType;
    SMI_HANDLER_PROTOCOL    HandlerProtocol;
    DLIST                   RegisteredCallbacks;
} SMM_CHILD_DISPATCHER;

#pragma pack(pop)

//---------------------------------------------------------------------------
//                         SW SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmSwAddHandler( IN VOID *Context );
EFI_STATUS  SmmSwRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmSwVerifyContext( IN VOID *Context );
BOOLEAN     SmmSwGetContext( VOID );
VOID        SmmSwDispatchSmi( VOID );

//---------------------- SW SMI Handler Porting hooks -----------------------

VOID        SwSmiEnable( VOID );
VOID        SwSmiDisable( VOID );
VOID        SwSmiClear( VOID );
BOOLEAN     SwSmiDetect( OUT UINT16 *Type );
UINTN       GetEAX( VOID );

//---------------------------------------------------------------------------
//                         SX SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmSxAddHandler( IN VOID *Context );
EFI_STATUS  SmmSxRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmSxVerifyContext( IN VOID *Context );
BOOLEAN     SmmSxGetContext( VOID );
VOID        SmmSxDispatchSmi( VOID );

//---------------------- SX SMI Handler Porting hooks -----------------------

VOID        SxSmiEnable( VOID );
VOID        SxSmiDisable( VOID );
VOID        SxSmiClear( VOID );
VOID        PutToSleep( IN VOID *Context );
BOOLEAN     SxSmiDetect( OUT UINT16 *Type );

//---------------------------------------------------------------------------
//                   Periodic timer SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmTimerAddHandler( IN VOID *Context );
EFI_STATUS  SmmTimerRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmTimerVerifyContext( IN VOID *Context );
BOOLEAN     SmmTimerGetContext( VOID );
VOID        SmmTimerDispatchSmi( VOID );

//---------------- Periodic timer SMI Handler Porting hooks -----------------

VOID        TimerSmiEnable( VOID );
VOID        TimerSmiDisable( VOID );
VOID        TimerSmiClear( VOID );
BOOLEAN     TimerSmiDetect( OUT UINT16 *Type );
VOID        TimerSetInterval( IN UINT64 Interval);

//---------------------------------------------------------------------------
//                         USB SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmUsbAddHandler( IN VOID *Context );
EFI_STATUS  SmmUsbRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmUsbVerifyContext( IN VOID *Context );
BOOLEAN     SmmUsbGetContext( VOID );
VOID        SmmUsbDispatchSmi( VOID );

//---------------------- USB SMI Handler Porting hooks ----------------------

VOID        UsbSmiSet( IN UINT16 ControllerType );
VOID        UsbSmiClear( IN UINT16 ControllerType );
BOOLEAN     UsbSmiDetect( OUT UINT16 *Type );
UINT16      GetControllerType( OUT EFI_DEVICE_PATH_PROTOCOL *Device );

//---------------------------------------------------------------------------
//                         GPI SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmGpiAddHandler( IN VOID *Context );
EFI_STATUS  SmmGpiRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmGpiVerifyContext( IN VOID *Context );
BOOLEAN     SmmGpiGetContext( VOID );
VOID        SmmGpiDispatchSmi( VOID );

//---------------------- GPI SMI Handler Porting hooks ----------------------

VOID        GpiSmiSet( IN UINT32 GpiEnableBit );
VOID        GpiSmiReset( IN UINT32 GpiDisableBit );
VOID        GpiSmiClear( IN UINT32 GpiClearBit );
BOOLEAN     GpiSmiDetect( OUT UINT32 *Gpi );

//---------------------------------------------------------------------------
//                  Standby button SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmSButtonAddHandler( IN VOID *Context );
EFI_STATUS  SmmSButtonRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmSButtonVerifyContext( IN VOID *Context );
BOOLEAN     SmmSButtonGetContext( VOID );
VOID        SmmSButtonDispatchSmi( VOID );

//---------------- Standby button SMI Handler Porting hooks -----------------

VOID        SButtonSmiEnable( VOID );
VOID        SButtonSmiDisable( VOID );
VOID        SButtonSmiClear( VOID );
BOOLEAN     SButtonSmiDetect( OUT UINT16 *Type );

//---------------------------------------------------------------------------
//                   Power button SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmPButtonAddHandler( IN VOID *Context );
EFI_STATUS  SmmPButtonRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmPButtonVerifyContext( IN VOID *Context );
BOOLEAN     SmmPButtonGetContext( VOID );
VOID        SmmPButtonDispatchSmi( VOID );

//---------------- Power button SMI Handler Porting hooks -------------------

VOID        PButtonSmiEnable( VOID );
VOID        PButtonSmiDisable( VOID );
VOID        PButtonSmiClear( VOID );
BOOLEAN     PButtonSmiDetect( OUT UINT16 *Type );

//---------------------------------------------------------------------------
//                        TCO SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmTcoAddHandler( IN VOID *Context );
EFI_STATUS  SmmTcoRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmTcoVerifyContext( IN VOID *Context );
BOOLEAN     SmmTcoGetContext( VOID );
VOID        SmmTcoDispatchSmi( VOID );

//--------------------- TCO SMI Handler Porting hooks -----------------------

VOID        TcoSmiSet( IN UINT32 TcoBitOffset );
VOID        TcoSmiReset( IN UINT32 TcoBitOffset );
VOID        TcoSmiEnable( VOID );
VOID        TcoSmiDisable( VOID );
VOID        TcoSmiClear( VOID );
BOOLEAN     TcoSmiDetect( OUT UINT32 *TcoStatus );

//---------------------------------------------------------------------------
//                     I/O Trap SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmIoTrapAddHandler( IN VOID *Context );
EFI_STATUS  SmmIoTrapRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmIoTrapVerifyContext( IN VOID *Context );
BOOLEAN     SmmIoTrapGetContext( VOID );
VOID        SmmIoTrapDispatchSmi( VOID );

//------------------ I/O Trap SMI Handler Porting hooks ---------------------

VOID        IoTrapSmiSet( IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *Context );
VOID        IoTrapSmiReset( IN EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *Context );
VOID        IoTrapSmiEnable( VOID );
VOID        IoTrapSmiDisable( VOID );
VOID        IoTrapSmiClear( VOID );
BOOLEAN     IoTrapSmiDetect( OUT EFI_SMM_IO_TRAP_DISPATCH_CONTEXT *Context );

//---------------------------------------------------------------------------
//                    BIOS Write SMI Handler functions
//---------------------------------------------------------------------------

EFI_STATUS  SmmBiosWriteAddHandler( IN VOID *Context );
EFI_STATUS  SmmBiosWriteRemoveHandler( IN VOID *Context );
EFI_STATUS  SmmBiosWriteVerifyContext( IN VOID *Context );
BOOLEAN     SmmBiosWriteGetContext( VOID );
VOID        SmmBiosWriteDispatchSmi( VOID );

//----------------- BIOS Write SMI Handler Porting hooks --------------------

VOID        BiosWriteSmiEnable( VOID );
VOID        BiosWriteSmiDisable( VOID );
VOID        BiosWriteSmiClear( VOID );
BOOLEAN     BiosWriteSmiDetect( VOID );

//---------------------------------------------------------------------------
//                      All purpose SMI Porting hooks
//---------------------------------------------------------------------------
VOID        ClearAllSmi( VOID );

VOID        SbSmiWorkaround( VOID );

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
