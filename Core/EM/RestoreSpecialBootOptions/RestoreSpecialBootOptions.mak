#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/BootOptionPolicies/RestoreSpecialBootOptions/RestoreSpecialBootOptions.mak 2     7/12/13 12:42a Dukeyeh $
#
# $Revision: 2 $
#
# $Date: 7/12/13 12:42a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/BootOptionPolicies/RestoreSpecialBootOptions/RestoreSpecialBootOptions.mak $
# 
# 2     7/12/13 12:42a Dukeyeh
# [TAG]  		EIP127111
# [Category]  	New Feature
# [Description]  	Initial Release.
# [Files]  		RestoreSpecialBootOptions.mak
# 
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	RestoerSpecialBootOptions.mak
#
# Description: Makefile for the RestoreSpecialBootOptions component. 
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\RestoreSpecialBootOptions.obj 

OBJ_DEPENDENCIES = \
	$(RestoreSpecialBootOptions_DIR)\RestoreSpecialBootOptions.c\
	$(BUILD_DIR)\RestoreSpecialBootOptions.h
	
$(BUILD_DIR)\RestoreSpecialBootOptions.obj : $(OBJ_DEPENDENCIES)
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(RestoreSpecialBootOptions_DIR)\RestoreSpecialBootOptions.c

H_DEPENDENCIES = \
	$(BUILD_DIR)\Token.h\
	$(RestoreSpecialBootOptions_DIR)\RestoreSpecialBootOptions.mak

$(BUILD_DIR)\RestoreSpecialBootOptions.h : $(H_DEPENDENCIES)
    	$(SILENT)type << >$(BUILD_DIR)\RestoreSpecialBootOptions.h
#define RESTORED_BOOT_OPTION_NAMES $(RESTORED_BOOT_OPTION_NAMES)
<<

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
