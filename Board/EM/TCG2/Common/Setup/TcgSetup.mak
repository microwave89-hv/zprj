#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgSetup/TcgSetup.mak 1     4/21/14 2:18p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:18p $
#**********************************************************************
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgSetup/TcgSetup.mak $
# 
# 1     4/21/14 2:18p Fredericko
# 
# 1     10/08/13 12:05p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:57p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 5     11/22/11 6:44p Fredericko
# [TAG]  		EIP67286
# [Category]  	Improvement
# [Description]  	Separate out how load defaults are handled in setup
# from the TpmPwd.c
# [Files]  		1. HandleLoadDefaultsSetup.c
# 2. TcgSetup.cif
# 3. TcgSetup.mak
# 4. TpmPwd.c
# 
# 4     10/07/11 6:54p Fredericko
# 
# 3     8/26/11 3:23p Fredericko
# 
# 2     3/29/11 1:23p Fredericko
# 
# 1     3/28/11 2:57p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
# 
# 19    5/19/10 6:20p Fredericko
# Updated AMI copyright header
# Included File Header
# EIP 37653
# 
#*************************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		TcgSetup.mak
#
# Description:	Make file for the OEM-specific sub-component of TCG
#
#<AMI_FHDR_END>
#**********************************************************************
all: 

$(BUILD_DIR)\TcgSetup.mak : $(TCG_SETUP_DIR)\$(@B).cif $(TCG_SETUP_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TCG_SETUP_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TPMTSE_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)\
    /I$(TcgPlatformSetupPolicy_DIR)\

!IF $(TPM_PASSWORD_AUTHENTICATION)
#---------------------------------------------------------------------------
# Compile Password customization file
#---------------------------------------------------------------------------
AMITSEBin : $(BUILD_DIR)\$(TCG_SETUP_DIR)\TPMPwd.obj

$(BUILD_DIR)\$(TCG_SETUP_DIR)\TPMPwd.obj : $(TCG_SETUP_DIR)\TPMPwd.obj
	$(CC) $(TPMTSE_CFLAGS) /Fo$(BUILD_DIR)\$(TCG_SETUP_DIR)\TPMPwd.obj $(TCG_SETUP_DIR)\TPMPwd.c
#---------------------------------------------------------------------------
!ENDIF

AMITSEBin : $(BUILD_DIR)\$(TCG_SETUP_DIR)\HandleLoadDefaultsSetup.obj

$(BUILD_DIR)\$(TCG_SETUP_DIR)\HandleLoadDefaultsSetup.obj : $(TCG_SETUP_DIR)\HandleLoadDefaultsSetup.obj
	$(CC) $(TPMTSE_CFLAGS) /Fo$(BUILD_DIR)\$(TCG_SETUP_DIR)\HandleLoadDefaultsSetup.obj $(TCG_SETUP_DIR)\HandleLoadDefaultsSetup.c

#---------------------------------------------------------------------------
#		Create TCG Setup Screens
#---------------------------------------------------------------------------
SetupSdbs :$(BUILD_DIR)\TcgSetup.mak  TCGSDB

TCGSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgSetup.mak  all\
		TYPE=SDB NAME=TcgSetup STRING_CONSUMERS=$(TCG_SETUP_DIR)\TcgSetup.sd
#---------------------------------------------------------------------------

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
