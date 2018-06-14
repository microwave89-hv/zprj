# MAK file for the Module Part: PowerMgmtS3

EDK : PowerMgmtS3

BUILD_PowerMgmtS3_DIR = $(BUILD_DIR)\$(PowerMgmtS3_DIR)

$(BUILD_DIR)\PowerMgmtS3.mak : $(PowerMgmtS3_DIR)\PowerMgmtS3.cif $(BUILD_RULES)
    $(CIF2MAK) $(PowerMgmtS3_DIR)\PowerMgmtS3.cif $(CIF2MAK_DEFAULTS)

PowerMgmtS3 : $(BUILD_DIR)\PowerMgmtS3.mak PowerMgmtS3Bin 

PowerMgmtS3_OBJECTS = \
    $(BUILD_PowerMgmtS3_DIR)\PowerMgmtS3.obj
	

PowerMgmtS3_MY_INCLUDES= \
    $(EDK_INCLUDES) \
    $(PROJECT_CPU_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)


PowerMgmtS3_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PowerMgmtS3SmmEntryPoint"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__

PowerMgmtS3_LIBS =\
    $(EFIGUIDLIB)\
    $(EDKFRAMEWORKGUIDLIB)\
    $(EDKPROTOCOLLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(CpuProtocolLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(PchPlatformSmmLib_LIB)

PowerMgmtS3Bin : $(PowerMgmtS3_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PowerMgmtS3.mak all\
    MAKEFILE=$(BUILD_DIR)\PowerMgmtS3.mak \
    "MY_INCLUDES=$(PowerMgmtS3_MY_INCLUDES)" \
    "MY_DEFINES=$(PowerMgmtS3_DEFINES)"\
    OBJECTS="$(PowerMgmtS3_OBJECTS)" \
    GUID=8F0B5301-C79B-44f1-8FD3-26D73E316700\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER \
    EDKIIModule=SMMDRIVER\
    DEPEX1=$(PowerMgmtS3_DIR)\PowerMgmtS3.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1
    
