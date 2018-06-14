# MAK file for the ModulePart:PTTHciSmm
all : PttHciSmm

PttHciSmm : $(BUILD_DIR)\PttHciSmm.mak PttHciSmmBin

$(BUILD_DIR)\PttHciSmm.mak : $(PttHciSmm_DIR)\PttHciSmm.cif $(PttHciSmm_DIR)\PttHciSmm.mak $(CP_BUILD_RULES)
	$(CIF2MAK) $(PttHciSmm_DIR)\PttHciSmm.cif $(CIF2MAK_DEFAULTS)

PTTHciSmm_INCLUDES= \
  $(ACPI_PLATFORM_INCLUDES)\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  /I$(INTEL_COUGAR_POINT_INCLUDE_DIR)\
  /IReferenceCode\ME\SampleCode\
  $(PROJECT_CPU_INCLUDES)

PTTHciSmm_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(MeProtocolLib_LIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
  $(MeGuidLib_LIB)\
  $(EFISCRIPTLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIGUIDLIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueDxeServicesTableLib_LIB)\
  $(EFIDRIVERLIB)\
  $(RcFviDxeLib_LIB)\
  $(PchPlatformDxeLib_LIB)\
  $(CpuPlatformLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\
  $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\

PTTHciSmm_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeFtpmSmm"\
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_HOB_LIB__ \
  /D PTT_FLAG

PTTHciSmmBin : $(PTTHciSmm_LIBS) 
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PttHciSmm.mak all\
    MAKEFILE=$(BUILD_DIR)\PttHciSmm.mak\
    "MY_INCLUDES=$(PTTHciSmm_INCLUDES)"\
    "MY_DEFINES=$(PTTHciSmm_DEFINES)"\
    GUID=8029a5b5-4088-48d2-96e0-f7052bc0a842\
    DEPEX1=$(PttHciSmm_DIR)\PTTHciSmm.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER\
    EDKIIModule=SMMDRIVER\
    COMPRESS=1