# MAK file for the ModulePart:CpuPlatformLib

$(TxtLib_LIB) : TxtLib

TxtLib : $(BUILD_DIR)\TxtLib.mak TxtLibBin

$(BUILD_DIR)\TxtLib.mak : $(TxtLib_DIR)\$(@B).cif $(TxtLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TxtLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TxtLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        /f $(BUILD_DIR)\TxtLib.mak all\
        BUILD_DIR=$(BUILD_DIR)\IA32 \
        "AFLAGS=$(AFLAGS) $(PROJECT_CPU_INCLUDES)" \
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES) $(INTEL_PCH_INCLUDES)"  \
        TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(TxtLib_LIB)"
