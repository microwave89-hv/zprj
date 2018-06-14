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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiGuidLib/EfiGuidLib.mak 1     1/20/12 4:00a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:00a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EfiGuidLib/EfiGuidLib.mak $
# 
# 1     1/20/12 4:00a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:23a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 3:12a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiGuidLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

$(EFIGUIDLIB) : EfiGuidLib

EfiGuidLib : $(BUILD_DIR)\EfiGuidLib.mak EfiGuidLibBin

$(BUILD_DIR)\EfiGuidLib.mak : $(EfiGuidLib_DIR)\$(@B).cif $(EfiGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiGuidLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiGuidLib.mak all\
		TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EfiGuidLib.mak all\
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