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
# $Header: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicy.mak 5     12/18/12 11:03p Josephlin $
#
# $Revision: 5 $
#
# $Date: 12/18/12 11:03p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/AmiGopPolicy/AmiGopPolicy.mak $
# 
# 5     12/18/12 11:03p Josephlin
# [TAG]  		EIP108311
# [Category]  	Improvement
# [Description]  	Create eLINK "OemGopEdidOverrideGetEdidList" for easy
# to implement EdidOverrideProtocol in project.
# [Files]  		AmiGopPolicy.c
# AmiGopPolicy.sdl
# AmiGopPolicy.mak
# AmiGopPolicyLib.c
# 
# 4     7/26/12 7:30a Josephlin
# Update File Header.
# 
# 3     7/23/12 5:20a Josephlin
# Fixed build error occured in VIA platform issue.
# 
# 2     7/23/12 3:32a Josephlin
# 1. Added input argument SetupData for eLink OemGopSwitchHookList.
# 2. Created token "AmiGopPolicySetupFile" and "AmiGopPolicySetupString"
# for override sd and uni file.
# 3. Rename AmiGopPolicyCallback to AmiGopSwitchCallback in case user
# confuse.
# 
# 1     6/29/12 3:44a Josephlin
# [TAG]  		EIP91970
# [Category]  	New Feature
# [Description]  	Initial Release for Display Switch with UEFI GOP driver
# support.
# [Files]  		AmiGopPolicy.cif
# AmiGopPolicy.c
# AmiGopPolicy.h
# AmiGopPolicy.mak
# AmiGopPolicy.sd
# AmiGopPolicy.sdl
# AmiGopPolicy.uni
# AmiGopPolicyLib.c
# AmiGopPolicySetup.c
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:         AmiGopPolicy.mak
#
# Description:  Make file that builds AmiGopPolicy components and link
#               them to respective binary.
#
#<AMI_FHDR_END>
#**********************************************************************

all : AmiGopPolicy

AmiGopPolicy : $(BUILD_DIR)\AmiGopPolicy.mak

#----------------------------------------------------------------------
#           Generic eModule dependencies
#----------------------------------------------------------------------
$(BUILD_DIR)\AmiGopPolicy.mak : $(AMIGOPPOLICY_DIR)\AmiGopPolicy.cif $(AMIGOPPOLICY_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(AMIGOPPOLICY_DIR)\AmiGopPolicy.cif $(CIF2MAK_DEFAULTS)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\AmiGopPolicy.obj \
$(BUILD_DIR)\AmiGopPolicyLib.obj

{$(AMIGOPPOLICY_DIR)}.c{$(BUILD_DIR)}.obj::
    $(CC) $(CFLAGS) \
    /D\"OEM_GOP_DEVICE_CHECK_LIST=$(OemGopDeviceCheckList)\"\
    /D\"OEM_GOP_SWITCH_HOOK_LIST=$(OemGopSwitchHookList)\"\
    /D\"OEM_GOP_EDID_OVERRIDE_GET_EDID_LIST=$(OemGopEdidOverrideGetEdidList)\"\
    /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\AmiGopPolicy.obj : $(AMIGOPPOLICY_DIR)\AmiGopPolicy.c
$(BUILD_DIR)\AmiGopPolicyLib.obj : $(AMIGOPPOLICY_DIR)\AmiGopPolicyLib.c

#----------------------------------------------------------------------
#           Create eModule Setup Screens
#----------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\AmiGopPolicy.sdb
SetupBin : $(BUILD_DIR)\AmiGopPolicySetup.obj $(AMICSPLib)

$(BUILD_DIR)\AmiGopPolicy.sdb : $(AmiGopPolicySetupData) $(AmiGopPolicySetupString)
    $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\AmiGopPolicy.sdb $(AmiGopPolicySetupString)
    $(STRGATHER) -scan -db $(BUILD_DIR)\AmiGopPolicy.sdb -od $(BUILD_DIR)\AmiGopPolicy.sdb $(AmiGopPolicySetupData)

$(BUILD_DIR)\AmiGopPolicySetup.obj : $(AMIGOPPOLICY_DIR)\AmiGopPolicySetup.c $(BUILD_DIR)\SetupStrTokens.h
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(AMIGOPPOLICY_DIR)\AmiGopPolicySetup.c

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