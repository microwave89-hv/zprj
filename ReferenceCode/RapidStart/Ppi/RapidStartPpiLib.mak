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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartPpiLib/RapidStartPpiLib.mak 1     4/19/12 8:10a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 4/19/12 8:10a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartPpiLib/RapidStartPpiLib.mak $
# 
# 1     4/19/12 8:10a Yurenlai
# Initial check in.
#
#*************************************************************************

all : RapidStartPpiLib

$(RapidStartPpiLib_LIB) : RapidStartPpiLib

RapidStartPpiLib : $(BUILD_DIR)\RapidStartPpiLib.mak RapidStartPpiLibBin

$(BUILD_DIR)\RapidStartPpiLib.mak : $(RapidStartPpiLib_DIR)\$(@B).cif $(RapidStartPpiLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(RapidStartPpiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartPpiLib_INCLUDES =\
            $(EDK_INCLUDES)\

RapidStartPpiLibBin : 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\RapidStartPpiLib.mak all\
            "MY_INCLUDES=$(RapidStartPpiLib_INCLUDES)" \
            TYPE=PEI_LIBRARY
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