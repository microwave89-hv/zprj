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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePostCodeLibDebug/EdkIIGlueBasePostCodeLibDebug.mak 1     1/20/12 3:54a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:54a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePostCodeLibDebug/EdkIIGlueBasePostCodeLibDebug.mak $
# 
# 1     1/20/12 3:54a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:16a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:53a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBasePostCodeLibDebug.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueBasePostCodeLibDebug_LIB) : EdkIIGlueBasePostCodeLibDebug

EdkIIGlueBasePostCodeLibDebug : $(BUILD_DIR)\EdkIIGlueBasePostCodeLibDebug.mak EdkIIGlueBasePostCodeLibDebugBin

$(BUILD_DIR)\EdkIIGlueBasePostCodeLibDebug.mak : $(EdkIIGlueBasePostCodeLibDebug_DIR)\$(@B).cif $(EdkIIGlueBasePostCodeLibDebug_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBasePostCodeLibDebug_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueBasePostCodeLibDebugBin :
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePostCodeLibDebug.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePostCodeLibDebug_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBasePostCodeLibDebug.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePostCodeLibDebug_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePostCodeLibDebug.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePostCodeLibDebug_LIB)"
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