#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOut.mak 5     1/22/13 4:29p Artems $
#
# $Revision: 5 $
#
# $Date: 1/22/13 4:29p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CsmOptOut/CsmOptOut.mak $
# 
# 5     1/22/13 4:29p Artems
# [TAG]  		EIP111710
# [Category]  	Improvement
# [Description]  	Replace MessageBox message and title with string tokens
# to allow
# different language usage
# [Files]  		CsmOptOut.mak CsmOptOut.uni CsmOptOutSetup.c
# 
# 4     6/20/12 6:06p Artems
# [TAG]  		EIP83692
# [Category]  	Improvement
# [Description]  	CSM OptOut setup page grayed out if secure boot is
# enabled
# CSM OptOut PlatformOverride protocol modified to fix SCT bugs
# Removed support for Launch CSM "Auto" option
# 
# [Files]  		CsmOptOut.c CsmOptOut.mak CsmOptOut.sd CsmOptOut.sdl
# CsmOptOut.uni CsmOptOutRuntime.c CsmOptOutSetup.c
# 
# 3     5/21/12 4:43p Artems
# [TAG]  		EIP86097
# [Category]  	Improvement
# [Description]  	Separate control for loading UEFI Oprom Driver
# Prevent user from disable CSM in setup if active video is legacy
# [Files]  		CsmOptOutSetup.c CsmOptOut.sdl CsmOptOut.mak 
# CsmOptOut.sdl
# 
# 2     3/16/12 5:15p Artems
# EIP 82586: CSM must not be loaded if Secure Boot is enabled
# 
# 1     11/12/11 2:57p Artems
# Initial check-in
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CsmOptOut.mak
#
# Description: Make file of the CSM OptOut module
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\CsmOptOut.obj
RUNTIMEBin : $(BUILD_DIR)\CsmOptOutRuntime.obj
SetupBin : $(BUILD_DIR)\CsmOptOutSetup.obj

CFLAGS=$(CFLAGS) /D\"OEM_CHECK_UEFI_OPROM_POLICY_LIST=$(OemCheckUefiOpromPolicyList)\"

{$(CsmOptOut_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(CsmOptOut_DIR) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\CsmOptOut.obj : $(CsmOptOut_DIR)\CsmOptOut.c
$(BUILD_DIR)\CsmOptOutRuntime.obj : $(CsmOptOut_DIR)\CsmOptOutRuntime.c
$(BUILD_DIR)\CsmOptOutSetup.obj : $(CsmOptOut_DIR)\CsmOptOutSetup.c

$(BUILD_DIR)\CsmOptOut.mak : $(CsmOptOut_DIR)\CsmOptOut.cif $(BUILD_RULES)
    $(CIF2MAK) $(CsmOptOut_DIR)\CsmOptOut.cif $(CIF2MAK_DEFAULTS)

SetupSdbs : CsmOptOutSDB

CsmOptOutSDB : $(BUILD_DIR)\CsmOptOut.mak 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\CsmOptOut.mak all\
	TYPE=SDB NAME=CsmOptOut \
    "STRING_CONSUMERS=$(CsmOptOut_DIR)\CsmOptOut.sd $(CsmOptOut_DIR)\CsmOptOutSetup.c"


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************