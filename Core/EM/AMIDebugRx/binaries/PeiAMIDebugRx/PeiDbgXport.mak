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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgXport.mak 3     7/17/09 7:15p Madhans $
#
# $Revision: 3 $
#
# $Date: 7/17/09 7:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgXport.mak $
# 
# 3     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 3     7/13/09 2:48p Sudhirv
# Updated with Coding Standards
# 
# 2     7/10/09 11:44a Sudhirv
# Updated
# 
# 1     7/07/09 4:46p Sudhirv
# Restructure Binaries Created
# 
# 2     5/05/09 8:05p Madhans
# Use the timestamp.h instead of timstamp.mak to avoid the octal issues.
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
# 
# 2     5/01/09 7:45p Madhans
# 
# 1     4/29/09 7:52a Sudhirv
# AMI Debug Rx module created
# 
# 7     12/12/08 5:42p Madhans
# USB Redirection Module
# 
# 5     6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 4     6/06/07 12:30p Madhans
# Debugger 1.06
# 
# 3     3/12/07 6:19p Madhans
# !!!coding standards!!!!
# 
# 2     1/25/07 3:07p Madhans
# xporthdr.c added as source
# 
# 1     1/22/07 4:12p Madhans
# 1.04.0002 Binary Version.
# 
# 6     12/15/06 4:51p Ashrafj
# Updated the Debugger eModule sources to support the CAR base address
# define in the APtio 4.5 project SDL token itself.
# Move the PEI Debugger modules (except PeiDebugSupport) from FV_BB to
# FV_MAIN to avoid insufficient space problem in PEI. Note that for this
# changes the Aptio 4.5 project should have the new version 0.4
# PEIDEBUGFIXUP utility build tool with CORE.MAK modified (Refer Santa
# Rosa project).
# 
# 5     3/15/06 7:43p Ashrafj
# Modfication done to provide the Binary integration for Aptio 4
# projects.
# 
# 4     12/12/05 3:22p Ashrafj
# Compiler optimization disable for Serial Port PEI Debug Transport.
# 
# 3     10/20/05 10:51a Ashrafj
# Compiler flags reset to original.
# 
# 2     10/20/05 10:06a Felixp
# missing dependencies added
# 
# 1     10/19/05 10:54a Felixp
# 
# 1     10/19/05 10:44a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiDbgXport.mak
#
# Description:	Makefile of Pei debugger Xport module
#
#<AMI_FHDR_END>
#**********************************************************************
all : PeiDbgXport

!IF "$(REDIRECTION_ONLY_MODE)" == "1"
PEIDBGXPORT_BUILD_DIR=$(PeiDbgXport_DIR)\XPORT\REDIR\
!ELSE
PEIDBGXPORT_BUILD_DIR=$(PeiDbgXport_DIR)\XPORT\DBGR\
!ENDIF

PEIDBGXPORT_OBJECTS = \
$(BUILD_DIR)\$(PeiDbgXport_DIR)\XPORT\XportHdr.obj\
$(PEIDBGXPORT_BUILD_DIR)\xp_layer.obj\
$(PEIDBGXPORT_BUILD_DIR)\transport.obj\

!IF "$(USB_DEBUG_TRANSPORT)" == "1"
PEIDBGXPORT_USB_OBJECTS = \
$(PEIDBGXPORT_BUILD_DIR)\UsbDebugPort.obj\
$(PEIDBGXPORT_BUILD_DIR)\usb_acc.obj\
$(PEIDBGXPORT_BUILD_DIR)\usb_xp.obj
!ENDIF

PeiDbgXport : $(BUILD_DIR)\PeiDbgXport.mak PeiDbgXportBin

$(BUILD_DIR)\PeiDbgXport.mak : $(PeiDbgXport_DIR)\$(@B).cif $(PeiDbgXport_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDbgXport_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiDbgXportBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgXport.mak all\
		GUID=C7E8BB67-1C3F-41ba-820F-3D0E9C365042\
		ENTRY_POINT=InitXLayer\
		TYPE=PEIM \
        PE_IMAGE_FORMAT=1\
		COMPRESS=0\
		"EXT_HEADERS=$(PeiDbgXport_DIR)\PeiDbgXport.mak $(BUILD_DIR)\Token.mak" \
		"OBJECTS=$(PEIDBGXPORT_OBJECTS)"\
		PRECOMPILED_OBJS=\
		"CFLAGS=$(PEI_DBG_CFLAGS) /DRELOCATE /I$(PeiAMIDebugRx_DIR)\INC"


!IF "$(USB_DEBUG_TRANSPORT)" == "1"
PeiDbgXportBin : $(PEIDBGXPORT_USB_OBJECTS)
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
