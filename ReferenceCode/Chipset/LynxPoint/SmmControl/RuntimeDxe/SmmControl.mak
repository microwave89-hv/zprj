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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/SmmControl/SmmControl.mak 2     2/24/12 2:24a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:24a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/SmmControl/SmmControl.mak $
# 
# 2     2/24/12 2:24a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:21a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#---------------------------------------------------------------------------
#   Create SmmControl Driver
#---------------------------------------------------------------------------
EDK : SmmControl
SmmControl : $(BUILD_DIR)\SmmControl.mak SmmControlBin


$(BUILD_DIR)\SmmControl.mak : $(SmmControl_DIR)\$(@B).cif $(SmmControl_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(SmmControl_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmControl_INCLUDES=\
          $(INTEL_PCH_INCLUDES)\
          $(EdkIIGlueLib_INCLUDES)\

SmmControl_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SmmControlDriverEntryInit"\
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

SmmControl_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseMemoryLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EDKPROTOCOLLIB)\
            $(PchPlatformDxeLib_LIB)\
            $(SmmControlLib_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\

SmmControlBin: $(SmmControl_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\SmmControl.mak all \
            "MY_INCLUDES=$(SmmControl_INCLUDES)" \
            "MY_DEFINES=$(SmmControl_DEFINES)" \
            GUID=A0BAD9F7-AB78-491b-B583-C52B7F84B9E0\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=RT_DRIVER\
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(SmmControl_DIR)\SmmControl.dxs\
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
