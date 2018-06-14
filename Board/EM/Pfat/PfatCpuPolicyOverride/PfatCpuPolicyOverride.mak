#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatCpuPolicyOverride/PfatCpuPolicyOverride.mak 4     10/29/12 4:10p Fredericko $
#
# $Revision: 4 $
#
# $Date: 10/29/12 4:10p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatCpuPolicyOverride/PfatCpuPolicyOverride.mak $
# 
# 4     10/29/12 4:10p Fredericko
# [TAG]  		EIP84115
# [Category]  	Improvement
# [Description]  	Implementing PFAT function for Shark Bay
# 
# 3     10/05/12 6:28p Fredericko
# Make Pfat build with Debug Mode Turned On. 
# 
# 2     9/25/12 6:16p Fredericko
# 
# 1     9/17/12 4:47p Fredericko
# Initial Check in for PfatCpuPolicyOverride
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PfatCpuPolicyOverride.mak
#
# Description: Make file for PfatCpuPolicyOverride
#
#
#<AMI_FHDR_END>
#**********************************************************************

all : PfatCpuPolicyOverride

PfatCpuPolicyOverride : $(BUILD_DIR)\PfatCpuPolicyOverride.mak PfatCpuPolicyOverrideBin

$(BUILD_DIR)\PfatCpuPolicyOverride.mak : $(PFAT_CPU_POLICY_OVERRIDE_PATH)\PfatCpuPolicyOverride.cif $(PFAT_CPU_POLICY_OVERRIDE_PATH)\PfatCpuPolicyOverride.mak $(BUILD_RULES)
   $(CIF2MAK) $(PFAT_CPU_POLICY_OVERRIDE_PATH)\PfatCpuPolicyOverride.cif $(CIF2MAK_DEFAULTS)

PFAT_CPU_POLICY_OVERRIDE_INCLUDES = \
   $(EdkIIGlueLib_INCLUDES)\
   /I$(INTEL_COUGAR_POINT_INCLUDE_DIR)\
   /I$(PROJECT_CPU_ROOT)\
   /I$(PROJECT_CPU_ROOT)\Include \

PFAT_CPU_POLICY_OVERRIDE_DEFINES=\
   $(MY_DEFINES)\
   /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=PfatCpuPolicyOverrideEntryPoint"\
   /D __EDKII_GLUE_BASE_LIB__ \
   /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
   /D __EDKII_GLUE_BASE_MEMORY_LIB__\
   /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
   /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
   /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

PFAT_CPU_POLICY_OVERRIDE_LIBS = \
     $(EDKFRAMEWORKGUIDLIB)\
     $(EDKPPILIB)\
     $(EdkIIGlueBaseLibIA32_LIB)\
     $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
     $(EdkIIGlueBaseMemoryLib_LIB)\
     $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
     $(EdkIIGluePeiReportStatusCodeLib_LIB)\
     $(EdkIIGluePeiServicesLib_LIB)\
     $(EdkIIGluePeiMemoryAllocationLib_LIB)\
     $(EdkIIGlueBasePciLibPciExpress_LIB)\
     $(EdkIIGlueBasePciExpressLib_LIB)\
     $(EdkIIGluePeiHobLib_LIB)\
     $(INTEL_SA_PPI_LIB)\
     $(CPU_PPI_LIB)\

PfatCpuPolicyOverrideBin : $(PFAT_CPU_POLICY_OVERRIDE_LIBS)
   $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
   /f $(BUILD_DIR)\PfatCpuPolicyOverride.mak all\
   NAME=PfatCpuPolicyOverride \
   MAKEFILE=$(BUILD_DIR)\PfatCpuPolicyOverride.mak \
   "MY_INCLUDES=$(PFAT_CPU_POLICY_OVERRIDE_INCLUDES)"\
   "MY_DEFINES = $(PFAT_CPU_POLICY_OVERRIDE_DEFINES)" \
   OBJECTS="$(BUILD_DIR)\$(PFAT_CPU_POLICY_OVERRIDE_PATH)\PfatCpuPolicyOverride.obj" \
   GUID=FAF79E9F-4D40-4F02-8AC9-4B5512708F7F \
   ENTRY_POINT=_ModuleEntryPoint	"EXT_HEADERS=$(BUILD_DIR)\token.h"\
   TYPE=PEIM \
   EDKIIModule=PEIM\
   DEPEX1=$(PFAT_CPU_POLICY_OVERRIDE_PATH)\PfatCpuPolicyOverride.dxs \
   DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX  \
   COMPRESS=0

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
