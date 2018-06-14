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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeLibrary/PTT/PTT Pei Library/PttHciDevicePeiLib.mak 1     12/18/12 5:48a Klzhan $
#
# $Revision: 1 $
#
# $Date: 12/18/12 5:48a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeLibrary/PTT/PTT Pei Library/PttHciDevicePeiLib.mak $
# 
# 1     12/18/12 5:48a Klzhan
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	AMI modify for TPM2.0
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:           
#
# Description:    
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : PttHciDevicePeiLib

PttHciDevicePeiLib : $(BUILD_DIR)\PttHciDevicePeiLib.mak PttHciDevicePeiLibBin

$(BUILD_DIR)\PttHciDevicePeiLib.mak : $(PttHciDevicePeiLib_DIR)\PttHciDevicePeiLib.cif $(PttHciDevicePeiLib_DIR)\PttHciDevicePeiLib.mak $(BUILD_RULES)
	$(CIF2MAK) $(PttHciDevicePeiLib_DIR)\PttHciDevicePeiLib.cif $(CIF2MAK_DEFAULTS)

PttHciDevicePeiLib_INCLUDES= \
  $(ME_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(EdkIIGlueInclude)\
  $(IndustryStandard_INCLUDES)\
  /IReferenceCode\ME\SampleCode\
  $(INTEL_PCH_INCLUDES)\
  
  
PttHciDevicePeiLib_DEFINES = $(MY_DEFINES)\
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
!IF "$(IntelPTT_SUPPORT)"=="1"
  /D PTT_FLAG
!ENDIF
  
  
PttHciDevicePeiLib_LIB_LINKS =\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueBaseTimerLibLocalApic_LIB)


PttHciDevicePeiLibBin: $(PttHciDevicePeiLib_LIB_LINKS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\PttHciDevicePeiLib.mak all\
	"MY_INCLUDES=$(PttHciDevicePeiLib_INCLUDES)"\
    "MY_DEFINES=$(PttHciDevicePeiLib_DEFINES)"\
	GUID=D58E4250-FDFF-4f6c-B972-9FCA453B3397\
	TYPE=PEI_LIBRARY    
