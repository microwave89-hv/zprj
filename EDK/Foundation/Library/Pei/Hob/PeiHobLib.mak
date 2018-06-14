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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PeiHobLib/PeiHobLib.mak 1     1/20/12 4:10a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:10a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PeiHobLib/PeiHobLib.mak $
# 
# 1     1/20/12 4:10a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:32a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:57a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PeiHobLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(PEIHOBLIB) : PeiHobLib

$(BUILD_DIR)\PeiHobLib.lib : PeiHobLib

PeiHobLib : $(BUILD_DIR)\PeiHobLib.mak PeiHobLibBin

$(BUILD_DIR)\PeiHobLib.mak : $(PeiHobLib_DIR)\$(@B).cif $(PeiHobLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(PeiHobLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

PeiHobLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\PeiHobLib.mak all\
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