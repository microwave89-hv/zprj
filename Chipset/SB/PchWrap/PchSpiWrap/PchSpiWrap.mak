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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PchSpiWrap/PchSpiWrap.mak 1     2/08/12 8:33a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:33a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PchSpiWrap/PchSpiWrap.mak $
# 
# 1     2/08/12 8:33a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchSpiWrap

PchSpiWrap : $(BUILD_DIR)\PchSpiWrap.mak PchSpiWrapBin

$(BUILD_DIR)\PchSpiWrap.mak : $(PchSpiWrap_DIR)\$(@B).cif $(PchSpiWrap_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PchSpiWrap_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSpiWrapBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\PchSpiWrap.mak all\
        GUID=B716A6F8-F3A1-4b8e-8582-5A303F1CDD64\
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES)"\
        ENTRY_POINT=PchSpiWrapEntry\
        TYPE=RT_DRIVER \
        DEPEX1=$(PchSpiWrap_DIR)\PchSpiWrap.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1
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
