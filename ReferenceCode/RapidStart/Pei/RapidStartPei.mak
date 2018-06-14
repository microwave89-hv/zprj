#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartPei/RapidStartPei.mak 7     11/07/13 2:47a Joshchou $
#
# $Revision: 7 $
#
# $Date: 11/07/13 2:47a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartPei/RapidStartPei.mak $
# 
# 7     11/07/13 2:47a Joshchou
# [TAG]  		EIP142523
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update to RC 1.7.0
# 
# 6     1/13/13 7:38a Bensonlai
# [TAG]  		EIP112060
# [Category]  	Spec Update
# [Severity]  	Normal
# [Description]  	[SBY]Intel Rapid Start Technology Framework Reference
# Code Production Candidate 0.9.0
# [Files]  		RapidStartDxe.c, RapidStartConfig.h, RapidStartDxe.dsc,
# RapidStartPei.dsc, RapidStartPei.c, RapidStartPei.inf,
# RapidStartPei.mak, RapidStartInfo.h
# 
# 5     10/15/12 5:45a Bensonlai
# [Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# 
# 4     9/26/12 3:26a Yurenlai
# [TAG]           None
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Beta Version 0.7.0.
# [Description]   ReferenceCode\RapidStart\*.*, RapidStartPeiLib.h
# 
# 2     5/14/12 11:26p Yurenlai
# [TAG]           EIP90075
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Alpha 2 Version 0.5.6.
# [Description]   ReferenceCode\RapidStart\*.*,
# Board\EM\iFfsWrapper\Library\*.*
# 
# 1     4/19/12 7:50a Yurenlai
# Initial check in.
#
#*************************************************************************

all : RapidStartPei
RapidStartPei : $(BUILD_DIR)\RapidStartPei.mak RapidStartPeiBin

$(BUILD_DIR)\RapidStartPei.mak : $(RapidStartPei_DIR)\$(@B).cif $(RapidStartPei_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(RapidStartPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartPei_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  $(ME_INCLUDES)\
  /I$(GfxDisplayLibPei_DIR)\
  $(RAPIDSTART_INCLUDES)\
  /I$(IntelPlatformProtocolLib_DIR)\

RapidStartPei_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=RapidStartPeiEntryPoint"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__\
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_PEI_HOB_LIB__ \
!IF "$(iME_SUPPORT)"=="1"
  /D ME_SUPPORT_FLAG\
!ENDIF

RapidStartPei_LIBS =\
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
  $(PchPlatformPeiLib_LIB)\
  $(IntelPchPpiLib_LIB)\
  $(MeGuidLib_LIB)\
  $(MeLibPpi_LIB)\
  $(RapidStartPpiLib_LIB)\
  $(RapidStartPeiLib_LIB)\
  $(RapidStartCommonPeiLib_LIB)\
  $(RapidStartGuidLib_LIB)\
  $(EdkIIGluePeiHobLib_LIB)\
  $(GfxDisplayLibPei_LIB)\
  $(EdkIIGluePeiFirmwarePerformanceLib_LIB)\
  $(INTEL_SA_PPI_LIB)\

RapidStartPeiBin : $(RapidStartPei_LIBS) $(PEILIB)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\RapidStartPei.mak all \
		NAME=RapidStartPei \
		MAKEFILE=$(BUILD_DIR)\RapidStartPei.mak \
		GUID=53f019e9-bb0c-424b-870a-1faf10b1cb4c \
		ENTRY_POINT=_ModuleEntryPoint \
		"MY_INCLUDES = $(RapidStartPei_INCLUDES)" \
		"MY_DEFINES = $(RapidStartPei_DEFINES)" \
		TYPE=PEIM \
		EDKIIModule=PEIM \
		DEPEX1=$(RapidStartPei_DIR)\RapidStartPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
