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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/HubPeim.h 4     11/24/12 5:42a Ryanchou $
//
// $Revision: 4 $
//
// $Date: 11/24/12 5:42a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/HubPeim.h $
// 
// 4     11/24/12 5:42a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 3     1/18/11 12:55a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 2     7/10/08 6:33p Michaela
// Updated to support OHCI controllers
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
// Name:        HubPeim.H
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

    HubPeim.h

   Abstract:

    Constants definitions for Usb Hub Peim

   Revision History

   --*/

#ifndef _PEI_HUB_PEIM_H
#define _PEI_HUB_PEIM_H

#include "Efi.h"
#include "Pei.h"
#include "usb.h"
#include "usbpeim.h"

#include "Ppi\UsbIo.h"
//
// Hub feature numbers
//
#define C_HUB_LOCAL_POWER   0
#define C_HUB_OVER_CURRENT  1


//
// Hub class code & sub class code
//
#define CLASS_CODE_HUB      0x09
#define SUB_CLASS_CODE_HUB  0

//
// Hub Status & Hub Change bit masks
//
#define HUB_STATUS_LOCAL_POWER  0x0001
#define HUB_STATUS_OVERCURRENT  0x0002

#define HUB_CHANGE_LOCAL_POWER  0x0001
#define HUB_CHANGE_OVERCURRENT  0x0002

//
// Hub Characteristics
//
#define HUB_CHAR_LPSM      0x0003
#define HUB_CHAR_COMPOUND  0x0004
#define HUB_CHAR_OCPM      0x0018

//
// Hub specific request
//
#define HUB_CLEAR_FEATURE                0x01
#define HUB_CLEAR_FEATURE_REQ_TYPE       0x20

#define HUB_CLEAR_FEATURE_PORT           0x01
#define HUB_CLEAR_FEATURE_PORT_REQ_TYPE  0x23

#define HUB_GET_BUS_STATE                0x02
#define HUB_GET_BUS_STATE_REQ_TYPE       0xa3

#define HUB_GET_DESCRIPTOR               0x06
#define HUB_GET_DESCRIPTOR_REQ_TYPE      0xa0

#define HUB_GET_HUB_STATUS               0x00
#define HUB_GET_HUB_STATUS_REQ_TYPE      0xa0

#define HUB_GET_PORT_STATUS              0x00
#define HUB_GET_PORT_STATUS_REQ_TYPE     0xa3

#define HUB_SET_DESCRIPTOR               0x07
#define HUB_SET_DESCRIPTOR_REQ_TYPE      0x20

#define HUB_SET_HUB_FEATURE              0x03
#define HUB_SET_HUB_FEATURE_REQ_TYPE     0x20

#define HUB_SET_HUB_DEPTH                0x0C
#define HUB_SET_HUB_DEPTH_REQ_TYPE       0x20

#define HUB_SET_PORT_FEATURE             0x03
#define HUB_SET_PORT_FEATURE_REQ_TYPE    0x23

// Hub port status and port change status bits
#define HUB_PORT_CONNECTION		0x0001
#define HUB_PORT_ENABLE			0x0002
#define HUB_PORT_SUSPEND		0x0004
#define HUB_PORT_OVER_CURRENT	0x0008
#define HUB_PORT_RESET			0x0010
#define HUB_PORT_POWER			0x0100
#define HUB_PORT_LOW_SPEED		0x0200
#define HUB_PORT_HIGH_SPEED		0x0400
#define HUB_PORT_TEST			0x0800
#define HUB_PORT_INDICATOR		0x1000

#define HUB_C_PORT_CONNECTION	0x0001
#define HUB_C_PORT_ENABLE		0x0002
#define HUB_C_PORT_SUSPEND		0x0004
#define HUB_C_PORT_OVER_CURRENT	0x0008
#define HUB_C_PORT_RESET		0x0010

// Super speed hub definition
#define SS_HUB_PORT_CONNECTION		0x0001
#define SS_HUB_PORT_ENABLE			0x0002
#define SS_HUB_PORT_OVER_CURRENT	0x0008
#define SS_HUB_PORT_RESET			0x0010
#define SS_HUB_PORT_LINK_STATE		0x01E0
#define SS_HUB_PORT_POWER			0x0200
#define SS_HUB_PORT_SPEED			0x1800

#define SS_HUB_C_PORT_CONNECTION	0x0001
#define SS_HUB_C_PORT_ENABLE		0x0002
#define SS_HUB_C_PORT_SUSPEND		0x0004
#define SS_HUB_C_PORT_OVER_CURRENT	0x0008
#define SS_HUB_C_PORT_RESET			0x0010
#define	SS_HUB_C_BH_PORT_RESET		0x0020
#define	SS_HUB_C_PORT_LINK_STATE	0x0040
#define	SS_HUB_C_PORT_CONFIG_ERROR	0x0080

#pragma pack(1)
typedef struct usb_hub_status
{
    UINT16 HubStatus;
    UINT16 HubChange;
} EFI_USB_HUB_STATUS;

typedef struct {
	struct {
		UINT16	Connected	:1;
		UINT16	Enabled		:1;
		UINT16	Reserved	:1;
		UINT16	OverCurrent	:1;
		UINT16	Reset		:1;
		UINT16	LinkState	:4;
		UINT16	Power		:1;
		UINT16	Speed		:3;
		UINT16	Reserved1	:3;
	} PortStatus;
	struct {
		UINT16	ConnectChange		:1;
		UINT16	Reserved			:2;
		UINT16	OverCurrentChange	:1;
		UINT16	ResetChange			:1;
		UINT16	BhResetChange		:1;
		UINT16	LinkStateChange		:1;
		UINT16	ConfigErrorChange	:1;
		UINT16	Reserved1			:8;
	} PortChange;
} USB3_HUB_PORT_STATUS;

#pragma pack()

EFI_STATUS
PeiHubGetPortStatus (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    OUT UINT32          *PortStatus );

EFI_STATUS
PeiHubSetPortFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    IN UINT8            Value );

EFI_STATUS
PeiHubSetHubFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Value );

EFI_STATUS
PeiHubGetHubStatus (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    OUT UINT32          *HubStatus );

EFI_STATUS
PeiHubClearPortFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    IN UINT8            Value );

EFI_STATUS
PeiHubClearHubFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Value );

EFI_STATUS
PeiSetHubDepth (
    IN EFI_PEI_SERVICES        **PeiServices,
    IN PEI_USB_IO_PPI          *UsbIoPpi,
	IN UINT16                  HubDepth);

EFI_STATUS
PeiGetHubDescriptor (
    IN EFI_PEI_SERVICES        **PeiServices,
    IN PEI_USB_IO_PPI          *UsbIoPpi,
    IN UINTN                   DescriptorSize,
    OUT EFI_USB_HUB_DESCRIPTOR *HubDescriptor );

EFI_STATUS
PeiDoHubConfig (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice );

VOID
PeiResetHubPort (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    UINT8               PortNum );

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
