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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusSmm/PchSmbusSmm.mak 2     2/24/12 2:28a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:28a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusSmm/PchSmbusSmm.mak $
# 
# 2     2/24/12 2:28a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:27a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSmbus SMM Driver
#---------------------------------------------------------------------------
EDK : PchSmbusSmm
PchSmbusSmm : $(BUILD_DIR)\PchSmbusSmm.mak PchSmbusSmmBin


$(BUILD_DIR)\PchSmbusSmm.mak : $(PchSmbusSmm_DIR)\$(@B).cif $(PchSmbusSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSmbusSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSmbusSmm_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchSmbusSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchSmbusSmm"\
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchSmbusSmm_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKPROTOCOLLIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformSmmLib_LIB) \
            $(PchSmbusCommonSmmLib_LIB)

PchSmbusSmmBin: $(PchSmbusSmm_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSmbusSmm.mak all \
            "MY_INCLUDES=$(PchSmbusSmm_INCLUDES)"\
            "MY_DEFINES=$(PchSmbusSmm_DEFINES)"\
            GUID=59287178-59B2-49ca-BC63-532B12EA2C53\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=RT_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(PchSmbusSmm_DIR)\PchSmbus.dxs\
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
