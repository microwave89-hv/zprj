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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/PeiUsbLib.c 10    11/24/12 5:43a Ryanchou $
//
// $Revision: 10 $
//
// $Date: 11/24/12 5:43a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/PeiUsbLib.c $
// 
// 10    11/24/12 5:43a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 9     4/12/11 12:00a Rameshr
// [TAG]- EIP 57444
// [Category]-IMPROVEMENT
// [Description]- PI1.1 Support.
// [Files]- OhciPeiboard.c,Xhcipei.c, Peiusblib.c
// 
// 8     10/11/10 4:51p Olegi
// XHCI support added.
// 
// 7     4/06/10 3:37p Fasihm
// EIP#31987 - Added the generic USBRecovery Fix in the module.
// 
// 6     3/17/09 5:10p Olegi
// Added IsPortHighSpeedDeviceAttached function.
// 
// 5     7/18/08 5:03p Michaela
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
// 4     7/10/08 6:33p Michaela
// Updated to support OHCI controllers
//
// 3     4/16/07 1:02p Sivagarn
// - Updated as per coding standard review
// - In previous check-in, TIANO.H file is removed and AMIMAPPING.H file
// is included
//
// 2     3/28/07 3:07a Meenakshim
// Removed dependency on core source files..Added amimapping file.
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
// Name:        PeiUsbLib.C
//
// Description: 
//      This file belongs to "Framework" and included here for
//      compatibility purposes. This file is modified by AMI to include
//      copyright message, appropriate header and integration code.
//      This file contains generic routines needed for USB recover
//      PEIM
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

    PeiUsbLib.c

   Abstract:

   Common Libarary  for PEI USB

   Revision History

   --*/

#include "Efi.h"
#include "Pei.h"
#include "usb.h"
#include "UsbPeim.h"
#include "PeiUsbLib.h"


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   ZeroMem
//
// Description: This library function initializes provided buffer with Zero
//
// Input:       *Buffer     Pointer to the buffer whose content to be inited
//              Size        Number of bytes to be filled in
//
// Output:      Returns None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID ZeroMem (
    OUT VOID    *Buffer,
    IN  UINTN   Size )
{
    UINT8 *Ptr;

    Ptr = Buffer;
    while (Size--) {
        *(Ptr++) = 0;
    }
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure:   PeiCopyMem
//
// Description: 
//      This library function copies bytes specified by Length from the memory
//      location specified by Source to the memory location specified by 
//      Destination.
//
// Input:
//      OUT VOID *Destination
//                  --  Target memory location of copy
//      IN  VOID *Source
//                  --  Source memory location
//      IN  UINTN Length
//                  --  Number of bytes to copy
//
// Output:     
//      VOID (No Return Value)
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

VOID PeiCopyMem (
    OUT VOID *Destination,
    IN VOID  *Source,
    IN UINTN Length )
{
    CHAR8 *Destination8;
    CHAR8 *Source8;

    Destination8 = Destination;
    Source8 = Source;
    while (Length--) {
        *(Destination8++) = *(Source8++);
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PeiUsbGetDescriptor
//
// Description:  
//      This function uses a device's PEI_USB_IO_PPI interface to execute a 
//      control transfer on the default control pipe to obtain a device 
//      descriptor.
//
// Input: 
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN PEI_USB_IO_PPI *UsbIoPpi
//                  --  PEI_USB_IO_PPI interface pointer for the device
//                      that is being accessed
//      IN UINT16 Value
//                  --  The upper byte of Value specifies the type of 
//                      descriptor and the lower byte of Value specifies
//                      the index (for configuration and string descriptors)
//      IN UINT16 Index
//                  --  Specifies the Language ID for string descriptors
//                      or zero for all other descriptors
//      IN UINT16 DescriptorLength
//                  --  Specifies the length of the descriptor to be
//                      retrieved
//      IN VOID *Descriptor
//                  --  Allocated buffer in which the descriptor will be 
//                      returned
//
// Output:  
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
// Notes:
//      The lower byte of Value is typically zero and the upper byte of 
//      Value specifies the type of descriptor:
//
//                  READ_BITS(Value,15,8)   Descriptor
//                  -------------------------------------------------
//                          1               DEVICE
//                          2               CONFIGURATION
//                          3               STRING
//                          4               INTERFACE
//                          5               ENDPOINT
//                          6               DEVICE_QUALIFIER
//                          7               OTHER_SPEED_CONFIGURATION
//                          8               INTERFACE_POWER
//
//      For additional reference, read the USB Device Framework chapter in 
//      the USB Specification (Revision 2.0)
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiUsbGetDescriptor (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT16           Value,
    IN UINT16           Index,
    IN UINT16           DescriptorLength,
    IN VOID             *Descriptor )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;

    if (UsbIoPpi == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    DevReq.RequestType = USB_DEV_GET_DESCRIPTOR_REQ_TYPE;
    DevReq.Request = USB_DEV_GET_DESCRIPTOR;
    DevReq.Value = Value;
    DevReq.Index = Index;
    DevReq.Length = DescriptorLength;

    Timeout = 3000;

    return UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
		EfiUsbDataIn,
        Timeout,
        Descriptor,
        DescriptorLength
    );

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PeiUsbSetDeviceAddress
//
// Description: 
//      This function uses a device's PEI_USB_IO_PPI interface to execute a 
//      control transfer on the default control pipe to set the device's 
//      address on the USB bus for all future accesses.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN PEI_USB_IO_PPI *UsbIoPpi
//                  --  PEI_USB_IO_PPI interface pointer for the device
//                      that is being accessed
//      IN UINT16 AddressValue
//                  --  The device address to be set
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiUsbSetDeviceAddress (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT16           AddressValue )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;

    if (UsbIoPpi == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    DevReq.RequestType = USB_DEV_SET_ADDRESS_REQ_TYPE;
    DevReq.Request = USB_DEV_SET_ADDRESS;
    DevReq.Value = AddressValue;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;

    return UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
    );

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PeiUsbClearDeviceFeature
//
// Description:  
//      This function uses a device's PEI_USB_IO_PPI interface to execute a 
//      control transfer on the default control pipe to clear or disable a
//      specific feature.
//
// Input: 
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN PEI_USB_IO_PPI *UsbIoPpi
//                  --  PEI_USB_IO_PPI interface pointer for the device
//                      that is being accessed
//      IN EFI_USB_RECIPIENT Recipient
//                  --  The recipient of the request can be a device,
//                      an interface or an endpoint respectively specified 
//                      by EfiUsbDevice, EfiUsbInterface or EfiUsbEndpoint.
//      IN UINT16 Value
//                  --  The feature selector to be cleared or disabled
//      IN UINT16 Target
//                  --  This value specifies an index for a specific 
//                      interface/endpoint or zero for device recipients.
//
// Output:  
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiUsbClearDeviceFeature (
    IN EFI_PEI_SERVICES  **PeiServices,
    IN PEI_USB_IO_PPI    *UsbIoPpi,
    IN EFI_USB_RECIPIENT Recipient,
    IN UINT16            Value,
    IN UINT16            Target )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;

    if (UsbIoPpi == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    switch (Recipient)
    {
    case EfiUsbDevice:
        DevReq.RequestType = 0x00;
        break;

    case EfiUsbInterface:
        DevReq.RequestType = 0x01;
        break;

    case EfiUsbEndpoint:
        DevReq.RequestType = 0x02;
        break;
    }

    DevReq.Request = USB_DEV_CLEAR_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = Target;
    DevReq.Length = 0;

    Timeout = 3000;

    return UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
    );

}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PeiUsbSetConfiguration
//
// Description: 
//      This function uses a device's PEI_USB_IO_PPI interface to execute a 
//      control transfer on the default control pipe to set the device's 
//      default configuration index of 1.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN PEI_USB_IO_PPI *UsbIoPpi
//                  --  PEI_USB_IO_PPI interface pointer for the device
//                      that is being accessed
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiUsbSetConfiguration (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    DevReq.RequestType = USB_DEV_SET_CONFIGURATION_REQ_TYPE;
    DevReq.Request = USB_DEV_SET_CONFIGURATION;
    DevReq.Value = 1;  // default
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;

    return UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
    );
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   PeiUsbClearEndpointHalt
//
// Description: 
//      This function uses a device's PEI_USB_IO_PPI interface to execute a 
//      control transfer on the default control pipe to clear a bulk Endpoint
//      halt condition (and resetting the Halt status bit) for a specified 
//      Endpoint.
//
// Input:
//      IN EFI_PEI_SERVICES **PeiServices
//                  --  PEI Sevices table pointer
//      IN PEI_USB_IO_PPI *UsbIoPpi
//                  --  PEI_USB_IO_PPI interface pointer for the device
//                      that is being accessed
//      IN UINT8 EndpointAddress
//                  --  The endpoint for which the Halt condition is to be 
//                      cleared
//
// Output: 
//      EFI_STATUS (Return Value)
//                  = EFI_SUCCESS on successful completion
//                      or valid EFI error code
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS PeiUsbClearEndpointHalt (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            EndpointAddress )
{
    EFI_STATUS     Status;
    PEI_USB_DEVICE *PeiUsbDev;
    EFI_USB_ENDPOINT_DESCRIPTOR *EndpointDescriptor;
    UINT8 EndpointIndex = 0;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );

    while (EndpointIndex < MAX_ENDPOINT) {
        Status = UsbIoPpi->UsbGetEndpointDescriptor( PeiServices, UsbIoPpi,
            EndpointIndex, &EndpointDescriptor );
        if ( EFI_ERROR( Status ) ) {
            return EFI_INVALID_PARAMETER;
        }

        if (EndpointDescriptor->EndpointAddress == EndpointAddress) {
            break;
        }

        EndpointIndex++;
    }

    if (EndpointIndex == MAX_ENDPOINT) {
        return EFI_INVALID_PARAMETER;
    }

    Status = PeiUsbClearDeviceFeature(
        PeiServices,
        UsbIoPpi,
        EfiUsbEndpoint,
        EfiUsbEndpointHalt,
        EndpointAddress
             );

    //
    // set data toggle to zero.
    //
    if ( ( PeiUsbDev->DataToggle & (1 << EndpointIndex) ) != 0 ) {
        PeiUsbDev->DataToggle =
            (UINT8) ( PeiUsbDev->DataToggle ^ (1 << EndpointIndex) );
    }

    return Status;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IsPortConnect
//
// Description: 
//      This function returns true if the Hub Class device's Current Connect 
//      Status bit is set in the port status value specified by PortStatus.
//
// Input:
//      IN UINT16 PortStatus
//                  --  This value is the USB Specification (Revision 2.0) 
//                      Hub Port Status Field value as returned by the Get 
//                      Port Status Hub Class device standard request.
//
// Output: 
//      BOOLEAN (Return Value)
//                  = TRUE if a device is present or FALSE if a device is not
//                      present
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPortConnect (
    IN UINT16 PortStatus )
{
    //
    // return the bit 0 value of PortStatus
    //
    if ( (PortStatus & USB_PORT_STAT_CONNECTION) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IsPortEnable
//
// Description: 
//
// Input:
//
// Output: 
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPortEnable (
    IN UINT16 PortStatus )
{
    //
    // return the bit 0 value of PortStatus
    //
    if ( (PortStatus & USB_PORT_STAT_ENABLE) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IsPortLowSpeedDeviceAttached
//
// Description: 
//      This function returns true if the Hub Class device's Low-Speed 
//      Device Attached bit is set in the port status value specified by 
//      PortStatus.
//
// Input:
//      IN UINT16 PortStatus
//                  --  This value is the USB Specification (Revision 2.0) 
//                      Hub Port Status Field value as returned by the Get 
//                      Port Status Hub Class device standard request.
//
// Output: 
//      BOOLEAN (Return Value)
//                  = TRUE if a low-speed device is present or FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPortLowSpeedDeviceAttached (
    UINT16 PortStatus )
{
    //
    // return the bit 9 value of PortStatus
    //
    if ( (PortStatus & USB_PORT_STAT_LOW_SPEED) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IsPortHighSpeedDeviceAttached
//
// Description: 
//      This function returns true if the Hub Class device's High-Speed 
//      Device Attached bit is set in the port status value specified by 
//      PortStatus.
//
// Input:
//      IN UINT16 PortStatus
//                  --  This value is the USB Specification (Revision 2.0) 
//                      Hub Port Status Field value as returned by the Get 
//                      Port Status Hub Class device standard request.
//
// Output: 
//      BOOLEAN (Return Value)
//                  = TRUE if a high-speed device is present or FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPortHighSpeedDeviceAttached (
    UINT16 PortStatus )
{
    //
    // return the bit 10 value of PortStatus
    //
    if ( (PortStatus & USB_PORT_STAT_HIGH_SPEED) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IsPortSuperSpeedDeviceAttached
//
// Description: 
//      This function returns true if connect status indicates the SuperSpeed
//      device.
//
// Output: 
//      BOOLEAN (Return Value)
//                  = TRUE if a super-speed device is present or FALSE otherwise
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPortSuperSpeedDeviceAttached (
    UINT16 PortStatus )
{
    //
    // return the bit 10 value of PortStatus
    //
    if ( (PortStatus & USB_PORT_STAT_SUPER_SPEED) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Procedure:   IsPortConnectChange
//
// Description: 
//      This function returns true if the Hub Class device's Connect Status 
//      Change bit is set in the port change status value specified 
//      by PortChangeStatus.
//
// Input:
//      IN UINT16 PortStatus
//                  --  This value is the USB Specification (Revision 2.0) 
//                      Hub Port Change Field value as returned by the Get 
//                      Port Status Hub Class device standard request.
//
// Output: 
//      BOOLEAN (Return Value)
//                  = TRUE if Current Connect status has changed or FALSE
//                      if no change has occurred to Current Connect status
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

BOOLEAN IsPortConnectChange (
    UINT16 PortChangeStatus )
{
    //
    // return the bit 0 value of PortChangeStatus
    //
    if ( (PortChangeStatus & USB_PORT_STAT_C_CONNECTION) != 0 ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}


#ifndef PI_SPECIFICATION_VERSION //old Core

EFI_STATUS PciCfgModify(
    IN CONST EFI_PEI_SERVICES 	**PeiServices,
    IN EFI_PEI_PCI_CFG_PPI_WIDTH	Width,
    IN UINT64					Address,
    IN UINTN					SetBits,
    IN UINTN					ClearBits)
{
    if((*PeiServices)->PciCfg==NULL)
        return EFI_NOT_AVAILABLE_YET;

    return (*PeiServices)->PciCfg->Modify(
                    (EFI_PEI_SERVICES**)PeiServices,
                    (*PeiServices)->PciCfg,
                    Width, Address,
                    SetBits, ClearBits);
}
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
