#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/BlockS3Var/BlockS3Var.mak 1     6/18/15 4:02a Calvinchen $
#
# $Revision: 1 $
#
# $Date: 6/18/15 4:02a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/BlockS3Var/BlockS3Var.mak $
# 
# 1     6/18/15 4:02a Calvinchen
# [TAG]  		EIP224171
# [Category]  	New Feature
# [Description]  	Initial check-in for New Security Vulnerabilities :
# Intel-TA-201505-001
# [Files]  		BlockS3Var.cif
# BlockS3Var.chm
# BlockS3Var.sdl
# BlockS3Var.mak
# BlockS3Var.c
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         BlockS3Var.mak
#
# Description:  This make file builds Blocked S3 Variable eModule
#
#<AMI_FHDR_END>
#*************************************************************************
Prepare : $(BUILD_DIR)/BlockedS3Var.h

$(BUILD_DIR)/BlockedS3Var.h :  $(BUILD_DIR)/token.mak
	$(ECHO) \
 #define BLOCKED_S3_VAR_ELINK $(BLOCKED_S3_VAR_LIST)$(EOL)\
> $(BUILD_DIR)/BlockedS3Var.h

NvramDxeBin : $(BUILD_DIR)\BlockS3Var.obj

BLOCKED_S3_VAR_CFLAGS=$(CFLAGS) /D\"BLOCKED_S3_VAR_LIST=$(BLOCKED_S3_VAR_LIST)\"

$(BUILD_DIR)\BlockS3Var.obj : $(BLOCK_S3_VAR_DIR)\BlockS3Var.c
	$(CC) $(BLOCKED_S3_VAR_CFLAGS) /Fo$(BUILD_DIR)\ $(BLOCK_S3_VAR_DIR)\BlockS3Var.c

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************