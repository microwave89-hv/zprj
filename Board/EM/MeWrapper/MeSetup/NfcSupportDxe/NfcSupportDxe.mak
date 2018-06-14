#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
#**********************************************************************
#
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportDxe.mak 1     11/02/14 9:43p Tristinchou $
#
# $Revision: 1 $
#
# $Date: 11/02/14 9:43p $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/NfcSupportDxe/NfcSupportDxe.mak $
# 
# 1     11/02/14 9:43p Tristinchou
# [TAG]  		EIP189985
# [Category]  	Improvement
# [Description]  	For ME 9.1.20.1035, add NFC related option in setup
# [Files]  		NfcSupportDxe.cif
# NfcSupportDxe.c
# NfcSupportDxe.h
# NfcSupportDxe.sdl
# NfcSupportDxe.dxs
# NfcSupportDxe.mak
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            NfcSupportDxe.mak
#
# Description:     Makfile for ME NFC Setup module.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : NfcSupportDxe

NfcSupportDxe : $(BUILD_DIR)\NfcSupportDxe.mak NfcSupportDxe_Bin

$(BUILD_DIR)\NfcSupportDxe.mak : $(NFC_SUPPORT_DXE_PATH)\$(@B).cif $(NFC_SUPPORT_DXE_PATH)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(NFC_SUPPORT_DXE_PATH)\$(@B).cif $(CIF2MAK_DEFAULTS)

NfcSupportDxe_INCLUDES=\
    $(EdkIIGlueLib_INCLUDES)\
    $(EDK_INCLUDES)\
    $(ME_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\

NfcSupportDxe_LIBS=\
    $(EDKPROTOCOLLIB)\
    $(EFIGUIDLIB)\
    $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EDKFRAMEWORKGUIDLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiDevicePathLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(MeLibDxe_LIB)\
    $(PchPlatformDxeLib_LIB)\

NfcSupportDxe_DEFINES=\
    $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=NfcSupportDxeEntryPoint"\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \

NfcSupportDxe_Bin : $(NfcSupportDxe_LIBS)
    $(MAKE) /$(MAKEFLAGS)  $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\NfcSupportDxe.mak all\
    "MY_INCLUDES=$(NfcSupportDxe_INCLUDES)"\
    "MY_DEFINES=$(NfcSupportDxe_DEFINES)"\
    GUID=1E5ACFFE-ED4C-4BC0-AE51-511EFDA0522E \
    ENTRY_POINT=_ModuleEntryPoint \
    EDKIIModule=DXEDRIVER\
    TYPE=BS_DRIVER \
    DEPEX1=$(NFC_SUPPORT_DXE_PATH)\NfcSupportDxe.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
    COMPRESS=1\

!IF DEFINED(NFC_SUPPORT_DXE_SUPPORT) && "$(NFC_SUPPORT_DXE_SUPPORT)" == "1"
SetupData : $(BUILD_DIR)\NfcSupportSetupHook.obj
!ENDIF

NfcSupportSetupHook_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)\
	-I $(NFC_SUPPORT_DXE_PATH)\
	-I $(PROJECT_DIR)\Include

$(BUILD_DIR)\NfcSupportSetupHook.obj : $(NFC_SUPPORT_DXE_PATH)\NfcSupportSetupHook.c
	$(CC) $(NfcSupportSetupHook_CFLAGS) /Fo$(BUILD_DIR)\ $(NFC_SUPPORT_DXE_PATH)\NfcSupportSetupHook.c 
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
