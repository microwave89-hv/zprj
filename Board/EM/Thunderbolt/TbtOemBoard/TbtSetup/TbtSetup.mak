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
#**********************************************************************
#
# $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtSetup/TbtSetup.mak 1     1/10/13 4:57a Barretlin $
#
# $Revision: 1 $
#
# $Date: 1/10/13 4:57a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtSetup/TbtSetup.mak $
# 
# 1     1/10/13 4:57a Barretlin
# Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
# Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
# 
# 2     12/12/12 4:47a Barretlin
# [TAG]  		None
# [Category]  	New Feature
# [Description]  	Add Thunderbolt TSE Setup Reset Hook
# [Files]  		TbtSetup.sdl TbtSetup.mak TbtSetup.cif TbtSetupReset.c
# 
# 1     12/08/11 4:09a Wesleychen
# Thunderbolt eModule initially releases.
# 
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            Tbt Setup.mak
#
# Description:     Makfile for TBT Setup module.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
All : TbtSetup

TbtSetup : $(BUILD_DIR)\TbtSetup.mak

SetupSdbs : $(BUILD_DIR)\TbtSetup.sdb

$(BUILD_DIR)\TbtSetup.sdb : $(TbtSetup_DIR)\$(@B).sd $(TbtSetup_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(TbtSetup_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(TbtSetup_DIR)\$(@B).sd

$(BUILD_DIR)\TbtSetup.mak : $(TbtSetup_DIR)\$(@B).cif $(TbtSetup_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(TbtSetup_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SetupBin : $(BUILD_DIR)\TbtSetup.obj

$(BUILD_DIR)\TbtSetup.obj : $(TbtSetup_DIR)\TbtSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) $(TBT_OEMBOARD_INCLUDES) /Fo$(BUILD_DIR)\ $(TbtSetup_DIR)\TbtSetup.c

#----------------------------------------------------------------------------
#       Create Thunderbolt Setup TSE Reset Hook
#----------------------------------------------------------------------------
AMITSEBin :  $(BUILD_DIR)\TbtSetupReset.obj

$(BUILD_DIR)\TbtSetupReset.obj : $(TbtSetup_DIR)\TbtSetupReset.c $(AMICSPLib)
		$(CC) $(CFLAGS) $(INTEL_PCH_INCLUDES) $(TBT_OEMBOARD_INCLUDES) /Fo$(BUILD_DIR)\ $(TbtSetup_DIR)\TbtSetupReset.c 

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