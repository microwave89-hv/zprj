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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiBootServicesTableLib/EdkIIGlueUefiBootServicesTableLib.mak 1     1/20/12 3:57a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:57a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiBootServicesTableLib/EdkIIGlueUefiBootServicesTableLib.mak $
# 
# 1     1/20/12 3:57a Jeffch
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
# Name:	EdkIIGlueUefiBootServicesTableLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueUefiBootServicesTableLib_LIB) : EdkIIGlueUefiBootServicesTableLib

EdkIIGlueUefiBootServicesTableLib : $(BUILD_DIR)\EdkIIGlueUefiBootServicesTableLib.mak EdkIIGlueUefiBootServicesTableLibBin

$(BUILD_DIR)\EdkIIGlueUefiBootServicesTableLib.mak : $(EdkIIGlueUefiBootServicesTableLib_DIR)\$(@B).cif $(EdkIIGlueUefiBootServicesTableLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueUefiBootServicesTableLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueUefiBootServicesTableLibBin :
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiBootServicesTableLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiBootServicesTableLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueUefiBootServicesTableLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiBootServicesTableLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiBootServicesTableLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiBootServicesTableLib_LIB)"
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