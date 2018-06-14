# MAK file for the ModulePart:TxtDxe
#-jeff debug
all : TxtDxe

TxtDxe : $(BUILD_DIR)\TxtDxe.mak TxtDxeBin

$(BUILD_DIR)\TxtDxe.mak : $(TxtDxe_DIR)\$(@B).cif $(TxtDxe_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(TxtDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TxtDxe_INCLUDES=\
  $(MISCFRAMEWORK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(PROJECT_CPU_INCLUDES)\
  $(TXT_INCLUDES)\

TxtDxe_DEFINES=\
  $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=DriverEntry"\
    /D PlatformPciExpressBaseAddress=$(PCIEX_BASE_ADDRESS) \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_LIB__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_HOB_LIB__ \

TxtDxe_LIBS=\
    $(EFIGUIDLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EDKPROTOCOLLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseLibX64_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EdkIIGlueBasePciExpressLib_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueBaseTimerLibLocalApic_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(EdkIIGlueHiiLib_LIB)\
    $(EFIDRIVERLIB)\
    $(UEFIEFIIFRSUPPORTLIB)\
    $(EFISCRIPTLIB)\
    $(CpuProtocolLib_LIB)\
    $(CpuGuidLib_LIB)\
    $(SaPcieDxeLib_LIB)\
    $(CPUIA32LIB)

TxtDxeBin :  $(TxtDxe_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\TxtDxe.mak all\
    "MY_INCLUDES=$(TxtDxe_INCLUDES)"\
    "MY_DEFINES=$(TxtDxe_DEFINES)"\
    "GUID=FF917E22-A228-448d-BDAA-68EFCCDDA5D3"\
    "AFLAGS=$(AFLAGS) $(PROJECT_CPU_INCLUDES)"\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=BS_DRIVER \
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(TxtDxe_DIR)\TxtDxe.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1\
