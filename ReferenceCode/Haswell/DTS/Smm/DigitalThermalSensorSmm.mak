# MAK file for the Module Part: PowerMgmtS3

EDK : DigitalThermalSensorSmm

BUILD_DigitalThermalSensorSmm_DIR = $(BUILD_DIR)\$(DigitalThermalSensorSmm_DIR)

$(BUILD_DIR)\DigitalThermalSensorSmm.mak : $(DigitalThermalSensorSmm_DIR)\DigitalThermalSensorSmm.cif $(BUILD_RULES)
    $(CIF2MAK) $(DigitalThermalSensorSmm_DIR)\DigitalThermalSensorSmm.cif $(CIF2MAK_DEFAULTS)

DigitalThermalSensorSmm : $(BUILD_DIR)\DigitalThermalSensorSmm.mak DigitalThermalSensorSmmBin 

DigitalThermalSensorSmm_OBJECTS = \
    $(BUILD_DigitalThermalSensorSmm_DIR)\DigitalThermalSensorSmm.obj	

DigitalThermalSensorSmm_MY_INCLUDES= \
    $(EDK_INCLUDES) \
    $(PROJECT_CPU_INCLUDES)\
    $(INTEL_PLATFORM_PROTOCOL_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)

DigitalThermalSensorSmm_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallDigitalThermalSensor"\
    /D PlatformPciExpressBaseAddress=$(PCIEX_BASE_ADDRESS) \
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
#    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__

DigitalThermalSensorSmm_LIBS =\
    $(EFIGUIDLIB)\
    $(EDKFRAMEWORKGUIDLIB)\
    $(EDKPROTOCOLLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(CpuProtocolLib_LIB)\
    $(EdkIIGlueBasePciExpressLib_LIB)\
    $(PpmAslUpdateLib_LIB)\
    $(SmmIoLib_LIB)\
    $(SmmKscLib_LIB)\
    $(DTSHookLib_LIB)\
    $(PchPlatformSmmLib_LIB)

DigitalThermalSensorSmmBin : $(DigitalThermalSensorSmm_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\DigitalThermalSensorSmm.mak all\
    MAKEFILE=$(BUILD_DIR)\DigitalThermalSensorSmm.mak \
    "MY_INCLUDES=$(DigitalThermalSensorSmm_MY_INCLUDES)" \
    "MY_DEFINES=$(DigitalThermalSensorSmm_DEFINES)"\
    OBJECTS="$(DigitalThermalSensorSmm_OBJECTS)" \
    GUID=77A6009E-116E-464D-8EF8-B35201A022DD\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER \
    EDKIIModule=SMMDRIVER\
    DEPEX1=$(DigitalThermalSensorSmm_DIR)\DigitalThermalSensorSmm.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1
    
