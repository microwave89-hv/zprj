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
# $Header: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticData.mak 7     5/15/09 3:26p Davidd $
#
# $Revision: 7 $
#
# $Date: 5/15/09 3:26p $
#************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/SMBIOS/SmbiosStaticData/SmbiosStaticData.mak $
# 
# 7     5/15/09 3:26p Davidd
# Changes made to the build process to support Nested Firmware Volume
# 
# 6     3/29/07 4:51p Davidd
# Changed the year in the AMI banner and adjust indentation.
# 
# 5     3/14/07 2:16p Pavell
# Changes for ITK
# 
# 4     11/09/05 2:07p Felixp
# Type of FFS file changed from RAW to FREEFORM
# 
# 3     11/07/05 6:18p Davidd
# Changes made to support AMIBCP.
# 
# 2     7/20/05 2:59p Davidd
# Removed masm option /Fl. Listing files are not needed.
# 
# 1     4/29/05 2:15p Davidd
# Initial checkin.
#
#************************************************************************//
all : SMBIOS_STATIC

SMBIOS_STATIC : $(BUILD_DIR)\SMBiosStaticData.ffs

$(BUILD_DIR)\SMBiosStaticData.ffs : $(BUILD_DIR)\SMBiosSD.bin
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=DAF4BF89-CE71-4917-B522-C89D32FBC59F\
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	RESOURCE=$** SECTION_GUID=AB56DC60-0057-11da-A8DB-000102EEE626 \
	FFSFILE=$@ COMPRESS=1 NAME=SMBiosStaticData

$(BUILD_DIR)\SMBiosSD.bin : $(BUILD_DIR)\SMBiosSD.exe
    exe2bin $(BUILD_DIR)\SMBiosSD.exe $(BUILD_DIR)\SMBiosSD.bin

$(BUILD_DIR)\SMBiosSD.exe : $(SMBOBJS) $(SMBIOSDATA_DIR)\SMBiosStaticDataEnd.asm $(BUILD_DIR)\timestamp.equ
    $(ASM) /c /nologo /Fo$(BUILD_DIR)\SMBiosStaticDataEnd.obj $(SMBIOSDATA_DIR)\SMBiosStaticDataEnd.asm
    $(ASMLINK) $(SMBOBJS) + $(BUILD_DIR)\SMBiosStaticDataEnd.obj, $(BUILD_DIR)\SMBiosSD.exe,$(BUILD_DIR)\SMBiosSD.map,,,

$(BUILD_DIR)\SMBiosStaticData.obj : $(SMBIOSDATA_DIR)\SMBiosStaticData.asm $(BUILD_DIR)\timestamp.equ
    $(ASM) /c /nologo /Fo$(BUILD_DIR)\SMBiosStaticData.obj $(SMBIOSDATA_DIR)\SMBiosStaticData.asm

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
