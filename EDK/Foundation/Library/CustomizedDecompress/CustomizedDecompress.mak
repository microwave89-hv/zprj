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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CustomizedDecompress/CustomizedDecompress.mak 1     1/20/12 3:59a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/CustomizedDecompress/CustomizedDecompress.mak $
# 
# 1     1/20/12 3:59a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:22a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:26a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CustomizedDecompress.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(CUSTOMIZEDDECOMPRESS) : CustomizedDecompress

$(BUILD_DIR)\CustomizedDecompress.lib : CustomizedDecompress

CustomizedDecompress : $(BUILD_DIR)\CustomizedDecompress.mak CustomizedDecompressBin

$(BUILD_DIR)\CustomizedDecompress.mak : $(CustomizedDecompress_DIR)\$(@B).cif $(CustomizedDecompress_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CustomizedDecompress_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CustomizedDecompressBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\CustomizedDecompress.mak all\
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