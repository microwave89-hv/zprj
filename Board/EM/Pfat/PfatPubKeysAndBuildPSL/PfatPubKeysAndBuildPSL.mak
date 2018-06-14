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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatUtilsandScripts/PfatPubKeysAndBuildPSL.mak 1     10/29/12 4:04p Fredericko $
#
# $Revision: 1 $
#
# $Date: 10/29/12 4:04p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatUtilsandScripts/PfatPubKeysAndBuildPSL.mak $
# 
# 1     10/29/12 4:04p Fredericko
# [TAG]  		EIP844115
# [Category]  	Improvement
# [Description]  	Added PfatPubKeysAndBuildPSL. Added Tools CutRom for
# stiching PfatImage, BuildAmiPfatHeader for creating Apfatdos header for
# PFAT. 
# [Files]  		PfatPubKeysAndBuildPSL.cif
# PfatPubKeysAndBuildPSL.sdl
# PfatPubKeysAndBuildPSL.mak
# dummy.bin
# BuildPSL.bat
# BuildAmiPfatHeader.exe
# CutRom.exe
#
# 7     9/21/12 5:08p Fredericko
# Modified to use cryptocon and keygen
#
# 4     9/17/12 4:34p Fredericko
# Changes to create PSL at build time. Changes for SignPfat utility error
# during build.
#
# 3     9/10/12 10:52p Fredericko
#
# 2     9/10/12 9:55p Fredericko
#
# 1     9/01/12 2:22a Fredericko
#
#*************************************************************************
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: PfatPubKey.mak
#
# Description:  Make for for PfatPubKey
#
#
#<AMI_FHDR_END>
#*************************************************************************
all: PfatPubKeyModule

PfatPubKeyModule : SETPFATPUBKEY

PFAT_PUB_KEY_FFS_FILE_GUID    = 8E295870-D377-4b75-BFDC-9AE2F6DBDE22

SETPFATPUBKEY: $(BUILD_DIR)\PfatPubKey.ffs

PUBLIC_KEY_FILENAME = $(PFATPUB_DIR)\PfatPublic.key
PRIVATE_KEY_FILENAME = $(PFATPUB_DIR)\PfatPrivate.key
PFAT_VKEY_EXP = $(PFATPUB_DIR)\.VkeyExp
PUBLIC_KEY_FILENAME_HASH = $(PFATPUB_DIR)\PubKeyhash.bin

PFAT_GENERATE_KEYS:
    del $(PUBLIC_KEY_FILENAME_HASH)
    if not exist $(PUBLIC_KEY_FILENAME) $(KEYGEN) $(PRIVATE_KEY_FILENAME) $(PUBLIC_KEY_FILENAME)
  	$(PFATCRYPTCON) -z -w -k $(PRIVATE_KEY_FILENAME) -f $(PFATPUB_DIR)\dummy.bin -s
    copy /b .out_key + $(PFAT_VKEY_EXP) $(PUBLIC_KEY_FILENAME_HASH)
    $(PFATCRYPTCON) -h2 -f $(PUBLIC_KEY_FILENAME_HASH) -o $(PUBLIC_KEY_FILENAME_HASH)

PREPARE : PFAT_GENERATE_KEYS

$(BUILD_DIR)\PfatPubKey.ffs : $(PUBLIC_KEY_FILENAME_HASH)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(PFAT_PUB_KEY_FFS_FILE_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=PfatPubKey

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
