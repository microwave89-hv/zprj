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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePeCoffLib/EdkIIGlueBasePeCoffLib.mak 1     1/20/12 3:54a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:54a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePeCoffLib/EdkIIGlueBasePeCoffLib.mak $
# 
# 1     1/20/12 3:54a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:16a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:52a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBasePeCoffLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


EdkIIGlueBasePeCoffLib_OBJECTS=\
$$(BUILD_DIR)\$(EdkIIGlueBasePeCoffLib_DIR)\BasePeCoff.obj

EdkIIGlueBasePeCoffLib_IA32_OBJECTS=\
$$(BUILD_DIR)\$(EdkIIGlueBasePeCoffLib_DIR)\Ia32\PeCoffLoaderEx.obj

!IF "$(PROCESSOR)"=="IA32"
EdkIIGlueBasePeCoffLib_OBJECTS =$(EdkIIGlueBasePeCoffLib_OBJECTS) $(EdkIIGlueBasePeCoffLib_IA32_OBJECTS)
!ELSEIF "$(PROCESSOR)"=="x64"
EdkIIGlueBasePeCoffLib_PEI_OBJECTS =$(EdkIIGlueBasePeCoffLib_OBJECTS) $(EdkIIGlueBasePeCoffLib_IA32_OBJECTS)
EdkIIGlueBasePeCoffLib_DXE_OBJECTS =$(EdkIIGlueBasePeCoffLib_OBJECTS)\
$$(BUILD_DIR)\$(EdkIIGlueBasePeCoffLib_DIR)\X64\PeCoffLoaderEx.obj
!ENDIF

$(EdkIIGlueBasePeCoffLib_LIB) : EdkIIGlueBasePeCoffLib

EdkIIGlueBasePeCoffLib : $(BUILD_DIR)\EdkIIGlueBasePeCoffLib.mak EdkIIGlueBasePeCoffLibBin

$(BUILD_DIR)\EdkIIGlueBasePeCoffLib.mak : $(EdkIIGlueBasePeCoffLib_DIR)\$(@B).cif $(EdkIIGlueBasePeCoffLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBasePeCoffLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueBasePeCoffLibBin : $(EdkIIGlueBaseMemoryLib_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePeCoffLib.mak all\
		"MY_INCLUDES=/I$(EdkIIGlueBasePeCoffLib_DIR)"\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePeCoffLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBasePeCoffLib_DXE_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBasePeCoffLib.mak all\
		"MY_INCLUDES=/I$(EdkIIGlueBasePeCoffLib_DIR)"\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePeCoffLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBasePeCoffLib_PEI_OBJECTS)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePeCoffLib.mak all\
		"MY_INCLUDES=/I$(EdkIIGlueBasePeCoffLib_DIR)"\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePeCoffLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBasePeCoffLib_OBJECTS)"
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
