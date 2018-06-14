#//*****************************************************************//
#//*****************************************************************//
#//*****************************************************************//
#//**                                                             **//
#//**         (C)Copyright 2009, American Megatrends, Inc.        **//
#//**                                                             **//
#//**                     All Rights Reserved.                    **//
#//**                                                             **//
#//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
#//**                                                             **//
#//**                     Phone (770)-246-8600                    **//
#//**                                                             **//
#//*****************************************************************//
#//*****************************************************************//
#//*****************************************************************//
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DbgrUsbCableSelectLib.mak 2     7/17/09 7:15p Madhans $
#
# $Revision: 2 $
#
# $Date: 7/17/09 7:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DbgrUsbCableSelectLib.mak $
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 2     7/13/09 2:43p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:46p Sudhirv
# Restructure Binaries Created
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
# 
# 2     5/01/09 7:44p Madhans
# 
# 1     4/29/09 7:51a Sudhirv
# AMI Debug Rx module created
# 
# 9     12/12/08 5:13p Madhans
# USB Redirecion Module.
# 
# 7     9/07/07 12:07a Madhans
# 1.07.0008 Eng Release
# 
# 6     6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 5     3/12/07 6:19p Madhans
# !!!coding standards!!!!
# 
# 4     1/22/07 4:14p Madhans
# 1.04.0002 Binary Version.
# 
# 3     12/26/06 7:07p Ashrafj
# Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
# Host.zip).
# PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
# Support added for StatusCode redirection without Debug feature enabled
# (not working if DXE only and x64 is enabled).
# Plus, some new SDL tokens defined to support the Aptio 4.5 build
# process in Debug or non-debug mode.
# All the components of Debugger eModule in source form.
# 
# 2     9/22/06 11:33a Ashrafj
# Removed the previous specific changes made to support the new USB
# cable, by means of SDL token.
# New changes made to support the new USB cables by means of providing
# the USB Standard Device Requests command functions in USB Transport
# modules, so that the porting engineer can use those in
# DbgrUsbCableSelectLib library sources.
# 
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	DbgrUsbCableSelectLib.mak
#
# Description:	Makefile of Debugger Usb Cable select lib
#
#<AMI_FHDR_END>
#**********************************************************************

!IF "$(USB_DEBUG_TRANSPORT)" == "1"
AMITransportBin : $(AMIDXELIB) $(BUILD_DIR)\DbgrUsbCableSelectLib.lib

!IF "$(PeiDebugger_SUPPORT)"=="1"
!IF "$(x64_BUILD)"!="1"
PeiDbgXportBin : $(BUILD_DIR)\DbgrUsbCableSelectLib.lib
!ELSE
PeiDbgXportBin : $(BUILD_DIR)\PeiDbgrUsbCableSelectLib.lib
PeiDbgXportx64Bin : $(BUILD_DIR)\DbgrUsbCableSelectLib.lib
!ENDIF
!ENDIF

!ENDIF

$(BUILD_DIR)\DbgrUsbCableSelectLib.lib : DbgrUsbCableSelectLib

DbgrUsbCableSelectLib : $(BUILD_DIR)\DbgrUsbCableSelectLib.mak DbgrUsbCableSelectLibBin

$(BUILD_DIR)\DbgrUsbCableSelectLib.mak : $(DbgrUsbCableSelectLib_DIR)\$(@B).cif $(DbgrUsbCableSelectLib_DIR)\DbgrUsbCableSelectLib.mak $(BUILD_RULES)
	$(CIF2MAK) $(DbgrUsbCableSelectLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!IF "$(x64_BUILD)"!="1"

DbgrUsbCableSelectLibBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\DbgrUsbCableSelectLib.mak all\
		TYPE=LIBRARY \
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT"
!ELSE

$(BUILD_DIR)\PeiDbgrUsbCableSelectLib.lib : DbgrUsbCableSelectLib

DbgrUsbCableSelectLibBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\DbgrUsbCableSelectLib.mak all\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\DbgrUsbCableSelectLib.lib\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT"
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\DbgrUsbCableSelectLib.mak all\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(BUILD_DIR)\PeiDbgrUsbCableSelectLib.lib\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT"
!ENDIF

#//*****************************************************************//
#//*****************************************************************//
#//*****************************************************************//
#//**                                                             **//
#//**         (C)Copyright 2009, American Megatrends, Inc.        **//
#//**                                                             **//
#//**                     All Rights Reserved.                    **//
#//**                                                             **//
#//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
#//**                                                             **//
#//**                     Phone (770)-246-8600                    **//
#//**                                                             **//
#//*****************************************************************//
#//*****************************************************************//
#//*****************************************************************//
