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
# $Header: /Alaska/SOURCE/Core/Modules/HashService/HashService.mak 1     5/24/12 3:33p Artems $
#
# $Revision: 1 $
#
# $Date: 5/24/12 3:33p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/HashService/HashService.mak $
# 
# 1     5/24/12 3:33p Artems
# [TAG]  		EIP N/A
# [Category]  	New Feature
# [Description]  	Added HashService protocol infrastructure
# [Files]  		HashService.cif
# HashService.sdl
# HashService.mak
# HashService.c
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: HashService.mak
#
# Description:  Make file to create Hash Service Binding Driver
#
#<AMI_FHDR_END>
#**********************************************************************

CORE_DXEBin : $(BUILD_DIR)\HashService.obj

$(BUILD_DIR)\HashService.obj : $(HashService_DIR)\HashService.c

{$(HashService_DIR)}.c{$(BUILD_DIR)}.obj::
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
