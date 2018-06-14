#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/ArchProtocolLib/ArchProtocolLib.mak 1     1/20/12 4:12a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:12a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/ArchProtocolLib/ArchProtocolLib.mak $
# 
# 1     1/20/12 4:12a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:34a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:06a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	ArchProtocolLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(ARCHPROTOCOLLIB) : ArchProtocolLib

$(BUILD_DIR)\ArchProtocolLib.lib : ArchProtocolLib

ArchProtocolLib : $(BUILD_DIR)\ArchProtocolLib.mak ArchProtocolLibBin

$(BUILD_DIR)\ArchProtocolLib.mak : $(ArchProtocolLib_DIR)\$(@B).cif $(ArchProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(ArchProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

ArchProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\ArchProtocolLib.mak all\
		TYPE=LIBRARY \
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************