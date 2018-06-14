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
# $Header: /Alaska/SOURCE/Modules/FlashSmi/FlashSmi.mak 1     1/20/15 1:36a Tristinchou $
#
# $Revision: 1 $
#
# $Date: 1/20/15 1:36a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/FlashSmi/FlashSmi.mak $
# 
# 1     1/20/15 1:36a Tristinchou
# [TAG]  		EIP196554
# [Category]  	New Feature
# [Description]  	Initial check-in
# [Files]  		FlashSmi.cif
# FlashSmi.chm
# FlashSmi.sdl
# FlashSmi.mak
# FlashSmi.c
# FlashSmi.dxs
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: FlashSmi.mak 
#
# Description: Make file for FlashSmi.
#
#<AMI_FHDR_END>
#**********************************************************************

all : FlashSmi

#---------------------------------------------------------------------------
# Create FlashSmi dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\FlashSmi.mak : $(FlashSmi_DIR)\$(@B).cif $(FlashSmi_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FlashSmi_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
#---------------------------------------------------------------------------
# Create FlashSmi DXE Component
#---------------------------------------------------------------------------
FlashSmi: $(BUILD_DIR)\FlashSmi.mak FlashSmiBin

FlashSmiObjs =\
$(BUILD_DIR)\$(FlashSmi_DIR)\FlashSmi.obj

FlashSmiBin : $(AMIDXELIB) $(AMICSPLib)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\FlashSmi.mak all\
            NAME=FlashSmi\
            GUID=755877a6-4f10-4a5c-9b2e-852123b9682c\
            "CFLAGS=$(CFLAGS) /I$(FlashSmi_DIR)"\
            OBJECTS="$(FlashSmiObjs)"\
            ENTRY_POINT=FlashSmiEntry\
            TYPE=RT_DRIVER\
            DEPEX1=$(FlashSmi_DIR)\FlashSmi.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
            COMPRESS=1

#---------------------------------------------------------------------------
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