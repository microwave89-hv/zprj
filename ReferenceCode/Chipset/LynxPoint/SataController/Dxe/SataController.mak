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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/SataController/SataController.mak 3     10/16/12 3:33a Scottyang $
#
# $Revision: 3 $
#
# $Date: 10/16/12 3:33a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/SataController/SataController.mak $
# 
# 3     10/16/12 3:33a Scottyang
# [TAG] EIP103924
# 
# [Category] Improvement
# 
# [Description] Update RC 0.7.1
# 
# [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 2     2/24/12 2:20a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:15a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create SataController Driver
#---------------------------------------------------------------------------
EDK : SataController
SataController : $(BUILD_DIR)\SataController.mak SataControllerBin


$(BUILD_DIR)\SataController.mak : $(SataController_DIR)\$(@B).cif $(SataController_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SataController_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SataController_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

SataController_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeSataControllerDriver"\
            /D"__EDKII_GLUE_DRIVER_BINDING_PROTOCOL_INSTANCE__=mSataControllerDriverBinding"\
            /D"__EDKII_GLUE_COMPONENT_NAME_PROTOCOL_INSTANCE__=mSataControllerName"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
            /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_LIB__ \
            /D __EDKII_GLUE_UEFI_DRIVER_MODEL_LIB__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_CF8__ \
            /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__

SataController_LIB_LINKS =\
            $(EFISCRIPTLIB) $(INTEL_PCH_PROTOCOL_LIB)\
            $(EDKPROTOCOLLIB)\
            $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiLib_LIB)\
            $(EdkIIGlueUefiDriverModelLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueBasePciLibCf8_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(PchPlatformDxeLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)

SataControllerBin: $(SataController_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\SataController.mak all \
            "MY_INCLUDES=$(SataController_INCLUDES)" \
            "MY_DEFINES=$(SataController_DEFINES)" \
            GUID=BB65942B-521F-4ec3-BAF9-A92540CF60D2\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER \
            EDKIIModule=DXEDRIVER\
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
