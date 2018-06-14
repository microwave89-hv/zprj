#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctSmm/IsctSmm.mak 1     9/02/12 11:19p Bensonlai $
#
# $Revision: 1 $
#
# $Date: 9/02/12 11:19p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctSmm/IsctSmm.mak $
# 
# 1     9/02/12 11:19p Bensonlai
# Intel Smart Connect Technology initially releases.
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IsctSmm.mak
#
# Description: Make file to build IsctSmm components
#
#
#<AMI_FHDR_END>
#**********************************************************************

EDK : IsctSmm

IsctSmm : $(BUILD_DIR)\IsctSmm.mak IsctSmmBin

$(BUILD_DIR)\IsctSmm.mak : $(IsctSmm_DIR)\$(@B).cif $(IsctSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(IsctSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IsctSmm_INCLUDES=\
      $(INTEL_PCH_INCLUDES)\
      $(INTEL_MCH_INCLUDES)\
      $(EdkIIGlueLib_INCLUDES)\
      /I$(IntelPlatformProtocolLib_DIR)\
      /I$(ISCT_PLATFORM_DIR)\

IsctSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallIsctSmm"\
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

IsctSmm_LIB_LINKS =\
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
      $(PchPlatformSmmLib_LIB)\
      $(INTEL_PCH_PROTOCOL_LIB)\
      $(IsctGuidLib_LIB)\
      $(IsctProtocolLib_LIB)\

IsctSmmBin: $(IsctSmm_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\IsctSmm.mak all \
            "MY_INCLUDES=$(IsctSmm_INCLUDES)" \
            "MY_DEFINES=$(IsctSmm_DEFINES)" \
            GUID=DBD5B6BA-6734-4C5D-BF53-2C210D93A012\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(IsctSmm_DIR)\IsctSmm.dxs\
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
