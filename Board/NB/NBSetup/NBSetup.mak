
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
# $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSetup/NBSetup.mak 2     4/05/12 2:25a Yurenlai $
#
# $Revision: 2 $
#
# $Date: 4/05/12 2:25a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NBSetup/NBSetup.mak $
# 
# 2     4/05/12 2:25a Yurenlai
# [TAG]         None
# [Category]    Improvement
# [Severity]    Important
# [Description] Fixed token RESET_RUNTIME_SERVICES_SUPPORT = 1 building
# error.
# [Files]       NBSetup.mak
# 
# 1     2/08/12 4:33a Yurenlai
# Intel Haswell/NB eChipset initially releases.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         NBSetup.mak
#
# Description:  This make file builds north bridge Setup
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************
All : NBSetup

NBSetup : $(BUILD_DIR)\NBSetup.mak

SetupSdbs : $(BUILD_DIR)\NB.sdb

$(BUILD_DIR)\NB.sdb : $(NBSetup_DIR)\$(@B).sd $(NBSetup_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(NBSetup_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(NBSetup_DIR)\$(@B).sd

$(BUILD_DIR)\NBSetup.mak : $(NBSetup_DIR)\$(@B).cif $(NBSetup_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(NBSetup_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SetupBin : $(BUILD_DIR)\NBSetup.obj

$(BUILD_DIR)\NBSetup.obj : $(NBSetup_DIR)\NBSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) $(INTEL_MCH_INCLUDES) /Fo$(BUILD_DIR)\ $(NBSetup_DIR)\NBSetup.c

AMITSEBin :  $(BUILD_DIR)\NBSetupReset.obj $(AMICSPLib)

$(BUILD_DIR)\NBSetupReset.obj : $(NBSetup_DIR)\NBSetupReset.c
		$(CC) $(CFLAGS) $(INTEL_PCH_INCLUDES) /Fo$(BUILD_DIR)\ $(NBSetup_DIR)\NBSetupReset.c 

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
