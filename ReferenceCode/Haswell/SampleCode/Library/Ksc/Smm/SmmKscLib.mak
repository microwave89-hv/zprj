# MAK file for the ModulePart:CpuPlatformLib

$(SmmKscLib_LIB) : SmmKscLib

SmmKscLib : $(BUILD_DIR)\SmmKscLib.mak SmmKscLibBin

$(BUILD_DIR)\SmmKscLib.mak : $(SmmKscLib_DIR)\$(@B).cif $(SmmKscLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SmmKscLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmKscLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR) \
        /f $(BUILD_DIR)\SmmKscLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
        TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(SmmKscLib_LIB)"