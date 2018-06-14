# MAK file for the ModulePart:PchMeUma

all: PchMeUma

$(BUILD_DIR)\PchMeUma.mak : $(PchMeUma_DIR)\PchMeUma.cif $(BUILD_RULES)
  $(CIF2MAK) $(PchMeUma_DIR)\PchMeUma.cif $(CIF2MAK_DEFAULTS)

PchMeUma: $(BUILD_DIR)\PchMeUma.mak PchMeUmaBin

PchMeUma_Pei_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  $(ME_INCLUDES)\
  /I$(MePttLibrary_DIR)\Pei


PchMeUma_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PchMeUmaEntry"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__\
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
!IF "$(IntelPTT_SUPPORT)"=="1"
  /D PTT_FLAG
!ENDIF

PchMeUma_LIBS =\
  $(EDKPROTOCOLLIB)\
  $(EDKFRAMEWORKPPILIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(IntelPchPpiLib_LIB)\
  $(EFIDRIVERLIB)\
  $(PEILIB)\
  $(MeLibPpi_LIB)\
  $(PchPlatformPeiLib_LIB)\
  $(MeGuidLib_LIB)\
  $(EdkIIGluePeiHobLib_LIB)\
  $(EFIGUIDLIB)\
  $(EFIPROTOCOLLIB)
##  $(EdkIIGluePeiFirmwarePerformanceLib_LIB)

PchMeUmaBin : $(PchMeUma_LIBS) $(HeciPei_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PchMeUma.mak all\
    NAME=PchMeUma\
    MAKEFILE=$(BUILD_DIR)\PchMeUma.mak \
    GUID=8C376010-2400-4d7d-B47B-9D851DF3C9D1\
    "MY_INCLUDES=$(PchMeUma_Pei_INCLUDES)" \
    "MY_DEFINES=$(PchMeUma_DEFINES)"\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(PchMeUma_DIR)\PchMeUma.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
    COMPRESS=0
