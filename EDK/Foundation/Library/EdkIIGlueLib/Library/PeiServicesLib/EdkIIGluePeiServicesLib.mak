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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiServicesLib/EdkIIGluePeiServicesLib.mak 2     2/24/12 5:01a Jeffch $
#
# $Revision: 2 $
#
# $Date: 2/24/12 5:01a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiServicesLib/EdkIIGluePeiServicesLib.mak $
# 
# 2     2/24/12 5:01a Jeffch
# 
# 1     1/20/12 3:57a Jeffch
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
# Name:	EdkIIGluePeiServicesLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGluePeiServicesLib_LIB) : EdkIIGluePeiServicesLib

EdkIIGluePeiServicesLib : $(BUILD_DIR)\EdkIIGluePeiServicesLib.mak EdkIIGluePeiServicesLibBin

$(BUILD_DIR)\EdkIIGluePeiServicesLib.mak : $(EdkIIGluePeiServicesLib_DIR)\$(@B).cif $(EdkIIGluePeiServicesLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGluePeiServicesLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGluePeiServicesLib_LIB_LINKS=\
$(EDKFRAMEWORKPPILIB)\
!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
$(EdkIIGluePeiServicesTablePointerLibMm7_LIB)
!ENDIF	

EdkIIGluePeiServicesLibBin : $(EdkIIGluePeiServicesLib_LIB_LINKS)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiServicesLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiServicesLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGluePeiServicesLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiServicesLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiServicesLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiServicesLib_LIB)"
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
