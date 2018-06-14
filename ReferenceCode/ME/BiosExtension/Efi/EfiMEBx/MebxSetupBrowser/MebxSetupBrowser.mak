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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/BiosExtension/EfiMEBx/MebxSetupBrowser/MebxSetupBrowser.mak 2     4/23/12 10:58p Klzhan $
#
# $Revision: 2 $
#
# $Date: 4/23/12 10:58p $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/BiosExtension/EfiMEBx/MebxSetupBrowser/MebxSetupBrowser.mak $
# 
# 2     4/23/12 10:58p Klzhan
# 1. Update MEBX binary
# 2. Add Elink for MEBX binary path.
# 
# 1     2/08/12 1:00a Klzhan
# Initial Check in 
# 
# 2     3/25/11 2:50a Klzhan
# Improvement : Remove un-use line.
# 
# 1     3/24/11 2:19a Klzhan
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
# Name:            MebxSetupBrowser.mak
#
# Description:     Mebx Setup Screen
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : $(BUILD_DIR)\MebxSetupBrowser.ffs

MebxSetupBrowser_INCLUDES=\
  $(EDK_SOURCE_INCLUDES)\
  $(ME_INCLUDES)\
  -I$(EDK_SOURCE)\Foundation\Efi\
  -I$(EDK_SOURCE)\Foundation\Include\
  -I$(EDK_SOURCE)\Foundation\Efi\Include\
  -I$(EDK_SOURCE)\Foundation\Framework\Include\
!IF "$(x64_BUILD)" == "1"
  -I$(EDK_SOURCE)\Foundation\Include\x64
!ELSE
  -I$(EDK_SOURCE)\Foundation\Include\ia32
!ENDIF

$(BUILD_DIR)\MebxSetupBrowser.ffs : $(EFIMebxSetup_FILE_PATH) $(MebxSetupBrowser_DIR)\$(@B).mak Core\FFS.mak
            $(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
            CPFLAGS="$(GLOBAL_DEFINES) /D TIANO_RELEASE_VERSION=0x00080006 $(EXTRA_DEFINES) $(MebxSetupBrowser_INCLUDES)" \
            BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(MebxSetupBrowser_DIR) \
            GUID=b62efbbb-3923-4cb9-a6e8-db818e828a80\
            NAME=$(@B)\
            TYPE=EFI_FV_FILETYPE_DRIVER \
            DEPEX1=$(MebxSetupBrowser_DIR)\MebxSetupBrowser.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
            PEFILE=$(EFIMebxSetup_FILE_PATH) FFSFILE=$@ COMPRESS=1 \

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