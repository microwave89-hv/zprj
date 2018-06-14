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
// $Header: /Alaska/SOURCE/Modules/USBRecovery/UsbBotPeimSrc/BotPeim.h 5     11/24/12 5:47a Ryanchou $
//
// $Revision: 5 $
//
// $Date: 11/24/12 5:47a $
//
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USBRecovery/UsbBotPeimSrc/BotPeim.h $
// 
// 5     11/24/12 5:47a Ryanchou
// [TAG]  		EIP103990
// [Category]  	Improvement
// [Description]  	Synchronized with USB PEI module 4.6.3_USB_08.10.24.
// [Files]  		EhciPei.c, EhciPei.h, OhciPei.c, OhciPei.h, UhcPeim.c,
// BotPeim.c, BotPeim.h, PeiAtapi.c, UsbBotPeim.c, UsbBotPeim.h,
// HubPeim.c, UsbPeim.c, XhciPei.c, XhciPei.h, HubPeim.h, PeiUsbLib.c,
// PeiUsbLib.h, UsbPeim.h
// 
// 4     7/10/08 6:38p Michaela
// Updated to support OHCI controllers
//
// 3     4/16/07 12:46p Sivagarn
// - Updated as per coding standard review
// - In previous check-in, TIANO.H file is removed and AMIMAPPING.H file
// is included
//
// 2     3/28/07 3:40a Meenakshim
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
// Name:        BotPeim.h
//
// Description: This file belongs to "Framework".
//              This file is modified by AMI to include copyright message,
//              appropriate header and integration code.
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
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

   BotPeim.h

   Abstract:

   BOT Transportation implementation

   --*/

#ifndef _PEI_BOT_PEIM_H
#define _PEI_BOT_PEIM_H

#define STATIC  static

#include "Atapi.h"
#include "AmiPeiLib.h"

#pragma pack(1)

//
//Bulk Only device protocol
//
typedef struct
{
    UINT32 dCBWSignature;
    UINT32 dCBWTag;
    UINT32 dCBWDataTransferLength;
    UINT8  bmCBWFlags;
    UINT8  bCBWLUN;
    UINT8  bCBWCBLength;
    UINT8  CBWCB[16];
} CBW;

typedef struct
{
    UINT32 dCSWSignature;
    UINT32 dCSWTag;
    UINT32 dCSWDataResidue;
    UINT8  bCSWStatus;
    UINT8  Filler[18];
} CSW;

#pragma pack()

//
// Status code, see Usb Bot device spec
//
#define CSWSIG  0x53425355
#define CBWSIG  0x43425355

EFI_STATUS
PeiUsbInquiry (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbTestUnitReady (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbRequestSense (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice,
    IN UINT8            *SenseKeyBuffer );

EFI_STATUS
PeiUsbReadCapacity (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbReadFormattedCapacity (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice );

EFI_STATUS
PeiUsbRead10 (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDevice,
    IN VOID             *Buffer,
    IN EFI_PEI_LBA      Lba,
    IN UINTN            NumberOfBlocks );

BOOLEAN
IsNoMedia (
    IN REQUEST_SENSE_DATA *SenseData,
    IN UINTN              SenseCounts );

BOOLEAN
IsMediaError (
    IN REQUEST_SENSE_DATA *SenseData,
    IN UINTN              SenseCounts );

BOOLEAN
IsMediaChange (
    IN REQUEST_SENSE_DATA *SenseData,
    IN UINTN              SenseCounts );

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