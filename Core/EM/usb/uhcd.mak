#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/USB/ALASKA/uhcd.mak 12    3/19/13 4:02a Ryanchou $
#
# $Revision: 12 $
#
# $Date: 3/19/13 4:02a $
#
#****************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/USB/ALASKA/uhcd.mak $
# 
# 12    3/19/13 4:02a Ryanchou
# [TAG]  		EIP118177
# [Category]  	Improvement
# [Description]  	Dynamically allocate HCStrucTable at runtime.
# [Files]  		usb.sdl, usbport.c, usbsb.c, amiusb.c, ehci.c, ohci.c,
# syskbc.c, sysnokbc.c, uhci.c, usb.c, usbCCID.c, usbdef.h, usbhid.c,
# usbhub.c, usbmass.c, usbrt.mak, usb.sd, amiusbhc.c, efiusbccid.c,
# efiusbhid.c, efiusbmass.c, efiusbms.c, uhcd.c, uhcd.h, uhcd.mak,
# usbmisc.c, usbsrc.sdl
# 
# 11    10/25/11 8:26a Wilsonlee
# [TAG]  		EIP71750
# [Category]  	New Feature
# [Description]  	Support extraUSB device driver hook by elink.
# [Files]  		usb.c, uhcd.c, uhcd.mak, usbrt.mak, usb.sdl
# 
# 10    5/16/08 12:03p Olegi
# Compliance with AMI coding standard.
#
#****************************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		UHCD.MAK
#
# Description:	Make file for the UHCD component
#
#<AMI_FHDR_END>
#**********************************************************************
all : UHCD 

UHCD : $(BUILD_DIR)\uhcd.mak UhcdElinkList UHCDBin

UHCD_EXT_HEADERS=\
	$(UHCD_DIR)\RT\usbdef.h\
	$(UHCD_DIR)\RT\amidef.h\
	$(UHCD_DIR)\RT\amiusb.h\
	$(UHCD_DIR)\uhcd.h\
	$(BUILD_DIR)\UsbDevDriverElinks.h

$(BUILD_DIR)\uhcd.mak : $(UHCD_DIR)\$(@B).cif $(UHCD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(UHCD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

UhcdElinkList:
	$(ECHO) #define USB_DEV_EFI_DRIVER $(USB_DEV_EFI_DRIVER_LIST) > $(BUILD_DIR)\UsbDevDriverElinks.h

$(BUILD_DIR)\debug.obj : $(USBRT_DIR)\debug.c $(BUILD_DIR)\token.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(USBRT_DIR)\debug.c /I$(UHCD_DIR) /I$(USBRT_DIR)

$(BUILD_DIR)\guids.obj : $(USBRT_DIR)\guids.c
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(USBRT_DIR)\guids.c /I$(UHCD_DIR) /I$(USBRT_DIR)

$(BUILD_DIR)\usbport.obj : $(USBPORTING_DIR)\usbport.c
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(USBPORTING_DIR)\usbport.c /I$(UHCD_DIR) /I$(USBRT_DIR)

$(BUILD_DIR)\uhcd.lib : $(BUILD_DIR)\debug.obj $(BUILD_DIR)\guids.obj
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\uhcd.mak all\
		"CFLAGS=$(CFLAGS) /I$(USBRT_DIR)"\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\uhcd.lib

UHCDBin : $(AMIDXELIB) $(BUILD_DIR)\uhcd.lib $(BUILD_DIR)\usbport.obj
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\uhcd.mak all\
		GUID=580DD900-385D-11d7-883A-00500473D4EB \
		ENTRY_POINT=AmiUsbDriverEntryPoint \
		"CFLAGS=$(CFLAGS) /I$(USBRT_DIR)"\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		"EXT_HEADERS=$(UHCD_EXT_HEADERS)"\
		TYPE=BS_DRIVER \
		COMPRESS=1\
		DEPEX1=$(UHCD_DIR)\uhcd.dxs \

#---------------------------------------------------------------------------
#		Create SB Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\usb.sdb
SetupBin : $(BUILD_DIR)\USBSetup.obj

$(BUILD_DIR)\usb.sdb : $(USB_SETUP_DIR)\usb.sd $(USB_SETUP_DIR)\usb.uni
	$(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\usb.sdb $(USB_SETUP_DIR)\usb.uni
	$(STRGATHER) -scan -db $(BUILD_DIR)\usb.sdb -od $(BUILD_DIR)\usb.sdb $(USB_SETUP_DIR)\usb.sd

$(BUILD_DIR)\USBSetup.obj : $(USB_SETUP_DIR)\USBSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(USB_SETUP_DIR)\USBSetup.c
#---------------------------------------------------------------------------


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
