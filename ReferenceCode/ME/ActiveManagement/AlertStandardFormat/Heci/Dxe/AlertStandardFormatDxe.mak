# MAK file for the ModulePart:AlertStandardFormatDxe

all : AlertStandardFormatDxe 

AlertStandardFormatDxe : $(BUILD_DIR)\AlertStandardFormatDxe.mak AlertStandardFormatDxeBin

$(BUILD_DIR)\AlertStandardFormatDxe.mak : $(AlertStandardFormatDxe_DIR)\$(@B).cif $(AlertStandardFormatDxe_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(AlertStandardFormatDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AlertStandardFormatDxe_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(AlertStandardFormat_INCLUDES)\
  $(IndustryStandard_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

AlertStandardFormatDxe_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(AmtLibDxe_LIB)\
  $(MeGuidLib_LIB)\
  $(MeProtocolLib_LIB)\
  $(MeAslUpdateLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\

AlertStandardFormatDxe_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=AlertStandardFormatDriverEntryPoint"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

AlertStandardFormatDxeBin : $(AlertStandardFormatDxe_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\AlertStandardFormatDxe.mak all\
		"MY_INCLUDES=$(AlertStandardFormatDxe_INCLUDES)" \
		"MY_DEFINES=$(AlertStandardFormatDxe_DEFINES)"\
		GUID=33c6406d-2f6b-41b5-8705-52bafb633c09 \
		ENTRY_POINT=_ModuleEntryPoint \
        EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(AlertStandardFormatDxe_DIR)\AlertStandardFormatDxe.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1
