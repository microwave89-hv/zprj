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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/PchSmbusLib/PchSmbusLib.mak 1     2/08/12 8:49a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:49a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/PchSmbusLib/PchSmbusLib.mak $
# 
# 1     2/08/12 8:49a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
all : PchSmbusLib

$(PchSmbusLib_LIB) : PchSmbusLib

PchSmbusLib : $(BUILD_DIR)\PchSmbusLib.mak PchSmbusLibBin

$(BUILD_DIR)\PchSmbusLib.mak : $(PchSmbusLib_DIR)\$(@B).cif $(PchSmbusLib_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(PchSmbusLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSmbusPeiLib_INCLUDES=\
		        $(EdkIIGlueLib_INCLUDES)\
                $(INTEL_PCH_INCLUDES)\
                /I$(EdkIIGluePeiSmbusLib_DIR)\
                /I$(PchSmbusLib_DIR)\Pei\

PchSmbusDxeLib_INCLUDES=\
		        $(EdkIIGlueLib_INCLUDES)\
                $(INTEL_PCH_INCLUDES)\
                /I$(EdkIIGlueDxeSmbusLib_DIR)\
                /I$(PchSmbusLib_DIR)\Dxe\

PchSmbusLibBin : 
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
                /f $(BUILD_DIR)\PchSmbusLib.mak all\
                "MY_INCLUDES=$(PchSmbusDxeLib_INCLUDES)" \
                TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
                /f $(BUILD_DIR)\PchSmbusLib.mak all\
                "MY_INCLUDES=$(PchSmbusPeiLib_INCLUDES)" \
                TYPE=PEI_LIBRARY
!ENDIF		
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
