#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012 American Megatrends, Inc.             **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/SgTpv.mak 5     1/15/13 5:00a Joshchou $
#
# $Revision: 5 $
#
# $Date: 1/15/13 5:00a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/SgTpv.mak $
# 
# 5     1/15/13 5:00a Joshchou
# [TAG]  		EIP107237 
# [Category]  	New Feature
# [Description]  	Support SG function on ULT platform.
# 
# 4     12/18/12 6:20a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Update for SA RC 081
# 
# 3     9/24/12 8:27a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Update for Reference Code v0.70
# [Files]  		SgTpv.mak
# 
# 2     9/09/12 11:15p Joshchou
# [TAG]  		EIPNone
# [Category]  	New Feature
# [Description]  	Tpv module support for sharkbay.
# [Files]  		SgTpv.sdl
# SgTpv.mak
# SgTpvPei.c
# SgTpvPei.dxs
# SgTpvDxe.c
# SgTpvDxe.dxs
# SgTpv.cif
# 
# 1     6/27/11 5:25a Alanlin
# [TAG]  		EIP61848
# [Category]  	New Feature
# [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
# Reference code 0.6.0
# [Files]  		SgTpv.cif
# SgTpv.sdl
# SgTpv.mak
# SgTpvPei.c
# SgTpvPei.dxs
# SgTpvDxe.c
# SgTpvDxe.dxs
# 
# 
# 3     12/07/10 3:13p Alexp
# SgTpvPeiBin build rule: replace EDK_DEFAULTS with EDKIIGLUE_DEFAULTS
# macro.
# Fixes the build error if project includes Rules.mak without
# modifications file.
# 
# 2     11/12/10 1:57p Alexp
# 
# 1     9/17/10 1:12p Alexp
# [TAG]    	  EIP43103 
# [Category]  Function Request
# [Severity]	  Normal
# [Symptom]    Initial check-in of SgTPV module
# [RootCause] Request to implement SG reference code .
# [Solution]	Initial check-in. 
# [Files]	
#         SgTpv.cif;*.sdl;*.mak;
#         SgTpvPei.c;*.dxs;
#         SgTpvDxe.c;*.dxs  
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SgTpv.mak
#
# Description:
# Make file to build Switchable Graphics module for Third Party Gfx vendors
#
#<AMI_FHDR_END>
#*************************************************************************
SwitchableGraphics: SgTpv

SgTpv : $(BUILD_DIR)\SgTpv.mak SgTpvDxeBin SgTpvPeiBin

$(BUILD_DIR)\SgTpv.mak : $(SgTpv_DIR)\$(@B).cif $(SgTpv_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SgTpv_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

BUILD_SGTPV_DIR = $(BUILD_DIR)\$(SgTpv_DIR)

################################################################################
# PEI 
################################################################################
SgTpv_PEI_OBJECTS = \
$(BUILD_SGTPV_DIR)\SGTpvPei.obj

SgTpvPei_INCLUDES=\
    $(EDK_INCLUDES)\
    $(PROJECT_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\SaDataHob\
    $(INTEL_MCH_INCLUDES)\SaPlatformPolicy\
    $(EdkIIGlueLib_INCLUDES)\
    $(SwitchableGraphics_INCLUDES)\
    /I$(NB_BOARD_DIR)\
    /I$(SgTpv_DIR)

SgTpvPei_DEFINES=\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SgTpvPeiInit"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_PEI_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
    /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__

SgTpvPei_LIBS=\
            $(SaGuidLib_LIB)\
            $(INTEL_SA_PPI_LIB)\
            $(IntelPchPpiLib_LIB)\
            $(EDKFRAMEWORKPPILIB) \
            $(BUILD_DIR)\IA32\EdkIIGlueBaseLib.lib\
	    $(EdkIIGlueBaseLibIA32_LIB)\
            $(EdkIIGlueBaseIoLibIntrinsic_LIB) \
            $(BUILD_DIR)\IA32\EdkIIGluePeiDebugLibReportStatusCode.lib\
            $(BUILD_DIR)\IA32\EdkIIGluePeiReportStatusCodeLib.lib\
            $(BUILD_DIR)\IA32\EdkIIGluePeiServicesLib.lib\
            $(BUILD_DIR)\IA32\EdkIIGluePeiMemoryAllocationLib.lib\
            $(BUILD_DIR)\IA32\EdkIIGlueBasePciLibPciExpress.lib\

#            $(EdkIIGlueBasePciLibPciExpress_LIB) \
#            $(EdkIIGluePeiMemoryAllocationLib_LIB) \
#            $(EdkIIGluePeiServicesLib_LIB) \
#            $(EdkIIGluePeiReportStatusCodeLib_LIB) \
#            $(EdkIIGluePeiDxeDebugLibReportStatusCode_LIB) \

#  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\

#  $(EdkIIGlueBaseMemoryLib_LIB)\

#  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\

#    $(PEILIB)

#  $(SwitchableGraphicsPei_LIBS)

SgTpvPeiBin : $(SgTpvPei_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\SgTpv.mak all\
    "MY_INCLUDES=$(SgTpvPei_INCLUDES)"\
    "MY_DEFINES=$(SgTpvPei_DEFINES)"\
    OBJECTS="$(SgTpv_PEI_OBJECTS)" \
    NAME=SgTpvPei\
    MAKEFILE=$(BUILD_DIR)\SgTpv.mak\
    GUID=0E2DAF63-8A4F-4026-A899-DE2D7F46E5EC\
    ENTRY_POINT=_ModuleEntryPoint\
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(SgTpv_DIR)\SgTpvPei.dxs\
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
    COMPRESS=0

################################################################################
# DXE 
################################################################################
SgTpv_DXE_OBJECTS = \
$(BUILD_SGTPV_DIR)\SGTpvDxe.obj

SgTpvDxe_INCLUDES=\
    $(EDK_INCLUDES) \
    $(MISCFRAMEWORK_INCLUDES)\
    $(EDK_SOURCE_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\SaDataHob\
    $(INTEL_MCH_INCLUDES)\SaPlatformPolicy\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_MPG_INCLUDES)\
    $(IndustryStandard_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(ACPI_PLATFORM_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    /I$(SgTpv_DIR)\
    /I$(INTEL_SYSTEM_AGENT_DIR)\SaInit\
    /I$(EDK_SOURCE)\Foundation\Efi\Include\

#    $(SwitchableGraphics_INCLUDES)\



SgTpvDxe_LIBS=\
    $(EDKPROTOCOLLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EFISCRIPTLIB)\
    $(EFIDRIVERLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(BUILD_DIR)\IA32\EdkIIGlueBaseLib.lib\
    $(EdkIIGlueBaseMemoryLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(INTEL_SA_PROTOCOL_LIB)\
    $(SaGuidLib_LIB)\
    $(IntelMpgProtocolLib_LIB)\
    $(EdkIIGlueBasePciExpressLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(CpuPlatformLib_LIB)\
    $(PchPlatformSmmLib_LIB)\

    #$(EdkIIGlueBaseLib_LIB)\

 
SgTpvDxeBin : $(SgTpvDxe_LIBS)
  $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
    /f $(BUILD_DIR)\SgTpv.mak all\
    GUID=3FE57AC2-C675-46B1-8458-AC6206588424\
    NAME=SgTpvDxe\
    MAKEFILE=$(BUILD_DIR)\SgTpv.mak\
    "MY_INCLUDES = $(SgTpvDxe_INCLUDES)" \
    OBJECTS="$(SgTpv_DXE_OBJECTS)" \
    ENTRY_POINT=SgTpvDxeEntryPoint\
    TYPE=BS_DRIVER\
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(SgTpv_DIR)\SgTpvDxe.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012 American Megatrends, Inc.             **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
