#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Core/CORE_DXE/CORE_DXE.mak 14    9/29/10 9:19a Felixp $
#
# $Revision: 14 $
#
# $Date: 9/29/10 9:19a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/CORE_DXE/CORE_DXE.mak $
# 
# 14    9/29/10 9:19a Felixp
# Enhancement(EIP 39464) : Implementation of the BdsEntry function is
# changed. 
# The BdsEntry is now a dispatching function that calls a collection of
# functions 
# formed by the BDS_CONTROL_FLOW eLink.
# 
# 13    8/26/10 12:52p Felixp
# Spelling error in one of the identifiers in BootOptioneLinks.h
# 
# 12    6/29/10 11:03p Felixp
# New Boot Options Maintenance Infrastructure.
# See AMI_Aptio_4.x_Boot_Options_Maintenance_Infrastructure_Porting_Guide
# _NDA.doc for details.
# 
# 11    2/23/10 9:19p Felixp
# Support of the BDS String Override via BDS_SDBS eLink (EIP 32696).
# 
# 10    11/19/09 12:55p Felixp
# Entry point name has changed (from DxeCoreEntry to DxeMain).
# 
# 9     6/08/06 7:13p Sivagarn
# - Updated file header
# - Fixed EIP 7580 issue. Search for (EIP7580) for changes
# 
# 8     3/13/06 1:44a Felixp
# BdsInitialize eLink created
# 
# 7     12/02/05 11:16a Felixp
# @set INCLUDE=%%INCLUDE%% removed since it's not needed.
# 
# 6     6/20/05 12:01p Felixp
# 
# 5     5/24/05 2:48p Felixp
# support for SUPPORTED_LANGUAGES
# 
# 4     4/12/05 2:59p Felixp
# 
# 3     4/08/05 7:39a Felixp
# Boot Menu implemented
# 
# 2     2/11/05 5:46p Felixp
# Binary files organization improved:
#   - extra layer of sub-component removed
#   - macros initialization moved to SDL tokens to eliminate undefined
# macros situation
#   - debug and release binaries have different names now (workaround for
# VeB limitation)
# 
# 1     1/28/05 12:44p Felixp
# 
# 4     1/25/05 3:27p Felixp
# compression enabled;
# dependency from token.h added
# 
# 3     1/21/05 12:01p Felixp
# BootScriptSave moved to CORE_DXE
# 
# 2     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 5     11/10/04 5:18p Felixp
# reference to EfiDriverLib.lib removed
# 
# 25    4/07/04 12:46a Felixp
# REAL PLATFORM DEBUGGING (lots of bug fixes)
# 
# 20    3/28/04 2:11p Felixp
# 1. PE Loader and some other commonly used code moved to the Library
# 2. Warnings fixed (from now on warning will be treated as error)
# 
# 19    3/27/04 9:23a Felixp
# 
# 18    3/25/04 3:47p Robert
# added Misc.obj to and removed reset.obj from the MAK file
# 
# 8     2/06/04 2:46a Felixp
#  - Support for VC6 tools
#  - bug fixes
# - component AddOn added
# 
# 7     2/04/04 6:50p Yakovlevs
# 
# 6     1/20/04 11:32a Felixp
# Memory Services added (at the moment they are non-buildable)
# 
# 5     1/18/04 8:33a Felixp
# From now on, OBJ files are created in a component specific subdirectory
# of $(BUILD_DIR)
# 
# 2     1/05/04 6:09p Robert
# 
# 1     12/05/03 4:15p Felixp
# 
#**********************************************************************

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
# Name:         CORE_DXE.MAK
#
# Description:  This NMAKE script file builds the CORE_DXE driver
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>

all : CORE_DXE

CORE_DXE : $(BUILD_DIR)\CORE_DXE.mak $(BUILD_DIR)\BootOptioneLinks.h CORE_DXEBin

$(BUILD_DIR)\CORE_DXE.mak : $(CORE_DXE_DIR)\$(@B).cif $(CORE_DXE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CORE_DXE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CORE_DXEBin : $(AMIDXELIB) $(CORE_DXE_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CORE_DXE.mak all\
		GUID=5AE3F37E-4EAE-41ae-8240-35465B5E81EB \
		ENTRY_POINT=DxeMain \
		TYPE=DXE_CORE LIBRARIES= \
		"CFLAGS=$(CFLAGS) /D\"SUPPORTED_LANGUAGES=$(SUPPORTED_LANGUAGES: =)\" /D\"SIO_DEVICE_LIST=$(DxeSioList)\" /D\"SIO_DEVICE_PTR_LIST=_AND_ $(DxeSioList: =_AND_ )\" "\
		"EXT_HEADERS=$(BUILD_DIR)\token.h $(BUILD_DIR)\BootOptioneLinks.h"\
		HAS_RESOURCES=1 COMPRESS=1\
		"INIT_LIST=$(DxeCoreInitialize)"\
		"INIT_LIST2=$(BdsEntryInitialize)"\
!IF "$(BDS_SDBS: =)"==""
        "STRGATHER_FLAGS=-db $(BUILD_DIR)\$(CORE_DXE_DIR)\Bds.sdb"\
!ELSE
        "STRGATHER_FLAGS=-db $(BUILD_DIR)\$(CORE_DXE_DIR)\Bds.sdb -db $(BDS_SDBS: = -db )"\
!ENDIF

# We are trying to convert a list of comma separated functions to a list of comma 
# separated function name strings.
# The original list of function may contain C comment blocks /* */
BDS_CONTROL_FLOW0 = $(BDS_CONTROL_FLOW: =) # remove the spaces
BDS_CONTROL_FLOW1 = $(BDS_CONTROL_FLOW0:*/,=*/) # remove commas after the comments
BDS_CONTROL_FLOW2 = $(BDS_CONTROL_FLOW1:*//*=) # merge the adjacent comments
BDS_CONTROL_FLOW3 = $(BDS_CONTROL_FLOW2:*/=*/") # add quote after the comment to begin the next string
BDS_CONTROL_FLOW4 = "$(BDS_CONTROL_FLOW3:,=",")", # add quotes before and after the commas
BDS_CONTROL_FLOW_STRINGS = $(BDS_CONTROL_FLOW4:"/*=/*) # remove quote before the comments

$(BUILD_DIR)\BootOptioneLinks.h : $(BUILD_DIR)\Token.h $(CORE_DXE_DIR)\CORE_DXE.mak
    	$(SILENT)type << >$(BUILD_DIR)\BootOptioneLinks.h
#define BOOT_OPTION_DP_MATCHING_FUNCTIONS $(BootOptionDpMatchingFunctions)
#define BOOT_OPTION_MATCHING_FUNCTIONS $(BootOptionMatchingFunctions)
#define BOOT_OPTION_BUILD_NAME_FUNCTIONS $(BootOptionBuildNameFunctions)
#define BOOT_OPTION_BUILD_FILE_PATH_FUNCTIONS $(BootOptionBuildFilePathFunctions)
#define BOOT_OPTION_BOOT_DEVICE_FILTERING_FUNCTIONS $(BootOptionBootDeviceFilteringFunctions)

#define BDS_CONTROL_FLOW $(BDS_CONTROL_FLOW)
#define BDS_CONTROL_FLOW_NAMES $(BDS_CONTROL_FLOW_STRINGS)
<<

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************