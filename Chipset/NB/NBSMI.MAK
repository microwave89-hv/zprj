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
# $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB SMI/NBSMI.MAK 1     2/08/12 4:35a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 4:35a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/NB SMI/NBSMI.MAK $
# 
# 1     2/08/12 4:35a Yurenlai
# Intel Haswell/NB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         NBSMI.MAK
#
# Description:  Make file for the NB SMI handler code
#
#<AMI_FHDR_END>
#*************************************************************************

all : NBSMI

NBSMI: $(BUILD_DIR)\NBSMI.mak NBSMIBin

$(BUILD_DIR)\NBSMI.mak : $(NB_SMI_PATH)\NBSMI.cif $(NB_SMI_PATH)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(NB_SMI_PATH)\NBSMI.cif $(CIF2MAK_DEFAULTS)

NB_SMI_OBJECTS = $(BUILD_NB_CHIPSET_DIR)\NBSMI.obj \
$(BUILD_NB_BOARD_DIR)\GetSetupData.obj

NBSMIBin : $(AMIDXELIB) $(AMICSPLib)
    @set INCLUDE=%%INCLUDE%%
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\NBSMI.mak all\
        "CFLAGS=$(CFLAGS) /I$(NB_BOARD_DIR) /I$(SB_BOARD_DIR) /I$(SB_CHIPSET_DIR)"\
        OBJECTS="$(NB_SMI_OBJECTS)" \
        GUID=D933DEDE-0260-4e76-A7D9-2F9F2440E5A5\
        ENTRY_POINT=InitializeNBSmm\
        TYPE=BS_DRIVER \
        COMPRESS=1

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
