# MAK file for the ModulePart:PchGuidLib
all : PchGuidLib

$(PchGuidLib_LIB) : PchGuidLib

PchGuidLib : $(BUILD_DIR)\PchGuidLib.mak PchGuidLibBin

$(BUILD_DIR)\PchGuidLib.mak : $(PchGuidLib_DIR)\$(@B).cif $(PchGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PchGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchGuidLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\PchGuidLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES)"  \
		TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
                /f $(BUILD_DIR)\PchGuidLib.mak all\
                "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES)"  \
                TYPE=PEI_LIBRARY
!ENDIF	
