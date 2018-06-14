#---------------------------------------------------------------------------
#   Create PchS3Pei module
#---------------------------------------------------------------------------
EDK : PchS3Peim
PchS3Peim : $(BUILD_DIR)\PchS3Peim.mak PchS3PeimBin


$(BUILD_DIR)\PchS3Peim.mak : $(PchS3Peim_DIR)\$(@B).cif $(PchS3Peim_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchS3Peim_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchS3Peim_INCLUDES=\
	$(EdkIIGlueLib_INCLUDES)\
	$(INTEL_PCH_INCLUDES)\

PchS3Peim_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchS3Peim"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_PEI_HOB_LIB__ \

PchS3Peim_LIB_LINKS=\
  $(IntelPchPpiLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB) \
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(WdtCommonPeiLib_LIB)\
  $(EDKFRAMEWORKPPILIB)\
  $(EdkIIGluePeiHobLib_LIB)\
  $(IntelSaSampleCodePpiLib_LIB)\
  $(PchPlatformPeiLib_LIB)\
  $(PchPciExpressHelpersPeiLib_LIB)\
  $(PEILIB)\

PchS3PeimBin: $(PchS3Peim_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchS3Peim.mak all \
            "MY_INCLUDES=$(PchS3Peim_INCLUDES)"\
            "MY_DEFINES=$(PchS3Peim_DEFINES)"\
            GUID=271DD6F2-54CB-45e6-8585-8C923C1AC706\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchS3Peim_DIR)\PchS3Peim.dxs\
            DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
            COMPRESS=0