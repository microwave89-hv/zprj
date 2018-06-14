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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/PeiUsbLib.h 5     11/24/12 5:43a Ryanchou $
//
// $Revision: 5 $
//
// $Date: 11/24/12 5:43a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/PeiUsbLib.h $
// 
// 5     11/24/12 5:43a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 4     10/11/10 4:51p Olegi
// XHCI support added.
// 
// 3     3/17/09 5:10p Olegi
// 
// 2     7/10/08 6:33p Michaela
// Updated to support OHCI controllers
//
// 1     9/22/06 4:07p Sivagarn
// - Initial Check-in
// - Included Recovery code in Source
// - Included appropriate headers for flies and functions
// - Updated copyright messages
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        PeiUsbLib.H
//
// Description: This file belongs to "Framework" and included here for
//              compatibility purposes. This file is modified by AMI to include
//              copyright message, appropriate header and integration code.
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

    PeiUsbLib.h

   Abstract:

   Common Libarary  for PEI USB

   Revision History

   --*/

#ifndef _PEI_USB_LIB_H
#define _PEI_USB_LIB_H

EFI_STATUS
PeiUsbGetDescriptor (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT16           Value,
    IN UINT16           Index,
    IN UINT16           DescriptorLength,
    IN VOID             *Descriptor );

EFI_STATUS
PeiUsbSetDeviceAddress (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT16           AddressValue );

EFI_STATUS
PeiUsbClearDeviceFeature (
    IN EFI_PEI_SERVICES  **PeiServices,
    IN PEI_USB_IO_PPI    *UsbIoPpi,
    IN EFI_USB_RECIPIENT Recipient,
    IN UINT16            Value,
    IN UINT16            Target );

EFI_STATUS
PeiUsbSetConfiguration (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi );

EFI_STATUS
PeiUsbClearEndpointHalt (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            EndpointAddress );

BOOLEAN
IsPortConnect (
    UINT16 PortStatus );

BOOLEAN
IsPortEnable (
    UINT16 PortStatus );

BOOLEAN
IsPortLowSpeedDeviceAttached (
    UINT16 PortStatus );

BOOLEAN
IsPortHighSpeedDeviceAttached (
    UINT16 PortStatus );

BOOLEAN
IsPortSuperSpeedDeviceAttached (
    UINT16 PortStatus );

BOOLEAN
IsPortConnectChange (
    UINT16 PortChangeStatus );

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