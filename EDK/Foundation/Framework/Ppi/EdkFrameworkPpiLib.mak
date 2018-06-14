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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkFrameworkPpiLib/EdkFrameworkPpiLib.mak 2     3/27/12 4:26a Jeffch $
#
# $Revision: 2 $
#
# $Date: 3/27/12 4:26a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkFrameworkPpiLib/EdkFrameworkPpiLib.mak $
# 
# 2     3/27/12 4:26a Jeffch
# 
# 1     1/20/12 4:03a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:26a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:19a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkFrameworkPpiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

$(EDKFRAMEWORKPPILIB) : EdkFrameworkPpiLib

EdkFrameworkPpiLib : $(BUILD_DIR)\EdkFrameworkPpiLib.mak EdkFrameworkPpiLibBin

$(BUILD_DIR)\EdkFrameworkPpiLib.mak : $(EdkFrameworkPpiLib_DIR)\$(@B).cif $(EdkFrameworkPpiLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkFrameworkPpiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkFrameworkPpiLibBin : $(EDKPPILIB)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EdkFrameworkPpiLib.mak all\
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