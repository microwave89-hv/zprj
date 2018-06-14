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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCode.mak 1     2/08/12 1:10a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:10a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtStatusCode/AmtStatusCode.mak $
# 
# 1     2/08/12 1:10a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:44a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:10a Klzhan
# Initial Check-in.
#
#**********************************************************************
#
#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:		AMTStatusCode.mak
#
# Description:	AMT Status Code Makfile.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

#---------------------------------------------------------------------------
#  AMT StatusCode for DXE
#---------------------------------------------------------------------------
CORE_DXEBin : $(BUILD_DIR)\$(STATUS_CODE_DIR)\AmtStatusCodeDxe.obj

$(BUILD_DIR)\$(STATUS_CODE_DIR)\AmtStatusCodeDxe.obj : $(AmtStatusCode_DIR)\AmtStatusCodeDxe.c
  $(CC) $(CFLAGS:/W4=/W3) /DTIANO_RELEASE_VERSION=0x00080006 /DDXE_STATUS_CODE $(AlertStandardFormatDxe_INCLUDES) $(EDK_INCLUDES) $(STATUS_CODE_INCLUDES) /Fo$(BUILD_DIR)\$(STATUS_CODE_DIR)\AmtStatusCodeDxe.obj $(AmtStatusCode_DIR)\AmtStatusCodeDxe.c

#---------------------------------------------------------------------------
#  AMT StatusCode for PEI
#---------------------------------------------------------------------------
CORE_PEIBin : $(BUILD_DIR)\$(STATUS_CODE_DIR)\AmtStatusCodePei.obj

$(BUILD_DIR)\$(STATUS_CODE_DIR)\AmtStatusCodePei.obj : $(AmtStatusCode_DIR)\AmtStatusCodePei.c
  $(CCPEI) $(CFLAGS:/W4=/W3) /DTIANO_RELEASE_VERSION=0x00080006 /DPEI_STATUS_CODE /IEDK\Foundation\Include\IA32 $(AlertStandardFormatPei_INCLUDES) $(EDK_INCLUDES) $(ME_INCLUDES) $(STATUS_CODE_INCLUDES) /Fo$(BUILD_DIR)\$(STATUS_CODE_DIR)\AmtStatusCodePei.obj $(AmtStatusCode_DIR)\AmtStatusCodePei.c

#---------------------------------------------------------------------------
#  AMT StatusCode for SMM
#---------------------------------------------------------------------------
SmmStatusCodeBin : $(BUILD_DIR)\$(SmmStatusCode_DIR)\AmtStatusCodeSmm.obj

$(BUILD_DIR)\$(SmmStatusCode_DIR)\AmtStatusCodeSmm.obj : $(AmtStatusCode_DIR)\AmtStatusCodeSmm.c
  $(CC) $(CFLAGS:/W4=/W3) /DTIANO_RELEASE_VERSION=0x00080006 /DSMM_STATUS_CODE $(AlertStandardFormat_INCLUDES) $(ME_INCLUDES) $(STATUS_CODE_INCLUDES) $(CORE_INCLUDES) /Fo$(BUILD_DIR)\$(SmmStatusCode_DIR)\AmtStatusCodeSmm.obj $(AmtStatusCode_DIR)\AmtStatusCodeSmm.c

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