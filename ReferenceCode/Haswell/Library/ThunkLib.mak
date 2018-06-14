# MAK file for the ModulePart:ThunkLib
ThunkLib_x64_OBJECTS =\
$(BUILD_DIR)\ReferenceCode\IvyBridgeRc\Library\ThunkLib\x64\x86Thunk.obj\
$(BUILD_DIR)\ReferenceCode\IvyBridgeRc\Library\ThunkLib\x64\Thunk16.obj\
$(BUILD_DIR)\ReferenceCode\IvyBridgeRc\Library\ThunkLib\x64\FxSave.obj\
$(BUILD_DIR)\ReferenceCode\IvyBridgeRc\Library\ThunkLib\x64\FxRestore.obj

ThunkLib_IA32_OBJECTS =\
$(BUILD_DIR)\IA32\ReferenceCode\IvyBridgeRc\Library\ThunkLib\Ia32\x86Thunk.obj\
$(BUILD_DIR)\IA32\ReferenceCode\IvyBridgeRc\Library\ThunkLib\Ia32\Thunk16.obj

ThunkLib_PORCESSOR_Ia32_CIF=$(ThunkLib_DIR)\ThunkLib\Ia32\ThunkLibIa32.cif
ThunkLib_PORCESSOR_x64_CIF=$(ThunkLib_DIR)\ThunkLib\x64\ThunkLibx64.cif

$(ThunkLib_LIB) : ThunkLib

ThunkLib : $(BUILD_DIR)\ThunkLib.mak ThunkLibBin

#-!IF "$(PROCESSOR)"=="x64"
$(BUILD_DIR)\ThunkLib.mak : $(ThunkLib_DIR)\$(@B).cif $(ThunkLib_DIR)\$(@B).mak $(BUILD_RULES) $(ThunkLib_PORCESSOR_Ia32_CIF) $(ThunkLib_PORCESSOR_x64_CIF)
	$(CIF2MAK) $(ThunkLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(ThunkLib_PORCESSOR_Ia32_CIF) $(ThunkLib_PORCESSOR_x64_CIF)
#-!ELSE
#-$(BUILD_DIR)\ThunkLib.mak : $(ThunkLib_DIR)\$(@B).cif $(ThunkLib_DIR)\$(@B).mak $(BUILD_RULES) $(ThunkLib_PORCESSOR_CIF)
#-	$(CIF2MAK) $(ThunkLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(ThunkLib_PORCESSOR_CIF)
#-!ENDIF

ThunkLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\ThunkLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(ThunkLib_LIB)"\
		"OBJECTS=$(ThunkLib_x64_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\ThunkLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(PROJECT_CPU_INCLUDES)"  \
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(ThunkLib_LIB)"\
		"OBJECTS=$(ThunkLib_IA32_OBJECTS)"
            
