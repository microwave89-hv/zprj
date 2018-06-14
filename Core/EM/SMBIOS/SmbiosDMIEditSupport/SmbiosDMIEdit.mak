#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEdit.mak 11    4/04/16 11:41a Davidd $
#
# $Revision: 11 $
#
# $Date: 4/04/16 11:41a $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMBIOS/SmbiosDMIEditSupport/SmbiosDMIEdit.mak $
# 
# 11    4/04/16 11:41a Davidd
# [TAG]  		EIP262865
# [Category]  	Improvement
# [Description]  	[APTIO4][Smbios]DmiEdit needs changes as smiflash
# protocol is being changed to deny calls with Smm buffer
# [Files]  		SmbiosDMIEdit.mak
# SmbiosDMIEdit.h
# SmbiosDMIEdit.c
# SmbiosDMIEditFunc.c
# 
# 10    11/14/12 5:01p Davidd
# 
# 9     9/04/12 11:03a Davidd
# [TAG]  		EIP96286
# [Category]  	Improvement
# [Description]  	Please help to reserve DMI Data for AFUDOS with /r in
# Capsule Mode
# [Files]  		Smbios.sdl
# SmbiosDMIEdit.mak
# SmbiosNvramFunc.c
# 
# 8     8/28/12 11:17a Davidd
# [TAG]  		EIP97178
# [Category]  	Improvement
# [Description]  	SMIFlash fails to build when SMBIOS_DMIEDIT_DATA_LOC =
# 2
# [Files]  		SmbiosDMIEdit.mak
# SmbiosDMIEdit.sdl
# 
# 7     4/06/10 3:29p Davidd
# Added AMICSPLib path - EIP 33862
# 
# 6     2/02/09 4:32p Davidd
# - Updated AMI header.
# - Changes added to build a libray function used to save and restore
# DMIEdit data (when NVRAM is used for storage) prior to and after
# flashing using SMIFlash.
# 
# 5     7/23/08 12:36p Davidd
# Changes made to build SmbiosDMIEditBoard.obj file.
# 
# 3     3/29/07 5:58p Davidd
# Changed the year in the AMI banner.
# 
# 2     8/10/05 10:44a Davidd
# Added command to copy the porting file SmbiosDMIEditBoard.c as building
# the module.
#
# 1     4/29/05 2:06p Davidd
# Initial checkin.
#
#************************************************************************//

all : SMBIOS_DMIEDIT_SUPPORT

!IF "$(SMBIOS_DMIEDIT_DATA_LOC)"=="2" && "$(SMBIOS_PRESERVE_NVRAM)"=="1"
SMBIOS_DMIEDIT_SUPPORT : $(BUILD_DIR)\SmbiosDMIEdit.mak SmbiosDMIEditBin $(BUILD_DIR)\SmbiosNvram.lib
!ELSE
SMBIOS_DMIEDIT_SUPPORT : $(BUILD_DIR)\SmbiosDMIEdit.mak SmbiosDMIEditBin
!ENDIF

$(BUILD_DIR)\SmbiosNvram.lib : $(BUILD_DIR)\SmbiosDMIEdit.mak SmbiosNvramlib

$(BUILD_DIR)\SmbiosDMIEdit.mak : $(SMBIOS_DMIEDIT_DIR)\$(@B).cif $(SMBIOS_DMIEDIT_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(CIF2MAK_DEFAULTS) $(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEdit.cif 

$(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEditBoard.obj : $(SMBIOS_DMIEDIT_BOARD_DIR)\SmbiosDMIEditBoard.c
		$(CC) $(CFLAGS:/W4=/W3) /Fo$(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\ $(SMBIOS_DMIEDIT_BOARD_DIR)\SmbiosDMIEditBoard.c 

!IF "$(AmiBufferValidationLib_SUPPORT)"=="1"
SMBIOSDMIEDIT_OBJECTS = $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEdit.obj $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEditFunc.obj $(BUILD_DIR)\AmiBufferValidationLib.lib
!ELSE
SMBIOSDMIEDIT_OBJECTS = $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEdit.obj $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEditFunc.obj
!ENDIF

SmbiosDMIEditBin : $(AMIDXELIB) $(AMICSPLib) $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEditBoard.obj
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmbiosDMIEdit.mak all\
        "CFLAGS=$(CFLAGS:/W4=/W3)"\
		NAME=SmbiosDMIEdit\
		MAKEFILE=$(BUILD_DIR)\SmbiosDMIEdit.mak \
		OBJECTS="$(SMBIOSDMIEDIT_OBJECTS)" \
		GUID=E2A74738-8934-48f5-8412-99E948C8DC1B \
		ENTRY_POINT=SmbiosDmiEditSupportInstall \
		TYPE=BS_DRIVER \
		DEPEX1=$(SMBIOS_DMIEDIT_DIR)\SmbiosDMIEdit.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1

$(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.obj : $(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.c
		if not exist $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR) mkdir $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)
		$(CC) $(CFLAGS:/W4=/W3) /Fo$(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\ $(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.c 

ReFlashBin : $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.obj

!IF "$(SMBIOS_DMIEDIT_DATA_LOC)"=="2" && "$(SMBIOS_PRESERVE_NVRAM)"=="1"
PRESERVE_LIB = $(PRESERVE_LIB) \
               $(BUILD_DIR)\SmbiosNvram.lib

SMBIOS_NVRAM_OBJECTS = $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.obj

SmbiosNvramlib : $(BUILD_DIR)\$(SMBIOS_DMIEDIT_DIR)\SmbiosNvramFunc.obj
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmbiosDMIEdit.mak all\
		"OBJECTS=$(SMBIOS_NVRAM_OBJECTS)"\
		TYPE=LIBRARY LIBRARY_NAME=$(BUILD_DIR)\SmbiosNvram.lib
!ENDIF

#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2016, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//
