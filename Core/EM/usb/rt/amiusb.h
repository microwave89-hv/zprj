//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/rt/amiusb.h 40    10/16/16 10:15p Wilsonlee $
//
// $Revision: 40 $
//
// $Date: 10/16/16 10:15p $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/rt/amiusb.h $
// 
// 40    10/16/16 10:15p Wilsonlee
// [TAG]  		EIP288158
// [Category]  	Improvement
// [Description]  	Check if gUsbData is integrity.
// [Files]  		amiusb.cif, usbsb.c, AmiUsbLib.cif, AmiUsbLib.sdl,
// AmiUsbSmmGlobalDataValidationLib.c,
// AmiUsbSmmGlobalDataValidationLib.cif,
// AmiUsbSmmGlobalDataValidationLib.mak, Crc32.c, amiusb.c, amiusb.h,
// ehci.c, elib.c, ohci.c, syskbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h,
// usbhid.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c, usbrt.mak, xhci.c,
// amiusbhc.c, efiusbccid.c, efiusbmass.c, uhcd.c, usbmisc.c,
// AmiUsbController.h, AmiUsbLibInclude.cif,
// AmiUsbSmmGlobalDataValidationLib.h
// 
// 39    3/02/16 9:44p Wilsonlee
// [TAG]  		EIP254309
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	GK-FORCE K83 USB KB function abnormal.
// [RootCause]  	This device has an interrupt out endpoint and doesn't
// support "Set Report" request.
// [Solution]  	Use the interrupt out endpoint instead of sending "Set
// Report" request.
// [Files]  		AmiUsbController.h, xhci.c, usbmass.c, usbkbd.h, usbkbd.c,
// usbhub.c, usbhid.c, usbdef.h, usbCCID.c, usb.c, uhci.c, ohci.c, ehci.c,
// amiusb.h, efiusbms,c, amiusbhc.c
// 
// 38    9/01/15 10:18p Wilsonlee
// [TAG]  		EIP235482
// [Category]  	Improvement
// [Description]  	Select this alternate setting for multiple TTs hubs.
// [Files]  		usbhub.c, usb.c, amiusb.h, usbdef.h
// 
// 37    4/10/15 3:09a Wilsonlee
// [TAG]  		EIP207413
// [Category]  	Improvement
// [Description]  	Install UsbApiTable and UsbMassApitTable in
// AmiUsbSmmProtocol.
// [Files]  		amiusbhc.c, AmiUsbController.h, usbdef.h, usbCCID.c, uhci.c,
// ehci.c, amiusbrtCCID.h, amiusb.h, amiusb.c, uhcd.c
// 
// 36    3/08/15 10:51p Wilsonlee
// [TAG]  		EIP207774
// [Category]  	Improvement
// [Description]  	Set USB_FLAG_DRIVER_STARTED flag when HC is running and
// clear it if we don't start any HC.
// [Files]  		uhci.c, usb.c, ehci.c, ohci.c, xhci.c, amiusb.h
// 
// 35    4/29/14 8:14p Wilsonlee
// [TAG]  		EIP163828
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	The mouses stop more than 4 seconds during TP 0xB4 when
// power on several times.
// [RootCause]  	The device sometime doesn't respond the set report
// command.
// [Solution]  	Change the timeout of set report command to 100 ms.
// [Files]  		syskbc.c, sysnokbc.c, usbhid.c, amiusb.h
// 
// 34    1/23/13 5:14a Ryanchou
// [TAG]  		EIP111280
// [Category]  	Improvement
// [Description]  	Add USB APIs for external driver.
// [Files]  		amiusb.c, amiusb.h, usbdef.h
// 
// 33    11/10/12 6:43a Ryanchou
// [TAG]  		EIP99431
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Cannot use the UsbIo's UsbAsyncInterruptTransfer for
// keyboard input
// [RootCause]  	Stopping EFI USB keyboard driver does not stop the
// endpoint polling, then application calls UsbAsyncInterruptTransfer,
// error will be returned.
// [Solution]  	Stops endpoint polling and release resource when
// disconnecting the device driver. And improve the
// UsbSyncInterruptTransfer.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhci.c, usb.c,
// usbCCID.c, usbdef.h, usbhub.c, usbkbd.c, usbmass.c, usbms.c,
// usbpoint.c, amiusbhc.c, efiusbhid.c, usbbus.c, usbbus.h
// 
// 32    9/28/12 2:36a Wilsonlee
// [TAG]  		EIP93154
// [Category]  	Improvement
// [Description]  	Change the unit of the FixedDelay from 15 us to 1 us.
// [Files]  		amiusb.h, xhci.c, ehci.c, ohci.c, uhci.c, usb.c, usbCCID.c,
// usbmass.c, usbhub.c, elib.c
// 
// 31    8/29/12 8:40a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 30    8/07/12 9:40p Wilsonlee
// [TAG]  		EIP96366
// [Category]  	New Feature
// [Description]  	Add the token "DEFAULT_USB_EMUL6064_OPTION" that
// control the default value of the I/O port 60h/64h emulation support
// option.
// [Files]  		usb.sd, usb.sdl, amiusb.c, amiusb.h
// 
// 29    5/04/12 6:44a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 28    1/13/12 4:29a Ryanchou
// [TAG]  		EIP47348
// [Category]  	New Feature
// [Description]  	Support for USB Port Reset function.
// [Files]  		amiusb.c, amiusb.h, amiusbhc.c, uhci.c, usb.c, usbbus.c,
// usbbus.h, usbmass.c
// 
// 27    11/08/11 8:25a Wilsonlee
// [TAG]  		EIP74876
// [Category]  	New Feature
// [Description]  	Add USB API for shutdown single USB controller.
// [Files]  		amiusb.c, amiusb.h, usb.c, usbdef.h, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 26    7/12/11 8:16a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 25    4/06/11 3:30a Tonylo
// [TAG]  		EIP57354
// [Category]  	Improvement
// [Description]  	Core 4.6.5.0 compliant. UEFI 2.3 and PI 1.x support.
// 
// 24    3/29/11 10:21a Ryanchou
// [TAG]  		EIP53518
// [Category]  	Improvement
// [Description]  	Added chipset xHCI chip support.
// [Files]  		amiusb.c, amiusb.h, ehci.c, ohci.c, uhcd.c, uhci.c, usb.c,
// usb.sdl, usbdef.h, usbport, usbsb.c, xhci.c
// 
// 23    11/22/10 8:45a Ryanchou
// [TAG]  		EIP48064
// [Category]  	Improvement
// [Description]  	The SB template implemented elink
// AcpiEnableCallbackList, the XHCI/EHCI hand off function should be
// invoked via the elink AcpiEnableCallbackList.
// [Files]  		amidef.h, amiusb.c, amiusb.dxs, amiusb.h,
// AmiUsbController.h, usb.sdl, usbrt.mak, usbsb.c
// 
// 22    7/15/10 4:43a Tonylo
// EIP15489 - Add USB HandOff function for shurdown/init USB legacy
// through USB API function.
// 
// 21    4/02/10 9:00a Olegi
// 
// 20    3/19/10 10:06a Olegi
// 
// 19    3/11/10 9:17a Olegi
// 
// 18    2/27/10 12:01p Olegi
// 
// 17    1/27/10 4:38p Olegi
// 
// 16    12/23/09 11:59a Olegi
// 
// 15    12/22/09 9:02a Olegi
// 
// 14    11/24/09 11:34a Olegi
// EIP#29733 - BIOS adds an USB API (Block KBC Access)
// 
// 13    11/13/09 9:14a Olegi
// 
// 12    10/30/09 5:48p Olegi
// 
// 11    10/02/09 10:50a Olegi
// Code cleanup.
// 
// 10    5/16/08 12:03p Olegi
// Compliance with AMI coding standard.
// 
// 9     12/17/07 4:04p Olegi
// KBC emulation support added.
// 
// 7     3/20/06 3:38p Olegi
// Version 8.5 - x64 compatible.
//
// 3     8/05/05 3:38p Andriyn
// Complience with EFI EDK
//
// 2     6/03/05 6:34p Andriyn
// EFI_SMM_USB_DISPATCH_CONTEXT param was added to SMI handlers to comply
// with Aptio framework
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           AmiUsb.h
//
//  Description:    AMI UsbRt driver definitions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _EFI_USB_H
#define _EFI_USB_H

#include "token.h"

#include <Protocol\DevicePath.h>
#if USB_RUNTIME_DRIVER_IN_SMM
#include <Protocol\SmmBase.h>
					                            //(EIP57354)>
#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x0001000A)
#include <Protocol\SmmControl2.h>
#else
#include <Protocol\SmmControl.h>
#endif
					                            //<(EIP57354)
#include <Protocol\SmmSwDispatch.h>
#include <Protocol\SmmUSBDispatch.h>
#endif

#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\AmiUsbController.h>
#include <Protocol\LoadedImage.h>
#include <Protocol\BlockIo.h>
#include <Protocol\PciIo.h>
#include <Protocol\SimplePointer.h>
#include <Protocol\SimpleTextIn.h>
#include <Protocol\ComponentName.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\FirmwareVolume.h >
#include <Protocol\UsbPolicy.h>
#include <Protocol\Emul6064Kbdinput.h>
#include <Protocol\Emul6064MsInput.h>
#include <Protocol\Emul6064Trap.h>
#include "usbdef.h"

EFI_STATUS
USBDriverEntryPoint(
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );


#if USB_RUNTIME_DRIVER_IN_SMM
VOID
USBSWSMIHandler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_SW_DISPATCH_CONTEXT   *DispatchContext
  );

VOID
UhciHWSMIHandler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  *DispatchContext
  );

VOID
OhciHWSMIHandler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  *DispatchContext
  );

VOID
EhciHWSMIHandler (
  IN  EFI_HANDLE                    DispatchHandle,
  IN  EFI_SMM_USB_DISPATCH_CONTEXT  *DispatchContext
  );

VOID
XhciHwSmiHandler (
  IN	EFI_HANDLE	DispatchHandle,
  IN	VOID  		*DispatchContext
  );
#endif

VOID		UsbApiHandler(VOID*);
EFI_STATUS	InstallUsbProtocols(VOID);

VOID
Emul6064TrapCallback (
  IN    EFI_EVENT       Event,
  IN    VOID            *Context
  );

EFI_STATUS	UsbInstallHwSmiHandler(HC_STRUC*);

UINT8   ByteReadIO (UINT16);
VOID    ByteWriteIO (UINT16, UINT8);
UINT32  ReadPCIConfig(UINT16, UINT8);
VOID    WordWritePCIConfig(UINT16, UINT8, UINT16);
UINT32  DwordReadMem(UINT32, UINT16);
VOID USBAPI_CheckPresence(URP_STRUC*);          // API 00h
VOID USBAPI_Start(URP_STRUC*);                  // API 20h
VOID USBAPI_Stop(URP_STRUC*);                   // API 21h
VOID USBAPI_DisableInterrupts(URP_STRUC*);      // API 22h
VOID USBAPI_EnableInterrupts(URP_STRUC*);       // API 23h
VOID USBAPI_MoveDataArea(URP_STRUC*);           // API 24h
VOID USBAPI_GetDeviceInfo(URP_STRUC*);          // API 25h
VOID USBAPI_CheckDevicePresence(URP_STRUC*);    // API 26h
VOID USBAPI_MassDeviceRequest(URP_STRUC*);      // API 27h
VOID USBAPI_PowerManageUSB(URP_STRUC*);         // API 28h
VOID USBAPI_PrepareForOS(URP_STRUC*);           // API 29h
VOID USBAPI_SecureInterface(URP_STRUC*);        // API 2Ah
VOID USBAPI_LightenKeyboardLEDs(URP_STRUC*);    // API 2Bh
VOID USBAPI_ChangeOwner(URP_STRUC*);            // API 2Ch
VOID USBAPI_HC_Proc(URP_STRUC*);                // API 2Dh
VOID USBAPI_Core_Proc(URP_STRUC*);              // API 2eh
VOID USBAPI_LightenKeyboardLEDs_Compatible(URP_STRUC*);    // API 2Fh
VOID USBAPI_KbcAccessControl(URP_STRUC*);       // API 30h      //(EIP29733+)
VOID USBAPI_LegacyControl(URP_STRUC*);       // API 31h      //
VOID USBAPI_GetDeviceAddress(URP_STRUC*);		// API 32h
VOID USBAPI_ExtDriverRequest(URP_STRUC*);		// API 33h
VOID USBAPI_CCIDRequest(URP_STRUC*);            // API 34h      
VOID USBAPI_UsbStopController(URP_STRUC*);      // API 35h	//(EIP74876+)
VOID USBAPI_HcStartStop(URP_STRUC *Urp);		// API 36h

VOID USBMassAPIGetDeviceInformation(URP_STRUC*);    // USB Mass API Sub-Func 00h
VOID USBMassAPIGetDeviceGeometry(URP_STRUC*);       // USB Mass API Sub-Func 01h
VOID USBMassAPIResetDevice(URP_STRUC*);             // USB Mass API Sub-Func 02h
VOID USBMassAPIReadDevice(URP_STRUC*);              // USB Mass API Sub-Func 03h
VOID USBMassAPIWriteDevice(URP_STRUC*);             // USB Mass API Sub-Func 04h
VOID USBMassAPIVerifyDevice(URP_STRUC*);            // USB Mass API Sub-Func 05h
VOID USBMassAPIFormatDevice(URP_STRUC*);            // USB Mass API Sub-Func 06h
VOID USBMassAPICommandPassThru(URP_STRUC*);         // USB Mass API Sub-Func 07h
VOID USBMassAPIAssignDriveNumber(URP_STRUC*);       // USB BIOS API function 08h
VOID USBMassAPICheckDevStatus(URP_STRUC*);          // USB BIOS API function 09h
VOID USBMassAPIGetDevStatus(URP_STRUC*);            // USB BIOS API function 0Ah
VOID USBMassAPIGetDeviceParameters(URP_STRUC*);     // USB BIOS API function 0Bh

DEV_INFO*   USBWrap_GetnthDeviceInfoStructure(UINT8);
VOID        USBWrap_GetDeviceCount(URP_STRUC*);
UINT8       USBWrapGetATAErrorCode(UINT32);
UINT16      USBMassRWVCommand(DEV_INFO*, UINT8, VOID*);
UINT8*      USB_GetDescriptor(HC_STRUC*, DEV_INFO*, UINT8*, UINT16, UINT8, UINT8);
UINT8		UsbSetInterface(HC_STRUC*, DEV_INFO*, UINT8);

UINT32      USB_ReConfigDevice(HC_STRUC*, DEV_INFO*);
UINT32      USB_ReConfigDevice2(HC_STRUC*, DEV_INFO*, CNFG_DESC*, INTRF_DESC*);
DEV_INFO*   UsbAllocDevInfo();
VOID        prepareForLegacyOS();
UINT32      USB_ResetAndReconfigDev(HC_STRUC*, DEV_INFO*);
UINT32		USB_DevDriverDisconnect(HC_STRUC*, DEV_INFO*);
VOID        USBKB_LEDOn();


EFI_DEVICE_PATH_PROTOCOL *AppendDevicePath (EFI_DEVICE_PATH_PROTOCOL*, EFI_DEVICE_PATH_PROTOCOL*);

UINT8        USB_StartHostControllers(USB_GLOBAL_DATA*);
UINT8        USB_StopHostControllers(USB_GLOBAL_DATA*);
EFI_STATUS	 InitializeUsbGlobalData(VOID);
UINT8        UsbHcStart(HC_STRUC*);
UINT8        UsbHcStop(HC_STRUC*);
VOID         FixedDelay(UINTN);
DEV_INFO*    USB_GetDeviceInfoStruc(UINT8, DEV_INFO*, UINT8, HC_STRUC*);
UINT8        USBMassGetDeviceInfo(MASS_GET_DEV_INFO*);
UINT8        USBMassGetDeviceGeometry(MASS_GET_DEV_GEO*);

UINT16       USBMassStartUnitCommand (DEV_INFO*);
UINT8        USBMassCmdPassThru (MASS_CMD_PASS_THRU*);
UINT8        USBMassGetDeviceStatus (MASS_GET_DEV_STATUS*);
UINT32       USBMassCheckDeviceReady(DEV_INFO*);
MASS_INQUIRY *USBMassGetDeviceParameters(DEV_INFO*);
VOID         InitSysKbc(EFI_EMUL6064KBDINPUT_PROTOCOL**, EFI_EMUL6064MSINPUT_PROTOCOL**);
EFI_STATUS   InSmmFunction(EFI_HANDLE, EFI_SYSTEM_TABLE*);
VOID         UsbPeriodicEvent();
DEV_INFO*    USB_DetectNewDevice(HC_STRUC*, UINT8, UINT8, UINT8);
UINT8        USB_EnableEndpointsDummy (HC_STRUC*, DEV_INFO*, UINT8*);
UINT8        USB_InitDeviceDataDummy (HC_STRUC*,DEV_INFO*,UINT8,UINT8**);
UINT8        USB_DeinitDeviceDataDummy (HC_STRUC*,DEV_INFO*);
VOID*        USB_MemAlloc(UINT16);
UINT8        USB_MemFree(VOID*, UINT16);
UINT8        USBCheckPortChange (HC_STRUC*, UINT8, UINT8);
VOID         UsbKbcAccessControl(UINT8);
EFI_STATUS   USBRT_LegacyControl (VOID *fpURP);
VOID         USB_StopUnsupportedHc();
UINT8        UsbControlTransfer(HC_STRUC*, DEV_INFO*, DEV_REQ, UINT16, VOID*);
UINT8        UsbInterruptTransfer(HC_STRUC*, DEV_INFO*, UINT8, UINT16, VOID*, UINT16, UINT16);
VOID         CheckBiosOwnedHc(VOID);
DEV_DRIVER*  UsbFindDeviceDriverEntry(DEV_DRIVER*);

#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
