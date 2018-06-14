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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IoTrap/IoTrap.mak 4     12/18/12 5:19a Scottyang $
#
# $Revision: 4 $
#
# $Date: 12/18/12 5:19a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IoTrap/IoTrap.mak $
# 
# 4     12/18/12 5:19a Scottyang
# [TAG] EIP109697
# [Category] Improvement
# [Description] Update PCH RC 0.8.1
# [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 3     9/26/12 2:27a Victortu
# 
# 2     2/24/12 2:10a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:44a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#---------------------------------------------------------------------------
#   Create IoTrap Driver
#---------------------------------------------------------------------------
EDK : IoTrap
IoTrap : $(BUILD_DIR)\IoTrap.mak IoTrapBin

$(BUILD_DIR)\IoTrap.mak : $(IoTrap_DIR)\$(@B).cif $(IoTrap_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(IoTrap_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IoTrap_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\
        /I$(EDK_SOURCE)\Foundation\Efi\Include\

IoTrap_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallIoTrap"\
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \


IoTrap_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueBasePciExpressLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EDKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(EFISCRIPTLIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

IoTrapBin: $(IoTrap_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\IoTrap.mak all \
            "MY_INCLUDES=$(IoTrap_INCLUDES)" \
            "MY_DEFINES=$(IoTrap_DEFINES)" \
            GUID=2374EDDF-F203-4fc0-A20E-61BAD73089D6\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(IoTrap_DIR)\IoTrapDepex.dxs\
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
