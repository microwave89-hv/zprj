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

#*************************************************************************
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiSmm/PchSpiSmm.mak 3     9/26/12 3:40a Victortu $
#
# $Revision: 3 $
#
# $Date: 9/26/12 3:40a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiSmm/PchSpiSmm.mak $
# 
# 3     9/26/12 3:40a Victortu
# Lynx Point PCH Chipset Framework Reference Code Beta 0.7.0
# 
# 2     2/24/12 2:26a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:24a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSpi SMM Driver
#---------------------------------------------------------------------------
EDK : PchSpiSmm
PchSpiSmm : $(BUILD_DIR)\PchSpiSmm.mak PchSpiSmmBin


$(BUILD_DIR)\PchSpiSmm.mak : $(PchSpiSmm_DIR)\$(@B).cif $(PchSpiSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSpiSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSpiSmm_INCLUDES=\
      $(INTEL_PCH_INCLUDES)\
      $(EdkIIGlueLib_INCLUDES)\
      $(PCH_SPI_INCLUDES)\
      $(PROJECT_CPU_INCLUDES)\

PchSpiSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchSpi"\
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

PchSpiSmm_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EDKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformSmmLib_LIB)\
            $(PchSpiCommonSmmLib_LIB)\
            $(EFISCRIPTLIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\

PchSpiSmmBin: $(PchSpiSmm_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSpiSmm.mak all \
            "MY_INCLUDES=$(PchSpiSmm_INCLUDES)"\
            "MY_DEFINES=$(PchSpiSmm_DEFINES)"\
            GUID=27F4917B-A707-4aad-9676-26DF168CBF0D\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(PchSpiSmm_DIR)\PchSpi.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
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
