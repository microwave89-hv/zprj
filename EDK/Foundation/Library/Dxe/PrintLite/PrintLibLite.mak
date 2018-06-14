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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PrintLibLite/PrintLibLite.mak 1     1/20/12 4:09a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:09a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/PrintLibLite/PrintLibLite.mak $
# 
# 1     1/20/12 4:09a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:31a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:53a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PrintLibLite.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(PRINTLIBLITE) : PrintLibLite

$(BUILD_DIR)\PrintLibLite.lib : PrintLibLite

PrintLibLite : $(BUILD_DIR)\PrintLibLite.mak PrintLibLiteBin

$(BUILD_DIR)\PrintLibLite.mak : $(PrintLibLite_DIR)\$(@B).cif $(PrintLibLite_DIR)\$(@B).mak $(BUILD_RULES) $(PrintLibLite_DIR)\Unicode\PrintLiteUnicode.cif
	$(CIF2MAK) $(PrintLibLite_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(PrintLibLite_DIR)\Unicode\PrintLiteUnicode.cif

PrintLibLiteBin : $(EDKPROTOCOLLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\PrintLibLite.mak all\
		"MY_INCLUDES=/I$(PrintLibLite_DIR) /I$(PrintLibLite_DIR)\Unicode"\
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