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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppPei/WdtAppPei.mak 1     2/08/12 8:34a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:34a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppPei/WdtAppPei.mak $
# 
# 1     2/08/12 8:34a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : WdtAppPei

$(BUILD_DIR)\WdtAppPei.mak : $(WdtAppPei_DIR)\$(@B).cif $(BUILD_RULES)
  $(CIF2MAK) $(WdtAppPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

WdtAppPei : $(BUILD_DIR)\WdtAppPei.mak WdtAppPeiBin

WdtAppPei_INCLUDES=\
	$(INTEL_PCH_INCLUDES)\
	$(WDT_APP_INCLUDES)\

WdtAppPeiBin : $(AMIPEILIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\WdtAppPei.mak all \
		"MY_INCLUDES = $(WdtAppPei_INCLUDES)" \
		NAME=WdtAppPei\
		MAKEFILE=$(BUILD_DIR)\WdtAppPei.mak \
		GUID=0F69F6D7-0E4B-43a6-BFC2-6871694369B0 \
		ENTRY_POINT=WdtAppPeiEntryPoint \
		TYPE=PEIM \
		DEPEX1=$(WdtAppPei_DIR)\WdtAppPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0

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
