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

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPlatformSetupPeiPolicy/TcgPlatformSetupPeiPolicy.mak 1     4/21/14 2:18p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:18p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPlatformSetupPeiPolicy/TcgPlatformSetupPeiPolicy.mak $
# 
# 1     4/21/14 2:18p Fredericko
# 
# 1     10/08/13 12:05p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:56p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 4     10/07/11 11:54a Fredericko
# 
# 1     9/27/11 10:10p Fredericko
# [TAG]  		EIP67286
# [Category]  	Improvement
# [Description]  	Initial check-in for Tcg Setup policy for pei
# [Files]  		TcgPlatformSetupPeiPolicy.cif
# TcgPlatformSetupPeiPolicy.c
# TcgPlatformSetupPeiPolicy.h
# TcgPlatformSetupPeiPolicy.sdl
# TcgPlatformSetupPeiPolicy.mak
# TcgPlatformSetupPeiPolicy.dxs
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TcgPlatformpeipolicy.mak
#
# Description:	Make file for TcgPlatformpeipolicy
#
#<AMI_FHDR_END>
#**********************************************************************
All : TcgPlatformSetupPeiPolicy

TcgPlatformSetupPeiPolicy : $(BUILD_DIR)\TcgPlatformSetupPeiPolicy.mak TcgPlatformSetupPeiPolicyBin

$(BUILD_DIR)\TcgPlatformSetupPeiPolicy.mak : $(TcgPlatformSetupPeiPolicy_DIR)\$(@B).cif $(TcgPlatformSetupPeiPolicy_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TcgPlatformSetupPeiPolicy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TcgPlatformSetupPeiPolicyBin :  $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgPlatformSetupPeiPolicy.mak all\
		GUID=0FE9DA53-043D-4265-A94D-FD77FEDE2EB4\
		ENTRY_POINT=TcgPlatformSetupPeiPolicyEntryPoint\
		DEPEX1=$(TcgPlatformSetupPeiPolicy_DIR)\TcgPlatformSetupPeiPolicy.dxs\
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX\
		TYPE=PEIM\
		COMPRESS=0

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
