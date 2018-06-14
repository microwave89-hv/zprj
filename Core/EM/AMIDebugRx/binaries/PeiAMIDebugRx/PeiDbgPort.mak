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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgPort.mak 6     6/28/11 7:53a Sudhirv $
#
# $Revision: 6 $
#
# $Date: 6/28/11 7:53a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgPort.mak $
# 
# 6     6/28/11 7:53a Sudhirv
# [TAG]  		EIP63446
# [Category]  	Defect.
# [Description]   To avoid build errors with Core 4.6.5.1_2 and
# AMIDebugRx Bin  	
# [Files]  		PEIDbgPort.mak 
# 
# 5     3/24/11 7:00p Madhans
# To remove /Fc from the CFLAGS
# 
# 4     2/22/10 4:17p Madhans
# 1.32
# 
# 5     2/20/10 11:44a Madhans
# if PeiDebuggerS3Initialize is found then use that in S3 case. 
# If not found try to use defaultSioinit function(SIOPEIDBG_Initialize)
# if it found in PeiDebuggerInitialize 
# 
# 4     10/19/09 7:25a Sudhirv
# Updated to Reduce S3 Resume wake time and fix SIO Issue
# 
# 3     9/30/09 3:05p Sudhirv
# For Debugger 1.31.0023_PreAlpha
# 
# 2     7/13/09 2:48p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:46p Sudhirv
# Restructure Binaries Created
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
# 
# 2     5/01/09 7:45p Madhans
# 
# 1     4/29/09 7:52a Sudhirv
# AMI Debug Rx module created
# 
# 5     12/12/08 5:42p Madhans
# USB Redirection Module
# 
# 3     6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 2     3/12/07 6:19p Madhans
# !!!coding standards!!!!
# 
# 1     1/22/07 4:12p Madhans
# 1.04.0002 Binary Version.
# 
# 5     12/26/06 7:07p Ashrafj
# Support added to support the Aptio 4.5 x64 EFI BIOS (use latest
# Host.zip).
# PEI Debugger in FV_MAIN (use new PEIDEBUGFIXUP).
# Support added for StatusCode redirection without Debug feature enabled
# (not working if DXE only and x64 is enabled).
# Plus, some new SDL tokens defined to support the Aptio 4.5 build
# process in Debug or non-debug mode.
# All the components of Debugger eModule in source form.
# 
# 4     4/21/06 12:38p Ashrafj
# Code cleanup.
# 
# 3     3/15/06 7:41p Ashrafj
# Modfication done to provide the Binary integration for Aptio 4
# projects.
# 
# 2     12/22/05 12:42p Ashrafj
# Changes done to support the complete Chipset template porting.
# 
# To use this changes, make sure to have the latest Board components of
# CPU, SB and SIO, which have the following ELINKS ported:
# - SBPEIDBG_Initialize,
# - CPUPEIDBG_Initialize,
# - SIOPEIDBG_Initialize,
# - SBPEIDBG_InitUsbEhci.
# 
# 1     11/29/05 6:04p Markw
# 
# 2     10/20/05 10:05a Felixp
# missing dependencies added
# 
# 1     10/19/05 10:54a Felixp
# 
# 1     10/19/05 10:44a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiDbgPort.mak
#
# Description:	Makefile of Pei debugPort module
#
#<AMI_FHDR_END>
#**********************************************************************
all : PeiDbgPort

PEIDBGPORT_OBJECTS = \
$(BUILD_DIR)\$(PEI_DBG_PORT_DIR)\PeiDbgPort.obj \

PEIDBGPORTUSB_OBJECTS = \
$(PEI_DBG_PORT_DIR)\PeiDbgPortUSB.obj

#if PeiDebuggerS3Initialize is found then use that in S3 case. 
#If not found try to use defaultSioinit function(SIOPEIDBG_Initialize) if it found in PeiDebuggerInitialize 
!IF "$(PeiDebuggerS3Initialize)" == ""
!IF "$(PeiDebuggerInitialize:SIOPEIDBG_Initialize,=)" != "$(PeiDebuggerInitialize)"
DbgRxSioS3Initialize = SIOPEIDBG_Initialize,
!ENDIF
!ELSE
DbgRxSioS3Initialize = $(PeiDebuggerS3Initialize)
!ENDIF

PeiDbgPort : $(BUILD_DIR)\PeiDbgPort.mak PeiDbgPortBin

$(BUILD_DIR)\PeiDbgPort.mak : $(PEI_DBG_PORT_DIR)\$(@B).cif $(PEI_DBG_PORT_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PEI_DBG_PORT_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiDbgPortBin : $(AMICSPLib) $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgPort.mak all\
		GUID=EB7D9740-DB60-45c2-A7A0-C2714EF4EB56\
		ENTRY_POINT=InitMain\
		TYPE=PEIM \
		COMPRESS=0\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		EXT_HEADERS=$(BUILD_DIR)\token.h\
		"OBJECTS=$(PEIDBGPORT_OBJECTS)"\
		"INIT_LIST=$(IsDbgS3)"\
		PRECOMPILED_OBJS=\
		"CFLAGS= $(GLOBAL_DEFINES) $(PEI_DBG_CFLAGS) /I$(PEI_DBG_PORT_DIR)\INC /D\"PEI_DBG_INIT_LIST=$(PeiDebuggerInitialize)\" /D\"PEI_DBG_S3_INIT_LIST=$(DbgRxSioS3Initialize)\" /DUSB_DEBUGGER /D\"IS_S3=$(IsDbgS3)\" "

!IF "$(USB_DEBUG_TRANSPORT)" == "1"
PeiDbgPortBin : $(PEIDBGPORTUSB_OBJECTS)
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
