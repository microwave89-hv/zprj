#---------------------------------------------------------------------------
#   Create AcpiFvi Driver
#---------------------------------------------------------------------------
EDK : AcpiFvi

AcpiFvi: $(BUILD_DIR)\AcpiFvi.mak AcpiFviBin

$(BUILD_DIR)\AcpiFvi.mak : $(AcpiFvi_DIR)\$(@B).cif $(AcpiFvi_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(AcpiFvi_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


AcpiFvi_DEFINES =$(MY_DEFINES)\
  /D "__EDKII_GLUE_MODULE_ENTRY_POINT__=AcpiFviEntryPoint" \
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \


AcpiFvi_LIB_LINKS =\
    $(EFIPROTOCOLLIB)\
	$(EDKFRAMEWORKPROTOCOLLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
  	$(EdkIIGlueBasePciExpressLib_LIB)\
    $(RcFviDxeLib_LIB)\
    $(EDKPROTOCOLLIB)\
    $(AcpiProtocolLib_LIB)\

AcpiFvi_INCLUDES=\
  /I ReferenceCode\AcpiTables\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

AcpiFviBin: $(AcpiFvi_LIB_LINKS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\AcpiFvi.mak all \
    "MY_INCLUDES=$(AcpiFvi_INCLUDES)"\
    "MY_DEFINES=$(AcpiFvi_DEFINES)"\
    GUID=D7E31ECB-0A17-4529-9B84-C529DE8E1C0E\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=BS_DRIVER\
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(AcpiFvi_DIR)\AcpiFvi.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1
