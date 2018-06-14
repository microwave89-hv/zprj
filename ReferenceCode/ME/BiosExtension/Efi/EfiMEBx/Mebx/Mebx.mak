#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
#**********************************************************************
#
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/BiosExtension/EfiMEBx/MEBx/Mebx.mak 2     4/23/12 10:51p Klzhan $
#
# $Revision: 2 $
#
# $Date: 4/23/12 10:51p $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/BiosExtension/EfiMEBx/MEBx/Mebx.mak $
# 
# 2     4/23/12 10:51p Klzhan
# 1. Update MEBX binary
# 2. Add Elink for OEM to locate MEBX path.
# 
# 1     2/08/12 12:59a Klzhan
# Initial Check in 
# 
# 3     9/26/11 5:35a Klzhan
# [TAG]  		EIP70516
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update ME 8.0 RC 0.8
# 
# 2     3/25/11 3:23a Klzhan
# Improvement : Remove un-use lines,and update Include path.
# 
# 1     3/24/11 2:09a Klzhan
# [TAG]  		EIP56501
# [Category]  	Improvement
# [Description]  	Support EFI MEBX.
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            MEBX.mak
#
# Description:     EFI MEBX
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : $(BUILD_DIR)\Mebx.ffs

Mebx_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES)\
  $(EDK_INCLUDES)


$(BUILD_DIR)\Mebx.ffs : $(EFIMebx_FILE_PATH) $(Mebx_DIR)\$(@B).mak Core\FFS.mak
            $(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
            CPFLAGS="$(GLOBAL_DEFINES) /D TIANO_RELEASE_VERSION=0x00080006 $(EXTRA_DEFINES) $(Mebx_INCLUDES)" \
            BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(Mebx_DIR) \
            GUID=9cfd802c-09a1-43d6-8217-aa49c1f90d2c\
            NAME=$(@B)\
            TYPE=EFI_FV_FILETYPE_DRIVER \
            DEPEX1=$(Mebx_DIR)\Mebx.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
            PEFILE=$(EFIMebx_FILE_PATH) FFSFILE=$@ COMPRESS=1 \

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************