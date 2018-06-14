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
# $Header: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/FrameworkPpiLib/FrameworkPpiLib.mak 1     10/15/08 2:19p Fasihm $
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
# Name:	FrameworkPpiLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : FrameworkPpiLib

$(BUILD_DIR)\FrameworkPpiLib.lib : FrameworkPpiLib

FrameworkPpiLib : $(BUILD_DIR)\FrameworkPpiLib.mak FrameworkPpiLibBin

$(BUILD_DIR)\FrameworkPpiLib.mak : $(FrameworkPpiLib_DIR)\$(@B).cif $(FrameworkPpiLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FrameworkPpiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

FrameworkPpiLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\FrameworkPpiLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) /I$(MISCFRAMEWORK_DIR) /I$(EDK_INCLUDES) /I$(PROJECT_DIR)\Include\IndustryStandard" \
		TYPE=PEI_LIBRARY \
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