//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbPeim.h 8     11/24/12 5:43a Ryanchou $
//
// $Revision: 8 $
//
// $Date: 11/24/12 5:43a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbPeim.h $
// 
// 8     11/24/12 5:43a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 7     1/18/11 12:50a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 6     10/11/10 4:51p Olegi
// XHCI support added.
// 
// 5     3/17/09 5:11p Olegi
// 
// 4     7/10/08 6:33p Michaela
// Updated to support OHCI controllers
//
// 3     4/16/07 1:03p Sivagarn
// - Updated as per coding standard review
// - In previous check-in, TIANO.H file is removed and AMIMAPPING.H file
// is included
//
// 2     3/28/07 3:07a Meenakshim
// Removed dependency on core source files..Added amimapping file.
//
// 1     9/22/06 4:06p Sivagarn
// - Initial Check-in
// - Included Recovery code in Source
// - Included appropriate headers for flies and functions
// - Updated copyright messages
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbPeim.H
//
// Description: This file belongs to "Framework" and included here for
//              compatibility purposes. This file is modified by AMI to include
//              copyright message, appropriate header and integration code
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//

/*++

   Copyright (c)  1999 - 2002 Intel Corporation. All rights reserved
   This software and associated documentation (if any) is furnished
   under a license and may only be used or copied in accordance
   with the terms of the license. Except as permitted by such
   license, no part of this software or documentation may be
   reproduced, stored in a retrieval system, or transmitted in any
   form or by any means without the express written consent of
   Intel Corporation.


   Module Name:

   UsbPeim.h

   Abstract:

   Usb Peim definition

   --*/

#ifndef _PEI_USB_PEIM_H
#define _PEI_USB_PEIM_H

#include "Efi.h"
#include "Pei.h"
#include "AmiMapping.h"
#include "AmiPeiLib.h"

#include "usb.h"

//
// Driver Produced PPI Prototypes
//
#include "Ppi\UsbIo.h"

//
// Driver Consumed PPI Prototypes
//
#include "Ppi\UsbHostController.h"

#define MAX_ROOT_PORT         2
#define MAX_ENDPOINT          16
#define HUB_TIME_OUT          3000
#define STALL_1_MILLI_SECOND  1000      // stall 1 ms


#define USB_SLOW_SPEED_DEVICE  0x01
#define USB_FULL_SPEED_DEVICE  0x02
#define USB_HIGH_SPEED_DEVICE  0x03
#define USB_SUPER_SPEED_DEVICE 0x04

//---------------------------------------------------------------------------
//      Values for InterfaceDescriptor.BaseClass
//---------------------------------------------------------------------------
#define BASE_CLASS_HID           0x03
#define BASE_CLASS_MASS_STORAGE  0x08
#define BASE_CLASS_HUB           0x09
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
//      Values for InterfaceDescriptor.Protocol
//---------------------------------------------------------------------------
#define PROTOCOL_KEYBOARD  0x01         // Keyboard device protocol
#define PROTOCOL_MOUSE     0x02         // Mouse device protocol?

// Mass storage related protocol equates
#define PROTOCOL_CBI         0x00       // Mass Storage Control/Bulk/Interrupt
                                        // with command completion interrupt
#define PROTOCOL_CBI_NO_INT  0x01       // MASS STORAGE Control/Bulk/Interrupt
                                        // with NO command completion interrupt
#define PROTOCOL_BOT         0x50       // Mass Storage Bulk-Only Transport
#define PROTOCOL_VENDOR      0xff       // Vendor specific mass protocol
//---------------------------------------------------------------------------

#define PEI_USB_DEVICE_SIGNATURE  EFI_SIGNATURE_32( 'U', 's', 'b', 'D' )
typedef struct
{
    UINTN Signature;
    PEI_USB_IO_PPI UsbIoPpi;
    EFI_PEI_PPI_DESCRIPTOR UsbIoPpiList;
    UINT8 DeviceAddress;
    UINT8 MaxPacketSize0;
    UINT8 DeviceSpeed;
    UINT8 DataToggle;
    UINT8 IsHub;
    UINT8 DownStreamPortNo;
    UINT8 Reserved[2];                       // Padding for IPF
    PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi;
    UINT8 *ConfigurationData;
    EFI_USB_CONFIG_DESCRIPTOR *ConfigDesc;
    EFI_USB_INTERFACE_DESCRIPTOR *InterfaceDesc;
    EFI_USB_ENDPOINT_DESCRIPTOR *EndpointDesc[MAX_ENDPOINT];
    UINT16 TransactionTranslator;
	UINT8  HubDepth;
} PEI_USB_DEVICE;

#define PEI_USB_DEVICE_FROM_THIS( a ) \
    PEI_CR( a, PEI_USB_DEVICE, UsbIoPpi, PEI_USB_DEVICE_SIGNATURE )

//
// Peim UsbIo prototype
//

EFI_STATUS
PeiUsbControlTransfer (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_USB_IO_PPI         *This,
    IN EFI_USB_DEVICE_REQUEST *Request,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT32                 Timeout,
    IN OUT VOID *Data         OPTIONAL,
    IN UINTN DataLength       OPTIONAL );

EFI_STATUS
PeiUsbBulkTransfer (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *This,
    IN UINT8            DeviceEndpoint,
    IN OUT VOID         *Data,
    IN OUT UINTN        *DataLength,
    IN UINTN            Timeout );

EFI_STATUS
PeiUsbGetInterfaceDescriptor (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN PEI_USB_IO_PPI               *This,
    IN EFI_USB_INTERFACE_DESCRIPTOR **InterfaceDescriptor );

EFI_STATUS
PeiUsbGetEndpointDescriptor (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_IO_PPI              *This,
    IN UINT8                       EndpointIndex,
    IN EFI_USB_ENDPOINT_DESCRIPTOR **EndpointDescriptor );

EFI_STATUS
PeiUsbPortReset (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *This );

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************