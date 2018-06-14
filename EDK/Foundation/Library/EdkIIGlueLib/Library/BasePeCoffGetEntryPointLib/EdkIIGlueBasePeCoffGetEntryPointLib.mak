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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePeCoffGetEntryPointLib/EdkIIGlueBasePeCoffGetEntryPointLib.mak 1     1/20/12 3:53a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:53a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePeCoffGetEntryPointLib/EdkIIGlueBasePeCoffGetEntryPointLib.mak $
# 
# 1     1/20/12 3:53a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:16a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:52a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBasePeCoffGetEntryPointLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueBasePeCoffGetEntryPointLib_LIB) : EdkIIGlueBasePeCoffGetEntryPointLib

EdkIIGlueBasePeCoffGetEntryPointLib : $(BUILD_DIR)\EdkIIGlueBasePeCoffGetEntryPointLib.mak EdkIIGlueBasePeCoffGetEntryPointLibBin

$(BUILD_DIR)\EdkIIGlueBasePeCoffGetEntryPointLib.mak : $(EdkIIGlueBasePeCoffGetEntryPointLib_DIR)\$(@B).cif $(EdkIIGlueBasePeCoffGetEntryPointLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBasePeCoffGetEntryPointLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueBasePeCoffGetEntryPointLibBin :
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePeCoffGetEntryPointLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePeCoffGetEntryPointLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBasePeCoffGetEntryPointLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePeCoffGetEntryPointLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePeCoffGetEntryPointLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePeCoffGetEntryPointLib_LIB)"
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