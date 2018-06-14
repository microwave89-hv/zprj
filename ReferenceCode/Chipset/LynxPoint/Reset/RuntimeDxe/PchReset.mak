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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchReset/PchReset.mak 3     6/24/13 6:21a Scottyang $
#
# $Revision: 3 $
#
# $Date: 6/24/13 6:21a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchReset/PchReset.mak $
# 
# 3     6/24/13 6:21a Scottyang
# [TAG]  		EIP127297
# [Category]  	Improvement
# [Description]  	Update PCH RC 1.6.0.
# [Files]  		SB.sd, SBDxe.c, ..\ReferenceCode\Chipset\LynxPoint\*.*
# 
# 2     2/24/12 2:16a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:04a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchReset Driver
#---------------------------------------------------------------------------
EDK : PchReset
PchReset : $(BUILD_DIR)\PchReset.mak PchResetBin


PchReset_OBJECTS = \
$(BUILD_DIR)\$(PchReset_DIR)\PchReset.obj

$(BUILD_DIR)\PchReset.mak : $(PchReset_DIR)\$(@B).cif $(PchReset_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchReset_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchReset_INCLUDES=\
        $(INTEL_PCH_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\

PchReset_DEFINES = $(MY_DEFINES)\
        /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPchReset"\
        /D"__EDKII_GLUE_SET_VIRTUAL_ADDRESS_MAP_EVENT_HANDLER__=PchResetVirtualAddressChangeEvent"\
        /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
        /D __EDKII_GLUE_BASE_LIB__ \
        /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
        /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
        /D __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__ \
        /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
        /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
        /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \

PchReset_LIB_LINKS =\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueBaseLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(ArchProtocolLib)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(EDKPROTOCOLLIB)\
            $(PchPlatformDxeLib_LIB)\
            $(DxeRuntimePciLibPciExpressLib_LIB)\
            $(PchResetCommonDxeLib_LIB)\
            $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\

PchResetBin: $(PchReset_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchReset.mak all \
            "MY_INCLUDES=$(PchReset_INCLUDES)"\
            "MY_DEFINES=$(PchReset_DEFINES)"\
            GUID=BB1FBD4F-2E30-4793-9BED-74F672BC8FFE\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=RT_DRIVER\
            EDKIIModule=DXEDRIVER\
            "OBJECTS=$(PchReset_OBJECTS)" \
            DEPEX1=$(PchReset_DIR)\PchReset.dxs\
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
