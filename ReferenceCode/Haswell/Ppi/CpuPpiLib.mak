# MAK file for the ModulePart:IntelSaPpiLib
EDK : CpuPpiLib

$(BUILD_DIR)\CpuPpiLib.lib : CpuPpiLib

CpuPpiLib : $(BUILD_DIR)\CpuPpiLib.mak CpuPpiLibBin

$(BUILD_DIR)\CpuPpiLib.mak : $(CPU_PPI_LIB_DIR)\$(@B).cif $(CPU_PPI_LIB_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(CPU_PPI_LIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CpuPpiLib_INCLUDES =\
    $(PROJECT_CPU_INCLUDES)\
    $(EDK_INCLUDES) \
    $(INTEL_MCH_INCLUDES)

CpuPpiLibBin : 
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\CpuPpiLib.mak all\
    "MY_INCLUDES=$(CpuPpiLib_INCLUDES)" \
    TYPE=PEI_LIBRARY \
    LIBRARY_NAME=$(CPU_PPI_LIB)