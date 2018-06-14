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
# $Header: /Alaska/BIN/Core/Runtime/Runtime.mak 8     6/24/09 4:28p Robert $
#
# $Revision: 8 $
#
# $Date: 6/24/09 4:28p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Runtime/Runtime.mak $
# 
# 8     6/24/09 4:28p Robert
# updated file description
# 
# 7     5/14/09 9:38a Felixp
# New feature: SMM version of Runtime Services
# Runtime driver is updated to install SMM version of the runtime
# services table.
# NVRAM driver is updated to populate SMM runtime table 
#   with the pointers to SMM version of variable services.
# 
# 6     5/01/09 6:11p Felixp
# Bug fix(EIP 19816). $(AMICSPLib) is linked with Runtime module
# (Used to be linked with NVRAM library that caused problems on systems
# without Core Sources).
# 
# 5     8/24/06 9:17a Felixp
# Preliminary x64 support (work in progress)
# 
# 4     12/02/05 11:16a Felixp
# @set INCLUDE=%%INCLUDE%% removed since it's not needed.
# 
# 3     6/16/05 10:48a Felixp
# NVRAMTokens.c replaced with Tokens.c
# 
# 2     2/11/05 5:48p Felixp
# Binary files organization improved:
#   - extra layer of sub-component removed
#   - macros initialization moved to SDL tokens to eliminate undefined
# macros situation
#   - debug and release binaries have different names now (workaround for
# VeB limitation)
#   - binaries reside in the component home directory (eliminates
# hardcoded paths)
# 
# 3     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Runtime.mak
#
# Description:	
#   This file contains the build commands for the Runtime binary 
#   components.
#
#<AMI_FHDR_END>
#**********************************************************************
all : RUNTIME

RUNTIME : CORE_PEI $(BUILD_DIR)\RUNTIME.mak RUNTIMEBin

$(BUILD_DIR)\RUNTIME.mak : $(RUNTIME_DIR)\$(@B).cif $(RUNTIME_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RUNTIME_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RUNTIMEBin : $(AMIDXELIB) $(Runtime_LIB) $(FLASHLIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\RUNTIME.mak all\
		GUID=CBC59C4A-383A-41eb-A8EE-4498AEA567E4 \
		ENTRY_POINT=RuntimeEntry \
		TYPE=RT_DRIVER LIBRARIES= \
		COMPRESS=1\
		"INIT_LIST=$(RuntimeInitialize)"\
        "INIT_LIST2=$(RuntimeSmmInitialize)"
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