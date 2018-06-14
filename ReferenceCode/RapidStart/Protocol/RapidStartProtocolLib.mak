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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartProtocolLib/RapidStartProtocolLib.mak 1     4/19/12 8:12a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 4/19/12 8:12a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartProtocolLib/RapidStartProtocolLib.mak $
# 
# 1     4/19/12 8:12a Yurenlai
# Initial check in.
#
#*************************************************************************

all : RapidStartProtocolLib

$(BUILD_DIR)\RapidStartProtocolLib.lib : RapidStartProtocolLib

RapidStartProtocolLib : $(BUILD_DIR)\RapidStartProtocolLib.mak RapidStartProtocolLibBin

$(BUILD_DIR)\RapidStartProtocolLib.mak : $(RapidStartProtocolLib_DIR)\$(@B).cif $(RapidStartProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RapidStartProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\RapidStartProtocolLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(MISCFRAMEWORK_INCLUDES) $(EdkIIGlueLib_INCLUDES)" \
		TYPE=LIBRARY

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
