#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/TxtSinitAcm/TxtSinitAcm.mak 1     8/14/13 4:35a Davidhsieh $
#
# $Revision: 1 $
#
# $Date: 8/14/13 4:35a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Haswell/AMI Cpu PKG/AMI TXT DXE/TxtSinitAcm/TxtSinitAcm.mak $
# 
# 1     8/14/13 4:35a Davidhsieh
# [TAG]  		None
# [Category]  	New Feature
# [Description]  	Txt Sinit ACM is included in BIOS
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Sinitacm.mak
#
# Description:
#  
#
#<AMI_FHDR_END>
#**********************************************************************
all : SinitAcmBin

#---------------------------------------------------------------------------
#               SINIT ACM
#---------------------------------------------------------------------------

SinitAcmBin : $(BUILD_DIR)\SinitAcmBin.ffs

$(BUILD_DIR)\SinitAcmBin.ffs : $(SINITACM_FILE)
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=7fbfe0ea-0e9d-406b-a202-ca6a7d0e0f1e \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1987-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************