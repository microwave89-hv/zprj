# MAK file for the ModulePart:SmmChildDispatcher
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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatcher.mak 1     2/08/12 8:27a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:27a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher/SmmChildDispatcher.mak $
# 
# 1     2/08/12 8:27a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         SmmChildDispatcher.mak
#
# Description:  Make file for the SMM Child Dispatcher driver.
#
#<AMI_FHDR_END>
#*************************************************************************
!IFNDEF BACKWARD_COMPATIBLE_MODE
BACKWARD_COMPATIBLE_MODE = 1
!ENDIF

all : SmmChildDispatcher

SmmChildDispatcher : $(BUILD_DIR)\SmmChildDispatcher.mak SmmChildDispatcherBin

$(BUILD_DIR)\SmmChildDispatcher.mak : $(SMM_CHILD_DISP_DIR)\SmmChildDispatcher.cif $(SMM_CHILD_DISP_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SMM_CHILD_DISP_DIR)\SmmChildDispatcher.cif $(CIF2MAK_DEFAULTS)

SmmChildDispatcherBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SmmChildDispatcher.mak all\
        "CFLAGS=$(CFLAGS) /I$(SB_BOARD_DIR)"\
        GUID=753630C9-FAE5-47a9-BBBF-88D621CD7282\
        ENTRY_POINT=SmmChildDispatchEntryPoint\
!IF $(BACKWARD_COMPATIBLE_MODE)
        TYPE=BS_DRIVER \
        DEPEX1=$(SMM_CHILD_DISP_DIR)\SmmChildDispatcher.DXS \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ELSE
        TYPE=RT_DRIVER \
        DEPEX1=$(SMM_CHILD_DISP_DIR)\SmmChildDispatcher.DXS \
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
