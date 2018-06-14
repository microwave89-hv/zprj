#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/HddPassword.mak 5     4/25/13 9:29a Kapilporwal $
#
# $Revision: 5 $
#
# $Date: 4/25/13 9:29a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/HddSecurity/HddPassword/HddPassword.mak $
# 
# 5     4/25/13 9:29a Kapilporwal
# [TAG]  		EIP108583
# [Category]  	New Feature
# [Description]  	support set HDD password in same page
# [Files]  		IdeSecurity.cif, IdeSecurity.mak, IdeSecurity.sdl,
# IdeSecurity.uni, IdeSecurityCommon.sd, IdeSecuritySetup.c,
# HddPassword.c, HddPassword.h, HddPassword.mak, HddPassword.sdl
# 
# 4     8/19/10 2:46a Rameshr
# Issue:Need do HDD PSW reset when warmboot
# EIP 40528
# 
# 3     6/30/10 4:15a Rameshr
# Modified the Hddpassword build procedure, so that customer can add
# their password oem files and build without modifying the Mak file
# 
# 2     3/11/10 3:50a Rameshr
# Issue: Same Structure definied in Hddpassword and Amitse.
# Solution: Amitse created tsecommon.h with all the common definition.
# EIP: 27339
# 
# 1     5/01/09 11:09a Rameshr
# Initial Check-in
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	HddPassword.mak
#
# Description: Make file for the Hddpassword.obj
#
#<AMI_FHDR_END>
#**********************************************************************
EDK_TSE_INCLUDES = \
	-I EDK\MiniSetup\TseLite \
	-I EDK\MiniSetup\Ezport \
	-I EDK\MiniSetup\BootOnly \
	-I EDK\MiniSetup\BootOnly\AMILogo \
	-I EDK\MiniSetup\uefi2.1 \
	/DTSE_FOR_APTIO_4_50

AMITSEBin :  $(BUILD_DIR)\HddPassword.obj $(BUILD_DIR)\ForceHddPassword.obj

{$(AMITSE_HDD_PASSWORD_DIR)}.c{$(BUILD_DIR)}.obj ::
	$(CC) $(CFLAGS) $(EDK_TSE_INCLUDES) -I $(TSEBIN_DIR)\Inc -I $(TSEBIN_DIR) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\HddPassword.mak : $(AMITSE_HDD_PASSWORD_DIR)\$(@B).cif $(AMITSE_HDD_PASSWORD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMITSE_HDD_PASSWORD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AMITSESDB : HddPassWordSDB

HddPassWordSDB : $(BUILD_DIR)\HddPassword.mak
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\HddPassword.mak all\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		"STRING_CONSUMERS=$(AMITSE_HDD_PASSWORD_DIR)\HddSecTokens.c"\
		TYPE=SDB NAME=HddPassword
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
