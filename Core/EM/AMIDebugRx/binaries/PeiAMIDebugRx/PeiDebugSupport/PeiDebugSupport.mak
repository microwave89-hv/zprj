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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDebugSupport/PeiDebugSupport.mak 4     3/16/11 4:44p Sudhirv $
#
# $Revision: 4 $
#
# $Date: 3/16/11 4:44p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDebugSupport/PeiDebugSupport.mak $
# 
# 4     3/16/11 4:44p Sudhirv
# Changes to Support Older Cores before 4.6.5.0
# 
# 3     3/09/11 8:23a Sudhirv
# EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 2     7/13/09 2:50p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:46p Sudhirv
# Restructure Binaries Created
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
# 
# 2     5/01/09 7:47p Madhans
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
# 4     6/06/07 6:13p Madhans
# Leave the Peidbgsupport in PE format
# 
# 3     3/12/07 6:20p Madhans
# !!!coding standards!!!!
# 
# 2     3/10/07 2:40p Madhans
# For 1.05.binary Release.
# 
# 1     1/22/07 4:12p Madhans
# 1.04.0002 Binary Version.
# 
# 6     12/26/06 7:07p Ashrafj
# Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
# Host.zip).
# PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
# Support added for StatusCode redirection without Debug feature enabled
# (not working if DXE only and x64 is enabled).
# Plus, some new SDL tokens defined to support the Aptio 4.5 build
# process in Debug or non-debug mode.
# All the components of Debugger eModule in source form.
# 
# 5     12/15/06 4:51p Ashrafj
# Updated the Debugger eModule sources to support the CAR base address
# define in the APtio 4.5 project SDL token itself.
# Move the PEI Debugger modules (except PeiDebugSupport) from FV_BB to
# FV_MAIN to avoid insufficient space problem in PEI. Note that for this
# changes the Aptio 4.5 project should have the new version 0.4
# PEIDEBUGFIXUP utility build tool with CORE.MAK modified (Refer Santa
# Rosa project).
# 
# 4     7/05/06 1:39p Ashrafj
# Include path updated
# 
# 3     3/15/06 7:48p Ashrafj
# Modfication done to provide the Binary integration for Aptio 4
# projects.
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
# Name:	PeiDebugSupport.mak
#
# Description:	Makefile of Pei DebugSupport PEI Module
#
#<AMI_FHDR_END>
#**********************************************************************

PEI_DBGSUPPORT_CFLAGS = $(PEI_DBG_CFLAGS) /I$(PeiAMIDebugRx_DIR)\INC

PEI_DBGSUPPORT_BUILD_DIR=$(PeiDebugSupport_DIR)

PEI_DBGSUPPORT_OBJECTS =\
!IFDEF PI_SPECIFICATION_VERSION
!IF $(PI_SPECIFICATION_VERSION)>=0x00010000
$(PEI_DBGSUPPORT_BUILD_DIR)\peidebugsupport_PI_1_1.obj \
$(PEI_DBGSUPPORT_BUILD_DIR)\relocdbg_PI_1_1.obj \
!ELSE
$(PEI_DBGSUPPORT_BUILD_DIR)\peidebugsupport.obj \
$(PEI_DBGSUPPORT_BUILD_DIR)\relocdbg.obj \
!ENDIF
!ELSE
$(PEI_DBGSUPPORT_BUILD_DIR)\peidebugsupport.obj \
$(PEI_DBGSUPPORT_BUILD_DIR)\relocdbg.obj \
!ENDIF
$(PEI_DBGSUPPORT_BUILD_DIR)\AmiDebugPort.obj \
$(BUILD_DIR)\$(PeiDebugSupport_DIR)\DbgrHelp.obj \
!IF "$(USB_DEBUG_TRANSPORT)" == "1"
$(PEI_DBGSUPPORT_BUILD_DIR)\DebugPortUsb.obj \
!ENDIF
!IF "$(REDIRECTION_ONLY_MODE)" == "1"
$(PEI_DBGSUPPORT_BUILD_DIR)\Emptyrelocdbgidt.obj \
!ENDIF
!IF "$(x64_BUILD)"=="1"
!IFDEF PI_SPECIFICATION_VERSION
!IF $(PI_SPECIFICATION_VERSION)>=0x00010000
$(PEI_DBGSUPPORT_BUILD_DIR)\PeiDbgSupportX64_PI_1_1.obj \
!ELSE
$(PEI_DBGSUPPORT_BUILD_DIR)\PeiDbgSupportX64.obj \
!ENDIF
!ELSE
$(PEI_DBGSUPPORT_BUILD_DIR)\PeiDbgSupportX64.obj \
!ENDIF
!IF "$(USB_DEBUG_TRANSPORT)" == "1"
$(PEI_DBGSUPPORT_BUILD_DIR)\CopyDbgXPortUsb.obj \
!ENDIF
!IF "$(REDIRECTION_ONLY_MODE)" == "1"
$(PEI_DBGSUPPORT_BUILD_DIR)\emptyX64idt.obj \
!ENDIF
!ELSE
$(PEI_DBGSUPPORT_BUILD_DIR)\EmptyNotify.obj \
!ENDIF


all : PeiDebugSupport 

PeiDebugSupport : $(BUILD_DIR)\PeiDebugSupport.mak PeiDebugSupportBin

$(BUILD_DIR)\PeiDebugSupport.mak : $(PeiDebugSupport_DIR)\$(@B).cif $(PeiDebugSupport_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDebugSupport_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiDebugSupportBin : $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDebugSupport.mak all\
		GUID=A47438D5-94E9-49b3-BC31-7E6BC9363814\
		ENTRY_POINT=PeiDebugSupportEntry \
		TYPE=PEIM \
        PE_IMAGE_FORMAT=1\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		COMPRESS=0\
		PRECOMPILED_OBJS=\
		"OBJECTS=$(PEI_DBGSUPPORT_OBJECTS)"\
		"CFLAGS = $(PEI_DBGSUPPORT_CFLAGS)"

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
