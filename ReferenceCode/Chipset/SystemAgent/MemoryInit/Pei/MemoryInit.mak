# MAK file for the ModulePart:MemoryInit

all: $(BUILD_DIR)\MemoryInit.mak MemoryInitBin

$(BUILD_DIR)\MemoryInit.mak : $(MemoryInit_DIR)\$(@B).cif $(MemoryInit_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(MemoryInit_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MemoryInitBin_INCLUDES=\
    $(PROJECT_CPU_INCLUDES) \
    /I$(NB_BOARD_DIR)\
    /I$(MemoryInit_DIR) \
    /I$(MemoryInit_DIR)\Source\Include \
    /I$(MemoryInit_DIR)\Source\Include\MrcRegisters \
    /I$(MemoryInit_DIR)\Source\AddrDecode \
    /I$(MemoryInit_DIR)\Source\Api \
    /I$(INTEL_SYSTEM_AGENT_DIR)\SampleCode \
    /I$(MemoryInit_DIR)\Source\ReadTraining \
    /I$(MemoryInit_DIR)\Source\WriteTraining \
    /I$(MemoryInit_DIR)\Source\SpdProcessing \
    /I$(MemoryInit_DIR)\Source\McConfiguration \
    /I$(MemoryInit_DIR)\Source\AggressiveTraining \
    /I$(INTEL_SA_PPI_LIB_DIR)\EviPeiInit \
    /I$(AcpiPlatform_DIR)\Include \
    /I$(PROJECT_DIR)\Include \
    $(PchMeUma_INCLUDES) \
    $(ME_INCLUDES) \
    $(INTEL_MCH_INCLUDES) \
    $(INTEL_PCH_INCLUDES) \
    $(EDK_INCLUDES) \
    $(TXT_INCLUDES) \
    $(EdkIIGlueLib_INCLUDES) \
    $(RAPIDSTART_INCLUDES) \
    /I$(RapidStartCommonLib_DIR) \

MemoryInitBin_LIBS=\
    $(AMIPEILIB) \
    $(CPUIA32LIB) \
    $(IntelSaSampleCodePpiLib_LIB) \
    $(EDKPPILIB) \
    $(EDKGUIDLIB) \
    $(INTEL_SA_PPI_LIB) \
    $(MeLibPpi_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseLibIA32_LIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB) \
    $(EdkIIGluePeiDebugLibReportStatusCode_LIB) \
    $(EdkIIGluePeiReportStatusCodeLib_LIB) \
    $(EdkIIGluePeiServicesLib_LIB) \
    $(EdkIIGluePeiMemoryAllocationLib_LIB) \
    $(EdkIIGluePeiHobLib_LIB) \
    $(EdkIIGluePeiSmbusLib_LIB) \
    $(PEILIB)\
    $(RapidStartPpiLib_LIB)\
    $(RapidStartPeiLib_LIB)\
    $(RapidStartCommonPeiLib_LIB)\
    $(PchPlatformPeiLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB) \
    $(IntelPchPpiLib_LIB)\
    $(EdkIIGlueBasePrintLib_LIB) \
    $(CPU_PPI_LIB) \
    $(CpuPlatformLib_LIB)\
    $(SaGuidLib_LIB)\
    $(TxtLib_LIB)

MemoryInitBin_DEFINES=\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PeimMemoryInit"\
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
    /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_PEI_HOB_LIB__ \
#!IFDEF SOFTSDV_FLAG
#    /D MRC_FLAG_SKIP_TRAINING\
#    /D MRC_FLAG_SKIP_JEDEC_RESET\
#!ENDIF # SOFTSDV_FLAG

#    /DINCLUDE_ME_CODE\
#    /DSFF_SUPPORT\
#    /DDDR2_SUPPORT\
#    /DDDR3_SUPPORT\
#    /DDDR3LV_SUPPORT\
#    /DTHERMAL_SUPPORT\
#    /DPRE_PRODUCTION_WA_SUPPORT\
#    /DREAD_TRAINING_SUPPORT\
#    /DWRITE_TRAINING_SUPPORT\
#    /D"SO_DIMM_SUPPORT=1"

MemoryInitBin: $(MemoryInitBin_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\MemoryInit.mak all\
    NAME=MemoryInit\
    MAKEFILE=$(BUILD_DIR)\MemoryInit.mak \
    "CFLAGS=$(CFLAGS) /Oi /Gs65536 /Zi /Gm" \
    "MY_INCLUDES=$(MemoryInitBin_INCLUDES)"\
    "MY_DEFINES=$(MemoryInitBin_DEFINES)"\
    GUID=3B42EF57-16D3-44CB-8632-9FDB06B41451\
    ENTRY_POINT=_ModuleEntryPoint\
    DEPEX1=$(MemoryInit_DIR)\MemoryInit.dxs\
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
    TYPE=PEIM\
    EDKIIModule=PEIM\
    COMPRESS=0

#
# We use the following Microsoft Visual C++ Compiler options:
#  /Oi      - Generate intrinsic functions (memset, memcpy etc.)
#  /Gs32768 - Limit stack checking calls to 32KB (default is 4KB)
#  /FAsc    - may be used to produce the *.COD files (intermediate assembly)
#
