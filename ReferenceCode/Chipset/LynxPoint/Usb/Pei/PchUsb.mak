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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchUsb/PchUsb.mak 4     10/16/12 3:37a Scottyang $
#
# $Revision: 4 $
#
# $Date: 10/16/12 3:37a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchUsb/PchUsb.mak $
# 
# 4     10/16/12 3:37a Scottyang
# [TAG] EIP103924
# 
# [Category] Improvement
# 
# [Description] Update RC 0.7.1
# 
# [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 3     7/02/12 9:19a Victortu
# 
# 2     2/24/12 2:30a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:30a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchUsb Driver
#---------------------------------------------------------------------------
EDK : PchUsb
PchUsb : $(BUILD_DIR)\PchUsb.mak PchUsbBin


$(BUILD_DIR)\PchUsb.mak : $(PchUsb_DIR)\$(@B).cif $(PchUsb_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchUsb_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchUsb_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        /I$(INTEL_PCH_DIR)\Library\PchPlatformLib\
        $(EdkIIGlueLib_INCLUDES)\

PchUsb_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchUsb"\
            /D__EDKII_GLUE_BASE_MEMORY_LIB__ \
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D__EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D__EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
            /D__EDKII_GLUE_PEI_SERVICES_LIB__ \
            /D__EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__\
            /D __EDKII_GLUE_BASE_PCI_LIB_CF8__

PchUsb_LIB_LINKS =\
            $(EDKFRAMEWORKPPILIB)\
            $(EdkIIGlueBaseMemoryLib_LIB) \
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB) \
            $(EdkIIGluePeiDebugLibReportStatusCode_LIB) \
            $(EdkIIGluePeiReportStatusCodeLib_LIB) \
            $(EdkIIGluePeiServicesLib_LIB) \
            $(EdkIIGluePeiMemoryAllocationLib_LIB) \
            $(EdkIIGlueBasePciLibCf8_LIB) \
            $(IntelPchPpiLib_LIB) \
            $(PchPlatformPeiLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)

PchUsbBin: $(PchUsb_LIB_LINKS) 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchUsb.mak all\
            NAME=PchUsb\
            MAKEFILE=$(BUILD_DIR)\PchUsb.mak \
            GUID=6B4FDBD2-47E1-4a09-BA8E-8E041F208B95\
            "MY_INCLUDES=$(PchUsb_INCLUDES)"\
            "MY_DEFINES=$(PchUsb_DEFINES)"\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=PEIM \
            EDKIIModule=PEIM\
            DEPEX1=$(PchUsb_DIR)\PchUsb.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
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
