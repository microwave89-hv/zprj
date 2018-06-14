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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkFrameworkGuidLib/EdkFrameworkGuidLib.mak 1     1/20/12 4:02a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:02a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkFrameworkGuidLib/EdkFrameworkGuidLib.mak $
# 
# 1     1/20/12 4:02a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:25a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:17a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkFrameworkGuidLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

$(EDKFRAMEWORKGUIDLIB) : EdkFrameworkGuidLib

EdkFrameworkGuidLib : $(BUILD_DIR)\EdkFrameworkGuidLib.mak EdkFrameworkGuidLibBin

$(BUILD_DIR)\EdkFrameworkGuidLib.mak : $(EdkFrameworkGuidLib_DIR)\$(@B).cif $(EdkFrameworkGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkFrameworkGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkFrameworkGuidLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EdkFrameworkGuidLib.mak all\
		TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkFrameworkGuidLib.mak all\
		TYPE=PEI_LIBRARY
!ENDIF
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