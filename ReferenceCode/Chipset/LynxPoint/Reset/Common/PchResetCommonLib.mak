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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchResetCommonLib/PchResetCommonLib.mak 1     2/08/12 9:06a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 9:06a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchResetCommonLib/PchResetCommonLib.mak $
# 
# 1     2/08/12 9:06a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchResetCommonLib

!IF "$(PchInitPeim_SUPPORT)" == "1"
PchResetCommonLib : PchResetCommonPeiLib
!ENDIF

!IF "$(PchInitDxe_SUPPORT)" == "1"
PchResetCommonLib : PchResetCommonDxeLib
!ENDIF

!IF "$(PchInitPeim_SUPPORT)" == "1"
!IF "$(PchInitDxe_SUPPORT)" == "1"
PchResetCommonLib : PchResetCommonDxeLib PchResetCommonPeiLib
!ENDIF
!ENDIF

!IF "$(PchInitDxe_SUPPORT)" == "1"
$(PchResetCommonDxeLib_LIB) : PchResetCommonDxeLib
!ENDIF

!IF "$(PchInitPeim_SUPPORT)" == "1"
$(PchResetCommonPeiLib_LIB) : PchResetCommonPeiLib
!ENDIF

PchResetCommonDxeLib : $(BUILD_DIR)\PchResetCommonLib.mak PchResetCommonLibDxeBin

PchResetCommonPeiLib : $(BUILD_DIR)\PchResetCommonLib.mak PchResetCommonLibPeiBin

$(BUILD_DIR)\PchResetCommonLib.mak : $(PchResetCommonLib_DIR)\$(@B).cif $(PchResetCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(PchResetCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchResetCommonLib_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

PchResetCommonLibDxe_INCLUDES=\
  $(PchResetCommonLib_INCLUDES) $(PCH_INITDXE_INCLUDES)

PchResetCommonLibPeim_INCLUDES=\
  $(PchResetCommonLib_INCLUDES) $(PCH_INITPEI_INCLUDES)

PchResetCommonLib_DEFINES = \
  $(CFLAGS)

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

PeimCpuBuildDefine = \
  /DMDE_CPU_IA32\

PchResetCommonLibPeim_DEFINES = \
            $(PchResetCommonLib_DEFINES)\
            $(PeimCpuBuildDefine)\

PchResetCommonLibDxe_DEFINES = \
            $(PchResetCommonLib_DEFINES)\
            $(DxeCpuBuildDefine)\

PchResetCommonLibDxeBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\PchResetCommonLib.mak all\
                "MY_INCLUDES=$(PchResetCommonLibDxe_INCLUDES)" \
                "CFLAGS=$(PchResetCommonLibDxe_DEFINES)"\
                TYPE=LIBRARY \
                LIBRARY_NAME=$(PchResetCommonDxeLib_LIB)

PchResetCommonLibPeiBin : $(EFISCRIPTLIB) $(EDKFRAMEWORKPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32 \
!ELSE
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
!ENDIF
                /f $(BUILD_DIR)\PchResetCommonLib.mak all\
                "MY_INCLUDES=$(PchResetCommonLibPeim_INCLUDES)" \
                "CFLAGS=$(PchResetCommonLibPeim_DEFINES)"\
                TYPE=PEI_LIBRARY \
                LIBRARY_NAME=$(PchResetCommonPeiLib_LIB)
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
