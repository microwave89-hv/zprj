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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePlatformPolicy.mak 4     12/04/12 5:57a Klzhan $
#
# $Revision: 4 $
#
# $Date: 12/04/12 5:57a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePlatformPolicy/MePlatformPolicy.mak $
# 
# 4     12/04/12 5:57a Klzhan
# [TAG]  		EIP107309
# [Category]  	New Feature
# [Description]  	Support ICC library for ME 9.5
# [Files]  		MePlatformPolicy.c
# MePlatformPolicy.h
# MePlatformPolicy.sdl
# MePlatformPolicy.mak
# MePlatformPolicy.cif
# 
# 3     4/23/12 11:13p Klzhan
# 
# 2     2/23/12 8:56a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:04a Klzhan
# Initial Check in 
# 
# 5     9/07/11 4:49a Klzhan
# Get thermal reporting data from HOB.
# 
# 4     7/26/11 8:23a Klzhan
# [TAG]  		EIP64542
# [Category]  	Improvement
# [Description]  	Replace  GetSbSetupData.
# 
# 3     7/11/11 4:41a Klzhan
# Fix system can't boot on ME FW 1076.
# 
# 2     7/08/11 4:20a Klzhan
# [TAG]  		EIP64189
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update ME RC to 0.7
# [Files]  		MePlatformPolicy.c
# MePlatformPolicy.h
# MePlatformPolicy.sdl
# MePlatformPolicy.mak
# MePlatformPolicy.cif
# 
# 1     2/25/11 1:41a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:09a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            MePlatformPolicy.mak
#
# Description:     
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
All : MePlatformPolicy

MePlatformPolicy : $(BUILD_DIR)\MePlatformPolicy.mak MePlatformPolicyBin

$(BUILD_DIR)\MePlatformPolicy.mak : $(MePlatformPolicy_DIR)\$(@B).cif $(MePlatformPolicy_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(MePlatformPolicy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MePlatformPolicy_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES) \
  $(MISCFRAMEWORK_INCLUDES) \
  $(NB_INCLUDES)\
  $(SB_INCLUDES)\
  /I$(PROJECT_DIR)\
  /IInclude\
  /I$(IccOverClocking_DIR)\
  /I$(INTEL_COUGAR_POINT_INCLUDE_DIR)

MePlatformPolicy_LIBS=\
  $(EdkIIGlueBaseLib_LIB)\
  $(EFIDRIVERLIB)\
  $(MeProtocolLib_LIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\

MePlatformPolicyBin : $(MePlatformPolicy_LIBS)
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
                /f $(BUILD_DIR)\MePlatformPolicy.mak all\
                GUID=BA67550C-3628-4137-A53E-42660E081604\
                "MY_INCLUDES = $(MePlatformPolicy_INCLUDES)" \
                ENTRY_POINT=MePlatformPolicyEntryPoint\
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