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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/PchPlatformLib/PchPlatformLib.mak 3     10/16/12 2:52a Scottyang $
#
# $Revision: 3 $
#
# $Date: 10/16/12 2:52a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/PchPlatformLib/PchPlatformLib.mak $
# 
# 3     10/16/12 2:52a Scottyang
# [TAG]  		EIP103924
# [Category]  	Improvement
# [Description]  	Update RC 0.7.1
# [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 2     7/02/12 9:17a Victortu
# 
# 1     2/08/12 8:48a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

# MAK file for the ModulePart:PchPlatformLib
EDK : PchPlatformLib

PchPlatformLib : PchPlatformSmmLib PchPlatformDxeLib PchPlatformPeiLib

$(PchPlatformSmmLib_LIB) : PchPlatformSmmLib
$(PchPlatformDxeLib_LIB) : PchPlatformDxeLib
$(PchPlatformPeiLib_LIB) : PchPlatformPeiLib

PchPlatformSmmLib : $(BUILD_DIR)\PchPlatformLib.mak PchPlatformLibSmmBin

PchPlatformDxeLib : $(BUILD_DIR)\PchPlatformLib.mak PchPlatformLibDxeBin

PchPlatformPeiLib : $(BUILD_DIR)\PchPlatformLib.mak PchPlatformLibPeiBin

$(BUILD_DIR)\PchPlatformLib.mak : $(PchPlatformLib_DIR)\$(@B).cif $(PchPlatformLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchPlatformLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchPlatformLib_INCLUDES =\
	    $(EdkIIGlueLib_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\
            $(EDK_INCLUDES)\

PchPlatformLib_LIBS=\
    $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF

PchPlatformLibSmmBin : $(PchPlatformLib_LIBS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchPlatformLib.mak all\
            "MY_INCLUDES=$(PchPlatformLib_INCLUDES)" \
            TYPE=LIBRARY \
            LIBRARIES=\
            LIBRARY_NAME=$(PchPlatformSmmLib_LIB)

PchPlatformLibDxeBin : $(PchPlatformLib_LIBS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchPlatformLib.mak all\
            "MY_INCLUDES=$(PchPlatformLib_INCLUDES)" \
            "CFLAGS=$(CFLAGS) $(PchPlatformLib_DEFINES)"\
            TYPE=LIBRARY \
            LIBRARIES=\
            LIBRARY_NAME=$(PchPlatformDxeLib_LIB)

PchPlatformLibPeiBin : $(PchPlatformLib_LIBS)
!IF "$(x64_BUILD)"=="1" 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
!ENDIF
            /f $(BUILD_DIR)\PchPlatformLib.mak all\
            "MY_INCLUDES=$(PchPlatformLib_INCLUDES)"\
            "CFLAGS=$(CFLAGS) $(PchPlatformLib_DEFINES)"\
            TYPE=PEI_LIBRARY \
            LIBRARIES=\
            LIBRARY_NAME=$(PchPlatformPeiLib_LIB)
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
