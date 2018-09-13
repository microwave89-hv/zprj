#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/SLP/SlpSupport.mak 8     8/09/11 10:18a Vyacheslava $
# $Revision: 8 $
# $Date: 8/09/11 10:18a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/SLP/SlpSupport.mak $
# 
# 8     8/09/11 10:18a Vyacheslava
# [TAG]  		EIP63678 
# [Description]  	The modules GUID has been changed. 
# 
# 7     7/01/11 12:00p Vyacheslava
# [TAG]  		EIP63678
# [Category]  	New Feature
# [Description]  	Preserve the OEM Activation SLIC during the BIOS
# recovery path.
# [Files]  		SlpSupport.sdl
# SlpSupport.mak
# SlpSupport.c
# SlpSupport.dxs
# SlpSupport.h
# SlpSupport.cif
# 
# 6     5/18/10 4:14p Vyacheslava
# Updated copiright header.
# 
# 5     8/19/09 11:49a Vyacheslava
# Removed token USE_SOURCE_BINARIES (EIP#25334).
# 
# 4     6/12/09 11:02a Vyacheslava
# EIP#23109: Synopsis: Tokens for SlpSupport eModule.
# Description: SlpSupport eModule needs to have tokens
# SLP_MARKER_ROM_FILENAME SLP_PUBKEY_ROM_FILENAME to make more flexible
# in changing Marker and Public Key files.
# 
# 3     2/11/08 12:01p Felixp
# Make file bug fix.
# 
# 2     5/30/07 6:24p Aaronp
# Changed mak file to allow for SDL token to include or exclude 
# the Public Key binary and the Marker binary.  This is necssary
# for supporting the AMISLP tool from the utilites group.
# 
# 1     3/30/07 3:39p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: SlpSupport.mak
#
# Description: Make file for SlpSupport eModule.
#
#<AMI_FHDR_END>
#**********************************************************************

all : SLP

SLP20MARKER_GUID = 69009842-63F2-43db-964B-EFAD1C39EC85
SLP20PUBKEY_GUID = 996AA1E0-1E8C-4f36-B519-A170A206FC14

SLP_BINARIES : $(BUILD_DIR)\SLP20Marker.ffs $(BUILD_DIR)\SLP20PubKey.ffs
SLP : $(BUILD_DIR)\SlpSupport.mak SlpSupportBin SLP_BINARIES

$(BUILD_DIR)\SlpSupport.mak : $(SLP_SUPPORT_DIR)\SlpSupport.cif 
    $(CIF2MAK) $(SLP_SUPPORT_DIR)\SlpSupport.cif $(CIF2MAK_DEFAULTS)

SlpSupportBin: $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SlpSupport.mak all\
        GUID=952821AA-EACD-465b-B478-5429DFC9A747\
        ENTRY_POINT=SlpSupport_EntryPoint\
        TYPE=BS_DRIVER\
        "EXT_HEADERS=$(BUILD_DIR)\Token.h"\
        COMPRESS=1

$(BUILD_DIR)\SLP20Marker.ffs : $(SLP_MARKER_ROM_FILENAME) 
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(SLP20MARKER_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)
 
$(BUILD_DIR)\SLP20PubKey.ffs : $(SLP_PUBKEY_ROM_FILENAME)
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(SLP20PUBKEY_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
