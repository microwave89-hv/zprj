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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkPpiLib/EdkPpiLib.mak 1     1/20/12 4:04a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:04a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkPpiLib/EdkPpiLib.mak $
# 
# 1     1/20/12 4:04a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:29a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 4:02a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkPpiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EDKPPILIB) : EdkPpiLib

$(BUILD_DIR)\EdkPpiLib.lib : EdkPpiLib

EdkPpiLib : $(BUILD_DIR)\EdkPpiLib.mak EdkPpiLibBin

$(BUILD_DIR)\EdkPpiLib.mak : $(EdkPpiLib_DIR)\$(@B).cif $(EdkPpiLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkPpiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkPpiLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EdkPpiLib.mak all\
		TYPE=PEI_LIBRARY \
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