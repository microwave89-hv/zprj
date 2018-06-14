#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Core/Modules/Recovery/RecoverySrc.mak 8     6/16/11 9:02a Felixp $
#
# $Revision: 8 $
#
# $Date: 6/16/11 9:02a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/Recovery/RecoverySrc.mak $
# 
# 8     6/16/11 9:02a Felixp
# Enhancement: Replace NAME=RECOVERY with LIBRARY_NAME=$(RECOVERYLIB) 
# to avoid temporary files with identical names in Recovery and
# RecoverySrc modules.
# 
# 7     7/01/09 4:19p Rameshr
# Coding Standard and File header updated.
# 
# 6     12/29/06 2:59p Felixp
# 
# 5     10/13/06 4:40p Felixp
# 
# 4     8/24/06 9:33a Felixp
# x64 Support: recovery.lib splitted into PEI and DXE parts
# 
# 3     12/19/05 6:36p Felixp
# 
# 2     12/02/05 11:22a Felixp
# 
# 1     12/01/05 9:45a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	RecoverySrc.mak
#
# Description: Builds the Recovery source and create the Recovery.lib
#
#<AMI_FHDR_END>
#**********************************************************************
all : RecoverySrc

$(RECOVERYLIB) : RecoverySrc

RecoverySrc : $(BUILD_DIR)\RecoverySrc.mak RecoverySrcPeiBin

$(BUILD_DIR)\RecoverySrc.mak : $(Recovery_DIR)\$(@B).cif $(Recovery_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(Recovery_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RecoverySrcPeiBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\RecoverySrc.mak all\
		MAKEFILE=$(BUILD_DIR)\RecoverySrc.mak\
		LIBRARY_NAME=$(RECOVERYLIB) TYPE=PEI_LIBRARY

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
