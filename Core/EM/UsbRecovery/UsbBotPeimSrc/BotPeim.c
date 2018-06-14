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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbBotPeimSrc/BotPeim.c 7     11/24/12 5:47a Ryanchou $
//
// $Revision: 7 $
//
// $Date: 11/24/12 5:47a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbBotPeimSrc/BotPeim.c $
// 
// 7     11/24/12 5:47a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 6     4/16/11 3:41a Ryanchou
// [TAG]  		EIP50311
// [Category]  	New Feature
// [Description]  	Multiple LUN device support added.
// [Files]  		BotPeim.c, UsbBotPeim.c, UsbBotPeim.h
// 
// 5     2/18/11 2:13a Ryanchou
// [TAG]  		EIP52191
// [Category]  	Bug Fix
// [Severity]  	Minor
// [Symptom]  	Recovery from card reader causes "EHCI Time-Out".
// [RootCause]  	The card reader returns zero length during BOT data
// transport, BIOS will do data transport again if the remain data length
// isn't zero, then CSW will be received in data transport phase.
// [Solution]  	Added the code that check if the transfered length is less
// than expect length, break the loop.
// [Files]  		BotPeim.c
// 
// 4     4/06/10 3:27p Fasihm
// EIP#31987 - Added the generic USBRecovery Fix in the module.
// 
// 3     7/10/08 6:38p Michaela
// Updated to support OHCI controllers
//
// 2     8/17/07 4:12p Ambikas
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
// Name:        BotPeim.C
//
// Description: This file belongs to "Framework".
//              This file is modified by AMI to include copyright message,
//              appropriate header and integration code.
//              This file contains generic routines needed for USB recovery
//              Mass Storage BOT PEIM
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

   BotPeim.c

   Abstract:

   BOT Transportation implementation

   --*/

#include "UsbBotPeim.h"
#include "BotPeim.h"
#include "PeiUsbLib.h"

extern VOID ZeroMem (
    IN VOID  *Buffer,
    IN UINTN Size );
extern VOID PeiCopyMem (
    IN VOID  *Destination,
    IN VOID  *Source,
    IN UINTN Length );


STATIC
EFI_STATUS BotRecoveryReset (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;
    PEI_USB_IO_PPI         *UsbIoPpi;
    UINT8      EndpointAddr;
    EFI_STATUS Status;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    if (UsbIoPpi == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );

    DevReq.RequestType = 0x21;
    DevReq.Request = 0xff;
    DevReq.Value = 0;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;

    Status = UsbIoPpi->UsbControlTransfer(
        PeiServices,
        UsbIoPpi,
        &DevReq,
        EfiUsbNoData,
        Timeout,
        NULL,
        0
             );

    //
    // clear bulk in endpoint stall feature
    //
    EndpointAddr = (PeiBotDev->BulkInEndpoint)->EndpointAddress;
    PeiUsbClearEndpointHalt( PeiServices, UsbIoPpi, EndpointAddr );

    //
    // clear bulk out endpoint stall feature
    //
    EndpointAddr = (PeiBotDev->BulkOutEndpoint)->EndpointAddress;
    PeiUsbClearEndpointHalt( PeiServices, UsbIoPpi, EndpointAddr );

    return Status;
}


STATIC
EFI_STATUS BotCommandPhase (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_BOT_DEVICE         *PeiBotDev,
    IN VOID                   *Command,
    IN UINT8                  CommandSize,
    IN UINT32                 DataTransferLength,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT16                 Timeout )
{
    CBW            cbw;
    EFI_STATUS     Status;
    PEI_USB_IO_PPI *UsbIoPpi;
    UINTN          DataSize;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    ZeroMem( &cbw, sizeof(CBW) );

    //
    // Fill the command block, detailed see BOT spec
    //
    cbw.dCBWSignature = CBWSIG;
    cbw.dCBWTag = 0x01;
    cbw.dCBWDataTransferLength = DataTransferLength;
    cbw.bmCBWFlags = (Direction == EfiUsbDataIn)? 0x80 : 0;
    cbw.bCBWLUN = PeiBotDev->Lun;
    cbw.bCBWCBLength = CommandSize;

    PeiCopyMem( cbw.CBWCB, Command, CommandSize );

    DataSize = sizeof(CBW);

    Status = UsbIoPpi->UsbBulkTransfer(
        PeiServices,
        UsbIoPpi,
        (PeiBotDev->BulkOutEndpoint)->EndpointAddress,
        (UINT8 *) &cbw,
        &DataSize,
        Timeout
             );
    if ( EFI_ERROR( Status ) ) {
        //
        // Command phase fail, we need to recovery reset this device
        //
        BotRecoveryReset( PeiServices, PeiBotDev );
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}


STATIC
EFI_STATUS BotDataPhase (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_BOT_DEVICE         *PeiBotDev,
    IN UINT32                 *DataSize,
    IN OUT VOID               *DataBuffer,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT16                 Timeout )
{
    EFI_STATUS     Status;
    PEI_USB_IO_PPI *UsbIoPpi;
    UINT8  EndpointAddr;
    UINTN  Remain;
    UINTN  Increment;
    UINT32 MaxPacketLen;
    UINT8  *BufferPtr;
    UINTN  TransferredSize;
	UINTN  TransferSize;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    Remain = *DataSize;
    BufferPtr = (UINT8 *) DataBuffer;
    TransferredSize = 0;

    //
    // retrieve the the max packet length of the given endpoint
    //
    if (Direction == EfiUsbDataIn) {
        MaxPacketLen = (PeiBotDev->BulkInEndpoint)->MaxPacketSize;
        EndpointAddr = (PeiBotDev->BulkInEndpoint)->EndpointAddress;
    }
    else {
        MaxPacketLen = (PeiBotDev->BulkOutEndpoint)->MaxPacketSize;
        EndpointAddr = (PeiBotDev->BulkOutEndpoint)->EndpointAddress;
    }

    while (Remain > 0) {
        //
        // Using 15 packets to avoid Bitstuff error
        //
        if (Remain > 16 * MaxPacketLen) {
            TransferSize = 16 * MaxPacketLen;
        }
        else {
            TransferSize = Remain;
        }

		Increment = TransferSize;
	
        Status = UsbIoPpi->UsbBulkTransfer(
            PeiServices,
            UsbIoPpi,
            EndpointAddr,
            BufferPtr,
            &Increment,
            Timeout
                 );

        TransferredSize += Increment;

        if ( EFI_ERROR( Status ) ) {
            PeiUsbClearEndpointHalt( PeiServices, UsbIoPpi, EndpointAddr );
            return Status;
        }
	
		if (Increment < TransferSize) {
			break;
		}
		
        BufferPtr += Increment;
        Remain -= Increment;
    }

    *DataSize = (UINT32) TransferredSize;

    return EFI_SUCCESS;
}


STATIC
EFI_STATUS BotStatusPhase (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev,
    OUT UINT8           *TransferStatus,
    IN UINT16           Timeout )
{
    CSW            csw;
    EFI_STATUS     Status;
    PEI_USB_IO_PPI *UsbIoPpi;
    UINT8          EndpointAddr;
    UINTN          DataSize;

    //UINT32 Temp;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    ZeroMem( &csw, sizeof(CSW) );

    EndpointAddr = (PeiBotDev->BulkInEndpoint)->EndpointAddress;

    //  DataSize = sizeof(CSW);
    DataSize = 0x0d; //bala changed

    //
    // Get the status field from bulk transfer
    //
    Status = UsbIoPpi->UsbBulkTransfer(
        PeiServices,
        UsbIoPpi,
        EndpointAddr,
        &csw,
        &DataSize,
        Timeout
             );

    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    if (csw.dCSWSignature == CSWSIG)
    {
        *TransferStatus = csw.bCSWStatus;
    }
    else {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}


EFI_STATUS PeiAtapiCommand (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_BOT_DEVICE         *PeiBotDev,
    IN VOID                   *Command,
    IN UINT8                  CommandSize,
    IN VOID                   *DataBuffer,
    IN UINT32                 BufferLength,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT16                 TimeOutInMilliSeconds )

/*++

   Routine Description:
    Send ATAPI command using BOT protocol.

   Arguments:
    This                  - Protocol instance pointer.
    Command               - Command buffer
    CommandSize           - Size of Command Buffer
    DataBuffer            - Data buffer
    BufferLength          - Length of Data buffer
    Direction             - Data direction of this command
    TimeoutInMilliseconds - Timeout value in ms

   Returns:
    EFI_SUCCES          - Commond succeeded.
    EFI_DEVICE_ERROR    - Command failed.

   --*/
{
    EFI_STATUS Status;
    EFI_STATUS BotDataStatus = EFI_SUCCESS;
    UINT8      TransferStatus;
    UINT32     BufferSize;
    UINT8      *Tmp;
    UINT32     Temp;

    Tmp = (UINT8 *) Command;
    Temp = Tmp[0];
    PEI_TRACE( (EFI_D_ERROR, PeiServices, "Executing ScsiCmd(%x)\n", Temp) );
    //
    // First send ATAPI command through Bot
    //
    Status = BotCommandPhase(
        PeiServices,
        PeiBotDev,
        Command,
        CommandSize,
        BufferLength,
        Direction,
        TimeOutInMilliSeconds
             );

    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }

    //
    // Send/Get Data if there is a Data Stage
    //
    switch (Direction)
    {
    case EfiUsbDataIn:
    case EfiUsbDataOut:
        BufferSize = BufferLength;

        BotDataStatus = BotDataPhase(
            PeiServices,
            PeiBotDev,
            &BufferSize,
            DataBuffer,
            Direction,
            TimeOutInMilliSeconds
                        );

        break;

    case EfiUsbNoData:
        break;
    }

    //
    // Status Phase
    //

    Status = BotStatusPhase(
        PeiServices,
        PeiBotDev,
        &TransferStatus,
        TimeOutInMilliSeconds
             );
    if ( EFI_ERROR( Status ) ) {
        BotRecoveryReset( PeiServices, PeiBotDev );
        return EFI_DEVICE_ERROR;
    }

    if (TransferStatus == 0x01) {
        return EFI_DEVICE_ERROR;
    }

    return BotDataStatus;
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