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

#*************************************************************************
#<AMI_FHDR_START>
#
# Name: AcpiProtocolLib.mak
#
# Description:
# 
#<AMI_FHDR_END>
#*************************************************************************
all : AcpiProtocolLib

$(AcpiProtocolLib_LIB) : AcpiProtocolLib

AcpiProtocolLib : $(BUILD_DIR)\AcpiProtocolLib.mak AcpiProtocolLibBin

$(BUILD_DIR)\AcpiProtocolLib.mak : $(AcpiProtocolLib_DIR)\$(@B).cif $(AcpiProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(AcpiProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
    
AcpiProtocolLib_INCLUDES =\
    $(EDK_INCLUDES) \
    $(EdkIIGlueLib_INCLUDES)

AcpiProtocolLibBin : 
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
        /f $(BUILD_DIR)\AcpiProtocolLib.mak all\
    "MY_INCLUDES=$(AcpiProtocolLib_INCLUDES)" \
        TYPE=LIBRARY

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
