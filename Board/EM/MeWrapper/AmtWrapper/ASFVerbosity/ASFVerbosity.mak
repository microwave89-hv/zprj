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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/ASF Verbosity/ASFVerbosity.mak 1     2/08/12 1:10a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:10a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/ASF Verbosity/ASFVerbosity.mak $
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
#
#**********************************************************************

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
#
# Name: ASFVerbosity.mak
#
# Description: This make file build ASFVerbosity
#               components and link them to respective binary
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>

all : ASFVERB

BUILD_ASF_VWEBOSITY_DIR = $(BUILD_DIR)\$(ASF_VWEBOSITY_DIR)

#---------------------------------------------------------------------------
#           Generic AMT dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\ASFVerbosity.mak : $(ASF_VWEBOSITY_DIR)\ASFVerbosity.cif $(BUILD_RULES)
    $(CIF2MAK) $(ASF_VWEBOSITY_DIR)\ASFVerbosity.cif $(CIF2MAK_DEFAULTS)
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#       Create ASF Verbosity DXE Component
#---------------------------------------------------------------------------
ASFVERB: $(BUILD_DIR)\ASFVerbosity.mak ASFVERBBin

ASFVERBBin : $(AMIDXELIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\ASFVerbosity.mak all\
            GUID=4f4ff580-b8a0-4332-a6b0-e2e568e36c9c \
            ENTRY_POINT=ASFVerbosityEntryPoint \
            TYPE=BS_DRIVER \
            COMPRESS=1
#---------------------------------------------------------------------------



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
