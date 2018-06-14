# MAK file for the ModulePart:AslUpdateLib
all : BootGuardTpmEventLogLib

$(BUILD_DIR)\BootGuardTpmEventLogLib.lib : BootGuardTpmEventLogLib

BootGuardTpmEventLogLib : $(BUILD_DIR)\BootGuardTpmEventLogLib.mak BootGuardTpmEventLogLibBin

$(BUILD_DIR)\BootGuardTpmEventLogLib.mak : $(BootGuardTpmEventLogLib_DIR)\$(@B).cif $(BootGuardTpmEventLogLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(BootGuardTpmEventLogLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

BootGuardTpmEventLogLib_INCLUDES=\
    $(PROJECT_CPU_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(iAMT_INCLUDES)\
    $(IndustryStandard_INCLUDES)

BootGuardTpmEventLogLib_DEFINES=\
    $(MY_DEFINES)\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__\
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

BootGuardTpmEventLogLib_LIBS=\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\

BootGuardTpmEventLogLibBin : 
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\BootGuardTpmEventLogLib.mak all \
    "MY_INCLUDES=$(BootGuardTpmEventLogLib_INCLUDES)"\
    "MY_DEFINES=$(BootGuardTpmEventLogLib_DEFINES)"\
    TYPE=LIBRARY\