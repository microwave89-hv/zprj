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

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/uhcd.h 49    10/16/16 11:19p Wilsonlee $
//
// $Revision: 49 $
//
// $Date: 10/16/16 11:19p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/uhcd.h $
// 
// 49    10/16/16 11:19p Wilsonlee
// [TAG]  		EIP284071
// [Category]  	Improvement
// [Description]  	Clear USBDataPt from EFI_USB_PROTOCOL at the
// readytoboot event.
// [Files]  		uhcd.c, uhcd.h
// 
// 48    7/07/16 1:13a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 47    1/19/16 3:19a Wilsonlee
// [TAG]  		EIP251667
// [Category]  	Improvement
// [Description]  	Implement EFI_USB2_HC_PROTOCOL.SetState() function.
// [Files]  		amiusbhc.c, uhcd.h
// 
// 46    11/23/14 9:12p Wilsonlee
// [TAG]  		EIP188119
// [Category]  	Improvement
// [Description]  	Disconnect devices and uninstall usb device related
// protocols if we call stop api for the host controllers.
// [Files]  		usbkbd.c, usbbus.c, uhcd.h, uhcd.c
// 
// 45    4/03/14 3:45a Wilsonlee
// [TAG]  		EIP156742
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	System hang at 0x9C during DC cycle test under RHEL6.5
// UEF.I
// [RootCause]  	The hw smi may be triggered when we reallocate memory for
// gUsbData->HcTable.
// [Solution]  	Assign the new memory space to gUsbData->HcTable before we
// free the old.
// [Files]  		uhcd.c, uhcd.h, usbmisc.c
// 
// 44    7/03/13 5:24a Ryanchou
// [TAG]  		EIP123988
// [Category]  	Improvement
// [Description]  	Move the code creating BBS table to end of POST.
// [Files]  		UsbBbs.c, UsbInt13.c, UsbInt13.cif, UsbInt13.h,
// UsbInt13.mak, UsbInt13.sdl, efiusbmass.c, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 43    3/19/13 4:02a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 42    1/11/13 4:22a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 41    8/29/12 8:40a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 40    5/04/12 6:45a Ryanchou
// [TAG]  		EIP82875
// [Category]  	Improvement
// [Description]  	Support start/stop individual USB host to avoid
// reconnect issues.
// [Files]  		usbport.c, usbsb.c, amiusb.c, amiusb.h, ehci.c, ohci.c,
// uhci.c, uhci.h, usb.c, usbdef.h, xhci.c, amiusbhc.c, uhcd.c, uhcd.h,
// usbbus.c, usbmisc.c
// 
// 39    5/04/12 5:32a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.h, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 38    12/14/11 2:12a Ryanchou
// [TAG]  		EIP76397
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	ASSERT occurred when executing "reconnect -r" under shell
// [RootCause]  	The EIP63188 changes locate all USB controllers at one
// time, the "reconnect -r" will connect ConIn and ConOut first, so USB
// driver only locate a controller.
// [Solution]  	Rollback the EIP63188 changes to avoid this issue.
// [Files]  		amiusbhc.c, efiusbhid.c, efiusbkb.c, uhcd.c, uhcd.h,
// usbbus.c usbhid.c
// 
// 37    12/07/11 10:53p Ryanchou
// [TAG]  		EIP77121
// [Category]  	Improvement
// [Description]  	Check added to skip PCI interface type 0xFE, it is not
// USB controller.
// [Files]  		uhcd.c, uhcd.h
// 
// 36    11/08/11 8:23a Wilsonlee
// [TAG]  		EIP74876
// [Category]  	New Feature
// [Description]  	Add USB API for shutdown single USB controller.
// [Files]  		amiusb.c, amiusb.h, usb.c, usbdef.h, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 35    11/08/11 2:00a Ryanchou
// [TAG]  		EIP63188
// [Category]  	Improvement
// [Description]  	External USB controller support.
// [Files]  		amidef.h, amiusb.c, ehci.c, ohci.c, uhcd.c, uhcd.h, uhci.c,
// usbdef.h, usbmisc.c, usbsb.c, xhci.c
// 
// 34    7/13/11 4:14a Ryanchou
// [TAG]  		EIP59332
// [Category]  	Improvement
// [Description]  	Modified the Stop function for UHCD and USBBUS to
// properly stop devices and uninstall the protocols.
// [Files]  		uhcd.c, uhcd.h, uhci.c, usbbus.c, UsbInt13.c, usbmisc.c
// 
// 33    7/12/11 11:43a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
// 32    5/03/11 10:49a Ryanchou
// [TAG]  		EIP59272
// [Category]  	Improvement
// [Description]  	According Uefi 2.1 Aptio porting document, changes made
// to install the component name protocol.
// [Files]  		componentname.c, componentname.h, efiusbkb.c, efiusbmass.c,
// efiusbms.c, uhcd.c, uhcd.h, usbbus.c
// 
// 31    4/06/11 3:22a Tonylo
// [TAG]  		EIP57354
// [Category]  	Improvement
// [Description]  	Core 4.6.5.0 compliant. UEFI 2.3 and PI 1.x support.
// 
// 30    4/06/11 12:46a Ryanchou
// [TAG]  		EIP51653
// [Category]  	New Feature
// [Description]  	Added an interface that skips specific port
// enumeration.
// [Files]  		AmiUsbController.h, uhcd.c, uhcd.h, usb.c, usbdef.h,
// usbport.c
// 
// 29    2/22/11 5:10a Tonylo
// [TAG]  		EIP52339
// [Category]  	New Feature
// [Description]  	USB changes of USB host safe disabling solution.
// [Files]  		USB.C
// UHCD.C
// UHCD.H
// AmiUsbController.h
// 
// 28    8/31/10 9:03a Tonylo
// Issue Number:  41544
// Category:  New Feature
// Description:  Add EntronTech XHCI support.
// 
// 27    6/22/10 9:11p Olegi
// EIP39708: Added new incompatibility type for HIDs that ignore boot
// protocol.
// 
// 26    6/17/10 10:34a Olegi
// EIP39326: Runtime data moved to runtime memory region.
// 
// 25    5/11/10 9:30a Olegi
// LocateAllCompanions returns the status; EIP#38161
// 
// 24    3/25/10 9:48a Olegi
// 
// 23    1/19/10 11:59a Olegi
// 
// 22    10/30/09 5:48p Olegi
// 
// 21    10/09/09 5:57p Olegi
// 
// 20    10/02/09 10:50a Olegi
// Code cleanup.
// 
// 19    3/26/09 2:17p Olegi
// All setup related code is moved to OEMPORT.C to maximize the porting
// capabilities.
// 
// 18    11/25/08 6:02p Olegi
// Support for OEM USB Boot Override feature. EIP#17052.
// 
// 13    5/16/08 12:03p Olegi
// Compliance with AMI coding standard.
//
// 9     3/16/07 6:11p Olegi
// ATOMIC macro redefinition undone.
// CRITICAL_CODE macro redefined.
//
// 8     3/16/07 5:18p Olegi
// Undefined ATOMIC macro.
//
// 7     3/20/06 3:38p Olegi
// Version 8.5 - x64 compatible.
//
// 6     3/01/06 3:54p Olegi
// USB_LEGACY_PLATFORM_SUPPORT added.
//
// 4     6/03/05 11:53a Andriyn
// findHC declaration migrated
//
// 3     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 2     5/10/05 4:13p Andriyn
// USBBUS implementation
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           Uhcd.h
//
//  Description:    AMI USB Host Controller Driver header file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMIUSB_H
#define _AMIUSB_H

#include <Protocol\BlockIo.h>
#include <Protocol\DevicePath.h>
#include <Protocol\PciIo.h>
#include <Protocol\SimplePointer.h>
#include <Protocol\ComponentName.h>
#include <Protocol\AmiUsbController.h>
#include <Protocol\AmiUsbCCID.h>
#include <Protocol\DriverBinding.h>
#include <Protocol\SimpleTextIn.h>
#include <Protocol\UsbIo.h>
#include "amidef.h"
#include "usbdef.h"


/* PCI Configuration Registers for USB */
// Class Code Register offset
#define CLASSC                      0x09
// USB IO Space Base Address Register offset
#define USBBASE                     0x20

//
// USB Base Class Code,Sub-Class Code and Programming Interface.
//
#define PCI_CLASSC_BASE_CLASS_SERIAL        0x0c
#define PCI_CLASSC_SUBCLASS_SERIAL_USB      0x03
#define PCI_CLASSC_IFT_USB_DEVICE			0xFE    // Interface type for USB Device
#define PCI_CLASSC_PI_UHCI                  0x00
#define PCI_CLASSC_PI_OHCI                  0x10
#define PCI_CLASSC_PI_EHCI                  0x20
#define PCI_CLASSC_PI_XHCI                  0x30

#pragma pack(push, 1)

//
// USB Class Code structure
//
typedef struct
{
  UINT8    PI;
  UINT8    SubClassCode;
  UINT8    BaseCode;
} USB_CLASSC;

#pragma pack(pop)

UINT8 UsbSmiReConfigDevice(HC_STRUC* hc, DEV_INFO* dev);

#define DEBUG_LEVEL_USBBUS          DEBUG_LEVEL_3
#define DEBUG_USBHC_LEVEL           DEBUG_LEVEL_3
#define DEBUG_USBHC_LEVEL8          DEBUG_LEVEL_8

EFI_STATUS usbhc_init(EFI_HANDLE  ImageHandle,EFI_HANDLE  ServiceHandle);

#define ATOMIC(a) {\
        EFI_TPL savetpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);\
        {a;}\
        gBS->RestoreTPL(savetpl);   \
}\

#define CRITICAL_CODE(level, a) {\
        EFI_TPL savetpl;\
        EFI_TPL currenttpl = gBS->RaiseTPL (TPL_HIGH_LEVEL); \
        gBS->RestoreTPL(currenttpl);\
        if(currenttpl<=level)\
            currenttpl=level;\
        savetpl = gBS->RaiseTPL (currenttpl);\
        {a;}\
        gBS->RestoreTPL(savetpl);   \
}\

//#define CRITICAL_CODE(level, a) {\
//      EFI_TPL savetpl = gBS->RaiseTPL (level);\
//      {a;}\
//      gBS->RestoreTPL(savetpl);   \
//}\

extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid; //(EIP59272)

EFI_STATUS  UsbMsInit(EFI_HANDLE  ImageHandle, EFI_HANDLE  ServiceHandle);
EFI_STATUS  UsbMassInit(EFI_HANDLE ImageHandle, EFI_HANDLE  ServiceHandle);
EFI_STATUS  UsbCCIDInit(EFI_HANDLE ImageHandle, EFI_HANDLE  ServiceHandle);
HC_STRUC*   FindHcStruc(EFI_HANDLE Controller);

EFI_STATUS
AmiUsbDriverEntryPoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable );

EFI_STATUS
AmiUsbDriverBindingSupported (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath );

EFI_STATUS
AmiUsbDriverBindingStart (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath );

EFI_STATUS
AmiUsbDriverBindingStop (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN UINTN                        NumberOfChildren,
    IN EFI_HANDLE                   *ChildHandleBuffer );

HC_STRUC*
AddHC (
    EFI_HANDLE					Controller,
    UINTN						PciBus,
    UINTN						PciDev,
    UINTN						PciFunc,
    UINT8       				HcType,
	UINT8       				Irq,
	EFI_DEVICE_PATH_PROTOCOL    *DevicePatch,
	EFI_PCI_IO_PROTOCOL   		*PciIo
);

EFI_STATUS
LocateEhciController(
	IN EFI_DRIVER_BINDING_PROTOCOL	*This,
	IN EFI_HANDLE					Controller,
	IN EFI_DEVICE_PATH_PROTOCOL 	*CompanionDevicePath
);

VOID
OnLegacyBoot (
    EFI_EVENT   Event,
    VOID        *Context );

VOID
EFIAPI
ReadyToBootNotify(
    EFI_EVENT   Event, 
    VOID        *Context
);

EFI_STATUS
GetRuntimeRegion (
    EFI_PHYSICAL_ADDRESS *Start,
    EFI_PHYSICAL_ADDRESS *End
);

EFI_STATUS  Dummy1(USB_MASS_DEV*   Device);
EFI_STATUS  Dummy2(VOID);

VOID        ReportDevices(CONNECTED_USB_DEVICES_NUM*);
UINT8       GetNextMassDeviceName(UINT8*, UINT8, UINT8);
VOID        UsbChangeEfiToLegacy (UINT8);
VOID*       AllocAlignedMemory(UINT32, UINT16);
VOID        USBGenerateSWSMI (UINT8);
VOID        UsbPrepareForLegacyOS();
EFI_STATUS  UpdateHcPciInfo();
EFI_STATUS  OemGetAssignUsbBootPort (UINT8*, UINT8*);
VOID  		UsbGetSkipList(USB_SKIP_LIST*, UINT8);	//(EIP51653+) 
VOID		FreeMemory(UINT32);
VOID		InvokeUsbApi(URP_STRUC*);


// USB HC binding protocol functions
EFI_STATUS
UsbHcSupported (
    EFI_DRIVER_BINDING_PROTOCOL *pThis,
    EFI_HANDLE  Controller,
    EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

EFI_STATUS
InstallHcProtocols(
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   Controller,
    IN EFI_PCI_IO_PROTOCOL   		*PciIo,
    IN HC_STRUC              		*HcData
);

EFI_STATUS
UsbHcStop (
   EFI_DRIVER_BINDING_PROTOCOL      *This,
   EFI_HANDLE                       Controller,
   UINTN                            NumberOfChildren,
   EFI_HANDLE                       *Children 
);

EFI_STATUS
AmiUsb2HcGetState(
  IN  EFI_USB2_HC_PROTOCOL    *This,
  OUT EFI_USB_HC_STATE        *State);

EFI_STATUS
AmiUsb2HcSetState(
  IN EFI_USB2_HC_PROTOCOL    *This,
  IN EFI_USB_HC_STATE        State);

EFI_STATUS EFIAPI
AmiUsb2HcSyncInterruptTransfer(
  IN EFI_USB2_HC_PROTOCOL    *hc_protocol,
  IN     UINT8                      deviceaddress,
  IN     UINT8                      endpointaddress,
  IN     UINT8                      DeviceSpeed,
  IN     UINTN                      maximumpacketlength,
  IN OUT VOID                       *data,
  IN OUT UINTN                      *datalength,
  IN OUT UINT8                      *datatoggle,
  IN     UINTN                      timeout,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
  OUT    UINT32                     *transferresult  );

EFI_STATUS EFIAPI AmiUsb2HcControlTransfer(
  IN EFI_USB2_HC_PROTOCOL           *hc_protocol,
  IN     UINT8                      deviceaddress,
  IN     UINT8                      DeviceSpeed,
  IN     UINTN                      maximumpacketlength,
  IN     EFI_USB_DEVICE_REQUEST     *request,
  IN     EFI_USB_DATA_DIRECTION     transferdirection,
  IN OUT VOID                       *data ,
  IN OUT UINTN                      *datalength,
  IN     UINTN                      timeout,
  IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
  OUT    UINT32                     *transferresult );

EFI_STATUS EFIAPI AmiUsb2HcBulkTransfer(
  IN EFI_USB2_HC_PROTOCOL   *hc_protocol,
  IN  UINT8                 deviceaddress,
  IN  UINT8                 endpointaddress,
  IN     UINT8              DeviceSpeed,
  IN  UINTN                 maximumpacketlength,
  IN     UINT8              DataBuffersNumber,
  IN OUT VOID               *Data[EFI_USB_MAX_BULK_BUFFER_NUM],
  IN OUT UINTN              *datalength,
  IN OUT UINT8              *datatoggle,
  IN  UINTN                 timeout,
  IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
  OUT UINT32                *transferresult );

EFI_STATUS EFIAPI AmiUsb2HcAsyncInterruptTransfer(
    IN EFI_USB2_HC_PROTOCOL                             *hc_protocol,
    IN UINT8                            deviceaddress,
    IN UINT8                            endpointaddress,
    IN UINT8                             DeviceSpeed,
    IN UINTN                            maxpacket,
    IN BOOLEAN                          isnewtransfer,
    IN OUT UINT8                        *datatoggle,
    IN UINTN                            pollinginterval  ,
    IN UINTN                            datalength,
    IN     EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    IN EFI_ASYNC_USB_TRANSFER_CALLBACK  callbackfunction ,
    IN VOID                             *context);

EFI_STATUS
AmiUsbBlkIoReset (
  IN  EFI_BLOCK_IO_PROTOCOL  *This,
  IN  BOOLEAN                ExtendedVerification
);

EFI_STATUS
AmiUsbBlkIoFlushBlocks (
  IN  EFI_BLOCK_IO_PROTOCOL  *This
);

EFI_STATUS
AmiUsbBlkIoReadBlocks (
  IN  EFI_BLOCK_IO_PROTOCOL  *This,
  IN  UINT32                 MediaId,
  IN  EFI_LBA                LBA,
  IN  UINTN                  BufferSize,
  OUT VOID                   *Buffer
);

EFI_STATUS
AmiUsbBlkIoWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                LBA,
  IN UINTN                  BufferSize,
  IN VOID                   *Buffer
);

VOID
ReportDevices(
    IN OUT CONNECTED_USB_DEVICES_NUM    *devs
);

EFI_STATUS UpdateMassDevicesForSetup();

UINT32 CalculateMemorySize(VOID);

VOID OnExitBootServices(EFI_EVENT, VOID*);
EFI_STATUS InitUsbSetupVars (USB_GLOBAL_DATA*, EFI_BOOT_SERVICES*, EFI_RUNTIME_SERVICES*);
UINT8 UsbSetupGetLegacySupport();

typedef EFI_STATUS (*USB_HC_PREINIT_FUNC) (
  IN EFI_HANDLE Handle,
    HC_STRUC    *HcStruc
);

typedef EFI_STATUS (*USB_HC_POSTSTOP_FUNC) (
  IN EFI_HANDLE Handle,
    HC_STRUC    *HcStruc
);

typedef struct {
    UINT64  PCICommand;
    UINT16  FrameListSize;
    UINT16  FrameListAlignment;
    USB_HC_PREINIT_FUNC HcPreInit;
	USB_HC_POSTSTOP_FUNC HcPostStop;
} HCSPECIFICINFO;

enum {
    opHC_Start,
    opHC_Stop,
    opHC_EnumeratePorts,
    opHC_DisableInterrupts,
    opHC_EnableInterrupts,
    opHC_ProcessInterrupt,
    opHC_GetRootHubStatus,
    opHC_DisableRootHub,
    opHC_EnableRootHub,
    opHC_ControlTransfer,
    opHC_BulkTransfer,
    opHC_InterruptTransfer,
    opHC_DeactivatePolling,
    opHC_ActivatePolling,
    opHC_DisableKeyRepeat,
    opHC_EnableKeyRepeat,
	opHC_EnableEndpoints,
    opHC_InitDeviceData,
    opHC_DeinitDeviceData,
    opHC_ResetRootHub,
    opHC_ClearEndpointState,
    opHC_GlobalSuspend,
};

EFI_STATUS  DummyHcFunc(EFI_HANDLE, HC_STRUC*);
EFI_STATUS  PreInitXhci(EFI_HANDLE, HC_STRUC*);
EFI_STATUS  PostStopXhci(EFI_HANDLE, HC_STRUC*);
EFI_STATUS  Usb3OemGetMaxDeviceSlots(UINT8*);
VOID        *AllocateHcMemory (IN EFI_PCI_IO_PROTOCOL*, UINTN, UINTN);
VOID		FreeHcMemory(IN EFI_PCI_IO_PROTOCOL*, IN UINTN, IN VOID*);
EFI_STATUS  ReallocateMemory(UINTN, UINTN, VOID**);
VOID        UsbSmiPeriodicEvent(VOID);
VOID        UhcdPciIoNotifyCallback (EFI_EVENT, VOID*);
VOID        UhcdPciIrqPgmNotifyCallback (EFI_EVENT, VOID*);
UINTN       UsbSmiHc(UINT8,UINT8, ...);
EFI_STATUS  USBPort_InstallEventHandler(HC_STRUC*);
VOID        Emul6064NotifyCallback(EFI_EVENT, VOID*);
EFI_STATUS  USBPort_XhciCapabilityOverride(    USB3_HOST_CONTROLLER *Usb3Hc);
VOID        UsbRtShutDownLegacy(VOID); 					//<(EIP52339+)
VOID        UsbRtStopController(UINT16);	//(EIP74876+)
VOID        UsbHcOnTimer(EFI_EVENT, VOID*);
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
