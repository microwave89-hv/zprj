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
# $Header: /Alaska/SOURCE/Core/Modules/FirmwareManagement/FirmwareManagement.mak 1     5/02/11 5:49p Artems $
#
# $Revision: 1 $
#
# $Date: 5/02/11 5:49p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/FirmwareManagement/FirmwareManagement.mak $
# 
# 1     5/02/11 5:49p Artems
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: FirmwareManagement.mak
#
# Description:  Make file to create FirmwareManagement Driver
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\FirmwareManagement.obj

$(BUILD_DIR)\FirmwareManagement.obj : $(FirmwareManagement_DIR)\FirmwareManagement.c

{$(FirmwareManagement_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $<

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
