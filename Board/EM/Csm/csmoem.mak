#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CSM/Generic/OEM Hooks/csmoem.mak 6     1/12/10 11:50a Olegi $
#
# $Revision: 6 $
#
# $Date: 1/12/10 11:50a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CSM/Generic/OEM Hooks/csmoem.mak $
# 
# 6     1/12/10 11:50a Olegi
# Copyright message updated.
# 
# 5     4/01/09 1:05p Olegi
# 
# 4     12/04/07 11:06a Olegi
# 
# 3     5/24/07 12:13p Fasihm
# Updated code to match the code review standards.
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		CSMOEM.MAK
#
# Description:	CSM OEM implementation makefile
#
#<AMI_FHDR_END>
#**********************************************************************

$(CSM_OEM_BIN_FILE): $(BUILD_DIR)\csmoem.exe
	exe2bin $*.exe $@

# Note: in the following rule OUTPOST file has to go first
$(BUILD_DIR)\csmoem.exe: $(BUILD_DIR)\CSMKRNL.OBJ $(CSM_OEMINT_OBJS) $(CSM_OEM16_OBJS) $(BUILD_DIR)\oem16sig.obj $(CSM_OEMSIG_OBJS)
	$(ASMLINK) @<<
$(**: = +^
),
$*.exe,
$*.map,,,
<<

#$(BUILD_DIR)\CSMKRNL.OBJ: $(BUILD_DIR)\CSMKRNL.ASM
#	@copy $(CSM_OEM_DIR)\mbiosequ.equ $(BUILD_DIR)
#	@copy $(CSM_OEM_DIR)\mbiosmac.mac $(BUILD_DIR)
#	$(ASM) /c /Fo$(BUILD_DIR)\ $(BUILD_DIR)\CSMKRNL.ASM

$(BUILD_DIR)\CSMKRNL.OBJ: $(CSM_OEM_DIR)\CSMKRNL.ASM
	$(ASM) /c /Fo$(BUILD_DIR)\ $(CSM_OEM_DIR)\CSMKRNL.ASM

$(BUILD_DIR)\oem16sig.obj: $(CSM_OEM_DIR)\oem16sig.asm
	$(ASM) /c /Fo$(BUILD_DIR)\ $(CSM_OEM_DIR)\oem16sig.asm

all: $(CSM_OEM_BIN_FILE)

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
