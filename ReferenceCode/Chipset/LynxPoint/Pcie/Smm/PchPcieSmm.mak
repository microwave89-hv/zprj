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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchPcieSmm/PchPcieSmm.mak 2     2/24/12 2:14a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:14a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchPcieSmm/PchPcieSmm.mak $
# 
# 2     2/24/12 2:14a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:57a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchPcieSmm Driver
#---------------------------------------------------------------------------
EDK : PchPcieSmm
PchPcieSmm : $(BUILD_DIR)\PchPcieSmm.mak PchPcieSmmBin


$(BUILD_DIR)\PchPcieSmm.mak : $(PchPcieSmm_DIR)\$(@B).cif $(PchPcieSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchPcieSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchPcieSmm_INCLUDES=\
           $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(EDK_INCLUDES)

PchPcieSmm_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchPcieSmm"\
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
            /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

PchPcieSmm_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformSmmLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKPROTOCOLLIB)\
            $(PchPciExpressHelpersDxeLib_LIB)\
            $(EFISCRIPTLIB)\
            $(EFIPROTOCOLLIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\

PchPcieSmmBin: $(PchPcieSmm_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f  $(BUILD_DIR)\PchPcieSmm.mak all \
            "MY_INCLUDES=$(PchPcieSmm_INCLUDES)" \
            "MY_DEFINES=$(PchPcieSmm_DEFINES)" \
            GUID=ACAEAA7A-C039-4424-88DA-F42212EA0E55\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(PchPcieSmm_DIR)\PchPcieSmm.dxs\
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
