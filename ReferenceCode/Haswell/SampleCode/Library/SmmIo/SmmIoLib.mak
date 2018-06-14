# MAK file for the ModulePart:CpuPlatformLib

$(SmmIoLib_LIB) : SmmIoLib

SmmIoLib : $(BUILD_DIR)\SmmIoLib.mak SmmIoLibBin

$(BUILD_DIR)\SmmIoLib.mak : $(SmmIoLib_DIR)\$(@B).cif $(SmmIoLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SmmIoLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmIoLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR) \
        /f $(BUILD_DIR)\SmmIoLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
        TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(SmmIoLib_LIB)"