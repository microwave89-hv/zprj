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
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtDxe.mak 1     1/10/13 4:56a Barretlin $
#
# $Revision: 1 $
#
# $Date: 1/10/13 4:56a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Thunderbolt/TbtDxe/TbtDxe.mak $
# 
# 1     1/10/13 4:56a Barretlin
# Change SS path and update module for Thunderbolt Spec 1.6 for Cactus
# Ridge chip and Thunderbolt Spec 0.5 for Redwood Ridge chip
# 
# 2     2/20/12 12:09a Wesleychen
# [TAG]         None
# [Category]    Improvement
# [Description] Add TbtDxeLib.
# [Files]       TbtDxeLib.c; TbtDxeLib.h; TbtDxe.mak; TbtDxe.sdl;
#               TbtDxe.cif.
# 
# 1     12/08/11 4:09a Wesleychen
# Thunderbolt eModule initially releases.
# 
# 6     1/13/10 2:13p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TbtDxe.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
All : TbtDxe

CFLAGS = $(CFLAGS) /I$(TbtDxe_DIR)
#----------------------------------------------------------------------------
#           Generic TBT dependencies
#----------------------------------------------------------------------------
$(BUILD_DIR)\TbtDxe.mak : $(TbtDxe_DIR)\$(@B).cif $(TbtDxe_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(TbtDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#----------------------------------------------------------------------------
#           Add files into CSP Library
#----------------------------------------------------------------------------
AMI_CSP_LIB_LIBRARY_PATH = $(AMI_CSP_LIB_LIBRARY_PATH);$(TbtDxe_DIR)

AMI_CSP_LIB_INCLUDE_FILES = "$(TbtDxe_DIR)\TbtDxeLib.h" + \
$(AMI_CSP_LIB_INCLUDE_FILES)

AMI_CSP_LIB_OBJS = $(AMI_CSP_LIB_OBJS) \
$(BUILD_DIR)\TbtDxeLib.obj

{$(TbtDxe_DIR)}.c{$(BUILD_DIR)}.obj::
    $(CC) $(CFLAGS) /I $(TbtDxe_DIR) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\TbtDxeLib.obj : $(TbtDxe_DIR)\TbtDxeLib.c

#----------------------------------------------------------------------------
#       Create TBT DXE Component
#----------------------------------------------------------------------------
TbtDxe : $(BUILD_DIR)\TbtDxe.mak TbtDxeBin
TBT_DXE_OBJECTS =\
$$(BUILD_DIR)\$(TbtDxe_DIR)\TbtDxe.obj \

TbtDxeBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
    /f $(BUILD_DIR)\TbtDxe.mak all\
    GUID=EFB7F614-BC8B-4DDD-B09A-22079FC1512F\
    ENTRY_POINT=TbtDxe_Init \
    "MY_INCLUDES=$(TBT_OEMBOARD_INCLUDES)"\
    TYPE=BS_DRIVER\
    DEPEX1=$(TbtDxe_DIR)\TbtDxe.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1
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
