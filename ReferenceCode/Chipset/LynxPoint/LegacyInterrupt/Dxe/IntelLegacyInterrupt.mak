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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IntelLegacyInterrupt/IntelLegacyInterrupt.mak 2     2/24/12 2:11a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:11a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/IntelLegacyInterrupt/IntelLegacyInterrupt.mak $
# 
# 2     2/24/12 2:11a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:45a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create IntelLegacyInterrupt Driver
#---------------------------------------------------------------------------
EDK : IntelLegacyInterrupt
IntelLegacyInterrupt : $(BUILD_DIR)\IntelLegacyInterrupt.mak IntelLegacyInterruptBin


$(BUILD_DIR)\IntelLegacyInterrupt.mak : $(IntelLegacyInterrupt_DIR)\$(@B).cif $(IntelLegacyInterrupt_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(IntelLegacyInterrupt_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelLegacyInterrupt_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\

IntelLegacyInterrupt_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=LegacyInterruptInstall"\
            /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

IntelLegacyInterrupt_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EDKPROTOCOLLIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\

IntelLegacyInterruptBin: $(IntelLegacyInterrupt_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\IntelLegacyInterrupt.mak all \
            "MY_INCLUDES=$(IntelLegacyInterrupt_INCLUDES)"\
            "MY_DEFINES=$(IntelLegacyInterrupt_DEFINES)"\
            GUID=C1C418F9-591D-461c-82A2-B9CD96DFEA86\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
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
