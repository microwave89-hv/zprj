# MAK file for the ModulePart:IntelSaProtocolLib
all : IntelSaProtocolLib

$(BUILD_DIR)\IntelSaProtocolLib.lib : IntelSaProtocolLib

IntelSaProtocolLib : $(BUILD_DIR)\SaProtocolLib.mak IntelSaProtocolLibBin

$(BUILD_DIR)\SaProtocolLib.mak : $(INTEL_SA_PROTOCOL_LIB_DIR)\$(@B).cif $(INTEL_SA_PROTOCOL_LIB_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(INTEL_SA_PROTOCOL_LIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelSaProtocolLib_INCLUDES =\
    $(EDK_INCLUDES) \
    $(INTEL_MCH_INCLUDES)

IntelSaProtocolLibBin : 
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\SaProtocolLib.mak all\
    "MY_INCLUDES=$(IntelSaProtocolLib_INCLUDES)" \
    TYPE=LIBRARY \
    LIBRARY_NAME=$(BUILD_DIR)\IntelSaProtocolLib.lib