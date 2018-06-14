#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelPlatformProtocolLib/IntelPlatformProtocolLib.mak 1     2/09/12 12:38a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/09/12 12:38a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelPlatformProtocolLib/IntelPlatformProtocolLib.mak $
# 
# 1     2/09/12 12:38a Yurenlai
# Initial check in.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	<ComponentName>.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : IntelPlatformProtocolLib

$(BUILD_DIR)\IntelPlatformProtocolLib.lib : IntelPlatformProtocolLib

IntelPlatformProtocolLib : $(BUILD_DIR)\IntelPlatformProtocolLib.mak IntelPlatformProtocolLibBin

$(BUILD_DIR)\IntelPlatformProtocolLib.mak : $(IntelPlatformProtocolLib_DIR)\$(@B).cif $(IntelPlatformProtocolLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IntelPlatformProtocolLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelPlatformProtocolLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\IntelPlatformProtocolLib.mak all\
		"MY_INCLUDES= /I$(MISCFRAMEWORK_DIR) $(EDK_INCLUDES) $(INTEL_PLATFORM_PROTOCOL_INCLUDES)"  \
		TYPE=LIBRARY \
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************