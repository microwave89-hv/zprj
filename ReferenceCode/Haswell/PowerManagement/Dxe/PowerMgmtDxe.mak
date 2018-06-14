# MAK file for the eModule:PowerManagement

EDK : PowerMgmtDxe

BUILD_PowerMgmtDxe_DIR = $(BUILD_DIR)\$(PowerMgmtDxe_DIR)

$(BUILD_DIR)\PowerMgmtDxe.mak : $(PowerMgmtDxe_DIR)\PowerMgmtDxe.cif $(BUILD_RULES)
    $(CIF2MAK) $(PowerMgmtDxe_DIR)\PowerMgmtDxe.cif $(CIF2MAK_DEFAULTS)

PowerMgmtDxe : $(BUILD_DIR)\PowerMgmtDxe.MAK PowerMgmtDxeBin 

PowerMgmtDxe_OBJECTS = \
    $(BUILD_PowerMgmtDxe_DIR)\IdleStates.obj \
    $(BUILD_PowerMgmtDxe_DIR)\MiscFunctions.obj \
    $(BUILD_PowerMgmtDxe_DIR)\PerformanceStates.obj \
    $(BUILD_PowerMgmtDxe_DIR)\PowerLimits.obj \
    $(BUILD_PowerMgmtDxe_DIR)\Thermal.obj \
    $(BUILD_PowerMgmtDxe_DIR)\PowerMgmtInit.obj

PowerMgmtDxe_MY_INCLUDES= \
    $(EdkIIGlueLib_INCLUDES)\
    /I$(EdkIIGlueBaseLib_DIR)\
    $(EDK_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(INTEL_PLATFORM_PROTOCOL_INCLUDES)

PowerMgmtDxe_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePowerManagement"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__
    
PowerMgmtDxe_LIBS =\
    $(EFIGUIDLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EDKPROTOCOLLIB)\
    $(EFISCRIPTLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueBaseTimerLibLocalApic_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(EdkIIGlueHiiLib_LIB)\
    $(EFIDRIVERLIB)\
    $(UEFIEFIIFRSUPPORTLIB)\
    $(CpuProtocolLib_LIB)\
    $(CpuGuidLib_LIB)\
    $(PchPlatformDxeLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(PpmAslUpdateLib_LIB)


PowerMgmtDxeBin : $(PowerMgmtDxe_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PowerMgmtDxe.mak all\
    NAME=PowerMgmtDxe\
    MAKEFILE=$(BUILD_DIR)\PowerMgmtDxe.mak \
    "MY_INCLUDES=$(PowerMgmtDxe_MY_INCLUDES)" \
    "MY_DEFINES=$(PowerMgmtDxe_DEFINES)"\
    OBJECTS="$(PowerMgmtDxe_OBJECTS)" \
    GUID=f7731b4c-58a2-4df4-8980-5645d39ece58\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER \
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(PowerMgmtDxe_DIR)\PowerMgmtDxe.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1
