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
#
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetup.mak 3     3/01/13 3:11a Klzhan $
#
# $Revision: 3 $
#
# $Date: 3/01/13 3:11a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MeSetup/MeSetup.mak $
# 
# 3     3/01/13 3:11a Klzhan
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Fix ICBO project build error.
# [Files]  		MeSetup.sdl
# MeSetup.mak
# MeSetup.sd
# MeSetup.uni
# MeSetup.c
# MeSetup.h
# MebxPrompt.c
# MeSetupReset.c
# MeSetup.cif
# 
# 2     2/07/13 3:24a Klzhan
# 
# 1     2/08/12 1:04a Klzhan
# Initial Check in 
# 
# 6     9/06/11 3:51a Klzhan
# Read key by RegisterKeyNofity.
# 
# 5     6/28/11 2:41a Klzhan
# Fix build error when iAMT_Support is off.
# 
# 4     6/20/11 8:17a Klzhan
# Not Show Remote Assistance message when SOL and KVM.
# 
# 3     6/20/11 4:18a Klzhan
# Support Remote assistance hot key detect.
# 
# 2     5/23/11 8:42a Klzhan
# Support CTRL + P check.
# 
# 1     2/25/11 1:41a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:09a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            Me Setup.mak
#
# Description:     Makfile for ME Setup module.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
All : MeSetup

MeSetup : $(BUILD_DIR)\MeSetup.mak

SetupSdbs : $(BUILD_DIR)\MeSetup.sdb

$(BUILD_DIR)\MeSetup.sdb : $(ME_SETUP_DIR)\$(@B).sd $(ME_SETUP_DIR)\$(@B).uni
        $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(ME_SETUP_DIR)\$(@B).uni
        $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(ME_SETUP_DIR)\$(@B).sd

$(BUILD_DIR)\MeSetup.mak : $(ME_SETUP_DIR)\$(@B).cif $(ME_SETUP_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(ME_SETUP_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SetupBin : $(BUILD_DIR)\MeSetup.obj

$(BUILD_DIR)\MeSetup.obj : $(PROJECT_DIR)\$(ME_SETUP_DIR)\MeSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(ME_SETUP_DIR)\MeSetup.c

!IF DEFINED(IntelPTT_SUPPORT) && "$(IntelPTT_SUPPORT)" == "1"
SetupData :  $(BUILD_DIR)\MebxPrompt.obj $(BUILD_DIR)\MeSetupReset.obj
!ELSE
SetupData :  $(BUILD_DIR)\MebxPrompt.obj
!ENDIF

MebxPrompt_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)\
	-I ReferenceCode\ME\Protocol\
!IF DEFINED(AmtWrapper_SUPPORT) && "$(AmtWrapper_SUPPORT)" == "1"
	-I $(AmtWrapperProtocolLib_DIR)\
!ENDIF
	-I $(MeGuidLib_DIR)\
        $(ME_INCLUDES)

$(BUILD_DIR)\MebxPrompt.obj : $(ME_SETUP_DIR)\MebxPrompt.c
		$(CC) $(MebxPrompt_CFLAGS) /Fo$(BUILD_DIR)\ $(ME_SETUP_DIR)\MebxPrompt.c 

$(BUILD_DIR)\MeSetupReset.obj : $(ME_SETUP_DIR)\MeSetupReset.c
		$(CC) $(MebxPrompt_CFLAGS) /Fo$(BUILD_DIR)\ $(ME_SETUP_DIR)\MeSetupReset.c 
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
