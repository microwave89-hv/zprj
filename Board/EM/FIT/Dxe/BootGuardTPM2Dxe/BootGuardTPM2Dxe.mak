#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
#<AMI_FHDR_START>
#
# Name:	BootGuardTPM2Dxe.mak
#
# Description: TPM2 Initialization Flow for Boot Guard
#
#<AMI_FHDR_END>
#**********************************************************************

TpmDrvBin : $(BUILD_DIR)\BootGuardTPM2Dxe.obj

TPM2_INCLUDE=\
    /I$(TpmDrv_DIR)\
    /I$(TCG_DIR)\

$(BUILD_DIR)\BootGuardTPM2Dxe.obj : $(BootGuardTPM2Dxe_PATH)\BootGuardTPM2Dxe.c
    $(CC) $(CFLAGS) /I$(PROJECT_DIR) /I$(PROJECT_DIR)\Include $(TPM2_INCLUDE) $(PROJECT_CPU_INCLUDES) /Fo$(BUILD_DIR)\BootGuardTPM2Dxe.obj $(BootGuardTPM2Dxe_PATH)\BootGuardTPM2Dxe.c

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
