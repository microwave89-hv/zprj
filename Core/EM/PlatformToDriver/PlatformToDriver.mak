#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Core/Modules/PlatformToDriverConfiguration/PlatformToDriver.mak 1     5/02/11 5:30p Artems $
#
# $Revision: 1 $
#
# $Date: 5/02/11 5:30p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/PlatformToDriverConfiguration/PlatformToDriver.mak $
# 
# 1     5/02/11 5:30p Artems
# Platform-to-Driver confuguration protocol supporting infrastructure
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: PlatformToDriver.mak
#
# Description:  Make file to create PlatformToDriver configuration Driver
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\PlatformToDriver.obj

$(BUILD_DIR)\PlatformToDriver.obj : $(PlatformToDriver_DIR)\PlatformToDriver.c

{$(PlatformToDriver_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /D \"PlatformToDriverAgentList=$(PlatformToDriverAgents)\" /Fo$(BUILD_DIR)\ $<

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
