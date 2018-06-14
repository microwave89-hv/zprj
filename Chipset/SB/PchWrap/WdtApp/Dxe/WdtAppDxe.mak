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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppDxe/WdtAppDxe.mak 1     2/08/12 8:34a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:34a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/WdtApp/WdtAppDxe/WdtAppDxe.mak $
# 
# 1     2/08/12 8:34a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : WdtAppDxe

$(BUILD_DIR)\WdtAppDxe.mak : $(WdtAppDxe_DIR)\$(@B).cif $(BUILD_RULES)
  $(CIF2MAK) $(WdtAppDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

WdtAppDxe : $(BUILD_DIR)\WdtAppDxe.mak WdtAppDxe_Bin

WdtAppDxe_INCLUDES=\
	$(INTEL_PCH_INCLUDES)\
	$(PROJECT_INCLUDES)\
	$(WDT_APP_INCLUDES)\

WdtAppDxe_Bin : $(AMICSPLib) $(AMIDXELIB) $(WdtAppProtocol_LIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\WdtAppDxe.mak all\
		"MY_INCLUDES=$(WdtAppDxe_INCLUDES)"\
		GUID=CE366D33-B057-4c03-8561-CAF17738B66F\
		ENTRY_POINT=WdtAppDxeEntryPoint \
		TYPE=BS_DRIVER \
		DEPEX1=$(WdtAppDxe_DIR)\WdtAppDxe.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\

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
