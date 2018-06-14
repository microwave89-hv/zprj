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

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/OemActivation/SmmOemActivation.mak 1     1/12/12 9:36a Vyacheslava $
#
# $Revision: 1 $
#
# $Date: 1/12/12 9:36a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OemActivation/SmmOemActivation.mak $
# 
# 1     1/12/12 9:36a Vyacheslava
# Separated to the module part. 
# 
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SmmOemActivation.mak
#
# Description: Make file for SmmOemActivation module.
#
#<AMI_FHDR_END>
#*************************************************************************

all : SmmOemActivation

SmmOemActivation : $(BUILD_DIR)\SmmOemActivation.mak SmmOemActivationBin

$(BUILD_DIR)\SmmOemActivation.mak : $(OemActivation_DIR)\$(@B).cif $(OemActivation_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(OemActivation_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmmOemActivationBin : $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SmmOemActivation.mak all\
        GUID=8434DA1F-5CEB-402e-A93C-038CBE0F3F0E\
        ENTRY_POINT=SmmOemActivation_EntryPoint\
!IF $(PI_SPECIFICATION_VERSION)<0x00001000A
        TYPE=BS_DRIVER\
!ELSE
        TYPE=SMM_DRIVER\
!ENDIF
        DEPEX1=$(OemActivation_DIR)\SmmOemActivation.dxs\
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX\
        "EXT_HEADERS=$(BUILD_DIR)\Token.h"\
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
