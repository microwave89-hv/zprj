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

# MAK file for the ModulePart:SaPcieDxeLib
EDK : SaPcieDxeLib

SaPcieDxeLib : $(BUILD_DIR)\SaPcieDxeLib.mak SaPcieDxeLibBin

$(BUILD_DIR)\SaPcieDxeLib.mak : $(SaPcieDxeLib_DIR)\$(@B).cif $(SaPcieDxeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SaPcieDxeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(SaPcieDxeLib_LIB) : SaPcieDxeLib

SaPcieDxeLib_DEFINES = \
            $(CFLAGS) \
    
SaPcieDxeLibBin: $(SaPcieLib_LIB)
	    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) \
            /f $(BUILD_DIR)\SaPcieDxeLib.mak all \
            "CFLAGS=$(SaPcieDxeLib_DEFINES)"\
            TYPE=LIBRARY LIBRARIES= \
            LIBRARY_NAME=$(SaPcieDxeLib_LIB)
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
