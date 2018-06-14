//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/RT/guids.c 21    8/08/11 5:28a Ryanchou $
//
// $Revision: 21 $
//
// $Date: 8/08/11 5:28a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/RT/guids.c $
// 
// 21    8/08/11 5:28a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 20    10/02/09 10:49a Olegi
// Code cleanup.
// 
// 19    2/04/09 12:54p Olegi
// Added NonSmmEmul6064TrapProtocol GUID definition.
// 
// 18    9/24/08 10:19a Rameshraju
// Removed Usblegacyplatform support.
// 
// 17    5/16/08 12:01p Olegi
// Compliance with AMI coding standard.
// 
// 16    12/17/07 4:04p Olegi
// KBC emulation support added.
// 
// 15    3/20/07 12:22p Olegi
//
// 14    11/15/06 3:42p Olegi
//
// 13    10/26/06 3:58p Olegi
//
// 12    5/03/06 9:59a Olegi
//
// 11    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 10    3/13/06 3:24p Felixp
//
// 9     3/01/06 3:51p Olegi
//
// 8     11/10/05 11:11a Olegi
//
// 7     10/20/05 2:44p Olegi
//
// 6     8/27/05 11:44a Andriyn
//
// 5     8/23/05 5:53p Olegi
//
// 4     8/05/05 3:38p Andriyn
// Complience with EFI EDK
//
// 3     5/20/05 12:09p Andriyn
//
// 2     5/20/05 11:05a Andriyn
// reconcile Aptio changes with Alaska
//
// 1     3/29/05 10:40a Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           guids.c
//
//  Description:    AMI USB guids library
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>


#include "amiusb.h"
#include    <Protocol\UsbHC.h>
#include    <Protocol\UsbPolicy.h>
#include    <setup.h>

//
// GUID variables
//
//EFI_GUID  mAMIUsbCoreGuid = {0x4eaaaa1, 0x29a1, 0x11d7, 0x88, 0x38, 0x0, 0x50, 0x4, 0x73, 0xd4, 0xeb};
//EFI_GUID  gEfiLoadedImageGuid =
//EFI_GUID gEfiSmmBaseProtocolGuid = EFI_SMM_BASE_PROTOCOL_GUID;
//EFI_GUID gEfiSmmSwDispatchProtocolGuid = EFI_SMM_SW_DISPATCH_PROTOCOL_GUID;
//EFI_GUID gEfiSmmUsbDispatchProtocolGuid = EFI_SMM_USB_DISPATCH_PROTOCOL_GUID;
//EFI_GUID gEfiLoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
//EFI_GUID gEfiDevicePathProtocolGuid   = EFI_DEVICE_PATH_PROTOCOL_GUID;
//EFI_GUID gEfiUSBProtocolGuid = EFI_USB_PROTOCOL_GUID;
//EFI_GUID gEfiSimplePointerProtocolGuid = EFI_SIMPLE_POINTER_PROTOCOL_GUID;
//EFI_GUID gEfiSimpleTextInProtocolGuid = EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID;
//EFI_GUID gEfiDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiHotPlugDeviceGuid = { 0x220ac432, 0x1d43, 0x49e5, 0xa7, 0x4f, 0x4c, 0x9d, 0xa6, 0x7a, 0xd2, 0x3b };
//EFI_GUID gEfiPciIoProtocolGuid = EFI_PCI_IO_PROTOCOL_GUID;
//EFI_GUID gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;
//EFI_GUID gEfiComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
//EFI_GUID gEfiSmmControlProtocolGuid = EFI_SMM_CONTROL_PROTOCOL_GUID;
//EFI_GUID gEfiUsb2HcProtocolGuid = EFI_USB2_HC_PROTOCOL_GUID;
//EFI_GUID gEfiUsbHcProtocolGuid = EFI_USB_HC_PROTOCOL_GUID;
//EFI_GUID gEfiFirmwareVolumeProtocolGuid = EFI_FIRMWARE_VOLUME_PROTOCOL_GUID;
EFI_GUID gEfiUsbPolicyProtocolGuid = EFI_USB_POLICY_PROTOCOL_GUID;
EFI_GUID gEmul6064MsInputProtocolGuid = EFI_EMUL6064MSINPUT_PROTOCOL_GUID;
EFI_GUID gEmul6064KbdInputProtocolGuid = EFI_EMUL6064KBDINPUT_PROTOCOL_GUID;
EFI_GUID gEmul6064TrapProtocolGuid = EFI_EMUL6064TRAP_PROTOCOL_GUID;
EFI_GUID gNonSmmEmul6064TrapProtocolGuid = EFI_NONSMMEMUL6064TRAP_PROTOCOL_GUID;
EFI_GUID gUsbTimingPolicyProtocolGuid = USB_TIMING_POLICY_PROTOCOL_GUID;

EFI_GUID gEfiSetupGuid = SETUP_GUID;


//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
