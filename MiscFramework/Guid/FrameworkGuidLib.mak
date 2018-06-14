#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/FrameworkGuidLib/FrameworkGuidLib.mak 1     10/15/08 2:19p Fasihm $
#
# $Revision: 1 $
#
# $Date: 10/15/08 2:19p $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	FrameworkGuidLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
EDK : FrameworkGuidLib

$(FrameworkGuidLib_LIB) : FrameworkGuidLib

FrameworkGuidLib : $(BUILD_DIR)\FrameworkGuidLib.mak FrameworkGuidLibBin

$(BUILD_DIR)\FrameworkGuidLib.mak : $(FrameworkGuidLib_DIR)\$(@B).cif $(FrameworkGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FrameworkGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

FrameworkGuidLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\FrameworkGuidLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) /I$(MISCFRAMEWORK_DIR)" \
		TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\FrameworkGuidLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) /I$(MISCFRAMEWORK_DIR)" \
		TYPE=PEI_LIBRARY
!ENDIF

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************