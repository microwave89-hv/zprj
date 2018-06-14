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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctPeiWakeReason/IsctWakeReason.mak 5     7/16/14 12:22a Mirayang $
#
# $Revision: 5 $
#
# $Date: 7/16/14 12:22a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctPeiWakeReason/IsctWakeReason.mak $
# 
# 5     7/16/14 12:22a Mirayang
# Add complete function with iRST.
# 
# 4     7/11/14 10:29a Mirayang
# Fix iRST bulid error.
# 
# 3     7/08/14 5:08a Mirayang
# EIP142924 iSCT 5.0 for Shark Bay Platform
# 
# 2     9/26/12 2:08a Bensonlai
# [TAG]  		Nono
# [Category]  	Improvement
# [Description]  	Modified comment
# [Files]  		IsctWakeReason.dxs
# IsctWakeReason.sdl
# IsctWakeReason.mak
# 
# 1     9/02/12 11:18p Bensonlai
# Intel Smart Connect Technology initially releases.
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IsctWakeReason.mak
#
# Description: Make file to build IsctWakeReason components
#
#
#<AMI_FHDR_END>
#**********************************************************************

all : IsctWakeReason
IsctWakeReason : $(BUILD_DIR)\IsctWakeReason.mak IsctWakeReasonBin

$(BUILD_DIR)\IsctWakeReason.mak : $(IsctWakeReason_DIR)\$(@B).cif $(IsctWakeReason_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(IsctWakeReason_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IsctWakeReason_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  /I$(ISCT_PLATFORM_DIR)\
  /I$(IntelPlatformProtocolLib_DIR)\
!IFDEF RapidStart_SUPPORT
!IF "$(RapidStart_SUPPORT)" == "1"
  $(RAPIDSTART_INCLUDES)\
!ENDIF
!ENDIF

IsctWakeReason_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=IsctPeiEntryPoint"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__\
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_PEI_MEMORY_ALLOCATION_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_PEI_HOB_LIB__ \

IsctWakeReason_LIBS =\
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
  $(EdkIIGluePeiHobLib_LIB) \
  $(IsctGuidLib_LIB)\
!IFDEF RapidStart_SUPPORT
!IF "$(RapidStart_SUPPORT)" == "1"
  $(RapidStartPpiLib_LIB)\
!ENDIF
!ENDIF

IsctWakeReasonBin : $(IsctWakeReason_LIBS) $(PEILIB)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\IsctWakeReason.mak all \
		NAME=IsctWakeReason \
		MAKEFILE=$(BUILD_DIR)\IsctWakeReason.mak \
		GUID=0C3B7B59-28E5-4C99-85E5-D0116DBFAAF2 \
		ENTRY_POINT=_ModuleEntryPoint \
		"MY_INCLUDES = $(IsctWakeReason_INCLUDES)" \
		"MY_DEFINES = $(IsctWakeReason_DEFINES)" \
		TYPE=PEIM \
		EDKIIModule=PEIM \
		DEPEX1=$(IsctWakeReason_DIR)\IsctWakeReason.dxs \
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
