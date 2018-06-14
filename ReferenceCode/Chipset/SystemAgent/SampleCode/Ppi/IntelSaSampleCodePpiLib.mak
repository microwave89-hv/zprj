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
# $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Refcode/SaSampleCode/IntelSaSampleCodePpiLib/IntelSaSampleCodePpiLib.mak 1     2/08/12 4:53a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 4:53a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Refcode/SaSampleCode/IntelSaSampleCodePpiLib/IntelSaSampleCodePpiLib.mak $
# 
# 1     2/08/12 4:53a Yurenlai
# Intel Haswell/NB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	IntelSaSampleCodePpiLib_LIB.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : IntelSaSampleCodePpiLib

$(BUILD_DIR)\IntelSaSampleCodePpiLib.lib : IntelSaSampleCodePpiLib

IntelSaSampleCodePpiLib : $(BUILD_DIR)\IntelSaSampleCodePpiLib.mak IntelSaSampleCodePpiLibBin

$(BUILD_DIR)\IntelSaSampleCodePpiLib.mak : $(IntelSaSampleCodePpiLib_DIR)\$(@B).cif $(IntelSaSampleCodePpiLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IntelSaSampleCodePpiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelSaSampleCodePpiLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\IntelSaSampleCodePpiLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(INTEL_MCH_INCLUDES) /I$(INTEL_SYSTEM_AGENT_DIR)\SampleCode" \
		TYPE=PEI_LIBRARY \
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