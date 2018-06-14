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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPlatformPolicy.mak 3     4/24/12 12:41a Klzhan $
#
# $Revision: 3 $
#
# $Date: 4/24/12 12:41a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtPlatformPolicy/AmtPlatformPolicy.mak $
# 
# 3     4/24/12 12:41a Klzhan
# 
# 2     2/23/12 8:59a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:08a Klzhan
# Initial Check in 
# 
# 2     9/26/11 6:19a Klzhan
# [TAG]  		EIP70516
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update ME 8.0 RC 0.8
# [Files]  		AmtPlatformPolicy.c
# AmtPlatformPolicy.h
# AmtPlatformPolicy.sdl
# AmtPlatformPolicy.mak
# AmtPlatformPolicy.dxs
# AmtPlatformPolicy.cif
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
All : AmtPlatformPolicy

AmtPlatformPolicy : $(BUILD_DIR)\AmtPlatformPolicy.mak AmtPlatformPolicyBin

$(BUILD_DIR)\AmtPlatformPolicy.mak : $(AmtPlatformPolicy_DIR)\$(@B).cif $(AmtPlatformPolicy_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmtPlatformPolicy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtPlatformPolicy_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES) \
  $(MISCFRAMEWORK_INCLUDES) \
  $(NB_INCLUDES)\
  $(SB_INCLUDES)\
  /I$(PROJECT_DIR)\
  /IInclude\

AmtPlatformPolicy_LIBS=\
  $(EFIDRIVERLIB)\
  $(MeProtocolLib_LIB)\
  $(MeLibDxe_LIB)\
  $(MeGuidLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiLib_LIB)\

AmtPlatformPolicyBin : $(AmtPlatformPolicy_LIBS) 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AmtPlatformPolicy.mak all\
		GUID=1be65202-9318-492d-a551-08df2bd60aee\
		"MY_INCLUDES = $(AmtPlatformPolicy_INCLUDES)" \
		ENTRY_POINT=AmtPlatformPolicyEntryPoint\
		DEPEX1=$(AmtPlatformPolicy_DIR)\AmtPlatformPolicy.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
		TYPE=BS_DRIVER\
		COMPRESS=1

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
