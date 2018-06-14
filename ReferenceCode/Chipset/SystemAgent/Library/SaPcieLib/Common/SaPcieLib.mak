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

# MAK file for the ModulePart:SaPcieLib
EDK : SaPcieLib

SaPcieLib : $(BUILD_DIR)\SaPcieLib.mak SaPcieLibBin

$(BUILD_DIR)\SaPcieLib.mak : $(SaPcieLib_DIR)\$(@B).cif $(SaPcieLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SaPcieLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(SaPcieLib_LIB) : SaPcieLib

SaPcieLib_INCLUDES=\
            $(EdkIIGlueLib_INCLUDES)\
            $(PROJECT_CPU_INCLUDES)\
            $(INTEL_MCH_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

SaPcieLib_DEFINES = \
            $(CFLAGS) \
    
SaPcieLibBin: 
	    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) \
            /f $(BUILD_DIR)\SaPcieLib.mak all \
            "MY_INCLUDES=$(SaPcieLib_INCLUDES)" \
            "CFLAGS=$(SaPcieLib_DEFINES)"\
            TYPE=LIBRARY LIBRARIES= \
            LIBRARY_NAME=$(SaPcieLib_LIB)

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
