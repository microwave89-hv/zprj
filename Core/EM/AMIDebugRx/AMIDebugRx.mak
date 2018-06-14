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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/AMIDebugRx.mak 3     8/28/12 8:59a Sudhirv $Revision: 1 $
#
# $Date: 8/28/12 8:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/AMIDebugRx.mak $(BUILD_DIR)\AMIDebugRx.mak
# 
# 3     8/28/12 8:59a Sudhirv
# Updated for AMI Debug for UEFI 2.04.0073 Label
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 2     7/13/09 2:41p Sudhirv
# Updated with Coding Standards
# 
# 1     7/07/09 4:45p Sudhirv
# Restructure Binaries Created
# 
# 2     4/29/09 8:05a Sudhirv
# Updated
# 
# 1     4/29/09 7:51a Sudhirv
# AMI Debug Rx module created
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AMIDebugRx_mak
#
# Description:	Make file for the USB Redirection component
#
#<AMI_FHDR_END>
#**********************************************************************
!IF "$(AMI_DEBUGGER_SUPPORT)"!="1" && "$(USB_REDIRECTION_SUPPORT)"!="1" && "$(AMIDEBUG_RX_SUPPORT)"=="1" && "$(PeiDebugger_SUPPORT)"=="0"
!ERROR AMIDEBUG_RX_SUPPORT requires the PeiDebugger_SUPPORT SDL token to be 1.\
 AMIDebugRx requires the PeiDebugger_SUPPORT SDL token to be enabled.
!ENDIF

!IF "$(AMI_DEBUGGER_SUPPORT)"!="1" && "$(USB_REDIRECTION_SUPPORT)"!="1" && "$(AMIDEBUG_RX_SUPPORT)"=="1" && "$(USB_DEBUG_TRANSPORT)"=="0"
!ERROR AMIDEBUG_RX_SUPPORT requires the USB_DEBUG_TRANSPORT SDL token to be 1.\
 AMIDebugRx requires the USB_DEBUG_TRANSPORT SDL token to be enabled.
!ENDIF

all : AMIDebugRx

AMIDebugRx : $(BUILD_DIR)\AMIDebugRx.mak

$(BUILD_DIR)\AMIDebugRx.mak : $(AMI_DebugRx_DIR)\$(@B).cif $(AMI_DebugRx_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMI_DebugRx_DIR)\DebugRx.cif $(CIF2MAK_DEFAULTS)

SetupSdbs : AMIDebugRxSDB

AMIDebugRxSDB : $(BUILD_DIR)\AMIDebugRx.mak 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\AMIDebugRx.mak all\
	TYPE=SDB NAME=AMIDebugRx STRING_CONSUMERS=$(AMI_DebugRx_DIR)\AMIDebugRx.sd

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
