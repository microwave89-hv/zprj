# MAK file for the ModulePart:HeciSmm
all : HeciSmm 

HeciSmm : $(BUILD_DIR)\HeciSmm.mak HeciSmmBin

$(BUILD_DIR)\HeciSmm.mak : $(HeciSmm_DIR)\$(@B).cif $(HeciSmm_DIR)\$(@B).mak $(CP_BUILD_RULES)
	$(CIF2MAK) $(HeciSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

HeciSmm_INCLUDES= \
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  /I$(INTEL_COUGAR_POINT_INCLUDE_DIR)
  

HeciSmm_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(MeProtocolLib_LIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
  $(MeGuidLib_LIB)\
  $(EFISCRIPTLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIGUIDLIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueDxeServicesTableLib_LIB)\
  $(EFIDRIVERLIB)\
  $(RcFviDxeLib_LIB)\
  $(PchPlatformDxeLib_LIB)

HeciSmm_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeHECI"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  
HeciSmmBin : $(HeciSmm_LIBS) 
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\HeciSmm.mak all\
    MAKEFILE=$(BUILD_DIR)\HeciSmm.mak\
    "MY_INCLUDES=$(HeciSmm_INCLUDES)"\
    "MY_DEFINES=$(HeciSmm_DEFINES)"\
	GUID=921CD783-3E22-4579-A71F-00D74197FCC8\
    DEPEX1=$(HeciSmm_DIR)\HeciSmm.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER\
    EDKIIModule=SMMDRIVER\
    COMPRESS=1
