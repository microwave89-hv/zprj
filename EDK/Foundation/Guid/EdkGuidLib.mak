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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkGuidLib/EdkGuidLib.mak 1     1/20/12 4:04a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:04a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkGuidLib/EdkGuidLib.mak $
# 
# 1     1/20/12 4:04a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:28a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:22a Iminglin
# EIP24919
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkGuidLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

$(EDKGUIDLIB) : EdkGuidLib

EdkGuidLib : $(BUILD_DIR)\EdkGuidLib.mak EdkGuidLibBin

$(BUILD_DIR)\EdkGuidLib.mak : $(EdkGuidLib_DIR)\$(@B).cif $(EdkGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkGuidLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EdkGuidLib.mak all\
		TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkGuidLib.mak all\
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