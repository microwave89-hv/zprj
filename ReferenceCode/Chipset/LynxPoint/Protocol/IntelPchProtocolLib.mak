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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IntelPchProtocolLib/IntelPchProtocolLib.mak 1     2/08/12 9:01a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 9:01a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IntelPchProtocolLib/IntelPchProtocolLib.mak $
# 
# 1     2/08/12 9:01a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

# MAK file for the ModulePart:IntelPchProtocolLib
EDK : IntelPchProtocolLib

$(INTEL_PCH_PROTOCOL_LIB) : IntelPchProtocolLib

IntelPchProtocolLib : $(BUILD_DIR)\IntelPchProtocolLib.mak IntelPchProtocolLibBin

$(BUILD_DIR)\IntelPchProtocolLib.mak : $(INTEL_PCH_PROTOCOL_LIB_DIR)\$(@B).cif $(INTEL_PCH_PROTOCOL_LIB_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(INTEL_PCH_PROTOCOL_LIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelPchProtocolLib_INCLUDES =\
            $(EDK_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

IntelPchProtocolLibBin : 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\IntelPchProtocolLib.mak all\
            "MY_INCLUDES=$(IntelPchProtocolLib_INCLUDES)" \
            TYPE=LIBRARY LIBRARIES= 
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
