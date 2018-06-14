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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLateInitSmm.mak 1     12/18/12 4:55a Scottyang $
#
# $Revision: 1 $
#
# $Date: 12/18/12 4:55a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLateInitSmm.mak $
# 
# 1     12/18/12 4:55a Scottyang
# [TAG] EIP109697
# [Category] Improvement
# [Description] Update PCH RC 0.8.1
# [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
#
#*************************************************************************
#---------------------------------------------------------------------------
#   Create PchLateInitSmm Driver
#---------------------------------------------------------------------------
EDK : PchLateInitSmm
PchLateInitSmm : $(BUILD_DIR)\PchLateInitSmm.mak PchLateInitSmmBin

$(BUILD_DIR)\PchLateInitSmm.mak : $(PchLateInitSmm_DIR)\$(@B).cif $(PchLateInitSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchLateInitSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchLateInitSmm_INCLUDES=\
        /I$(INTEL_PCH_DIR)\PchInit\Common\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\
        /I$(EDK_SOURCE)\Foundation\Efi\Include\

PchLateInitSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PchLateInitSmmEntryPoint"\
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \

PchLateInitSmm_LIB_LINKS =\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformDxeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EDKPROTOCOLLIB)\
            $(EFISCRIPTLIB)\
            $(PchUsbCommonDxeLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

PchLateInitSmmBin: $(PchLateInitSmm_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchLateInitSmm.mak all \
            "MY_INCLUDES=$(PchLateInitSmm_INCLUDES)" \
            "MY_DEFINES=$(PchLateInitSmm_DEFINES)" \
            GUID=D7B10D4E-67E6-4C74-83E9-F9AF0ACC33CC\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(PchLateInitSmm_DIR)\PchLateInitSmm.dxs\
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
