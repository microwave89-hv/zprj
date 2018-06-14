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
# Name:         IntelSaGopSetup.mak
#
# Description:  This make file builds north bridge Setup
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************
All : IntelSaGopSetup

IntelSaGopSetup : $(BUILD_DIR)\IntelSaGopSetup.mak

$(BUILD_DIR)\IntelSaGopSetup.mak : $(IntelSaGopSetup_DIR)\$(@B).cif $(IntelSaGopSetup_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(IntelSaGopSetup_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SetupBin : $(BUILD_DIR)\IntelSaGopSetup.obj

$(BUILD_DIR)\IntelSaGopSetup.obj : $(IntelSaGopSetup_DIR)\IntelSaGopSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(IntelSaGopSetup_DIR)\IntelSaGopSetup.c

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
