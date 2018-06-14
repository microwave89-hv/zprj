# MAK file for the ModulePart:AlertStandardFormat
all : AlertStandardFormatPei 

AlertStandardFormatPei : $(BUILD_DIR)\AlertStandardFormatPei.mak AlertStandardFormatPeiBin

$(BUILD_DIR)\AlertStandardFormatPei.mak : $(AlertStandardFormatPei_DIR)\$(@B).cif $(AlertStandardFormatPei_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(AlertStandardFormatPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AlertStandardFormatPei_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(AlertStandardFormat_INCLUDES)\
  $(IndustryStandard_INCLUDES)\

AlertStandardFormatPei_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(MeGuidLib_LIB)\
  $(MeLibPpi_LIB)\
  $(AmtLibPei_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(EdkIIGluePeiHobLib_LIB)\

AlertStandardFormatPei_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=AlertStandardFormatDriverPeiEntryPoint"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__\
  /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \

AlertStandardFormatPeiBin : $(AlertStandardFormatPei_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\AlertStandardFormatPei.mak all\
    "MY_INCLUDES=$(AlertStandardFormatPei_INCLUDES)"\
    "MY_DEFINES=$(AlertStandardFormatPei_DEFINES)"\
    GUID=3e4817fd-2742-4351-b59f-91493280329c \
    ENTRY_POINT=_ModuleEntryPoint \
    EDKIIModule=PEIM\
    TYPE=PEIM \
    DEPEX1=$(AlertStandardFormatPei_DIR)\AlertStandardFormatPei.dxs \
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
    COMPRESS=0
