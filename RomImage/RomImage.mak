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

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
#
# Name:         RomImage.mak
#
# Description:
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>

!IFDEF ME_ROM_IMAGE_BUILD_SUPPORT
!IF $(ME_ROM_IMAGE_BUILD_SUPPORT) == 1
END:  BUILD_ME

!IF "$(SecureMod_SUPPORT)"=="1"
BUILD_ME: $(FWCAPSULE_FILE_NAME) $(AMI_ROM)
!ELSE
BUILD_ME: $(AMI_ROM)
!ENDIF
    @if exist Rom_*.bin @del /q Rom_*.bin
    @if exist Rom00_*.bin @del /q Rom00_*.bin
    @if exist Rom01_*.bin @del /q Rom01_*.bin

!IFDEF PfatServices_SUPPORT
!IF $(PfatServices_SUPPORT) == 1
    @if exist AMIPFAT_*.bin @del /q AMIPFAT_*.bin
    $(FITC_BUILD_PFAT_RULES)
!ELSE
    $(FITC_BUILD_RULES)
!ENDIF
!ELSE
    $(FITC_BUILD_RULES)
!ENDIF

!ENDIF
!ENDIF

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

