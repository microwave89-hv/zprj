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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PrintLib/PrintLib.mak 1     1/20/12 4:08a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:08a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PrintLib/PrintLib.mak $
# 
# 1     1/20/12 4:08a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:31a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:52a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PrintLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(PRINTLIB) : PrintLib

$(BUILD_DIR)\PrintLib.lib : PrintLib

PrintLib : $(BUILD_DIR)\PrintLib.mak PrintLibBin

$(BUILD_DIR)\PrintLib.mak : $(PrintLib_DIR)\$(@B).cif $(PrintLib_DIR)\$(@B).mak $(BUILD_RULES) $(PrintLib_DIR)\Unicode\PrintUnicode.cif
	$(CIF2MAK) $(PrintLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(PrintLib_DIR)\Unicode\PrintUnicode.cif

PrintLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\PrintLib.mak all\
		"MY_INCLUDES=/I$(PrintLib_DIR) /I$(PrintLib_DIR)\Unicode"\
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
