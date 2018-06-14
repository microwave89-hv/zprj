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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchInitPeim/PchInitPeim.mak 4     12/18/12 4:53a Scottyang $
#
# $Revision: 4 $
#
# $Date: 12/18/12 4:53a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchInitPeim/PchInitPeim.mak $
# 
# 4     12/18/12 4:53a Scottyang
# [TAG] EIP109697
# [Category] Improvement
# [Description] Update PCH RC 0.8.1
# [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 3     11/20/12 8:36a Scottyang
# [TAG]  		EIP107014
# [Category]  	Improvement
# [Description]  	Update RC 0.8.0
# [Files]  		ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 2     2/24/12 2:13a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:53a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchInitPeim module
#---------------------------------------------------------------------------
EDK : PchInitPeim
PchInitPeim : $(BUILD_DIR)\PchInitPeim.mak PchInitPeimBin


$(BUILD_DIR)\PchInitPeim.mak : $(PchInitPeim_DIR)\$(@B).cif $(PchInitPeim_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchInitPeim_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchInitPeim_INCLUDES=\
            /I$(INTEL_PCH_DIR)\PchInit\Common\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            /I$(INTEL_PCH_DIR)\Guid\SurvivabilityHob\
            $(ME_INCLUDES)\

PchInitPeim_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchInitPpi"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchInitPeim_LIB_LINKS =\
            $(GuidLib_LIB) \
            $(PchPlatformPeiLib_LIB) \
            $(IntelPchPpiLib_LIB)\
            $(EDKFRAMEWORKPPILIB) \
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB) \
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB) \
            $(EdkIIGluePeiReportStatusCodeLib_LIB) \
            $(EdkIIGluePeiServicesLib_LIB) \
            $(EdkIIGluePeiMemoryAllocationLib_LIB) \
            $(EdkIIGlueBasePciLibCf8_LIB) \
            $(PchUsbCommonPeiLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(PEILIB)

PchInitPeimBin: $(PchInitPeim_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchInitPeim.mak all \
            "MY_INCLUDES=$(PchInitPeim_INCLUDES)"\
            "MY_DEFINES=$(PchInitPeim_DEFINES)"\
            NAME=PchInitPeim\
            MAKEFILE=$(BUILD_DIR)\PchInitPeim.mak \
            GUID=FD236AE7-0791-48c4-B29E-29BDEEE1A838\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchInitPeim_DIR)\PchInitPeim.dxs\
            DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
            COMPRESS=0
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
