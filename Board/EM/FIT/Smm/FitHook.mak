#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Smm/FitHook.mak 1     7/03/13 10:06p Bensonlai $
#
# $Revision: 1 $
#
# $Date: 7/03/13 10:06p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/FIT/Smm/FitHook.mak $
# 
# 1     7/03/13 10:06p Bensonlai
# [TAG]  		EIP128151
# [Category]  	Improvement
# [Description]  	Implement an option(/b) to flash FV_DATA region uisng
# AFU flash utility.
# [Files]  		FitHook.cif
# FitHook.c
# FitHook.sdl
# FitHook.mak
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: FitHook.mak
#
# Description: Make file for FitHook eModule.
#
#<AMI_FHDR_END>
#*************************************************************************

all : FitHook

FitHook : $(BUILD_DIR)\FitHook.mak FitHookBin

$(BUILD_DIR)\FitHook.mak : $(FIT_HOOK_PATH)\$(@B).cif $(FIT_HOOK_PATH)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(FIT_HOOK_PATH)\$(@B).cif $(CIF2MAK_DEFAULTS)

FitHookObjs = $(BUILD_DIR)\$(FIT_HOOK_PATH)\FitHook.obj

FitHookBin : $(AMIDXELIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\FitHook.mak all\
            "CFLAGS=$(CFLAGS:/W4=/W3) /I$(OFBD_DIR)" \
            OBJECTS="$(FitHookObjs)" \
            NAME=FitHook \
            TYPE=LIBRARY LIBRARY_NAME=$(FIT_HOOK_LIB)

$(FIT_HOOK_LIB) : FitHook

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
