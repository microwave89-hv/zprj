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
# $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/AuthenticatedVariable_efi/AuthVariable.mak 6     8/15/13 11:26a Alexp $
#
# $Revision: 6 $
#
# $Date: 8/15/13 11:26a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/AuthenticatedVariable_efi/AuthVariable.mak $
# 
# 6     8/15/13 11:26a Alexp
# Link AmyCryptoLib
# 
# 5     11/19/12 4:41p Alexp
# Fix for Win8 SecureBoot logo requirement: restore Secure Boot state
# across flash updates.
# Move all secure boot Setup settings to a separate varstore variable. 
# Preserve var across re-flash
# 
# 4     10/16/12 3:45p Alexp
# Implemented  R/O Variables support via fixed and OEM defined (eLink)
# lists
# 
# 3     9/19/12 4:29p Alexp
# New feature: add facility to link external Physical User Presence
# detect hooks via eLink:PhysicalUserPresenceDetect
# 
# 2     6/30/11 4:02p Alexp
# added Callback event on Setup Mode change request form Security Setup
# Page.
# 
# 1     6/13/11 5:25p Alexp
# 
# 2     5/11/11 1:03p Alexp
# filled in file header text
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: AuthVariable.mak
# 
# Description:
# Link Authenticated Variable extension to NVRAM driver
#
#<AMI_FHDR_END>
#*************************************************************************
NvramDxeBin : $(BUILD_DIR)\$(NVRAM_DIR)\AUTHVARIABLE.obj $(BUILD_DIR)\$(NVRAM_DIR)\AUTH2VARIABLE.obj $(CRYPTOLIB)

AuthVariable_INCLUDES= \
    /I $(AuthVariable_DIR) \
    /I $(SecureBoot_DIR) \
    /I $(NVRAM_DIR)

AuthVariable_LISTS= \
    /D PHYSICAL_USER_PRESENCE_DETECT_LIST=$(PhysicalUserPresenceDetect) \
    /D OEM_READONLY_VAR_LIST=$(OemReadOnlyVariableList)

$(BUILD_DIR)\$(NVRAM_DIR)\AUTHVARIABLE.obj $(BUILD_DIR)\$(NVRAM_DIR)\AUTH2VARIABLE.obj: \
 $(AuthVariable_DIR)\AUTHVARIABLE.c $(AuthVariable_DIR)\AUTH2VARIABLE.c
    if not exist $(*D) mkdir $(*D)
    $(CC) $(CFLAGS) $(AuthVariable_LISTS) $(AuthVariable_INCLUDES) /Fo$@ $(AuthVariable_DIR)\$(*B).c

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
