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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiIfrSupportLib/EfiIfrSupportLib.mak 1     1/20/12 4:07a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:07a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiIfrSupportLib/EfiIfrSupportLib.mak $
# 
# 1     1/20/12 4:07a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:30a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:45a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiIfrSupportLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EFIIFRSUPPORTLIB) : EfiIfrSupportLib

$(BUILD_DIR)\EfiIfrSupportLib.lib : EfiIfrSupportLib

EfiIfrSupportLib : $(BUILD_DIR)\EfiIfrSupportLib.mak EfiIfrSupportLibBin

$(BUILD_DIR)\EfiIfrSupportLib.mak : $(EfiIfrSupportLib_DIR)\$(@B).cif $(EfiIfrSupportLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiIfrSupportLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiIfrSupportLibBin : $(EFIGUIDLIB) $(EDKFRAMEWORKPROTOCOLLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiIfrSupportLib.mak all\
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