#---------------------------------------------------------------------------
#   Create SaInitDxe Driver
#---------------------------------------------------------------------------
EDK : SaInitDxe

SaInitDxe: $(BUILD_DIR)\SaInitDxe.mak SaInitDxeBin

$(BUILD_DIR)\SaInitDxe.mak : $(SaInitDxe_DIR)\$(@B).cif $(SaInitDxe_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SaInitDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SaInitDxe_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_MCH_INCLUDES) \
  $(INTEL_PCH_INCLUDES)\
  $(IndustryStandard_INCLUDES)\
  $(INTEL_PLATFORM_PROTOCOL_INCLUDES)\
  $(PROJECT_CPU_INCLUDES)\
  /I$(INTEL_SYSTEM_AGENT_DIR)\Library\SaPcieLib\Common\
  /I$(INTEL_SYSTEM_AGENT_DIR)\SampleCode\

SaInitDxe_DEFINES =$(MY_DEFINES)\
  /D "__EDKII_GLUE_MODULE_ENTRY_POINT__=SaInitEntryPoint" \
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_DXE_HOB_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

SaInitDxe_LIB_LINKS =\
    $(EFIPROTOCOLLIB)\
    $(EDKGUIDLIB)\
    $(EFICOMMONLIB)\
    $(EFISCRIPTLIB)\
    $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(INTEL_SA_PROTOCOL_LIB)\
    $(INTEL_PCH_PROTOCOL_LIB)\
    $(IntelPlatformProtocolLib_LIB)\
!IF $(EFI_SPECIFICATION_VERSION) >= 0x0002000A
    $(UEFIEFIIFRSUPPORTLIB)\
!ELSE
    $(EFIIFRSUPPORTLIB) \
!ENDIF
    $(SaGuidLib_LIB)\
  	$(EdkIIGlueBasePciExpressLib_LIB)\
    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EDKPROTOCOLLIB)\
    $(RcFviDxeLib_LIB)\
    $(PchPlatformDxeLib_LIB)\
    $(CpuPlatformLib_LIB)\
#
# Comment out SaPcieDxeLib if ASPM initialization in DXE phase was not supported
#
    $(SaPcieDxeLib_LIB)\

SaInitDxeBin: $(SaInitDxe_LIB_LINKS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\SaInitDxe.mak all \
    "MY_INCLUDES=$(SaInitDxe_INCLUDES)"\
    "MY_DEFINES=$(SaInitDxe_DEFINES)"\
    GUID=DE23ACEE-CF55-4fb6-AA77-984AB53DE811\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=BS_DRIVER\
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(SaInitDxe_DIR)\SaInit.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1
