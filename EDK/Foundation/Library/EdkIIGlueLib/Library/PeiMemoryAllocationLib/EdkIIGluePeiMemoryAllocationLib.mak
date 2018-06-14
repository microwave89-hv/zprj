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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiMemoryAllocationLib/EdkIIGluePeiMemoryAllocationLib.mak 1     1/20/12 3:56a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:56a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiMemoryAllocationLib/EdkIIGluePeiMemoryAllocationLib.mak $
# 
# 1     1/20/12 3:56a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:19a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:57a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGluePeiMemoryAllocationLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGluePeiMemoryAllocationLib_LIB) : EdkIIGluePeiMemoryAllocationLib

EdkIIGluePeiMemoryAllocationLib : $(BUILD_DIR)\EdkIIGluePeiMemoryAllocationLib.mak EdkIIGluePeiMemoryAllocationLibBin

$(BUILD_DIR)\EdkIIGluePeiMemoryAllocationLib.mak : $(EdkIIGluePeiMemoryAllocationLib_DIR)\$(@B).cif $(EdkIIGluePeiMemoryAllocationLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGluePeiMemoryAllocationLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGluePeiMemoryAllocationLibBin : $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGluePeiServicesTablePointerLibMm7_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiMemoryAllocationLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiMemoryAllocationLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGluePeiMemoryAllocationLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiMemoryAllocationLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiMemoryAllocationLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiMemoryAllocationLib_LIB)"
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