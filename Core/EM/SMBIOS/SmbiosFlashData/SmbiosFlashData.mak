#************************************************************************
#************************************************************************
#**                                                                    **
#**         (C)Copyright 1985-2009, American Megatrends, Inc.          **
#**                                                                    **
#**                        All Rights Reserved.                        **
#**                                                                    **
#**          5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
#**                                                                    **
#**                        Phone: (770)-246-8600                       **
#**                                                                    **
#************************************************************************
#************************************************************************
#************************************************************************
# $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosFlashData/SmbiosFlashData.mak 8     3/15/10 12:10p Davidd $
#
# $Revision: 8 $
#
# $Date: 3/15/10 12:10p $
#************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosFlashData/SmbiosFlashData.mak $
# 
# 8     3/15/10 12:10p Davidd
# Making sure the checksum is not calculated, else, the system hangs on
# reset after flash. FFS_CHECKSUM=0.
# 
# 7     5/15/09 3:26p Davidd
# Changes made to the build process to support Nested Firmware Volume
# 
# 6     1/28/09 11:55a Davidd
# New changes added to support DMIEdit data storage location in flash
# selectable via SMBIOS_DMIEDIT_DATA_LOC SDL token
# 
# 5     12/30/08 3:27p Davidd
# Removed switches to ganerate List and Map files.
# 
# 4     3/29/07 6:12p Davidd
# Changed the year in the AMI banner.
# 
# 3     1/27/06 5:40p Davidd
# Set compression to off.
# 
# 2     8/22/05 5:08p Davidd
# Set file compression to ON.
# 
# 1     4/29/05 2:06p Davidd
# Initial checkin.
#
#************************************************************************//

!IF "$(SMBIOS_DMIEDIT_DATA_LOC)"!="2"
all : SMBIOS_FLASHDATA

SMBIOS_FLASHDATA : $(BUILD_DIR)\SMBiosFlashData.ffs

$(BUILD_DIR)\SMBiosFlashData.ffs : $(BUILD_DIR)\SMBiosFD.bin
        $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=FD44820B-F1AB-41C0-AE4E-0C55556EB9BD\
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        BINFILE=$** FFSFILE=$@ COMPRESS=0 NAME=SmbiosFlashData FFS_CHECKSUM=0

$(BUILD_DIR)\SMBiosFD.bin : $(BUILD_DIR)\SMBiosFD.exe
  exe2bin $(BUILD_DIR)\SMBiosFD.exe $(BUILD_DIR)\SMBiosFD.tmp
  copy /b $(BUILD_DIR)\SMBiosFD.tmp + /b $(SOURCE_DIR)\pad.txt /b $(BUILD_DIR)\SMBiosFD.bin

$(BUILD_DIR)\SMBiosFD.exe : $(SMBIOS_FLASHDATA_DIR)\SMBiosFlashData.asm $(SMBIOS_FLASHDATA_DIR)\SMBiosFlashData.mak
  $(ASM) /c /nologo /Fo$(BUILD_DIR)\SMBiosFD.obj $(SMBIOS_FLASHDATA_DIR)\SMBiosFlashData.asm
  $(ASMLINK) $(BUILD_DIR)\SMBiosFD.obj, $(BUILD_DIR)\SMBiosFD.exe , NUL,,,
!ENDIF

#************************************************************************
#************************************************************************
#**                                                                    **
#**         (C)Copyright 1985-2009, American Megatrends, Inc.          **
#**                                                                    **
#**                        All Rights Reserved.                        **
#**                                                                    **
#**          5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
#**                                                                    **
#**                        Phone: (770)-246-8600                       **
#**                                                                    **
#************************************************************************
#************************************************************************
