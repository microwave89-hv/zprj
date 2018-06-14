//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
// $Header: /Alaska/SOURCE/Modules/SMM/SmmUsbDispatch.h 5     4/06/11 5:55p Markw $
//
// $Revision: 5 $
//
// $Date: 4/06/11 5:55p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/SMM/SmmUsbDispatch.h $
// 
// 5     4/06/11 5:55p Markw
// Remove Smm.h include.
// 
// 4     2/07/11 3:38p Markw
// [TAG]  		EIP53481
// [Category]  	New Feature
// [Description]  	Add PIWG 1.1 SMM support.
// Small header update.
// [Files]  		Smm.sdl, SmmPrivateShared.h, SmmDispatcher.mak,
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

#ifndef __SMM_USB_DISPATCH_PROTOCOL_H__
#define __SMM_USB_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <EFI.h>

#define EFI_SMM_USB_DISPATCH_PROTOCOL_GUID \
	{0xa05b6ffd, 0x87af, 0x4e42, 0x95, 0xc9, 0x62, 0x28, 0xb6, 0x3c, 0xf3, 0xf3}

GUID_VARIABLE_DECLARATION(gEfiSmmUsbDispatchProtocolGuid,EFI_SMM_USB_DISPATCH_PROTOCOL_GUID);

typedef struct _EFI_SMM_USB_DISPATCH_PROTOCOL EFI_SMM_USB_DISPATCH_PROTOCOL;

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

//********************************************************
// EFI_SMM_USB_DISPATCH
//********************************************************
typedef VOID (EFIAPI *EFI_SMM_USB_DISPATCH) (
	IN EFI_HANDLE					DispatchHandle,
	IN EFI_SMM_USB_DISPATCH_CONTEXT	*DispatchContext
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_USB_REGISTER) (
	IN EFI_SMM_USB_DISPATCH_PROTOCOL	*This,
	IN EFI_SMM_USB_DISPATCH				DispatchFunction,
	IN EFI_SMM_USB_DISPATCH_CONTEXT		*DispatchContext,
	OUT EFI_HANDLE						*DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_USB_UNREGISTER) (
	IN EFI_SMM_USB_DISPATCH_PROTOCOL	*This,
	IN EFI_HANDLE						DispatchHandle
);

struct _EFI_SMM_USB_DISPATCH_PROTOCOL {
	EFI_SMM_USB_REGISTER	Register;
	EFI_SMM_USB_UNREGISTER	UnRegister;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
