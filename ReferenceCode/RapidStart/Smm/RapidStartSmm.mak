#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartSmm/RapidStartSmm.mak 3     10/15/12 5:38a Bensonlai $
#
# $Revision: 3 $
#
# $Date: 10/15/12 5:38a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartSmm/RapidStartSmm.mak $
# 
# 3     10/15/12 5:38a Bensonlai
# [Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# 
# 2     9/26/12 3:33a Yurenlai
# [TAG]           None
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Beta Version 0.7.0.
# [Description]   ReferenceCode\RapidStart\*.*, RapidStartPeiLib.h
# 
# 1     4/19/12 8:07a Yurenlai
# Initial check in.
#
#*************************************************************************

EDK : RapidStartSmm

RapidStartSmm : $(BUILD_DIR)\RapidStartSmm.mak RapidStartSmmBin

$(BUILD_DIR)\RapidStartSmm.mak : $(RapidStartSmm_DIR)\$(@B).cif $(RapidStartSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(RapidStartSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartSmm_INCLUDES=\
      $(RAPIDSTART_INCLUDES)\
      $(INTEL_PCH_INCLUDES)\
      $(INTEL_MCH_INCLUDES)\
      $(EdkIIGlueLib_INCLUDES)\
      /I$(IntelPlatformProtocolLib_DIR)\
!IF "$(ISCT_PLATFORM_SUPPORT)"=="1"
      /I$(ISCT_PLATFORM_DIR)\
!ENDIF

RapidStartSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=RapidStartSmmEntryPoint"\
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

RapidStartSmm_LIB_LINKS =\
      $(EFIPROTOCOLLIB)\
      $(EDKPROTOCOLLIB)\
      $(EDKFRAMEWORKPROTOCOLLIB)\
      $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
      $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
      $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
      $(ArchProtocolLib)\
      $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
      $(EdkIIGlueBaseMemoryLib_LIB)\
      $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
      $(EdkIIGlueDxeServicesTableLib_LIB)\
      $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
      $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
      $(EdkIIGlueBasePciLibPciExpress_LIB)\
      $(EdkIIGlueUefiLib_LIB)\
      $(EdkIIGlueUefiBootServicesTableLib_LIB)\
      $(EdkIIGlueUefiDevicePathLib_LIB)\
      $(RapidStartCommonSmmLib_LIB)\
      $(RapidStartProtocolLib_LIB)\
      $(PchPlatformSmmLib_LIB)\
      $(RapidStartGuidLib_LIB)\
      $(INTEL_PCH_PROTOCOL_LIB)\
!IF "$(ISCT_PLATFORM_SUPPORT)"=="1"
      $(IsctGuidLib_LIB)\
      $(IsctProtocolLib_LIB)\
!ENDIF

RapidStartSmmBin: $(RapidStartSmm_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\RapidStartSmm.mak all \
            "MY_INCLUDES=$(RapidStartSmm_INCLUDES)" \
            "MY_DEFINES=$(RapidStartSmm_DEFINES)" \
            GUID=43172851-cf7e-4345-9fe0-d7012bb17b88\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(RapidStartSmm_DIR)\RapidStartSmm.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
            COMPRESS=1
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
