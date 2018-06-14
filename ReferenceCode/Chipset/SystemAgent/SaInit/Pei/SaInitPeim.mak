#---------------------------------------------------------------------------
#   Create SaInitPeim module
#---------------------------------------------------------------------------
all : SaInitPeim
SaInitPeim : $(BUILD_DIR)\SaInitPeim.mak SaInitPeimBin

$(BUILD_DIR)\SaInitPeim.mak : $(SaInitPeim_DIR)\$(@B).cif $(SaInitPeim_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SaInitPeim_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SaInitPeim_INCLUDES=\
            $(INTEL_MCH_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(PROJECT_CPU_INCLUDES)\
            $(RAPIDSTART_INCLUDES)\
            $(PchMeUma_INCLUDES)\
            /I$(PROJECT_CPU_ROOT)\Library\OverclockingLib \

SaInitPeim_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SaInitPeiEntryPoint"\
            /D __EDKII_GLUE_BASE_LIB__ \
            /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

SaInitPeim_LIB_LINKS =\
            $(INTEL_SA_PPI_LIB) \
            $(IntelPchPpiLib_LIB)\
            $(EDKFRAMEWORKPPILIB) \
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB) \
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB) \
            $(EdkIIGluePeiReportStatusCodeLib_LIB) \
            $(EdkIIGluePeiServicesLib_LIB) \
            $(EdkIIGluePeiMemoryAllocationLib_LIB) \
            $(EdkIIGlueBasePciLibPciExpress_LIB) \
            $(EdkIIGlueBasePciExpressLib_LIB)\
            $(PEILIB)\
            $(SaGuidLib_LIB)\
            $(EdkIIGlueBasePciExpressLib_LIB)\
            $(EdkIIGlueBasePostCodeLibPort80_LIB)\
            $(CPU_PPI_LIB)\
            $(CpuPlatformLib_LIB)\
            $(PchPlatformPeiLib_LIB)\
            $(EdkIIGluePeiHobLib_LIB)\
            $(OcPlatformLib_LIB)\
#
# Uncomment all the RapidStart include directories and library if RapidStart is supported
#
#  RapidStartPpiLib
            $(RapidStartPpiLib_LIB)\
            $(MeLibPpi_LIB)

SaInitPeimBin: $(SaInitPeim_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\SaInitPeim.mak all \
            "MY_INCLUDES=$(SaInitPeim_INCLUDES)"\
            "MY_DEFINES=$(SaInitPeim_DEFINES)"\
            NAME=SaInitPeim\
            MAKEFILE=$(BUILD_DIR)\SaInitPeim.mak \
            GUID=FD236AE7-0791-48c4-B29E-29BDEEE1A811\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(SaInitPeim_DIR)\SaInitPeim.dxs\
            DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
            COMPRESS=0
