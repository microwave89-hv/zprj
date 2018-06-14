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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPeiPolicyInit/AmtPeiPolicyInit.mak 2     2/23/12 8:59a Klzhan $
#
# $Revision: 2 $
#
# $Date: 2/23/12 8:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPeiPolicyInit/AmtPeiPolicyInit.mak $
# 
# 2     2/23/12 8:59a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:09a Klzhan
# 
# 1     3/29/11 5:03a Klzhan
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
All : AmtPeiPolicyInit

AmtPeiPolicyInit : $(BUILD_DIR)\AmtPeiPolicyInit.mak AmtPeiPolicyInitBin

$(BUILD_DIR)\AmtPeiPolicyInit.mak : $(AmtPeiPlatformPolicy_DIR)\$(@B).cif $(AmtPeiPlatformPolicy_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmtPeiPlatformPolicy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtPeiPlatformPolicy_INCLUDES=\
  $(EDK_INCLUDES) \
  $(ME_INCLUDES) \
  $(MISCFRAMEWORK_INCLUDES) \
  $(NB_INCLUDES)\
  $(SB_INCLUDES)\
  /I$(PROJECT_DIR)\
  /IInclude\


AmtPeiPlatformPolicy_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=AmtPeiPolicyInitEntryPoint"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__\
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

AmtPeiPlatformPolicy_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(MeLibPpi_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGluePeiServicesLib_LIB)\
  $(EdkIIGluePeiHobLib_LIB)\
  $(EdkIIGluePeiMemoryAllocationLib_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(PEILIB)


AmtPeiPolicyInitBin : $(AmtPeiPlatformPolicy_LIBS) 
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\AmtPeiPolicyInit.mak all\
		GUID=A05ECE52-15A8-424e-BFD3-FCF3D566A09C\
		"MY_INCLUDES = $(AmtPeiPlatformPolicy_INCLUDES)" \
                "MY_DEFINES=$(AmtPeiPlatformPolicy_DEFINES)"\
		ENTRY_POINT=AmtPeiPolicyInitEntryPoint\
		TYPE=PEIM\
                EDKIIModule=PEIM\
		DEPEX1=$(AmtPeiPlatformPolicy_DIR)\AmtPeiPolicyInit.dxs\
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
