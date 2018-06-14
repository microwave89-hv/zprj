#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#***********************************************************************
# $Header: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbInt13.mak 4     7/03/13 5:21a Ryanchou $
#
# $Revision: 4 $
#
# $Date: 7/03/13 5:21a $
#***********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/USB/ALASKA/Int13/UsbInt13.mak $
# 
# 4     7/03/13 5:21a Ryanchou
# [TAG]  		EIP123988
# [Category]  	Improvement
# [Description]  	Move the code creating BBS table to end of POST.
# [Files]  		UsbBbs.c, UsbInt13.c, UsbInt13.cif, UsbInt13.h,
# UsbInt13.mak, UsbInt13.sdl, efiusbmass.c, uhcd.c, uhcd.h,
# AmiUsbController.h
# 
# 3     1/21/09 10:58a Olegi
# Dependency on AMIUSB and CSM has been added, callback notification is
# removed.
# 
# 2     10/24/08 3:05p Olegi
# 
# 1     5/16/08 12:12p Olegi
# First check-in.
# 
#***********************************************************************

all: USBINT13

USBINT13 : $(BUILD_DIR)\usbint13.mak USBI13

$(BUILD_DIR)\usbint13.mak: $(UINT13_DIR)\usbint13.cif $(UINT13_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CIF2MAK_DEFAULTS) $(UINT13_DIR)\usbint13.cif

USBI13: $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\usbint13.mak all\
		GUID=4C006CD9-19BA-4617-8483-609194A1ACFC\
		ENTRY_POINT=UsbInt13EntryPoint\
		TYPE=BS_DRIVER\
        "CFLAGS=$(CFLAGS) /I$(USBRT_DIR)"\
		COMPRESS=1\
		DEPEX1=$(UINT13_DIR)\usbint13.dxs \

$(BUILD_DIR)\UsbBbs.obj: $(UINT13_DIR)\$(@B).c
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(UINT13_DIR)\$(@B).c

CORE_DXE_LIBBin : $(BUILD_DIR)\UsbBbs.obj

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
