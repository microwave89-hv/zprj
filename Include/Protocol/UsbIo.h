//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2010, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**              5555 Oakbrook Pkwy, Suite 200 Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/UsbIo.h 9     5/04/12 5:35a Wilsonlee $
//
// $Revision: 9 $
//
// $Date: 5/04/12 5:35a $
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           UsbIo.h
//
//  Description:    AMI USB IO interface header file
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>


#ifndef _USBIO_INC_
#define _USBIO_INC_

#define EFI_USB_IO_PROTOCOL_GUID \
    { 0x2B2F68D6, 0x0CD2, 0x44cf, 0x8E, 0x8B, 0xBB, 0xA2, 0x0B, 0x1B, 0x5B, 0x75 }

GUID_VARIABLE_DECLARATION(gEfiUsbIoProtocolGuid,EFI_USB_IO_PROTOCOL_GUID);

typedef struct _EFI_USB_IO_PROTOCOL EFI_USB_IO_PROTOCOL;

#pragma pack(push, 1)

//
// See USB1.1 for detail descrption.
// 
typedef struct {
	UINT8 Length;
	UINT8 DescriptorType;
	UINT16 BcdUSB;
	UINT8 DeviceClass;
	UINT8 DeviceSubClass;
	UINT8 DeviceProtocol;
	UINT8 MaxPacketSize0;
	UINT16 IdVendor;
	UINT16 IdProduct;
	UINT16 BcdDevice;
	UINT8 StrManufacturer;
	UINT8 StrProduct;
	UINT8 StrSerialNumber;
	UINT8 NumConfigurations;
} EFI_USB_DEVICE_DESCRIPTOR;

typedef struct {
	UINT8 Length;
	UINT8 DescriptorType;
	UINT16 TotalLength;
	UINT8 NumInterfaces;
	UINT8 ConfigurationValue;
	UINT8 Configuration;
	UINT8 Attributes;
	UINT8 MaxPower;
} EFI_USB_CONFIG_DESCRIPTOR;

typedef struct {
	UINT8 Length;
	UINT8 DescriptorType;
	UINT8 InterfaceNumber;
	UINT8 AlternateSetting;
	UINT8 NumEndpoints;
	UINT8 InterfaceClass;
	UINT8 InterfaceSubClass;
	UINT8 InterfaceProtocol;
	UINT8 Interface;
} EFI_USB_INTERFACE_DESCRIPTOR;


// EFI_USB_ENDPOINT_DESCRIPTOR's EndPointAttributes 
//  must mask the returned attributes before checking
#define USB_ENDPOINT_TYPE_MASK          3

#define USB_ENDPOINT_TYPE_CONTROL       0
#define USB_ENDPOINT_TYPE_ISOCHRONOUS   1
#define USB_ENDPOINT_TYPE_BULK          2
#define USB_ENDPOINT_TYPE_INTERRUPT     3

typedef struct {
	UINT8 Length;
	UINT8 DescriptorType;
	UINT8 EndpointAddress;
	UINT8 Attributes;
	UINT16 MaxPacketSize;
	UINT8 Interval;
} EFI_USB_ENDPOINT_DESCRIPTOR;

typedef struct {
  UINT8  Length;
  UINT8  DescriptorType;
  CHAR16 String[1];
} EFI_USB_STRING_DESCRIPTOR;

typedef enum {
	EfiUsbDataIn,
	EfiUsbDataOut,
	EfiUsbNoData
} EFI_USB_DATA_DIRECTION;

//
// Error code for USB Transfer Results
//
#define EFI_USB_NOERROR 			0x0000
#define EFI_USB_ERR_NOTEXECUTE 		0x0001
#define EFI_USB_ERR_STALL 			0x0002
#define EFI_USB_ERR_BUFFER 			0x0004
#define EFI_USB_ERR_BABBLE 			0x0008
#define EFI_USB_ERR_NAK 			0x0010
#define EFI_USB_ERR_CRC 			0x0020
#define EFI_USB_ERR_TIMEOUT 		0x0040
#define EFI_USB_ERR_BITSTUFF 		0x0080
#define EFI_USB_ERR_SYSTEM 			0x0100



typedef struct {
	UINT8 RequestType;
	UINT8 Request;
	UINT16 Value;
	UINT16 Index;
	UINT16 Length;
} EFI_USB_DEVICE_REQUEST;

#pragma pack(pop)

typedef EFI_STATUS (EFIAPI *EFI_ASYNC_USB_TRANSFER_CALLBACK) (
  IN void         *Data,
  IN UINTN        DataLength,
  IN void         *Context,
  IN UINT32       Status);

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_CONTROL_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN EFI_USB_DEVICE_REQUEST         *Request,
  IN EFI_USB_DATA_DIRECTION         Direction,
  IN UINT32                         Timeout,
  IN OUT void                       *Data       OPTIONAL,
  IN UINTN                          DataLength  OPTIONAL,
  OUT UINT32                        *Status  );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_BULK_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN UINT8                          DeviceEndpoint,
  IN OUT void                       *Data,
  IN OUT UINTN                      *DataLength,
  IN UINTN                          Timeout,
  OUT UINT32                        *Status );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL      *This,
  IN UINT8                            DeviceEndpoint,
  IN BOOLEAN                          IsNewTransfer,
  IN UINTN                            PollingInterval    OPTIONAL,
  IN UINTN                            DataLength         OPTIONAL,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  InterruptCallBack  OPTIONAL,
  IN void                             *Context           OPTIONAL );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_SYNC_INTERRUPT_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN     UINT8                      DeviceEndpoint,
  IN OUT void                       *Data,
  IN OUT UINTN                      *DataLength,
  IN     UINTN                      Timeout,
  OUT    UINT32                     *Status );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL    *This,
  IN     UINT8                      DeviceEndpoint,
  IN OUT void                       *Data,
  IN     UINTN                      DataLength,
  OUT    UINT32                     *Status );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER) (
  IN EFI_USB_IO_PROTOCOL      *This,
  IN UINT8                            DeviceEndpoint,
  IN OUT void                         *Data,
  IN     UINTN                        DataLength,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  IsochronousCallBack,
  IN void                             *Context   OPTIONAL );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_PORT_RESET) ( IN EFI_USB_IO_PROTOCOL    *This );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_GET_DEVICE_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL   *This,
  OUT EFI_USB_DEVICE_DESCRIPTOR     *DeviceDescriptor );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_GET_CONFIG_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL   *This,
  OUT EFI_USB_CONFIG_DESCRIPTOR     *ConfigurationDescriptor );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_GET_INTERFACE_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL   *This,
  OUT EFI_USB_INTERFACE_DESCRIPTOR  *InterfaceDescriptor );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL   *This,
  IN  UINT8                         EndpointIndex,
  OUT EFI_USB_ENDPOINT_DESCRIPTOR   *EndpointDescriptor );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_GET_STRING_DESCRIPTOR) (
  IN EFI_USB_IO_PROTOCOL   *This,
  IN  UINT16                        LangID,
  IN  UINT8                         StringID,
  OUT CHAR16                        **String );

typedef EFI_STATUS (EFIAPI *EFI_USB_IO_GET_SUPPORTED_LANGUAGE) (
  IN EFI_USB_IO_PROTOCOL   *This,
  OUT UINT16                        **LangIDTable,
  OUT UINT16                        *TableSize );



//
//  _EFI_USB_IO_PROTOCOL
//
typedef struct _EFI_USB_IO_PROTOCOL {
  //
  // IO transfer
  //
  EFI_USB_IO_CONTROL_TRANSFER             UsbControlTransfer;
  EFI_USB_IO_BULK_TRANSFER                UsbBulkTransfer;
  EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER     UsbAsyncInterruptTransfer;
  EFI_USB_IO_SYNC_INTERRUPT_TRANSFER      UsbSyncInterruptTransfer;
  EFI_USB_IO_ISOCHRONOUS_TRANSFER         UsbIsochronousTransfer;
  EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER   UsbAsyncIsochronousTransfer;
  
  //
  // Common device request
  //
  EFI_USB_IO_GET_DEVICE_DESCRIPTOR        UsbGetDeviceDescriptor;
  EFI_USB_IO_GET_CONFIG_DESCRIPTOR        UsbGetConfigDescriptor;
  EFI_USB_IO_GET_INTERFACE_DESCRIPTOR     UsbGetInterfaceDescriptor;
  EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR      UsbGetEndpointDescriptor;
  EFI_USB_IO_GET_STRING_DESCRIPTOR        UsbGetStringDescriptor;
  EFI_USB_IO_GET_SUPPORTED_LANGUAGE       UsbGetSupportedLanguages;

  //
  // Reset controller's parent port
  //
  EFI_USB_IO_PORT_RESET                   UsbPortReset;
} EFI_USB_IO_PROTOCOL;

#endif //_USBIO_INC_

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2010, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**              5555 Oakbrook Pkwy, Suite 200 Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
