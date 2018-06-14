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
# $Header: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/EfiSmmDriverLib/EfiSmmDriverLib.mak 1     10/15/08 2:20p Fasihm $
#
# $Revision: 1 $
#
# $Date: 10/15/08 2:20p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/EfiSmmDriverLib/EfiSmmDriverLib.mak $
# 
# 1     10/15/08 2:20p Fasihm
# Initial check-in for the Calpella Crb MiscFramework module.
# 
# 1     8/26/08 2:08p Fasihm
# This is the first CRB drop used for the PowerOn of the Calpella CRB
# platform (RedFort)
# With this project one needs to add the correct CPU Microcodes.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiSmmDriverLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
Framework : EfiSmmDriverLib

$(BUILD_DIR)\EfiSmmDriverLib.lib : EfiSmmDriverLib

EfiSmmDriverLib : $(BUILD_DIR)\EfiSmmDriverLib.mak EfiSmmDriverLibBin

$(BUILD_DIR)\EfiSmmDriverLib.mak : $(EfiSmmDriverLib_DIR)\$(@B).cif $(EfiSmmDriverLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiSmmDriverLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiSmmDriverLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiSmmDriverLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(MISCFRAMEWORK_INCLUDES)" \
		TYPE=LIBRARY \
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