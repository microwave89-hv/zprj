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
# Name:	BootGuardTPMPei.mak
#
# Description: TPM Initialization Flow for Boot Guard
#
#<AMI_FHDR_END>
#**********************************************************************

TCG_FILE_INCLUDE=\
    /I$(TcgPlatformSetupPeiPolicy_DIR)\
    /I$(TCG_DIR)\
    /I$(AMI_TCG_PLATFORM_PEI_DIR)

AMI_TCG_LIB_OBJECTS = $(AMI_TCG_LIB_OBJECTS) \
$(BUILD)\BootGuardTPMPei.obj

Make_AMITTCG_LIB : $(BUILD_DIR)\BootGuardTPMPei.obj

$(BUILD_DIR)\BootGuardTPMPei.obj : $(BootGuardTPMPei_PATH)\BootGuardTPMPei.c
    $(CC) $(CFLAGS) /I$(PROJECT_DIR) /I$(PROJECT_DIR)\Include $(TCG_FILE_INCLUDE) $(PROJECT_CPU_INCLUDES) /Fo$(BUILD_DIR)\BootGuardTPMPei.obj $(BootGuardTPMPei_PATH)\BootGuardTPMPei.c

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
