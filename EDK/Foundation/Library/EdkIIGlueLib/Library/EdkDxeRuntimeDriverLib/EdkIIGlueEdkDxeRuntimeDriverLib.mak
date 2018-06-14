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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueEdkDxeRuntimeDriverLib/EdkIIGlueEdkDxeRuntimeDriverLib.mak 1     1/20/12 3:56a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:56a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueEdkDxeRuntimeDriverLib/EdkIIGlueEdkDxeRuntimeDriverLib.mak $
# 
# 1     1/20/12 3:56a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:18a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:55a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueEdkDxeRuntimeDriverLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS=

!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64" || "$(PROCESSOR)"=="EBC"
EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS=$(EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS)\
$$(BUILD_DIR)\$(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\Common\RuntimeLib.obj\
$$(BUILD_DIR)\$(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\Common\RuntimeService.obj
!ELSEIF "$(PROCESSOR)"=="IPF"
EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS=$(EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS)\
$$(BUILD_DIR)\$(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\Ipf\RuntimeLib.obj\
$$(BUILD_DIR)\$(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\Ipf\RuntimeService.obj
!ENDIF

$(EdkIIGlueEdkDxeRuntimeDriverLib_LIB) : EdkIIGlueEdkDxeRuntimeDriverLib

EdkIIGlueEdkDxeRuntimeDriverLib : $(BUILD_DIR)\EdkIIGlueEdkDxeRuntimeDriverLib.mak EdkIIGlueEdkDxeRuntimeDriverLibBin

$(BUILD_DIR)\EdkIIGlueEdkDxeRuntimeDriverLib.mak : $(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\$(@B).cif $(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueEdkDxeRuntimeDriverLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueEdkDxeRuntimeDriverLib_LIB_LINKS=$(EdkIIGlueUefiLib_LIB)\
$(EdkIIGlueBaseLib_LIB)\
$(EdkIIGlueUefiBootServicesTableLib_LIB)\
$(EFIPROTOCOLLIB)\
!IF "$(PROCESSOR)"=="IPF"
$(EdkIIGlueEdkDxeSalLib_LIB)
!ENDIF

EdkIIGlueEdkDxeRuntimeDriverLibBin : $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB_LINKS)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueEdkDxeRuntimeDriverLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)"\
		"OBJECTS=$(EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueEdkDxeRuntimeDriverLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)"\
		"OBJECTS=$(EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueEdkDxeRuntimeDriverLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)"\
		"OBJECTS=$(EdkIIGlueEdkDxeRuntimeDriverLib_OBJECTS)"
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
