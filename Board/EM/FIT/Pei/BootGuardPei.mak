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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardPei.mak 1     2/25/13 1:15a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 2/25/13 1:15a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Pei/BootGuardPei.mak $
# 
# 1     2/25/13 1:15a Bensonlai
# [TAG]  		EIP114386
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	[SBY] Ultrabook for Shark Bay Platform - : Boot Guard
# for 4th Gen Intel Core Processor based on Mobile U-Processor Line -
# BIOS Writer's Guide - Rev 0.8.1
# [Files]  		BootGuardPei.cif
# BootGuardPei.c
# BootGuardPei.h
# BootGuardPei.dxs
# BootGuardPei.sdl
# BootGuardPei.mak
# PeiCryptLib.lib
# OpensslLib.lib
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: BootGuardPei.mak
#
# Description: Make file for BootGuardPei
#
#<AMI_FHDR_END>
#**********************************************************************

all : BootGuardPei

BootGuardPei : $(BUILD_DIR)\BootGuardPei.mak BootGuardPeiBin

$(BUILD_DIR)\BootGuardPei.mak : $(BOOT_GUARD_PEI_PATH)\BootGuardPei.cif $(BOOT_GUARD_PEI_PATH)\BootGuardPei.mak $(BUILD_RULES)
    $(CIF2MAK) $(BOOT_GUARD_PEI_PATH)\BootGuardPei.cif $(CIF2MAK_DEFAULTS)

BOOT_GUARD_PEI_INCLUDES = \
    $(EdkIIGlueLib_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\

BOOT_GUARD_PEI_DEFINES=\
    $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=BootGuardPeiEntryPoint"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__\
    /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
    /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
    /D __EDKII_GLUE_PEI_HOB_LIB__ \

BOOT_GUARD_PEI_LIBS = \
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseLibIA32_LIB)\
    $(EdkIIGlueBasePrintLib_LIB)\
    $(EdkIIGluePeiMemoryAllocationLib_LIB)\
    $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
    $(EdkIIGluePeiReportStatusCodeLib_LIB)\
    $(EdkIIGluePeiServicesLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EdkIIGlueBasePostCodeLibPort80_LIB)\
    $(EDKFRAMEWORKPPILIB)\
    $(EdkIIGluePeiHobLib_LIB)\
    $(PchPlatformPeiLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(BootGuardLib_LIB)\

BootGuardPeiBin: $(BOOT_GUARD_PEI_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\BootGuardPei.mak all\
    NAME=BootGuardPei \
    MAKEFILE=$(BUILD_DIR)\BootGuardPei.mak \
    "MY_INCLUDES=$(BOOT_GUARD_PEI_INCLUDES)"\
    "MY_DEFINES=$(BOOT_GUARD_PEI_DEFINES)" \
    GUID=B41956E1-7CA2-42db-9562-168389F0F066 \
    ENTRY_POINT=_ModuleEntryPoint	"EXT_HEADERS=$(BUILD_DIR)\token.h"\
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(BOOT_GUARD_PEI_PATH)\BootGuardPei.dxs \
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX  \
    COMPRESS=0

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
