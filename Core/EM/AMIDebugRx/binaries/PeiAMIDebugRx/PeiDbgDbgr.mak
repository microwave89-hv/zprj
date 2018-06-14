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
# $Header: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgDbgr.mak 2     7/17/09 7:15p Madhans $
#
# $Revision: 2 $
#
# $Date: 7/17/09 7:15p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMIDebugRx/binaries/PeiAMIDebugRx/PeiDbgDbgr.mak $
# 
# 2     7/17/09 7:15p Madhans
# DebugRx 1.30.0022
# 
# 4     7/15/09 5:56p Madhans
# X64 Support and clean up.
# 
# 3     7/13/09 2:48p Sudhirv
# Updated with Coding Standards
# 
# 2     7/08/09 9:34a Sudhirv
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
# 6     12/12/08 5:42p Madhans
# USB Redirection Module
# 
# 4     6/13/07 3:38p Madhans
# Copyright Year updated.
# 
# 3     6/06/07 12:30p Madhans
# Debugger 1.06
# 
# 2     3/12/07 6:19p Madhans
# !!!coding standards!!!!
# 
# 1     1/22/07 4:12p Madhans
# 1.04.0002 Binary Version.
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
# Name:	PeiDbgDbgr.mak
#
# Description:	Make file pei debugger
#
#<AMI_FHDR_END>
#**********************************************************************
all : PeiDbgDbgr

PEIDBGDBGR_BUILD_DIR=$(PeiDbgDbgr_DIR)\DBGR

PEIDBGDBGR_OBJECTS = \
$(BUILD_DIR)\$(PeiDbgDbgr_DIR)\DBGR\dbgrhdr.obj

PEIDBGMIN_OBJECTS = \
$(PEIDBGDBGR_BUILD_DIR)\mindbgr.obj

PEIDBGDBGRLIB = $(BUILD_DIR)\PeiDbgDbgr.lib

PeiDbgDbgr : $(BUILD_DIR)\PeiDbgDbgr.mak $(PEIDBGDBGRLIB) PeiDbgDbgrBin

$(BUILD_DIR)\PeiDbgDbgr.mak : $(PeiDbgDbgr_DIR)\$(@B).cif $(PeiDbgDbgr_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiDbgDbgr_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(PEIDBGDBGRLIB) :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgDbgr.mak all\
		TYPE=PEI_LIBRARY\
		LIBRARY_NAME=$(PEIDBGDBGRLIB)\
		"CFLAGS=$(PEI_DBG_CFLAGS) /DRELOCATE /I$(PeiAMIDebugRx_DIR)\INC /I$(Foundation_DIR)"\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak"

PeiDbgDbgrBin : 
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\PeiDbgDbgr.mak all\
		GUID=4AAAAE15-5AEB-4c11-B91D-A3966AC04847\
		ENTRY_POINT=InitDbgLayer\
		TYPE=PEIM \
		PE_IMAGE_FORMAT=1\
		COMPRESS=0\
		"OBJECTS="\
		PRECOMPILED_OBJS=\
		"EXT_HEADERS=$(BUILD_DIR)\Token.mak" \
		"CFLAGS=$(PEI_DBG_CFLAGS) /DRELOCATE /I$(PeiDbgDbgr_DIR)\INC"

PeiDbgDbgrBin : $(PEIDBGDBGR_OBJECTS)

!IF "$(REDIRECTION_ONLY_MODE)" == "1"
PeiDbgDbgrBin : $(PEIDBGMIN_OBJECTS)
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
