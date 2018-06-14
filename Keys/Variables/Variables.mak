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
# $Header: /Alaska/SOURCE/Modules/SecureBoot_WIN8/SecureVariables/Variables.mak 3     7/25/13 9:14a Alexp $
#
# $Revision: 3 $
#
# $Date: 7/25/13 9:14a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SecureBoot_WIN8/SecureVariables/Variables.mak $
# 
# 3     7/25/13 9:14a Alexp
# EIP#118850: ECR1009: Add build rules to include "dbt" variable
# 
# 2     7/13/12 3:20p Alexp
# 1. Add .Help file containing description of Key certificates included
# in each Secure Variables
# 2. Modify Build rules in order to let file overrides from Create Vars
# Module
# 
# 1     6/05/12 4:59p Alexp
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: Certificates.mak
#
# Description:  
# 
#
#<AMI_FHDR_END>
#*************************************************************************
SecureBootModule: SETPLATFORMKEYS

#---------------------------------------------------------------------------
#        Set Secured Variables 
#---------------------------------------------------------------------------
SETPLATFORMKEYS: \
$(BUILD_DIR)\PkVar.ffs \
$(BUILD_DIR)\KekVar.ffs \
$(BUILD_DIR)\dbVar.ffs \
!IF "$(DBT_include)" == "1" 
$(BUILD_DIR)\dbtVar.ffs \
!ENDIF
!IF "$(DBX_include)" == "1" 
$(BUILD_DIR)\dbxVar.ffs
!ENDIF

PK_FFS_FILE_EFI_AUTH_VAR_GUID   = CC0F8A3F-3DEA-4376-9679-5426BA0A907E
KEK_FFS_FILE_AUTH_EFI_VAR_GUID  = 9FE7DE69-0AEA-470a-B50A-139813649189
DB_FFS_FILE_AUTH_EFI_VAR_GUID   = FBF95065-427F-47b3-8077-D13C60710998
DBX_FFS_FILE_AUTH_EFI_VAR_GUID  = 9D7A05E9-F740-44c3-858B-75586A8F9C8E
DBT_FFS_FILE_AUTH_EFI_VAR_GUID  = C246FBBF-F75C-43F7-88A6-B5FD0CF1DB7F

# PK is used as FW Root platform key. Used to verify Aptio FW images
$(BUILD_DIR)\PkVar.ffs : $(PkVar)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(PK_FFS_FILE_EFI_AUTH_VAR_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(*B)

$(BUILD_DIR)\KekVar.ffs : $(KekVar)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(KEK_FFS_FILE_AUTH_EFI_VAR_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(*B)

$(BUILD_DIR)\dbVar.ffs : $(dbVar)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(DB_FFS_FILE_AUTH_EFI_VAR_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(*B)

$(BUILD_DIR)\dbtVar.ffs : $(dbtVar)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(DBT_FFS_FILE_AUTH_EFI_VAR_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(*B)

$(BUILD_DIR)\dbxVar.ffs : $(dbxVar)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=$(DBX_FFS_FILE_AUTH_EFI_VAR_GUID) \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(*B)
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
