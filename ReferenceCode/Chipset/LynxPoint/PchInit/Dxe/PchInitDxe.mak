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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchInitDxe/PchInitDxe.mak 6     1/14/13 2:40a Scottyang $
#
# $Revision: 6 $
#
# $Date: 1/14/13 2:40a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchInitDxe/PchInitDxe.mak $
# 
# 6     1/14/13 2:40a Scottyang
# [TAG] EIP112059 
# 
# [Category] Improvement
# 
# [Description] Update PCH RC 0.9.0.
# [Files] ReferenceCode\Chipset\LynxPoint\*.*
# 
# 5     11/20/12 8:34a Scottyang
# [TAG]  		EIP107014
# [Category]  	Improvement
# [Description]  	Update RC 0.8.0
# [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 4     8/13/12 9:14a Victortu
# 
# 3     7/02/12 9:56a Victortu
# 
# 2     2/24/12 2:12a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:51a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchInitDxe Driver
#---------------------------------------------------------------------------
EDK : PchInitDxe
PchInitDxe : $(BUILD_DIR)\PchInitDxe.mak PchInitDxeBin


$(BUILD_DIR)\PchInitDxe.mak : $(PchInitDxe_DIR)\$(@B).cif $(PchInitDxe_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchInitDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MY_DEFINES=\
!IF "$(PCH_DEBUG_INFO)"=="1"
  /D"PCH_DEBUG_INFO=1"\
!ELSE
  /D"PCH_DEBUG_INFO=0"\
!ENDIF

PchInitDxe_INCLUDES=\
            /I$(PchUsbCommonLib_DIR)\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            /I$(INTEL_PCH_DIR)\Protocol\PchInfo\
            /I$(INTEL_PCH_DIR)\SampleCode\Include\
            /I$(INTEL_PCH_DIR)\SampleCode\Library\AslUpdate\Dxe\
            /I$(INTEL_PCH_DIR)\Guid\SurvivabilityHob\
            $(ME_INCLUDES)

PchInitDxe_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PchInitEntryPoint"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
            /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__\
            /D __EDKII_GLUE_DXE_HOB_LIB__

PchInitDxe_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EDKPROTOCOLLIB)\
            $(PchPciExpressHelpersDxeLib_LIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformDxeLib_LIB)\
            $(EFIGUIDLIB)\
            $(EFISCRIPTLIB)\
            $(PchUsbCommonDxeLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(RcFviDxeLib_LIB)\
            $(PchAslUpdateLib_LIB)\
            $(EdkIIGlueDxeHobLib_LIB)\
!IF "$(iME_SUPPORT)"=="1"
            $(PchGuidLib_LIB)\
            $(MeLibDxe_LIB)
!ENDIF

PchInitDxeBin: $(PchInitDxe_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchInitDxe.mak all \
            "MY_INCLUDES=$(PchInitDxe_INCLUDES)"\
            "MY_DEFINES=$(PchInitDxe_DEFINES)"\
            GUID=DE23ACEE-CF55-4fb6-AA77-984AB53DE823\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(PchInitDxe_DIR)\PchInit.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
!IF "$(SOFTSDV_PARTIAL_COMPRESS)"=="1"
            COMPRESS=0
!ELSE
            COMPRESS=1
!ENDIF
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
