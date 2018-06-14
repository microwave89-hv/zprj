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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiLib/EdkIIGlueUefiLib.mak 1     1/20/12 3:58a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:58a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiLib/EdkIIGlueUefiLib.mak $
# 
# 1     1/20/12 3:58a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:20a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:59a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueUefiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueUefiLib_LIB) : EdkIIGlueUefiLib

EdkIIGlueUefiLib : $(BUILD_DIR)\EdkIIGlueUefiLib.mak EdkIIGlueUefiLibBin

$(BUILD_DIR)\EdkIIGlueUefiLib.mak : $(EdkIIGlueUefiLib_DIR)\$(@B).cif $(EdkIIGlueUefiLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueUefiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueUefiLibBin : $(EdkIIGlueBaseLib_LIB) $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGlueUefiBootServicesTableLib_LIB) $(EdkIIGlueDxeMemoryAllocationLib_LIB) $(EFIGUIDLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueUefiLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiLib_LIB)"
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
