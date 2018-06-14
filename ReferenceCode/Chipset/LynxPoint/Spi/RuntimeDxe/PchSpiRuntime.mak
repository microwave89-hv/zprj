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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiRuntime/PchSpiRuntime.mak 2     2/24/12 2:27a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:27a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSpiRuntime/PchSpiRuntime.mak $
# 
# 2     2/24/12 2:27a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:26a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSpiRuntime Driver
#---------------------------------------------------------------------------
EDK : PchSpiRuntime
PchSpiRuntime : $(BUILD_DIR)\PchSpiRuntime.mak PchSpiRuntimeBin


$(BUILD_DIR)\PchSpiRuntime.mak : $(PchSpiRuntime_DIR)\$(@B).cif $(PchSpiRuntime_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSpiRuntime_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSpiRuntime_INCLUDES=\
      $(INTEL_PCH_INCLUDES)\
      $(EdkIIGlueLib_INCLUDES)\
      $(EDK_INCLUDES)\
      $(PCH_SPI_INCLUDES)\

PchSpiRuntime_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchSpi"\
      /D "__EDKII_GLUE_SET_VIRTUAL_ADDRESS_MAP_EVENT_HANDLER__=PchSpiVirtualAddressChangeEvent"\
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \


PchSpiRuntime_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(EDKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(DxeRuntimePciLibPciExpressLib_LIB)\
            $(PchPlatformDxeLib_LIB)\
            $(EFISCRIPTLIB)\
            $(PchSpiCommonDxeLib_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\

PchSpiRuntimeBin: $(PchSpiRuntime_LIB_LINKS)  
	    $(ECHO) DEPENDENCY_START > $(BUILD_DIR)\Fake.dxs
	    $(ECHO) FALSE >> $(BUILD_DIR)\Fake.dxs
	    $(ECHO) DEPENDENCY_END >> $(BUILD_DIR)\Fake.dxs
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSpiRuntime.mak all \
            "MY_INCLUDES=$(PchSpiRuntime_INCLUDES)"\
            "MY_DEFINES=$(PchSpiRuntime_DEFINES)"\
            GUID=C194C6EA-B68C-4981-B64B-9BD271474B20\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=RT_DRIVER\
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(BUILD_DIR)\Fake.dxs\
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
