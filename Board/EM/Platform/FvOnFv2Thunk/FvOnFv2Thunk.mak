# /*++
# 
# --*/
all : FvOnFv2Thunk

FvOnFv2Thunk : $(BUILD_DIR)\FvOnFv2Thunk.mak FvOnFv2ThunkBin

$(BUILD_DIR)\FvOnFv2Thunk.mak : $(FvOnFv2Thunk_DIR)\FvOnFv2Thunk.cif $(FvOnFv2Thunk_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(FvOnFv2Thunk_DIR)\FvOnFv2Thunk.cif $(CIF2MAK_DEFAULTS)

FvOnFv2Thunk_INCLUDES = \
    $(EdkIIGlueLib_INCLUDES)

FvOnFv2Thunk_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeFirmwareVolume2"\
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
      /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__

FvOnFv2Thunk_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EDKPROTOCOLLIB)
                       
FvOnFv2ThunkBin : $(FvOnFv2Thunk_LIB_LINKS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        /f $(BUILD_DIR)\FvOnFv2Thunk.mak all\
        NAME=FvOnFv2Thunk\
        "MY_INCLUDES=$(FvOnFv2Thunk_INCLUDES)"\
        "MY_DEFINES=$(FvOnFv2Thunk_DEFINES)" \
        GUID=5007A40E-A5E0-44f7-86AE-662F9A91DA26\
        ENTRY_POINT=_ModuleEntryPoint\
        EDKIIModule=DXEDRIVER\
        DEPEX1=$(FvOnFv2Thunk_DIR)\FvOnFv2Thunk.dxs \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        TYPE=BS_DRIVER\
        COMPRESS=1\
