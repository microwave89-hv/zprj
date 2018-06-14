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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPlatformSetupPolicy/TcgPlatformSetupPolicy.mak 1     4/21/14 2:18p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:18p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPlatformSetupPolicy/TcgPlatformSetupPolicy.mak $
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
# 2     9/29/11 1:55a Fredericko
# 
# 1     9/27/11 10:11p Fredericko
# [TAG]  		EIP67286
# [Category]  	Improvement
# [Description]  	Initial check-in for Tcg Setup policy for Dxe
# [Files]  		TcgPlatformSetupPolicy.cif
# TcgPlatformSetupPolicy.c
# TcgPlatformSetupPolicy.h
# TcgPlatformSetupPolicy.sdl
# TcgPlatformSetupPolicy.mak
# TcgPlatformSetupPolicy.dxs
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	TcgPlatformpolicy.mak   
#
# Description:	Make file for TcgPlatformpolicy
#
#<AMI_FHDR_END>
#**********************************************************************
All : TcgPlatformSetupPolicy

TcgPlatformSetupPolicy : $(BUILD_DIR)\TcgPlatformSetupPolicy.mak TcgPlatformSetupPolicyBin

$(BUILD_DIR)\TcgPlatformSetupPolicy.mak : $(TcgPlatformSetupPolicy_DIR)\$(@B).cif $(TcgPlatformSetupPolicy_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TcgPlatformSetupPolicy_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TcgPlatformSetupPolicyBin :  $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgPlatformSetupPolicy.mak all\
		GUID=196CA3D8-9A5A-4735-B328-8FFC1D93D188\
		ENTRY_POINT=TcgPlatformSetupPolicyEntryPoint\
		DEPEX1=$(TcgPlatformSetupPolicy_DIR)\TcgPlatformSetupPolicy.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
		TYPE=BS_DRIVER\
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
