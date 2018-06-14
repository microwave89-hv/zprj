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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/GraphicsLite/GraphicsLite.mak 1     1/20/12 4:08a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:08a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/GraphicsLite/GraphicsLite.mak $
# 
# 1     1/20/12 4:08a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:31a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:51a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	GraphicsLite.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(GRAPHICSLITE) : GraphicsLite

$(BUILD_DIR)\GraphicsLite.lib : GraphicsLite

GraphicsLite : $(BUILD_DIR)\GraphicsLite.mak GraphicsLiteBin

$(BUILD_DIR)\GraphicsLite.mak : $(GraphicsLite_DIR)\$(@B).cif $(GraphicsLite_DIR)\$(@B).mak $(BUILD_RULES) $(GraphicsLite_DIR)\Unicode\GraphicsLiteUnicode.cif
	$(CIF2MAK) $(GraphicsLite_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(GraphicsLite_DIR)\Unicode\GraphicsLiteUnicode.cif

GraphicsLiteBin : $(EFIDRIVERLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\GraphicsLite.mak all\
		"MY_INCLUDES=/I$(GraphicsLite_DIR) /I$(GraphicsLite_DIR)\Unicode"\
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