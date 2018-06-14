# MAK file for the ModulePart:CpuPlatformLib

$(CpuPlatformLib_LIB) : CpuPlatformLib

CpuPlatformLib : $(BUILD_DIR)\CpuPlatformLib.mak CpuPlatformLibBin

$(BUILD_DIR)\CpuPlatformLib.mak : $(CpuPlatformLib_DIR)\$(@B).cif $(CpuPlatformLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CpuPlatformLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuPlatformLib_MY_INCLUDES=\
    $(EDK_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    /I$(PROJECT_CPU_ROOT)\Library\CpuPlatformLib\
    /I$(INTEL_PCH_DIR)\Include\
    /I$(INTEL_PCH_DIR)\Include\Library

CpuPlatformLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR) \
        /f $(BUILD_DIR)\CpuPlatformLib.mak all\
        "MY_INCLUDES=$(CpuPlatformLib_MY_INCLUDES)"  \
        TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(CpuPlatformLib_LIB)"
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR)\IA32 \
        /f $(BUILD_DIR)\CpuPlatformLib.mak all\
        "MY_INCLUDES=$(CpuPlatformLib_MY_INCLUDES)"  \
        TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(CpuPlatformLib_LIB)"
