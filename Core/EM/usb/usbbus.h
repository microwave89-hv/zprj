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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/usbbus.h 17    12/20/13 3:42a Wilsonlee $
//
// $Revision: 17 $
//
// $Date: 12/20/13 3:42a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/usbbus.h $
// 
// 17    12/20/13 3:42a Wilsonlee
// [TAG]  		EIP147402
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	System hang at 0xA2 if plugging Seagate USB device.
// [RootCause]  	This device doesn't respond get descriptor command after
// we install mass storage driver.
// [Solution]  	We store the string descriptor when we load the langid
// table.
// [Files]  		usbbus.c, usbbus.h
// 
// 16    1/11/13 4:19a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 15    11/10/12 6:41a Ryanchou
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
// 14    9/04/12 6:15a Ryanchou
// [TAG]  		EIP99123
// [Category]  	Improvement
// [Description]  	Roll back EIP79221 changes that has device
// compatibility issue.
// [Files]  		usbbus.c, usbbus.h
// 
// 13    5/04/12 5:33a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.h, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 12    1/31/12 12:35a Roberthsu
// [TAG]           EIP79221
// [Category]      Improvement
// [Description]   Add get serial number and product string descriptor.
// [Files]         usbbus.c,usbbus.h
// 
// 11    1/13/12 4:27a Ryanchou
// [TAG]  		EIP47348
// [Category]  	New Feature
// [Description]  	Support for USB Port Reset function.
// [Files]  		amiusb.c, amiusb.h, amiusbhc.c, uhci.c, usb.c, usbbus.c,
// usbbus.h, usbmass.c
// 
// 10    2/16/11 5:20p Olegi
// [TAG]  		EIP53956
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	UsbIo Control/Bulk/Interrupt transfers fail because
// GetEndpointDesc() returns incorrect end point
// [RootCause]  	The macro COMPRESS_EP_ADR will cause data to be
// overwritten in the a2endpoint array of the DEVGROUP_T structure.
// [Solution]  	Redefine COMPRESS_EP_ADR macro as:
// #define COMPRESS_EP_ADR(a) ( a & 0xF ) 
// [Files]  		usbbus.h
// 
// 9     9/05/08 4:14p Olegi
// 
// 8     5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 7     3/20/07 1:29p Olegi
//
// 5     3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 4     6/15/05 1:59p Andriyn
// Comments were changed
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           UsbBus.h
//
//  Description:    AMI USB bus driver header file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _USBBUS_INC_
#define _USBBUS_INC_
#include "tree.h"


#define USB_MAXLANID          16
#define USB_MAXCHILDREN       8
#define USB_MAXCONTROLLERS    4

#define USB_US_LAND_ID   0x0409

//
// Forward declaring
//
struct usb_io_device;
typedef struct _EFI_USB2_HC_PROTOCOL EFI_USB2_HC_PROTOCOL;

#pragma pack(push, 1)

typedef struct {
  UINT8  Length;
  UINT8  DescriptorType;
} USB_DESCRIPTOR_T;

typedef struct {
  UINT8  len;
  UINT8  desctype;
  UINT16 langID[1];
} lang_table_t;

typedef struct {
    UINT8   address;
    EFI_USB_ENDPOINT_DESCRIPTOR* desc;
} endpoint_t;

#pragma pack(pop)

enum node_type_enum { NodeHC, NodeDevice, NodeGroup };


typedef struct {
    int                                 type;
    EFI_HANDLE                          handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *dp;
    EFI_USB2_HC_PROTOCOL                *hc;     // USB_HC_ installed on controller
} usbbus_data_t;

typedef struct _USBBUS_HC_T {
    int                                 type;
    EFI_HANDLE                          handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *dp;
    EFI_USB2_HC_PROTOCOL                *hc;     // USB_HC_ installed on controller
    HC_STRUC                            *hc_data;
    TREENODE_T                          node;
} USBBUS_HC_T;

#define COMPRESS_EP_ADR(a)              ( a & 0xF )

typedef struct _DEVGROUP_T {
    int                                 type;
    EFI_HANDLE                          handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *dp;
    EFI_USB2_HC_PROTOCOL                *hc;    //  USB_HC_ that the controller is attached to
    DEV_INFO                            *dev_info;
    HC_STRUC                            *hc_info;
    lang_table_t                        *lang_table;
    EFI_USB_STRING_DESCRIPTOR           *ManufacturerStrDesc;
    EFI_USB_STRING_DESCRIPTOR           *ProductStrDesc;
    EFI_USB_STRING_DESCRIPTOR           *SerialNumberStrDesc;
    EFI_USB_DEVICE_DESCRIPTOR           dev_desc;
    EFI_USB_CONFIG_DESCRIPTOR           **configs;
    endpoint_t                          endpoints[0x20];
    EFI_USB_ENDPOINT_DESCRIPTOR*        a2endpoint[0x20];
    int                                 endpoint_count;

    int                                 active_config; // index in configs
    int                                 config_count;
    int                                 f_DevDesc;
    TREENODE_T                          node;
} DEVGROUP_T;

typedef struct _USBDEV_T {
    int                                 type;
    EFI_HANDLE                          handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *dp;
    EFI_USB2_HC_PROTOCOL                *hc; //USB_HC_ that the controller is attached to
    DEV_INFO                            *dev_info;
    HC_STRUC                            *hc_info;
    //UINT8                             toggle; //toggle param for bulk transfer
    CHAR16*                             name;
    int                                 f_connected; //was ConnectControllers successful?
    int                                 first_endpoint;
    int                                 end_endpoint;
    EFI_USB_INTERFACE_DESCRIPTOR*       descIF;
    UINT8                               speed;
    EFI_USB_IO_PROTOCOL                 io;
    TREENODE_T                          node;
	int									async_endpoint;
} USBDEV_T;



EFI_STATUS UsbBusSupported (
  EFI_DRIVER_BINDING_PROTOCOL     *pThis,
  EFI_HANDLE                      controller,
  EFI_DEVICE_PATH_PROTOCOL        * );

EFI_STATUS UsbBusStart (
  EFI_DRIVER_BINDING_PROTOCOL     *pThis,
  EFI_HANDLE                      controller,
  EFI_DEVICE_PATH_PROTOCOL        * );

EFI_STATUS UsbBusStop (
  EFI_DRIVER_BINDING_PROTOCOL     *pThis,
  EFI_HANDLE                      controller,
  UINTN                           NumberOfChildren,
  EFI_HANDLE                      *ChildHandleBuffer );

EFI_STATUS UsbBusInit(EFI_HANDLE  ImageHandle,EFI_HANDLE  ServiceHandle);

USBDEV_T* UsbIo2Dev(EFI_USB_IO_PROTOCOL* p);

UINT8*
UsbSmiGetDescriptor(
    HC_STRUC* Hc,
    DEV_INFO* Dev,
    UINT8*    Buf,
    UINT16    Len,
    UINT8     DescType,
    UINT8     DescIndex
);

UINT16
UsbSmiControlTransfer (
    HC_STRUC*   HCStruc,
    DEV_INFO*   DevInfo,
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length
);

UINT8
UsbResetAndReconfigDev(
    HC_STRUC*   HostController,
    DEV_INFO*   Device
);

UINT8
UsbDevDriverDisconnect(
    HC_STRUC*   HostController,
    DEV_INFO*   Device
);

#define GETBIT(bitarray,value,bit) \
    ((value) =  (UINT8)(((bitarray) & (1 << (bit)))>>(bit)))\

#define SETBIT(bitarray,value,bit) \
    (bitarray) =  (((bitarray) & ~(1 << (bit))) | (((value)&1) << (bit)) )\

#define IsSlow(dev) dev->speed
#define GetSpeed(dev) dev->speed

VOID InstallDevice(DEV_INFO* DevInfo);
int eUninstallDevice(VOID* Node, VOID* Context);
EFI_STATUS RemoveDevInfo(DEV_INFO* pDevInfo);


#endif //_USBBUS_INC_

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
