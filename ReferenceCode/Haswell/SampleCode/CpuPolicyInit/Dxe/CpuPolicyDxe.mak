# MAK file for the eModule:PowerManagement

EDK : CpuPolicyInitDxe

BUILD_CpuPolicyInitDxe_DIR = $(BUILD_DIR)\$(CpuPolicyInitDxe_DIR)

$(BUILD_DIR)\CpuPolicyDxe.mak : $(CpuPolicyInitDxe_DIR)\CpuPolicyDxe.cif $(BUILD_RULES)
    $(CIF2MAK) $(CpuPolicyInitDxe_DIR)\CpuPolicyDxe.cif $(CIF2MAK_DEFAULTS)

CpuPolicyInitDxe : $(BUILD_DIR)\CpuPolicyDxe.MAK CpuPolicyInitDxeBin 

CpuInitDxe_OBJECTS = \
    $(BUILD_CpuPolicyInitDxe_DIR)\CpuPolicyInitDxe.obj \

CpuInitDxe_MY_INCLUDES= \
    $(EDK_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    /I$(PROJECT_CPU_ROOT)\
    /I$(UefiEfiIfrSupportLib_DIR)\
    /I$(PROJECT_CPU_ROOT)\Include \

CpuInitDxe_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=CpuPolicyInitDxeEntryPoint"\
    /D TXT_SUPPORT_FLAG=1 \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
    /D FV_MICROCODE_BASE=$(FV_MICROCODE_BASE) \
    /D __EDKII_GLUE_HII_LIB__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
!ifdef PACK_MICROCODE
    /D PACK_MICROCODE=$(PACK_MICROCODE) \
!else
    /D PACK_MICROCODE=0 \
!endif
    /D SMM_FROM_SMBASE_DRIVER=$(SMM_FROM_SMBASE_DRIVER) \
    /D MICROCODE_BLOCK_SIZE=$(MICROCODE_BLOCK_SIZE) \

CpuInitDxe_LIBS =\
    $(PchPlatformLib)\
    $(EfiRuntimeLib_LIB)\
    $(INTEL_PCH_PROTOCOL_LIB)\
    $(EFIRUNTIMELIB)\
    $(CPUIA32LIB)\
    $(EFIPROTOCOLLIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(CpuGuidLib_LIB)\
!IF $(EFI_SPECIFICATION_VERSION) >= 0x0002000A
    $(UEFIEFIIFRSUPPORTLIB)\
!ELSE
    $(EFIIFRSUPPORTLIB) \
!ENDIF
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiDevicePathLib_LIB)\
    $(CpuProtocolLib_LIB)\
    $(EFIDRIVERLIB)\
    $(CpuPlatformLib_LIB)\
    $(PchPlatformDxeLib_LIB)\
    $(EFISCRIPTLIB)

CpuPolicyInitDxeBin : $(CpuInitDxe_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\CpuPolicyDxe.mak all\
    NAME=CpuPolicyDxe\
    MAKEFILE=$(BUILD_DIR)\CpuPolicyDxe.mak \
    "MY_INCLUDES=$(CpuInitDxe_MY_INCLUDES)" \
    "MY_DEFINES=$(CpuInitDxe_DEFINES)"\
    OBJECTS="$(CpuInitDxe_OBJECTS)" \
    GUID=15B9B6DA-00A9-4de7-B8E8-ED7AFB88F16E\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=BS_DRIVER \
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(CpuPolicyInitDxe_DIR)\CpuPolicyInitDxe.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1
#-----------------------------------------------------------------------
