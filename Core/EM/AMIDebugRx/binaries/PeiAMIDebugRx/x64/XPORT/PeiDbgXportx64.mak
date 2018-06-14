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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/x64/XPORT/PeiDbgXportx64.mak 3     7/17/09 7:15p Madhans $
#
# $Revision: 3 $
#
# $Date: 7/17/09 7:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/x64/XPORT/PeiDbgXportx64.mak $
# 
# 3     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 3     7/15/09 5:56p Madhans
# X64 Support and clean up.
# 
# 2     7/13/09 2:52p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:47p Sudhirv
# Restructure Binaries Created
# 
# 2     5/04/09 11:35a Madhans
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
# 
# 2     5/01/09 7:47p Madhans
# 
# 1     4/29/09 7:52a Sudhirv
# AMI Debug Rx module created
# 
# 4     6/13/07 3:17p Madhans
# Copyright Year updated.
# 
# 3     1/22/07 11:43a Madhans
# Modification made for Binary Release 1.04.0003.
# 
# 1     12/26/06 7:17p Ashrafj
# Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
# Host.zip).
# PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
# Support added for StatusCode redirection without Debug feature enabled
# (not working if DXE only and x64 is enabled).
# Plus, some new SDL tokens defined to support the Aptio 4.5 build
# process in Debug or non-debug mode.
# All the components of Debugger eModule in source form.
# 
# 1     12/26/06 7:10p Ashrafj
# Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
# Host.zip).
# PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
# Support added for StatusCode redirection without Debug feature enabled
# (not working if DXE only and x64 is enabled).
# Plus, some new SDL tokens defined to support the Aptio 4.5 build
# process in Debug or non-debug mode.
# All the components of Debugger eModule in source form.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiDbgXportx64.mak
#
# Description:	Makefile of Xport64 module
#
#<AMI_FHDR_END>
#**********************************************************************


!IF "$(REDIRECTION_ONLY_MODE)" == "1"
PEIDBGXPORTx64_BUILD_DIR=$(PeiDbgXportx64_DIR)\REDIR
!ELSE
PEIDBGXPORTx64_BUILD_DIR=$(PeiDbgXportx64_DIR)\DBGR
!ENDIF

PEIDBGXPORTX64_OBJS=\
$(PEIDBGXPORTx64_BUILD_DIR)\transport.obj\
$(PEIDBGXPORTx64_BUILD_DIR)\xp_layer.obj\
$(BUILD_DIR)\$(PeiDbgXportx64_DIR)\XportHdr.obj\

PEIDBGXPORTx64_USB_OBJECTS =\
$(PEIDBGXPORTx64_BUILD_DIR)\usb_acc.obj\
$(PEIDBGXPORTx64_BUILD_DIR)\usb_xp.obj\
$(PEIDBGXPORTx64_BUILD_DIR)\UsbDebugPort.obj

!INCLUDE $(BUILD_DIR)\TimeStamp.mak

all : PeiDbgXportx64

PeiDbgXportx64 : $(BUILD_DIR)\PeiDbgXportx64.mak PeiDbgXportx64Bin

$(BUILD_DIR)\PeiDbgXportx64.mak : $(PeiDbgXportx64_DIR)\$(@B).cif $(PeiDbgXportx64_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDbgXportx64_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiDbgXportx64Bin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgXportx64.mak all\
		GUID=511D0266-F2E0-4df8-AE3A-FDB98523BFB9\
		ENTRY_POINT=InitXLayer\
		TYPE=BS_DRIVER \
		COMPRESS=1\
		"OBJECTS=$(PEIDBGXPORTX64_OBJS)"\
		"CFLAGS=$(PEI_DBG_CFLAGS) /DRELOCATE /I$(PeiDbgDbgr_DIR)\INC /I$(DbgrX64_DIR) "

!IF "$(USB_DEBUG_TRANSPORT)" == "1"
PeiDbgXportx64Bin : $(PEIDBGXPORTx64_USB_OBJECTS)
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
