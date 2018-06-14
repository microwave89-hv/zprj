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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DebuggerLib/DebuggerLib.mak 4     3/16/11 4:42p Sudhirv $
#
# $Revision: 4 $
#
# $Date: 3/16/11 4:42p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/LIBS/DebuggerLib/DebuggerLib.mak $
# 
# 4     3/16/11 4:42p Sudhirv
# Changes to Support Older Core before 4.6.5.0
# 
# 3     3/09/11 8:16a Sudhirv
# EIP 53658 - AMIDebugRx\Debugger support for PI 1.1
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 2     7/13/09 2:45p Sudhirv
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
# 4     12/12/08 5:14p Madhans
# USB Redirecion Module.
# 
# 3     9/07/07 11:14a Madhans
# 1.07.0008 Eng Release
# 
# 2     6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 1     3/10/07 2:37p Madhans
# For 1.05.binary Release.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	DebuggerLib.mak
#
# Description:	Library to send Ld image notifications to PEI debugger 
#
#<AMI_FHDR_END>
#**********************************************************************

!IFDEF PI_SPECIFICATION_VERSION
!IF $(PI_SPECIFICATION_VERSION)>=0x00010000

CORE_PEIBin : $(DebuggerLib_DIR)\DebuggerLib_PI_1_1.lib

PeiDebugSupportBin : $(DebuggerLib_DIR)\DebuggerLib_PI_1_1.lib

!IF "$(x64_BUILD)"!="1"
CORE_DXEBin : $(DebuggerLib_DIR)\DebuggerLib_PI_1_1.lib

!ELSE
CORE_DXEBin : $(DebuggerLib_DIR)\DebuggerLibX64_PI_1_1.lib


!ENDIF

!ELSE
CORE_PEIBin : $(DebuggerLib_DIR)\DebuggerLib.lib

#!IF "$(DbgPortStatusRedirectionOnly_SUPPORT)" != "1"
PeiDebugSupportBin : $(DebuggerLib_DIR)\DebuggerLib.lib

!IF "$(x64_BUILD)"!="1"
CORE_DXEBin : $(DebuggerLib_DIR)\DebuggerLib.lib

!ELSE
CORE_DXEBin : $(DebuggerLib_DIR)\DebuggerLibX64.lib


!ENDIF
!ENDIF
!ELSE

CORE_PEIBin : $(DebuggerLib_DIR)\DebuggerLib.lib

#!IF "$(DbgPortStatusRedirectionOnly_SUPPORT)" != "1"
PeiDebugSupportBin : $(DebuggerLib_DIR)\DebuggerLib.lib

!IF "$(x64_BUILD)"!="1"
CORE_DXEBin : $(DebuggerLib_DIR)\DebuggerLib.lib

!ELSE
CORE_DXEBin : $(DebuggerLib_DIR)\DebuggerLibX64.lib


!ENDIF
#!ENDIF
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
