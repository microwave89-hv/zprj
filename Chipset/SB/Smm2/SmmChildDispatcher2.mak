# MAK file for the ModulePart:SmmChildDispatcher II
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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatcher2.mak 2     4/25/12 9:32a Victortu $
#
# $Revision: 2 $
#
# $Date: 4/25/12 9:32a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SmmChildDispatcher2/SmmChildDispatcher2.mak $
# 
# 2     4/25/12 9:32a Victortu
# [TAG]         None
# [Category]    Improvement
# [Description] Reprogram SMM ChildDispatcher drivers.
# [Files]       SmiHandlerGeneric.c; SmiHandlerPorting.c;
# SmiHandlerGeneric2.c; SmmChildDispatch2Main.c; SmmChildDispatcher2.mak;
# SmmChildDispatcher2.sdl; SmmChildDispatch.h; SmmChildDispatchMain.c;
# SmmChildDispatchProtocol.c; SmmChildDispatcher.dxs;
# PchSmiDispatcher.sdl
# 
# 1     2/08/12 8:28a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         SmmChildDispatcher2.mak
#
# Description:  Make file for the SMM Child Dispatcher II driver.
#
#<AMI_FHDR_END>
#*************************************************************************
!IFNDEF BACKWARD_COMPATIBLE_MODE
BACKWARD_COMPATIBLE_MODE = 1
!ENDIF

all : SmmChildDispatcher2

SmmChildDispatcher2 : $(BUILD_DIR)\SmmChildDispatcher2.mak SmmChildDispatcher2Bin

$(BUILD_DIR)\SmmChildDispatcher2.mak : $(SMM_CHILD_DISP2_DIR)\SmmChildDispatcher2.cif $(SMM_CHILD_DISP2_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SMM_CHILD_DISP2_DIR)\SmmChildDispatcher2.cif $(CIF2MAK_DEFAULTS)

SmmChildDispatcher2Bin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SmmChildDispatcher2.mak all\
        "CFLAGS=$(CFLAGS) /I$(SB_BOARD_DIR)"\
        GUID=E53734A3-E594-4c25-B1A2-081445650F7F\
        ENTRY_POINT=SmmChildDispatch2EntryPoint\
        TYPE=DXESMM_DRIVER \
        DEPEX1=$(SMM_CHILD_DISP2_DIR)\SmmChildDispatcher2.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(SMM_CHILD_DISP2_DIR)\SmmChildDispatcher2.dxs \
        DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
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
