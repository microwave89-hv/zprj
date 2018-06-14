#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperProtocolLib/AmtWrapperProtocolLib.mak 1     2/08/12 1:09a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 1:09a $
#**********************************************************************
# Revision History
# ----------------
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmtWrapperProtocolLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : AmtWrapperProtocolLib

$(BUILD_DIR)\AmtWrapperProtocolLib.lib : AmtWrapperProtocolLib

AmtWrapperProtocolLib : $(BUILD_DIR)\AmtWrapperProtocolLib.mak AmtWrapperProtocolLibBin

$(BUILD_DIR)\AmtWrapperProtocolLib.mak : $(AmtWrapperProtocolLib_DIR)\$(@B).cif $(AmtWrapperProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmtWrapperProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtWrapperProtocolLib_INCLUDES=\
		$(EDK_INCLUDES) \
		$(ME_INCLUDES) \
		$(MISCFRAMEWORK_INCLUDES) 
		
AmtWrapperProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AmtWrapperProtocolLib.mak all\
		"MY_INCLUDES=$(AmtWrapperProtocolLib_INCLUDES)" \
		TYPE=LIBRARY \

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************