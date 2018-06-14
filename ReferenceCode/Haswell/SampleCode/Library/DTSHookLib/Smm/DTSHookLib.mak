# MAK file for the ModulePart:CpuPlatformLib

$(DTSHookLib_LIB) : DTSHookLib

DTSHookLib : $(BUILD_DIR)\DTSHookLib.mak DTSHookLibBin

$(BUILD_DIR)\DTSHookLib.mak : $(DTSHookLib_DIR)\$(@B).cif $(DTSHookLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(DTSHookLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

DTSHookLibBin :
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        BUILD_DIR=$(BUILD_DIR) \
        /f $(BUILD_DIR)\DTSHookLib.mak all\
        "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
        TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(DTSHookLib_LIB)"