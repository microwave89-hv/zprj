# MAK file for the ModulePart:TxtPei

all : TxtPei

TxtPei : $(BUILD_DIR)\TxtPei.mak TxtPeiBin TxtPeiAp.bin $(BUILD_DIR)\TxtPeiap.ffs

$(BUILD_DIR)\TxtPei.mak : $(TxtPei_DIR)\$(@B).cif $(TxtPei_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TxtPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MY_DEFINES=\
  /DAMI_MICROCODE_PPI\
!IF "$(TXT_DEBUG_INFO)"=="1"
  /D"TXT_DEBUG_INFO=1"\
!ELSE
  /D"TXT_DEBUG_INFO=0"\
!ENDIF

TxtPei_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(TXT_INCLUDES)\
  $(PROJECT_CPU_INCLUDES)\
  $(PROJECT_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  $(TCG_INCLUDES)\

TxtPei_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PeimEntry"\
  /D PlatformPciExpressBaseAddress=$(PCIEX_BASE_ADDRESS) \
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_PEI_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__\
  /D __EDKII_GLUE_PEI_SERVICES_TABLE_POINTER_LIB_MM7__ \

TxtPei_OBJECTS=\
  $(BUILD_DIR)\$(TxtPei_DIR)\TxtPei.obj\
  $(BUILD_DIR)\$(TxtPei_DIR)\TxtPeiLib.obj\
  $(BUILD_DIR)\$(TxtPei_DIR)\Ia32\TxtPeiBsp.obj

TxtPei_LIBS=\
  $(EDKFRAMEWORKPPILIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(BUILD_DIR)\IA32\EdkIIGlueBaseLib.lib\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGluePeiDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(EdkIIGluePeiHobLib_LIB)\
  $(EdkIIGluePeiMemoryAllocationLib_LIB)\
  $(CpuGuidLib_LIB)\
  $(CPU_PPI_LIB)\
  $(SaGuidLib_LIB)\
  $(PEIHOBLIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueBasePciExpressLib_LIB)\
  $(PchPlatformPeiLib_LIB)\
  $(CpuPlatformLib_LIB)\
  $(BootGuardLib_LIB)\
  $(TxtLib_LIB)

TxtPeiBin : $(TxtPei_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\TxtPei.mak all\
    "MY_INCLUDES=$(TxtPei_INCLUDES)"\
    "MY_DEFINES=$(TxtPei_DEFINES)"\
    "OBJECTS=$(TxtPei_OBJECTS)" \
    "AFLAGS=$(AFLAGS)  $(PROJECT_CPU_INCLUDES)"\
    GUID=CA9D8617-D652-403b-B6C5-BA47570116AD\
    ENTRY_POINT=_ModuleEntryPoint\
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(TxtPei_DIR)\TxtPei.dxs \
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
    COMPRESS=0\

TxtPeiAp.bin: $(BUILD_DIR)\TxtPeiap.bin

$(BUILD_DIR)\TxtPeiap.bin: $(BUILD_DIR)\TxtPeiAp.obj

$(BUILD_DIR)\TxtPeiAp.obj:$(TxtPei_DIR)\Ia32\TxtPeiAp.asm16
  $(ASM) /c /nologo $(PROJECT_CPU_INCLUDES) /Fo$(BUILD_DIR)\TxtPeiAp.obj $(TxtPei_DIR)\Ia32\TxtPeiAp.asm16
  $(ASMLINK) $(BUILD_DIR)\TxtPeiAp.obj, $*.exe, $*.map,,,
  exe2bin $*.exe $*.bin

$(BUILD_DIR)\TxtPeiap.ffs : $(BUILD_DIR)\TxtPeiap.bin
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
		GUID=$(AP_GUID) \
		TYPE=EFI_FV_FILETYPE_RAW \
		FFS_CHECKSUM=0 \
		FFS_ALIGNMENT=5 \
		RAWFILE=$(BUILD_DIR)\TxtPeiap.bin \
		COMPRESS=0 \
		FFSFILE=$@ \
		NAME=DummyName

TXT_AP_FIXUP:
    $(TxtTools_DIR)\STAFixup.exe $(AP_GUID) $(AMI_ROM) $(AP_FIXUP_FILE) $(AP_OFFSET)

AFTER_ROM: TXT_AP_FIXUP
