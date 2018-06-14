# MAK file for the ModulePart:AslUpdateLib
all : PpmAslUpdateLib

$(BUILD_DIR)\PpmAslUpdateLib.lib : PpmAslUpdateLib

PpmAslUpdateLib : $(BUILD_DIR)\PpmAslUpdateLib.mak PpmAslUpdateLibBin

$(BUILD_DIR)\PpmAslUpdateLib.mak : $(PpmAslUpdateLib_DIR)\$(@B).cif $(PpmAslUpdateLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PpmAslUpdateLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PpmAslUpdateLib_INCLUDES=\
    $(PROJECT_CPU_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(iAMT_INCLUDES)\
    $(IndustryStandard_INCLUDES)

PpmAslUpdateLib_DEFINES=\
    $(MY_DEFINES)\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__\
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

PpmAslUpdateLib_LIBS=\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\

PpmAslUpdateLibBin : 
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PpmAslUpdateLib.mak all \
    "MY_INCLUDES=$(PpmAslUpdateLib_INCLUDES)"\
    "MY_DEFINES=$(PpmAslUpdateLib_DEFINES)"\
    TYPE=LIBRARY\