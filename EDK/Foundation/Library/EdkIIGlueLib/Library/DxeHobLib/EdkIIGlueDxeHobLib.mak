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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeHobLib/EdkIIGlueDxeHobLib.mak 1     1/20/12 3:55a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeHobLib/EdkIIGlueDxeHobLib.mak $
# 
# 1     1/20/12 3:55a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:17a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:54a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueDxeHobLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueDxeHobLib_LIB) : EdkIIGlueDxeHobLib

EdkIIGlueDxeHobLib : $(BUILD_DIR)\EdkIIGlueDxeHobLib.mak EdkIIGlueDxeHobLibBin

$(BUILD_DIR)\EdkIIGlueDxeHobLib.mak : $(EdkIIGlueDxeHobLib_DIR)\$(@B).cif $(EdkIIGlueDxeHobLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueDxeHobLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)		

EdkIIGlueDxeHobLibBin : $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGlueUefiLib_LIB) $(EDKFRAMEWORKGUIDLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeHobLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeHobLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueDxeHobLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeHobLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeHobLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeHobLib_LIB)"
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
