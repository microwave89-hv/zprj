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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiPeim/PchSpiPeim.mak 2     2/24/12 2:24a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:24a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiPeim/PchSpiPeim.mak $
# 
# 2     2/24/12 2:24a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:23a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSpiPeim Driver
#---------------------------------------------------------------------------
EDK : PchSpiPeim
PchSpiPeim : $(BUILD_DIR)\PchSpiPeim.mak PchSpiPeimBin


$(BUILD_DIR)\PchSpiPeim.mak : $(PchSpiPeim_DIR)\$(@B).cif $(PchSpiPeim_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSpiPeim_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSpiPeim_INCLUDES=\
	$(PCH_SPI_INCLUDES)\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchSpiPeim_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchSpi"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
            /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchSpiPeim_LIB_LINKS =\
            $(PchPlatformPeiLib_LIB)\
            $(PchSpiCommonPeiLib_LIB)\
            $(IntelPchPpiLib_LIB)\
            $(IntelPchPpiLib_BIN)\
            $(EDKFRAMEWORKGUIDLIB)\
            $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
            $(EdkIIGluePeiReportStatusCodeLib_LIB)\
            $(EdkIIGluePeiServicesLib_LIB)\
            $(EdkIIGluePeiMemoryAllocationLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

PchSpiPeimBin: $(PchSpiPeim_LIB_LINKS) 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSpiPeim.mak all\
            NAME=PchSpiPeim\
            MAKEFILE=$(BUILD_DIR)\PchSpiPeim.mak \
            GUID=AA652CB9-2D52-4624-9FAE-D4E58B67CA46\
            "MY_INCLUDES=$(PchSpiPeim_INCLUDES)"\
            "MY_DEFINES=$(MY_DEFINES) $(PchSpiPeim_DEFINES)"\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchSpiPeim_DIR)\PchSpi.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
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
