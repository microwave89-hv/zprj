#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/SMIFlash/SMIFlash.mak 13    11/02/12 7:13a Calvinchen $
#
# $Revision: 13 $
#
# $Date: 11/02/12 7:13a $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SMIFlash/SMIFlash.mak $
# 
# 13    11/02/12 7:13a Calvinchen
# [TAG]  		EIP64328
# [Category]  	Improvement
# [Description]  	Improvement: 
#  1. (EIP64328) Update modules to be compliant with PI 1.2 and UEFI
# 2.3.1 specifications. 
# BugFix: 
#  1. (EIP100950) Fix the attribute of Win8 Debug Variable been changed
# after restored. 
#  2. (EIP98199) The #### in Boot#### should be upper case. 
# [Files]  		SMIFlash.mak
# SMIFlash.dxs
# SMIFlash.c
# SMIFlash.chm
# SMIFlashLinks.c
# SMIFlashDxe.dxs
# SMIFlash.cif
# 
# 12    5/29/12 5:45a Klzhan
# [TAG]  		EIP86878
# [Category]  	Improvement
# [Description]  	Restore SMBIOS data when recovery.
# [Files]  		SMIFlash.sdl
# SMIFlash.mak
# SMIFlash.dxs
# SMIFlash.c
# SMIFlash.chm
# SMIFlashLinks.c
# SMIFlash.cif
# 
# 11    5/23/12 3:01a Klzhan
# [TAG]  		EIP81706 
# [Category]  	Improvement
# [Description]  	Restore variables when recovery.
# 
# 10    3/06/12 2:41a Klzhan
# Improvement :
# 1. Add non SMM Elinks
# 2. Search Variables on in-active NVRam.
# 
# 9     11/23/11 3:39a Calvinchen
# [TAG]  		EIP54533
# [Category]  	Improvement
# [Description]  	1. Removed BiosLockEnablePatchHook hook. Moved to
# Chipset file. 
# 2. Also enable/disable PS2 keyboard in Enable/DisableUSBKBD hook. 
# 3. (EIP54533) Request for afu capable updating OEM firmware volumes 
# [Files]  		SMIFlash.sdl
# SMIFlash.mak
# SMIFlash.chm
# SMIFlashLinks.c
# 
# 8     3/23/11 4:44a Calvinchen
# [TAG]  		EIP53067
# [Category]  	Improvement
# [Description]  	Modified for OEM Secure BIOS Update Requirements.
# [Files]  		SMIFlash.sdl
# SMIFlash.mak
# SMIFlash.dxs
# SMIFlash.c
# SMIFlash.chm
# SMIFlashLinks.c
# SMIFlash.cif
# 
# 7     6/15/10 3:11a Klzhan
# Improvement: Add Elink to modify GetFlashInfo.
# 
# 6     2/02/09 6:42p Fredericko
# 
# 5     1/29/09 5:36p Fredericko
# modified build for SMIFLASH_PRE_UPDATE_LIST and
# SMIFLASH_END_UPDATE_LIST. See EIP 18819
# 
# 4     8/15/07 7:07p Pats
# Modified to support preservation of passwords through flashing.
# 
# 3     12/29/06 3:04p Felixp
# 1. Updated to use new Flash Interface.
# 2. Embedded Controller support added.
# 
# 2     12/02/05 11:48a Felixp
# 
# 1     4/05/05 3:47p Sivagarn
# Initial Checkin
#
#************************************************************************//

all : SMIFlash

SMIFLASH_BUILD_DIR = $(BUILD_DIR)\$(SMI_FLASH_DIR)

SMIFlash : $(SMIFLASH_BUILD_DIR)\RomLayout.obj $(BUILD_DIR)\SMIFlash.mak SMIFlashBin

SMIFlashObjects =\
$(SMIFLASH_BUILD_DIR)\SMIFlash.obj\
$(SMIFLASH_BUILD_DIR)\SMIFlashLinks.obj\
$(SMIFLASH_BUILD_DIR)\RomLayout.obj\
$(BUILD_DIR)\$(NVRAM_DIR)\NVRAMRead.obj\

SMIFLASH_LISTS = \
/D\"PRESERVE_FFS_GUID=$(SMIFlashPreserveRomHoleGuid)\"\
/D\"SMIFLASH_IN_SMM_LIST=$(SMIFlashInSmmList)\"\
/D\"SMIFLASH_NOT_IN_SMM_LIST=$(SMIFlashNotSmmList)\"\
/D\"SMIFLASH_END_UPDATE_LIST=$(SMIFlashEndUpdateList)\"\
/D\"SMIFLASH_PRE_UPDATE_LIST=$(SMIFlashPreUpdateList)\"\
/D\"SMIFLASH_PRE_HANDLER_LIST=$(SMIFlashPreHandlerList)\"\
/D\"SMIFLASH_END_HANDLER_LIST=$(SMIFlashEndHandlerList)\"

$(BUILD_DIR)\SMIFlash.mak : $(SMI_FLASH_DIR)\SMIFlash.cif $(SMI_FLASH_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SMI_FLASH_DIR)\SMIFlash.cif $(CIF2MAK_DEFAULTS)

SMIFlashBin : $(AMIDXELIB) $(FLASHLIB) $(PRESERVE_LIB)
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SMIFlash.mak all\
        GUID=BC327DBD-B982-4f55-9F79-056AD7E987C5\
        OBJECTS="$(SMIFlashObjects)" \
        ENTRY_POINT=SMIFlashDriverEntryPoint\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        "CFLAGS=$(CFLAGS) /DVFRCOMPILE $(SMIFLASH_LISTS)"\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A
        TYPE=DXESMM_DRIVER\
        DEPEX1=$(SMI_FLASH_DIR)\SMIFlash.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
        DEPEX2=$(SMI_FLASH_DIR)\SMIFlashDxe.dxs \
        DEPEX2_TYPE=EFI_SECTION_DXE_DEPEX \
!ELSE
        TYPE=BS_DRIVER\
        DEPEX1=$(SMI_FLASH_DIR)\SMIFlash.dxs \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF		 
        COMPRESS=1

$(SMIFLASH_BUILD_DIR)\RomLayout.obj : $(BUILD_DIR)\RomLayout.c
    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\RomLayout.c

#---------------------------------------------------------------------------
#               Reflash link file
#---------------------------------------------------------------------------
!IF "$(RECOVERY_PRESERVE_VARS_IN_SMM)"=="1"
ReFlashBin : $(BUILD_DIR)\ReflashHooks.obj

$(BUILD_DIR)\ReflashHooks.obj : $(SMI_FLASH_DIR)\SMIFlashLinks.c
    $(CC) /Fo$(BUILD_DIR)\ReflashHooks.obj $(CFLAGS) /D_OUTSIDE_SMM_ $(SMI_FLASH_DIR)\SMIFlashLinks.c
!ENDIF

#//**********************************************************************//
#//**********************************************************************//
#//**                                                                  **//
#//**        (C)Copyright 1985-2005, American Megatrends, Inc.         **//
#//**                                                                  **//
#//**                       All Rights Reserved.                       **//
#//**                                                                  **//
#//**             6145-F Northbelt Pkwy, Norcross, GA 30071            **//
#//**                                                                  **//
#//**                       Phone: (770)-246-8600                      **//
#//**                                                                  **//
#//**********************************************************************//
#//**********************************************************************//
