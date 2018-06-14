#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/MEUD.mak 9     5/09/11 3:24a Klzhan $
#
# $Revision: 9 $
#
# $Date: 5/09/11 3:24a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/MEUD.mak $
# 
# 9     5/09/11 3:24a Klzhan
# Add Setup Item in Advanced Page to select regions to update.
# 
# 8     4/22/11 2:29a Klzhan
# Remove the code related to ME AUTO UPDATE.
# 
# 7     12/27/10 4:38a Klzhan
# Improvement : ME auto update.
# 
# 6     11/09/10 10:26p Klzhan
# Fix Build warming.
# 
# 5     10/30/09 6:40a Klzhan
# BugFix : Fix compile Fail.
# 
# 4     10/20/09 3:43a Klzhan
# Improvement : Replace TSE2.0 callback by formset callback.
# 
# 3     10/13/09 6:13a Klzhan
# Improvement : Add a token for ME SECOVR setup item.
# 
# 2     10/13/09 3:32a Klzhan
# 1. Support TSE2.0 Exit page callback for ME update(SECOVR_MEI_MSG
# mode).
# 
# 1     9/30/09 11:15p Lawrencechang
# Move Intel ME update module part to an independent SS path.
# 
# 2     7/02/09 8:25a Klzhan
# 
# 1     4/13/09 5:47a Lawrencechang
# Initial check-in.
# 
# 1     3/18/07 5:23p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	MEUD.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : MEUD

MEUD : $(BUILD_DIR)\MEUD.mak MEUDBin

$(BUILD_DIR)\MEUD.mak : $(OFBD_MEUD_DIR)\$(@B).cif $(OFBD_MEUD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(OFBD_MEUD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MEUDBin : $(FLASHLIB)
        @set INCLUDE=%%INCLUDE%%
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\MEUD.mak all\
        NAME=MEUD \
        TYPE=LIBRARY LIBRARY_NAME=$(MEUDLIB)

$(MEUDLIB) : MEUD 

#---------------------------------------------------------------------------
# Compile Password customization file
#---------------------------------------------------------------------------
MEUDMSG_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)\

AMITSE.mak : $(BUILD_DIR)\$(OFBD_MEUD_DIR)\MEUD_MSG.obj

$(BUILD_DIR)\$(OFBD_MEUD_DIR)\MEUD_MSG.obj : $(OFBD_MEUD_DIR)\MEUD_MSG.c
	$(CC) $(MEUDMSG_CFLAGS) $(ME_INCLUDES) /Fo$@ $**
#----------------------------------------------------------------------------
#       Create ME Setup Screens
#----------------------------------------------------------------------------
SetupSdbs : $(MELIB) $(BUILD_DIR)\MEUD.mak MEUDSDB
SetupBin : $(BUILD_DIR)\InitMEUDString.obj

MEUDSDB :
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\MEUD.mak all\
        TYPE=SDB NAME=MEUD STRING_CONSUMERS=$(OFBD_MEUD_DIR)\MEUD.sd

$(BUILD_DIR)\InitMEUDString.obj : $(PROJECT_DIR)\$(OFBD_MEUD_DIR)\InitMEUDString.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(PROJECT_DIR)\$(OFBD_MEUD_DIR)\InitMEUDString.c

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
