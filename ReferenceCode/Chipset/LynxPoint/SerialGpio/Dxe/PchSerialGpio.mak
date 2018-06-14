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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSerialGpio/PchSerialGpio.mak 2     2/24/12 2:20a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:20a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchSerialGpio/PchSerialGpio.mak $
# 
# 2     2/24/12 2:20a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:15a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchSerialGpio Driver
#---------------------------------------------------------------------------
EDK : PchSerialGpio
PchSerialGpio : $(BUILD_DIR)\PchSerialGpio.mak PchSerialGpioBin

$(BUILD_DIR)\PchSerialGpio.mak : $(PchSerialGpio_DIR)\$(@B).cif $(PchSerialGpio_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchSerialGpio_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchSerialGpio_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchSerialGpio_DEFINES = $(MY_DEFINES)\
        /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchSerialGpio"\
        /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
        /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
        /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
        /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
        /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
        /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PchSerialGpio_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EDKPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(PchPlatformDxeLib_LIB)

PchSerialGpioBin: $(PchSerialGpio_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchSerialGpio.mak all \
            "MY_INCLUDES=$(PchSerialGpio_INCLUDES)"\
            "MY_DEFINES=$(PchSerialGpio_DEFINES)"\
            GUID=FC1B7640-3466-4c06-B1CC-1C935394B5C2\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(PchSerialGpio_DIR)\PchSerialGpio.dxs\
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
