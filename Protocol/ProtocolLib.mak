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
# $Header: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/ProtocolLib/ProtocolLib.mak 1     10/15/08 2:19p Fasihm $
#
# $Revision: 1 $
#
# $Date: 10/15/08 2:19p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/MPG/Calpella/MiscFramework/ProtocolLib/ProtocolLib.mak $
# 
# 1     10/15/08 2:19p Fasihm
# Initial check-in for the Calpella Crb MiscFramework module used.
# 
# 1     8/26/08 2:08p Fasihm
# This is the first CRB drop used for the PowerOn of the Calpella CRB
# platform (RedFort)
# With this project one needs to add the correct CPU Microcodes.
# 
# 1     9/12/06 9:11a Fasihm
# FirstCheckin for the Project ProtocolLib in MiscFramework folder.
# 
# 1     9/12/06 9:05a Fasihm
# ProtocolLib files needed in MiscFramework.
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
# Name:	<ComponentName>.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : ProtocolLib

$(BUILD_DIR)\ProtocolLib.lib : ProtocolLib

ProtocolLib : $(BUILD_DIR)\ProtocolLib.mak ProtocolLibBin

$(BUILD_DIR)\ProtocolLib.mak : $(ProtocolLib_DIR)\$(@B).cif $(ProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(ProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

ProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\ProtocolLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(MISCFRAMEWORK_INCLUDES) /I$(PROJECT_DIR)" \
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