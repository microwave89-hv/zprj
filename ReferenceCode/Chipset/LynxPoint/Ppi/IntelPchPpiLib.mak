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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IntelPchPpiLib/IntelPchPpiLib.mak 1     2/08/12 8:58a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:58a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IntelPchPpiLib/IntelPchPpiLib.mak $
# 
# 1     2/08/12 8:58a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

# MAK file for the ModulePart:IntelPchPpiLib
all : IntelPchPpiLib

$(IntelPchPpiLib_LIB) : IntelPchPpiLib

IntelPchPpiLib : $(BUILD_DIR)\IntelPchPpiLib.mak IntelPchPpiLibBin

$(BUILD_DIR)\IntelPchPpiLib.mak : $(IntelPchPpiLib_DIR)\$(@B).cif $(IntelPchPpiLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(IntelPchPpiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelPchPpiLib_INCLUDES =\
            $(EDK_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

IntelPchPpiLibBin : 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\IntelPchPpiLib.mak all\
            "MY_INCLUDES=$(IntelPchPpiLib_INCLUDES)" \
            TYPE=PEI_LIBRARY LIBRARIES= \
            LIBRARY_NAME=$(IntelPchPpiLib_LIB)
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
