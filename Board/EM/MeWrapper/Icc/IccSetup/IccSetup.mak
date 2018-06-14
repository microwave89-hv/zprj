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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccSetup.mak 1     2/08/12 1:07a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:07a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccSetup/IccSetup.mak $
# 
# 1     2/08/12 1:07a Klzhan
# Initial Check in 
# 
# 2     5/04/11 3:06a Klzhan
# EIP58767 : ICC setup items will not be hidden when load default.
# 
# 1     2/25/11 1:42a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:10a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            IccSetup.mak
#
# Description:     Makefile Setup hooks for ICC.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
All :

SetupSdbs : $(BUILD_DIR)\IccSetup.sdb

SetupBin : $(BUILD_DIR)\IccCallbacks.obj

$(BUILD_DIR)\IccSetup.mak : $(IccSetup_DIR)\$(@B).cif $(IccSetup_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IccSetup_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\IccSetup.sdb : $(BUILD_DIR)\IccSetup.mak $(IccSetup_DIR)\*.sd $(IccSetup_DIR)\*.uni
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\IccSetup.mak all\
        TYPE=SDB NAME=IccSetup

$(BUILD_DIR)\IccCallbacks.obj : $(IccSetup_DIR)\IccCallbacks.c
	$(CC) $(CFLAGS)\
		$(INTEL_MCH_INCLUDES) \
		$(INTEL_PCH_INCLUDES) \
		$(ME_INCLUDES)\
		$(ICC_INCLUDES)\
		$(NB_INCLUDES) \
		$(WDT_APP_INCLUDES) \
		/Fo$(BUILD_DIR)\ $(IccSetup_DIR)\IccCallbacks.c

#---------------------------------------------------------------------------
#		Icc SETUP load dafault hook
#---------------------------------------------------------------------------
AMITSEBin : $(BUILD_DIR)\IccLoadDefault.obj

IccLoadDefault_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)

$(BUILD_DIR)\IccLoadDefault.obj : $(IccSetup_DIR)\IccLoadDefault.c
  	$(CC) $(IccLoadDefault_CFLAGS) /Fo$(BUILD_DIR)\IccLoadDefault.obj $(IccSetup_DIR)\IccLoadDefault.c

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