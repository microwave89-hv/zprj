#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOption.mak 1     10/30/12 4:21a Bibbyyeh $
#
# $Revision: 1 $
#
# $Date: 10/30/12 4:21a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/PTT/FastBootOption/FastBootOption.mak $
# 
# 1     10/30/12 4:21a Bibbyyeh
# [TAG]           EIP105177
# [Category]      New Feature
# [Description]   Report pseudo boot option for Windows 'Boot To Device'
# support
# [Files]         FastBootOption.cif FastBootOption.sdl
# FastBootOption.mak FastBootOption.h FastBootOption.c
# FastBootOptionBds.c FastBootOption.dxs
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: FastBootOption.mak
#
# Description:  Make file to build FastBootOption Driver Sources.
#
#<AMI_FHDR_END>
#**********************************************************************
all : FastBootOption

FastBootOption : $(BUILD_DIR)\FastBootOption.mak FastBootOptionBin

$(BUILD_DIR)\FastBootOption.mak : $(FastBootOption_DIR)\$(@B).cif $(FastBootOption_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(FastBootOption_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

FastBootOptionBin: $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\FastBootOption.mak all\
        GUID=A58C5D1D-C22B-4845-90BC-8C94FCE96457\
        ENTRY_POINT=FastBootOptionEntryPoint \
        TYPE=BS_DRIVER \
        COMPRESS=1\
        "OBJECTS=$(BUILD_DIR)\$(FastBootOption_DIR)\FastBootOption.obj"

CORE_DXE_LIBBin : $(BUILD_DIR)\FastBootOptionBds.obj

#-----------------------------------------------------------------------
# AMICSP library files compilation
#-----------------------------------------------------------------------
{$(FastBootOption_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(FastBootOption_DIR) /I $(Foundation_DIR) /I $(CORE_DXE_DIR) /Fo$(BUILD_DIR)\ $<

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
