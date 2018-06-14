#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CSM/Generic/Chipset/SouthBridge/LegacyInterrupt.mak 8     1/12/10 11:51a Olegi $
#
# $Revision: 8 $
#
# $Date: 1/12/10 11:51a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CSM/Generic/Chipset/SouthBridge/LegacyInterrupt.mak $
# 
# 8     1/12/10 11:51a Olegi
# Copyright message updated.
# 
# 7     4/27/07 5:21p Olegi
# CSM.CHM preparations.
# 
# 6     12/02/05 11:44a Felixp
# 
# 5     4/04/05 4:19p Sivagarn
# Included CSP Library into the build process
# 
# 2     2/22/05 10:00a Sivagarn
# - Updated to latest labeled CSM & Core
# 
# 4     1/18/05 3:22p Felixp
# PrintDebugMessage renamed to Trace
# 
# 3     12/24/04 3:42p Felixp
# 
# 2     11/30/04 4:22p Felixp
# Updated in accordance with the latest build process
# 
# 1     10/26/04 9:48a Olegi
# 
# 1     8/25/04 3:01p Markw
# 
# 1     8/13/04 2:39p Markw
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: LegacyInterrupt
#
# Description:	Legacy Interrupt make file
#
#<AMI_FHDR_END>
#**********************************************************************
all : LegacyInterrupt

LegacyInterrupt : $(BUILD_DIR)\LegacyInterrupt.mak LegacyInterruptBin

$(BUILD_DIR)\LegacyInterrupt.mak : $(LEGACY_INTERRUPT_DIR)\$(@B).cif $(LEGACY_INTERRUPT_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(LEGACY_INTERRUPT_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

LegacyInterruptBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\LegacyInterrupt.mak all\
		GUID=71ED12D1-250B-42fb-8C17-10DCFA771701\
		ENTRY_POINT=InitializeLegacyInterrupt\
		TYPE=BS_DRIVER\
		COMPRESS=1

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
