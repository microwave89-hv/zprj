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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchResetPeim/PchResetPeim.mak 2     2/24/12 2:17a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:17a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchResetPeim/PchResetPeim.mak $
# 
# 2     2/24/12 2:17a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:05a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchResetPeim module
#---------------------------------------------------------------------------
EDK : PchResetPeim
PchResetPeim : $(BUILD_DIR)\PchResetPeim.mak PchResetPeimBin


$(BUILD_DIR)\PchResetPeim.mak : $(PchResetPeim_DIR)\$(@B).cif $(PchResetPeim_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchResetPeim_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchResetPeim_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\

PchResetPeim_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchReset"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchResetPeim_LIB_LINKS =\
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
            $(PchResetCommonPeiLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

PchResetPeimBin: $(PchResetPeim_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchResetPeim.mak all \
            "MY_INCLUDES=$(PchResetPeim_INCLUDES)"\
            "MY_DEFINES=$(PchResetPeim_DEFINES)"\
            NAME=PchResetPeim\
            MAKEFILE=$(BUILD_DIR)\PchResetPeim.mak \
            GUID=FF259F16-18D1-4298-8DD2-BD87FF2894A9\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchResetPeim_DIR)\PchReset.dxs\
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
