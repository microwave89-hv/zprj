# MAK file for the ModulePart:HeciPei

all: HeciPei

$(BUILD_DIR)\HeciPei.mak : $(HeciPei_DIR)\HeciPei.cif $(BUILD_RULES)
  $(CIF2MAK) $(HeciPei_DIR)\HeciPei.cif $(CIF2MAK_DEFAULTS)

HeciPei: $(BUILD_DIR)\HeciPei.mak HeciPeiBin

HeciPei_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(INTEL_PCH_INCLUDES)


HeciPei_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PeimHeciInit"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__\
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

HeciPei_LIBS =\
  $(EDKPROTOCOLLIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
 

HeciPeiBin : $(EDKFRAMEWORKPPILIB) $(MeLibPpi_LIB) $(HeciPei_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\HeciPei.mak all\
    NAME=HeciPei\
    MAKEFILE=$(BUILD_DIR)\HeciPei.mak \
    GUID=9cf30325-dc5c-4556-a8b0-74215c5f7fc4\
    "MY_INCLUDES=$(HeciPei_INCLUDES)" \
    "MY_DEFINES=$(HeciPei_DEFINES)"\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(HeciPei_DIR)\HeciInit.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
    COMPRESS=0
