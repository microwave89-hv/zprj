#---------------------------------------------------------------------------
#		Create PCI Host Bridge DXE Component
#---------------------------------------------------------------------------
EDK : BdatAccessHandler

BdatAccessHandler : $(BUILD_DIR)\BdatAccessHandler.mak BdatAccessHandlerBin

$(BUILD_DIR)\BdatAccessHandler.mak : $(BdatAccessHandler_DIR)\BdatAccessHandler.cif $(BUILD_RULES)
	$(CIF2MAK) $(BdatAccessHandler_DIR)\BdatAccessHandler.cif $(CIF2MAK_DEFAULTS)

BdatAccessHandler_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(EDK_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  $(INTEL_PCH_INCLUDES)

BdatAccessHandler_DEFINES =$(MY_DEFINES)\
  /D "__EDKII_GLUE_MODULE_ENTRY_POINT__=BdatAccessHandler" \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \

BdatAccessHandler_LIB_LINKS =\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EDKPROTOCOLLIB)\
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
    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(INTEL_SA_PROTOCOL_LIB)\
    $(CpuPlatformLib_LIB)\

BdatAccessHandlerBin :  $(BdatAccessHandler_LIB_LINKS)
                        $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
                        /f $(BUILD_DIR)\BdatAccessHandler.mak all\
                        GUID=6DB9486F-6AF6-4090-984D-238482CE3EA4 \
                        ENTRY_POINT=_ModuleEntryPoint \
                        "MY_DEFINES=$(BdatAccessHandler_DEFINES)"\
                        "MY_INCLUDES=$(BdatAccessHandler_INCLUDES)"\
                        TYPE=BS_DRIVER \
                        EDKIIModule=DXEDRIVER\
                        DEPEX1=$(BdatAccessHandler_DIR)\BdatAccessHandler.dxs\
                        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
                        COMPRESS=1