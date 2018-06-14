# MAK file for the eModule:PowerManagement

EDK : CpuInitPei

BUILD_CpuInitPei_DIR = $(BUILD_DIR)\$(CpuInitPei_DIR)

$(BUILD_DIR)\CpuInitPei.mak : $(CpuInitPei_DIR)\CpuInitPei.cif $(BUILD_RULES)
    $(CIF2MAK) $(CpuInitPei_DIR)\CpuInitPei.cif $(CIF2MAK_DEFAULTS)

CpuInitPei : $(BUILD_DIR)\CpuInitPei.MAK CpuInitPeiBin 

CpuInitPei_OBJECTS = \
    $(BUILD_CpuInitPei_DIR)\CpuInitPeim.obj \
    $(BUILD_CpuInitPei_DIR)\CachePeim.obj \
    $(BUILD_CpuInitPei_DIR)\CpuOcInit.obj \
    $(BUILD_CpuInitPei_DIR)\PfatInit.obj \
    $(BUILD_CpuInitPei_DIR)\ia32\Cpu.obj \
    $(BUILD_CpuInitPei_DIR)\BootGuardInit.obj

CpuInitPei_MY_INCLUDES= \
    $(EDK_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(ME_INCLUDES)\
    $(INTEL_PCH_INCLUDES)

CpuInitPei_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PeimInitializeCpu"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
    /D __EDKII_GLUE_PEI_SERVICES_TABLE_POINTER_LIB_MM7__ \

CpuInitPei_LIBS =\
    $(CPU_PPI_LIB)\
    $(CPUIA32LIB)\
    $(EdkIIGluePeiServicesLib_LIB) \
    $(EdkIIGluePeiReportStatusCodeLib_LIB) \
    $(EfiRuntimeLib_LIB)\
    $(INTEL_PCH_PROTOCOL_LIB)\
    $(EFIRUNTIMELIB)\
    $(EDKFRAMEWORKPPILIB) \
    $(EdkIIGluePeiMemoryAllocationLib_LIB)\
    $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
    $(BUILD_DIR)\IA32\EdkIIGlueBaseLib.lib\
    $(IntelPchPpiLib_LIB)\
    $(EdkIIGlueBaseLibIA32_LIB)\
    $(EdkIIGluePeiHobLib_LIB) \
    $(CpuGuidLib_LIB) \
    $(PEIHOBLIB) \
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB) \
    $(EdkIIGlueBasePciExpressLib_LIB)\
    $(PchPlatformPeiLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(OcPlatformLib_LIB)\
    $(MeLibPpi_LIB)\
    $(BootGuardLib_LIB)\
    $(EFISCRIPTLIB)

CpuInitPeiBin : $(CpuInitPei_LIBS) $(HeciPei_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\CpuInitPei.mak all\
    NAME=CpuInitPei\
    MAKEFILE=$(BUILD_DIR)\CpuInitPei.mak \
    "MY_INCLUDES=$(CpuInitPei_MY_INCLUDES)" \
    "MY_DEFINES=$(CpuInitPei_DEFINES)"\
    OBJECTS="$(CpuInitPei_OBJECTS)" \
    GUID=01359D99-9446-456d-ADA4-50A711C03ADA\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(CpuInitPei_DIR)\CpuInitPeim.DXS \
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX  \
    COMPRESS=0
#-----------------------------------------------------------------------
