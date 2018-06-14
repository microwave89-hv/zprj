#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/Dxe/MeSetupDxe.mak 2     3/01/13 3:13a Klzhan $
#
# $Revision: 2 $
#
# $Date: 3/01/13 3:13a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/Dxe/MeSetupDxe.mak $
# 
# 2     3/01/13 3:13a Klzhan
# 
# 1     2/07/13 2:04a Klzhan
# [TAG]  		EIP114344
# [Category]  	Improvement
# [Description]  	Create a setup item for TPM Device Selection
# [Files]  		MeSetupDxe.cif
# MeSetupDxe.c
# MeSetupDxe.h
# MeSetupDxe.sdl
# MeSetupDxe.dxs
# MeSetupDxe.mak
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            MeSetupDxe.mak
#
# Description:     Makfile for ME Setup Dxe module.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : MeSetupDxe

MeSetupDxe : $(BUILD_DIR)\MeSetupDxe.mak MeSetupDxe_Bin

$(BUILD_DIR)\MeSetupDxe.mak : $(ME_SETUP_DXE_PATH)\$(@B).cif $(ME_SETUP_DXE_PATH)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(ME_SETUP_DXE_PATH)\$(@B).cif $(CIF2MAK_DEFAULTS)

MeSetupDxe_INCLUDES=\
    $(EdkIIGlueLib_INCLUDES)\
    $(EDK_INCLUDES)\
    $(ME_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\

MeSetupDxe_LIBS=\
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
    $(PttDxe_LIB)\
    $(PttHeciDxeLib_LIB)\
    $(MeLibDxe_LIB)\
    $(PchPlatformDxeLib_LIB)\

MeSetupDxe_DEFINES=\
    $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=MeSetupDxeEntryPoint"\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_DXE_HOB_LIB__ \

MeSetupDxe_Bin : $(MeSetupDxe_LIBS)
    $(MAKE) /$(MAKEFLAGS)  $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\MeSetupDxe.mak all\
    "MY_INCLUDES=$(MeSetupDxe_INCLUDES)"\
    "MY_DEFINES=$(MeSetupDxe_DEFINES)"\
    GUID=D27AC0E1-D553-4c59-BCFE-89E5FFE9BEA6 \
    ENTRY_POINT=_ModuleEntryPoint \
    EDKIIModule=DXEDRIVER\
    TYPE=BS_DRIVER \
    DEPEX1=$(ME_SETUP_DXE_PATH)\MeSetupDxe.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
    COMPRESS=1\
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
