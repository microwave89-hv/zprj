# MAK file for the ModulePart:BiosExtensionLoader

all : BiosExtensionLoader 

BiosExtensionLoader : $(BUILD_DIR)\BiosExtensionLoader.mak BiosExtensionLoaderBin

$(BUILD_DIR)\BiosExtensionLoader.mak : $(BiosExtensionLoader_DIR)\$(@B).cif $(BiosExtensionLoader_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(BiosExtensionLoader_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

BiosExtensionLoader_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  /I$(MeProtocolLib_DIR)\AmtPlatformPolicy\
  $(IndustryStandard_INCLUDES)\
  $(NB_INCLUDES) \
  $(INTEL_PCH_INCLUDES)\
  /I$(INTEL_COUGAR_POINT_DIR)\
  /I$(PROJECT_DIR)\Core\EM\Terminal

BiosExtensionLoader_DEFINES=$(MY_DEFINES)\
!IF "$(TCG_SUPPORT)"=="1"
  /D TCG_SUPPORT\
!ENDIF 
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=MebxDriverEntry"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__\
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
  /D __EDKII_GLUE_DXE_HOB_LIB__

BiosExtensionLoader_LIB_LINKS =\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(MeGuidLib_LIB)\
  $(EFIGUIDLIB)\
  $(EDKPROTOCOLLIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiDevicePathLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\
  $(AmtProtocolLib_LIB)\
  $(EFIDRIVERLIB)\
  $(INTEL_PCH_PROTOCOL_LIB)\
  $(PchPlatformDxeLib_LIB)

BiosExtensionLoaderBin : $(BiosExtensionLoader_LIB_LINKS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\BiosExtensionLoader.mak all\
		"MY_INCLUDES=$(BiosExtensionLoader_INCLUDES)"\
		"MY_DEFINES=$(BiosExtensionLoader_DEFINES)"\
		GUID=97cc7188-79c9-449f-b969-065b64bf9c69 \
		ENTRY_POINT=_ModuleEntryPoint \
        EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(BiosExtensionLoader_DIR)\BiosExtensionLoader.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\

