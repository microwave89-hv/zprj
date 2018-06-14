#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/USB/ALASKA/rt/usbrt.mak 27    10/16/16 10:15p Wilsonlee $
#
# $Revision: 27 $
#
# $Date: 10/16/16 10:15p $
#
#****************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/USB/ALASKA/rt/usbrt.mak $
# 
# 27    10/16/16 10:15p Wilsonlee
# [TAG]  		EIP288158
# [Category]  	Improvement
# [Description]  	Check if gUsbData is integrity.
# [Files]  		amiusb.cif, usbsb.c, AmiUsbLib.cif, AmiUsbLib.sdl,
# AmiUsbSmmGlobalDataValidationLib.c,
# AmiUsbSmmGlobalDataValidationLib.cif,
# AmiUsbSmmGlobalDataValidationLib.mak, Crc32.c, amiusb.c, amiusb.h,
# ehci.c, elib.c, ohci.c, syskbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h,
# usbhid.c, usbhub.c, usbkbd.c, usbmass.c, usbms.c, usbrt.mak, xhci.c,
# amiusbhc.c, efiusbccid.c, efiusbmass.c, uhcd.c, usbmisc.c,
# AmiUsbController.h, AmiUsbLibInclude.cif,
# AmiUsbSmmGlobalDataValidationLib.h
# 
# 26    12/03/14 9:38p Wilsonlee
# [TAG]  		EIP193805
# [Category]  	Improvement
# [Description]  	Security Enhancement for SMIHandler in USB module.
# [Files]  		amiusb.c, uhcd.c, usbrt.mak, usbdef.h, usbsb.c
# 
# 25    3/19/13 4:02a Ryanchou
# [TAG]  		EIP118177
# [Category]  	Improvement
# [Description]  	Dynamically allocate HCStrucTable at runtime.
# [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
# syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
# usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
# efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
# usbmisc.c, usbsrc.sdl
# 
# 24    11/20/12 9:07p Wilsonlee
# [TAG]  		EIP90887
# [Category]  	New Feature
# [Description]  	Add a hook to check keyboard buffer for speicial chars.
# [Files]  		usb.sdl, usbrt.mak, usbkbd.c
# 
# 23    8/29/12 8:41a Ryanchou
# [TAG]  		EIP77262
# [Category]  	New Feature
# [Description]  	Remove SMM dependency of USB.
# [Files]  		usb.sdl, usbport.c, amiusb.c, amiusb.dxs, amiusb.h, ehci.c,
# elib.c, ohci.c, uhci.c, usb.c, usbdef.h, usbrt.mak, xhci.c, amiusbhc.c,
# efiusbccid.c, efiusbhid.c, efiusbkb.c, efiusbmass.c, uhcd.c, uhcd.dxs,
# uhcd.h, usbmisc.c, AmiUsbController.h
# 
# 22    1/16/12 6:02a Ryanchou
# [TAG]  		EIP81132
# [Description]  	Add core version check for EIP80609 solution.
# [Files]  		amiusb.c, usbrt.mak, usbsb.c
# 
# 21    1/14/12 4:10a Ryanchou
# [TAG]  		EIP80609
# [Category]  	Bug Fix
# [Severity]  	Important
# [Symptom]  	If to enable debug mode and set launch CSM is "Never" in
# setup, system will hang at 0xB1
# [RootCause]  	The pointer AmiUsb is invalid if CSM is not launched,
# that may cause CPU exception.
# [Solution]  	Added USB smm protocol, and use SmmLocateProtocol to get
# the pointer.
# [Files]  		amiusb.c, AmiUsbController.h, usbrt.mak, usbsb.c
# 
# 20    10/25/11 8:27a Wilsonlee
# [TAG]  		EIP71750
# [Category]  	New Feature
# [Description]  	Support extraUSB device driver hook by elink.
# [Files]  		usb.c, uhcd.c, uhcd.mak, usbrt.mak, usb.sdl
# 
# 19    11/22/10 8:45a Ryanchou
# [TAG]  		EIP48064
# [Category]  	Improvement
# [Description]  	The SB template implemented elink
# AcpiEnableCallbackList, the XHCI/EHCI hand off function should be
# invoked via the elink AcpiEnableCallbackList.
# [Files]  		amidef.h, amiusb.c, amiusb.dxs, amiusb.h,
# AmiUsbController.h, usb.sdl, usbrt.mak, usbsb.c
# 
# 18    11/13/09 9:14a Olegi
# EIP31023: key repeat rates are defined by SDL tokens.
# 
# 17    10/30/09 5:48p Olegi
# 
# 16    5/16/08 12:03p Olegi
# Compliance with AMI coding standard.
#
#****************************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		UsbRt.mak
#
# Description:	Make file for the UsbRt component
#
#<AMI_FHDR_END>
#**********************************************************************

all : USBRT

!ifndef PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!endif

!ifndef CORE_COMBINED_VERSION
CORE_COMBINED_VERSION = $(CORE_MAJOR_VERSION)*65536+$(CORE_MINOR_VERSION)*100+$(CORE_REVISION)*10+$(CORE_BUILD_NUMBER)
!endif

USBRT : $(BUILD_DIR)\usbrt.mak UsbRtElinkList USBRTBin 

USBRT_EXT_HEADERS=\
	$(UHCD_DIR)\RT\usbdef.h\
	$(UHCD_DIR)\RT\amidef.h\
	$(UHCD_DIR)\RT\amiusb.h\
	$(BUILD_DIR)\UsbDevDriverElinks.h

$(BUILD_DIR)\usbrt.mak : $(USBRT_DIR)\$(@B).cif $(USBRT_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(USBRT_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

UsbRtElinkList: UhcdElinkList
	$(ECHO) #define USB_DEV_DELAYED_DRIVER $(USB_DEV_DELAYED_DRIVER_LIST) >> $(BUILD_DIR)\UsbDevDriverElinks.h
	$(ECHO) #define USB_DEV_DRIVER $(USB_DEV_DRIVER_LIST) >> $(BUILD_DIR)\UsbDevDriverElinks.h
	$(ECHO) #define KBD_BUFFER_CHECK_ELINK_LIST	$(CheckKeyBoardBufferForSpecialChars) >> $(BUILD_DIR)\UsbDevDriverElinks.h

$(BUILD_DIR)\dummyusbrt.obj:
	copy << $(BUILD_DIR)\dummyusbrt.c
#include "amidef.h"
#include "usbdef.h"
#include "usbkbd.h"

extern	UINT8	UHCI_FillHCDEntries(HCD_HEADER*);
extern	UINT8	OHCI_FillHCDEntries(HCD_HEADER*);
extern	UINT8	EHCI_FillHCDEntries(HCD_HEADER*);
extern	UINT8	XHCI_FillHCDEntries(HCD_HEADER*);
extern	USB_GLOBAL_DATA *gUsbData;

void FillHcdEntries()
{
#if UHCI_SUPPORT
	UHCI_FillHCDEntries (&gUsbData->aHCDriverTable[USB_INDEX_UHCI]);
#endif
#if OHCI_SUPPORT
	OHCI_FillHCDEntries (&gUsbData->aHCDriverTable[USB_INDEX_OHCI]);
#endif
#if EHCI_SUPPORT
	EHCI_FillHCDEntries (&gUsbData->aHCDriverTable[USB_INDEX_EHCI]);
#endif
#if XHCI_SUPPORT
	XHCI_FillHCDEntries (&gUsbData->aHCDriverTable[USB_INDEX_XHCI]);
#endif
}
<<
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(BUILD_DIR)\dummyusbrt.c /I$(UHCD_DIR) /I$(USBRT_DIR)

!if $(USB_RUNTIME_DRIVER_IN_SMM) == 1
!ifdef AcpiEnableCallbackList
$(BUILD_DIR)\usbsb.obj: $(USB_SB_DIR)\usbsb.c
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(USB_SB_DIR)\usbsb.c /I$(USB_SB_DIR) /I$(USBRT_DIR)

$(BUILD_DIR)\usbacpi.obj: $(USB_SB_DIR)\usbsb.c
	$(CC) $(CFLAGS) /DUSB_ACPI_ENABLE_CALLBACK /Fo$(BUILD_DIR)\usbacpi.obj $(USB_SB_DIR)\usbsb.c /I$(USB_SB_DIR) /I$(USBRT_DIR)

AcpiModeEnableBin: $(BUILD_DIR)\usbacpi.obj

!else
$(BUILD_DIR)\usbsb.obj: $(USB_SB_DIR)\usbsb.c
	$(CC) $(CFLAGS) /DUSB_ACPI_ENABLE_DISPATCH /Fo$(BUILD_DIR)\ $(USB_SB_DIR)\usbsb.c /I$(USB_SB_DIR) /I$(USBRT_DIR)

!endif
!endif

$(BUILD_DIR)\usbrtport.obj : $(USBPORTING_DIR)\usbport.c
	$(CC) $(CFLAGS) /DUSB_RT_DRIVER /Fo$(BUILD_DIR)\UsbrtPort.obj $(USBPORTING_DIR)\usbport.c /I$(UHCD_DIR) /I$(USBRT_DIR)

USBRTBinObjects = \
	$(BUILD_DIR)\dummyusbrt.obj \
!if $(USB_RUNTIME_DRIVER_IN_SMM) == 1
	$(BUILD_DIR)\usbsb.obj \
	$(BUILD_DIR)\AmiBufferValidationLib.lib \
	$(BUILD_DIR)\AmiUsbSmmGlobalDataValidationLib.lib \
!endif
	$(BUILD_DIR)\usbrtport.obj

USBRTBin : $(AMIDXELIB) $(USBRTBinObjects)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\usbrt.mak all\
		GUID=04EAAAA1-29A1-11d7-8838-00500473D4EB \
		ENTRY_POINT=USBDriverEntryPoint \
		"CFLAGS=$(CFLAGS) /I$(UHCD_DIR)"\
		"AFLAGS=$(AFLAGS) /Fl"\
		"EXT_HEADERS=$(USBRT_EXT_HEADERS)"\
!if $(USB_RUNTIME_DRIVER_IN_SMM) == 1 && $(PI_SPECIFICATION_VERSION) >= 0x00001000A && $(CORE_COMBINED_VERSION) >= 0x4028B
		TYPE=SMM_DRIVER \
		DEPEX1=$(USBRT_DIR)\amiusb.dxs \
!else
		TYPE=BS_DRIVER \
		DEPEX1=$(USBRT_DIR)\amiusb.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!endif
		COMPRESS=1\

#		"CFLAGS=$(CFLAGS:/W3=/W4) /I$(UHCD_DIR)"\

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2016, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
