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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusCommonLib/PchSmbusCommonLib.mak 1     2/08/12 9:18a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 9:18a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusCommonLib/PchSmbusCommonLib.mak $
# 
# 1     2/08/12 9:18a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchSmbusCommonLib

PchSmbusCommonLib : PchSmbusCommonDxeLib PchSmbusCommonSmmLib PchSmbusCommonPeiLib

$(PchSmbusCommonSmmLib_LIB) : PchSmbusCommonSmmLib
$(PchSmbusCommonDxeLib_LIB) : PchSmbusCommonDxeLib
$(PchSmbusCommonPeiLib_LIB) : PchSmbusCommonPeiLib

PchSmbusCommonSmmLib : $(BUILD_DIR)\PchSmbusCommonLib.mak PchSmbusCommonLibSmmBin

PchSmbusCommonDxeLib : $(BUILD_DIR)\PchSmbusCommonLib.mak PchSmbusCommonLibDxeBin

PchSmbusCommonPeiLib : $(BUILD_DIR)\PchSmbusCommonLib.mak PchSmbusCommonLibPeiBin

$(BUILD_DIR)\PchSmbusCommonLib.mak : $(PchSmbusCommonLib_DIR)\$(@B).cif $(PchSmbusCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(PchSmbusCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSmbusCommonLib_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

PchSmbusCommonLibSmm_INCLUDES=\
  $(PchSmbusCommonLib_INCLUDES) 

PchSmbusCommonLibDxe_INCLUDES=\
  $(PchSmbusCommonLib_INCLUDES)

PchSmbusCommonLibPeim_INCLUDES=\
  $(PchSmbusCommonLib_INCLUDES)

PchSmbusCommonLib_DEFINES = \
  $(CFLAGS)

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

PeimCpuBuildDefine = \
  /DMDE_CPU_IA32\

PchSmbusCommonLibPeim_DEFINES = \
            $(PchSmbusCommonLib_DEFINES)\
            $(PeimCpuBuildDefine)\

PchSmbusCommonLibDxe_DEFINES = \
            $(PchSmbusCommonLib_DEFINES)\
            $(DxeCpuBuildDefine)\

PchSmbusCommonLibSmm_DEFINES = \
            $(PchSmbusCommonLibDxe_DEFINES)\

PchSmbusCommonLibDxeBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\PchSmbusCommonLib.mak all\
                "MY_INCLUDES=$(PchSmbusCommonLibDxe_INCLUDES)" \
                "CFLAGS=$(PchSmbusCommonLibDxe_DEFINES)"\
                TYPE=LIBRARY \
                LIBRARY_NAME=$(PchSmbusCommonDxeLib_LIB)

PchSmbusCommonLibSmmBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\PchSmbusCommonLib.mak all\
                "MY_INCLUDES=$(PchSmbusCommonLibSmm_INCLUDES)" \
                "CFLAGS=$(PchSmbusCommonLibSmm_DEFINES)"\
                TYPE=LIBRARY \
                BUILD_DIR=$(BUILD_DIR)\Smm\
                LIBRARY_NAME=$(PchSmbusCommonSmmLib_LIB)

PchSmbusCommonLibPeiBin :
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32 \
!ELSE
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
!ENDIF
                /f $(BUILD_DIR)\PchSmbusCommonLib.mak all\
                "MY_INCLUDES=$(PchSmbusCommonLibPeim_INCLUDES)" \
                "CFLAGS=$(PchSmbusCommonLibPeim_DEFINES)"\
                TYPE=PEI_LIBRARY \
                LIBRARY_NAME=$(PchSmbusCommonPeiLib_LIB)
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
