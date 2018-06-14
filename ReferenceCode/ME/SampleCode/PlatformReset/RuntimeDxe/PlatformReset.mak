#---------------------------------------------------------------------------
#   Create PlatformReset Driver
#---------------------------------------------------------------------------

All : PlatformReset

PlatformReset : $(BUILD_DIR)\PlatformReset.mak PlatformResetBin

$(BUILD_DIR)\PlatformReset.mak : $(PlatformReset_DIR)\$(@B).cif $(PlatformReset_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PlatformReset_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PlatformReset_INCLUDES=\
    $(ME_INCLUDES) \
    /I$(ME_DIR)\SampleCode \
    $(INTEL_PCH_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\

PlatformReset_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePlatformReset"\
  /D"__EDKII_GLUE_SET_VIRTUAL_ADDRESS_MAP_EVENT_HANDLER__=PchResetVirtualddressChangeEvent"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

PlatformReset_LIBS=\
    $(MeLibDxe_LIB)\
    $(MeSampleCodeProtocolLib_LIB)\
    $(INTEL_PCH_PROTOCOL_LIB)\
    $(EDKPROTOCOLLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(IntelMpgProtocolLib_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(MePlatformGetResetTypeProtocolLib_LIB)
#    $(EFIDRIVERLIB)\
#    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
#    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\


PlatformResetBin : $(PlatformReset_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PlatformReset.mak all \
    GUID=9A9A912B-5F53-4586-8820-704485A29D21\
    "MY_INCLUDES=$(PlatformReset_INCLUDES)"\
    "MY_DEFINES=$(PlatformReset_DEFINES)"\
    ENTRY_POINT=_ModuleEntryPoint\
    TYPE=RT_DRIVER\
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(PlatformReset_DIR)\PlatformReset.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1


