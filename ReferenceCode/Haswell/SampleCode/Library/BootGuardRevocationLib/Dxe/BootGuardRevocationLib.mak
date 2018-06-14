# MAK file for the ModulePart:AslUpdateLib
all : BootGuardRevocationLib

$(BUILD_DIR)\BootGuardRevocationLib.lib : BootGuardRevocationLib

BootGuardRevocationLib : $(BUILD_DIR)\BootGuardRevocationLib.mak BootGuardRevocationLibBin

$(BUILD_DIR)\BootGuardRevocationLib.mak : $(BootGuardRevocationLib_DIR)\$(@B).cif $(BootGuardRevocationLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(BootGuardRevocationLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

BootGuardRevocationLib_INCLUDES=\
    $(PROJECT_CPU_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(iAMT_INCLUDES)\
    $(IndustryStandard_INCLUDES)

BootGuardRevocationLib_DEFINES=\
    $(MY_DEFINES)\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__\
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

BootGuardRevocationLib_LIBS=\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\

BootGuardRevocationLibBin : 
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\BootGuardRevocationLib.mak all \
    "MY_INCLUDES=$(BootGuardRevocationLib_INCLUDES)"\
    "MY_DEFINES=$(BootGuardRevocationLib_DEFINES)"\
    TYPE=LIBRARY\