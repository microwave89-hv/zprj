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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/DxeRuntimePciLibPciExpress/DxeRuntimePciLibPciExpress.mak 1     2/08/12 8:46a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:46a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/DxeRuntimePciLibPciExpress/DxeRuntimePciLibPciExpress.mak $
# 
# 1     2/08/12 8:46a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

# MAK file for the ModulePart:DxeRuntimePciLibPciExpress
EDK : DxeRuntimePciLibPciExpress

DxeRuntimePciLibPciExpress : $(BUILD_DIR)\DxeRuntimePciLibPciExpress.mak DxeRuntimePciLibPciExpressBin

$(BUILD_DIR)\DxeRuntimePciLibPciExpress.mak : $(DxeRuntimePciLibPciExpress_DIR)\$(@B).cif $(DxeRuntimePciLibPciExpress_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(DxeRuntimePciLibPciExpress_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(DxeRuntimePciLibPciExpressLib_LIB) : DxeRuntimePciLibPciExpress

DxeRuntimePciLibPciExpress_INCLUDES=\
            $(EDK_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

DxeRuntimePciLibPciExpress_DEFINES = \
$(CFLAGS) \
$(DxeCpuBuildDefine) \
    
DxeRuntimePciLibPciExpressBin: 
	    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) \
            /f $(BUILD_DIR)\DxeRuntimePciLibPciExpress.mak all \
            "MY_INCLUDES=$(DxeRuntimePciLibPciExpress_INCLUDES)" \
            "CFLAGS=$(DxeRuntimePciLibPciExpress_DEFINES)"\
            TYPE=LIBRARY LIBRARIES= \
            LIBRARY_NAME=$(DxeRuntimePciLibPciExpressLib_LIB)
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
