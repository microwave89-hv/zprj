#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir.mak 8     12/08/14 3:36a Anbuprakashp $
#
# $Revision: 8 $
#
# $Date: 12/08/14 3:36a $
#**********************************************************************
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Legacy Serial Redirection/LegacySredir.mak $
# 
# 8     12/08/14 3:36a Anbuprakashp
# [TAG]  		EIP192305
# [Category]  	Improvement
# [Description]  	Replacing SmmGetMemoryType usage in LegacySredir module
# with AmiBufferValidationLib
# [Files]  		LegacySredir.mak, LegacySmmSredir.c, LegacySredir_Setup.C
# 
# 7     2/27/12 5:49a Jittenkumarp
# [TAG]  		EIP81401
# [Category]  	New Feature
# [Description]  	Select Redirection After BIOS POST as BootLoader in
# serial redirection, the behaviour is not same as Core8.
# [Files]  		LegacySredir.c, LegacySredir.mak, LegacySredir.sdl,
# LegacySredir_Setup.c, LegacySredir.h ,SerialBootCall.asm,
# SredirBootFail.asm,GRAPHREDIR.ASM, INT10REDIR.ASM, OR_MOD.EQU,
# SREDIR.ASM
# 
# 6     9/20/10 4:09a Rameshr
# [TAG]- EIP 44007
# [Category]-IMPROVEMENT
# [Description]- Invalid PCI COM device list added as Elink. These
# devices will not be used for Redirection.
# [Files]- LegacySredir.mak, LegacySredir.sdl, LegacySredir_Setup.c
# 
# 5     5/03/10 1:55a Rameshr
# Callback function added for read and write function of the Serial Port.
# EIP 37850
# 
# 4     6/29/09 12:11p Rameshr
# Coding Standard and File header updated.
# 
# 3     11/06/08 9:54a Rameshraju
# Guid's updated.
# 
# 2     4/17/07 4:41a Rameshraju
# PCIserial support added
# 
#**********************************************************************
#<AMI_FHDR_START>
#**********************************************************************
#
# Name:         LegacySredir.MAK
#
# Description:  Make file for the Legacy Serial Redirection Module part
#
#**********************************************************************
#<AMI_FHDR_END>

all : LEGACYSREDIR

LEGACYSREDIR : $(BUILD_DIR)\LEGACYSREDIR.mak SerialCallBack LEGACYR_ROM LEGACYSREDIRBin

$(BUILD_DIR)\LEGACYSREDIR.mak : $(LEGACYSREDIR_DIR)\LEGACYSREDIR.cif $(LEGACYSREDIR_BOARD_DIR)\LegacySredir-Board.cif $(LEGACYSREDIR_DIR)\LEGACYSREDIR.mak $(BUILD_RULES)
	$(CIF2MAK) $(LEGACYSREDIR_DIR)\LEGACYSREDIR.cif $(LEGACYSREDIR_BOARD_DIR)\LegacySredir-Board.cif $(CIF2MAK_DEFAULTS)

LEGACYSREDIR_INCLUDES = $(AMIDXELIB) \
                        $(AMICSPLib) \
                        $(BUILD_DIR)\AmiBufferValidationLib.lib

LegacySreDir_OBJECTS = \
$(BUILD_DIR)\$(LEGACYSREDIR_DIR)\LegacySredir.obj \
$(BUILD_DIR)\$(LEGACYSREDIR_DIR)\LegacySmmSredir.obj \
$(BUILD_DIR)\$(LEGACYSREDIR_BOARD_DIR)\LegacySredir_Setup.obj

LEGACYSREDIRBin : $(LEGACYSREDIR_INCLUDES)
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\LEGACYSREDIR.mak all\
		GUID=4A3602BC-1A05-4c82-99B4-588CD2A32CD5 \
		ENTRY_POINT=LegacySredirEntryPoint \
		"CFLAGS=$(CFLAGS) /I$(LEGACYSREDIR_DIR) /D\"INVALID_PCICOM_DEVICELIST=$(InvalidPciComDeviceList)\"" \
        "OBJECTS=$(LegacySreDir_OBJECTS)"\
		TYPE=BS_DRIVER \
		EXT_HEADERS=$(BUILD_DIR)\token.h\
		BINFILE=$(BUILD_DIR)\ROMss.bin \
		SECTION_GUID=9BA21891-7E7D-4e94-B8DF-F4D2D320801C \
		COMPRESS=1\

SerialCallBack: $(BUILD_DIR)\SerialCallback.obj

$(BUILD_DIR)\SerialCallback.obj: $(LEGACYSREDIR_BOARD_DIR)\SerialCallback.asm
	$(ASM) /c /nologo /Fo$(BUILD_DIR)\ /Fl$(BUILD_DIR)\ $(LEGACYSREDIR_BOARD_DIR)\SerialCallback.asm

$(BUILD_DIR)\SerialBootCall.obj: $(LEGACYSREDIR_DIR)\SerialBootCall.asm
    $(ASM) /c /nologo /Fo$(BUILD_DIR)\ /Fl$(BUILD_DIR)\ $(LEGACYSREDIR_DIR)\SerialBootCall.asm

$(BUILD_DIR)\SredirBootFail.obj: $(LEGACYSREDIR_DIR)\SredirBootFail.asm
    $(ASM) /c /nologo /Fo$(BUILD_DIR)\ /Fl$(BUILD_DIR)\ $(LEGACYSREDIR_DIR)\SredirBootFail.asm

LEGACYR_ROM :
	$(PACKOPROM) /o$(BUILD_DIR)\ROMss.bin <<$(BUILD_DIR)\ROMss.inf
[MODULE]
ModuleID = 3
VendorID = 7
DeviceID = 9
File = addon\SREDIR.bin
<<KEEP

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2008, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
