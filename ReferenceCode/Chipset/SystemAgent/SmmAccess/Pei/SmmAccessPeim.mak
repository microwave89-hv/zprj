#---------------------------------------------------------------------------
#   Create SmmAccessPeim Driver
#---------------------------------------------------------------------------
EDK : SmmAccessPeim
SmmAccessPeim : $(BUILD_DIR)\SmmAccessPeim.mak SmmAccessPeimBin

$(BUILD_DIR)\SmmAccessPeim.mak : $(SmmAccessPeim_DIR)\$(@B).cif $(SmmAccessPeim_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SmmAccessPeim_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmAccessPeim_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  $(INTEL_CPU_INCLUDES)\

SmmAccessPeim_DEFINES = $(MY_DEFINES)\
            /DMDE_CPU_IA32\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SmmAccessPeimEntryPoint"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
            /D __EDKII_GLUE_PEI_HOB_LIB__\

SmmAccessPeim_LIB_LINKS =\
            $(EDKFRAMEWORKGUIDLIB)\
            $(EDKPPILIB)\
            $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
            $(EdkIIGluePeiReportStatusCodeLib_LIB)\
            $(EdkIIGluePeiServicesLib_LIB)\
            $(EdkIIGluePeiMemoryAllocationLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EdkIIGlueBasePciExpressLib_LIB)\
            $(EdkIIGluePeiHobLib_LIB)\
            $(IntelSaSampleCodePpiLib_LIB)\

SmmAccessPeimBin: $(SmmAccessPeim_LIB_LINKS) 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\SmmAccessPeim.mak all\
            NAME=SmmAccessPeim\
            MAKEFILE=$(BUILD_DIR)\SmmAccessPeim.mak \
            GUID=6ECFCE51-5724-450c-A38A-58553E954422\
            "MY_INCLUDES=$(SmmAccessPeim_INCLUDES)"\
            "MY_DEFINES=$(SmmAccessPeim_DEFINES)"\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(SmmAccessPeim_DIR)\SmmAccessPeim.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
            COMPRESS=0
