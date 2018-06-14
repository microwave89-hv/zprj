# MAK file for the ModulePart:SaGuidLib
all : SaGuidLib

$(SaGuidLib_LIB) : SaGuidLib

SaGuidLib : $(BUILD_DIR)\SaGuidLib.mak SaGuidLibBin

$(BUILD_DIR)\SaGuidLib.mak : $(SaGuidLib_DIR)\$(@B).cif $(SaGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SaGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SaGuidLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\SaGuidLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES)"  \
		TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1" 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
                /f $(BUILD_DIR)\SaGuidLib.mak all\
                "MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES)"  \
                TYPE=PEI_LIBRARY
!ENDIF	
