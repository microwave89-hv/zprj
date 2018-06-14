# MAK file for the ModulePart:AtAmDxe

all : AtAmDxe

AtAmDxe : $(BUILD_DIR)\AtAmDxe.mak AtAmDxeBin

$(BUILD_DIR)\AtAmDxe.mak : $(AtAmDxe_DIR)\$(@B).cif $(AtAmDxe_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AtAmDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


AtAmDxe_INCLUDES=\
  $(AT_INCLUDES)\
  $(ME_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(EdkIIGlueInclude)\
  $(IndustryStandard_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\


AtAmDxe_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=AtAmEntryPoint"\
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \


AtAmDxe_LIB_LINKS =\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(INTEL_PCH_PROTOCOL_LIB)\
  $(EdkIIGlueBasePrintLib_LIB) \
  $(EdkIIGlueUefiLib_LIB)\
  $(TdtProtocolLib_LIB)\
  $(ProtocolLib_LIB)\
  $(EFISCRIPTLIB)\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(AmtGuidLib_LIB)\
  $(EFIGUIDLIB)\
  $(EDKPROTOCOLLIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EFIDRIVERLIB)\
  $(MeChipsetDxeLib_LIB)\
  $(AtDxeLib_LIB)\
  $(PchPlatformDxeLib_LIB)
  


# MAK file for the eModule:AtAmDxe

AtAmDxeBin : $(AtAmDxe_LIB_LINKS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\AtAmDxe.mak all\
		"MY_INCLUDES=$(AtAmDxe_INCLUDES)"\
        	"MY_DEFINES=$(AtAmDxe_DEFINES)"\
		GUID=C810485E-D0EC-4e98-AAB5-120C7E554428\
		ENTRY_POINT=_ModuleEntryPoint \
		TYPE=BS_DRIVER \
        	EDKIIModule=DXEDRIVER\
		DEPEX1=$(AtAmDxe_DIR)\AtAm.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\


