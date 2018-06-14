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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiDriverModelLib/EdkIIGlueUefiDriverModelLib.mak 1     1/20/12 3:58a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:58a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiDriverModelLib/EdkIIGlueUefiDriverModelLib.mak $
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
# Name:	EdkIIGlueUefiDriverModelLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueUefiDriverModelLib_LIB) : EdkIIGlueUefiDriverModelLib

EdkIIGlueUefiDriverModelLib : $(BUILD_DIR)\EdkIIGlueUefiDriverModelLib.mak EdkIIGlueUefiDriverModelLibBin

$(BUILD_DIR)\EdkIIGlueUefiDriverModelLib.mak : $(EdkIIGlueUefiDriverModelLib_DIR)\$(@B).cif $(EdkIIGlueUefiDriverModelLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueUefiDriverModelLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueUefiDriverModelLibBin : $(EdkIIGlueUefiBootServicesTableLib_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiDriverModelLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiDriverModelLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueUefiDriverModelLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiDriverModelLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiDriverModelLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiDriverModelLib_LIB)"
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