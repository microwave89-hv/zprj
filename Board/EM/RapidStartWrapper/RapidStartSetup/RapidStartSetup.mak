#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartSetup/RapidStartSetup.mak 3     5/03/13 2:53a Bensonlai $
#
# $Revision: 3 $
#
# $Date: 5/03/13 2:53a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartSetup/RapidStartSetup.mak $
# 
# 3     5/03/13 2:53a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	After changed the iRST status, we don't have to do a
# cold reset.
# 
# 2     1/13/13 7:49a Bensonlai
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Disabling the RapidStart while STAT mode in the IDE
# mode
# [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
# RapidStartDxePolicyInit.mak, RapidStartSetup.c, RapidStartSetup.mak,
# RapidStartSetup.sd, RapidStartSetup.sdl
# 
# 1     10/15/12 4:42a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	[Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# [Files]  		RapidStartSetup.cif
# RapidStartSetup.sdl
# RapidStartSetup.mak
# RapidStartSetup.sd
# RapidStartSetup.uni
# RapidStartSetup.c
# RapidStartSetup.h
# RapidStartSetupReset.c
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: RapidStartSetup.mak
#
# Description: Component description file for the RapidStart
#
#<AMI_FHDR_END>
#**********************************************************************

All : RapidStartSetup

RapidStartSetup : $(BUILD_DIR)\RapidStartSetup.mak

SetupSdbs : $(BUILD_DIR)\RapidStartSetup.sdb

$(BUILD_DIR)\RapidStartSetup.sdb : $(RapidStartSetup_DIR)\$(@B).sd $(RapidStartSetup_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(RapidStartSetup_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(RapidStartSetup_DIR)\$(@B).sd

$(BUILD_DIR)\RapidStartSetup.mak : $(RapidStartSetup_DIR)\$(@B).cif $(RapidStartSetup_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(RapidStartSetup_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SetupBin : $(BUILD_DIR)\RapidStartSetup.obj

$(BUILD_DIR)\RapidStartSetup.obj : $(PROJECT_DIR)\$(RapidStartSetup_DIR)\RapidStartSetup.c $(BUILD_DIR)\SetupStrTokens.h $(AMICSPLib)
	$(CC) $(CFLAGS) $(INTEL_PCH_INCLUDES) /I$(RapidStartInclude_DIR) /Fo$(BUILD_DIR)\ $(RapidStartSetup_DIR)\RapidStartSetup.c

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
