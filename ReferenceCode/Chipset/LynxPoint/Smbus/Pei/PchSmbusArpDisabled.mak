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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusArpDisabled/PchSmbusArpDisabled.mak 2     2/24/12 2:23a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:23a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusArpDisabled/PchSmbusArpDisabled.mak $
# 
# 2     2/24/12 2:23a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:20a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSmbusArpDisabled Driver
#---------------------------------------------------------------------------
EDK : PchSmbusArpDisabled
PchSmbusArpDisabled : $(BUILD_DIR)\PchSmbusArpDisabled.mak PchSmbusArpDisabledBin


$(BUILD_DIR)\PchSmbusArpDisabled.mak : $(PchSmbusArpDisabled_DIR)\$(@B).cif $(PchSmbusArpDisabled_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSmbusArpDisabled_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSmbusArpDisabled_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchSmbusArpDisabled_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchSmbusPeim"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_CF8_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchSmbusArpDisabled_LIB_LINKS =\
            $(EDKFRAMEWORKPPILIB)\
            $(PchPlatformPeiLib_LIB)\
            $(PchSmbusCommonPeiLib_LIB)\
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
            $(EdkIIGluePeiReportStatusCodeLib_LIB)\
            $(EdkIIGluePeiServicesLib_LIB)\
            $(EdkIIGluePeiMemoryAllocationLib_LIB)\
            $(EdkIIGlueBasePciLibCf8_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

PchSmbusArpDisabledBin: $(PchSmbusArpDisabled_LIB_LINKS) 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSmbusArpDisabled.mak all\
            NAME=PchSmbusArpDisabled\
            MAKEFILE=$(BUILD_DIR)\PchSmbusArpDisabled.mak \
            GUID=643DF777-F312-42ed-81CC-1B1F57E18AD6\
            "MY_INCLUDES=$(PchSmbusArpDisabled_INCLUDES)"\
            "MY_DEFINES=$(MY_DEFINES) $(PchSmbusArpDisabled_DEFINES)"\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchSmbusArpDisabled_DIR)\PchSmbus.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
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
