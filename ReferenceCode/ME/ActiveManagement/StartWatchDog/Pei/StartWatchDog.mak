# MAK file for the ModulePart:StartWatchDog

all: StartWatchDog

StartWatchDog: $(BUILD_DIR)\StartWatchDog.mak StartWatchDogBin

$(BUILD_DIR)\StartWatchDog.mak : $(StartWatchDog_DIR)\$(@B).cif $(StartWatchDog_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(StartWatchDog_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


StartWatchDog_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  
StartWatchDog_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PeiInitStartWatchDog"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__\
  /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \

StartWatchDog_LIBS =\
  $(EDKPROTOCOLLIB)\
  $(AmtLibPei_LIB)\
  $(MeLibPpi_LIB)\
  $(MeLibPei_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(EdkIIGluePeiMemoryAllocationLib_LIB)\

StartWatchDogBin : $(StartWatchDog_LIBS)
        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
                /f $(BUILD_DIR)\StartWatchDog.mak all\
                NAME=StartWatchDog\
                MAKEFILE=$(BUILD_DIR)\StartWatchDog.mak \
                GUID=5479E09C-2E74-481b-89F8-B0172E388D1F\
                "MY_INCLUDES=$(StartWatchDog_INCLUDES)"\
                "MY_DEFINES=$(StartWatchDog_DEFINES)"\
                ENTRY_POINT=_ModuleEntryPoint \
                TYPE=PEIM \
                EDKIIModule=PEIM\
                DEPEX1=$(StartWatchDog_DIR)\StartWatchDog.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
                COMPRESS=0
