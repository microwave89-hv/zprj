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
# $Header: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/AmiTcmlib/AmiTcmlib.mak 1     4/21/14 2:15p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:15p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Libraries/TisLib/AmiTcmlib/AmiTcmlib.mak $
# 
# 1     4/21/14 2:15p Fredericko
# 
# 1     10/08/13 11:59a Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:50p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 7     3/29/11 12:51p Fredericko
# 
# 6     3/29/11 11:52a Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
#
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:		AmiTcmlib.mak
#
# Description:	Make file for AmiTcmlib
#
#<AMI_FHDR_END>
#************************************************************************
all : $(BUILD_DIR)\AmiTcmlib.lib

#---------------------------------------------------------------------------
#			$(BUILD_DIR)\AmiTcgLibDxe.lib
#---------------------------------------------------------------------------
$(BUILD_DIR)\AmiTcmlib.lib : $(BUILD_DIR)\AmiTcmlib.mak  MakeAmiTcmlib

$(BUILD_DIR)\AmiTcmlib.mak : $(AMI_TCM_LIB)\AmiTcmlib.cif $(AMI_TCM_LIB)\AmiTcmlib.mak $(BUILD_RULES)
	$(CIF2MAK) $(AMI_TCM_LIB)\AmiTcmlib.cif $(CIF2MAK_DEFAULTS)

MakeAmiTcmlib: 
!IF "$(PROCESSOR)"=="x64"
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTcmlib.mak all\
		TYPE=LIBRARY
		$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\AmiTcmlib.mak all\
		TYPE=PEI_LIBRARY
!ELSE
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTcmlib.mak all\
		TYPE=LIBRARY
!ENDIF

#---------------------------------------------------------------------------

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
