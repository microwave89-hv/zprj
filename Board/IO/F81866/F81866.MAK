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
#
#*************************************************************************
# $Header: /Alaska/BIN/IO/Fintek/F81866/F81866.MAK 2     12/14/11 9:21p Kasalinyi $
#
# $Revision: 2 $
#
# $Date: 12/14/11 9:21p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/IO/Fintek/F81866/F81866.MAK $
# 
# 2     12/14/11 9:21p Kasalinyi
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Fix Smart Function build error
# [Files]  		F81866DXE.C
# F81866.SD
# F81866.MAK
# IO_F81866.SDL
# 
# 1     7/20/11 4:22a Kasalinyi
# [Category]  	Improvement
# [Description]  	Initial Porting 
# [Files]  		F81866.CIF
# IO_F81866.SDL
# F81866.ASL
# F81866.MAK
# F81866.SD
# F81866.UNI
# F81866DXE.C
# F81866PEI.C
# F81866PeiDebugger.C
# F81866Setup.C
# F81866Setup.H
# History.txt
# F81866.chm
# 
# 6     3/21/11 9:41p Mikes
# seperate the core and oem job
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:  <F81866.MAK>
#
# Description:     SIO module component make file
#
#<AMI_FHDR_END>
#*************************************************************************
{$(F81866_DIR)}.C{$(BUILD_DIR)}.OBJ::
    $(CC) $(CFLAGS) /D\"SIO_IoRange_Decode_LIST=$(IoRangeDecodeList)\" /Fo$(BUILD_DIR)\\ $< 

!IF "$(IODECODETYPE)"=="1"
$(BUILD_DIR)\DxeOemIoDecode.OBJ : $(F81866_DIR)\BSP\OemIoDecode.c
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\DxeOemIoDecode.OBJ $(F81866_DIR)\BSP\OemIoDecode.c

$(BUILD_DIR)\PeiOemIoDecode.OBJ : $(F81866_DIR)\BSP\OemIoDecode.c
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\PeiOemIoDecode.OBJ $(F81866_DIR)\BSP\OemIoDecode.c

F81866PEI_OBJ= $(BUILD_DIR)\F81866PEI.OBJ \
$(BUILD_DIR)\PeiOemIoDecode.OBJ

F81866DXE_OBJ= $(BUILD_DIR)\F81866DXE.OBJ \
$(BUILD_DIR)\DxeOemIoDecode.OBJ

!ELSE

F81866PEI_OBJ= $(BUILD_DIR)\F81866PEI.OBJ
F81866DXE_OBJ= $(BUILD_DIR)\F81866DXE.OBJ
!ENDIF

$(F81866PEI_OBJ) : $(F81866_DIR)\F81866.MAK $(F81866_DIR)\BSP\PeiIoTable.h
$(F81866DXE_OBJ) : $(F81866_DIR)\F81866.MAK $(F81866_DIR)\BSP\DxeIoTable.h

!IF "$(F81866_SMF_SUPPORT)"=="1"
$(BUILD_DIR)\F81866SmartFan.OBJ : $(F81866_DIR)\BSP\F81866SmartFan.c
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\F81866SmartFan.OBJ $(F81866_DIR)\BSP\F81866SmartFan.c
!ENDIF

CORE_PEIBin : $(F81866PEI_OBJ) $(AMICSPLib)

!IF "$(F81866_SMF_SUPPORT)" == "1"
CORE_DXEBin : $(BUILD_DIR)\F81866SmartFan.OBJ $(F81866DXE_OBJ) $(AMICSPLib) \
!ELSE
CORE_DXEBin : $(F81866DXE_OBJ) $(AMICSPLib) 
!ENDIF

#--------------------------------------------------------------------------
#        Create SIO Setup Screen
#--------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\F81866.MAK F81866SDB

$(BUILD_DIR)\F81866.MAK : $(F81866_DIR)\$(@B).CIF $(F81866_DIR)\$(@B).MAK $(BUILD_RULES)
    $(CIF2MAK) $(F81866_DIR)\$(@B).CIF $(CIF2MAK_DEFAULTS)

F81866SDB : $(BUILD_DIR)\F81866.mak
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\F81866.MAK all\
        TYPE=SDB NAME=F81866 STRING_CONSUMERS=$(F81866_DIR)\F81866.SD

all : Build_SetupStringList

SetupBin : $(BUILD_DIR)\F81866Setup.OBJ \
!IF "$(F81866_HWM_PRESENT)" == "1"
$(BUILD_DIR)\F81866HwmOemHooks.OBJ
!ENDIF

Build_SetupStringList :
    $(ECHO) #define STR_TABLE_LIST $(SetupStrTableList) > $(BUILD_DIR)\SetupStringList.h


$(BUILD_DIR)\F81866Setup.OBJ : $(F81866_DIR)\F81866Setup.C $(BUILD_DIR)\SetupStrTokens.H
    $(CC) $(CFLAGS) /D\"HWM_External_Fun_LIST=$(HwmExtFunList)\" \
                    /Fo$(BUILD_DIR)\ $(F81866_DIR)\F81866Setup.C

!IF "$(F81866_HWM_PRESENT)" == "1"
$(BUILD_DIR)\F81866HwmOemHooks.OBJ : $(F81866_DIR)\BSP\F81866HwmOemHooks.c
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(F81866_DIR)\BSP\F81866HwmOemHooks.c
!ENDIF

#--------------------------------------------------------------------------
#        SB Debugger Initialization
#--------------------------------------------------------------------------
PEI_F81866_DBG_FLAGS = $(CFLAGS) \
!IF "$(USB_DEBUG_TRANSPORT)" == "1"
    /DUSB_DEBUGGER
!ENDIF

$(BUILD_DIR)\F81866PeiDebugger.OBJ : $(PROJECT_DIR)\$(F81866_DIR)\F81866PeiDebugger.C
    $(CC) $(PEI_F81866_DBG_FLAGS) /Fo$(BUILD_DIR)\F81866PeiDebugger.OBJ $(PROJECT_DIR)\$(F81866_DIR)\F81866PeiDebugger.C

PeiDbgPortBin : $(BUILD_DIR)\F81866PeiDebugger.OBJ $(F81866PEI_OBJ)

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

