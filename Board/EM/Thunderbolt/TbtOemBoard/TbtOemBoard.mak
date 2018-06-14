#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemBoard.mak 1     1/10/13 4:57a Barretlin $
#
# $Revision: 1 $
#
# $Date: 1/10/13 4:57a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtOemBoard/TbtOemBoard.mak $
# 
# 1     1/10/13 4:57a Barretlin
# Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
# Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
# 
# 2     2/19/12 11:57p Wesleychen
# [TAG]         None
# [Category]    Improvement
# [Description] Add TbtOemLib.
# [Files]       TbtOemLib.c; TbtOemLib.h; TbtOemBoard,mak;
#               TbtOemBoard.cif.
# 
# 1     12/08/11 4:09a Wesleychen
# Thunderbolt eModule initially releases.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TbtOemBoard.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
All : TbtOemBoard

TbtOemBoard : $(BUILD_DIR)\TbtOemBoard.mak TbtOemBoardBin

$(BUILD_DIR)\TbtOemBoard.mak : $(TbtOemBoard_DIR)\$(@B).cif $(TbtOemBoard_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(TbtOemBoard_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TbtOemBoardBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
    /f $(BUILD_DIR)\TbtOemBoard.mak all\
    GUID=B4DE05C0-1BD0-11E1-8F0E-77F34724019B\
    ENTRY_POINT=TbtOemBoard_Init \
    "MY_INCLUDES=$(TBT_OEMBOARD_INCLUDES)"\
    TYPE=BS_DRIVER\
    DEPEX1=$(TbtOemBoard_DIR)\TbtOemBoard.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1

#----------------------------------------------------------------------------
#           Add files into CSP Library
#----------------------------------------------------------------------------
AMI_CSP_LIB_LIBRARY_PATH = $(AMI_CSP_LIB_LIBRARY_PATH);$(TbtOemBoard_DIR)

AMI_CSP_LIB_INCLUDE_FILES = "$(TbtOemBoard_DIR)\TbtOemLib.h" + \
"$(TbtOemBoard_DIR)\TbtOemBoard.h" + \
$(AMI_CSP_LIB_INCLUDE_FILES)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\TbtOemLib.obj \

{$(TbtOemBoard_DIR)}.c{$(BUILD_DIR)}.obj::
    $(CC) $(CFLAGS) /I $(TbtDxe_DIR) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\TbtOemLib.obj : $(TbtOemBoard_DIR)\TbtOemLib.c

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************