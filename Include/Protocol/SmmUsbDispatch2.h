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

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/SMM/SmmUsbDispatch2.h 2     3/04/11 3:36p Markw $
//
// $Revision: 2 $
//
// $Date: 3/04/11 3:36p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmUsbDispatch2.h $
// 
// 2     3/04/11 3:36p Markw
// Update headers.
// 
// 1     2/07/11 4:04p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support
// [Files]  		mm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
// SmmDispatcher.h, SmmDispatcher.c,
// Smst.c, SmmPiSmst.c, SmmInit.c, SmmBase.c, SmmBase2.c,
// SmmDriverDispatcher.c, Smm Framewwork Protocol files, SmmPi.h,
// Smm Pi Protocol files, SmmPciRbio files
// 
// 3     7/08/09 8:02p Markw
// Update headers.
// 
// 2     3/28/07 2:43p Markw
// 
//**********************************************************************


//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name: SmmUsbDispatch.h
//
// Description:	Smm Usb Dispatch Protocol header.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef __SMM_USB_DISPATCH_PROTOCOL2_H__
#define __SMM_USB_DISPATCH_PROTOCOL2_H__
#if PI_SPECIFICATION_VERSION >= 0x0001000A

#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>
#include <SmmPi.h>


#ifndef SMM_USB_DEF
#define SMM_USB_DEF

//********************************************************
// EFI_USB_SMI_TYPE
//********************************************************
typedef enum {
	UsbLegacy, UsbWake
} EFI_USB_SMI_TYPE;

//********************************************************
// EFI_SMM_USB_DISPATCH_CONTEXT
//********************************************************
typedef struct {
	EFI_USB_SMI_TYPE			Type;
	EFI_DEVICE_PATH_PROTOCOL	*Device;
} EFI_SMM_USB_DISPATCH_CONTEXT;

#endif

/////////////////////////////////////////////////////
// PI 1.1 Definitions
////////////////////////////////////////////////////

#define EFI_SMM_USB_DISPATCH2_PROTOCOL_GUID \
    {0xee9b8d90, 0xc5a6, 0x40a2, 0xbd, 0xe2, 0x52, 0x55, 0x8d, 0x33, 0xcc, 0xa1} 

GUID_VARIABLE_DECLARATION(gEfiSmmUsbDispatch2ProtocolGuid,EFI_SMM_USB_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_USB_DISPATCH2_PROTOCOL EFI_SMM_USB_DISPATCH2_PROTOCOL;

///
/// The dispatch function's context.
///
typedef struct {
  ///
  /// Describes whether this child handler will be invoked in response to a USB legacy 
  /// emulation event, such as port-trap on the PS/2* keyboard control registers, or to a 
  /// USB wake event, such as resumption from a sleep state.
  ///
  EFI_USB_SMI_TYPE          Type;
  ///
  /// The device path is part of the context structure and describes the location of the 
  /// particular USB host controller in the system for which this register event will occur.
  /// This location is important because of the possible integration of several USB host 
  /// controllers in a system.
  ///
  EFI_DEVICE_PATH_PROTOCOL  *Device;
} EFI_SMM_USB_REGISTER_CONTEXT;


/**
  Provides the parent dispatch service for the USB SMI source generator.

  This service registers a function (DispatchFunction) which will be called when the USB-
  related SMI specified by RegisterContext has occurred. On return, DispatchHandle 
  contains a unique handle which may be used later to unregister the function using UnRegister().
  The DispatchFunction will be called with Context set to the same value as was passed into 
  this function in RegisterContext and with CommBuffer containing NULL and 
  CommBufferSize containing zero.

  @param[in]  This               Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL instance.
  @param[in]  DispatchFunction   Function to register for handler when a USB-related SMI occurs. 
  @param[in]  RegisterContext    Pointer to the dispatch function's context.
                                 The caller fills this context in before calling
                                 the register function to indicate to the register
                                 function the USB SMI types for which the dispatch
                                 function should be invoked.
  @param[out] DispatchHandle     Handle generated by the dispatcher to track the function instance.

  @retval EFI_SUCCESS            The dispatch function has been successfully
                                 registered and the SMI source has been enabled.
  @retval EFI_DEVICE_ERROR       The driver was unable to enable the SMI source.
  @retval EFI_INVALID_PARAMETER  RegisterContext is invalid. The USB SMI type
                                 is not within valid range.
  @retval EFI_OUT_OF_RESOURCES   There is not enough memory (system or SMM) to manage this child.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SMM_USB_REGISTER2)(
  IN  CONST EFI_SMM_USB_DISPATCH2_PROTOCOL  *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2    DispatchFunction,
  IN  CONST EFI_SMM_USB_REGISTER_CONTEXT    *RegisterContext,
  OUT       EFI_HANDLE                      *DispatchHandle
  );

/**
  Unregisters a USB service.

  This service removes the handler associated with DispatchHandle so that it will no longer be 
  called when the USB event occurs.

  @param[in]  This               Pointer to the EFI_SMM_USB_DISPATCH2_PROTOCOL instance.
  @param[in]  DispatchHandle     Handle of the service to remove. 

  @retval EFI_SUCCESS            The dispatch function has been successfully
                                 unregistered and the SMI source has been disabled
                                 if there are no other registered child dispatch
                                 functions for this SMI source.
  @retval EFI_INVALID_PARAMETER  The DispatchHandle was not valid.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_SMM_USB_UNREGISTER2)(
  IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                      DispatchHandle
  );

///
/// Interface structure for the SMM USB SMI Dispatch2 Protocol
///
/// This protocol provides the parent dispatch service for the USB SMI source generator.
///
struct _EFI_SMM_USB_DISPATCH2_PROTOCOL {
  EFI_SMM_USB_REGISTER2    Register;
  EFI_SMM_USB_UNREGISTER2  UnRegister;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
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
