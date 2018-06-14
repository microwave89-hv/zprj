//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbInt13.h 13    12/24/14 1:13a Wilsonlee $
//
// $Revision: 13 $
//
// $Date: 12/24/14 1:13a $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbInt13.h $
// 
// 13    12/24/14 1:13a Wilsonlee
// [TAG]  		EIP192517
// [Category]  	Improvement
// [Description]  	USB Driver handles 0x100 NumHeads as a valid value.
// [Files]  		usbmass.c, usbdef.h, UsbInt13.c, UsbInt13.h, UI13.bin,
// Bfiusb.equ, Bfiusb.asm
// 
// 12    12/15/13 10:13p Wilsonlee
// [TAG]  		EIP136594
// [Category]  	New Feature
// [Description]  	Support 64 bits LBA of usb mass storages.
// [Files]  		Bfiusb.asm, Bfiusb.equ, UsbInt13.c, UsbInt13.h, amiusb.c,
// usbdef.h, usbmass.c, UsbMass.h, efiusbmass.c, UI13.bin
// 
// 11    7/23/13 2:11a Wilsonlee
// [TAG]  		EIP127941
// [Category]  	Improvement
// [Description]  	Replace UI13HDDFunc08 with UI13FDDFunc08 if the media
// descriptor is a fixed disk.
// [Files]  		UsbInt13.h, UsbInt13.c, usbmass.c, usbdef.h, Bfiusb.asm,
// Bfiusb.equ
// 
// 10    7/03/13 5:21a Ryanchou
// [TAG]  		EIP123988
// [Category]  	Improvement
// [Description]  	Move the code creating BBS table to end of POST.
// [Files]  		UsbBbs.c, UsbInt13.c, UsbInt13.cif, UsbInt13.h,
// UsbInt13.mak, UsbInt13.sdl, efiusbmass.c, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 9     1/06/12 1:01a Rajeshms
// [TAG]  		EIP62737
// [Category]  	Improvement
// [Description]  	Added USB Device number into USB mass device name
// string based on SDL Token.
// [Files]  		Usb.sdl, usbport.c, usbmass.c, UsbInt13.h, UsbInt13.c,
// usbbus.c, Bfiusb.equ
// 
// 8     3/04/11 11:42a Olegi
// [TAG]  		EIP51927
// [Category]  	Improvement
// [Description]  	Support for the interface path reporting in USB INT13
// function 48.
// [Files]  		UsbInt13.c
// UsbInt13.h
// 
// 7     10/12/10 2:07a Rameshr
// [TAG]- EIP 44585
// [Category]-IMPROVEMENT
// [Description]- Number of maximum supported USB Mass Storage device
// increased from 8 to 16. 
// [Files]- Uin13.bin, UsbPort.c, UsbInt13.h, Usb.c, Usbdef.h, Uasbmass.c,
// Usb.sd, usb.uni, UsbSetup.c, UsbSrc.sdl, UsbPolicy.h
// 
// 6     5/21/09 5:14p Olegi
// 
// 5     11/25/08 5:59p Olegi
// 
// 4     11/03/08 9:53a Olegi
// 
// 3     10/24/08 3:06p Olegi
// 
// 2     6/27/08 5:50p Olegi
// 
// 1     5/16/08 12:12p Olegi
// First check-in.
// 
//****************************************************************************

#ifndef __UI13_HEADER__
#define __UI13_HEADER__

#include "efi.h"

#pragma pack(1)

//<AMI_FHDR_START>
//---------------------------------------------------------------------------
//
//  Name:           UINT13.H
//  Description:    Definitions and structures for USB INT13
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>

VOID        AmiUsbNotifyCallback (EFI_EVENT, VOID*);
VOID        ReadyToBootNotify(EFI_EVENT, VOID*);
EFI_STATUS  InstallUsbLegacyBootDevices (VOID);
EFI_STATUS  UsbInstallLegacyDevice (USB_MASS_DEV*);
EFI_STATUS  UsbUninstallLegacyDevice (USB_MASS_DEV*);

#define     USBDEVS_MAX_ENTRIES 16

typedef struct _USBMASS_INT13_DEV {
    UINT8   Handle;
    UINT8   BbsEntryNo;
    UINT8   DevBaidType;
    UINT16  NumHeads;
    UINT16  LBANumHeads;
    UINT16  NumCylinders;
    UINT16  LBANumCyls;
    UINT8   NumSectors;
    UINT8   LBANumSectors;
    UINT16  BytesPerSector;
    UINT8   MediaType;
    UINT64  LastLBA;
    UINT8   BpbMediaDesc;
    UINT8   DeviceNameString[64];
} USBMASS_INT13_DEV;

//
// The following data structure is located in UI13.BIN
//
typedef struct _UINT13_DATA {
    USBMASS_INT13_DEV   UsbMassI13Dev[USBDEVS_MAX_ENTRIES];
    UINT8               MfgGenericName[12];    // "USB Storage", 0
    UINT16              BcvOffset;
    UINT16              CheckForUsbCDROMOffset;
    UINT16              UsbSmmDataOffset;
    UINT16              UsbPciLocationTableOffset;
} UINT13_DATA;

typedef struct _USB_PCI_LOCATION {
    UINT8   Handle;         // USB device address
    UINT16  PciLocation;    // Bus[15..8] Device[7..3] Function[2..0]
} USB_PCI_LOCATION;

#pragma pack()

typedef enum {
    Floppy,
    HardDrive,
    CDROM
} HOTPLUG_DEVICE;

EFI_STATUS InitializeHotplugDevices();

#endif

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2008, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
