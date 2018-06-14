//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/UsbPolicy.h 22    12/24/14 10:43p Wilsonlee $
//
// $Revision: 22 $
//
// $Date: 12/24/14 10:43p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Protocol/UsbPolicy.h $
// 
// 22    12/24/14 10:43p Wilsonlee
// [TAG]  		EIP196287
// [Category]  	Improvement
// [Description]  	Display info of connected usb controllers and remove or
// grayed-out some item according the connected usb controller number.
// [Files]  		uhcd.c, usbport.c, usb.uni, usb.sd, usbsetup.c,
// AmiUsbController.h, UsbPolicy.h
// 
// 21    12/21/12 5:03a Ryanchou
// [TAG]  		EIP71730
// [Category]  	New Feature
// [Description]  	Added OHCI handoff support.
// [Files]  		usb.sdl, usbport.c, amiusb.c, usbdef.h, UsbPolicy.h, usb.sd,
// usb.uni
// 
// 20    9/04/12 8:01a Wilsonlee
// [TAG]  		EIP99882
// [Category]  	New Feature
// [Description]  	Add the usb setup item and usbpolicyprotocol to enable
// or disable the usb mass storage driver.
// [Files]  		UsbPolicy.h, usb.uni, usb.sd, usbmass.c, usbdef.h,
// efiusbmass.c, usbport.c, uhcd.c
// 
// 19    5/03/12 5:11a Ryanchou
// [TAG]  		EIP83361
// [Category]  	New Feature
// [Description]  	Added "USB 2.0 Controller Mode" setup item.
// [Files]  		ehci.c, usb.sd, usb.sdl, usb.uni, usbdef.h, UsbPolicy.h,
// usbport.c
// 
// 18    8/08/11 5:26a Ryanchou
// [TAG]  		EIP60561
// [Category]  	New Feature
// [Description]  	Add USB timing policy protocol for timing override.
// [Files]  		ehci.c, guids.c, ohci.c, uhcd.c, uhci.c usb.c, usbdef.h,
// usbhub.c, usbmass.c, UsbPolicy.h, usbport.c usbsrc.sdl
// 
// 17    2/18/11 1:15a Ryanchou
// [TAG]  		EIP48184
// [Category]  	Improvement
// [Description]  	Update files according to the new Setup Customization
// guidelines.
// [Files]  		usb.sd, UsbPolicy.h
// 
// 16    10/12/10 2:45a Rameshr
// [TAG]- EIP 44585
// [Category]-IMPROVEMENT
// [Description]- Number of maximum supported USB Mass Storage device
// increased from 8 to 16. 
// [Files]- Uin13.bin, UsbPort.c, UsbInt13.h, Usb.c, Usbdef.h, Uasbmass.c,
// Usb.sd, usb.uni, UsbSetup.c, UsbSrc.sdl, UsbPolicy.h
//
//**********************************************************************

//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           UsbPolicy.h
//
//  Description:    Protocol used for USB policy definitions
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AMIUSB_POLICY_PROTOCOL_H_
#define _AMIUSB_POLICY_PROTOCOL_H_

#define EFI_USB_POLICY_PROTOCOL_GUID \
  { 0x5859cb76, 0x6bef, 0x468a, 0xbe, 0x2d, 0xb3, 0xdd, 0x1a, 0x27, 0xf0, 0x12 }
#define USB_TIMING_POLICY_PROTOCOL_GUID \
  { 0x89e3c1dc, 0xb5e3, 0x4d34, 0xae, 0xad, 0xdd, 0x7e, 0xb2, 0x82, 0x8c, 0x18 }

#ifndef VFRCOMPILE
typedef enum {
	USBMASS_EMU_AUTO,
	USBMASS_EMU_FDD,
	USBMASS_EMU_FORCED_FDD,
	USBMASS_EMU_HDD,
	USBMASS_EMU_CD
} USBMASS_EMU_TYPE;
#endif

#define USB_DEVPLCY_STATUS_PRESENT	1

#ifndef TYPEDEF_USB_SUPPORT_SETUP
#define TYPEDEF_USB_SUPPORT_SETUP
typedef struct {
	UINT8	UsbMainSupport;
	UINT8	UsbLegacySupport;
	UINT8	UsbEhciHandoff;
	UINT8	UsbOhciHandoff;
	UINT8	UsbHotplugFddSupport;
	UINT8	UsbHotplugHddSupport;
	UINT8	UsbHotplugCdromSupport;
	UINT8	UsbEmul6064;
	UINT8	UsbMassResetDelay;
	UINT8	UsbControlTimeOut;  //(EIP30079+)
	UINT8	UsbEmu1;
	UINT8	UsbEmu2;
	UINT8	UsbEmu3;
	UINT8	UsbEmu4;
	UINT8	UsbEmu5;
	UINT8	UsbEmu6;
	UINT8	UsbEmu7;
	UINT8	UsbEmu8;
	UINT8	UsbEmu9;
	UINT8	UsbEmu10;
	UINT8	UsbEmu11;
	UINT8	UsbEmu12;
	UINT8	UsbEmu13;
	UINT8	UsbEmu14;
	UINT8	UsbEmu15;
	UINT8	UsbEmu16;
	UINT8	UsbXhciSupport;
	UINT8	UsbXhciHandoff;
	UINT8	PowerGoodDeviceDelay;
	UINT8	PowerGoodDeviceNumDelay;
	UINT8	UsbHiSpeedSupport;
    UINT8   UsbMassDriverSupport;		//(EIP99882+)
} USB_SUPPORT_SETUP;
#endif

#ifndef TYPEDEF_USB_MASS_DEV_VALID
#define TYPEDEF_USB_MASS_DEV_VALID
typedef struct{
	UINT8	UsbEmu1Valid;
	UINT8	UsbEmu2Valid;
	UINT8	UsbEmu3Valid;
	UINT8	UsbEmu4Valid;
	UINT8	UsbEmu5Valid;
	UINT8	UsbEmu6Valid;
	UINT8	UsbEmu7Valid;
	UINT8	UsbEmu8Valid;
	UINT8	UsbEmu9Valid;
	UINT8	UsbEmu10Valid;
	UINT8	UsbEmu11Valid;
	UINT8	UsbEmu12Valid;
	UINT8	UsbEmu13Valid;
	UINT8	UsbEmu14Valid;
	UINT8	UsbEmu15Valid;
	UINT8	UsbEmu16Valid;
} USB_MASS_DEV_VALID;
#endif

#define	MAX_USB_MASS				8
#define SETUP_DATA_HOTPLUG_ENABLED	1
#define SETUP_DATA_HOTPLUG_DISABLED	2
#define SETUP_DATA_HOTPLUG_AUTO		3
#define SETUP_DATA_RESETDELAY_20S	1

#ifndef VFRCOMPILE
typedef struct _USB_POLICY_PROTOCOL {
	USB_SUPPORT_SETUP	*UsbDevPlcy;
} EFI_USB_POLICY_PROTOCOL;
#endif

#define EMULATION_FAKE_INTERFACE	1

#ifndef TYPEDEF_USB_MASS_DEV_NUM
#define TYPEDEF_USB_MASS_DEV_NUM
typedef struct {
	UINT8	UsbMassDevNum;
	UINT8	IsInteractionAllowed;
} USB_MASS_DEV_NUM;
#endif

#ifndef TYPEDEF_USB_CONTROLLER_NUM
#define TYPEDEF_USB_CONTROLLER_NUM
typedef struct {
    UINT8   UhciNum;
    UINT8   OhciNum;
    UINT8   EhciNum;
    UINT8   XhciNum;
} USB_CONTROLLER_NUM;
#endif

typedef struct {
	UINT16	UsbTimingPolicyRevision;
    UINT16  UsbTimingPolicyLength;
	UINT16  EhciPortPowerOnDelay;
	UINT16  EhciPortConnect;
	UINT16  EhciPortReset;
	UINT16  OhciHcResetDelay;
	UINT16  OhciPortEnable;
	UINT16  OhciHcReset;
	UINT16  UhciGlobalReset;
	UINT16  UhciPortEnable;
	UINT16  HubPortConnect;
	UINT16  HubPortEnable;
	UINT16  MassDeviceComeUp;
    UINT16  RmhPowerOnDelay;
} USB_TIMING_POLICY;

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
