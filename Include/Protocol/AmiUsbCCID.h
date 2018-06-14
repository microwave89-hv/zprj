//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

//****************************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/AmiUsbCCID.h 3     5/02/12 2:02a Rajeshms $
//
// $Revision: 3 $
//
// $Date: 5/02/12 2:02a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/AmiUsbCCID.h $
// 
// 3     5/02/12 2:02a Rajeshms
// [TAG]  		EIP83117
// [Category]  	Improvement
// [Description]  	Extend the Support to different smart card Readers and
// smart Cards.
// [Files]  		usbCCID.c, amiusbrtCCID.h, usbdef.h, efiusbccid.c,
// AmiusbCCID.h
// 
// 2     10/14/11 4:58a Rajeshms
// [TAG]  		EIP70315
// [Category]  	Improvement
// [Description]  	Remove Slot number in the USB CCID API's
// [Files]  		efiusbccid.c, AmiUsbCCID.h
// 
// 1     7/12/11 8:19a Ryanchou
// [TAG]  		EIP56918
// [Category]  	New Feature
// [Description]  	Added CCID device support.
// [Files]  		amiusb.c, amiusb.h, amiusbrtCCID.h, ehci.c, ohci.c, uhci.c,
// usb.c, UsbCCID.c, usbdef.h, usbrt.cif, usbsetup.c, efiusbccid.c,
// framework.cif, uhcd.c, uhcd.cif, uhcd.h, usbsrc.sdl, AmiusbCCID.h,
// AmiUsbController.h, AmiUSBProtocols.cif
// 
//****************************************************************************

//<AMI_FHDR_START>
//-----------------------------------------------------------------------------
//
//  Name:           AmiUsbCCID.h
//
//  Description:    AMI USB CCID Protocol definition
//
//-----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _USB_CCID_H
#define _USB_CCID_H

#include <EFI.h>

#ifndef GUID_VARIABLE_DEFINITION

// CCID definitions/Structures
typedef struct _AMI_CCID_IO_PROTOCOL AMI_CCID_IO_PROTOCOL;

#define AMI_CCID_IO_PROTOCOL_GUID \
  { 0xB167C2F5, 0xE26A, 0x4DFF, 0x8E, 0x1C, 0x08, 0x07, 0xC7, 0xF0, 0x2A, 0x88}

#define AMI_CCID_PRESENCE_GUID \
  { 0x5FDEE00D, 0xDA40, 0x405A, 0xB9, 0x2E, 0xCF, 0x4A, 0x80, 0xEA, 0x8F, 0x76}

typedef enum {
  I_BLOCK,
  S_IFS_REQUEST = 0xC1,
  S_ABORT_REQUEST,
  S_WTX_REQUEST    
} ISBlock;

typedef
EFI_STATUS
(*AMI_CCID_SMARTCLASSDESCRIPTOR) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *ResponseBuffer
);

typedef
EFI_STATUS
(*AMI_CCID_GET_ATR) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINT8                            Slot,
    OUT UINT8                           *ATRData
);

typedef
EFI_STATUS
(*AMI_CCID_POWERUP_SLOT) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError,
    OUT UINT8                           *ATRData
);

typedef
EFI_STATUS
(*AMI_CCID_POWERDOWN_SLOT) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError
);

typedef
EFI_STATUS
(*AMI_CCID_GET_SLOT_STATUS) (
    IN AMI_CCID_IO_PROTOCOL              *This,
    OUT UINT8                            *bStatus,
    OUT UINT8                            *bError,
    OUT UINT8                            *bClockStatus
);

typedef
EFI_STATUS
(*AMI_CCID_XFR_BLOCK) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINTN                            CmdLength,
    IN UINT8                            *CmdBuffer,
    IN UINT8                            ISBlock,
    OUT UINT8                           *bStatus,
    OUT UINT8                           *bError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
);

typedef
EFI_STATUS
(*AMI_CCID_GET_PARAMETERS) (
    IN AMI_CCID_IO_PROTOCOL              *This,
    OUT UINT8                            *bStatus,
    OUT UINT8                            *bError,
    OUT UINTN                            *ResponseLength,
    OUT UINT8                            *ResponseBuffer
);

typedef struct _AMI_CCID_IO_PROTOCOL {

    AMI_CCID_SMARTCLASSDESCRIPTOR       USBCCIDAPISmartClassDescriptor;
    AMI_CCID_GET_ATR                    USBCCIDAPIGetAtr;
    AMI_CCID_POWERUP_SLOT               USBCCIDAPIPowerupSlot;    
    AMI_CCID_POWERDOWN_SLOT             USBCCIDAPIPowerDownSlot;    
    AMI_CCID_GET_SLOT_STATUS            USBCCIDAPIGetSlotStatus;
    AMI_CCID_XFR_BLOCK                  USBCCIDAPIXfrBlock;
    AMI_CCID_GET_PARAMETERS             USBCCIDAPIGetParameters;    
        
}AMI_CCID_IO_PROTOCOL;

typedef struct {
    AMI_CCID_IO_PROTOCOL        CCIDIoProtocol;
    VOID                        *DevInfo;
    UINT8                       Slot;
    EFI_HANDLE                  ControllerHandle;
    EFI_HANDLE                  ChildHandle;

} USB_ICC_DEV;

#endif
#endif // _USB_CCID_H

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2011, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
