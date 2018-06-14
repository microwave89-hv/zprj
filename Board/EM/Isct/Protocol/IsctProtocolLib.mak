#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctProtocolLib/IsctProtocolLib.mak 1     9/02/12 11:20p Bensonlai $
#
# $Revision: 1 $
#
# $Date: 9/02/12 11:20p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctProtocolLib/IsctProtocolLib.mak $
# 
# 1     9/02/12 11:20p Bensonlai
# Intel Smart Connect Technology initially releases.
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IsctProtocolLib.mak
#
# Description: Make file to build IsctProtocolLib components
#
#
#<AMI_FHDR_END>
#**********************************************************************

all : IsctProtocolLib

$(BUILD_DIR)\IsctProtocolLib.lib : IsctProtocolLib

IsctProtocolLib : $(BUILD_DIR)\IsctProtocolLib.mak IsctProtocolLibBin

$(BUILD_DIR)\IsctProtocolLib.mak : $(IsctProtocolLib_DIR)\$(@B).cif $(IsctProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IsctProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IsctProtocolLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\IsctProtocolLib.mak all\
		"MY_INCLUDES=$(EDK_INCLUDES) $(MISCFRAMEWORK_INCLUDES) $(EdkIIGlueLib_INCLUDES)" \
		TYPE=LIBRARY

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
