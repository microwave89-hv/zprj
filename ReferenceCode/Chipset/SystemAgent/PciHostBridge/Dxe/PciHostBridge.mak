#---------------------------------------------------------------------------
#		Create PCI Host Bridge DXE Component
#---------------------------------------------------------------------------
EDK : PciHostBridge

PciHostBridge : $(BUILD_DIR)\PciHostBridge.mak PciHostBridgeBin

$(BUILD_DIR)\PciHostBridge.mak : $(PciHostBridge_DIR)\PciHostBridge.cif $(BUILD_RULES)
	$(CIF2MAK) $(PciHostBridge_DIR)\PciHostBridge.cif $(CIF2MAK_DEFAULTS)

PciHostBridge_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(EDK_INCLUDES)\
  $(PROJECT_CPU_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  /IInclude

PciHostBridge_DEFINES =$(MY_DEFINES)\
  /D "__EDKII_GLUE_MODULE_ENTRY_POINT__=PciHostBridgeEntryPoint" \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

PciHostBridge_LIB_LINKS =\
    $(ArchProtocolLib)\
    $(EFISCRIPTLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EDKPROTOCOLLIB)\
    $(EFIDRIVERLIB)\
    $(CpuPlatformLib_LIB)\
    $(PchPlatformDxeLib_LIB)

PciHostBridgeBin :  $(PciHostBridge_LIB_LINKS)
                        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
                        /f $(BUILD_DIR)\PciHostBridge.mak all\
                        GUID=8D6756B9-E55E-4d6a-A3A5-5E4D72DDF772 \
                        ENTRY_POINT=_ModuleEntryPoint \
                        "MY_DEFINES=$(PciHostBridge_DEFINES)"\
                        "MY_INCLUDES=$(PciHostBridge_INCLUDES)"\
                        TYPE=BS_DRIVER \
                        EDKIIModule=DXEDRIVER\
                        DEPEX1=$(PciHostBridge_DIR)\PciHostBridge.dxs\
                        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
                        COMPRESS=1
