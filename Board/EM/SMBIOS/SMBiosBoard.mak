#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//

#************************************************************************//
# $Header: /Alaska/BIN/Modules/SMBIOS/SMBiosBoard.mak 9     11/01/10 12:33p Davidd $
#
# $Revision: 9 $
#
# $Date: 11/01/10 12:33p $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/SMBIOS/SMBiosBoard.mak $
# 
# 9     11/01/10 12:33p Davidd
# [TAG]           EIP41560
# [Category]      Improvement
# [Description]   DMIEDIT modified values are not preserved in reboot
# [Files]
#    Smbios.c
#    Smbios.sdl
#    SmbiosBoard.c
#    SmbiosBoard.mak
# 
# 8     6/02/09 3:45p Davidd
# Updated AMI headers (EIP 22180)
# 
# 7     1/22/08 4:19p Olegi
# 
# 3     10/29/07 7:27p Felixp
# Update to be compatible with SMBIOS label 4.6.1_ALPHA_01.05
# 
# 2     12/02/05 12:17p Felixp
# Pricate SMBIOSBoard.mak added.
# 
# 1     12/02/05 12:16p Felixp
# 
# 2     12/02/05 11:45a Felixp
# 
# 1     7/18/05 6:01p Davidd
# File added for porting the SMBIOS dynamic data.
#
#************************************************************************//

all : SMBIOSBOARD

SMBIOSBOARD : $(BUILD_DIR)\SMBiosBoard.mak SMBiosBoardBin  SmBiosPnPBin

SMBIOS_BOARD_OBJECTS = $(BUILD_DIR)\BOARD\EM\SMBIOS\smbiosboard.obj

$(BUILD_DIR)\SMBiosBoard.mak : $(SMBIOS_DIR)\SMBIOSBoard.CIF $(SMBIOS_DIR)\$(@B).mak $(BUILD_RULES)
       $(CIF2MAK) $(SMBIOS_DIR)\SMBIOSBoard.CIF $(CIF2MAK_DEFAULTS)

SMBiosBoardBin : $(AMIDXELIB)
       $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
               /f $(BUILD_DIR)\SMBiosBoard.mak all\
               NAME=SMBiosBoard \
               OBJECTS="$(SMBIOS_BOARD_OBJECTS)" \
               GUID=CEF68C66-06AB-4fb3-A3ED-5FFA885B5725\
               ENTRY_POINT=SMIBiosBoardDriverEntryPoint\
               TYPE=BS_DRIVER \
               "CFLAGS=$(CFLAGS) /D\"SMBIOS_OEM_UPDATE_LIST=$(SmbiosOemUpdateList)\""\
               COMPRESS=1

SmBiosPnPBin: $(BUILD_DIR)\smbrun.inf

$(BUILD_DIR)\smbrun.inf: $(BUILD_DIR)\token.mak $(CSM_OEM_SMBIOS_PNPFUNC_FILE)
    copy << $@

[MODULE]
ModuleID = 1
VendorID = 0
DeviceID = 3
File = $(CSM_OEM_SMBIOS_PNPFUNC_FILE)
<<

$(CSM_OEM_SMBIOS_PNPFUNC_FILE): $(BUILD_DIR)\smbrun.obj
    $(ASMLINK) $(BUILD_DIR)\smbrun.obj, $*.exe, $*.map,,,
    exe2bin $*.exe $@

$(BUILD_DIR)\smbrun.obj: $(SMBIOS_DIR)\smbrun.asm
    $(ASM) /c /nologo /Fo$(BUILD_DIR)\ $(SMBIOS_DIR)\smbrun.asm


#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//
