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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/PttWrapper/PttWrapper.mak 1     11/07/12 6:21a Klzhan $
#
# $Revision: 1 $
#
# $Date: 11/07/12 6:21a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/PttWrapper/PttWrapper.mak $
# 
# 1     11/07/12 6:21a Klzhan
# 
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PttWrapper.mak
#
# Description:
#
#<AMI_FHDR_END>
#**********************************************************************

all : PttWrapper

PttWrapper : $(BUILD_DIR)\PttWrapper.mak PttWrapperBin

$(BUILD_DIR)\PttWrapper.mak : $(PttWrapper_DIR)\$(@B).cif $(PttWrapper_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(PttWrapper_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PttWrapperBin : $(AMIDXELIB) 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
    /f $(BUILD_DIR)\PttWrapper.mak all\
    GUID=b19ef33c-10a6-4066-9217-8e5ee011a52f\
    ENTRY_POINT=PttWrapperEntryPoint\
    TYPE=BS_DRIVER \
    COMPRESS=1

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