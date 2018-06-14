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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetupInfo/PlatformSetupInfo.mak 2     4/05/12 7:14a Yurenlai $
#
# $Revision: 2 $
#
# $Date: 4/05/12 7:14a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/PlatformSetupInfo/PlatformSetupInfo.mak $
# 
# 2     4/05/12 7:14a Yurenlai
# [TAG]         None
# [Category]    Improvement
# [Severity]    Important
# [Description] Fixed building error for Intel System Agent
# Label:"4.6.5.3_Intel_SA-RC_055_004".
# [Files]       PlatformSetupInfo.c, PlatformSetupInfo.mak
# 
# 1     2/24/12 1:02a Yurenlai
# Add PlatformSetupInfo module part.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	PlatformSetupInfo.mak
#
# Description: MAK file for the PlatformSetupInfo module	
#
#<AMI_FHDR_END>
#*************************************************************************
All : PlatformSetupInfo

PlatformSetupInfo : $(BUILD_DIR)\PlatformSetupInfo.mak

SetupSdbs : $(BUILD_DIR)\PlatformSetupInfo.sdb

$(BUILD_DIR)\PlatformSetupInfo.sdb : $(PlatformSetupInfo_DIR)\$(@B).sd $(PlatformSetupInfo_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(PlatformSetupInfo_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(PlatformSetupInfo_DIR)\$(@B).sd

$(BUILD_DIR)\PlatformSetupInfo.mak : $(PlatformSetupInfo_DIR)\$(@B).cif $(PlatformSetupInfo_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(PlatformSetupInfo_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PlatformSetupInfo_INCLUDES= \
  $(INTEL_PCH_INCLUDES)\
!if "$(IntelTXT_SUPPORT)"=="1"
  $(TXT_INCLUDES)\
!endif
  $(PROJECT_CPU_INCLUDES)\

SetupBin : $(BUILD_DIR)\PlatformSetupInfo.obj

$(BUILD_DIR)\PlatformSetupInfo.obj : $(PROJECT_DIR)\$(PlatformSetupInfo_DIR)\PlatformSetupInfo.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) $(PlatformSetupInfo_INCLUDES) /Fo$(BUILD_DIR)\ $(PlatformSetupInfo_DIR)\PlatformSetupInfo.c
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