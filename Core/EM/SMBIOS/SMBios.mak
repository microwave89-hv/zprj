#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **//
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
# $Header: /Alaska/SOURCE/Modules/SMBIOS/SMBios.mak 9     3/26/12 12:06p Davidd $
#
# $Revision: 9 $
#
# $Date: 3/26/12 12:06p $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMBIOS/SMBios.mak $
# 
# 9     3/26/12 12:06p Davidd
# [TAG]  		EIP84370
# [Category]  	New Feature
# [Description]  	Flash memory(type 16 and 17) on aptio
# [Files]  		Smbdata.mac
# SmbiosStaticData.asm
# SmbiosStaticData.sdl
# Smbios.c
# Smbios.mak
# Smbios.h
# 
# 8     8/04/10 2:44p Davidd
# Remove environment variables "MAKEFILE" and "INCLUDE" - EIP 40634.
# 
# 7     4/06/10 10:30a Davidd
# 
# 6     6/02/09 11:14a Davidd
# Updated AMI header section.
# 
# 5     12/30/08 3:21p Davidd
# Changes added for x32 and x64 binary support.
# 
# 4     1/22/08 4:27p Olegi
# 
# 3     12/26/07 5:06p Olegi
# 
# 2     3/29/07 5:56p Davidd
# Changed the year in the AMI banner.
# 
# 1     5/02/05 3:16p Davidd
# Initial Check-in.
# 
# 1     4/29/05 2:14p Davidd
# Initial checkin.
#
#************************************************************************//

all : SMBIOS

SMBIOS : $(BUILD_DIR)\SMBios.mak SMBiosBin

SMBIOS_OBJECTS = $(BUILD_DIR)\CORE\EM\SMBIOS\smbios.obj

$(BUILD_DIR)\SMBios.mak : $(SMBIOS_CORE_SRC_DIR)\SMBIOSCore.CIF $(SMBIOS_CORE_SRC_DIR)\$(@B).mak $(BUILD_RULES)
       $(CIF2MAK) $(SMBIOS_CORE_SRC_DIR)\SMBIOSCore.CIF $(CIF2MAK_DEFAULTS)

SMBiosBin : $(AMIDXELIB) $(FLASHLIB)
       $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
               /f $(BUILD_DIR)\SMBios.mak all\
!IF "$(x64_BUILD)"=="1"
               NAME=SMBios64 \
!ELSE
               NAME=SMBios32 \
!ENDIF
               MAKEFILE=$(BUILD_DIR)\SMBios.mak\
               OBJECTS="$(SMBIOS_OBJECTS)" \
               GUID=B13EDD38-684C-41ed-A305-D7B7E32497DF\
               ENTRY_POINT=SmbiosDriverEntryPoint\
               TYPE=BS_DRIVER \
               COMPRESS=1

#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2010, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//
