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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiSmbusLib/EdkIIGluePeiSmbusLib.mak 1     1/20/12 3:57a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:57a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiSmbusLib/EdkIIGluePeiSmbusLib.mak $
# 
# 1     1/20/12 3:57a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:19a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:58a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGluePeiSmbusLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGluePeiSmbusLib_LIB) : EdkIIGluePeiSmbusLib

EdkIIGluePeiSmbusLib : $(BUILD_DIR)\EdkIIGluePeiSmbusLib.mak EdkIIGluePeiSmbusLibBin

$(BUILD_DIR)\EdkIIGluePeiSmbusLib.mak : $(EdkIIGluePeiSmbusLib_DIR)\$(@B).cif $(EdkIIGluePeiSmbusLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGluePeiSmbusLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGluePeiSmbusLibBin : $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGluePeiServicesTablePointerLibMm7_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiSmbusLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiSmbusLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGluePeiSmbusLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiSmbusLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiSmbusLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiSmbusLib_LIB)"
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