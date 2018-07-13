all : AAEONSecurity

AAEONSecurity : $(BUILD_DIR)\AAEONSecurity.mak AAEONSecurityBin

$(BUILD_DIR)\AAEONSecurity.mak : $(AAEON_SECURITY_DIR)\$(@B).cif $(AAEON_SECURITY_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AAEON_SECURITY_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AAEONSecurityBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AAEONSecurity.mak all\
		Name=AAEONSecurity \
		GUID=bedf0344-f4b9-4071-914d-e3ef72727547\
		ENTRY_POINT=AAEONSecurityEntryPoint\
		TYPE=BS_DRIVER \
		COMPRESS=1
