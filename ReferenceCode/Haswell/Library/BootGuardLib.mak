# MAK file for the ModulePart:CpuPlatformLib

$(BootGuardLib_LIB) : BootGuardLib

BootGuardLib : $(BUILD_DIR)\BootGuardLib.mak BootGuardLibBin

$(BUILD_DIR)\BootGuardLib.mak : $(BootGuardLib_DIR)\$(@B).cif $(BootGuardLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(BootGuardLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

BootGuardLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR) \
        /f $(BUILD_DIR)\BootGuardLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES) $(INTEL_PCH_INCLUDES)"  \
        TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(BootGuardLib_LIB)"
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR)\IA32 \
        /f $(BUILD_DIR)\BootGuardLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES) $(INTEL_PCH_INCLUDES)"  \
        TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(BootGuardLib_LIB)"
