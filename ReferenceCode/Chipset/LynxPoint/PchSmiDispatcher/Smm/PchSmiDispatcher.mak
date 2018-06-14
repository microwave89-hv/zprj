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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmiDispatcher/PchSmiDispatcher.mak 3     6/24/13 6:08a Scottyang $
#
# $Revision: 3 $
#
# $Date: 6/24/13 6:08a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSmiDispatcher/PchSmiDispatcher.mak $
# 
# 3     6/24/13 6:08a Scottyang
# [TAG]  		EIP127297
# [Category]  	Improvement
# [Description]  	Update PCH RC 1.6.0.
# [Files]  		SB.sd, SBDxe.c, ..\ReferenceCode\Chipset\LynxPoint\*.*
# 
# 2     2/24/12 2:14a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 8:54a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSmiDispatcher Driver
#---------------------------------------------------------------------------
EDK : PchSmiDispatcher
PchSmiDispatcher : $(BUILD_DIR)\PchSmiDispatcher.mak PchSmiDispatcherBin


$(BUILD_DIR)\PchSmiDispatcher.mak : $(PchSmiDispatcher_DIR)\$(@B).cif $(PchSmiDispatcher_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSmiDispatcher_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSmiDispatcher_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchSmiDispatcher_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializePchSmmDispatcher"\
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \

PchSmiDispatcher_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EDKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformSmmLib_LIB)\
            $(EdkIIGlueSmmFirmwarePerformanceLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\

PchSmiDispatcherBin: $(COMPILERSTUB) $(PchSmiDispatcher_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f  $(BUILD_DIR)\PchSmiDispatcher.mak all \
            "MY_INCLUDES=$(PchSmiDispatcher_INCLUDES)" \
            "MY_DEFINES=$(PchSmiDispatcher_DEFINES)" \
            GUID=B0D6ED53-B844-43f5-BD2F-61095264E77E\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(PchSmiDispatcher_DIR)\PchSmiDispatcher.dxs\
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
