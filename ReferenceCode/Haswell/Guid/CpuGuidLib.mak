# MAK file for the ModulePart:PpmGuidLib

$(CpuGuidLib_LIB) : CpuGuidLib

CpuGuidLib : $(BUILD_DIR)\CpuGuidLib.mak CpuGuidLibBin

$(BUILD_DIR)\CpuGuidLib.mak : $(CpuGuidLib_DIR)\$(@B).cif $(CpuGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CpuGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuGuidLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CpuGuidLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
		TYPE=LIBRARY \
		LIBRARY_NAME=$(CpuGuidLib_LIB)
    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
            /f $(BUILD_DIR)\CpuGuidLib.mak all\
            "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
            TYPE=PEI_LIBRARY
