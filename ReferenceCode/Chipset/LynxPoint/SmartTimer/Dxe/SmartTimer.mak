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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/SmartTimer/SmartTimer.mak 3     9/26/12 3:17a Victortu $
#
# $Revision: 3 $
#
# $Date: 9/26/12 3:17a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/SmartTimer/SmartTimer.mak $
# 
# 3     9/26/12 3:17a Victortu
# Lynx Point PCH Chipset Framework Reference Code Beta 0.7.0
# 
# 2     2/24/12 2:21a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:17a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create SmartTimer Driver
#---------------------------------------------------------------------------
EDK : SmartTimer
SmartTimer : $(BUILD_DIR)\SmartTimer.mak SmartTimerBin


$(BUILD_DIR)\SmartTimer.mak : $(SmartTimer_DIR)\$(@B).cif $(SmartTimer_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SmartTimer_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmartTimer_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

SmartTimer_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=TimerDriverInitialize"\
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__

SmartTimer_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(ArchProtocolLib)\
            $(EDKPROTOCOLLIB)


SmartTimerBin: $(SmartTimer_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\SmartTimer.mak all \
            "MY_INCLUDES=$(SmartTimer_INCLUDES)"\
            "MY_DEFINES=$(SmartTimer_DEFINES)"\
            GUID=90CB75DB-71FC-489d-AACF-943477EC7212\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(SmartTimer_DIR)\SmartTimer.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
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
