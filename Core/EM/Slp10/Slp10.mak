#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*****************************************************************************
# $Header: /Alaska/SOURCE/Modules/Slp10/Slp10.mak 2     7/14/09 12:26p Vyacheslava $
#
# $Revision: 2 $
#
# $Date: 7/14/09 12:26p $
#*****************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Slp10/Slp10.mak $
# 
# 2     7/14/09 12:26p Vyacheslava
# EIP#17468: Synopsis: customers are requesting support for SLP1.0.
# Description: Mandal, We have support for SLP2.0 but not SLP1.0. Core8
# has support for both and customers ar requesting SLP1.0 support. Please
# let us know your plans for this.
# - Removed $(BUILD_DIR)\AmiHpLibrary.lib.
# 
# 1     6/18/09 5:31p Vyacheslava
# Initial Creation
# 
#*****************************************************************************
#<AMI_FHDR_START>
#
# Name: Slp10.mak
#
# Description: Make file for Slp10 eModule.
#
#<AMI_FHDR_END>
#*****************************************************************************

all : Slp10

Slp10 : $(BUILD_DIR)\Slp10.mak $(BUILD_DIR)\OemTable.bin Slp10Bin

SLP10_OBJECTS = $(BUILD_DIR)\$(Slp10_DIR)\Slp10.obj

$(BUILD_DIR)\Slp10.mak : $(Slp10_DIR)\$(@B).cif $(Slp10_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(Slp10_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\OemTable.bin : $(Slp10_DIR)\OemTable.asm
    $(ASM) /c /Fo$(BUILD_DIR)\ $(Slp10_DIR)\OemTable.asm
    $(ASMLINK) $(BUILD_DIR)\OemTable.obj, $*.exe, $*.map,,,
    exe2bin $*.exe $@

Slp10Bin : $(AMIDXELIB) 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Slp10.mak all\
        GUID=8E477676-55FD-48cf-9210-15A99B27D740\
        OBJECTS="$(SLP10_OBJECTS)" \
        ENTRY_POINT=Slp10_EntryPoint\
        RESOURCE=$(BUILD_DIR)\OemTable.bin\
        SECTION_GUID=2EBE0275-6458-4af9-91ED-D3F4EDB100AA\
        TYPE=BS_DRIVER\
        COMPRESS=1

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
