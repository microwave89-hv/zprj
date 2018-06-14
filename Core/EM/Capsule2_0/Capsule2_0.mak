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
# $Header: /Alaska/SOURCE/Core/Modules/Capsule2_0/Capsule2_0.mak 1     5/24/12 4:22p Artems $
#
# $Revision: 1 $
#
# $Date: 5/24/12 4:22p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/Capsule2_0/Capsule2_0.mak $
# 
# 1     5/24/12 4:22p Artems
# [TAG]  		EIP74625
# [Category]  	New Feature
# [Description]  	New Capsule PPI required by latest Intel's MRC code
# [Files]  		Capsule2_0.cif
# Capsule2_0.sdl
# Capsule2_0.mak
# Capsule2_0.c
# Capsule2_0.h
# Capsule2_0Runtime.c
# Capsule2_0Bds.c
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: Capsule2_0.mak
#
# Description:  Make file to create Capsule Driver
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_PEIBin : $(BUILD_DIR)\Capsule2_0.obj
RUNTIMEBin : $(BUILD_DIR)\Capsule2_0Runtime.obj
CORE_DXEBin : $(BUILD_DIR)\Capsule2_0Bds.obj

CFLAGS=$(CFLAGS) /D\"OEM_PROCESS_CAPSULE_LIST=$(OemProcessCapsuleList)\"

{$(Capsule2_0_DIR)}.c{$(BUILD_DIR)}.obj::
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
