//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UhcPeimSrc/UsbHostController.h 8     1/18/11 1:04a Ryanchou $
//
// $Revision: 8 $
//
// $Date: 1/18/11 1:04a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UhcPeimSrc/UsbHostController.h $
// 
// 8     1/18/11 1:04a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 7     10/22/10 2:56a Rameshr
// [TAG]- EIP 43687
// [Category]-IMPROVEMENT
// [Description]- Build warning from UsbRecovery driver -
// UsbHostController.obj : warning LNK4221: no public symbols found;
// archive member will be inaccessible. 
// [Files]- uhcpeim.c, usbpeim.c, UsbHostcontroller.h
// 
// 6     10/12/10 11:19a Olegi
// XHCI support added.
// 
// 5     4/26/10 4:17p Krishnakumarg
// DebugRx causes the system to hang in Recovery mode EIP#34401
// 
// 4     3/17/09 5:08p Olegi
// Added TransactionTranslator for slow/full speed devices behind USB2
// hub.
// 
// 3     3/03/09 7:27p Olegi
// MaximumPacketLength changed from UINT8 to UINT16.
// 
// 2     7/10/08 6:37p Michaela
// Updated to support OHCI controllers
//
// 1     9/22/06 12:21p Sivagarn
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbHostController.h
//
// Description: This file belongs to "Framework".
//              This file is modified by AMI to include copyright message,
//              appropriate header and integration code.
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

   UsbHostController.h

   Abstract:

   Usb Host Controller PPI as defined in EFI 2.0

   This code abstracts the PEI core to provide Usb Host Contrller
   access services.

   --*/

#ifndef _PEI_USB_HOST_CONTROLLER_PPI_H_
#define _PEI_USB_HOST_CONTROLLER_PPI_H_

#include "core\em\usbrecovery\usb.h"

#define PEI_USB_HOST_CONTROLLER_PPI_GUID  {\
        0x652b38a9, 0x77f4, 0x453f, 0x89, 0xd5, 0xe7, \
        0xbd, 0xc3, 0x52, 0xfc, 0x53}

GUID_VARIABLE_DECLARATION(gPeiUsbHostControllerPpiGuid,PEI_USB_HOST_CONTROLLER_PPI_GUID);
EFI_FORWARD_DECLARATION( PEI_USB_HOST_CONTROLLER_PPI );

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_CONTROL_TRANSFER)(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT8                       MaximumPacketLength,
    IN UINT16                      TransactionTranslator,
    IN EFI_USB_DEVICE_REQUEST      *Request,
    IN EFI_USB_DATA_DIRECTION      TransferDirection,
    IN OUT VOID *Data              OPTIONAL,
    IN OUT UINTN *DataLength       OPTIONAL,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_BULK_TRANSFER)(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       DeviceAddress,
    IN UINT8                       EndPointAddress,
    IN UINT8                       DeviceSpeed,
    IN UINT16                      MaximumPacketLength,
    IN UINT16                      TransactionTranslator,
    IN OUT VOID                    *Data,
    IN OUT UINTN                   *DataLength,
    IN OUT UINT8                   *DataToggle,
    IN UINTN                       TimeOut,
    OUT UINT32                     *TransferResult
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_GET_ROOTHUB_PORT_NUMBER)(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    OUT UINT8                      *PortNumber
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_GET_ROOTHUB_PORT_STATUS)(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    OUT EFI_USB_PORT_STATUS        *PortStatus
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_SET_ROOTHUB_PORT_FEATURE)(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_CLEAR_ROOTHUB_PORT_FEATURE)(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN EFI_USB_PORT_FEATURE        PortFeature
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_PRECONFIGURE_DEVICE) (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       PortNumber,
    IN UINT8                       Speed,
    IN UINT16                      TransactionTranslator 
);

typedef
EFI_STATUS
(EFIAPI * PEI_USB_HOST_CONTROLLER_ENABLE_ENDPOINTS) (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *This,
    IN UINT8                       *ConfigurationData
);

typedef struct _PEI_USB_HOST_CONTROLLER_PPI
{
    PEI_USB_HOST_CONTROLLER_CONTROL_TRANSFER ControlTransfer;
    PEI_USB_HOST_CONTROLLER_BULK_TRANSFER    BulkTransfer;
    PEI_USB_HOST_CONTROLLER_GET_ROOTHUB_PORT_NUMBER    GetRootHubPortNumber;
    PEI_USB_HOST_CONTROLLER_GET_ROOTHUB_PORT_STATUS    GetRootHubPortStatus;
    PEI_USB_HOST_CONTROLLER_SET_ROOTHUB_PORT_FEATURE   SetRootHubPortFeature;
    PEI_USB_HOST_CONTROLLER_CLEAR_ROOTHUB_PORT_FEATURE
    ClearRootHubPortFeature;
    BOOLEAN         DebugPortUsed;
    PEI_USB_HOST_CONTROLLER_PRECONFIGURE_DEVICE     PreConfigureDevice;
    PEI_USB_HOST_CONTROLLER_ENABLE_ENDPOINTS        EnableEndpoints;
} PEI_USB_HOST_CONTROLLER_PPI;


#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
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