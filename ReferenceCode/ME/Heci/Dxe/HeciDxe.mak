# MAK file for the ModulePart:HeciDxe
all : HeciDxe 

HeciDxe : $(BUILD_DIR)\HeciDxe.mak HeciDxeBin

$(BUILD_DIR)\HeciDxe.mak : $(HeciDxe_DIR)\$(@B).cif $(HeciDxe_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(HeciDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

HeciDxe_INCLUDES= \
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(INTEL_PCH_INCLUDES)

HeciDxe_LIBS=\
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
  $(EdkIIGlueBasePrintLib_LIB)\
  $(EFIDRIVERLIB)\
  $(RcFviDxeLib_LIB)\
  $(PchPlatformDxeLib_LIB)\
  $(INTEL_PCH_PROTOCOL_LIB)\

HeciDxe_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeHECI"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
#                     /D iFFS_FLAG \

HeciDxeBin : $(HeciDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\HeciDxe.mak all\
		"MY_INCLUDES=$(HeciDxe_INCLUDES)"\
		"MY_DEFINES=$(HeciDxe_DEFINES)"\
		GUID=55E76644-78A5-4a82-A900-7126A5798892 \
		ENTRY_POINT=_ModuleEntryPoint \
        EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(HeciDxe_DIR)\Hecidrv.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\
