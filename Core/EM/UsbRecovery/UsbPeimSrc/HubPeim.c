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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbPeimSrc/HubPeim.c 12    11/24/12 5:46a Ryanchou $
//
// $Revision: 12 $
//
// $Date: 11/24/12 5:46a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbPeimSrc/HubPeim.c $
// 
// 12    11/24/12 5:46a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 11    8/24/11 4:24a Roberthsu
// [TAG]           EIP67320
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       USB recovery will fail when plug-in USB touch panel on
// Oaktrail platform
// [RootCause]     Usbrecovery will exit when get portchanged.Touch panel
// port status is early than usbkey.So usbrecovery fail.
// [Solution]      Add delay after hub set port power.
// [Files]         HubPeim.c
// 
// 10    1/18/11 12:54a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 9     4/26/10 4:17p Krishnakumarg
// DebugRx causes the system to hang in Recovery mode EIP#34401
// 
// 8     4/06/10 3:31p Fasihm
// EIP#31987 - Added the generic USBRecovery Fix in the module.
// 
// 7     3/17/09 5:03p Olegi
// Removed unnecessary CLEAR_FEATURE (Reset) and SET_FEATURE (Enable) in
// the hub enumeration routine.
// 
// 6     7/18/08 5:05p Michaela
// 1  File-level debugging is now available
// 2  AMI_USB_DEBUG_INTERFACE.WaitConsoleKey() now returns
//    the keypress so that conditional debugging can
//    be dynamic (alphanumeric keys only)
// 3  Added more function headers.
// 4  Removed code that will never be used (I.e., Bala?).
// 5  Moved typedef, contants and extern declarations
//    into header files.
// 6  Now all controller blocks are enabled for SB700
//    (EHCI controllers route to companion controller
//    by default)
// 7  Removed unused constants and typedefs n OhciPei.h
//    (also reorganized the file to make it more 
//    readable.)
// 8  Renamed many functions/variables according to
//    coding standard.
// 9  Removed code initializing data structures for
//    periodic lists, as this is not needed.
// 10 Removed the CONTROLLER_TYPE SDL token to
//    allow UHCI and OHCI controllers to supported
//    simultaneously. (modified MAKE files 
//    accordingly)
// 
// 5     7/10/08 6:37p Michaela
// Updated to support OHCI controllers
//
// 4     8/17/07 4:14p Ambikas
//
// 3     4/16/07 12:54p Sivagarn
// - Updated as per coding standard review
// - In previous check-in, TIANO.H file is removed and AMIMAPPING.H file
// is included
//
// 2     3/28/07 3:38a Meenakshim
//
// 1     9/22/06 12:19p Sivagarn
// - Initial Checkin
// - Included Recovery code in Source
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        HubPeim.C
//
// Description: This file belongs to "Framework".
//              This file is modified by AMI to include copyright message,
//              appropriate header and integration code.
//              This file contains generic routines needed for USB recovery
//              PEIM
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

/*++
   This file contains 'Framework Code' and is licensed as such
   under the terms of your license agreement with Intel or your
   vendor.  This file may not be modified, except as allowed by
   additional terms of your license agreement.
   --*/

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

    HubPeim.c

   Abstract:

    Usb Hub Request Support In PEI Phase

   Revision History

   --*/
//NOT NEEDED FOR APTIO
//#include "Efi.h"
//#include "EfiDriverLib.h"
//#include "usb.h"

#include "HubPeim.h"
#include "UsbPeim.h"
#include "PeiUsbLib.h"

#include EFI_PPI_DEFINITION( Stall )
static EFI_GUID gPeiStallPpiGuid = EFI_PEI_STALL_PPI_GUID;

//NOT NEEDED FOR APTIO
//#include "usbbus.h"
//#include "usblib.h"
//#include "hub.h"

extern VOID ZeroMem (
    IN VOID  *Buffer,
    IN UINTN Size );

typedef struct {
	UINT32	HubPortStatus;
	UINT32	EfiPortStatus;
} EFI_USB_PORT_STATUS_MAP;

EFI_USB_PORT_STATUS_MAP  HubPortStatusMap[] = {
	// Port status bits
	{HUB_PORT_CONNECTION, USB_PORT_STAT_CONNECTION},
 	{HUB_PORT_ENABLE, USB_PORT_STAT_ENABLE},
	{HUB_PORT_SUSPEND, USB_PORT_STAT_SUSPEND},
	{HUB_PORT_OVER_CURRENT, USB_PORT_STAT_OVERCURRENT},
	{HUB_PORT_RESET, USB_PORT_STAT_RESET},
	{HUB_PORT_POWER, USB_PORT_STAT_POWER},
	{HUB_PORT_LOW_SPEED, USB_PORT_STAT_LOW_SPEED},
	{HUB_PORT_HIGH_SPEED, USB_PORT_STAT_HIGH_SPEED},
	// Port status change bits
	{HUB_C_PORT_CONNECTION << 16, USB_PORT_STAT_C_CONNECTION << 16},
	{HUB_C_PORT_ENABLE << 16, USB_PORT_STAT_C_ENABLE << 16},
	{HUB_C_PORT_SUSPEND << 16, USB_PORT_STAT_C_SUSPEND << 16},
	{HUB_C_PORT_OVER_CURRENT << 16, USB_PORT_STAT_C_OVERCURRENT << 16},
	{HUB_C_PORT_RESET << 16, USB_PORT_STAT_C_RESET << 16}
};

EFI_USB_PORT_STATUS_MAP  SsHubPortStatusMap[] = {
	// Port status bits
	{SS_HUB_PORT_CONNECTION, USB_PORT_STAT_CONNECTION | USB_PORT_STAT_SUPER_SPEED},
 	{SS_HUB_PORT_ENABLE, USB_PORT_STAT_ENABLE},
	{SS_HUB_PORT_OVER_CURRENT, USB_PORT_STAT_OVERCURRENT},
	{SS_HUB_PORT_RESET, USB_PORT_STAT_RESET},
	{SS_HUB_PORT_POWER, USB_PORT_STAT_POWER},
	// Port status change bits
	{SS_HUB_C_PORT_CONNECTION << 16, USB_PORT_STAT_C_CONNECTION << 16},
	{SS_HUB_C_PORT_ENABLE << 16, USB_PORT_STAT_C_ENABLE << 16},
	{SS_HUB_C_PORT_SUSPEND << 16, USB_PORT_STAT_C_SUSPEND << 16},
	{SS_HUB_C_PORT_OVER_CURRENT << 16, USB_PORT_STAT_C_OVERCURRENT << 16},
	{SS_HUB_C_PORT_RESET << 16, USB_PORT_STAT_C_RESET << 16}
};

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PeiHubGetPortStatus
//
// Description: 
//      This function uses a device's PEI_USB_IO_PPI interface to execute a 
//      control transfer on the default control pipe to issue a Hub 
//      Class-specific request to obtain the port status and port status
//      change bits.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN PEI_USB_IO_PPI *UsbIoPpi
//                  --  PEI_USB_IO_PPI interface pointer for the device
//                      that is being accessed
//      IN UINT8 Port
//                  --  This value is the hub port number for which the
//                      status is to be returned.
//      OUT UINT32 *PortStatus
//                  --  This output value is the USB Specification 
//                      (Revision 2.0) Hub Port Status field (upper word)
//                      and Change Status field (lower word) values as 
//                      returned by the Get Port Status Hub Class device 
//                      standard request.
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiHubGetPortStatus (
    IN  EFI_PEI_SERVICES    **PeiServices,
    IN  PEI_USB_IO_PPI      *UsbIoPpi,
    IN  UINT8               Port,
    OUT UINT32              *PortStatus )
{
    EFI_USB_DEVICE_REQUEST DevReq;
	PEI_USB_DEVICE *PeiUsbDev;
    EFI_STATUS EfiStatus;
	UINT32 HubPortStatus = 0;
	UINT32 Timeout;
	EFI_USB_PORT_STATUS_MAP	*PortStatusMap;
	UINT8	Index;
	UINT8	Count;

	PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );
    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_GET_PORT_STATUS_REQ_TYPE;
    DevReq.Request = HUB_GET_PORT_STATUS;
    DevReq.Value = 0;
    DevReq.Index = Port;
    DevReq.Length = sizeof(UINT32);

    Timeout = 3000;

    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbDataIn,
        Timeout,
        &HubPortStatus,
        sizeof(UINT32)
                );

	if (PeiUsbDev->DeviceSpeed != USB_SUPER_SPEED_DEVICE) {
		PortStatusMap = HubPortStatusMap;
		Count = sizeof(HubPortStatusMap) / sizeof(EFI_USB_PORT_STATUS_MAP);
	} else {
		PortStatusMap = SsHubPortStatusMap;
		Count = sizeof(SsHubPortStatusMap) / sizeof(EFI_USB_PORT_STATUS_MAP);
	}

	for (*PortStatus = 0, Index = 0; Index < Count; Index++) {
		if (HubPortStatus & PortStatusMap[Index].HubPortStatus) {
			*PortStatus |= PortStatusMap[Index].EfiPortStatus;
		}
	}

    return EfiStatus;
}


EFI_STATUS PeiHubSetPortFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    IN UINT8            Value )

/*++

   Routine Description:
    Set specified feature to a give hub port

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Port            -   Usb hub port number (starting from 1).
    Value           -   New feature value.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT
    EFI_INVALID_PARAMETER

   --*/

{
    EFI_USB_DEVICE_REQUEST DevReq;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_SET_PORT_FEATURE_REQ_TYPE;
    DevReq.Request = HUB_SET_PORT_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = Port;
    DevReq.Length = 0;

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
                );

    return EfiStatus;
}


EFI_STATUS PeiHubClearPortFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    IN UINT8            Value )

/*++

   Routine Description:
    Clear a specified feature of a given hub port

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Port            -   Usb hub port number (starting from 1).
    Value           -   Feature value that will be cleared from
                        that hub port.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT
    EFI_INVALID_PARAMETER

   --*/
{
    EFI_USB_DEVICE_REQUEST DevReq;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_CLEAR_FEATURE_PORT_REQ_TYPE;
    DevReq.Request = HUB_CLEAR_FEATURE_PORT;
    DevReq.Value = Value;
    DevReq.Index = Port;
    DevReq.Length = 0;

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
                );

    return EfiStatus;
}


EFI_STATUS PeiHubGetHubStatus (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    OUT UINT32          *HubStatus )

/*++

   Routine Description:
    Get Hub Status

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    HubStatus       -   Current Hub status and change status.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST DevReq;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_GET_HUB_STATUS_REQ_TYPE;
    DevReq.Request = HUB_GET_HUB_STATUS;
    DevReq.Value = 0;
    DevReq.Index = 0;
    DevReq.Length = sizeof(UINT32);

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbDataIn,
        Timeout,
        HubStatus,
        sizeof(UINT32)
                );

    return EfiStatus;
}


EFI_STATUS PeiHubSetHubFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Value )

/*++

   Routine Description:
    Set a specified feature to the hub

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Value           -   Feature value that will be set to the hub.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST DevReq;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_SET_HUB_FEATURE_REQ_TYPE;
    DevReq.Request = HUB_SET_HUB_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
                );

    return EfiStatus;
}


EFI_STATUS PeiHubClearHubFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Value )

/*++

   Routine Description:
    Set a specified feature to the hub

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Value           -   Feature value that will be cleared from the hub.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST DevReq;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_CLEAR_FEATURE_REQ_TYPE;
    DevReq.Request = HUB_CLEAR_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
                );

    return EfiStatus;

}

EFI_STATUS PeiSetHubDepth (
    IN EFI_PEI_SERVICES        **PeiServices,
	IN PEI_USB_IO_PPI          *UsbIoPpi,
	IN UINT16                  HubDepth)
{
    EFI_USB_DEVICE_REQUEST DevReq;
	PEI_USB_DEVICE *PeiUsbDev;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

	PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );
	if (PeiUsbDev->DeviceSpeed != USB_SUPER_SPEED_DEVICE) {
		return EFI_SUCCESS;
	}

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_SET_HUB_DEPTH_REQ_TYPE;
    DevReq.Request = HUB_SET_HUB_DEPTH;
    DevReq.Value = HubDepth;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
                );

	return EfiStatus;
}

EFI_STATUS PeiGetHubDescriptor (
    IN EFI_PEI_SERVICES        **PeiServices,
    IN PEI_USB_IO_PPI          *UsbIoPpi,
    IN UINTN                   DescriptorSize,
    OUT EFI_USB_HUB_DESCRIPTOR *HubDescriptor )

/*++

   Routine Description:
    Get the hub descriptor

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    DescriptorSize  -   The length of Hub Descriptor buffer.
    HubDescriptor   -   Caller allocated buffer to store the hub descriptor
                        if successfully returned.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST DevReq;
	PEI_USB_DEVICE *PeiUsbDev;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

	PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );
    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = USB_RT_HUB | 0x80;
    DevReq.Request = HUB_GET_DESCRIPTOR;
    DevReq.Value = PeiUsbDev->DeviceSpeed == USB_SUPER_SPEED_DEVICE ? 
											USB_DT_SS_HUB << 8: USB_DT_HUB << 8;
    DevReq.Index = 0;
    DevReq.Length = (UINT16) DescriptorSize;

    Timeout = 3000;
    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbDataIn,
        Timeout,
        HubDescriptor,
        (UINT16) DescriptorSize
                );

    return EfiStatus;

}


EFI_STATUS PeiDoHubConfig (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice )

/*++

   Routine Description:
    Configure the hub

   Arguments:
    PeiUsbDevice         -   Indicating the hub controller device that
                              will be configured

   Returns:
    EFI_SUCCESS
    EFI_DEVICE_ERROR

   --*/
{
    EFI_USB_HUB_DESCRIPTOR HubDescriptor;
    EFI_STATUS Status;
    EFI_USB_HUB_STATUS     HubStatus;
    UINTN  i;
    UINT32 PortStatus;
    PEI_USB_IO_PPI *UsbIoPpi;

    BOOLEAN SkipDebugPort = PeiUsbDevice->UsbHcPpi->DebugPortUsed;
//(EIP67320+)>
    PEI_STALL_PPI       *PeiStall;  
    (**PeiServices).LocatePpi(
        PeiServices,
        &gPeiStallPpiGuid,
        0,
        NULL,
        &PeiStall
    );
//<(EIP67320+)
    ZeroMem( &HubDescriptor, sizeof(HubDescriptor) );
    UsbIoPpi = &PeiUsbDevice->UsbIoPpi;

	Status = PeiSetHubDepth(PeiServices,
		UsbIoPpi,
		PeiUsbDevice->HubDepth);
	if ( EFI_ERROR( Status ) ) {
		return EFI_DEVICE_ERROR;
	}

    //
    // First get the whole descriptor, then
    // get the number of hub ports
    //
    Status = PeiGetHubDescriptor(
        PeiServices,
        UsbIoPpi,
        sizeof(EFI_USB_HUB_DESCRIPTOR),
        &HubDescriptor
             );
    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }

    PeiUsbDevice->DownStreamPortNo = HubDescriptor.NbrPorts;

    Status = PeiHubGetHubStatus( PeiServices,
        UsbIoPpi,
        (UINT32 *) &HubStatus
             );

    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }

    //
    //  Get all hub ports status
    //
    for (i = 0; i < PeiUsbDevice->DownStreamPortNo; i++) {

// Intel Debug port - Second port of the controller
    if(SkipDebugPort && (i == 1) ) 
        continue;

        Status = PeiHubGetPortStatus( PeiServices,
            UsbIoPpi,
            (UINT8) (i + 1),
            &PortStatus
                 );
        if ( EFI_ERROR( Status ) ) {
            continue;
        }
    }

    //
    //  Power all the hub ports
    //
    for (i = 0; i < PeiUsbDevice->DownStreamPortNo; i++) {
// Intel Debug port - Second port of the controller
    if( SkipDebugPort && (i == 1) )
        continue;

        Status = PeiHubSetPortFeature( PeiServices,
            UsbIoPpi,
            (UINT8) (i + 1),
            EfiUsbPortPower
                 );
        if ( EFI_ERROR( Status ) ) {
            continue;
        }
    }

    //
    // Clear Hub Status Change
    //
    Status = PeiHubGetHubStatus( PeiServices,
        UsbIoPpi,
        (UINT32 *) &HubStatus
             );
    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }
    else {
        //
        // Hub power supply change happens
        //
        if (HubStatus.HubChange & HUB_CHANGE_LOCAL_POWER) {
            PeiHubClearHubFeature( PeiServices,
                UsbIoPpi,
                C_HUB_LOCAL_POWER
            );
        }

        //
        // Hub change overcurrent happens
        //
        if (HubStatus.HubChange & HUB_CHANGE_OVERCURRENT) {
            PeiHubClearHubFeature( PeiServices,
                UsbIoPpi,
                C_HUB_OVER_CURRENT
            );
        }
    }
    PeiStall->Stall( PeiServices, PeiStall, (HubDescriptor.PwrOn2PwrGood << 1) *1000);  //(EIP67320)
    return EFI_SUCCESS;

}


//
// Send reset signal over the given root hub port
//
VOID PeiResetHubPort (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    UINT8               PortNum )
{
    PEI_STALL_PPI       *PeiStall;
    UINT8               n;
    EFI_USB_PORT_STATUS HubPortStatus;


    (**PeiServices).LocatePpi(
        PeiServices,
        &gPeiStallPpiGuid,
        0,
        NULL,
        &PeiStall
    );

    //
    // reset root port
    //
    PeiHubSetPortFeature(
        PeiServices,
        UsbIoPpi,
        PortNum,
        EfiUsbPortReset
    );

    n = 20;
    do {
        PeiHubGetPortStatus(
            PeiServices,
            UsbIoPpi,
            PortNum,
            (UINT32 *) &HubPortStatus
        );
        PeiStall->Stall(
            PeiServices,
            PeiStall,
            1000
        );
        n -= 1;
    } while ( (HubPortStatus.PortChangeStatus &
               USB_PORT_STAT_C_RESET) == 0 && n > 0 );

    PeiStall->Stall(
        PeiServices,
        PeiStall,
        500
    );
    //
    // Clear any change status
    //
    PeiHubClearPortFeature(
        PeiServices,
        UsbIoPpi,
        PortNum,
        EfiUsbPortResetChange
    );

    return;
}


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