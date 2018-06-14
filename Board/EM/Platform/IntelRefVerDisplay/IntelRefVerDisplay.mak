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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelRefVerDisplay/IntelRefVerDisplay.mak 4     6/13/12 8:51a Yurenlai $
#
# $Revision: 4 $
#
# $Date: 6/13/12 8:51a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelRefVerDisplay/IntelRefVerDisplay.mak $
# 
# 4     6/13/12 8:51a Yurenlai
# [TAG]         None
# [Description] 01. Implement Intel Rapid Start Technology RC version
# info.
#               02. Remove DPTF and TxT RefCode version in setup, because
# they are not separate components.
# [Files]       IntelRefVerDisplay.mak, IntelRefVerDisplay.sd,
# IntelRefVerDisplay.uni, IntelRefVerSetup.c
# 
# 3     4/25/12 1:22p Yurenlai
# [TAG]         None
# [Category]    Improvement
# [Description] Corrected Setup RC Version info.
# [Files]       IntelRefVerDisplay.mak, IntelRefVerSetup.c, AcpiAsl.sdl
# 
# 2     2/24/12 1:27a Yurenlai
# Initial IntelRefVerDisplay midule part.
# 
# 1     2/09/12 12:39a Yurenlai
# Initial check in.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	IntelRefVerDisplay.mak
#
# Description: MAK file for the IntelRefVerDisplay module	
#
#<AMI_FHDR_END>
#*************************************************************************
All : IntelRefVerDisplay

IntelRefVerDisplay : $(BUILD_DIR)\IntelRefVerDisplay.mak

SetupSdbs : $(BUILD_DIR)\IntelRefVerDisplay.sdb

$(BUILD_DIR)\IntelRefVerDisplay.sdb : $(IntelRefVerDisplay_DIR)\$(@B).sd $(IntelRefVerDisplay_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(IntelRefVerDisplay_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(IntelRefVerDisplay_DIR)\$(@B).sd

$(BUILD_DIR)\IntelRefVerDisplay.mak : $(IntelRefVerDisplay_DIR)\$(@B).cif $(IntelRefVerDisplay_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(IntelRefVerDisplay_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelRefVerSetup_INCLUDES= \
!if "$(INTEL_CPURC_SUPPORT)"=="1"
  /I$(CpuProtocolLib_DIR)\
!endif
  /I$(INTEL_SA_PROTOCOL_LIB_DIR)\
  /I$(INTEL_PCH_PROTOCOL_LIB_DIR)\
  /I$(AcpiProtocolLib_DIR)\
!if "$(iME_SUPPORT)"=="1"
  /I$(MeProtocolLib_DIR)\
!endif
!if "$(IntelTXT_SUPPORT)"=="1"
  /I$(TxtProtocolLib_DIR)\
!endif
!if "$(DigitalThermalSensor_SUPPORT)"=="1"
  /I$(DtsProtocolLib_DIR)\
!endif
!if "$(RapidStart_SUPPORT)"=="1"
  /I$(RapidStartProtocolLib_DIR)\
!endif

SetupBin : $(BUILD_DIR)\IntelRefVerSetup.obj

$(BUILD_DIR)\IntelRefVerSetup.obj : $(PROJECT_DIR)\$(IntelRefVerDisplay_DIR)\IntelRefVerSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) $(IntelRefVerSetup_INCLUDES) /Fo$(BUILD_DIR)\ $(IntelRefVerDisplay_DIR)\IntelRefVerSetup.c
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