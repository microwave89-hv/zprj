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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MdesStatusCode/MdesStatusCode.mak 1     7/27/12 5:12a Klzhan $
#
# $Revision: 1 $
#
# $Date: 7/27/12 5:12a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MdesStatusCode/MdesStatusCode.mak $
# 
# 1     7/27/12 5:12a Klzhan
# [TAG]  		EIPNone
# [Category]  	New Feature
# [Description]  	Add support MDES
# [Files]  		MdesStatusCode.cif
# MdesStatusCode.sdl
# MdesStatusCode.mak
# MdesStatusCodeDxe.c
# 
# 2     12/08/11 3:29a Klzhan
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Fix build error when AMT disabled.
# 
# 1     10/19/11 9:06a Calvinchen
# [TAG]  		EIPNone
# [Category]  	New Feature
# [Description]  	Added MDES BIOS Status Code Support.
# [Files]  		MdesStatusCode.cif
# MdesStatusCode.sdl
# MdesStatusCode.mak
# MdesStatusCodeDxe.c
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:		MeStatusCode.mak
#
# Description:	AMT Status Code Makfile.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

#---------------------------------------------------------------------------
#  AMT StatusCode for DXE
#---------------------------------------------------------------------------
MdesStatusCodeIncludes =\
  /I$(MeProtocolLib_DIR)\MePlatformPolicy \
  $(ME_INCLUDES)\
  /I$(MdesStatusCodeDrv_DIR)

CORE_DXEBin : $(BUILD_DIR)\$(STATUS_CODE_DIR)\MdesStatusCodeDxe.obj

$(BUILD_DIR)\$(STATUS_CODE_DIR)\MdesStatusCodeDxe.obj : $(MdesStatusCode_DIR)\MdesStatusCodeDxe.c
  $(CC) $(CFLAGS:/W4=/W3) /DTIANO_RELEASE_VERSION=0x00080006 $(MdesStatusCodeIncludes) /DDXE_STATUS_CODE $(AlertStandardFormatDxe_INCLUDES) $(EDK_INCLUDES) $(STATUS_CODE_INCLUDES) /Fo$(BUILD_DIR)\$(STATUS_CODE_DIR)\MdesStatusCodeDxe.obj $(MdesStatusCode_DIR)\MdesStatusCodeDxe.c

RUNTIMEBin : $(BUILD_DIR)\$(STATUS_CODE_DIR)\MdesStatusCodeRuntime.obj
$(BUILD_DIR)\$(STATUS_CODE_DIR)\MdesStatusCodeRuntime.obj : $(MdesStatusCode_DIR)\MdesStatusCodeDxe.c
  $(CC) $(CFLAGS:/W4=/W3) /DTIANO_RELEASE_VERSION=0x00080006 $(EDK_INCLUDES) $(STATUS_CODE_INCLUDES) /Fo$(BUILD_DIR)\$(STATUS_CODE_DIR)\MdesStatusCodeRuntime.obj $(MdesStatusCode_DIR)\MdesStatusCodeDxe.c

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************