#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBSetup/SBSetup.mak 1     2/08/12 8:23a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:23a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SBSetup/SBSetup.mak $
# 
# 1     2/08/12 8:23a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         SBSetup.mak
#
# Description:  This make file builds north bridge Setup
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************
All : SBSetup

SBSetup : $(BUILD_DIR)\SBSetup.mak

SetupSdbs : $(BUILD_DIR)\SB.sdb

$(BUILD_DIR)\SB.sdb : $(SBSetup_DIR)\$(@B).sd $(SBSetup_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(SBSetup_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(SBSetup_DIR)\$(@B).sd

$(BUILD_DIR)\SBSetup.mak : $(SBSetup_DIR)\$(@B).cif $(SBSetup_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(SBSetup_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SetupBin : $(BUILD_DIR)\SBSetup.obj

$(BUILD_DIR)\SBSetup.obj : $(PROJECT_DIR)\$(SBSetup_DIR)\SBSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) $(INTEL_PCH_INCLUDES) /Fo$(BUILD_DIR)\ $(SBSetup_DIR)\SBSetup.c
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************