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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchUsbCommonLib/PchUsbCommonLib.mak 2     8/13/12 9:08a Victortu $
#
# $Revision: 2 $
#
# $Date: 8/13/12 9:08a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchUsbCommonLib/PchUsbCommonLib.mak $
# 
# 2     8/13/12 9:08a Victortu
# 
# 1     2/08/12 9:29a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchUsbCommonLib

!IF "$(PchInitPeim_SUPPORT)" == "1"
PchUsbCommonLib : PchUsbCommonPeiLib
!ENDIF

!IF "$(PchInitDxe_SUPPORT)" == "1"
PchUsbCommonLib : PchUsbCommonDxeLib
!ENDIF

!IF "$(PchInitPeim_SUPPORT)" == "1"
!IF "$(PchInitDxe_SUPPORT)" == "1"
PchUsbCommonLib : PchUsbCommonDxeLib PchUsbCommonPeiLib
!ENDIF
!ENDIF

!IF "$(PchInitDxe_SUPPORT)" == "1"
$(PchUsbCommonDxeLib_LIB) : PchUsbCommonDxeLib
!ENDIF

!IF "$(PchInitPeim_SUPPORT)" == "1"
$(PchUsbCommonPeiLib_LIB) : PchUsbCommonPeiLib
!ENDIF

PchUsbCommonDxeLib : $(BUILD_DIR)\PchUsbCommonLib.mak PchUsbCommonLibDxeBin

PchUsbCommonPeiLib : $(BUILD_DIR)\PchUsbCommonLib.mak PchUsbCommonLibPeiBin

$(BUILD_DIR)\PchUsbCommonLib.mak : $(PchUsbCommonLib_DIR)\$(@B).cif $(PchUsbCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(PchUsbCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchUsbCommonLib_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  /I$(INTEL_PCH_DIR)\Protocol\PchInfo\

PchUsbCommonLibDxe_INCLUDES=\
  $(PchUsbCommonLib_INCLUDES) $(PCH_INITDXE_INCLUDES)

PchUsbCommonLibPeim_INCLUDES=\
  $(PchUsbCommonLib_INCLUDES) $(PCH_INITPEI_INCLUDES)

PchUsbCommonLib_DEFINES = \
  $(CFLAGS)

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

PeimCpuBuildDefine = \
  /DMDE_CPU_IA32\

PchUsbCommonLibPeim_DEFINES = \
            $(PchUsbCommonLib_DEFINES)\
            $(PeimCpuBuildDefine)\

PchUsbCommonLibDxe_DEFINES = \
            $(PchUsbCommonLib_DEFINES)\
            $(DxeCpuBuildDefine)\

PchUsbCommonLibDxeBin :  
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
                /f $(BUILD_DIR)\PchUsbCommonLib.mak all\
                "MY_INCLUDES=$(PchUsbCommonLibDxe_INCLUDES)" \
                "CFLAGS=$(PchUsbCommonLibDxe_DEFINES)"\
                TYPE=LIBRARY \
                LIBRARY_NAME=$(PchUsbCommonDxeLib_LIB)

PchUsbCommonLibPeiBin : $(EFISCRIPTLIB) $(EDKFRAMEWORKPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32 \
!ELSE
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
!ENDIF
                /f $(BUILD_DIR)\PchUsbCommonLib.mak all\
                "MY_INCLUDES=$(PchUsbCommonLibPeim_INCLUDES)" \
                "CFLAGS=$(PchUsbCommonLibPeim_DEFINES)"\
                TYPE=PEI_LIBRARY \
                LIBRARY_NAME=$(PchUsbCommonPeiLib_LIB)
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
