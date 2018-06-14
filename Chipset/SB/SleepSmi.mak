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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SleepSmi/SleepSmi.mak 1     2/08/12 8:30a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:30a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SleepSmi/SleepSmi.mak $
# 
# 1     2/08/12 8:30a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         SleepSmi.MAK
#
# Description:  Make file for the SMM Sleep SMI handler code
#
#<AMI_FHDR_END>
#*************************************************************************
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

all : SleepSmi

SleepSmi : $(BUILD_DIR)\SleepSmi.mak SleepSmiBin

$(BUILD_DIR)\SleepSmi.mak : $(SLEEP_SMI_DIR)\SleepSmi.cif $(SLEEP_SMI_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SLEEP_SMI_DIR)\SleepSmi.cif $(CIF2MAK_DEFAULTS)

SleepSmiBin : $(AMICSPLib) $(AMIDXELIB)
    @set INCLUDE=%%INCLUDE%%
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SleepSmi.mak all\
        GUID=6298FE18-D5EF-42b7-BB0C-2953283F5704\
        ENTRY_POINT=InitSleepSmi\
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES)" \
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A
        TYPE=BS_DRIVER \
        DEPEX1=$(SLEEP_SMI_DIR)\SleepSmi.DXS \
!ELSE
        TYPE=BS_DRIVER \
        DEPEX1=$(SLEEP_SMI_DIR)\SleepSmi.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
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
