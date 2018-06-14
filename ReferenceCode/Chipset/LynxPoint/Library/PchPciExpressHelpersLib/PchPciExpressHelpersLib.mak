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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/PchPciExpressHelpersLib/PchPciExpressHelpersLib.mak 2     10/16/12 4:57a Scottyang $
#
# $Revision: 2 $
#
# $Date: 10/16/12 4:57a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/PchPciExpressHelpersLib/PchPciExpressHelpersLib.mak $
# 
# 2     10/16/12 4:57a Scottyang
# [TAG]  		EIP84720
# [Category]  	Improvement
# [Description]  	Support Hot-Plug in Shark Bay
# [Files]  		PchRootPort.c, PchPcie.asl, PchPciExpressHelpersLib.mak,
# PchPciExpressHlpersLibrary.c, SB.sdl
# 
# 1     2/08/12 8:47a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchPciExpressHelpersLib

PchPciExpressHelpersLib : PchPciExpressHelpersDxeLib PchPciExpressHelpersPeiLib

$(PchPciExpressHelpersDxeLib_LIB) : PchPciExpressHelpersDxeLib
$(PchPciExpressHelpersPeiLib_LIB) : PchPciExpressHelpersPeiLib

PchPciExpressHelpersDxeLib : $(BUILD_DIR)\PchPciExpressHelpersLib.mak PchPciExpressHelpersLibDxeBin
PchPciExpressHelpersPeiLib : $(BUILD_DIR)\PchPciExpressHelpersLib.mak PchPciExpressHelpersLibPeiBin

$(BUILD_DIR)\PchPciExpressHelpersLib.mak : $(PchPciExpressHelpersLib_DIR)\$(@B).cif $(PchPciExpressHelpersLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchPciExpressHelpersLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchPciExpressHelpersLib_INCLUDES=\
            $(EDK_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

PchPciExpressHelpersLib_DEFINES=\
            $(CFLAGS)\
    
PchPciExpressHelpersLibDxeBin:
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchPciExpressHelpersLib.mak all \
            "MY_INCLUDES=$(PchPciExpressHelpersLib_INCLUDES)" \
            TYPE=LIBRARY LIBRARIES= \
            LIBRARY_NAME=$(PchPciExpressHelpersDxeLib_LIB)

PchPciExpressHelpersLibPeiBin: 
!IF "$(x64_BUILD)"=="1" 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
!ENDIF
            /f $(BUILD_DIR)\PchPciExpressHelpersLib.mak all \
            "MY_INCLUDES=$(PchPciExpressHelpersLib_INCLUDES)" \
            "MY_DEFINES=$(PchPciExpressHelpersLib_DEFINES)" \
            LIBRARIES= \
            TYPE=PEI_LIBRARY LIBRARY_NAME=$(PchPciExpressHelpersPeiLib_LIB)
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
