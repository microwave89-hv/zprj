# MAK file for the eModule:AMTDxe

all : AMTDxe 


AMTDxe : $(BUILD_DIR)\AMTDxe.mak AMTDxeBin

$(BUILD_DIR)\AMTDxe.mak : $(AMTDxe_DIR)\$(@B).cif $(AMTDxe_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMTDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


AMTDxe_INCLUDES=\
  $(ME_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)


AMTDxe_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=ActiveManagementEntryPoint"\
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \


AMTDxe_LIB_LINKS =\
  $(EDKPROTOCOLLIB)\
  $(ProtocolLib_LIB)\
  $(EFISCRIPTLIB)\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(PchPlatformDxeLib_LIB)
 

AMTDxeBin : $(AMTDxe_LIB_LINKS) $(MeDxe_LIB_LINKS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\AMTDxe.mak all\
		"MY_INCLUDES=$(AMTDxe_INCLUDES)"\
        "MY_DEFINES=$(AMTDxe_DEFINES)"\
		GUID=D739F969-FB2D-4bc2-AFE7-081327D3FEDE \
		ENTRY_POINT=_ModuleEntryPoint \
		TYPE=BS_DRIVER \
        EDKIIModule=DXEDRIVER\
		DEPEX1=$(AMTDxe_DIR)\ActiveManagement.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\
