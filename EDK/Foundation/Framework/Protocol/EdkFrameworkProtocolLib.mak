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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkFrameworkProtocolLib/EdkFrameworkProtocolLib.mak 1     1/20/12 4:03a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:03a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkFrameworkProtocolLib/EdkFrameworkProtocolLib.mak $
# 
# 1     1/20/12 4:03a Jeffch
# 
# 1     9/27/11 6:27a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:20a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkFrameworkProtocolLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EDKFRAMEWORKPROTOCOLLIB) : EdkFrameworkProtocolLib

$(BUILD_DIR)\EdkFrameworkProtocolLib.lib : EdkFrameworkProtocolLib

EdkFrameworkProtocolLib : $(BUILD_DIR)\EdkFrameworkProtocolLib.mak EdkFrameworkProtocolLibBin

$(BUILD_DIR)\EdkFrameworkProtocolLib.mak : $(EdkFrameworkProtocolLib_DIR)\$(@B).cif $(EdkFrameworkProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkFrameworkProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkFrameworkProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EdkFrameworkProtocolLib.mak all\
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