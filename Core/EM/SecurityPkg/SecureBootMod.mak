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
# $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/SecureBootMod.mak 14    11/19/12 4:40p Alexp $
#
# $Revision: 14 $
#
# $Date: 11/19/12 4:40p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/SecureBootMod.mak $
# 
# 14    11/19/12 4:40p Alexp
# Fix for Win8 SecureBoot logo requirement: restore Secure Boot state
# across flash updates.
# Move all secure boot Setup settings to a separate varsore variable. 
# Preserve var across re-flash
# 
# 13    8/23/12 5:40p Alexp
# Added SecureBootMod.c file to the list of String Consumers
# 
# 12    8/15/12 4:48p Alexp
# 1. Modify Secure Boot page controls. Hide all controls under new
# sub-page 
# 2. Refrash Secure Boot Setup screens upon user load Defaults/Previous
# values
# 3. 
# 
# 11    6/05/12 10:30a Alexp
# moved build rules for default SecureVariables to SecureVariable eModule
# 
# 10    6/01/12 4:13p Alexp
# cleaned up Include list
# 
# 8     3/09/12 3:29p Alexp
# Implementation to PRESERVE_SECURE_VARIABLES on Flash Update is moved
# here from SecSmiFlash component
# 
# 7     8/25/11 8:33a Alexp
# add back .dxs dependency on AmiDigitalSig protocol. Needed if Secure
# Variable provisioning is enabled at Driver's entry point
# 
# 6     8/24/11 6:23p Alexp
# link SecureBootMod.obj to SetupBin. 
# 
# 5     8/22/11 5:19p Alexp
# restored CallBack notification method to set Manufacturing defaults
# from TSE SetupPage
# 
# 4     8/18/11 4:50p Alexp
# 1. removed callback events on Security Page updates
# 2. Add DEPEX on AmiDigitalSig protocol
# 
# 3     7/18/11 9:58a Alexp
# make Variable ffs files compressed
# 
# 2     6/30/11 4:25p Alexp
# add dependency on SecureVariable module with OEM defined default
# variables for PK-KEK-db-dbx
# if present will add setup control to provision default Secure Variables
# 
# 1     6/30/11 3:47p Alexp
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SecureBootMod.mak
#
# Description:  
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all: SecureBootModule

SecureBootModule : $(BUILD_DIR)\SecureBootMod.mak SecureBootModDxe

$(BUILD_DIR)\SecureBootMod.mak : $(SecureBoot_DIR)\SecureBootMod.cif $(BUILD_RULES)
    $(CIF2MAK) $(SecureBoot_DIR)\SecureBootMod.cif $(CIF2MAK_DEFAULTS)

SecureBootModDxe : $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SecureBootMod.mak all\
        NAME=SecureBootMod\
        "MY_INCLUDES=/I$(SecureBoot_DIR)"\
        MAKEFILE=$(BUILD_DIR)\SecureBootMod.mak \
        GUID=A95C1D60-CB9F-4BD8-A030-3F1C4A185156 \
        ENTRY_POINT=SecureBootMod_Init\
        "EXT_HEADERS=$(BUILD_DIR)\SetupStrTokens.h $(BUILD_DIR)\AUTOID.h"\
        DEPEX1=$(SecureBoot_DIR)\SecureBootMod.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        TYPE=BS_DRIVER COMPRESS=1

#---------------------------------------------------------------------------
#        Create Setup Screen(s)
#---------------------------------------------------------------------------
SetupSdbs : SecureBootModSDB 

SecureBootModSDB : $(BUILD_DIR)\SecureBootMod.mak
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SecureBootMod.mak all\
        TYPE=SDB NAME=SecureBootMod\
        "MY_INCLUDES=/I$(SecureBoot_DIR)"\
        "STRING_CONSUMERS=$(SecureBoot_DIR)\SecureBootMod.sd $(SecureBoot_DIR)\SecureBootMod.c"

#---------------------------------------------------------------------------
#        Link Callback Lib to Setup
#---------------------------------------------------------------------------
SetupBin : $(BUILD_DIR)\$(Setup_DIR)\SecureBootMod.obj

$(BUILD_DIR)\$(Setup_DIR)\SecureBootMod.obj : $(SecureBoot_DIR)\SecureBootMod.c $(BUILD_DIR)\SetupStrTokens.h
    $(CC) $(CFLAGS) /I$(SecureBoot_DIR) /DSETUP_COMPILE=1 $(SecureBoot_DIR)\SecureBootMod.c /Fo$@

AMITSEBin : $(BUILD_DIR)\$(TSEBIN_DIR)\SecureBootMod.obj
$(BUILD_DIR)\$(TSEBIN_DIR)\SecureBootMod.obj : $(SecureBoot_DIR)\SecureBootMod.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /DTSEBIN_COMPILE=1 /I$(SecureBoot_DIR) /I $(TSEBIN_DIR)\Inc /I $(TSEBIN_DIR) /I$(CORE_DIR) $(SecureBoot_DIR)\SecureBootMod.c /Fo$@

#---------------------------------------------------------------------------
#       Link SMIFlash hooks to SmiFlash module
#---------------------------------------------------------------------------
!IF "$(PRESERVE_SECURE_VARIABLES)" == "1"
SMIFlashBin : $(BUILD_DIR)\$(SMI_FLASH_DIR)\SecureBootMod.obj

$(BUILD_DIR)\$(SMI_FLASH_DIR)\SecureBootMod.obj: $(SecureBoot_DIR)\SecureBootMod.c
    $(CC) $(CFLAGS) /I$(SecureBoot_DIR) /I$(CORE_DIR) /DSMIFLASH_COMPILE=1 /DSMM_COMPILE=1 /Fo$@ $**
!ENDIF

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
