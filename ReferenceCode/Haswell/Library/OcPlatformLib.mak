# MAK file for the ModulePart:CpuPlatformLib

$(OcPlatformLib_LIB) : OcPlatformLib

OcPlatformLib : $(BUILD_DIR)\OcPlatformLib.mak OcPlatformLibBin

$(BUILD_DIR)\OcPlatformLib.mak : $(OcPlatformLib_DIR)\$(@B).cif $(OcPlatformLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OcPlatformLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OcPlatformLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR) \
        /f $(BUILD_DIR)\OcPlatformLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES) $(INTEL_PCH_INCLUDES)"  \
        TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(OcPlatformLib_LIB)"
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR)\IA32 \
        /f $(BUILD_DIR)\OcPlatformLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES) $(INTEL_PCH_INCLUDES)"  \
        TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(OcPlatformLib_LIB)"
