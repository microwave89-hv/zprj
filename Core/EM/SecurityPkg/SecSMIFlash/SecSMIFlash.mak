#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/SecSMIFlash.mak 14    3/18/14 3:12p Alexp $
#
# $Revision: 14 $
#
# $Date: 3/18/14 3:12p $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureFlashPkg/SecureSmiFlash/SecSMIFlash.mak $
# 
# 14    3/18/14 3:12p Alexp
# update year to 2014 in ftr & hdr
# 
# 13    11/21/12 10:40a Alexp
# do not link CryptoLib with SecSmiFlash.
# 
# 12    8/10/12 11:48a Alexp
# Removed build rules of now obsolete SecSmiFlashHooks 
# 
# 11    5/18/12 5:03p Alexp
# 1. Link Crypto Library with VerifyFwCap in Recovery boot flow.Use Hash
# functions only
# 2. Pass SEC_FLASH_GUID_DEFINES containing unique FwCap Ffs Guid and
# Section guids
# 
# 10    12/01/11 5:30p Alexp
# restore build rules. When needed, PRESERVE_LIB eLink can be reused
# 
# 9     12/01/11 3:37p Alexp
#  Add Build target for SecSmiFlashHooks library. New lib is linked to
#  SmiFlash and (or) OFBD SecFlash via PRESERVE_LIB eLink list
# 
# 7     11/30/11 8:13p Alexp
# left optional link rules for future usage with Ofbd module
# 
# 5     9/20/11 2:20p Alexp
# removed linkage of SecFlashHooks with ReFlash.
# 
# 4     8/18/11 4:47p Alexp
# 1. Add Depex rule to launch SecSmiFlash after AimDigitalSig protocol is
# available
# 2. Link SecSMIFlashHooks to ReFlash driver. Needed to preserve
# SecureVars on Recovery style reFlash
# 
# 3     8/11/11 5:32p Alexp
# updated header
# 
# 2     8/05/11 3:28p Alexp
# add SMM_COMPILE flag to SecSMIFlashHook compile rules
# 
#************************************************************************//

all : SecSMIFlash

SecSMIFlash : $(BUILD_DIR)\SecSMIFlash.mak SecSMIFlashBin

$(BUILD_DIR)\SecSMIFlash.mak : $(SEC_SMI_FLASH_DIR)\SecSMIFlash.cif $(SEC_SMI_FLASH_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SEC_SMI_FLASH_DIR)\SecSMIFlash.cif $(CIF2MAK_DEFAULTS)

BUILD_SecSMIFlash_DIR = $(BUILD_DIR)\$(SEC_SMI_FLASH_DIR)

SecSMIFlash_INCLUDES= \
    /I $(SEC_SMI_FLASH_DIR)\
    /I$(CORE_DIR)

SecSMIFlash_OBJECTS = \
    $(BUILD_SecSMIFlash_DIR)\SecSMIFlash.obj \
    $(BUILD_SecSMIFlash_DIR)\VerifyFwCapsule.obj

SecSMIFlashBin : $(AMIDXELIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SecSMIFlash.mak all\
        GUID=3BF4AF16-AB7C-4b43-898D-AB26AC5DDC6C\
        ENTRY_POINT=SecSMIFlashDriverEntryPoint\
        OBJECTS="$(SecSMIFlash_OBJECTS)" \
        "CFLAGS=$(CFLAGS) $(SEC_FLASH_GUID_DEFINES)" \
        TYPE=RT_DRIVER "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        DEPEX1=$(SEC_SMI_FLASH_DIR)\SecSMIFlash.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
