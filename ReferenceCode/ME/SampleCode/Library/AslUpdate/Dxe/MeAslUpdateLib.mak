# MAK file for the ModulePart:AslUpdateLib
all : MeAslUpdateLib

$(BUILD_DIR)\MeAslUpdateLib.lib : MeAslUpdateLib

MeAslUpdateLib : $(BUILD_DIR)\MeAslUpdateLib.mak MeAslUpdateLibBin

$(BUILD_DIR)\MeAslUpdateLib.mak : $(MeAslUpdateLib_DIR)\$(@B).cif $(MeAslUpdateLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(MeAslUpdateLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeAslUpdateLib_INCLUDES=\
    $(EDK_INCLUDES)\
    $(ME_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(iAMT_INCLUDES)\
    $(IndustryStandard_INCLUDES)

MeAslUpdateLib_DEFINES=\
    $(MY_DEFINES)\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__\
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

MeAslUpdateLib_LIBS=\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\

MeAslUpdateLibBin : $(MeAslUpdateLib_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\MeAslUpdateLib.mak all \
    "MY_INCLUDES=$(MeAslUpdateLib_INCLUDES)"\
    "MY_DEFINES=$(MeAslUpdateLib_DEFINES)"\
    TYPE=LIBRARY\