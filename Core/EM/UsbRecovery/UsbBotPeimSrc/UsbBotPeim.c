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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbBotPeimSrc/UsbBotPeim.c 13    11/24/12 5:47a Ryanchou $
//
// $Revision: 13 $
//
// $Date: 11/24/12 5:47a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbBotPeimSrc/UsbBotPeim.c $
// 
// 13    11/24/12 5:47a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 12    4/16/11 3:42a Ryanchou
// [TAG]  		EIP50311
// [Category]  	New Feature
// [Description]  	Multiple LUN device support added.
// [Files]  		BotPeim.c, UsbBotPeim.c, UsbBotPeim.h
// 
// 11    10/12/10 11:20a Olegi
// XHCI support added.
// 
// 10    2/23/10 3:36p Olegi
// Bugfixes found by Coverity tests: EIP34507.
// 
// 9     3/03/09 7:22p Olegi
// Added EHCI support.
// 
// 8     10/21/08 5:58p Michaela
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
// 7     7/29/08 5:51p Michaela
// 1) Updated code to move most porting tasks to SDL
// 2) Added more debug break points and improved interactive
//     debugging capability for when a serial port is not available.
// 3) Updated help files
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
// 5     7/10/08 6:38p Michaela
// Updated to support OHCI controllers
//
// 4     10/23/07 5:42p Ambikas
//
// 3     8/17/07 4:35p Ambikas
//
// 2     8/17/07 4:11p Ambikas
//
// 1     9/22/06 12:17p Sivagarn
// - Included Recovery code in Source
//
// 1     9/22/06 12:14p Sivagarn
// - Initial checkin
// - Included Recovery code in Source
//
//*****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
// Name:        UsbbotPeim.C
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
   This file contains a 'Sample Driver' and is licensed as such
   under the terms of your license agreement with Intel or your
   vendor.  This file may be modified by the user, subject to
   the additional terms of the license agreement
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

   UsbBotPeim.c

   Abstract:

   Usb Bus PPI

   --*/

#include "UsbBotPeim.h"
#include "BotPeim.h"
#define PAGESIZE  4096
#include EFI_PPI_DEFINITION( Stall )
#include EFI_PPI_DEFINITION( LoadFile )

static EFI_GUID gPeiStallPpiGuid = PEI_STALL_PPI_GUID;
static EFI_GUID gPeiBlockIoPpiGuid = EFI_PEI_VIRTUAL_BLOCK_IO_PPI;
static EFI_GUID gPeiUsbIoPpiGuid = PEI_USB_IO_PPI_GUID;

//
// Global function
//
STATIC
EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH |
    EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gPeiUsbIoPpiGuid,
    NotifyOnUsbIoPpi
};

STATIC
EFI_PEI_RECOVERY_BLOCK_IO_PPI mRecoveryBlkIoPpi = {
    BotGetNumberOfBlockDevices,
    BotGetMediaInfo,
    BotReadBlocks
};

STATIC
EFI_PEI_PPI_DESCRIPTOR mPpiList = {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gPeiBlockIoPpiGuid,
    NULL
};

//
// Driver Entry Point
//
EFI_STATUS
PeimInitializeUsbBot (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices );

STATIC
EFI_STATUS
PeiBotDetectMedia (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev );

EFI_STATUS PeimInitializeUsbBot (
    IN EFI_FFS_FILE_HEADER *FfsHeader,
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS     Status;
    UINTN          UsbIoPpiInstance;
    EFI_PEI_PPI_DESCRIPTOR *TempPpiDescriptor;
    PEI_USB_IO_PPI *UsbIoPpi;
	UINTN           PpiInstance;

    for (PpiInstance = 0; PpiInstance < PEI_MAX_USB_RECOVERY_INIT_PPI; PpiInstance++)
    {
        PEI_USB_CHIP_INIT_PPI  *UsbChipsetRecoveryInitPpi;
        static EFI_GUID gPeiChipUsbRecoveryInitPpiGuid = PEI_USB_CHIP_INIT_PPI_GUID;

        Status = (**PeiServices).LocatePpi( PeiServices, &gPeiChipUsbRecoveryInitPpiGuid,
            PpiInstance, NULL, &UsbChipsetRecoveryInitPpi );
        if (EFI_ERROR( Status ) ) break;

        UsbChipsetRecoveryInitPpi->EnableChipUsbRecovery(PeiServices);
    }	

  #if (PEI_EHCI_SUPPORT == 1)
    EhciPeiUsbEntryPoint( FfsHeader, PeiServices );
  #endif
  #if (PEI_UHCI_SUPPORT == 1)
    UhciPeiUsbEntryPoint( FfsHeader, PeiServices );
    UhcPeimEntry( FfsHeader, PeiServices );
  #endif
  #if (PEI_OHCI_SUPPORT == 1)
    OhciPeiUsbEntryPoint( FfsHeader, PeiServices ); // 0xff02
  #endif
  #if (PEI_XHCI_SUPPORT == 1)
    XhciPeiUsbEntryPoint( FfsHeader, PeiServices ); // 0xff02
  #endif
    PeimInitializeUsb( FfsHeader, PeiServices ); // 0xff05

    
    //
    // locate all usb io PPIs
    //
    for (UsbIoPpiInstance = 0;
         UsbIoPpiInstance < PEI_FAT_MAX_USB_IO_PPI;
         UsbIoPpiInstance++)
    {
        Status = (**PeiServices).LocatePpi( PeiServices,
            &gPeiUsbIoPpiGuid,
            UsbIoPpiInstance,
            &TempPpiDescriptor,
            &UsbIoPpi
                 );
        if ( EFI_ERROR( Status ) ) {
            break;
        }

        InitUsbBot( PeiServices, UsbIoPpi );

    }

    return EFI_SUCCESS;
}


EFI_STATUS NotifyOnUsbIoPpi (
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN VOID                      *InvokePpi )
{
    PEI_USB_IO_PPI *UsbIoPpi;

    UsbIoPpi = (PEI_USB_IO_PPI *) InvokePpi;

    InitUsbBot( PeiServices, UsbIoPpi );

    return EFI_SUCCESS;
}

EFI_STATUS GetMaxLun (
    IN  EFI_PEI_SERVICES    **PeiServices,
    IN  PEI_USB_IO_PPI      *UsbIoPpi,
    IN  UINT8               Port,
    OUT UINT8               *MaxLun )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    EFI_STATUS EfiStatus;
    UINT32     Timeout;

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    //
    // Fill Device request packet
    //
    DevReq.RequestType = 0xA1;
    DevReq.Request = 0x0FE;
    DevReq.Value = 0;
    DevReq.Index = Port;
    DevReq.Length = sizeof(UINT8);

    Timeout = 3000;

    EfiStatus = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        UsbDataIn,
        Timeout,
        MaxLun,
        sizeof(UINT8)
                );

    return EfiStatus;
}


EFI_STATUS InitUsbBot (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi )
{
    STATIC UINTN   UsbIoPpiIndex = 0;

    PEI_BOT_DEVICE *PeiBotDevice;
    EFI_STATUS     Status;
    EFI_USB_INTERFACE_DESCRIPTOR *InterfaceDesc;
    UINT8                        *AllocateAddress;
    EFI_USB_ENDPOINT_DESCRIPTOR  *EndpointDesc;
    UINT8 i;
    UINT8 MaxLun = 0;
    UINT8 CurrentLun;

    //
    // Check its interface
    //
    Status = UsbIoPpi->UsbGetInterfaceDescriptor( PeiServices,
        UsbIoPpi, &InterfaceDesc );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    //
    // Check if it is the BOT device we support
    //

    if ( (InterfaceDesc->InterfaceClass != BASE_CLASS_MASS_STORAGE)
        || (InterfaceDesc->InterfaceProtocol != PROTOCOL_BOT) ) {

        return EFI_NOT_FOUND;
    }

    Status = GetMaxLun(PeiServices,UsbIoPpi,InterfaceDesc->InterfaceNumber,&MaxLun);
    
    for(CurrentLun = 0; CurrentLun <= MaxLun; CurrentLun++) {
    
	    Status = (*PeiServices)->AllocatePool( PeiServices,
	        sizeof(PEI_BOT_DEVICE), &AllocateAddress );
	    if ( EFI_ERROR( Status ) ) {
	        return Status;
	    }

        PeiBotDevice = (PEI_BOT_DEVICE *) ( (UINTN) AllocateAddress );
		(**PeiServices).SetMem(PeiBotDevice, sizeof(PEI_BOT_DEVICE), 0);

        PeiBotDevice->Signature = PEI_BOT_DEVICE_SIGNATURE;
        PeiBotDevice->UsbIoPpi = UsbIoPpi;
        PeiBotDevice->BotInterface = InterfaceDesc;
        PeiBotDevice->FdEmulOffset = 0; //bala
        //
        // Default value
        //
        PeiBotDevice->Media.DeviceType = UsbMassStorage;
        PeiBotDevice->Media.BlockSize = 0x200;
        PeiBotDevice->Lun = CurrentLun;
    
        //
        // Check its Bulk-in/Bulk-out endpoint
        //
        for (i = 0; i < 2; i++) {
            Status = UsbIoPpi->UsbGetEndpointDescriptor( PeiServices,
                UsbIoPpi, i, &EndpointDesc );
            if ( EFI_ERROR( Status ) ) {
                return Status;
            }

            if (EndpointDesc->Attributes != 2) {
                continue;
            }

            if ( (EndpointDesc->EndpointAddress & 0x80) != 0 ) {
                PeiBotDevice->BulkInEndpoint = EndpointDesc;
            }
            else {
                PeiBotDevice->BulkOutEndpoint = EndpointDesc;
            }

        }

        PeiBotDevice->BlkIoPpi = mRecoveryBlkIoPpi;
        PeiBotDevice->BlkIoPpiList = mPpiList;
        PeiBotDevice->BlkIoPpiList.Ppi = &PeiBotDevice->BlkIoPpi;

        Status = PeiUsbInquiry( PeiServices, PeiBotDevice );
        if ( EFI_ERROR( Status ) ) {
            return Status;
        }

        Status = (**PeiServices).InstallPpi( PeiServices,
            &PeiBotDevice->BlkIoPpiList );
        if ( EFI_ERROR( Status ) ) {
            return Status;
        }
    }

    return EFI_SUCCESS;
}


EFI_STATUS BotGetNumberOfBlockDevices (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices )
{
    //
    // For Usb devices, this value should be always 1
    //

    *NumberBlockDevices = 1;
    return EFI_SUCCESS;
}


EFI_STATUS BotGetMediaInfo (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA       *MediaInfo )
{
    PEI_BOT_DEVICE *PeiBotDev;
    EFI_STATUS     Status = EFI_SUCCESS;

    PeiBotDev = PEI_BOT_DEVICE_FROM_THIS( This );

    Status = PeiBotDetectMedia(
        PeiServices,
        PeiBotDev
             );

    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    *MediaInfo = PeiBotDev->Media;

    return EFI_SUCCESS;
}


EFI_STATUS PeiBotDetectMedia (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev )
{

    EFI_STATUS Status = EFI_SUCCESS;
    UINT8                *AllocateAddress;
    REQUEST_SENSE_DATA   *SensePtr;
    UINT8         SenseKey, ASC, ASCQ;
    UINT8         RetryCount, RetryReq = 0;
    PEI_STALL_PPI *StallPpi;
    UINT32        Temp;
    UINT32        Temp1, Temp2, Temp3;

    //PeiUsbReadCapacity fills PeiBotDev structure for
    //BlockSize, LastBlock, Media Present
    for (RetryCount = 0; RetryCount < 25; RetryCount++)
    {
        Status = PeiUsbReadCapacity(
            PeiServices,
            PeiBotDev
                 );

        if ( EFI_ERROR( Status ) )
        {
            Temp = RetryCount;

            //If ReadCapcity fails, then find out type of error
            if (RetryCount == 0)
            {
				if (PeiBotDev->SensePtr == NULL) {
	                //During the first retry allocate the memory
	                Status = (**PeiServices).AllocatePool(
	                    PeiServices,
	                    sizeof(REQUEST_SENSE_DATA),
	                    &AllocateAddress
	                         );
	                if ( EFI_ERROR( Status ) )
	                {
	                    return Status;
	                }
					PeiBotDev->SensePtr = (REQUEST_SENSE_DATA *)AllocateAddress;
				}
                SensePtr = PeiBotDev->SensePtr;
                (**PeiServices).SetMem((VOID*)SensePtr, sizeof(REQUEST_SENSE_DATA), 0);
                Status = (**PeiServices).LocatePpi( PeiServices,
                    &gPeiStallPpiGuid, 0, NULL, &StallPpi );
            }

            Status = PeiUsbRequestSense(
                PeiServices,
                PeiBotDev,
                (UINT8 *) SensePtr
                     );
            if ( EFI_ERROR( Status ) )
            {
                //If RequestSense also fails, then there is an serious error
                //Return to the caller with appropriate error code
                //              PeiBotDev->Media.MediaPresent = FALSE;
                //              PeiBotDev->Media.BlockSize = 0;
                //              Status = EFI_DEVICE_ERROR;
                //              return EFI_DEVICE_ERROR;
            }
            //TODO:Parse the sense buffer for the error
            //If media getting ready, then wait for few mSec, then
            //retry ReadCapacity
            //For all other errors, return with error condition

            SenseKey = SensePtr->sense_key;
            ASC = SensePtr->addnl_sense_code;
            ASCQ = SensePtr->addnl_sense_code_qualifier;
            Temp1 = SenseKey;
            Temp2 = ASC;
            Temp3 = ASCQ;

            if ( (SenseKey == 0x02) && (ASC == 0x3a) && (ASCQ == 00) )
            {
                //medium Not Present.
                //Don't retry.
                return EFI_DEVICE_ERROR;

            }
            // The following retry logic is broken, assigning RetryReq 1 does
            // not make sense and leads to a dead code later: "if (!RetryReq)"
            // Remove this assignment. EIP34507
            //For all error retry ReadCapacity 25 times
            //RetryReq = 1;   //Do retry
            if (SenseKey == 0x02)
            {
                //Logical Unit Problem
                if (ASC == 0x04)
                {
                    //Becoming Ready/Init Required/ Busy/ Format in Progress.
                    RetryReq = 1;   //Do retry

                }
                if ( (ASC == 0x06) || (ASC == 0x08) )
                {
                    //No ref. found/ Comm failure
                    RetryReq = 1;   //Do retry
                }
            }


            PeiBotDev->Media.MediaPresent = FALSE;
            PeiBotDev->Media.BlockSize = 0;
            Status = EFI_DEVICE_ERROR;
            if (!RetryReq) {
                return Status;
            }
        }
        else {
            Status = EFI_SUCCESS;
            return Status; //Command Passed so return to caller
        }

        //Wait for 100 msec
        StallPpi->Stall( PeiServices, StallPpi, 100 * 1000 );
    }
    return Status;
}


EFI_STATUS BotReadBlocks (
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN UINTN                         DeviceIndex,
    IN EFI_PEI_LBA                   StartLBA,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer )
{
    PEI_BOT_DEVICE *PeiBotDev;
    EFI_STATUS     Status = EFI_SUCCESS;
    UINTN BlockSize;
    UINTN NumberOfBlocks;
    UINT8                *AllocateAddress;
    REQUEST_SENSE_DATA   *SensePtr;
    UINT8         SenseKey, ASC, ASCQ;
    UINT8         RetryCount;
    PEI_STALL_PPI *StallPpi;
    UINT32        Temp1, Temp2, Temp3;

    PeiBotDev = PEI_BOT_DEVICE_FROM_THIS( This );

    Temp1 = (UINT32) StartLBA;

    StartLBA += PeiBotDev->FdEmulOffset;

    //
    // Check parameters
    //
    if (Buffer == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    if (BufferSize == 0)
    {
        return EFI_SUCCESS;
    }

    BlockSize = PeiBotDev->Media.BlockSize;

    if (BufferSize % BlockSize != 0)
    {
        Status = EFI_BAD_BUFFER_SIZE;
    }

    if (!PeiBotDev->Media.MediaPresent)
    {
        return EFI_NO_MEDIA;
    }

    if (StartLBA > PeiBotDev->Media.LastBlock)
    {
        Status = EFI_INVALID_PARAMETER;
    }

    NumberOfBlocks = BufferSize / (PeiBotDev->Media.BlockSize);

    for (RetryCount = 0; RetryCount < 3; RetryCount++)
    {
        Status = PeiUsbRead10(
            PeiServices,
            PeiBotDev,
            Buffer,
            StartLBA,
            NumberOfBlocks
                 );
        if ( EFI_ERROR( Status ) )
        {

            if (RetryCount == 0)
            {
				if (PeiBotDev->SensePtr == NULL) {
	                Status = (**PeiServices).AllocatePool(
	                    PeiServices,
	                    sizeof(REQUEST_SENSE_DATA),
	                    &AllocateAddress
	                         );
	                if ( EFI_ERROR( Status ) )
	                {
	                    return Status;
	                }
					PeiBotDev->SensePtr = (REQUEST_SENSE_DATA *) AllocateAddress;
				}
                SensePtr = PeiBotDev->SensePtr;
                (**PeiServices).SetMem((VOID*)SensePtr, sizeof(REQUEST_SENSE_DATA), 0);
                Status = (**PeiServices).LocatePpi( PeiServices,
                    &gPeiStallPpiGuid, 0, NULL, &StallPpi );
            }

            Status = PeiUsbRequestSense(
                PeiServices,
                PeiBotDev,
                (UINT8 *) SensePtr
                     );
            if ( EFI_ERROR( Status ) )
            {
                //If RequestSense also fails, then there is an serious error
                //Return to the caller with appropriate error code
                return EFI_DEVICE_ERROR;
            }
            //TODO:Parse the sense buffer for the error
            //If media getting ready, then wait for few mSec, then
            //retry ReadCapacity
            //For all other errors, return with error condition

            SenseKey = SensePtr->sense_key;
            ASC = SensePtr->addnl_sense_code;
            ASCQ = SensePtr->addnl_sense_code_qualifier;
            Temp1 = SenseKey;
            Temp2 = ASC;
            Temp3 = ASCQ;
            StallPpi->Stall( PeiServices, StallPpi, 9000 );

        }
        break; //break the for loop
    }
    return EFI_SUCCESS;

}


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