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

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/HddAcoustic/Acoustic.mak 1     1/05/11 12:22a Rameshr $
#
# $Revision: 1 $
#
# $Date: 1/05/11 12:22a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/HddAcoustic/Acoustic.mak $
# 
# 1     1/05/11 12:22a Rameshr
# Initial check-in for Hdd Acoustic Management Support.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: Acoustic.mak
#
# Description: Make file for the Acoustic Module 
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : Acoustic

Acoustic : $(BUILD_DIR)\Acoustic.mak AcousticBin

$(BUILD_DIR)\Acoustic.mak : $(ACOUSTIC_DIR)\Acoustic.cif $(ACOUSTIC_DIR)\Acoustic.mak $(BUILD_RULES)
    $(CIF2MAK) $(ACOUSTIC_DIR)\Acoustic.cif $(CIF2MAK_DEFAULTS)

Acoustic_OBJECTS = \
        $(BUILD_DIR)\$(ACOUSTIC_DIR)\Acoustic.obj\
        $(BUILD_DIR)\$(ACOUSTIC_DIR)\AcousticBoard.obj\

Acoustic_INCLUDES = \
        /I$(PROJECT_DIR)\
        /I$(SB_CHIPSET_DIR)\
        /I$(ACOUSTIC_DIR)\
        /I$(SB_BOARD_DIR)\
        

AcousticBin : $(AMIDXELIB) $(AMICSPLib) $(EFIDRIVERLIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        "MY_INCLUDES=$(Acoustic_INCLUDES)"\
        /f $(BUILD_DIR)\Acoustic.mak all\
        GUID=0639408B-19A6-4b5d-BAFB-12A2F5114032\
        ENTRY_POINT=AcousticEntryPoint\
        TYPE=BS_DRIVER \
        COMPRESS=1 HAS_RESOURCES=1\
		"OBJECTS=$(Acoustic_OBJECTS)"

#---------------------------------------------------------------------------
#       Create Acoustic Setup Screens
#---------------------------------------------------------------------------
!IF "$(LOCAL_ACOUSTIC_SETUP)"=="1"

SetupSdbs : $(BUILD_DIR)\Acoustic.mak ACOUSTICSDB
SetupBin : $(BUILD_DIR)\AcousticSetup.obj

ACOUSTICSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Acoustic.mak all\
		TYPE=SDB NAME=Acoustic MAKEFILE=$(BUILD_DIR)\Acoustic.Mak STRING_CONSUMERS=$(ACOUSTIC_DIR)\Acoustic.sd

$(BUILD_DIR)\AcousticSetup.obj : $(ACOUSTIC_DIR)\AcousticSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(ACOUSTIC_DIR)\AcousticSetup.c

!ENDIF

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
