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
# $Header: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216.MAK 3     7/04/11 3:22a Kasalinyi $
#
# $Revision: 3 $
#
# $Date: 7/04/11 3:22a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/IO/Fintek/F81216_Sec/F81216.MAK $
# 
# 3     7/04/11 3:22a Kasalinyi
# [Category]  	Improvement
# [Description]  	Update to new template
# [Files]  		IO_F81216.SDL
# F81216.ASL
# F81216.MAK
# F81216.SD
# F81216.UNI
# F81216DXE.C
# F81216PEI.C
# F81216Setup.H
# F81216.CIF
# 
# 2     10/28/10 2:26a Mikes
# Clean code
# 
# 1     3/31/10 5:55a Fantasylai
# Initial release to F81216 just as a second IO
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:  <F81216.MAK>
#
# Description:     Make file to include SIO module in project
#
#
#<AMI_FHDR_END>
#*************************************************************************
{$(F81216_DIR)}.C{$(BUILD_DIR)}.OBJ::
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\\ $< 

F81216PEI_OBJ= $(BUILD_DIR)\F81216PEI.OBJ
F81216DXE_OBJ= $(BUILD_DIR)\F81216DXE.OBJ

$(F81216PEI_OBJ) : $(F81216_DIR)\F81216.MAK $(F81216_DIR)\BSP\PeiIoTable.h
$(F81216DXE_OBJ) : $(F81216_DIR)\F81216.MAK $(F81216_DIR)\BSP\DxeIoTable.h

CORE_PEIBin : $(F81216PEI_OBJ) $(AMICSPLib) 
CORE_DXEBin : $(F81216DXE_OBJ) $(AMICSPLib)

#---------------------------------------------------------------------------
#        Create SIO Setup Screen
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\F81216.MAK F81216SDB

$(BUILD_DIR)\F81216.MAK : $(F81216_DIR)\$(@B).CIF $(F81216_DIR)\$(@B).MAK $(BUILD_RULES)
    $(CIF2MAK) $(F81216_DIR)\$(@B).CIF $(CIF2MAK_DEFAULTS)

F81216SDB : $(BUILD_DIR)\F81216.mak
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\F81216.MAK all\
        TYPE=SDB NAME=F81216 STRING_CONSUMERS=$(F81216_DIR)\F81216.SD

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
