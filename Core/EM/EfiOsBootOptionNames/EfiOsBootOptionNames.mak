#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**              5555 Oak brook Pkwy, Norcorss, GA 30093             **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/BootOptionPolicies/EfiOsBootOptionNames/EfiOsBootOptionNames.mak 5     3/11/15 6:48a Dukeyeh $
#
# $Revision: 5 $
#
# $Date: 3/11/15 6:48a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/BootOptionPolicies/EfiOsBootOptionNames/EfiOsBootOptionNames.mak $
# 
# 5     3/11/15 6:48a Dukeyeh
# [TAG]  		EIP178808
# [Category]  	New Feature
# [Description]  	Implement the selection of
# NEW_UEFI_OS_OPTION_ORDER_POLICY item in Setup.
# [Files]  		EfiOsBootOptionNames.sdl
# EfiOsBootOptionNames.mak
# EfiOsBootOrder.c
# EfiOsBootOptionNames.cif
# 
# 4     3/11/15 3:47a Dukeyeh
# [TAG]  		EIP204138
# [Category]  	Improvement
# [Description]  	Add a CREATE_BOOT_OPTION_WITH_UEFI_FILE_NAME_POLICY
# token to control whether create
# "UEFI OS" boot option if can't find any other in specified file paths
# (default) or just create it.
# [Files]  		EfiOsBootOptionNames.sdl
# EfiOsBootOptionNames.mak
# EfiOsBootOrder.c
# 
# 3     5/23/14 5:08a Dukeyeh
# [TAG]  		EIP167957 
# [Category]  	Bug Fix
# [RootCause]  	EIP147262 - The "EFI OS BootOptionNames" module can't
# support the "FixedBootOrder" module Boot option strings. 
# EIP159984 - Linux UEFI OS boot issue. 
# EIP168792 - Possible heap corruption - EFI OS BootOptionNames 
# [Solution]  	EIP147262 =>A new token
# "DISPLAY_FULL_OPTION_NAME_WITH_FBO" is added to control this.
# EIP159984 =>Should NOT kill the UEFI OS boot option that created by OS.
# EIP168792 =>NEW_STRING_BUFFER_LENGTH is replaced with the actual size
# of the allocated memory, NewStringLength. 
# 
# [Files]  		EfiOsBootOptionNames.sdl
# EfiOsBootOptionNames.mak
# EfiOsBootOptionNames.chm
# EfiOsBootOptionNames.c
# EfiOsBootOrder.c
# EfiOsBootOptionNames.cif
#  
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiOsBootOptionNames.mak
#
# Description:	
#   Adds EfiOsBootOptionNames.obj to AMITSEBin dependencies
#   and builds EfiOsBootOptionNames.obj.
#
#   Adds EfiOsBootOrder.obj to CORE_DXEBin dependencies
#   and builds EfiOsBootOrder.obj.
#
#<AMI_FHDR_END>
#**********************************************************************

#
#  EfiOsBootOrder.c
#
CORE_DXEBin : $(BUILD_DIR)\EfiOsBootOrder.obj

$(BUILD_DIR)\EfiOsBootOrder.obj : $(EfiOsBootOptionNames_DIR)\EfiOsBootOrder.c EfiOsFilePathMapElinkList
	$(CC) $(CFLAGS) /I$(TSEBIN_DIR)\Inc /I$(CORE_DXE_DIR) /Fo$(BUILD_DIR)\ $(EfiOsBootOptionNames_DIR)\EfiOsBootOrder.c $(BUILD_DIR)\EfiOsNamesFilePathMaps.h

EfiOsFilePathMapElinkList:
	$(SILENT)type << >$(BUILD_DIR)\EfiOsNamesFilePathMaps.h
#define EfiOsFilePathMaps $(EfiOsBootOptionNamesFilePathItem)
<<

#
#  EfiOsBootOptionNames.c
#
AMITSEBin: $(BUILD_DIR)\EfiOsBootOptionNames.obj

$(BUILD_DIR)\EfiOsBootOptionNames.obj : $(EfiOsBootOptionNames_DIR)\EfiOsBootOptionNames.c
    $(CC) $(CFLAGS) /I$(TSEBIN_DIR)\Inc /Fo$(BUILD_DIR)\ $(EfiOsBootOptionNames_DIR)\EfiOsBootOptionNames.c

#
#  SDB
#
SetupSdbs : $(BUILD_DIR)\EfiOsBootOptionNames.sdb

$(BUILD_DIR)\EfiOsBootOptionNames.sdb : $(EfiOsBootOptionNames_DIR)\$(@B).sd $(EfiOsBootOptionNames_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(EfiOsBootOptionNames_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(EfiOsBootOptionNames_DIR)\$(@B).sd

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**              5555 Oak brook Pkwy, Norcorss, GA 30093             **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
