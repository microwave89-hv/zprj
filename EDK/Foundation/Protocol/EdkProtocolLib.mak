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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkProtocolLib/EdkProtocolLib.mak 1     1/20/12 4:05a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 4:05a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkProtocolLib/EdkProtocolLib.mak $
# 
# 1     1/20/12 4:05a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:29a Wesleychen
# Intel EDK initially releases.
# 
# 2     9/02/09 4:04a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkProtocolLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EDKPROTOCOLLIB) : EdkProtocolLib

$(BUILD_DIR)\EdkProtocolLib.lib : EdkProtocolLib

EdkProtocolLib : $(BUILD_DIR)\EdkProtocolLib.mak EdkProtocolLibBin

!IF "$(PROCESSOR)"=="IPF"
EDK_PROTOCOL_LIB_PROCESSOR_CIF=$(EdkProtocolLib_DIR)\EdkProtocolLibIPF.cif
!ENDIF

$(BUILD_DIR)\EdkProtocolLib.mak : $(EdkProtocolLib_DIR)\$(@B).cif $(EdkProtocolLib_DIR)\$(@B).mak $(BUILD_RULES) $(EDK_PROTOCOL_LIB_PROCESSOR_CIF)
	$(CIF2MAK) $(EdkProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(EDK_PROTOCOL_LIB_PROCESSOR_CIF)

EdkProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\EdkProtocolLib.mak all\
		TYPE=LIBRARY\
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