#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Core/CORE_PEI/CORE_PEI.mak 6     5/01/09 6:12p Felixp $
#
# $Revision: 6 $
#
# $Date: 5/01/09 6:12p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/CORE_PEI/CORE_PEI.mak $
# 
# 6     5/01/09 6:12p Felixp
# Bug fix(EIP 19816). $(AMICSPLib) is linked with CORE_PEI module
# (Used to be linked with NVRAM library that caused problems on systems
# without Core Sources).
# 
# 5     8/24/06 9:17a Felixp
# Preliminary x64 support (work in progress)
# 
# 4     12/02/05 11:15a Felixp
# @set INCLUDE=%%INCLUDE%% removed since it's not needed.
# 
# 3     6/16/05 10:47a Felixp
# 1. variables from NVRAMTokens.c moved to Tokens.c
# 2. PeiCoreMemoryInstalled initialization list added
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
# 3     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 1     12/23/04 9:42a Felixp
# 
# 2     11/01/04 8:06a Felixp
# 
# 1     7/12/04 6:33p Felixp
# 
# 24    3/29/04 2:32a Felixp
# 
# 23    3/28/04 2:11p Felixp
# 1. PE Loader and some other commonly used code moved to the Library
# 2. Warnings fixed (from now on warning will be treated as error)
# 
# 22    3/23/04 4:56p Felixp
# 
# 21    3/20/04 12:03p Felixp
# 
# 20    3/19/04 11:12a Robert
# 
# 19    2/19/04 10:08a Felixp
# Debugging code removed.
# 
# 18    2/10/04 1:24p Felixp
# 
# 17    2/06/04 2:46a Felixp
#  - Support for VC6 tools
#  - bug fixes
# - component AddOn added
# 
# 16    2/04/04 2:04a Felixp
# work in progress...
# 
# 15    1/28/04 3:24a Felixp
# 
# 14    1/22/04 12:47p Felixp
# 
# 13    1/19/04 4:23p Felixp
# work in progress...
# 
# 12    1/18/04 8:34a Felixp
# 1. From now on, OBJ files are created in a component specific
# subdirectory of $(BUILD_DIR)
# 2. New files added
# 
# 11    1/15/04 11:05a Felixp
# hob.c and ffs.c files added
# 
# 10    1/06/04 5:28p Yakovlevs
# 
# 9     1/06/04 4:03p Felixp
# 
# 8     1/06/04 11:26a Felixp
# 
# 7     1/02/04 5:39p Robert
# 
# 6     12/30/03 5:54p Robert
# 
# 5     12/23/03 9:34a Felixp
# dependency from the makefile added
# 
# 4     12/12/03 12:23p Felixp
# 
# 3     12/12/03 12:07p Robert
# Added Pci Cfg and Cpu Io obj references to the mak file
# 
# 2     12/12/03 11:29a Felixp
# PEICORE_OBJECTS and PEICORE_HEADERS variables created
# 
# 1     12/05/03 4:15p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Pei.mak
#
# Description:	PeiCore makefile:
#	-Builds EXE File
#	-Invokes FFS.Mak to build PeiCore.FFS
#
#<AMI_FHDR_END>
#**********************************************************************
all : CORE_PEI

CORE_PEI : $(BUILD_DIR)\CORE_PEI.mak CORE_PEIBin

$(BUILD_DIR)\CORE_PEI.mak : $(CORE_PEI_DIR)\$(@B).cif $(CORE_PEI_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CORE_PEI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CORE_PEIBin : $(AMIPEILIB) $(CORE_PEI_LIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CORE_PEI.mak all\
		GUID=92685943-D810-47ff-A112-CC8490776A1F \
		ENTRY_POINT=PeiCoreEntry \
		TYPE=PEI_CORE LIBRARIES= \
		COMPRESS=0\
		EXT_HEADERS=$(BUILD_DIR)\token.h\
		"INIT_LIST=$(PeiCoreInitialize)"\
		"INIT_LIST2=$(PeiCoreMemoryInstalled)"\
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************