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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/Wdt/WdtCommonLib/WdtCommonLib.mak 1     2/08/12 9:31a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 9:31a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/Wdt/WdtCommonLib/WdtCommonLib.mak $
# 
# 1     2/08/12 9:31a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
EDK : WdtCommonLib
WdtDxe : $(BUILD_DIR)\WdtDxe.mak WdtDxeBin

WdtCommonLib : WdtCommonDxeLib WdtCommonPeiLib

$(WdtCommonDxeLib_LIB) : WdtCommonDxeLib
$(WdtCommonPeiLib_LIB) : WdtCommonPeiLib

WdtCommonDxeLib : $(BUILD_DIR)\WdtCommonLib.mak WdtCommonLibDxeBin

WdtCommonPeiLib : $(BUILD_DIR)\WdtCommonLib.mak WdtCommonLibPeiBin

$(BUILD_DIR)\WdtCommonLib.mak : $(WdtCommonLib_DIR)\$(@B).cif $(WdtCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(WdtCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

WdtCommonLib_INCLUDES=\
	$(EdkIIGlueLib_INCLUDES)\
	$(INTEL_PCH_INCLUDES)\
	$(WdtCommonLib_INCLUDES)


WdtCommonLib_DEFINES = \
  $(CFLAGS)

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

PeimCpuBuildDefine = \
  /DMDE_CPU_IA32\

WdtCommonLibPeim_DEFINES = \
            $(WdtCommonLib_DEFINES)\
            $(PeimCpuBuildDefine)\

WdtCommonLibDxe_DEFINES = \
            $(WdtCommonLib_DEFINES)\
            $(DxeCpuBuildDefine)\

WdtCommonLibDxeBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\WdtCommonLib.mak all\
                "MY_INCLUDES=$(WdtCommonLib_INCLUDES)" \
                "CFLAGS=$(WdtCommonLibDxe_DEFINES)"\
                TYPE=LIBRARY \
                LIBRARY_NAME=$(WdtCommonDxeLib_LIB)

WdtCommonLibPeiBin :
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32 \
!ELSE
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
!ENDIF
                /f $(BUILD_DIR)\WdtCommonLib.mak all\
                "MY_INCLUDES=$(WdtCommonLib_INCLUDES)" \
                "CFLAGS=$(WdtCommonLibPeim_DEFINES)"\
                TYPE=PEI_LIBRARY \
                LIBRARY_NAME=$(WdtCommonPeiLib_LIB)
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
