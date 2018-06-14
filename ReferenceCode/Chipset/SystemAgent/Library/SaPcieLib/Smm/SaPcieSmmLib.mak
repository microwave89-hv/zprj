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

#---------------------------------------------------------------------------
#   Create SaPcieSmmLib Driver
#---------------------------------------------------------------------------

# MAK file for the ModulePart:SaPcieSmmLib
EDK : SaPcieSmmLib

SaPcieSmmLib : $(BUILD_DIR)\SaPcieSmmLib.mak SaPcieSmmLibBin

$(BUILD_DIR)\SaPcieSmmLib.mak : $(SaPcieSmmLib_DIR)\$(@B).cif $(SaPcieSmmLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SaPcieSmmLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(SaPcieSmmLib_LIB) : SaPcieSmmLib

SaPcieSmmLib_DEFINES = \
            $(CFLAGS) \
    
SaPcieSmmLibBin: $(SaPcieLib_LIB)
	    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) \
            /f $(BUILD_DIR)\SaPcieSmmLib.mak all \
            "CFLAGS=$(SaPcieSmmLib_DEFINES)"\
            TYPE=LIBRARY LIBRARIES= \
            LIBRARY_NAME=$(SaPcieSmmLib_LIB)
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
