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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiRuntimeServicesTableLib/EdkIIGlueUefiRuntimeServicesTableLib.mak 1     1/20/12 3:58a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:58a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueUefiRuntimeServicesTableLib/EdkIIGlueUefiRuntimeServicesTableLib.mak $
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
# Name:	EdkIIGlueUefiRuntimeServicesTableLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueUefiRuntimeServicesTableLib_LIB) : EdkIIGlueUefiRuntimeServicesTableLib

EdkIIGlueUefiRuntimeServicesTableLib : $(BUILD_DIR)\EdkIIGlueUefiRuntimeServicesTableLib.mak EdkIIGlueUefiRuntimeServicesTableLibBin

$(BUILD_DIR)\EdkIIGlueUefiRuntimeServicesTableLib.mak : $(EdkIIGlueUefiRuntimeServicesTableLib_DIR)\$(@B).cif $(EdkIIGlueUefiRuntimeServicesTableLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueUefiRuntimeServicesTableLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueUefiRuntimeServicesTableLibBin :
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiRuntimeServicesTableLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiRuntimeServicesTableLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueUefiRuntimeServicesTableLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiRuntimeServicesTableLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueUefiRuntimeServicesTableLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueUefiRuntimeServicesTableLib_LIB)"
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