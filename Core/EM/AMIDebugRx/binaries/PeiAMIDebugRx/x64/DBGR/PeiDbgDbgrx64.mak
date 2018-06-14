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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/x64/DBGR/PeiDbgDbgrx64.mak 2     7/17/09 7:15p Madhans $
#
# $Revision: 2 $
#
# $Date: 7/17/09 7:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/x64/DBGR/PeiDbgDbgrx64.mak $
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 3     7/15/09 5:56p Madhans
# X64 Support and clean up.
# 
# 2     7/13/09 2:51p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:46p Sudhirv
# Restructure Binaries Created
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
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
# 2     3/12/07 6:20p Madhans
# !!!coding standards!!!!
# 
# 1     1/22/07 4:12p Madhans
# 1.04.0002 Binary Version.
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
# Name:	PeiDbgDbgrx64.mak
#
# Description:	Makefile of Debugger x64 Module that is loaded by Peidebugsupport
#
#<AMI_FHDR_END>
#**********************************************************************
all : PeiDbgDbgrx64

PeiDbgDbgrx64 : $(BUILD_DIR)\PeiDbgDbgrx64.mak PeiDbgDbgrx64Bin

$(BUILD_DIR)\PeiDbgDbgrx64.mak : $(PeiDbgDbgrx64_DIR)\$(@B).cif $(PeiDbgDbgrx64_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDbgDbgrx64_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PEIDBGDBGR_OBJS = \
$(PeiDbgDbgrx64_DIR)\mindbgr.obj 


PeiDbgDbgrx64Bin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgDbgrx64.mak all\
		GUID=C253ED0A-C48B-4ee3-A65E-75F61F3AD251\
		ENTRY_POINT=InitDbgLayer\
		TYPE=BS_DRIVER \
		PRECOMPILED_OBJS=\
		COMPRESS=1\
		"OBJECTS="\

!IF "$(REDIRECTION_ONLY_MODE)" == "1"
PeiDbgDbgrx64Bin : $(PEIDBGDBGR_OBJS)
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
