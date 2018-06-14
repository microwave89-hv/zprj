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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtLockKBD/AmtLockKBD.mak 1     2/08/12 1:10a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:10a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtLockKBD/AmtLockKBD.mak $
# 
# 1     2/08/12 1:10a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:45a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:11a Klzhan
# Initial Check-in.
#
#**********************************************************************

#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:		AMTLockKBD.mak
#
# Description:	AMT Lock KeyBoard.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>
all : AMTLOCKKBD $(BUILD_DIR)\AmtInt9.obj

AMT_LOCKKBD_BUILD_DIR = $(BUILD_DIR)\$(AmtLockKBD_DIR)

#---------------------------------------------------------------------------
#           Generic AMT dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\AmtLockKBD.mak : $(AmtLockKBD_DIR)\AmtLockKBD.cif $(BUILD_RULES)
    $(CIF2MAK) $(AmtLockKBD_DIR)\AmtLockKBD.cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\AmtInt9.obj: $(AmtLockKBD_DIR)\AmtInt9.asm
    $(ASM16) /c /nologo /Fo$(BUILD_DIR)\ $(AmtLockKBD_DIR)\AmtInt9.asm

#---------------------------------------------------------------------------

AMT_LOCKKBD_OBJECTS = \
$(BUILD_DIR)\$(AmtLockKBD_DIR)\AmtLockKBD.obj

#---------------------------------------------------------------------------
#       Create ASF Verbosity DXE Component
#---------------------------------------------------------------------------
AMTLOCKKBD: $(BUILD_DIR)\AmtLockKBD.mak AMTLOCKKBDBin

AMTLOCKKBDBin : $(AMIDXELIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\AmtLockKBD.mak all\
            MAKEFILE=$(BUILD_DIR)\AmtLockKBD.mak \
            OBJECTS="$(AMT_LOCKKBD_OBJECTS)" \
            GUID=5507247A-846B-4f22-B55F-72B4049435EF \
            ENTRY_POINT=AMTLOCKKBDEntryPoint \
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