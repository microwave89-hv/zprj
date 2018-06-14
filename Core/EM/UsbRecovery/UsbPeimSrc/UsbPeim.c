//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbPeimSrc/UsbPeim.c 17    11/24/12 5:46a Ryanchou $
//
// $Revision: 17 $
//
// $Date: 11/24/12 5:46a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbPeimSrc/UsbPeim.c $
// 
// 17    11/24/12 5:46a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 16    8/23/12 10:01p Wilsonlee
// [TAG]  		EIP97069
// [Category]  	Improvement
// [Description]  	Reset root port algorythm update.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// UhcPeim.h, UsbPeim.c, usb.h
// 
// 15    1/18/11 1:06a Ryanchou
// [TAG]  		EIP47931
// [Category]  	Improvement
// [Description]  	Added USB 3.0 hub support.
// [Files]  		EhciPei.c, EhciPei.h, HubPeim.c, HubPeim.h, OhciPei.c,
// OhciPei.h, UhcPeim.c, UhcPeim.h, usb.h, UsbHostController.h,
// UsbIoPeim.c, UsbPeim.c, UsbPeim.h, XhciPei.c, XhciPei.h
// 
// 14    10/22/10 2:55a Rameshr
// [TAG]- EIP 43687
// [Category]-IMPROVEMENT
// [Description]- Build warning from UsbRecovery driver -
// UsbHostController.obj : warning LNK4221: no public symbols found;
// archive member will be inaccessible. 
// [Files]- uhcpeim.c, usbpeim.c, UsbHostcontroller.h
// 
// 13    10/12/10 11:20a Olegi
// XHCI support added.
// 
// 12    1/06/10 11:23a Olegi
// Fix for EIP32503: The Interface descriptor of some devices is not
// directly after the configuration descriptor, and the first Endpoint
// descriptor is not directly after the Interface either. Changed the
// descriptior data parser.
// 
// 11    10/20/09 9:17a Olegi
// EIP#28255: Set proper TransactionTranslator field for a non-hispeed USB
// device.
// 
// 10    3/17/09 5:07p Olegi
// Added TransactionTranslator for slow/full speed devices behind USB2
// hub.
// 
// 9     10/21/08 5:57p Michaela
// Added EHCI-related fixes for issues 
// that may occur if EHCI is used before 
// USB Recovery is invoked:
//   Added SDL Tokens: 
//     PEI_EHCI_PCI_BDFS and 
//     PEI_EHCI_MEM_BASE_ADDRESSES. 
// 
// Removed/modified some debugging 
// development code:
//   Removed SDL Tokens: 
//     USBR_DEBUG_SUPPORT and 
//     USBR_SERIAL_PORT_AVAILABLE 
//   Removed Elinks: 
//     UsbRecoveryDebug_DIR and 
//     $(BUILD_DIR)\UsbRecoveryDebugDxe.ffs 
//   Modified SDL Token: 
//     FORCE_RECOVERY to default value of 0. 
// 
// (See this module's Help documentation 
// for more information.)
// 
// 8     7/29/08 5:52p Michaela
// 1) Updated code to move most porting tasks to SDL
// 2) Added more debug break points and improved interactive
//     debugging capability for when a serial port is not available.
// 3) Updated help files
// 
// 7     7/18/08 5:05p Michaela
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
// 6     7/10/08 6:37p Michaela
// Updated to support OHCI controllers
//
// 5     10/23/07 5:41p Ambikas
//
// 4     8/17/07 4:13p Ambikas
//
// 3     4/16/07 12:55p Sivagarn
// - Updated as per coding standard review
// - In previous check-in, TIANO.H file is removed and AMIMAPPING.H file
// is included
//
// 2     3/28/07 3:36a Meenakshim
//
// 1     9/22/06 12:19p Sivagarn
// - Initial Checkin
// - Included Recovery code in Source
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbPeim.C
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

   UsbPeim.c

   Abstract:

   Usb Bus PPI

   --*/

#include "UsbPeim.h"
#include "HubPeim.h"
#include "PeiUsbLib.h"


#include EFI_PPI_DEFINITION (Stall)
#include EFI_PPI_DEFINITION (LoadFile)

EFI_GUID gPeiUsbIoPpiGuid = PEI_USB_IO_PPI_GUID;

extern EFI_GUID gPeiStallPpiGuid;


#define PAGESIZE  4096

//static BOOLEAN  mImageInMemory = FALSE;


//
// Driver Entry Point
//


EFI_STATUS
PeimInitializeUsb (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );

//
// UsbIo PPI interface function
//
STATIC PEI_USB_IO_PPI         mUsbIoPpi = {
    PeiUsbControlTransfer,
    PeiUsbBulkTransfer,
    PeiUsbGetInterfaceDescriptor,
    PeiUsbGetEndpointDescriptor,
    PeiUsbPortReset
};

STATIC EFI_PEI_PPI_DESCRIPTOR mUsbIoPpiList = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gPeiUsbIoPpiGuid,
    NULL
};

//
// Helper functions
//
STATIC
EFI_STATUS
PeiUsbEnumeration (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi );

STATIC
EFI_STATUS
PeiConfigureUsbDevice (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice,
    IN UINT8            Port,
    IN OUT UINT8        *DeviceAddress );

STATIC
EFI_STATUS
PeiUsbGetAllConfiguration (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice );


VOID
ResetRootPort (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi,
    UINT8                          PortNum );

extern VOID ZeroMem (
    IN VOID  *Buffer,
    IN UINTN Size );



//
// PEIM Entry Point
//
// EFI_PEIM_ENTRY_POINT (PeimInitializeUsb);

EFI_STATUS PeimInitializeUsb (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS Status;
    UINTN      i;
    PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi;

    // Assign resources and enable UHCI controllers
    //
    // when the image is in flash, the global variable
    // mImageInMemory could not be modified;
    // when the image is successfully loaded into memory,
    // mImageInMemory could be modified to TRUE.
    //

    i = 0;
    while (TRUE) {
        //
        // Get UsbHcPpi at first.
        //
        Status = (**PeiServices).LocatePpi( PeiServices,
            &gPeiUsbHostControllerPpiGuid, i, NULL, &UsbHcPpi );

        if ( EFI_ERROR( Status ) ) {
            break;
        }

        PeiUsbEnumeration( PeiServices, UsbHcPpi ); // 0xff06
        i++;
    }

    return EFI_SUCCESS;
}


STATIC
EFI_STATUS PeiHubEnumeration (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice,
    IN UINT8            *CurrentAddress )
//
// Since we are not going to support hot-plug, we will do a
// dedicated polling process to get all ports change event
// discovered. This can help to avoid introduce interrupt
// transfer into the system, for each hub, we will wait for
// 3s and if one port is enabled we will not wait for others
// We will start parsing each of them in sequence.
//
{
    UINTN                Delay;
    UINT8                Port;
    EFI_STATUS           Status;
    PEI_USB_IO_PPI       *UsbIoPpi;
    EFI_USB_PORT_STATUS  PortStatus;
    BOOLEAN              PortChanged;
	UINT8                *AllocateAddress;
    PEI_USB_DEVICE       *NewPeiUsbDevice;
    PEI_STALL_PPI        *StallPpi;


    PortChanged = FALSE;

    UsbIoPpi = &PeiUsbDevice->UsbIoPpi;
    Status = (**PeiServices).LocatePpi( PeiServices, &gPeiStallPpiGuid,
        0, NULL, &StallPpi );

    Delay = (HUB_TIME_OUT * STALL_1_MILLI_SECOND / 50000) + 1;

    //
    // Do while will do a 3s scan for the USB HUB for a connected
    // device. If we have found one, the waiting process will be
    // breaked since we assue other ports will be discovered at
    // the same time.
    //
    do {
	    for (Port = 1; Port <= PeiUsbDevice->DownStreamPortNo; Port++) {

            Status = PeiHubGetPortStatus( PeiServices, UsbIoPpi,
	            Port, (UINT32 *) &PortStatus );

            if ( EFI_ERROR( Status ) ) {
                continue;
            }

            if ( IsPortConnectChange( PortStatus.PortChangeStatus ) ) {
                PortChanged = TRUE;
                PeiHubClearPortFeature( PeiServices, UsbIoPpi,
	                Port, EfiUsbPortConnectChange );

                if ( IsPortConnect( PortStatus.PortStatus ) ) {

					if (IsPortEnable(PortStatus.PortStatus) == FALSE) {
	                    //
	                    // First reset and enable this port
	                    //
		                PeiResetHubPort( PeiServices, UsbIoPpi, Port );

		                PeiHubGetPortStatus( PeiServices, UsbIoPpi,
		                    Port, (UINT32 *) &PortStatus );
					}

                    //
                    // Begin to deal with the new device
                    //
	                Status = (*PeiServices)->AllocatePool( PeiServices,
	                    sizeof(PEI_USB_DEVICE), &AllocateAddress );
                    if ( EFI_ERROR( Status ) ) {
                        return EFI_OUT_OF_RESOURCES;
                    }

	                NewPeiUsbDevice = (PEI_USB_DEVICE *)AllocateAddress;

                    ZeroMem( NewPeiUsbDevice, sizeof(PEI_USB_DEVICE) );

                    NewPeiUsbDevice->Signature =
                        PEI_USB_DEVICE_SIGNATURE;
                    NewPeiUsbDevice->DeviceAddress = 0;
                    NewPeiUsbDevice->MaxPacketSize0 = 8;
                    NewPeiUsbDevice->DataToggle = 0;
                    NewPeiUsbDevice->UsbIoPpi = mUsbIoPpi;
                    NewPeiUsbDevice->UsbIoPpiList = mUsbIoPpiList;
                    NewPeiUsbDevice->UsbIoPpiList.Ppi =
                        &NewPeiUsbDevice->UsbIoPpi;
                    NewPeiUsbDevice->UsbHcPpi =
                        PeiUsbDevice->UsbHcPpi;
                    NewPeiUsbDevice->DeviceSpeed =
                        USB_FULL_SPEED_DEVICE;
                    NewPeiUsbDevice->IsHub = 0x0;
                    NewPeiUsbDevice->DownStreamPortNo = 0x0;
                    NewPeiUsbDevice->TransactionTranslator =
	                    (UINT16)(Port << 7) + PeiUsbDevice->DeviceAddress;
					NewPeiUsbDevice->HubDepth = 0x0;
										//(EIP28255+)>
					if ( (PeiUsbDevice->DeviceSpeed == USB_SLOW_SPEED_DEVICE) ||
						(PeiUsbDevice->DeviceSpeed == USB_FULL_SPEED_DEVICE) )
					{
						NewPeiUsbDevice->TransactionTranslator = PeiUsbDevice->TransactionTranslator;
					}
										//<(EIP28255+)
                    if ( IsPortLowSpeedDeviceAttached( PortStatus.PortStatus ) )
                    {
                        NewPeiUsbDevice->DeviceSpeed = USB_SLOW_SPEED_DEVICE;
                    }

                    if ( IsPortHighSpeedDeviceAttached( PortStatus.PortStatus ) )
                    {
                        NewPeiUsbDevice->DeviceSpeed = USB_HIGH_SPEED_DEVICE;
                    }

                    if ( IsPortSuperSpeedDeviceAttached( PortStatus.PortStatus ) )
                    {
                        NewPeiUsbDevice->DeviceSpeed = USB_SUPER_SPEED_DEVICE;
                    }

                    //
                    // Configure that Usb Device
                    //
                    Status = PeiConfigureUsbDevice( PeiServices,
	                    NewPeiUsbDevice, Port, CurrentAddress );

                if ( EFI_ERROR( Status ) ) {
                    PeiHubClearPortFeature( PeiServices, UsbIoPpi,
	                        Port, EfiUsbPortEnable );
                    continue;
                }

                    Status = (**PeiServices).InstallPpi( PeiServices,
                        &NewPeiUsbDevice->UsbIoPpiList );

                    if (NewPeiUsbDevice->InterfaceDesc->InterfaceClass
                        == BASE_CLASS_HUB)
                    {
                        NewPeiUsbDevice->IsHub = 0x1;
						NewPeiUsbDevice->HubDepth = PeiUsbDevice->HubDepth + 1;

                        Status = PeiDoHubConfig( PeiServices,
                            NewPeiUsbDevice );
                        if ( EFI_ERROR( Status ) ) {
                            return Status;
                        }
                        PeiHubEnumeration( PeiServices, NewPeiUsbDevice,
                            CurrentAddress );
                    }
                }

            }
        }

        if (PortChanged) {
            break;
        }
        StallPpi->Stall( PeiServices, StallPpi, 50000 );

    } while (Delay--);

    return EFI_SUCCESS;
}


STATIC
EFI_STATUS PeiUsbEnumeration (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi )
{
    UINT8                NumOfRootPort;
    EFI_STATUS           Status;
    UINT8                Port;
    EFI_USB_PORT_STATUS  PortStatus;
    PEI_USB_DEVICE       *PeiUsbDevice;
	UINT8                *AllocateAddress;
    UINT8                CurrentAddress;
    PEI_STALL_PPI        *PeiStall;

    (**PeiServices).LocatePpi(
        PeiServices,
        &gPeiStallPpiGuid,
        0,
        NULL,
        &PeiStall
    );

    CurrentAddress = 0;
    UsbHcPpi->GetRootHubPortNumber(
        PeiServices,
        UsbHcPpi,
        (UINT8 *) &NumOfRootPort
    );


    for (Port = 1; Port <= NumOfRootPort; Port++) {
        //
        // First get root port status to detect changes happen
        //
        UsbHcPpi->GetRootHubPortStatus(
            PeiServices,
            UsbHcPpi,
            Port,
            &PortStatus
        );

        if ( IsPortConnectChange( PortStatus.PortChangeStatus ) ) {

            //
            // Changes happen, first clear this change status
            //
            UsbHcPpi->ClearRootHubPortFeature(
                PeiServices,
                UsbHcPpi,
                Port,
                EfiUsbPortConnectChange
            );

            if ( IsPortConnect( PortStatus.PortStatus ) ) {

				if (IsPortEnable(PortStatus.PortStatus) == FALSE) {
	                //
	                // First reset and enable this port
	                //
	                ResetRootPort( PeiServices, UsbHcPpi, Port );

	                UsbHcPpi->GetRootHubPortStatus(
	                    PeiServices,
	                    UsbHcPpi,
	                    Port,
	                    &PortStatus
	                );
				}

                //
                // Connect change happen
                //
                Status = (*PeiServices)->AllocatePool(
                    PeiServices,
                    sizeof(PEI_USB_DEVICE),
                    &AllocateAddress
                         );
                if ( EFI_ERROR( Status ) ) {
                    return EFI_OUT_OF_RESOURCES;
                }

                PeiUsbDevice = (PEI_USB_DEVICE *) ( (UINTN) AllocateAddress );
                ZeroMem( PeiUsbDevice, sizeof(PEI_USB_DEVICE) );

                PeiUsbDevice->Signature = PEI_USB_DEVICE_SIGNATURE;
                PeiUsbDevice->DeviceAddress = 0;
                PeiUsbDevice->MaxPacketSize0 = 8;
                PeiUsbDevice->DataToggle = 0;
                PeiUsbDevice->UsbIoPpi = mUsbIoPpi;
                PeiUsbDevice->UsbIoPpiList = mUsbIoPpiList;
                PeiUsbDevice->UsbIoPpiList.Ppi = &PeiUsbDevice->UsbIoPpi;
                PeiUsbDevice->UsbHcPpi = UsbHcPpi;
                PeiUsbDevice->DeviceSpeed = USB_FULL_SPEED_DEVICE;
                PeiUsbDevice->IsHub = 0x0;
                PeiUsbDevice->DownStreamPortNo = 0x0;
                PeiUsbDevice->TransactionTranslator = 0x0;
				PeiUsbDevice->HubDepth = 0x0;

                if ( IsPortLowSpeedDeviceAttached( PortStatus.PortStatus ) )
                {
                    PeiUsbDevice->DeviceSpeed = USB_SLOW_SPEED_DEVICE;
                }

                if ( IsPortHighSpeedDeviceAttached( PortStatus.PortStatus ) )
                {
                    PeiUsbDevice->DeviceSpeed = USB_HIGH_SPEED_DEVICE;
                }

                if ( IsPortSuperSpeedDeviceAttached( PortStatus.PortStatus ) )
                {
                    PeiUsbDevice->DeviceSpeed = USB_SUPER_SPEED_DEVICE;
                }

                //
                // Delay some times to enable usb devices to initiate.
                //
                PeiStall->Stall(
                    PeiServices,
                    PeiStall,
                    5000
                );

                //
                // Configure that Usb Device
                //
                Status = PeiConfigureUsbDevice(
                    PeiServices,
                    PeiUsbDevice,
                    Port,
                    &CurrentAddress
                         );

                if ( EFI_ERROR( Status ) ) {
                    UsbHcPpi->ClearRootHubPortFeature(
                        PeiServices,
                        UsbHcPpi,
                        Port,
                        EfiUsbPortEnable
                    );
                    continue;
                }

                Status = (**PeiServices).InstallPpi(
                    PeiServices,
                    &PeiUsbDevice->UsbIoPpiList
                         );

                if (PeiUsbDevice->InterfaceDesc->InterfaceClass
                    == BASE_CLASS_HUB)
                {
                    PeiUsbDevice->IsHub = 0x1;

                    Status = PeiDoHubConfig( PeiServices, PeiUsbDevice );
                    if ( EFI_ERROR( Status ) ) {
                        return Status;
                    }

                    PeiHubEnumeration( PeiServices, PeiUsbDevice,
                        &CurrentAddress );
                }
            }
        }
    }

    return EFI_SUCCESS;
}


STATIC EFI_STATUS PeiConfigureUsbDevice (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice,
    IN UINT8            Port,
    IN OUT UINT8        *DeviceAddress )
{
    EFI_USB_DEVICE_DESCRIPTOR DeviceDescriptor;
    EFI_STATUS     Status;
    PEI_USB_IO_PPI *UsbIoPpi;
    UINT8 i;
    PEI_STALL_PPI  *StallPpi = NULL;
    UINT8 Retry = 2;

    ( **PeiServices ).LocatePpi( PeiServices, &gPeiStallPpiGuid,
        0, NULL, &StallPpi );

    if (PeiUsbDevice->UsbHcPpi->PreConfigureDevice != NULL) {
        Status = PeiUsbDevice->UsbHcPpi->PreConfigureDevice( PeiServices,
            PeiUsbDevice->UsbHcPpi, Port, PeiUsbDevice->DeviceSpeed, 
            PeiUsbDevice->TransactionTranslator);
        if ( EFI_ERROR( Status ) ) {
            return Status;
        }
    }

    UsbIoPpi = &PeiUsbDevice->UsbIoPpi;

    //-----------------------------------------------------------------------
    // Try 5 times to read the first 8 bytes to determine the size
    for (i = 0; i < 5; i++) {
        Status = PeiUsbGetDescriptor( PeiServices,
            UsbIoPpi,
            SET_DESCRIPTOR_TYPE( USB_DT_DEVICE ), // Value = Type << 8 | Index
            0,                                    // Index
            8,                                    // DescriptorLength
            &DeviceDescriptor );
        if ( !EFI_ERROR( Status ) ) {
            break;
        }
        StallPpi->Stall( PeiServices, StallPpi, 100 * 1000 ); // 100msec delay
    }
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    //-----------------------------------------------------------------------
    // Set MaxPacketSize0 = 0x40 if packet size is not specified
    PeiUsbDevice->MaxPacketSize0 = (DeviceDescriptor.MaxPacketSize0)
                                   ? DeviceDescriptor.MaxPacketSize0
                                   : 0x40;


    //-----------------------------------------------------------------------
    // Get the entire USB device descriptor
    StallPpi->Stall( PeiServices, StallPpi, 10 * 1000 ); // 10msec delay
    Status = PeiUsbGetDescriptor(
        PeiServices,
        UsbIoPpi,
        SET_DESCRIPTOR_TYPE( USB_DT_DEVICE ),   // Value = Type << 8 | Index
        0,                                      // Index
        sizeof(EFI_USB_DEVICE_DESCRIPTOR),      // DescriptorLength
        &DeviceDescriptor );
        
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    //-----------------------------------------------------------------------
    // Get its default configuration and its first interface
    StallPpi->Stall( PeiServices, StallPpi, 10 * 1000 ); // 10msec delay
    Status = PeiUsbGetAllConfiguration(
        PeiServices,
        PeiUsbDevice );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    //-----------------------------------------------------------------------
    // Set the device's address
    StallPpi->Stall( PeiServices, StallPpi, 10 * 1000 ); // 10msec delay
    (*DeviceAddress)++;
    Status = PeiUsbSetDeviceAddress(
        PeiServices,
        UsbIoPpi,
        *DeviceAddress );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }
    PeiUsbDevice->DeviceAddress = *DeviceAddress;


    StallPpi->Stall( PeiServices, StallPpi, 200 * 1000 ); // 200msec delay

    Status = PeiUsbSetConfiguration(
        PeiServices,
        UsbIoPpi );

    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    return EFI_SUCCESS;
}


STATIC EFI_STATUS PeiUsbGetAllConfiguration (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *Device )
{
	EFI_USB_CONFIG_DESCRIPTOR	ConfigDesc = {0};
	EFI_USB_ENDPOINT_DESCRIPTOR	*EndPointDesc = NULL;	//(EIP32503+)
    EFI_STATUS     Status;
    PEI_USB_IO_PPI *UsbIoPpi = &Device->UsbIoPpi;
    UINTN i;
    UINT8          *LastAddress = 0;


    // Here we are parsing the descriptors for the device
    // configurations where the hierarchy of descriptors
    // is as follows:
    //
    // +----------------+
    // | Configuration1 |
    // +----------------+
    //        |         +------------+
    //        +---------| Interface1 |----+------------------+
    //        |         +------------+    |                  |
    //        |                     +-----------+       +-------------+
    //        |                     | Endpoint1 |  ...  | EndpointMax |
    //        |                     +-----------+       +-------------+
    //        |                :
    //        |                :
    //        |                :
    //        |
    //        |         +--------------+
    //        +---------| InterfaceMax |----+------------------+
    //                  +--------------+    |                  |
    //        :                       +-----------+       +-------------+
    //        :                       | Endpoint1 |  ...  | EndpointMax |
    //                                +-----------+       +-------------+
    // +------------------+
    // | ConfigurationMax |
    // +------------------+
    //        |         +------------+
    //        +---------| Interface1 |----+------------------+
    //        |         +------------+    |                  |
    //        |                     +-----------+       +-------------+
    //        |                     | Endpoint1 |  ...  | EndpointMax |
    //        |                     +-----------+       +-------------+
    //        |                :
    //        |                :
    //        |                :
    //        |         +--------------+
    //        +---------| InterfaceMax |----+------------------+
    //                  +--------------+    |                  |
    //                                +-----------+       +-------------+
    //                                | Endpoint1 |  ...  | EndpointMax |
    //                                +-----------+       +-------------+


    //-------------------------------------------------------------
    // Fortunately, we are only interested in the first/default
    // configuration and its first/default interface, so life is
    // simple!
    //-------------------------------------------------------------

    //-------------------------------------------------------------
    // First get the device's 9-byte configuration descriptor to
    // determine the length of all descriptors
    Status = PeiUsbGetDescriptor(
        PeiServices,
        UsbIoPpi,
        USB_DT_CONFIG << 8,
        0,
        9,
        &ConfigDesc );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    Status = (*PeiServices)->AllocatePool( PeiServices,
    	ConfigDesc.TotalLength, &Device->ConfigurationData );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }
    //-------------------------------------------------------------
    // Get all the descriptors for this configuration using
    // TotalLength from the first 9 bytes previously read.
    // Then, save the Configuration descriptor into the
    // device management structure.
    Status = PeiUsbGetDescriptor(
        PeiServices,
        UsbIoPpi,
        USB_DT_CONFIG << 8,
        0,
        ConfigDesc.TotalLength,
        (VOID *) Device->ConfigurationData );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }
    Device->ConfigDesc =
        (EFI_USB_CONFIG_DESCRIPTOR *) Device->ConfigurationData;

    LastAddress = Device->ConfigurationData +
                  Device->ConfigDesc->TotalLength - 1;

    if (Device->UsbHcPpi->EnableEndpoints != NULL) {
        Status = Device->UsbHcPpi->EnableEndpoints(PeiServices,
                    Device->UsbHcPpi, Device->ConfigurationData);
    
        if ( EFI_ERROR( Status ) ) {
            return Status;
        }
    }

    //--------------------------------------------------------------
    // Assume the Interface descriptor is directly after the
    // configuration descriptor.
    //--------------------------------------------------------------
    Device->InterfaceDesc = (EFI_USB_INTERFACE_DESCRIPTOR *)
                            ( (UINT8 *) Device->ConfigDesc +
                             Device->ConfigDesc->Length );
										//(EIP32503+)>
	while ((UINT8 *)Device->InterfaceDesc < LastAddress && 
			Device->InterfaceDesc->DescriptorType != USB_DT_INTERFACE)
	{
		Device->InterfaceDesc = (EFI_USB_INTERFACE_DESCRIPTOR *)
                            ( (UINT8 *) Device->InterfaceDesc +
                             Device->InterfaceDesc->Length );
	}
										//<(EIP32503+)
    //--------------------------------------------------------------
    // Assume the first Endpoint descriptor is directly after the
    // Interface descriptor.
    //--------------------------------------------------------------
    									//(EIP32503)>
    EndPointDesc = (EFI_USB_ENDPOINT_DESCRIPTOR *)
                   ( (UINT8 *) Device->InterfaceDesc +
                   Device->InterfaceDesc->Length );

    for (i = 0; i < Device->InterfaceDesc->NumEndpoints && 
		(UINT8 *)EndPointDesc < LastAddress; )
	{
		if(EndPointDesc->DescriptorType == USB_DT_ENDPOINT)
		{
			Device->EndpointDesc[i++] = EndPointDesc;
		}
		EndPointDesc = (EFI_USB_ENDPOINT_DESCRIPTOR *)
    	               ( (UINT8 *) EndPointDesc +
        	           EndPointDesc->Length );
    }
										//<(EIP32503)
    return EFI_SUCCESS;
}


//
// Send reset signal over the given root hub port
//
VOID ResetRootPort (
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi,
    UINT8                          PortNum )
{
    EFI_PEI_STALL_PPI       *PeiStall;
	EFI_USB_PORT_STATUS     PortStatus;
	UINT8                   i;

    ( **PeiServices ).LocatePpi(
        PeiServices,
        &gPeiStallPpiGuid,
        0,
        NULL,
        &PeiStall
    );


    //
    // reset root port
    //
    UsbHcPpi->SetRootHubPortFeature(
        PeiServices,
        UsbHcPpi,
        PortNum,
        EfiUsbPortReset
    );

	for (i = 0; i < 100; i++) {
        UsbHcPpi->GetRootHubPortStatus(
            PeiServices,
            UsbHcPpi,
            PortNum,
            &PortStatus
        );

		if ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET) != 0) {
			break;
		}

	    PeiStall->Stall(
	        PeiServices,
	        PeiStall,
	        1 * 1000            // NVS - Changed to 10 msec (as per AMI USB Code)
	    );
	}

	if ((PortStatus.PortChangeStatus & USB_PORT_STAT_C_RESET) == 0) {
		return;
	}

    //
    // clear reset root port
    //
    UsbHcPpi->ClearRootHubPortFeature(
        PeiServices,
        UsbHcPpi,
        PortNum,
        EfiUsbPortResetChange
    );


    UsbHcPpi->GetRootHubPortStatus(
        PeiServices,
        UsbHcPpi,
        PortNum,
        &PortStatus
    );

	if ((PortStatus.PortChangeStatus & USB_PORT_STAT_ENABLE) == 0) {
		//
		// Set port enable
		//
		UsbHcPpi->SetRootHubPortFeature(
		    PeiServices,
		    UsbHcPpi,
		    PortNum,
		    EfiUsbPortEnable
		);
	    PeiStall->Stall(
	        PeiServices,
	        PeiStall,
	        100 * 1000            // NVS - Changed to 100msec as per AMI USB code
	    );
	}

    return;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************