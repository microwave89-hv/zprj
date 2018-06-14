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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PciHotPlug/PciHotPlug.mak 2     2/24/12 2:00a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:00a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/PchWrap/PciHotPlug/PciHotPlug.mak $
# 
# 2     2/24/12 2:00a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:37a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#---------------------------------------------------------------------------
#   Create PciHotPlug Driver
#---------------------------------------------------------------------------
EDK : PciHotPlug

PciHotPlug : $(BUILD_DIR)\PciHotPlug.mak PciHotPlugBin

$(BUILD_DIR)\PciHotPlug.mak : $(PciHotPlug_DIR)\$(@B).cif $(PciHotPlug_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PciHotPlug_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PciHotPlug_INCLUDES=\
      $(INTEL_PCH_INCLUDES)\
      $(EdkIIGlueLib_INCLUDES)\
      $(NB_INCLUDES)\
      $(SB_INCLUDES)\
      /I$(PROJECT_DIR)\
      /IInclude\

PciHotPlug_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PciHotPlug"\
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \

PciHotPlug_LIB_LINKS =\
            $(EDKPROTOCOLLIB) \
            $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)

PciHotPlugBin: $(PciHotPlug_LIB_LINKS)  
      $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
              /f $(BUILD_DIR)\PciHotPlug.mak all \
              "MY_INCLUDES=$(PciHotPlug_INCLUDES)"\
              "MY_DEFINES=$(PciHotPlug_DEFINES)"\
              GUID=3022E512-B94A-4f12-806D-7EF1177899D8\
              ENTRY_POINT=_ModuleEntryPoint \
              TYPE=BS_DRIVER\
              EDKIIModule=DXEDRIVER\
              DEPEX1=$(PciHotPlug_DIR)\PciHotPlug.dxs\
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
