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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DbgrX64Lib/DbgrX64Lib.mak 3     4/20/11 8:59a Sudhirv $
#
# $Revision: 3 $
#
# $Date: 4/20/11 8:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DbgrX64Lib/DbgrX64Lib.mak $
# 
# 3     4/20/11 8:59a Sudhirv
# [TAG]  		EIP58619
# [Category]  	Defect
# [Severity]  	Major
# [Symptom]  	Statuscode 16 and 17 have build errors with USBRedirection
# [RootCause]  	StatuscodeRuntimeBin added after Statuscode_15 was having
# build errors in accessing Dbgrx64 lib functions.
# [Solution]  	StatusCodeRuntimeBin build support with DbgrX64Lib.lib
# [Files]  		DbgrX64Lib.mak
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 2     7/13/09 2:44p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:46p Sudhirv
# Restructure Binaries Created
# 
# 1     5/01/09 7:48p Madhans
# AMIDebug Rx Module. Intial Checkin.
# 
# 1     4/29/09 7:51a Sudhirv
# AMI Debug Rx module created
# 
# 2     6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 1     1/22/07 4:14p Madhans
# 1.04.0002 Binary Version.
# 
# 2     1/05/07 1:05p Ashrafj
# Latest version 1.04.0001 Beta
# Known issues from previous 1.04.000 Beta release has been fixed.
# 
# 1     12/26/06 7:09p Ashrafj
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
# Name:	DbgrX64Lib.mak
#
# Description:	Common library to support the porting of Debugger to 
#				support EFIx64
#
#<AMI_FHDR_END>
#**********************************************************************

!IF "$(PROCESSOR)"=="x64"
PeiDbgDbgrx64Bin : $(DbgrX64_DIR)\DbgrX64Lib.lib
PeiDbgXportx64Bin : $(DbgrX64_DIR)\DbgrX64Lib.lib
PeiDbgDxeCpuLibBin : $(DbgrX64_DIR)\DbgrX64Lib.lib
#AMIDebuggerBin  : $(DbgrX64_DIR)\DbgrX64Lib.lib
IsaSerialDbgBin : $(DbgrX64_DIR)\DbgrX64Lib.lib
PeiDbgStatusCodeLibBin : $(DbgrX64_DIR)\DbgrX64Lib.lib
AMITransportBin : $(DbgrX64_DIR)\DbgrX64Lib.lib
CORE_DXEBin : $(DbgrX64_DIR)\DbgrX64Lib.lib
#EIP 58619 - Building issue between UsbRedirection and StatusCode modules (16-17) on HuronRiver project
StatusCodeRuntimeBin : $(DbgrX64_DIR)\DbgrX64Lib.lib
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

