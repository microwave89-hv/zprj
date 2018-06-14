#//**********************************************************************
#//**********************************************************************
#//**                                                                  **
#//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#//**                                                                  **
#//**                       All Rights Reserved.                       **
#//**                                                                  **
#//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#//**                                                                  **
#//**                       Phone: (770)-246-8600                      **
#//**                                                                  **
#//**********************************************************************
#//**********************************************************************

#************************************************************************
# $Header: /Alaska/SOURCE/Modules/BootScriptHide/BootScriptHide.mak 1     9/10/14 6:31p Aaronp $
#
# $Date: 9/10/14 6:31p $
#
#************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/BootScriptHide/BootScriptHide.mak $
# 
# 1     9/10/14 6:31p Aaronp
# First addition of BootScriptHide emodule.
#************************************************************************

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
# Name:		BootScriptHide.mak
#
# Description:  Make file for the Boot Script Hide emodule
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>
all : BootScriptHideDxe BootScriptHidePei BootScriptHideSmm

$(BUILD_DIR)\BootScriptHide.mak : $(BOOT_SCRIPT_HIDE_DIR)\BootScriptHide.cif $(BUILD_RULES)
	$(CIF2MAK) $(BOOT_SCRIPT_HIDE_DIR)\BootScriptHide.cif $(CIF2MAK_DEFAULTS)

BootScriptHideDxe : $(BUILD_DIR)\BootScriptHide.mak BootScriptHideDxeBin

HIDE_BOOT_SCRIPT_DXE_OBJECTS = $(BUILD_DIR)\$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHideDxe.obj

### DXE ###
BootScriptHideDxeBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\BootScriptHide.mak all\
		NAME=BootScriptHideDxe\
		MAKEFILE=$(BUILD_DIR)\BootScriptHide.mak \
		BUILD_DIR=$(BUILD_DIR)\
		OBJECTS="$(HIDE_BOOT_SCRIPT_DXE_OBJECTS)" \
		GUID=A570F393-B0F5-44A4-8550-61600597B409 \
		ENTRY_POINT=BootScriptHideDxeEntryPoint \
		TYPE=BS_DRIVER \
		DEPEX1=$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHideDxe.DXS \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=0


### PEI ###
!IF "$(x64_BUILD)"=="1"
HIDE_BOOT_SCRIPT_PEI_OBJECTS = $(BUILD_DIR)\IA32\$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHidePei.obj
!ELSE
HIDE_BOOT_SCRIPT_PEI_OBJECTS = $(BUILD_DIR)\$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHidePei.obj
!ENDIF

BootScriptHidePei : $(AMIPEILIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\BootScriptHide.mak all\
		NAME=BootScriptHidePei\
		MAKEFILE=$(BUILD_DIR)\BootScriptHide.mak \
!IF "$(x64_BUILD)"=="1"
		BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
		BUILD_DIR=$(BUILD_DIR)\
!ENDIF
        OBJECTS="$(HIDE_BOOT_SCRIPT_PEI_OBJECTS)" \
		GUID=9B8A0C3A-5186-4B55-89F4-CAFDE613DAB1 \
		"MY_INCLUDES=/I$(ACPI_DIR)" \
		ENTRY_POINT=BootScriptHidePeiEntryPoint \
		TYPE=PEIM \
		DEPEX1=$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHidePei.DXS \
        DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        COMPRESS=0

### SMM ###
!IF $(PI_SPECIFICATION_VERSION) < 0x0001000A
!ERROR BotoScriptHide requires PI 1.1 or higher
!ENDIF

BootScriptHideSmm : $(BUILD_DIR)\BootScriptHide.mak BootScriptHideSmmBin

HIDE_BOOT_SCRIPT_SMM_OBJECTS = $(BUILD_DIR)\$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHideSmm.obj

BootScriptHideSmmBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\BootScriptHide.mak all\
		NAME=BootScriptHideSmm\
		MAKEFILE=$(BUILD_DIR)\BootScriptHide.mak \
		BUILD_DIR=$(BUILD_DIR)\
        OBJECTS="$(HIDE_BOOT_SCRIPT_SMM_OBJECTS)" \
		GUID=70B8BACB-0B26-4048-A6F8-03A6AF2C5029 \
		"MY_INCLUDES=/I$(ACPI_DIR)" \
		ENTRY_POINT=BootScriptHideSmmEntryPoint \
		TYPE=SMM_DRIVER \
        DEPEX1=$(BOOT_SCRIPT_HIDE_DIR)\BootScriptHideSmm.dxs \
        DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX \
		COMPRESS=0

#//**********************************************************************
#//**********************************************************************
#//**                                                                  **
#//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#//**                                                                  **
#//**                       All Rights Reserved.                       **
#//**                                                                  **
#//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#//**                                                                  **
#//**                       Phone: (770)-246-8600                      **
#//**                                                                  **
#//**********************************************************************
#//**********************************************************************