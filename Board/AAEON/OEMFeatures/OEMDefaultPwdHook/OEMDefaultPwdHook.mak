#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
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
# $Header: $
#
# $Revision: $
#
# $Date: $
#**********************************************************************
# Revision History
# ----------------
# $Log: $
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	OemTseHook.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

AMITSEBin : $(BUILD_DIR)\OEMDefaultPwdHook.obj 

OEMDefaultPwdHook_CFLAGS=$(CFLAGS) \
    -I $(TSESRC_DIR) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)

$(BUILD_DIR)\OEMDefaultPwdHook.obj : $(OemDefaultPwdHook_DIR)\OEMDefaultPwdHook.obj
	$(CC) $(OEMDefaultPwdHook_CFLAGS) /Fo$(BUILD_DIR)\OEMDefaultPwdHook.obj $(OemDefaultPwdHook_DIR)\OEMDefaultPwdHook.c


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2007, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
