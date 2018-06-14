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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/PeiDbgStatusCodeLib.mak 5     3/14/11 9:15p Madhans $
#
# $Revision: 5 $
#
# $Date: 3/14/11 9:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/PeiDbgStatusCodeLib.mak $
# 
# 5     3/14/11 9:15p Madhans
# To contribute to CSPLib a function to know if DebugRx is connected or
# Not connected.
# 
# 4     9/30/09 8:00p Madhans
# Updated for 1.31. Refer release notes.
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 6     7/16/09 6:35p Sudhirv
# Updated the Path to avoid build errors with GENERIC_CABLE_SUPPORT
# 
# 5     7/16/09 5:20p Madhans
# Fix for Build error in Peidebugger Off
# 
# 4     7/16/09 3:07p Madhans
# To fix the Serial Debugger issuel and To do cleanup.
# 
# 3     7/15/09 5:56p Madhans
# X64 Support and clean up.
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
# 3     5/01/09 7:44p Madhans
# 
# 2     4/30/09 8:52a Sudhirv
# Added DummySerialIo for AMI Debug Rx
# 
# 1     4/29/09 7:51a Sudhirv
# AMI Debug Rx module created
# 
# 15    12/12/08 5:13p Madhans
# USB Redirecion Module.
# 
# 13    5/21/08 12:26p Madhans
# To Support New Status Code Lib changes.
# 
# 12    10/26/07 5:03p Madhans
# For 1.20.0011 Release
# 
# 10    6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 9     4/05/07 6:36p Madhans
# Debugger 1.05.0005
# 
# 8     3/12/07 6:19p Madhans
# !!!coding standards!!!!
# 
# 7     3/10/07 2:36p Madhans
# For 1.05.binary Release.
# 
# 6     2/28/07 7:57p Madhans
# Dbgrhelp.obj kept as source.
# 
# 5     1/25/07 10:33a Madhans
# PLATFORM_DIR symbol name canged to _DBG_PLATFORM_DIR as it confilicts
# with SantaROSA.
# 
# 4     1/22/07 4:46p Madhans
# Fixed the build issue.
# 
# 3     1/22/07 4:14p Madhans
# 1.04.0002 Binary Version.
# 
# 7     1/05/07 1:05p Ashrafj
# Latest version 1.04.0001 Beta
# Known issues from previous 1.04.000 Beta release has been fixed.
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
# 5     6/30/06 12:12p Ashrafj
# Modified to support the redirection of StatusCode debug messages
# through DXE debugger, which was previously possible only if PEI Debug
# support is enabled.
# The PeiDbgStatusCodeLib component's ELINK is now enabled for DXE
# debugger, without PEI Debug support. This means that StatusCode
# messages will not cross over the wire until DXE debugger gets control
# of the target.
# 
# 4     6/14/06 7:33p Ashrafj
# Minor build error fix - added dependency of AMIDXELIB
# 
# 3     3/15/06 7:41p Ashrafj
# Modfication done to provide the Binary integration for Aptio 4
# projects.
# 
# 2     10/20/05 10:07a Felixp
# missing dependencies added
# 
# 1     10/19/05 10:54a Felixp
# 
# 1     10/19/05 10:44a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiDbgStatusCodeLib.mak
#
# Description:	Makefile of pei debugger status code lib
#
#<AMI_FHDR_END>
#**********************************************************************
STSCODELIB_CFLAGS = /DALASKA_SUPPORT /I $(AMI_DebugRx_DIR)\binaries\PeiAMIDebugRx\INC

BUILD_DBGSTATUSCODE_DIR=$(BUILD_DIR)\$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib

!IF "$(x64_BUILD)"=="1"
_DBG_PLATFORM_DIR=x64
!ELSE
_DBG_PLATFORM_DIR=ia32
!ENDIF

!IF "$(REDIRECTION_ONLY_MODE)" == "1"
!IF "$(PeiDebugger_SUPPORT)"=="1"
DBGSTATUSCODE_OBJS= \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\PeiDbgStatusCode.obj \
$(BUILD_DBGSTATUSCODE_DIR)\DbgrHelp.obj \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\GetDbgInterfaceDxe.obj \
!IF "$(CONSOLE_REDIRECTION_SUPPORT)" != "1" || "$(REDIRECTION_ONLY_MODE)" != "1"
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\DummyAmiSerialIO.obj
!ENDIF

IA32_DBGSTATUSCODE_OBJS= \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\IA32\PeiDbgStatusCode.obj  \
$(BUILD_DIR)\IA32\$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\DbgrHelp.obj \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\IA32\GetDbgInterfacePei.obj

!ELSE
DBGSTATUSCODE_OBJS= \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\AMIDbgPortStatusCodeDxe.obj\
!IF "$(CONSOLE_REDIRECTION_SUPPORT)" != "1" || "$(REDIRECTION_ONLY_MODE)" != "1"
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\DummyAmiSerialIO.obj
!ENDIF

IA32_DBGSTATUSCODE_OBJS= \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\IA32\AMIDbgPortStatusCodePei.obj  \
!ENDIF

!ELSE
DBGSTATUSCODE_OBJS= \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\PeiDbgStatusCode.obj \
$(BUILD_DBGSTATUSCODE_DIR)\DbgrHelp.obj \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\GetDbgInterfaceDxe.obj \
!IF "$(CONSOLE_REDIRECTION_SUPPORT)" != "1" || "$(REDIRECTION_ONLY_MODE)" != "1"
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\$(_DBG_PLATFORM_DIR)\DummyAmiSerialIO.obj
!ENDIF

IA32_DBGSTATUSCODE_OBJS= \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\IA32\PeiDbgStatusCode.obj  \
$(BUILD_DIR)\IA32\$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\DbgrHelp.obj \
$(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\IA32\GetDbgInterfacePei.obj
!ENDIF

PeiDbgStatusCodeLib : $(BUILD_DIR)\PeiDbgStatusCodeLibBin.mak PeiDbgStatusCodeLibBin DxeDbgStatusCodeLibBin

$(BUILD_DIR)\PeiDbgStatusCodeLibBin.mak : $(PeiDbgStatusCodeLib_DIR)\PeiDbgStatusCodeLibBin.cif $(PeiDbgStatusCodeLib_DIR)\PeiDbgStatusCodeLib.mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDbgStatusCodeLib_DIR)\PeiDbgStatusCodeLibBin.cif $(CIF2MAK_DEFAULTS)

!IF "$(x64_BUILD)"!="1"

PEIDBGSTATUSCODELIB = $(BUILD_DIR)\PeiDbgStatusCodeLib.lib

PEIDBGSTATUSCODEPEILIB = $(BUILD_DIR)\PeiDbgStatusCodePeiLib.lib

StatusCodeBin : $(PEIDBGSTATUSCODELIB) $(AMIDXELIB)
StatusCodePeiBin: $(PEIDBGSTATUSCODEPEILIB)
StatusCodeDxeBin: $(PEIDBGSTATUSCODELIB) 

CORE_DXEBin: $(PEIDBGSTATUSCODELIB) $(AMIDXELIB)

$(PEIDBGSTATUSCODELIB) $(PEIDBGSTATUSCODEPEILIB) : PeiDbgStatusCodeLib 

PeiDbgStatusCodeLibBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgStatusCodeLibBin.mak all\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(PEIDBGSTATUSCODEPEILIB)\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"OBJECTS=$(IA32_DBGSTATUSCODE_OBJS)"\
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT /DPEIDBG_BUILD_ONLY $(STSCODELIB_CFLAGS)"

DxeDbgStatusCodeLibBin :
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgStatusCodeLibBin.mak all\
		TYPE=LIBRARY LIBRARY_NAME=$(PEIDBGSTATUSCODELIB)\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"OBJECTS=$(DBGSTATUSCODE_OBJS)"\
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT $(STSCODELIB_CFLAGS)"


!ELSE

PEIDBGSTATUSCODELIB = $(BUILD_DIR)\PeiDbgStatusCodeLib.lib 
PEIDBGSTATUSCODELIBX64 = $(BUILD_DIR)\PeiDbgStatusCodeLibX64.lib

StatusCodeBin : $(PEIDBGSTATUSCODELIB)
StatusCodeBin : $(PEIDBGSTATUSCODELIBX64)
StatusCodePeiBin : $(PEIDBGSTATUSCODELIB)
StatusCodeDxeBin: $(PEIDBGSTATUSCODELIBX64)

$(PEIDBGSTATUSCODELIB) $(PEIDBGSTATUSCODELIBX64) : PeiDbgStatusCodeLib

PeiDbgStatusCodeLibBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgStatusCodeLibBin.mak all\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		TYPE=PEI_LIBRARY LIBRARY_NAME=$(PEIDBGSTATUSCODELIB)\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"OBJECTS=$(IA32_DBGSTATUSCODE_OBJS)"\
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT /DPEIDBG_BUILD_ONLY $(STSCODELIB_CFLAGS)"

DxeDbgStatusCodeLibBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgStatusCodeLibBin.mak all\
		TYPE=LIBRARY LIBRARY_NAME=$(PEIDBGSTATUSCODELIBX64)\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"OBJECTS=$(DBGSTATUSCODE_OBJS)"\
		"CFLAGS = $(CFLAGS) /DALASKA_SUPPORT $(STSCODELIB_CFLAGS)"

!ENDIF

AMICSPLibBin : $(BUILD_DIR)\HostConStatus.obj
$(BUILD_DIR)\HostConStatus.obj : $(BUILD_DIR)\Token.mak $(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\HostConStatus.c
    $(CC) $(C_FLAGS) $(STSCODELIB_CFLAGS) /DALASKA_SUPPORT  /c $(PeiDbgStatusCodeLib_DIR)\StatusCodeLib\HostConStatus.c /Fo$@ /FR$(@R).SBR


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
