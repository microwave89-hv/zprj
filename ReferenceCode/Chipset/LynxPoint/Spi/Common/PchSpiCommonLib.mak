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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiCommonLib/PchSpiCommonLib.mak 1     2/08/12 9:22a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 9:22a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiCommonLib/PchSpiCommonLib.mak $
# 
# 1     2/08/12 9:22a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchSpiCommonLib

PchSpiCommonLib : PchSpiCommonDxeLib PchSpiCommonSmmLib PchSpiCommonPeiLib

$(PchSpiCommonSmmLib_LIB) : PchSpiCommonSmmLib
$(PchSpiCommonDxeLib_LIB) : PchSpiCommonDxeLib
$(PchSpiCommonPeiLib_LIB) : PchSpiCommonPeiLib

PchSpiCommonSmmLib : $(BUILD_DIR)\PchSpiCommonLib.mak PchSpiCommonLibSmmBin

PchSpiCommonDxeLib : $(BUILD_DIR)\PchSpiCommonLib.mak PchSpiCommonLibDxeBin

PchSpiCommonPeiLib : $(BUILD_DIR)\PchSpiCommonLib.mak PchSpiCommonLibPeiBin

$(BUILD_DIR)\PchSpiCommonLib.mak : $(PchSpiCommonLib_DIR)\$(@B).cif $(PchSpiCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(PchSpiCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSpiCommonLib_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

PchSpiCommonLibSmm_INCLUDES=\
  $(PchSpiCommonLib_INCLUDES) $(PCH_SPI_INCLUDES) 

PchSpiCommonLibDxe_INCLUDES=\
  $(PchSpiCommonLib_INCLUDES) $(PCH_SPI_INCLUDES)

PchSpiCommonLibPeim_INCLUDES=\
  $(PchSpiCommonLib_INCLUDES) $(PCH_SPI_INCLUDES)

PchSpiCommonLib_DEFINES = \
  $(CFLAGS)

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

PeimCpuBuildDefine = \
  /DMDE_CPU_IA32\

PchSpiCommonLibPeim_DEFINES = \
            $(PchSpiCommonLib_DEFINES)\
            $(PeimCpuBuildDefine)\

PchSpiCommonLibDxe_DEFINES = \
            $(PchSpiCommonLib_DEFINES)\
            $(DxeCpuBuildDefine)\

PchSpiCommonLibSmm_DEFINES = \
            $(PchSpiCommonLibDxe_DEFINES)\

PchSpiCommonLibDxeBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\PchSpiCommonLib.mak all\
                "MY_INCLUDES=$(PchSpiCommonLibDxe_INCLUDES)" \
                "CFLAGS=$(PchSpiCommonLibDxe_DEFINES)"\
                TYPE=LIBRARY \
                LIBRARY_NAME=$(PchSpiCommonDxeLib_LIB)

PchSpiCommonLibSmmBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\PchSpiCommonLib.mak all\
                "MY_INCLUDES=$(PchSpiCommonLibSmm_INCLUDES)" \
                "CFLAGS=$(PchSpiCommonLibSmm_DEFINES)"\
                TYPE=LIBRARY \
                BUILD_DIR=$(BUILD_DIR)\Smm\
                LIBRARY_NAME=$(PchSpiCommonSmmLib_LIB)

PchSpiCommonLibPeiBin :
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32 \
!ELSE
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
!ENDIF
                /f $(BUILD_DIR)\PchSpiCommonLib.mak all\
                "MY_INCLUDES=$(PchSpiCommonLibPeim_INCLUDES)" \
                "CFLAGS=$(PchSpiCommonLibPeim_DEFINES)"\
                TYPE=PEI_LIBRARY \
                LIBRARY_NAME=$(PchSpiCommonPeiLib_LIB)
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
