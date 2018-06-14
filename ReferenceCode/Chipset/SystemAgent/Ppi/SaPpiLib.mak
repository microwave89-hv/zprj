# MAK file for the ModulePart:IntelSaPpiLib
all : IntelSaPpiLib

$(BUILD_DIR)\IntelSaPpiLib.lib : IntelSaPpiLib

IntelSaPpiLib : $(BUILD_DIR)\SaPpiLib.mak IntelSaPpiLibBin

$(BUILD_DIR)\SaPpiLib.mak : $(INTEL_SA_PPI_LIB_DIR)\$(@B).cif $(INTEL_SA_PPI_LIB_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(INTEL_SA_PPI_LIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelSaPpiLib_INCLUDES =\
    $(EDK_INCLUDES) \
    $(INTEL_MCH_INCLUDES)

IntelSaPpiLibBin : 
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\SaPpiLib.mak all\
    "MY_INCLUDES=$(IntelSaPpiLib_INCLUDES)" \
    TYPE=PEI_LIBRARY \
    LIBRARY_NAME=$(BUILD_DIR)\IntelSaPpiLib.lib