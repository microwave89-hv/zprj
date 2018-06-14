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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/GraphicsLib/GraphicsLib.mak 1     1/20/12 4:07a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:07a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/GraphicsLib/GraphicsLib.mak $
# 
# 1     1/20/12 4:07a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:31a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:49a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	GraphicsLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(GRAPHICSLIB) : GraphicsLib

$(BUILD_DIR)\GraphicsLib.lib : GraphicsLib

GraphicsLib : $(BUILD_DIR)\GraphicsLib.mak GraphicsLibBin

$(BUILD_DIR)\GraphicsLib.mak : $(GraphicsLib_DIR)\$(@B).cif $(GraphicsLib_DIR)\$(@B).mak $(BUILD_RULES) $(GraphicsLib_DIR)\Unicode\GraphicsUnicode.cif
	$(CIF2MAK) $(GraphicsLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(GraphicsLib_DIR)\Unicode\GraphicsUnicode.cif

GraphicsLibBin : $(EFIDRIVERLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\GraphicsLib.mak all\
		"MY_INCLUDES=/I$(GraphicsLib_DIR) /I$(GraphicsLib_DIR)\Unicode"\
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