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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePeiPolicyInit/MePeiPolicyInit.mak 2     2/23/12 8:56a Klzhan $
#
# $Revision: 2 $
#
# $Date: 2/23/12 8:56a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePeiPolicyInit/MePeiPolicyInit.mak $
# 
# 2     2/23/12 8:56a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:05a Klzhan
# Initial Check in 
# 
# 1     3/29/11 4:53a Klzhan
# 
# 1     2/25/11 1:45a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:11a Klzhan
# Initial Check-in.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmtPlatformPolicy.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
All : MEPeiPolicyInit

MEPeiPolicyInit : $(BUILD_DIR)\MEPeiPolicyInit.mak MEPeiPolicyInitBin

$(BUILD_DIR)\MEPeiPolicyInit.mak : $(MEPeiPlatformPolicy_DIR)\$(@B).cif $(MEPeiPlatformPolicy_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MEPeiPlatformPolicy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MEPeiPlatformPolicy_INCLUDES=\
  $(EDK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(INTEL_PCH_INCLUDES)


MEPeiPlatformPolicy_DEFINES=$(MY_DEFINES)\
    /D "__EDKII_GLUE_MODULE_ENTRY_POINT__=MePeiPolicyInitEntryPoint" \
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
    /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \

MEPeiPlatformPolicy_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(MeLibPpi_LIB)\
  $(EdkIIGluePeiHobLib_LIB)\
  $(EdkIIGluePeiMemoryAllocationLib_LIB)\
  $(PEILIB)

MEPeiPolicyInitBin : $(MEPeiPlatformPolicy_LIBS) 
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\MEPeiPolicyInit.mak all\
    GUID=12C67BE1-AD2E-4f13-A95F-6EDC2C4392DE\
    "MY_INCLUDES = $(MEPeiPlatformPolicy_INCLUDES)" \
    "MY_DEFINES=$(MEPeiPlatformPolicy_DEFINES)"\
    ENTRY_POINT=MePeiPolicyInitEntryPoint\
    TYPE=PEIM\
    EDKIIModule=PEIM\
    DEPEX1=$(MEPeiPlatformPolicy_DIR)\MEPeiPolicyInit.dxs\
    DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
    COMPRESS=0

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
