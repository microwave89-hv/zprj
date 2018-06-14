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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeSampleCode/MePlatformGetResetTypeProtocolLib/MePlatformGetResetTypeProtocolLib.mak 1     2/08/12 12:55a Klzhan $
#
# $Revision: 1 $
#
# $Date: 2/08/12 12:55a $
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
all : MePlatformGetResetTypeProtocolLib

$(BUILD_DIR)\MePlatformGetResetTypeProtocolLib.lib : MePlatformGetResetTypeProtocolLib

MePlatformGetResetTypeProtocolLib : $(BUILD_DIR)\MePlatformGetResetTypeProtocolLib.mak MePlatformGetResetTypeProtocolLibBin

$(BUILD_DIR)\MePlatformGetResetTypeProtocolLib.mak : $(MePlatformGetResetTypeProtocolLib_DIR)\$(@B).cif $(MePlatformGetResetTypeProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MePlatformGetResetTypeProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MePlatformGetResetTypeProtocolLib_INCLUDES=\
		$(EDK_INCLUDES) \
                $(EdkIIGlueLib_INCLUDES)\
		$(ME_INCLUDES) \
		$(MISCFRAMEWORK_INCLUDES) \
                -I ReferenceCode\ME\SampleCode
		
MePlatformGetResetTypeProtocolLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\MePlatformGetResetTypeProtocolLib.mak all\
		"MY_INCLUDES=$(MePlatformGetResetTypeProtocolLib_INCLUDES)" \
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