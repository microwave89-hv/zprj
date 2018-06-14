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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/ActiveBios/ActiveBios.mak 2     2/24/12 2:09a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:09a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/ActiveBios/ActiveBios.mak $
# 
# 2     2/24/12 2:09a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:40a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#---------------------------------------------------------------------------
#   CreateActiveBios Driver
#---------------------------------------------------------------------------
EDK : ActiveBios
ActiveBios : $(BUILD_DIR)\ActiveBios.mak ActiveBiosBin


$(BUILD_DIR)\ActiveBios.mak : $(ActiveBios_DIR)\$(@B).cif $(ActiveBios_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(ActiveBios_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

ActiveBios_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\

ActiveBios_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallActiveBios"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
            /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

ActiveBios_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformDxeLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\

ActiveBiosBin: $(ActiveBios_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\ActiveBios.mak all \
            "MY_INCLUDES=$(ActiveBios_INCLUDES)" \
            "MY_DEFINES=$(ActiveBios_DEFINES)" \
            GUID=BFD59D42-FE0F-4251-B772-4B098A1AEC85\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER \
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(ActiveBios_DIR)\ActiveBiosDepex.dxs\
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
