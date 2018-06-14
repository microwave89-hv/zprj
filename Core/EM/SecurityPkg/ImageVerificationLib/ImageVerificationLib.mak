#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/ImageVerification_efi/ImageVerificationLib.mak 5     8/15/13 11:28a Alexp $
#
# $Revision: 5 $
#
# $Date: 8/15/13 11:28a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/ImageVerification_efi/ImageVerificationLib.mak $
# 
# 5     8/15/13 11:28a Alexp
# 
# 4     11/19/12 4:42p Alexp
# Fix for Win8 SecureBoot logo requirement: restore Secure Boot state
# across flash updates.
# Move all secure boot Setup settings to a separate varsore variable. 
# Preserve var across re-flash
# 
# 3     6/30/11 4:01p Alexp
# moved Setup Page defines to parent SecureBoot module
# 
# 2     6/15/11 3:06p Alexp
# removed commented instructions 
# 
# 1     6/13/11 5:25p Alexp
# 
# 5     5/17/11 5:35p Alexp
# 
# 
# 3     5/11/11 1:03p Alexp
# update file hdr 
# 
# 2     5/10/11 12:35p Alexp
# 
# 1     5/09/11 10:04a Alexp
# 
# 3     5/04/11 7:15p Alexp
# add Setup controls on Secure page
# 
# 2     4/11/11 12:58p Alexp
# remove Crypto lib linkage
# 
# 1     3/12/11 11:31a Alexp
# 
# 1     3/10/11 5:00p Alexp
# 
# 1     3/03/11 6:35p Alexp
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: ImageVerificationLib.mak
#
# Description:  installs Security Architecture Protocol 
# 
#
#<AMI_FHDR_END>
#*************************************************************************
CORE_DXE_LIBBin : $(IMAGEVERIFY_LIB)

$(IMAGEVERIFY_LIB) : $(BUILD_DIR)\ImageVerificationLib.mak ImageVerificationLibBin

$(BUILD_DIR)\ImageVerificationLib.mak : $(ImageVerificationLib_DIR)\ImageVerificationLib.cif $(BUILD_RULES)
    $(CIF2MAK) $(ImageVerificationLib_DIR)\ImageVerificationLib.cif $(CIF2MAK_DEFAULTS)

ImageVerificationLib_INCLUDES= \
    /I $(ImageVerificationLib_DIR) \
    /I $(SecureBoot_DIR) \
    /I $(CORE_DIR)

ImageVerificationLibBin :  $(CRYPTOLIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
    /f $(BUILD_DIR)\ImageVerificationLib.mak all\
    NAME=ImageVerificationLib\
    MAKEFILE=$(BUILD_DIR)\ImageVerificationLib.mak\
    "MY_INCLUDES= $(ImageVerificationLib_INCLUDES)" \
    TYPE=LIBRARY
