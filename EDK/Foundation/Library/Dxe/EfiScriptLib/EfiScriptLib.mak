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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiScriptLib/EfiScriptLib.mak 1     1/20/12 4:12a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:12a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiScriptLib/EfiScriptLib.mak $
# 
# 1     1/20/12 4:12a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:35a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:46a Iminglin
# EIP24919
# 
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiScriptLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EFISCRIPTLIB) : EfiScriptLib

$(BUILD_DIR)\EfiScriptLib.lib : EfiScriptLib

EfiScriptLib : $(BUILD_DIR)\EfiScriptLib.mak EfiScriptLibBin

$(BUILD_DIR)\EfiScriptLib.mak : $(EfiScriptLib_DIR)\$(@B).cif $(EfiScriptLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiScriptLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiScriptLibBin : $(EDKFRAMEWORKPROTOCOLLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiScriptLib.mak all\
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