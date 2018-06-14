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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgIDT.mak 2     7/17/09 7:15p Madhans $
#
# $Revision: 2 $
#
# $Date: 7/17/09 7:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgIDT.mak $
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
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
# Name:	PeiDbgIDT.mak
#
# Description:	Makefile of pei idt module
#
#<AMI_FHDR_END>
#**********************************************************************
all : PeiDbgIDT

PEI_DBGIDT_BUILD_DIR=$(PeiDbgIDT_DIR)\IDT

PEIDBGIDT_OBJECTS = \
$(PeiDbgIDT_DIR)\IDT\emptyidt.obj

PeiDbgIDT : $(BUILD_DIR)\PeiDbgIDT.mak  PeiDbgIDTBin

$(BUILD_DIR)\PeiDbgIDT.mak : $(PeiDbgIDT_DIR)\$(@B).cif $(PeiDbgIDT_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDbgIDT_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiDbgIDTBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgIDT.mak all\
		GUID=811B4F4D-FB0B-4008-A42B-E551FD4A0F28\
		ENTRY_POINT=SetUpIDT\
		TYPE=PEIM \
		COMPRESS=0\
		"OBJECTS="\
		PRECOMPILED_OBJS=\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"CFLAGS=$(PEI_DBG_CFLAGS) /I$(PeiAMIDebugRx_DIR)\INC"


!IF "$(REDIRECTION_ONLY_MODE)" == "1"
PeiDbgIDTBin : $(PEIDBGIDT_OBJECTS)
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
