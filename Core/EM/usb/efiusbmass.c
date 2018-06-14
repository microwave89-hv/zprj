//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
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
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbmass.c 65    10/20/16 11:20p Wilsonlee $
//
// $Revision: 65 $
//
// $Date: 10/20/16 11:20p $
//
//****************************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/efiusbmass.c $
// 
// 65    10/20/16 11:20p Wilsonlee
// [TAG]  		EIP297268
// [Category]  	Improvement
// [Description]  	Update Media information only in EfiUsbMass driver when
// Media is changed.
// [Files]  		usbmass.c, efiusbmass.c
// 
// 64    10/16/16 10:18p Wilsonlee
// [TAG]  		EIP288158
// [Category]  	Improvement
// [Description]  	Check if gUsbData is integrity.
// [Files]  		amiusb.cif, usbsb.c, AmiUsbLib.cif, AmiUsbLib.sdl,
// AmiUsbSmmGlobalDataValidationLib.c,
// AmiUsbSmmGlobalDataValidationLib.cif,
// AmiUsbSmmGlobalDataValidationLib.mak, Crc32.c, amiusb.c, amiusb.h,
// ehci.c, elib.c, ohci.c, syskbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h,
// usbhid.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c, usbrt.mak, xhci.c,
// amiusbhc.c, efiusbccid.c, efiusbmass.c, uhcd.c, usbmisc.c,
// AmiUsbController.h, AmiUsbLibInclude.cif,
// AmiUsbSmmGlobalDataValidationLib.h
// 
// 63    7/07/16 1:12a Wilsonlee
// [TAG]  		EIP277810
// [Category]  	Improvement
// [Description]  	Validate the memory buffer is entirely outside of SMM.
// [Files]  		usbsb.c, amiusb.c, ehci.c, ohci.c, uhci.c, usbCCID.c,
// usbdef.h, usbmass.c, xhci.c, amiusbhc.c, efiusbccid.c, efiusbmass.c,
// uhcd.c, uhcd.h, usbmisc.c
// 
// 62    5/28/15 5:01a Wilsonlee
// [TAG]  		EIP218997
// [Category]  	Improvement
// [Description]  	Break the GetQueue loop if UninstallDevice is failed.
// [Files]  		usbbus.c, efiusbkb.c, efiusbmass.c, efiusbms.c,
// efiusbpoint.c, efiusbhid.c
// 
// 61    5/27/15 2:15a Wilsonlee
// [TAG]  		EIP220162
// [Category]  	Improvement
// [Description]  	The read / write request contain the latest LBA that
// are valid.
// [Files]  		usbmass.c, efiusbmass.c
// 
// 60    5/13/15 2:46a Wilsonlee
// [TAG]  		EIP216587
// [Category]  	Improvement
// [Description]  	Add 64-bit addressing buffer support for usb transfers.
// [Files]  		amiusbhc.c, efiusbmass.c
// 
// 59    4/29/15 11:28p Wilsonlee
// [TAG]  		EIP215031
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	Transcend USB 3.0 HDD is disappeared in the setup menu by
// cold boot.
// [RootCause]  	We only can get SerialNumber string descriptor before
// setting configuration for this device, otherwise it is failed at
// getting this descriptor and inquiry command is also failed.
// [Solution]  	Retry inquiry command.
// [Files]  		usb.c, usbmass.c, efiusbmass.c, usbbus.c, usbdef.h
// 
// 58    9/30/14 2:04a Wilsonlee
// [TAG]  		EIP183572
// [Category]  	Improvement
// [Description]  	Change tpl of UsbHcOnTimer to EFI_TPL_CALLBACK
// [Files]  		efiusbmass.c, usbbus.c
// 
// 57    9/30/14 1:30a Wilsonlee
// [TAG]  		EIP186438
// [Category]  	Improvement
// [Description]  	We should close UsbIoProtocol if it has any error in
// InstallUsbMass.
// [Files]  		efiusbmass.c
// 
// 56    8/20/14 5:25a Wilsonlee
// [TAG]  		EIP182011
// [Category]  	Improvement
// [Description]  	We don't need to update NVRAM variables in
// InstallUsbMass and UninstallUSBMass functions.
// [Files]  		efiusbmass.c, usbsetup.c
// 
// 55    7/18/14 11:39p Wilsonlee
// [TAG]  		EIP174022
// [Category]  	Improvement
// [Description]  	Check if the mass storage device is present before
// installing BlkIo protocol.
// [Files]  		xhci.c, efiusbmass.c
// 
// 54    4/30/14 5:27a Wilsonlee
// [TAG]  		EIP164842
// [Category]  	Improvement
// [Description]  	Check if the devices have put into to our queue before
// we put them.
// [Files]  		UsbInt13.c, amiusb.c, ehci.c, ohci.c, usb.c, usbdef.h,
// usbmass.c, xhci.c, amiusbhc.c, efiusbmass.c, uhcd.c, usbbus.c, usbsb.c
// 
// 53    4/07/14 2:08a Wilsonlee
// [TAG]  		EIP156126
// [Category]  	Bug Fix
// [Severity]  	Important
// [Symptom]  	The power Format of UEFI can not be identified when we
// install OS from USB CD-ROM.
// [RootCause]  	The media information is incorrect when we install
// BlockIoProtocol for usb CD / DVD devices.
// [Solution]  	Get the media status before we install BlockIoProtocol.
// [Files]  		usbmass.c, usbdef.h, efiusbmass.c
// 
// 52    12/24/13 3:21a Wilsonlee
// [TAG]  		EIP148177
// [Category]  	Improvement
// [Description]  	change from EFI_MBR_WRITE_PROTECTION_PROTOCOL to
// AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL
// [Files]  		efiusbmass.c
// 
// 51    12/18/13 3:59a Wilsonlee
// [TAG]  		EIP147574
// [Category]  	Improvement
// [Description]  	MbrWriteProtectionProtocol file name changesd to
// AmiMbrWriteProtectionProtocol.h
// [Files]  		efiusbmass.c
// 
// 50    12/15/13 10:17p Wilsonlee
// [TAG]  		EIP136594
// [Category]  	New Feature
// [Description]  	Support 64 bits LBA of usb mass storages.
// [Files]  		Bfiusb.asm, Bfiusb.equ, UsbInt13.c, UsbInt13.h, amiusb.c,
// usbdef.h, usbmass.c, UsbMass.h, efiusbmass.c, UI13.bin
// 
// 49    8/16/13 4:18a Ryanchou
// 
// 48    7/29/13 5:29a Roberthsu
// [TAG]           EIP126741
// [Category]      Bug Fix
// [Severity]      Normal
// [Symptom]       Cannot boot to uefi usb device with Sophos software.
// [RootCause]     When boot into tool. Ownership to os event occur.Usb
// will disconnect device.And record this disconnect event. Then ownership
// to bios,bios will connect all device.Run legacy to efi function. Bios
// run disconnect event first.Then reconnect device.Because usb key behind
// hub. So usb key disconnect also.
// [Solution]      Check device when device reconnect.If device and port
// number the same.Use the same device info.
// [Files]         usb.c,usbmass.c,efiusbmass.c,uhcd.c
// 
// 47    7/03/13 5:23a Ryanchou
// [TAG]  		EIP123988
// [Category]  	Improvement
// [Description]  	Move the code creating BBS table to end of POST.
// [Files]  		UsbBbs.c, UsbInt13.c, UsbInt13.cif, UsbInt13.h,
// UsbInt13.mak, UsbInt13.sdl, efiusbmass.c, uhcd.c, uhcd.h,
// AmiUsbController.h
// 
// 46    7/03/13 4:49a Ryanchou
// [TAG]  		EIP127800
// [Category]  	Improvement
// [Description]  	Add non-bootable device type handing
// [Files]  		usbmass.c, efiusbmass.c
// 
// 45    7/01/13 5:45a Kapilporwal
// [TAG]  		EIP125560
// [Category]  	Improvement
// [Description]  	 	Please support Boot Sector Virus Protection for CSM
// Disabled Mode
// [Files]  		VirusProtect.c, VirusProtect.dxs, AhciBus.c,
// AhciController.c, CsmBlockIo.c, CsmInt13.c, Ata.c, IdeBus.c,
// SdioBlkIo.c, SdioDriver.c, efiusbmass.c
// 
// 44    3/19/13 4:00a Ryanchou
// [TAG]  		EIP118177
// [Category]  	Improvement
// [Description]  	Dynamically allocate HCStrucTable at runtime.
// [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
// syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
// usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
// efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
// usbmisc.c, usbsrc.sdl
// 
// 43    1/22/13 3:11a Wilsonlee
// [TAG]  		EIP112938
// [Category]  	Improvement
// [Description]  	Create a header file for usb mass storage driver.
// [Files]  		UsbMass.h, usbmass.c, usbdef.h, amiusb.c, efiusbmass.c
// 
// 42    1/22/13 2:40a Wilsonlee
// [TAG]  		EIP110305
// [Category]  	Improvement
// [Description]  	Set the device address after we send the first
// get-device-descriptor command.
// [Files]  		usbmass.c, usb.c, usbdef.h, usbbus.c, efiusbmass.c, uhcd.c,
// usbport.c
// 
// 41    1/11/13 4:19a Ryanchou
// [TAG]  		EIP102491
// [Category]  	Improvement
// [Description]  	Synchronized with Aptio V USB module
// [Files]  		usbport.c, usbsb.c, ehci.c, ehci.h, ohci.c, ohci.h, uhci.h,
// usb.c, usbdef.h, usbhid.c, usbhub.c, usbkbd.c, usbkbd.h, usbmass.c.
// usbms.c, usbpoint.c, xhci.h, usb.sd, amiusbhc.c, componentname.c,
// efiusbkc.c, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h, usbmisc.c
// 
// 40    9/04/12 8:04a Wilsonlee
// [TAG]  		EIP99882
// [Category]  	New Feature
// [Description]  	Add the usb setup item and usbpolicyprotocol to enable
// or disable the usb mass storage driver.
// [Files]  		UsbPolicy.h, usb.uni, usb.sd, usbmass.c, usbdef.h,
// efiusbmass.c, usbport.c, uhcd.c
// 
// 39    8/29/12 8:36a Ryanchou
// [TAG]  		EIP77262
// [Category]  	New Feature
// [Description]  	Remove SMM dependency of USB.
// [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
// elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
// efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
// uhcd.h, usbmisc.c, AmiUsbController.h
// 
// 38    5/04/12 5:30a Wilsonlee
// [TAG]  		EIP89307
// [Category]  	Improvement
// [Description]  	Modify incorrect #pragma pack directive.
// [Files]  		amidef.h, amiusb.c, ehci.h, ohci.c, ohci.h, uhci.h, usb.c,
// usbdef.h, xhci.h, efiusbmass.c, uhcd.c, uhcd.h, usbbus.c, usbbus.h,
// UsbIo.h
// 
// 37    1/10/12 5:47a Deepthins
// [TAG]  		EIP73939
// [Category]  	Improvement
// [Description]  	For USB BlockIo driver , AmiUsbBlkIoReadWrite function
// should return EFI_ EFI_MEDIA_CHANGED if media id does not match and if
// alignment is not proper then it should return EFI_INVALID_PARAMETER.
// [Files]  		efiusbmass.c
// 
// 36    11/05/11 3:39a Ryanchou
// [TAG]  		EIP71108
// [Category]  	Bug Fix
// [Severity]  	Normal
// [Symptom]  	The token of "REMOVE_USB_STORAGE_FROM_BBS_IF_NO_MEDIA¡§
// can't work normal
// [RootCause]  	While a SD card is not plugged into the card reader, its
// wBlockSize is actually 0xFFFF, which this
// gAmiUsbController->UsbInstallLegacyDevice(MassDev) is not being
// executed, that is why whatever values the token
// REMOVE_USB_STORAGE_FROM_BBS_IF_NO_MEDIA are, the card reader won't be
// seen from the "boot option" in the SETUP.
// [Solution]  	Add one condition in the function InstallUSBMass.
// [Files]  		efiusbmass.c
// 
// 35    6/22/11 1:42a Ryanchou
// [TAG]  		EIP59738
// [Category]  	Improvement
// [Description]  	Support Block size other than 512 bytes USB HDD in UEFI
// mode.
// [Files]  		efiusbmass.c, uhci.c, usb.c, usbdef.h, usbmass.c
// 
// 34    5/27/11 7:39a Rameshr
// [TAG]- EIP 58689
// [Category]-IMPROVEMENT
// [Description]- Update implementation of EFI_BLOCK_IO_PROTOCOL as
// described in UEFI specification v 2.3.1, page 12.8
// [Files]- efiusbmass.c
// 
// 33    5/03/11 10:47a Ryanchou
// [TAG]  		EIP59272
// [Category]  	Improvement
// [Description]  	According Uefi 2.1 Aptio porting document, changes made
// to install the component name protocol.
// [Files]  		componentname.c, componentname.h, efiusbkb.c, efiusbmass.c,
// efiusbms.c, uhcd.c, uhcd.h, usbbus.c
// 
// 32    3/04/11 1:30p Olegi
// 
// 31    3/04/11 1:25p Olegi
// [TAG]  		EIP55172
// [Category]  	Spec Update
// [Severity]  	Important
// [Description]  	Install EFI_COMPONENT_NAME_PROTOCOL if BIOS is in UEFI
// 2.0 mode and EFI_COMPONENT_NAME2_PROTOCOL if BIOS is in UEFI 2.1 mode.
// [Files]  		uhcd.c
// usbbus.c
// efiusbkb.c
// efiusbmass.c
// efiusbms.c
// componentname.c
// componentname.h
// 
// 30    9/07/10 4:41a Tonylo
// Remove user tags for coding standard.
// 
// 29    8/17/10 11:39p Ryanchou
// EIP41547: Fixed system hangs if hot plug USB device during
// initialization.
// 
// 28    6/17/10 10:36a Olegi
// EIP39092: Change the order of protocol installation in InstallUSBMass.
// 
// 27    2/23/10 1:36p Olegi
// Work around Klockwork issues. EIP34370
// 
// 26    8/04/09 11:01a Olegi
// Install legacy mass storage device only when USB legacy support is
// enabled. EIP#24484
// 
// 25    6/16/09 10:40a Olegi
// Fix for EIP#14848: EFI_BLOCK_IO_PROTOCOL.EFI_BLOCK_IO_MEDIA->ReadOnly
// 
// 24    5/21/09 5:16p Olegi
// 
// 23    3/26/09 2:17p Olegi
// All setup related code is moved to OEMPORT.C to maximize the porting
// capabilities.
// 
// 22    2/18/09 3:46p Olegi
// Added a feature that allows to skip mass storage device installation
// depending on physical media presence. EIP#19260.
// 
// 21    12/16/08 10:52a Olegi
// Correction in the return values: 0 changed to NULL. EIP#17767.
// 
// 19    6/27/08 5:58p Olegi
// 
// 18    5/16/08 12:02p Olegi
// Compliance with AMI coding standard.
// 
// 17    4/17/07 10:51a Olegi
// 
// 16    3/20/07 1:29p Olegi
//
// 14    10/12/06 7:12p Andriyn
// Support unexpected plug-off USB device
//
// 13    4/14/06 6:41p Olegi
//
// 12    3/20/06 3:37p Olegi
// Version 8.5 - x64 compatible.
//
// 11    3/16/06 2:34p Olegi
//
// 9     3/06/06 6:27p Olegi
// Lun devices support modifications: supported using the index in
// DEV_INFO table, not through dedicated massLun table.
//
// 8     1/11/06 1:44p Olegi
//
// 7     11/04/05 6:20p Olegi
// Multiple LUN support.
//
// 6     10/20/05 2:45p Olegi
//
// 5     8/23/05 5:55p Olegi
//
// 4     6/03/05 9:33a Olegi
// - Correction in reporting status code from Read/Write routines
// - MediaId manipulation fix
//
// 3     5/19/05 8:06p Olegi
// Aptio changes in driver 8.1 implementation.
//
// 2     5/17/05 7:51p Andriyn
// USB BUS pre-release
//
// 1     3/28/05 6:20p Olegi
//
// 1     3/15/05 9:23a Olegi
// Initial VSS check-in.
//
//****************************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           EFIUSBMASS.C
//
//  Description:    EFI USB Mass Storage Driver
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#include "amidef.h"
#include "usbdef.h"
#include "uhcd.h"
#include "componentname.h"
#include "usbbus.h"
#include "setup.h"
#include "UsbMass.h"

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
#include <Protocol\AmiBlockIoWriteProtection.h>
AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *AmiBlkWriteProtection = NULL;
#endif

#define USBMASS_DRIVER_VERSION 1
#define READ 1
#define WRITE 0

extern  USB_GLOBAL_DATA     *gUsbData;
extern  EFI_USB_PROTOCOL    *gAmiUsbController;


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   InstallUsbMass
//
// Description: Installs BlkIo protocol on a USB Mass Storage device
//
// Input:       DevInfo - pointer to a USB device structure to install the protocol.
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
InstallUsbMass(
    EFI_HANDLE Controller,
    DEV_INFO* DevInfo
)
{
    USB_MASS_DEV    *MassDev;
    EFI_STATUS      Status;
    UINT8           LogicalAddress;
    URP_STRUC       Parameters;

    //Applying check to media not present device only
    if (!(DevInfo->bLastStatus & USB_MASS_MEDIA_PRESENT)) {
        if (gUsbData->dUSBStateFlag & USB_FLAG_MASS_MEDIA_CHECK) {
            if (gUsbData->dUSBStateFlag & USB_FLAG_MASS_SKIP_FDD_MEDIA_CHECK) {
                if (!(DevInfo->bSubClass == SUB_CLASS_UFI)) {
                    return EFI_DEVICE_ERROR;
                }
            } else {
                return EFI_DEVICE_ERROR;
            }
        }
    }

    for (LogicalAddress=1; LogicalAddress < MAX_DEVICES; LogicalAddress++) {
        if (&gUsbData->aDevInfoTable[LogicalAddress] == DevInfo) {
            break;
        }
    }
    ASSERT(LogicalAddress < MAX_DEVICES);
    
    if (LogicalAddress >= MAX_DEVICES) {
        return EFI_DEVICE_ERROR;
    }
    
    Parameters.bFuncNumber = USB_API_MASS_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_MASSAPI_GET_MEDIA_STATUS;
    Parameters.ApiData.MassGetDevSts.bDevAddr = LogicalAddress;
    Parameters.ApiData.MassGetDevSts.bDeviceStatus = 0;
    InvokeUsbApi(&Parameters);

    gBS->AllocatePool(EfiBootServicesData, sizeof(USB_MASS_DEV), &MassDev);

    //
    // Handshaking...
    //
    MassDev->DevInfo    = DevInfo;
    DevInfo->MassDev    = (VOID*)&MassDev->BlockIoProtocol;
    MassDev->Handle     = Controller;
    MassDev->DevString  = (UINT8*)&DevInfo->DevNameString;
    MassDev->StorageType = DevInfo->bStorageType;

    //
    // Install BLOCK_IO protocol interface
    //
    gBS->AllocatePool(EfiBootServicesData, sizeof(EFI_BLOCK_IO_MEDIA), &MassDev->Media);

    MassDev->Media->MediaId             = 0;        // Media change indicator
    MassDev->Media->LogicalPartition    = FALSE;
    MassDev->Media->ReadOnly            = FALSE;
    MassDev->Media->WriteCaching        = FALSE;
    MassDev->Media->BlockSize           = DevInfo->wBlockSize;
    MassDev->Media->IoAlign             = 0;

    if (DevInfo->bLastStatus & USB_MASS_MEDIA_REMOVEABLE) {
        MassDev->Media->RemovableMedia = TRUE;
    } else {
        MassDev->Media->RemovableMedia = FALSE;
    }
    if ((DevInfo->bLastStatus & USB_MASS_MEDIA_PRESENT) && 
        (DevInfo->MaxLba != 0) && (DevInfo->wBlockSize != 0)) {
        // For SCSI devices, this is reported in the READ CAPACITY (16) parameter 
        // data Returned Logical Block Address field (see SBC-3) minus one.
        MassDev->Media->LastBlock = DevInfo->MaxLba - 1;   // LastBlock is 0-based
        MassDev->Media->MediaPresent = TRUE;
    } else {
        MassDev->Media->LastBlock = 0;
        MassDev->Media->MediaPresent = FALSE;
    }

#if defined CORE_COMBINED_VERSION && CORE_COMBINED_VERSION > 0x4028a
    if(pST->Hdr.Revision >= 0x0002001F) {
        MassDev->BlockIoProtocol.Revision    = EFI_BLOCK_IO_PROTOCOL_REVISION3;
        //
        // Default value set to 1 logical blocks per PhysicalBlock
        //
        MassDev->Media->LogicalBlocksPerPhysicalBlock=1;

        //
        // Default value set to 0 for Lowest Aligned LBA
        //
        MassDev->Media->LowestAlignedLba=0;

        MassDev->Media->OptimalTransferLengthGranularity=MassDev->Media->BlockSize;
    } else {
        MassDev->BlockIoProtocol.Revision    = 1;
    }
#else 
    MassDev->BlockIoProtocol.Revision    = 1;
#endif

    MassDev->BlockIoProtocol.Media        = MassDev->Media;
    MassDev->BlockIoProtocol.Reset        = AmiUsbBlkIoReset;
    MassDev->BlockIoProtocol.ReadBlocks   = AmiUsbBlkIoReadBlocks;
    MassDev->BlockIoProtocol.WriteBlocks  = AmiUsbBlkIoWriteBlocks;
    MassDev->BlockIoProtocol.FlushBlocks  = AmiUsbBlkIoFlushBlocks;

    MassDev->LogicalAddress = LogicalAddress;

    MassDev->PciBDF = gUsbData->HcTable[DevInfo->bHCNumber - 1]->wBusDevFuncNum;

#if !defined (CORE_COMBINED_VERSION) || CORE_COMBINED_VERSION <= 0x40280
    // Install INT13 device if Legacy USB support is enabled
    if((gUsbData->dUSBStateFlag & USB_FLAG_DISABLE_LEGACY_SUPPORT) == 0) {
        if (DevInfo->bPhyDevType != USB_MASS_DEV_UNKNOWN &&
            !(DevInfo->bPhyDevType != USB_MASS_DEV_CDROM && 
            (DevInfo->wBlockSize > 0x200 && DevInfo->wBlockSize != 0xFFFF))){
            gAmiUsbController->UsbInstallLegacyDevice(MassDev);
        }
    }
#endif

    USB_DEBUG(DEBUG_LEVEL_3, "InstallUSBMass(%x): BS %d, MaxLBA %lx, LA: %x %s\n",
        DevInfo, DevInfo->wBlockSize, DevInfo->MaxLba,
        MassDev->LogicalAddress, &DevInfo->DevNameString);

    Status = gBS->InstallProtocolInterface(
                    &MassDev->Handle,
                    &gEfiBlockIoProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &MassDev->BlockIoProtocol
                    );
    USB_DEBUG(DEBUG_LEVEL_3, "Install BlockIO on %x status = %r\n", Controller, Status);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   UninstallUSBMass
//
// Description: Removes BlkIo protocol from USB Mass Storage device
//
// Input:       DevInfo - pointer to a USB device structure
//
// Output:      None
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UninstallUSBMass(USB_MASS_DEV *MassDev)
{
    EFI_STATUS      Status;
	DEV_INFO		*DevInfo = MassDev->DevInfo;
    HC_STRUC*       HcData;
    UINT8           UsbStatus;

    HcData = gUsbData->HcTable[DevInfo->bHCNumber - 1];
 	UsbStatus = UsbDevDriverDisconnect(HcData, DevInfo);
	ASSERT(UsbStatus == USB_SUCCESS);

    USB_DEBUG(DEBUG_LEVEL_3, "Uninstall mass storage device  %x: ", MassDev->Handle);
    
    Status  = gBS->UninstallMultipleProtocolInterfaces(
                MassDev->Handle,
                &gEfiBlockIoProtocolGuid,
                &MassDev->BlockIoProtocol,
                NULL);

#if !defined (CORE_COMBINED_VERSION) || CORE_COMBINED_VERSION <= 0x40280
    gAmiUsbController->UsbUninstallLegacyDevice(MassDev);
#endif

    USB_DEBUG(DEBUG_LEVEL_3, "%r\n", Status);
    if(!EFI_ERROR(Status)){
        gBS->FreePool(MassDev->Media);
        gBS->FreePool(MassDev);
        DevInfo->MassDev = NULL;
    }

    return Status;
}

/************ BlockIO Protocol implementation routines******************/
//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiUsbBlkIoReset
//
// Description: Reset the USB Logic Drive
//
// Input:       This: A pointer to the Block I/O protocol interface
//
//              ExtendedVerification: Indicate that the driver may perform
//              an exhaustive verification operation of the device during
//              reset
//
// Output:      EFI_SUCCESS: The USB Logic Drive is reset
//              EFI_DEVICE_ERROR: The Floppy Logic Drive is not functioning
//              correctly and can not be reset
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AmiUsbBlkIoReset (
  IN  EFI_BLOCK_IO_PROTOCOL  *This,
  IN  BOOLEAN                ExtendedVerification
  )

{
    return  EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiUsbBlkIoFlushBlocks
//
// Description: Flush USB Mass Storage Device
//
// Input:       This: A pointer to the Block I/O protocol interface
//
// Output:      EFI_SUCCESS: The USB Logic Drive successfully flushed
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AmiUsbBlkIoFlushBlocks (
  IN  EFI_BLOCK_IO_PROTOCOL  *This
  )
{
    return EFI_SUCCESS;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiUsbBlkIoReadWrite
//
// Description: This routine is invoked from AmiUsbBlkIoReadBlocks and
//              AmiUsbBlkIoWriteBlocks. See these for parameters reference.
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AmiUsbBlkIoReadWrite (
  IN  EFI_BLOCK_IO_PROTOCOL  *This,
  IN  UINT32                 MediaId,
  IN  EFI_LBA                Lba,
  IN  UINTN                  BufferSize,
  IN OUT VOID                *Buffer,
  UINT8                     ReadWrite
  )
{
    USB_MASS_DEV            *MassDev;
    URP_STRUC               Parameters;
    EFI_STATUS              Status = EFI_SUCCESS;
    UINT32                  Buf;
    UINT32                  BytesToTransfer;
    UINT32                  BytesRemaining;
    UINT16                  BlockSize;
    UINTN                   BufferAddress;
	UINT8					*DataBuffer;
	UINTN					Pages;
    DEV_INFO                *DevInfo;

    MassDev   = (USB_MASS_DEV*)This;
    BlockSize = ((DEV_INFO*)(MassDev->DevInfo))->wBlockSize;

    //
    // Check if media id matches
    //
    if ( This->Media->MediaId != MediaId ) {
        return EFI_MEDIA_CHANGED;
    }

    if (BufferSize == 0) return EFI_SUCCESS;
    if (Buffer == NULL) return EFI_INVALID_PARAMETER;

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    BufferAddress = (UINTN)Buffer;
    if((This->Media->IoAlign > 1 ) && (BufferAddress % This->Media->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }
    

    //
    // Get media status
    //
    This->Media->MediaPresent = TRUE;   // Initialize, to be updated if no media

    Parameters.bFuncNumber = USB_API_MASS_DEVICE_REQUEST;
    Parameters.bSubFunc = USB_MASSAPI_GET_MEDIA_STATUS;
    Parameters.ApiData.MassGetDevSts.bDevAddr = (UINT8)MassDev->LogicalAddress;
    Parameters.ApiData.MassGetDevSts.bDeviceStatus = 0;

 	InvokeUsbApi(&Parameters);

    DevInfo = (DEV_INFO*)MassDev->DevInfo;

    if ((Parameters.ApiData.MassGetDevSts.bDeviceStatus & USB_MASS_MEDIA_PRESENT) && 
        (DevInfo->MaxLba != 0) && (DevInfo->wBlockSize != 0)) {
        if ((DevInfo->wBlockSize != This->Media->BlockSize) ||
           ((DevInfo->MaxLba -1)!= This->Media->LastBlock) ||
            (Parameters.ApiData.MassGetDevSts.bDeviceStatus & USB_MASS_MEDIA_CHANGED)) {
            This->Media->MediaId++;
            This->Media->ReadOnly = FALSE;
            This->Media->LastBlock = DevInfo->MaxLba - 1;
            This->Media->BlockSize = DevInfo->wBlockSize;
        }
    } else {
        This->Media->LastBlock = 0; 
    }

    if ((!(Parameters.ApiData.MassGetDevSts.bDeviceStatus & USB_MASS_MEDIA_PRESENT)) 
        ||(This->Media->LastBlock == 0) || (This->Media->BlockSize == 0)) {
        This->Media->MediaPresent = FALSE;
        This->Media->LastBlock = 0;
        return EFI_NO_MEDIA;
    }
    
    if (MediaId != This->Media->MediaId) {
        return EFI_MEDIA_CHANGED;
    }
    //
    // Check Parameter to comply with EFI 1.1 Spec
    //
    if (Lba > This->Media->LastBlock) {
        return EFI_INVALID_PARAMETER;
    }

    BlockSize = ((DEV_INFO*)(MassDev->DevInfo))->wBlockSize;

    if ((Lba + (BufferSize / BlockSize) - 1) > This->Media->LastBlock) {
        return EFI_INVALID_PARAMETER;
    }

    if (BufferSize % BlockSize != 0) {
        return EFI_BAD_BUFFER_SIZE;
    }

	DataBuffer = (UINT8*)(UINTN)Buffer;
	if (Shr64((UINTN)Buffer, 32)) {
		Pages = EFI_SIZE_TO_PAGES(BufferSize);
		DataBuffer = (UINT8*)0xFFFFFFFF;
		Status = gBS->AllocatePages(AllocateMaxAddress, EfiBootServicesData,
                		Pages, (EFI_PHYSICAL_ADDRESS*)&DataBuffer);
		if (!(EFI_ERROR(Status))) {
    		if (ReadWrite == WRITE) {
    			gBS->CopyMem(DataBuffer, Buffer, BufferSize);
    		}
		}  else {
		    DataBuffer = (UINT8*)(UINTN)Buffer;
		}
	}

    BytesRemaining = (UINT32)BufferSize;
    Buf = (UINT32)(UINTN)DataBuffer;
    while (BytesRemaining) {
        BytesToTransfer = (BytesRemaining > 0x10000)? 0x10000 : BytesRemaining;
        //
        // Prepare URP_STRUC with USB_MassRead attributes
        //
        Parameters.bFuncNumber = USB_API_MASS_DEVICE_REQUEST;
        Parameters.bSubFunc = (ReadWrite == READ)? USB_MASSAPI_READ_DEVICE : USB_MASSAPI_WRITE_DEVICE;
        Parameters.ApiData.MassRead.DevAddr = (UINT8)MassDev->LogicalAddress;//MassDev->DevInfo->bDeviceAddress;
        Parameters.ApiData.MassRead.StartLba = Lba;
        Parameters.ApiData.MassRead.NumBlks = (UINT16)(BytesToTransfer/((DEV_INFO*)MassDev->DevInfo)->wBlockSize);
        Parameters.ApiData.MassRead.PreSkipSize = 0;
        Parameters.ApiData.MassRead.PostSkipSize = 0;
        Parameters.ApiData.MassRead.BufferPtr = Buf;

        /*
        if (ReadWrite == READ) {
            USB_DEBUG(DEBUG_LEVEL_3, "Reading...%x bytes, Lba %x ", BytesToTransfer, CurrentLba);
        } else {
            USB_DEBUG(DEBUG_LEVEL_3, "Writng...%x bytes, Lba %x ", BytesToTransfer, CurrentLba);
        }
        */
		InvokeUsbApi(&Parameters);
		
        switch (Parameters.bRetValue) {
            case USB_ATA_NO_MEDIA_ERR:
                    Status = EFI_NO_MEDIA;  // No media in drive
                    This->Media->MediaPresent = FALSE;
                    break;
            case USB_ATA_WRITE_PROTECT_ERR:
                    Status = (ReadWrite == READ)? EFI_SUCCESS : EFI_WRITE_PROTECTED;
                    if (Status == EFI_WRITE_PROTECTED)  
                        This->Media->ReadOnly = TRUE;
                    break;
            case USB_ATA_TIME_OUT_ERR:          // 0x080 Command timed out error
            case USB_ATA_DRIVE_NOT_READY_ERR:   // 0x0AA Drive not ready error
            case USB_ATA_DATA_CORRECTED_ERR:    // 0x011 Data corrected error
            case USB_ATA_PARAMETER_FAILED:      // 0x007 Bad parameter error
            case USB_ATA_MARK_NOT_FOUND_ERR:    // 0x002 Address mark not found error
            case USB_ATA_READ_ERR:              // 0x004 Read error
            case USB_ATA_UNCORRECTABLE_ERR:     // 0x010 Uncorrectable data error
            case USB_ATA_BAD_SECTOR_ERR:        // 0x00A Bad sector error
            case USB_ATA_GENERAL_FAILURE:       // 0x020 Controller general failure
                    Status = EFI_DEVICE_ERROR;
                    break;
            default:
                    Status = EFI_SUCCESS;
        }
        //  USB_DEBUG(DEBUG_LEVEL_3, "Status= %r\n", Status);
        if (EFI_ERROR(Status)) {
            break;
        }
        BytesRemaining = BytesRemaining - BytesToTransfer;
        Buf = Buf + BytesToTransfer;
        Lba = Lba + (UINT32)BytesToTransfer/((DEV_INFO*)(MassDev->DevInfo))->wBlockSize;
    }

	if (DataBuffer != Buffer) {
		if (ReadWrite == READ) {
			gBS->CopyMem(Buffer, DataBuffer, BufferSize - BytesRemaining);
		}
		gBS->FreePages((EFI_PHYSICAL_ADDRESS)DataBuffer, Pages);
	}

    return  Status;
}



//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiUsbBlkIoReadBlocks
//
// Description: Read the requested number of blocks from the device
//
// Input:       This EFI_BLOCK_IO *: A pointer to the Block I/O protocol
//                                   interface
//              MediaId UINT32: The media id that the read request is for
//              LBA EFI_LBA:    The starting logic block address to read from
//                              on the device
//              BufferSize UINTN:   The size of the Buffer in bytes
//              Buffer VOID *:  A pointer to the destination buffer for the data
//
//
// Output:      EFI_SUCCESS:     The data was read correctly from the device
//              EFI_DEVICE_ERROR:The device reported an error while attempting
//                                  to perform the read operation
//              EFI_NO_MEDIA:    There is no media in the device
//              EFI_MEDIA_CHANGED:   The MediaId is not for the current media
//              EFI_BAD_BUFFER_SIZE: The BufferSize parameter is not a multiple
//                              of the intrinsic block size of the device
//              EFI_INVALID_PARAMETER:The read request contains LBAs that are
//                          not valid, or the buffer is not on proper alignment
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AmiUsbBlkIoReadBlocks (
  IN  EFI_BLOCK_IO_PROTOCOL  *This,
  IN  UINT32                 MediaId,
  IN  EFI_LBA                Lba,
  IN  UINTN                  BufferSize,
  OUT VOID                   *Buffer
)

{
    EFI_STATUS  Status;
    EFI_TPL     OldTpl;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);
    
    Status = AmiUsbBlkIoReadWrite(This, MediaId, Lba, BufferSize, Buffer, READ);
    
    gBS->RestoreTPL(OldTpl);
    
    return Status;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   AmiUsbBlkIoWriteBlocks
//
// Description: Write a specified number of blocks to the device
//
// Input:       This EFI_BLOCK_IO *: A pointer to the Block I/O protocol
//              interface
//              MediaId UINT32: The media id that the write request is for
//              LBA EFI_LBA:    The starting logic block address to written
//              BufferSize UINTN:   The size of the Buffer in bytes
//              Buffer VOID *:  A pointer to the destination buffer for the data
//
//
// Output:      EFI_SUCCESS:     The data were written correctly to the device
//              EFI_WRITE_PROTECTED: The device can not be written to
//              EFI_NO_MEDIA:    There is no media in the device
//              EFI_MEDIA_CHANGED:   The MediaId is not for the current media
//              EFI_DEVICE_ERROR:  The device reported an error while attempting
//                                  to perform the write operation
//              EFI_BAD_BUFFER_SIZE: The BufferSize parameter is not a multiple
//                                  of the intrinsic block size of the device
//              EFI_INVALID_PARAMETER:The read request contains LBAs that are
//                          not valid, or the buffer is not on proper alignment
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
AmiUsbBlkIoWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSize,
  IN VOID                   *Buffer
  )
{
    EFI_STATUS  Status;
    EFI_TPL     OldTpl;
#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
    if(AmiBlkWriteProtection != NULL) {
        // Get user input
        Status = AmiBlkWriteProtection->BlockIoWriteProtectionCheck( 
                                                    AmiBlkWriteProtection,
                                                    This,
                                                    Lba,
                                                    BufferSize
                                                    );
        // Abort operation if denied
        if(Status == EFI_ACCESS_DENIED) {
            return Status;
        }
    } 
#endif
    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);
    
    Status = AmiUsbBlkIoReadWrite(This, MediaId, Lba, BufferSize, Buffer, WRITE);
    
    gBS->RestoreTPL(OldTpl);
    
    return Status;    
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbMassSupported
//
// Description: Verifies if usb mouse support can be installed on a device
//
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

static
EFI_STATUS
UsbMassSupported (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *Dp)
{
    EFI_USB_INTERFACE_DESCRIPTOR Desc;
    EFI_STATUS Status;
    EFI_USB_IO_PROTOCOL *UsbIo;
										//(EIP99882+)>
    if (!gUsbData->UsbSetupData.UsbMassDriverSupport) {
        return EFI_UNSUPPORTED;
    }
										//<(EIP99882+)
    Status = gBS->OpenProtocol ( Controller,  &gEfiUsbIoProtocolGuid,
        &UsbIo, This->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_BY_DRIVER );
    if( EFI_ERROR(Status))
        return Status;

    VERIFY_EFI_ERROR(
        gBS->CloseProtocol (
        Controller, &gEfiUsbIoProtocolGuid,
        This->DriverBindingHandle, Controller));

    Status = UsbIo->UsbGetInterfaceDescriptor(UsbIo, &Desc  );
    if(EFI_ERROR(Status))
        return EFI_UNSUPPORTED;

    if ( Desc.InterfaceClass == BASE_CLASS_MASS_STORAGE &&
        (
        Desc.InterfaceProtocol == PROTOCOL_CBI ||
        Desc.InterfaceProtocol == PROTOCOL_CBI_NO_INT   ||
        Desc.InterfaceProtocol == PROTOCOL_BOT ))
    {
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbMassStart
//
// Description: Starts USB mass storage device
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

static
EFI_STATUS
UsbMassStart(
    EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE Controller,
    EFI_DEVICE_PATH_PROTOCOL *Dp
)
{
    EFI_STATUS              Status;
    EFI_USB_IO_PROTOCOL     *UsbIo;
    DEV_INFO                *DevInfo;
    USBDEV_T*               Dev;
    HC_STRUC*               HcData;
    UINT8                   UsbStatus;

    USB_DEBUG(DEBUG_LEVEL_3, "USB: UsbMassStart: starting...\n");
    //
    // Open Protocols
    //
    Status = gBS->OpenProtocol(Controller, &gEfiUsbIoProtocolGuid,
                &UsbIo, This->DriverBindingHandle,
                Controller, EFI_OPEN_PROTOCOL_BY_DRIVER);
    
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Dev = UsbIo2Dev(UsbIo);

    if (Dev == NULL) {
        return EFI_DEVICE_ERROR;
    }

    DevInfo = Dev->dev_info;
    
    if (DevInfo->bLUN) {
        USB_DEBUG(DEBUG_LEVEL_3, "USB: Skiping LUN %d\n", DevInfo->bLUN);
    } else {
        HcData = gUsbData->HcTable[Dev->dev_info->bHCNumber - 1];
        UsbStatus = UsbSmiReConfigDevice(HcData, Dev->dev_info);
        if (UsbStatus != USB_SUCCESS) {
            USB_DEBUG(DEBUG_LEVEL_3, 
                    "USB: UsbMassStart: failed to Reconfigure: %d\n", UsbStatus);
            gBS->CloseProtocol(Controller, &gEfiUsbIoProtocolGuid,
                            This->DriverBindingHandle, Controller);
            return EFI_DEVICE_ERROR;
        }
    } //End Reconfigure

    if (!(DevInfo->Flag & DEV_INFO_DEV_PRESENT)) {
        gBS->CloseProtocol(Controller, &gEfiUsbIoProtocolGuid,
                        This->DriverBindingHandle, Controller);
        return EFI_DEVICE_ERROR;
    }

    Status = InstallUsbMass(Controller, DevInfo);

    if (EFI_ERROR(Status)) {
    
        gBS->CloseProtocol(Controller, &gEfiUsbIoProtocolGuid,
                        This->DriverBindingHandle, Controller);
        return Status;
    }

#if defined CORE_COMBINED_VERSION && (CORE_COMBINED_VERSION > 0x4028E)
    if(AmiBlkWriteProtection == NULL) {
        Status = pBS->LocateProtocol(&gAmiBlockIoWriteProtectionProtocolGuid, NULL, &AmiBlkWriteProtection); 
        if(EFI_ERROR(Status)) {
            AmiBlkWriteProtection = NULL;
        }
    }
#endif

    return Status;
}

//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbMassStop
//
// Description: Stops USB mass storage device and removes BlkIo
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbMassStop(
    EFI_DRIVER_BINDING_PROTOCOL *Binding,
    EFI_HANDLE Controller,
    UINTN NumberOfChildren,
    EFI_HANDLE *Children
)
{
    EFI_STATUS Status;
    EFI_BLOCK_IO_PROTOCOL   *BlockIo;

    VERIFY_EFI_ERROR(
        Status = gBS->OpenProtocol ( Controller,  &gEfiBlockIoProtocolGuid,
        &BlockIo, Binding->DriverBindingHandle,
        Controller, EFI_OPEN_PROTOCOL_GET_PROTOCOL ));
    if (EFI_ERROR(Status))
        return Status;

    Status = UninstallUSBMass((USB_MASS_DEV*)BlockIo);

    VERIFY_EFI_ERROR(
        gBS->CloseProtocol (
        Controller, &gEfiUsbIoProtocolGuid,
        Binding->DriverBindingHandle, Controller));

    return Status;
}


CHAR16*
UsbMassGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return NULL;
}


//<AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name:        UsbMassInit
//
// Description: USB Mass storage driver entry point
//
//---------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
UsbMassInit(
    EFI_HANDLE  ImageHandle,
    EFI_HANDLE  ServiceHandle
)
{
                                        //(EIP59272)>
    static NAME_SERVICE_T Names;
    static EFI_DRIVER_BINDING_PROTOCOL Binding = {
        UsbMassSupported,
        UsbMassStart,
        UsbMassStop,
        USBMASS_DRIVER_VERSION,
        NULL,
        NULL };

    Binding.DriverBindingHandle = ServiceHandle;
    Binding.ImageHandle = ImageHandle;

    return gBS->InstallMultipleProtocolInterfaces(
        &Binding.DriverBindingHandle,
        &gEfiDriverBindingProtocolGuid, &Binding,
        &gEfiComponentName2ProtocolGuid, InitNamesProtocol(&Names,
                L"USB Mass Storage driver", UsbMassGetControllerName),
        NULL);
                                        //<(EIP59272)
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Pkwy, Norcross, GA 30093                 **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
