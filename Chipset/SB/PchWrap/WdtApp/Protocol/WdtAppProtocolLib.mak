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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppProtocolLib/WdtAppProtocolLib.mak 1     2/08/12 8:36a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:36a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppProtocolLib/WdtAppProtocolLib.mak $
# 
# 1     2/08/12 8:36a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

all : WdtAppProtocolLib

$(WdtAppProtocol_LIB) : WdtAppProtocolLib

WdtAppProtocolLib : $(BUILD_DIR)\WdtAppProtocolLib.mak WdtAppProtocolLibBin

$(BUILD_DIR)\WdtAppProtocolLib.mak : $(WdtAppProtocol_DIR)\$(@B).cif $(WdtAppProtocol_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(WdtAppProtocol_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

WdtAppProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\WdtAppProtocolLib.mak all\
		TYPE=LIBRARY \
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
