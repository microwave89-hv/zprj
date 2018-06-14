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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/Intel Haswell Cpu RC PKG/Cpu Policy PEI/CpuPolicyPei.mak 5     7/02/12 7:23a Davidhsieh $
#
# $Revision: 5 $
#
# $Date: 7/02/12 7:23a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/Intel Haswell Cpu RC PKG/Cpu Policy PEI/CpuPolicyPei.mak $
# 
# 5     7/02/12 7:23a Davidhsieh
# 
# 4     5/22/12 4:36a Davidhsieh
# Add TXT_SUPPORT_FLAG define
# 
# 3     5/14/12 2:20a Davidhsieh
# 
# 2     2/23/12 2:46a Davidhsieh
# 
# 1     2/07/12 3:56a Davidhsieh
# 
# 2     9/21/11 11:22p Davidhsieh
# 
# 1     5/06/11 6:06a Davidhsieh
# First release
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: 
#
# Description: 
#
#<AMI_FHDR_END>
#**********************************************************************
EDK : CpuPolicyPei

BUILD_CpuInitPei_DIR = $(BUILD_DIR)\$(CpuPolicyPei_DIR)

$(BUILD_DIR)\CpuPolicyPei.mak : $(CpuPolicyPei_DIR)\CpuPolicyPei.cif $(BUILD_RULES)
    $(CIF2MAK) $(CpuPolicyPei_DIR)\CpuPolicyPei.cif $(CIF2MAK_DEFAULTS)

CpuPolicyPei : $(BUILD_DIR)\CpuPolicyPei.mak CpuPolicyPeiBin

CpuPolicyPei_OBJECTS = \
    $(BUILD_CpuInitPei_DIR)\CpuPolicyInitPei.obj

CpuPolicyPei_MY_INCLUDES= \
    $(EDK_INCLUDES) \
    /I$(PROJECT_CPU_ROOT)\
    /I$(PROJECT_CPU_ROOT)\Include \
    /I$(PROJECT_CPU_ROOT)\Include\Library \
    /I$(PROJECT_CPU_ROOT)\\Library \
    /I$(CpuInitPei_DIR)

CpuPolicyPei_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=CpuPolicyInitPeiEntryPoint"\
    /D TXT_SUPPORT_FLAG=1 \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_TABLE_POINTER_LIB_MM7__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \


CpuPolicyPei_LIBS =\
    $(PchPlatformLib)\
    $(EfiRuntimeLib_LIB)\
    $(INTEL_PCH_PROTOCOL_LIB)\
    $(EFIRUNTIMELIB)\
    $(EDKFRAMEWORKPPILIB) \
    $(CPUIA32LIB)\
    $(EFIPROTOCOLLIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(IntelPchPpiLib_LIB)\
    $(EdkIIGlueBaseLibIA32_LIB)\
    $(EdkIIGluePeiHobLib_LIB) \
    $(CpuGuidLib_LIB) \
    $(EdkIIGluePeiServicesLib_LIB) \
    $(EdkIIGluePeiReportStatusCodeLib_LIB) \
    $(PEIHOBLIB) \
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiDevicePathLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB) \
    $(EdkIIGlueBasePciExpressLib_LIB)\
    $(CPU_PPI_LIB)\
    $(PchPlatformPeiLib_LIB)\
    $(CpuPlatformLib_LIB)\
    $(EFISCRIPTLIB)

CpuPolicyPeiBin : $(CpuPolicyPei_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\CpuPolicyPei.mak all\
    NAME=CpuPolicyPei\
    MAKEFILE=$(BUILD_DIR)\CpuPolicyPei.mak \
    "MY_INCLUDES=$(CpuPolicyPei_MY_INCLUDES)" \
    "MY_DEFINES=$(CpuPolicyPei_DEFINES)"\
    OBJECTS="$(CpuPolicyPei_OBJECTS)" \
    GUID=0ac2d35d-1c77-1033-a6f8-7ca55df7d0aa\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=PEIM \
    EDKIIModule=PEIM\
    DEPEX1=$(CpuPolicyPei_DIR)\CpuPolicyInitPei.dxs \
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX  \
    COMPRESS=0

#---------------------------------------------------------------------------
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
