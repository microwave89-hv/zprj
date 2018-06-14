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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/S3Support/Smm/S3SupportSmm.mak 1     5/21/15 3:01a Dennisliu $Revision:
#
# $Date: 5/21/15 3:01a $Log:
# 
#*************************************************************************

#---------------------------------------------------------------------------
#   Create S3SupportSmm Driver
#---------------------------------------------------------------------------
EDK : S3SupportSmm
S3SupportSmm : $(BUILD_DIR)\S3SupportSmm.mak S3SupportSmmBin


$(BUILD_DIR)\S3SupportSmm.mak : $(S3SupportSmm_DIR)\$(@B).cif $(S3SupportSmm_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(S3SupportSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

S3SupportSmm_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\

S3SupportSmm_DEFINES = $(MY_DEFINES)\
            /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=S3SupportSmmEntryPoint"\
            /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
            /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
            /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
            /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
            /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
            /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \

S3SupportSmm_LIB_LINKS =\
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

S3SupportSmmBin: $(S3SupportSmm_LIB_LINKS)  
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\S3SupportSmm.mak all \
            "MY_INCLUDES=$(S3SupportSmm_INCLUDES)"\
            "MY_DEFINES=$(S3SupportSmm_DEFINES)"\
            GUID=BFBEDBD4-1B7E-42f5-A528-4351E860F120\
            ENTRY_POINT=_ModuleEntryPoint \
            TYPE=BS_DRIVER\
            EDKIIModule=SMMDRIVER\
            DEPEX1=$(S3SupportSmm_DIR)\S3SupportSmm.dxs\
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