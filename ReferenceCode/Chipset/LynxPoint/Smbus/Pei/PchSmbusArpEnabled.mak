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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusArpEnabled/PchSmbusArpEnabled.mak 2     2/24/12 2:29a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:29a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmbusArpEnabled/PchSmbusArpEnabled.mak $
# 
# 2     2/24/12 2:29a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:28a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSmbusArpEnabled Driver
#---------------------------------------------------------------------------
EDK : PchSmbusArpEnabled
PchSmbusArpEnabled : $(BUILD_DIR)\PchSmbusArpEnabled.mak PchSmbusArpEnabledBin


$(BUILD_DIR)\PchSmbusArpEnabled.mak : $(PchSmbusArpEnabled_DIR)\$(@B).cif $(PchSmbusArpEnabled_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSmbusArpEnabled_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSmbusArpEnabled_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchSmbusArpEnabled_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchSmbusPeim"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_PEI_HOB_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchSmbusArpEnabled_LIB_LINKS =\
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
            $(EdkIIGluePeiHobLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

PchSmbusArpEnabledBin: $(PchSmbusArpEnabled_LIB_LINKS) 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSmbusArpEnabled.mak all\
            NAME=PchSmbusArpEnabled\
            MAKEFILE=$(BUILD_DIR)\PchSmbusArpEnabled.mak \
            GUID=22B194B4-CC0E-46c7-9FCE-DA10D6ED1731\
            "MY_INCLUDES=$(PchSmbusArpEnabled_INCLUDES)"\
            "MY_DEFINES=$(MY_DEFINES) $(PchSmbusArpEnabled_DEFINES)"\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchSmbusArpEnabled_DIR)\PchSmbus.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
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
