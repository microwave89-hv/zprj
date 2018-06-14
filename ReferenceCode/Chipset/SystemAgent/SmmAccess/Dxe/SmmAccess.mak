#---------------------------------------------------------------------------
#    Create SmmAccess Driver
#---------------------------------------------------------------------------
EDK : SmmAccess

SmmAccess : $(BUILD_DIR)\SmmAccess.mak SmmAccessBin

$(BUILD_DIR)\SmmAccess.mak : $(SmmAccess_DIR)\$(@B).cif $(SmmAccess_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SmmAccess_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmAccess_INCLUDES = \
    $(EdkIIGlueLib_INCLUDES)\
    $(EDK_INCLUDES)\
    $(INTEL_MCH_INCLUDES)

SmmAccess_DEFINES = $(MY_DEFINES)\
  /D "__EDKII_GLUE_MODULE_ENTRY_POINT__=SmmAccessDriverEntryPoint" \
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_DXE_HOB_LIB__\
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \

SmmAccess_LIB_LINKS =\
  $(EDKFRAMEWORKGUIDLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIPROTOCOLLIB)\
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
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
  $(EdkIIGlueDxeServicesTableLib_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EDKPROTOCOLLIB)\

SmmAccessBin: $(SmmAccess_LIB_LINKS)
  $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\SmmAccess.mak all \
    "MY_INCLUDES=$(SmmAccess_INCLUDES)" \
    "MY_DEFINES=$(SmmAccess_DEFINES)"\
    GUID=1323C7F8-DAD5-4126-A54B-7A05FBF41515\
    ENTRY_POINT=_ModuleEntryPoint\
    TYPE=BS_DRIVER \
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(SmmAccess_DIR)\SmmAccess.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1
