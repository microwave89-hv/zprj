# MAK file for the ModulePart:MeFwDowngrade
all : MeFwDowngrade

MeFwDowngrade : $(BUILD_DIR)\MeFwDowngrade.mak MeFwDowngradeBin

$(BUILD_DIR)\MeFwDowngrade.mak : $(MeFwDowngrade_DIR)\$(@B).cif $(MeFwDowngrade_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MeFwDowngrade_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeFwDowngrade_INCLUDES= \
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

MeFwDowngrade_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
  $(AmtLibDxe_LIB)\
  $(MeGuidLib_LIB)\
  $(INTEL_PCH_PROTOCOL_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIGUIDLIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EFIDRIVERLIB)\
  $(PchPlatformDxeLib_LIB)

MeFwDowngrade_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=MeFwDowngradeEntryPoint"\
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\

MeFwDowngradeBin : $(MeFwDowngrade_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\MeFwDowngrade.mak all\
		"MY_INCLUDES=$(MeFwDowngrade_INCLUDES)"\
		"MY_DEFINES=$(MeFwDowngrade_DEFINES)"\
		GUID=5820EEB4-C135-4854-9D2A-AA9EFC4475E9 \
		ENTRY_POINT=_ModuleEntryPoint \
                EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(MeFwDowngrade_DIR)\MeFwDowngrade.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\
