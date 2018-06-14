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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelPlatformProtocolLib/DxeKscLib/DxeKscLib.mak 1     2/09/12 12:39a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/09/12 12:39a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/Platform/IntelPlatformProtocolLib/DxeKscLib/DxeKscLib.mak $
# 
# 1     2/09/12 12:39a Yurenlai
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
all : DxeKscLib

$(BUILD_DIR)\DxeKscLib.lib : DxeKscLib

DxeKscLib : $(BUILD_DIR)\DxeKscLib.mak DxeKscLibBin

$(BUILD_DIR)\DxeKscLib.mak : $(DxeKscLib_DIR)\$(@B).cif $(DxeKscLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(DxeKscLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

DxeKscLibBin : $(EFIDRIVERLIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\DxeKscLib.mak all\
        "CFLAGS=$(CFLAGS) "\
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