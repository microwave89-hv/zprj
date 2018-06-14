#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/S3Support/Dxe/PchS3Support.mak 1     5/21/15 2:53a Dennisliu $
#
# $Revision: 1 $
#
# $Date: 5/21/15 2:53a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/S3Support/Dxe/PchS3Support.mak $
# 
# 1     5/21/15 2:53a Dennisliu
# [TAG]  		EIP217847 
# [Category]  	Improvement
# [Description]  	[PCH] Shark Bay-M/DT Reference Code Production Version
# 1.9.1
# [Files]  		PchS3Support.sdl
# PchS3Support.mak
# PchS3Support.c
# PchS3Support.h
# PchS3Support.dxs
# PchS3Support.inf
# 
#*************************************************************************

#---------------------------------------------------------------------------
#   Create PchS3Support Driver
#---------------------------------------------------------------------------
EDK : PchS3Support
PchS3Support : $(BUILD_DIR)\PchS3Support.mak PchS3SupportBin


$(BUILD_DIR)\PchS3Support.mak : $(PchS3Support_DIR)\$(@B).cif $(PchS3Support_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(PchS3Support_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PchS3Support_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\

PchS3Support_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PchS3SupportEntryPoint"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
            /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_DXE_HOB_LIB__ \

PchS3Support_LIB_LINKS =\
            $(EDKFRAMEWORKPROTOCOLLIB)\
            $(EDKPROTOCOLLIB)\
            $(PchPlatformDxeLib_LIB)\
            $(EFISCRIPTLIB) $(EFIPROTOCOLLIB)\
            $(INTEL_PCH_PROTOCOL_LIB)\
            $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
            $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
            $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
            $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
            $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
            $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(PchS3SupportCommonDxeLib_LIB)\
            $(EdkIIGlueBasePciLibPciExpress_LIB)\
            $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
            $(EFIDRIVERLIB)\
            $(EdkIIGlueUefiDevicePathLib_LIB)\
            $(EdkIIGlueUefiLib_LIB)\
            $(EdkIIGlueDxeHobLib_LIB)\


PchS3SupportBin: $(PchS3Support_LIB_LINKS)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\PchS3Support.mak all \
            "MY_INCLUDES=$(PchS3Support_INCLUDES)"\
            "MY_DEFINES=$(PchS3Support_DEFINES)"\
            GUID=08F2C63B-08DE-4ccd-8670-ACFE644A1C48\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=DXEDRIVER\
            DEPEX1=$(PchS3Support_DIR)\PchS3Support.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
            COMPRESS=1
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************