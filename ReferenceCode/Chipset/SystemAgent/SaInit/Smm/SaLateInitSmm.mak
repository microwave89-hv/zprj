#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#---------------------------------------------------------------------------
#   Create SaLateInitSmm Driver
#---------------------------------------------------------------------------
EDK : SaLateInitSmm
SaLateInitSmm : $(BUILD_DIR)\SaLateInitSmm.mak SaLateInitSmmBin


$(BUILD_DIR)\SaLateInitSmm.mak : $(SaLateInitSmm_DIR)\$(@B).cif $(SaLateInitSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SaLateInitSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SaLateInitSmm_INCLUDES=\
        $(EdkIIGlueLib_INCLUDES)\
        $(INTEL_MCH_INCLUDES)\
        $(INTEL_PCH_INCLUDES)\
        /I$(INTEL_SYSTEM_AGENT_DIR)\Library\SaPcieLib\Common\

SaLateInitSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SaLateInitSmmEntryPoint"\
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_LIB__ \
      /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
      /D __EDKII_GLUE_DXE_HOB_LIB__ \

SaLateInitSmm_LIB_LINKS =\
            $(EDKPROTOCOLLIB)\
            $(ArchProtocolLib)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EdkIIGlueUefiLib_LIB)\
            $(EdkIIGlueSmmFirmwarePerformanceLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EFIPROTOCOLLIB)\
            $(INTEL_SA_PROTOCOL_LIB)\
            $(SaGuidLib_LIB)\
            $(EdkIIGlueDxeHobLib_LIB)\
            $(CpuPlatformLib_LIB)\
            $(PchPlatformDxeLib_LIB)\
            $(SaPcieSmmLib_LIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\

SaLateInitSmmBin: $(COMPILERSTUB) $(SaLateInitSmm_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f  $(BUILD_DIR)\SaLateInitSmm.mak all \
            "MY_INCLUDES=$(SaLateInitSmm_INCLUDES)" \
            "MY_DEFINES=$(SaLateInitSmm_DEFINES)" \
            GUID=2D1E361C-7B3F-4d15-8B1F-66E551FABDC7\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(SaLateInitSmm_DIR)\SaLateInitSmm.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
            COMPRESS=1
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
