#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardDxe.mak 1     2/25/13 1:11a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 2/25/13 1:11a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Dxe/BootGuardDxe.mak $
# 
# 1     2/25/13 1:11a Bensonlai
# [TAG]  		EIP114386
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
# for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
# BIOS Writer's Guide - Rev 0.8.1
# [Files]  		BootGuardDxe.cif
# BootGuardDxe.c
# BootGuardDxe.h
# BootGuardDxe.sdl
# BootGuardDxe.dxs
# BootGuardDxe.mak
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: BootGuardDxe.mak
#
# Description: Make file for BootGuardDxe
#
#<AMI_FHDR_END>
#**********************************************************************

all : BootGuardDxe

BootGuardDxe : $(BUILD_DIR)\BootGuardDxe.mak BootGuardDxe_Bin

$(BUILD_DIR)\BootGuardDxe.mak : $(BOOT_GUARD_DXE_PATH)\$(@B).cif $(BOOT_GUARD_DXE_PATH)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(BOOT_GUARD_DXE_PATH)\$(@B).cif $(CIF2MAK_DEFAULTS)

BootGuardDxe_INCLUDES=\
    $(EdkIIGlueLib_INCLUDES)\
    $(EDK_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\

BootGuardDxe_LIBS=\
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
    $(PchPlatformDxeLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(BootGuardLib_LIB)\

BootGuardDxe_DEFINES=\
    $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=BootGuardDxeEntryPoint"\
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_DXE_HOB_LIB__ \

BootGuardDxe_Bin : $(BootGuardDxe_LIBS)
    $(MAKE) /$(MAKEFLAGS)  $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\BootGuardDxe.mak all\
    "MY_INCLUDES=$(BootGuardDxe_INCLUDES)"\
    "MY_DEFINES=$(BootGuardDxe_DEFINES)"\
    GUID=1DB43EC9-DF5F-4cf5-AAF0-0E85DB4E149A \
    ENTRY_POINT=_ModuleEntryPoint \
    EDKIIModule=DXEDRIVER\
    TYPE=BS_DRIVER \
    DEPEX1=$(BOOT_GUARD_DXE_PATH)\BootGuardDxe.dxs \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
    COMPRESS=1\

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
