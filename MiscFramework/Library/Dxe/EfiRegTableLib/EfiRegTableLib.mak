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
# $Header: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/EfiRegTableLib/EfiRegTableLib.mak 1     10/15/08 2:19p Fasihm $
#
# $Revision: 1 $
#
# $Date: 10/15/08 2:19p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/EfiRegTableLib/EfiRegTableLib.mak $
# 
# 1     10/15/08 2:19p Fasihm
# Initial check-in for the Calpella Crb MiscFramework module used.
# 
# 1     8/26/08 2:08p Fasihm
# This is the first CRB drop used for the PowerOn of the Calpella CRB
# platform (RedFort)
# With this project one needs to add the correct CPU Microcodes.
# 
# 2     9/11/06 7:20p Fasihm
# Changed the CFLAGS to MY_LIBRARY for the Build process.
# 
# 1     6/27/06 6:06p Felixp
# 
# 1     6/05/06 6:31p Fasihm
# Initial check-in for the MiscFramework module placed in the Edk part on
# SSF.
# 
# 1     5/12/06 3:12p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EfiRegTableLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
Framework : EfiRegTableLib

$(BUILD_DIR)\EfiRegTableLib.lib : EfiRegTableLib

EfiRegTableLib : $(BUILD_DIR)\EfiRegTableLib.mak EfiRegTableLibBin

$(BUILD_DIR)\EfiRegTableLib.mak : $(EfiRegTableLib_DIR)\$(@B).cif $(EfiRegTableLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EfiRegTableLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EfiRegTableLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EfiRegTableLib.mak all\
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