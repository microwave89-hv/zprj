# MAK file for the eModule: CpuS3Peim

EDK : CpuS3Peim

BUILD_CpuS3Peim_DIR = $(BUILD_DIR)\$(CpuS3Peim_DIR)

$(BUILD_DIR)\CpuS3Peim.mak : $(CpuS3Peim_DIR)\CpuS3Peim.cif $(BUILD_RULES)
    $(CIF2MAK) $(CpuS3Peim_DIR)\CpuS3Peim.cif $(CIF2MAK_DEFAULTS)

CpuS3Peim : $(BUILD_DIR)\CpuS3Peim.MAK CpuS3PeimBin 

CpuS3Peim_OBJECTS = \
    $(BUILD_CpuS3Peim_DIR)\CpuS3Peim.obj \
    $(BUILD_CpuS3Peim_DIR)\MtrrSync.obj \
    $(BUILD_CpuS3Peim_DIR)\Microcode.obj \
    $(BUILD_CpuS3Peim_DIR)\MpFuncs.obj \
    $(BUILD_CpuS3Peim_DIR)\CpuAsm.obj

CpuS3Peim_MY_INCLUDES= \
    $(EDK_INCLUDES) \
    /I$(PROJECT_CPU_ROOT) \
    /I$(PROJECT_CPU_ROOT)\Include \
    $(PROJECT_CPU_INCLUDES)\
    /I$(INTEL_SYSTEM_AGENT_DIR) \
    /I$(INTEL_SYSTEM_AGENT_DIR)\Include \
    /I$(INTEL_SYSTEM_AGENT_DIR)\SampleCode \

#-    $(CPU_INCLUDES)\

CpuS3Peim_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeCpu"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_TABLE_POINTER_LIB_MM7__ \


CpuS3Peim_LIBS =\
    $(EDKFRAMEWORKPPILIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB) \
    $(EdkIIGluePeiDebugLibReportStatusCode_LIB) \
    $(EdkIIGluePeiReportStatusCodeLib_LIB)\
    $(EdkIIGluePeiServicesLib_LIB)\
    $(EDKPPILIB)\
    $(EdkIIGlueBaseTimerLibLocalApic_LIB)\
    $(EdkIIGluePeiHobLib_LIB) \
    $(CPU_PPI_LIB)\
    $(INTEL_SA_PPI_LIB)\
    $(CpuGuidLib_LIB)\
    $(CPUIA32LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EdkIIGlueBasePciExpressLib_LIB)\
    $(PchPlatformPeiLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(BootGuardLib_LIB)\
    $(IntelSaSampleCodePpiLib_LIB)\
  
CpuS3PeimBin : $(CpuS3Peim_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\CpuS3Peim.mak all\
    NAME=CpuS3Peim\
    MAKEFILE=$(BUILD_DIR)\CpuS3Peim.mak \
    "MY_INCLUDES=$(CpuS3Peim_MY_INCLUDES)" \
    "MY_DEFINES=$(CpuS3Peim_DEFINES)"\
    OBJECTS="$(CpuS3Peim_OBJECTS)" \
    GUID=C866BD71-7C79-4BF1-A93B-066B830D8F9A\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(CpuS3Peim_DIR)\CpuS3Peim.DXS \
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX  \
    COMPRESS=0
#-----------------------------------------------------------------------
