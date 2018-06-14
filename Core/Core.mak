#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Core/Core.mak 78    9/10/12 4:52p Artems $
#
# $Revision: 78 $
#
# $Date: 9/10/12 4:52p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Core.mak $
# 
# 78    9/10/12 4:52p Artems
# [TAG]  		EIP88859
# [Description]  	Build error in GenRomLayout.bat when too many FFS files
# or file name is too long.
# [Files]  		Core.mak Fv.mak
# 
# 77    8/02/12 11:51a Artems
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	Removed FV_SIGNED attribute from NVRAM firmware volume
# [Files]  		Core.mak
# 
# 76    12/20/11 4:07p Artems
# Added token for extended rom layout filename to support new FWbuild
# feature
# 
# 75    11/16/11 9:46a Felixp
# [TAG]  		EIP75724
# [Category]  	Improvement
# [Description]  	Disable delayed environment variable expansion in the
# selectdbg.bat.
# 
# 74    10/28/11 4:14p Felixp
# [TAG]  		EIP70518
# [Category]  	Improvement
# [Description]  	New FV_BB_DESCRIPTOR attribute is added.
# ROM_AREA_VITAL attribute is added to mark that the area is required for
# the firmware recovery to work.
# 
# 73    6/29/11 2:43p Artems
# Removed support for UEFI 2.0
# 
# 72    6/28/11 3:06p Felixp
# 
# 71    6/14/11 5:24p Artems
# EIP 61949: Fixed bug in apriori list generation
# 
# 70    6/13/11 11:56a Artems
# Added NVRAM to list of signed volumes
# 
# 69    5/13/11 4:22p Artems
# Added secure flash update. Added new Error message about incompatible
# token combinations
# Changed Error message format
# 
# 68    3/25/11 9:55a Felixp
# Enhancement: HpkTool command line in the Defaults target is updated 
# to use new TSE SDL token INI_FILE_PATH.
# 
# 67    3/16/11 10:58p Felixp
# CIF2MAK_DEFAULTS SDL token is added(used to be a macro in Core.mak).
# 
# 66    3/15/11 5:20p Felixp
# BUILD_RULES SDL token is created (used to be a macro in Core.mak).
# 
# 65    3/09/11 10:03a Artems
# Fixed bug - handle situation when nested FV is empty
# 
# 64    2/05/11 1:40p Artems
# Added PI 1.0-1.1 support
# Added Nested FV support
# Changed ROM layout structure (field "OFFSET" added)
# 
# 63    11/08/10 5:12p Felixp
# $(BUILD_DIR)\Tokens.c.h target is updated to make sure the file is
# re-built when Token.h changes
# 
# 62    11/05/10 2:24p Felixp
# EDK_INCLUDES macro override is removed
# 
# 61    11/05/10 1:44p Felixp
# Improvement(EIP 46043):
#  The build script that generates firmware volume description files
# (Build\FV_xxx.inf) is updated 
#   to support longer file lists.
# 
# 60    10/01/10 10:56a Felixp
# Error message is printed when Setup Data Layout Override is used in
# UEFI 2.0 mode.
# 
# 59    10/01/10 7:56a Felixp
# Minor improvement of RomLayout.c: comments with area name are added 
# 
# 58    6/20/10 11:49p Felixp
# CIF2MAK_DEFAULTS macro is updated. 
# /lproject.lfo switch is added.
# 
# 57    6/09/10 10:38p Felixp
# Setup Customization Framework Support.
# 
# 56    4/26/10 2:56p Felixp
# 
# 55    4/23/10 5:26p Felixp
# Support for setup defaults in FV_MAIN is added.
# 
# 54    3/05/10 5:30p Felixp
# Enhancement:
# Targets of types GUID_LIBRARY and PEI_GUID_LIBRARY are updated to
# reduce length of the command line.
# 
# 53    2/24/10 2:48p Felixp
# 
# 52    2/04/10 5:12p Felixp
# Auto-generated file Build\AutoId.h is included in Setup.h
# 
# 51    1/26/10 5:03p Felixp
# Support for generation of the DXE apriori file is added. 
# The list of FFS files that should be added to the DXE a priori list is
# specified 
# as a part of FV descriptor using DXE_APRIORI_FILE_LIST parameter.
# 
# 50    1/21/10 3:54p Felixp
# Font file target $(BUILD_DIR)\Font.ffs is replaced with pseudo-target
# FontFfs to always recreate the file.
# The /F 2.1 switch is added for UEFI 2.1 builds to create UEFI 2.1 font
# pack.
# 
# 49    12/17/09 2:29p Felixp
# Minor updates:
# 1. Target name and UEFI version are printed at the end of the build
# process
# 2. Print standard message about successful build completion for a
# single component build(EIP 32658).
# 
# 48    11/24/09 11:33a Felixp
# AmiProtocolLib build command is updated to pass value of the
# DEFAULT_LANGUAGE.
# 
# 47    10/09/09 5:11p Felixp
# UEFI 2.1-related changes.
# 
# 46    8/27/09 11:47a Felixp
# Generate PeiSym.lst only if PEI Debugger is enabled
# 
# 42    7/01/09 1:29p Felixp
# Tokens.c target: add dependency from Token.h 
# ROM Layout generation: do not describe ROM Holes in FwBuild script
# (this is not supported by some versions of FwBuild).
# 
# 40    5/22/09 6:16p Felixp
# FWBUILD flags updated to generate AMI Debugger listing file
# 
# 38    5/08/09 6:05p Felixp
# - support for ROM holes (FFS files with fixed addresses)
# - ROM_AREA_FV_BOOT attributes is removed
# - NVRAM back up area is defined using eLink 
#   (hard coded entry in the ROM script is removed)
# 
# 37    5/08/09 12:15a Felixp
# Ifrastructure to simplify ROM layout customization(EIP 18426).
# Build process and source code that deals with ROM layout 
# is updated in order to simplify ROM layout customization.
# 
# 36    5/04/09 2:00p Felixp
# Support for alternative font data packaging(EIP 18489) is added.
# Description: Build process is updated to provide framework that can be
# used to 
# overwrite default packaging of the font data.
# Two new SDL tokens are created:
# "LANGUAGE_FONT_LIST" - Space separated list of language identifiers. 
# The fonts for these languages will be included into the ROM image.
# "STRING_PACK_POST_PROCESS_COMMAND" - The token defines command 
# used in rules.mak to perform additional processing of 
# module's HII string pack ($(BUILD_DIR)$(NAME)Str.hpk) 
# after standard processing (performed by StrGather utility) is
# completed.
# 
# 35    3/05/09 9:46a Felixp
# Bug fix: Problem with target specific builds (build.bat target=X).
# Description: The target specific build didn't work for modules that 
#   use Setup.h without prior full build.
# Symptoms: Build fails with "SetupDefinitions.h not found" error.
# Details: Core make files are updated to add target that 
#   generates SetupDefinitions.h into the list of dependents of the top 
#   level target being built (original code only did it for target
# "all").
# 
# 34    11/03/08 10:31a Felixp
# Current debug mode is printed at the end of the build process.
# 
# 32    10/22/08 3:56p Felixp
# Some of the build process warnings are eliminated
# 
# 30    10/10/08 9:43a Felixp
# Dependency list for $(BUILD_DIR)\SetupDefinitions.h target is created 
# (the file used to be built during every build).
# 
# 29    10/10/08 9:36a Felixp
#  - AFTER_ROM target was not in the list of dependents of the target all
#  - Delete ROM image at the beginning of the build process
# 
# 28    10/09/08 11:54a Felixp
# Fault tolerant NVRAM update support
# 
# 27    9/05/07 1:42a Felixp
# 1. Debugging-related tokens updated to use boolean tokens instead of
# enumeration
# 2. Support for ROM_IMAGE_SIZE is added.
# 
# 26    9/04/07 11:38a Felixp
# Two pseudo-targets AFTER_FV and AFTER_ROM are added. 
# These targets can be used to add custom build steps towards the end of
# the build process.
# AFTER_FV - Use this target to execute your custom build steps after the
# firmware volumes are built and before the final ROM image is created.
# AFTER_ROM - Use this target to execute your custom build steps after
# the final ROM image is created.
# For example, to hook up custom target X to be executed at the end of
# the build process add
# AFTER_ROM : X  or AFTER_FV : X
# into a make file, which defines target X.
# 
# 25    8/31/07 9:33a Felixp
# The way FV_NVRAM created is changed:
# 1. FV_NVRAM is now a standard (FFS-based) FV.
# 2. NVRAM image is encapsulated into FFS file (NVRAM.ffs)
# 3. NVRAM image (NVRAM.bin) is no longer blank. It is expected that it
# will be generated by one of the modules (currently AMITSE).
# 
# 22    3/18/07 12:45p Felixp
# FWBUILD is used to dump ROM content at the end of the build process
# 
# 21    12/28/06 6:37p Felixp
# Added message at the end of the build process to display ROM file name
# and build mode.
# 
# 20    12/27/06 7:32a Felixp
# Updated to support new version of debugger that can keep PEI binaries
# in FV_MAIN
# 
# 19    12/07/06 10:23a Pavell
# Moved ITK processing to ITK.mak
# 
# 15    9/26/06 9:01a Felixp
# Multilanguage support added. New FontTool is required.
# 
# 13    8/24/06 9:06a Felixp
# Preliminary x64 support (work in progress)
# 
# 11    6/21/06 5:44p Felixp
# ProtocolLib renamed to AmiProtocolLib
# PpiLib renamed to AmiPpiLib
# 
# 8     1/17/06 11:27a Felixp
# Final ROM image generation altered: exact addresses for FV_MAIN, FV_BB
# and NVRAM  used.
# 
# 7     8/22/05 7:03p Felixp
# AMI Debugger support
# 
# 6     7/22/05 2:20a Felixp
#  NVRAM enclosed into Firmware volume
# 
# 5     6/17/05 3:24p Felixp
# Setup support: Setup Map generation commands added
# 
# 4     6/16/05 10:42a Felixp
# 1. Tokens.c added. It has variables representing SDL tokens.
# 2. InitList.c extended to support 2 init lists
# 
# 3     2/11/05 5:33p Felixp
# CORE_BIN_DIR definition removed
# 
# 2     2/04/05 9:19a Felixp
# $(AMI_ROM) value is saved to file $(BUILD_DIR)\amiromname.txt
# The file is used by the Build.mak to implement Clean command
# 
# 3     1/25/05 12:53p Felixp
# Check for validity of DEBUG_MODE added
# 
# 2     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 9     12/03/04 7:26p Felixp
# CIF2MAK version 2.0
# 
# 7     11/18/04 6:25p Felixp
# support for 2 FVs added
# 
# 6     7/26/04 4:41p Yakovlevs
# 
# 4     1/13/04 12:18p Felixp
# merge64 command line switch /s added to launch the utility in silent
# mode
# 
# 3     1/08/04 4:46p Felixp
# comments improved
# 
# 2     12/09/03 11:50a Felixp
# Comments changed for the better HelpBuiler compatibility.
# 
# 1     12/05/03 4:15p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Core.mak
#
# Description:	Makefile that builds the BIOS.
# Prerequisites(set up by the Build.mak): 
#	- BUILD_DIR macros is set
#	- $(BUILD_DIR) directory exists
#	- $(BUILD_DIR)\token.mak file generated by AMISDL exists
#
# Core.mak includes make files for all other modules in the project
# Makefiles of individual modules has to add their targets 
# to the dependents list of the target ALL.
# Core.mak also defines how to create a final rom image (AMI_ROM).
#
#<AMI_FHDR_END>
#**********************************************************************
!INCLUDE $(BUILD_DIR)\token.mak
!INCLUDE Core\Languages.mak

!IF $(EFI_SPECIFICATION_VERSION) <= 0x20000
ERROR_MESSAGE=UEFI 2.0 mode is not supported.^
To resolve the problem, increase the value of EFI_SPECIFICATION_VERSION
!ERROR $(ERROR_MESSAGE)
!ENDIF

!IF "$(CoreSrc_SUPPORT)"!="1"
ERROR_MESSAGE=Core Sources are required for build the project
!ERROR $(ERROR_MESSAGE)
!ENDIF

BUILD_DEFAULTS = \
	"EXT_OBJS=$**" BUILD_ROOT=$(BUILD_DIR) PROJECT_DIR=$(PROJECT_DIR)
NO_EXT_OBJS_BUILD_DEFAULTS = \
	BUILD_ROOT=$(BUILD_DIR) PROJECT_DIR=$(PROJECT_DIR)

!IF "$(TARGET)"!="PREPARE"
$(TARGET) : PREPARE
!ENDIF

$(BUILD_DIR)\Core.mak : $(CORE_DIR)\$(@B).cif $(CORE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CORE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\Tokens.c.h : $(LIBRARY_DIR)\Tokens.c $(BUILD_DIR)\Core.mak $(BUILD_DIR)\token.h
    $(SILENT)copy << $(BUILD_DIR)\Tokens.c.h  > NUL
#include <$(LIBRARY_DIR)\Tokens.c>
<<KEEP

$(BUILD_DIR)\AmiProtocolLib.lib : Include\Protocol\*.h $(BUILD_DIR)\Tokens.c.h
	$(MAKE) /$(MAKEFLAGS) $(NO_EXT_OBJS_BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Core.mak all\
		TYPE=GUID_LIBRARY NAME=$(@B)\
		"HEADERS=Include\Protocol\^*.h $(BUILD_DIR)\Tokens.c.h"\
		"MY_DEFINES=/D_PIDEController_ /DDEFAULT_LANGUAGE_CODE=$(DEFAULT_LANGUAGE)"

$(BUILD_DIR)\AmiPpiLib.lib : Include\Ppi\*.h $(BUILD_DIR)\Tokens.c.h
	$(MAKE) /$(MAKEFLAGS) $(NO_EXT_OBJS_BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Core.mak all\
		TYPE=PEI_GUID_LIBRARY NAME=$(@B)\
		"HEADERS=Include\Ppi\^*.h $(BUILD_DIR)\Tokens.c.h"

PREPARE :
	$(ECHO) $(AMI_ROM) > $(BUILD_DIR)\amiromname.txt
	-@if exist $(BUILD_DIR)\targets.mak $(DEL) $(BUILD_DIR)\targets.mak
    -@if exist $(AMI_ROM) $(DEL) $(AMI_ROM)
	$(FONT_TOOL) /S /T $(BUILD_DIR)\font.tmp
#create list of debuggable modules
!IF "$(SELECTIVE_DEBUGGING_SUPPORT)"=="1" && "$(SELECTIVE_DEBUGGING)"!=""
#The first IF clause is needed to be able to use
#ELSEIF in the for loop below
	$(SILENT)type << >$(BUILD_DIR)\selectdbg.bat
@echo off
setlocal disabledelayedexpansion
echo !IF 0 > $(BUILD_DIR)\selectivedebugmodules.mak
for %%i in ($(SELECTIVE_DEBUGGING)) do (
echo !ELSEIF "$$(NAME)"=="%%i" >> $(BUILD_DIR)\selectivedebugmodules.mak
echo SELECTIVE_DEBUG_ENABLE=1 >> $(BUILD_DIR)\selectivedebugmodules.mak
)
echo !ELSE >> $(BUILD_DIR)\selectivedebugmodules.mak
echo SELECTIVE_DEBUG_ENABLE=0 >> $(BUILD_DIR)\selectivedebugmodules.mak
echo !ENDIF >> $(BUILD_DIR)\selectivedebugmodules.mak
<<
    $(SILENT)$(BUILD_DIR)\selectdbg.bat
!ENDIF

PREPARE : $(BUILD_DIR)\SetupDefinitions.h
!IF "$(Setup_SUPPORT)"=="1"
# $(BUILD_DIR)\AUTOID.h target is defined in Setup.mak
PREPARE : $(BUILD_DIR)\AUTOID.h
!ENDIF
PREPARE : $(BUILD_DIR)\RomLayout.ini

$(BUILD_DIR)\SetupDefinitions.h : $(SETUP_DEFINITIONS) $(BUILD_DIR)\token.mak Core\Core.mak
	type << >$(BUILD_DIR)\SetupDefinitions.h
!IF "$(SETUP_DEFINITIONS)"!=""
#include<$(SETUP_DEFINITIONS: =>^
#include<)>
!ENDIF
<<
	type << >$(BUILD_DIR)\ControlDefinitions.h
!IF "$(SETUP_DEFINITIONS)"!=""
#define CONTROL_DEFINITION
#include<SetupDefinitions.h>
#undef CONTROL_DEFINITION
#define CONTROLS_ARE_DEFINED
!ENDIF
<<
	type << >$(BUILD_DIR)\GenericSetupDataDefinition.h
#pragma pack(1)
typedef struct{
  UINT8 Numlock;
  #define SETUP_DATA_DEFINITION
  #include <SetupDefinitions.h>
  #undef SETUP_DATA_DEFINITION
} SETUP_DATA;
#pragma pack()
<<
	type << >$(BUILD_DIR)\SetupDataDefinition.h
!IF "$(SETUP_DATA_LAYOUT_OVERRIDE_HEADER)"==""
#include<GenericSetupDataDefinition.h>
!ELSE
!IF $(EFI_SPECIFICATION_VERSION) < 0x2000A
!MESSAGE Setup Data Layout Override is not supported in UEFI 2.0 mode.
!MESSAGE To disable Setup Data Layout Override, set SETUP_DATA_LAYOUT_OVERRIDE_SUPPORT SDL token to "Off".
!MESSAGE To switch to UEFI 2.1 mode, set EFI_SPECIFICATION_VERSION SDL token to 0x2000A.
!ERROR Unsupported configuration.
!ENDIF
!IF !EXIST($(SETUP_DATA_LAYOUT_OVERRIDE_HEADER))
!ERROR Setup Data Layout Override header file "$(SETUP_DATA_LAYOUT_OVERRIDE_HEADER)" defined by the SETUP_DATA_LAYOUT_OVERRIDE_HEADER SDL token is not found.
!ENDIF
#ifndef VFRCOMPILE
#include<$(SETUP_DATA_LAYOUT_OVERRIDE_HEADER)>
#else
#include<GenericSetupDataDefinition.h>
#endif
!ENDIF
!IF "$(PROJECT_SETUP_HEADER)"!=""
!IF !EXIST($(PROJECT_SETUP_HEADER))
!ERROR Project specific setup header file "$(PROJECT_SETUP_HEADER)" defined by the PROJECT_SETUP_HEADER SDL token is not found.
!ENDIF
#include<$(PROJECT_SETUP_HEADER)>
!ENDIF
<<


CC_TARGET=$(SILENT)maketarget $(BUILD_DIR)\targets.mak $(BUILD_DIR) $$(CC) $$(EXTRA_CFLAGS)
ASM_TARGET=$(SILENT)maketarget $(BUILD_DIR)\targets.mak $(BUILD_DIR) $$(ASM) $$(EXTRA_AFLAGS)
CC=$(CC_TARGET)

!INCLUDE $(BUILD_DIR)\module.mak

#NOTE: starting from Core 4.6.3.6 
# generation of the Firmware Volumes (FV) is no longer a separate build step.
# All FV and the final ROM image are created by the single ROM target command.
# COMPATIBILITY IMPLICATION: *.fv files are no longer available during execution
# of the AFTER_FV target commands.
# Targets BEFORE_FV, FV, and AFTER_FV are now equivalent.
# All three of them are preserved for backward compatibility
# (otherwise just one would be enough).
all : BEFORE_FV FV AFTER_FV ROM AFTER_ROM

BEFORE_FV : FontFfs $(BUILD_DIR)\NVRAM.ffs

FontFfs :
    $(FONT_TOOL) /IL $(LANGUAGE_FONT_LIST) /T $(BUILD_DIR)\font.tmp
    $(FONT_TOOL)\
!IF $(EFI_SPECIFICATION_VERSION) >= 0x2000A
        /F 2.1\
!ENDIF
	    /O $(BUILD_DIR)\font.out /T $(BUILD_DIR)\font.tmp
	$(AMIRC) /s /o$(BUILD_DIR)\font.sec $(BUILD_DIR)\font.out
	$(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
		NAME=$(@B) \
		BUILD_DIR=$(BUILD_DIR) \
#Do not change this GUID. HIIDB uses this GUID to locate font file
		GUID=DAC2B117-B5FB-4964-A312-0DCC77061B9B \
		TYPE=EFI_FV_FILETYPE_FREEFORM \
		FFSFILE=$(BUILD_DIR)\Font.ffs COMPRESS=1 \
		SECTION=font.sec \

# create NVRAM.FFS
$(BUILD_DIR)\NVRAM.FFS : $(BUILD_DIR)\NVRAM.bin
	 $(MAKE) /f Core\FFS.mak BUILD_DIR=$(BUILD_DIR) \
	    GUID=CEF5B9A3-476D-497f-9FDC-E98143E0422C \
	    TYPE=EFI_FV_FILETYPE_RAW FFS_CHECKSUM=0\
	    RAWFILE=$(BUILD_DIR)\NVRAM.bin \
        FFSFILE=$(BUILD_DIR)\NVRAM.FFS COMPRESS=0 NAME=NVRAM

# Don't change this GUID; NVRAM driver expects it
# // {9221315B-30BB-46b5-813E-1B1BF4712BD3}
#define SETUP_DEFAULTS_FFS_GUID { 0x9221315b, 0x30bb, 0x46b5, { 0x81, 0x3e, 0x1b, 0x1b, 0xf4, 0x71, 0x2b, 0xd3 } }
SETUP_DEFAULTS_FFS_GUID=9221315B-30BB-46b5-813E-1B1BF4712BD3

!IF "$(SETUP_DEFAULTS_IN_FV_MAIN)"=="1"
BEFORE_FV : Defaults

Defaults:
    $(HPKTOOL) -i$(IFR_DIR_LIST: = -i)\
!IF "$(INI_FILE_PATH)"!=""
        -f$(INI_FILE_PATH)\
!ELSEIF $(EFI_SPECIFICATION_VERSION) > 0x20000
        -f$(TSEBIN_DIR)\uefisetup.ini\
!ELSE
        -f$(TSEBIN_DIR)\setup.ini\
!ENDIF
        -o$(BUILD_DIR)\tmp.asm -do$(BUILD_DIR)\Defaults.bin\
!IF "$(MANUFACTURING_MODE_SUPPORT)"=="1"
        -dm\
!ENDIF
        -r -de$(FLASH_ERASE_POLARITY) -dl$(DEFAULT_LANGUAGE)\
        -dg4599D26F-1A11-49b8-B91F-858745CFF824\
        -h$(AMITSE_HPK_FILE_ORDER)
    -$(DEL) pkgtmp*.tmp
	$(MAKE) /f Core\FFS.mak BUILD_DIR=$(BUILD_DIR)\
        GUID=$(SETUP_DEFAULTS_FFS_GUID)\
	    TYPE=EFI_FV_FILETYPE_FREEFORM\
	    BINFILE=$(BUILD_DIR)\Defaults.bin \
        FFSFILE=$(BUILD_DIR)\Defaults.FFS COMPRESS=1 NAME=Defaults
!ENDIF

#**********************************************************************
#<AMI_GHDR_START>
# Name:	AMI_ROM
#
# Description:	
#	BIOS ROM image (AMI_ROM) includes FV_MAIN firmware volume 
#	and blank NVRAM area.
#	FV.MAK is used to create FV_MAIN
#	Prerequisites:
#		- Core.mak Prerequisites
#		The following macros must be defined:
#		- FV_MAIN - List of Base Names (file name w/o extension)
#		  for the FFS files to be included in the Firmware Volume
#		  This macros is getting generated by 
#		  the AMISDL from the corresponding eLink defined in Core.sdl
#		  To add module to FV_MAIN, module's SDL file has to define eLink
#		  with the name set to base name of the module's FFS binary 
#		  and the parent set to FV_MAIN.
#		The following macros are expected to be defined by the SDL file
#		of the Flash Module:
#		-FLASH_SIZE - Size of the Flash Device in bytes
#		-FLASH_BLOCK_SIZE - Size of the Flash Device Block
#		-FLASH_ERASE_POLARITY - Flash Device Erase Polarity
#		-FV_MAIN_BASE - Base Address of the FV_MAIN
#		-FV_MAIN_BLOCKS - Number of Blocks occupied by the FV_MAIN
#		-NVRAM_SIZE - Size of NVRAM area
#
#<AMI_GHDR_END>
#**********************************************************************
#Nothing to do here.
# The FV are created by the ROM target command
#This target is here for backward compatibility.
# See also comment above the all target description
FV :

#Nothing to do here.
#This target that can be used by OEM modules for any custom
#build steps that need to be performed after FV generation and prior to ROM generation.

#-----Long e-Link handling example--------------
#uncomment the following code to solve the problem from EIP 88859
#$(BUILD_DIR)\FvMainFfsList.mak : $(BUILD_DIR)\token.mak
#  @copy << $(BUILD_DIR)\FvMainFfsList.mak
#FILE_LIST=$(FV_MAIN)
#<<KEEP
#-----Long e-Link handling example end----------

AFTER_FV:

FV_NVRAM_DESCRIPTOR=FV(\
name=FV_NVRAM, address=$(NVRAM_ADDRESS),\
offset=$(NVRAM_ADDRESS)-$(FLASH_BASE),\
size=$(NVRAM_SIZE), file_list=$(BUILD_DIR)\NVRAM.FFS\
)
FV_MAIN_DESCRIPTOR=FV(\
name=FV_MAIN, address=$(FV_MAIN_BASE),\
offset=$(FV_MAIN_BASE)-$(FLASH_BASE),\
size=$(FV_MAIN_BLOCKS)*$(FLASH_BLOCK_SIZE),\
!IF "$(FV_MAIN_NESTED)"!=""
file_list=$(BUILD_DIR)\FV_MAIN_NESTED.ffs $(FV_MAIN),\
attr=ROM_AREA_FV_PEI+ROM_AREA_FV_DXE+ROM_AREA_FV_NFV_PRESENT+ROM_AREA_FV_SIGNED\
!ELSE
file_list=$(FV_MAIN),\
#-----Long e-Link handling example--------------
#uncomment the following string below to solve the problem from EIP 88859
#file_list_file=$(BUILD_DIR)\FvMainFfsList.mak,\
#-----Long e-Link handling example end----------
attr=ROM_AREA_FV_PEI+ROM_AREA_FV_DXE+ROM_AREA_FV_SIGNED\
!ENDIF
)

!IF "$(FV_MAIN_NESTED)"!=""
FV_MAIN_NESTED_DESCRIPTOR=FV(\
name=FV_MAIN_NESTED, nested=1,\
file_list=$(FV_MAIN_NESTED)\
)
ROM_IMAGE=$(ROM_IMAGE) $(FV_MAIN_NESTED_DESCRIPTOR)
!ENDIF

FV_BB_DESCRIPTOR=FV(\
name=FV_BB, address=$(FV_BB_BASE),\
offset=$(FV_BB_BASE)-$(FLASH_BASE),\
size=$(FV_BB_BLOCKS)*$(FLASH_BLOCK_SIZE),\
file_list=$(FV_BB), attr=ROM_AREA_FV_PEI+ROM_AREA_FV_DXE+ROM_AREA_FV_SIGNED+ROM_AREA_VITAL\
)
NVRAM_BACKUP_DESCRIPTOR=HOLE(\
name=NVRAM_BACKUP, address=$(NVRAM_BACKUP_ADDRESS),\
offset=$(NVRAM_BACKUP_ADDRESS)-$(FLASH_BASE),\
size=$(NVRAM_SIZE)\
)

#-----Long e-Link handling example--------------
#uncomment the following string below and use it instead of generic one to solve the problem from EIP 88859
#$(BUILD_DIR)\RomLayout.ini : $(BUILD_DIR)\token.mak Core\Core.mak Core\Fv.mak $(BUILD_DIR)\FvMainFfsList.mak
#-----Long e-Link handling example end----------
$(BUILD_DIR)\RomLayout.ini : $(BUILD_DIR)\token.mak Core\Core.mak Core\Fv.mak
	@echo all : > $(BUILD_DIR)\beforefv.mak
    $(SILENT)copy << $(BUILD_DIR)\RomLayout.ini  > NUL
output
	BIOS($(AMI_ROM))
end
group BIOS
!IF "$(ROM_IMAGE_SIZE)"!=""
    size=$(ROM_IMAGE_SIZE)
!ELSE
    size=$(FLASH_SIZE)
!ENDIF
    upper=0xFFFFFFFF
    components
<<KEEP
    $(SILENT)copy << $(BUILD_DIR)\RomLayout.c > NUL
#include <RomLayout.h>
#pragma pack(1)
ROM_AREA RomLayout[] = {
<<KEEP
    $(SILENT)copy << $(BUILD_DIR)\GenRomLayout.bat > NUL
@echo off
set BUILD_DIR=$(BUILD_DIR)
set ERASE_POLARITY=$(FLASH_ERASE_POLARITY)
set BLOCK_SIZE=$(FLASH_BLOCK_SIZE)
set ECHO=$(ECHO)
set MAKE=$(MAKE)
set chunks=0
for /f "tokens=1 delims=( " %%a in (%1) do @(
    set /A chunks+=1
)
set rchunks=0
for /f "tokens=1* delims=( " %%a in (%1) do @(
    set /A rchunks+=1
    for /f "tokens=1* delims=)" %%c in ("%%b") do @(
        call $(BUILD_DIR)\GenFvDesc.bat "type=%%a,%%c"
        if not exist $(BUILD_DIR)\RomLayout.ini goto :eof
    )
)
if not %chunks%==%rchunks% (
    echo ERROR: file list too long
    goto error
)
goto :eof
:error
del $(BUILD_DIR)\RomLayout.ini
<<KEEP
    $(SILENT)copy << $(BUILD_DIR)\GenFvDesc.bat > NUL
@echo off
setlocal
for /f "tokens=1-10 delims=," %%a in (%*) do (
    if NOT "%%a"=="" set %%a
    if NOT "%%b"=="" set %%b
    if NOT "%%c"=="" set %%c
    if NOT "%%d"=="" set %%d
    if NOT "%%e"=="" set %%e
    if NOT "%%f"=="" set %%f
    if NOT "%%g"=="" set %%g
    if NOT "%%h"=="" set %%h
    if NOT "%%i"=="" set %%i
    if NOT "%%j"=="" set %%j
)
if /I "%attr%"=="" set attr=0
if not "%NAME%"=="" echo     // %NAME% >> $(BUILD_DIR)\RomLayout.c
if /I %type%==FV (
!IF !$(BRIEF)
    echo FV: NAME="%NAME%" ADDRESS="%ADDRESS%" SIZE="%SIZE%"
!ENDIF
    if /I "%nested%"=="1" (
        if "%ADDRESS%"=="" set ADDRESS=0
        set GLOBAL_COMPRESSION=0
    ) 
    if "%SIZE%"=="" (
        set BLOCKS=AUTO
    ) else (
        set /A BLOCKS=%size%/%BLOCK_SIZE%
    )

    $(MAKE) -f Core\fv.mak PI_SPECIFICATION_VERSION=$(PI_SPECIFICATION_VERSION)
    if not exist $(BUILD_DIR)\%NAME%.inf goto error
    if /I not "%nested%"=="1" (
        echo     file %NAME% FvDesc=$(BUILD_DIR)\%NAME%.inf lower=%ADDRESS% end >> $(BUILD_DIR)\RomLayout.ini
        echo     {%ADDRESS%, %OFFSET%, %SIZE%, RomAreaTypeFv, %attr%}, >> $(BUILD_DIR)\RomLayout.c
    ) else (
        $(MAKE) -f Core\ffs.mak TYPE=EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE FV_DESC=$(BUILD_DIR)\%NAME%.inf BUILD_DIR=$(BUILD_DIR) GUID=AE717C2F-1A42-4f2b-8861-78B79CA07E07 FFSFILE=$(BUILD_DIR)\%NAME%.ffs NAME=%NAME% COMPRESS=1
    )
)else if /I %type%==file (
!IF !$(BRIEF)
    echo File: NAME="%NAME%" ADDRESS="%ADDRESS%" FILE="%FILE%"
!ENDIF
    echo         file %NAME% binfile=%FILE% lower=%ADDRESS% end >> $(BUILD_DIR)\RomLayout.ini
    echo     {%ADDRESS%, %OFFSET%, %SIZE%, RomAreaTypeRaw, %attr%}, >> $(BUILD_DIR)\RomLayout.c
)else if /I %type%==hole (
!IF !$(BRIEF)
    echo Hole: NAME="%NAME%" ADDRESS="%ADDRESS%" SIZE="%SIZE%"
!ENDIF
    echo     {%ADDRESS%, %OFFSET%, %SIZE%, RomAreaTypeRaw, %attr%}, >> $(BUILD_DIR)\RomLayout.c
)else (
    echo ERROR: Invalid ROM_IMAGE element "%type%".
    goto error
)
if "%ADDRESS%"=="" (
    echo ERROR: Invalid ROM_IMAGE element. Address is not defined for element "%type%(%NAME% %FILE%)". 
    goto error
)
endlocal
goto :eof
:error
del $(BUILD_DIR)\RomLayout.ini
<<KEEP
    $(SILENT)copy << $(BUILD_DIR)\GenFvList.bat > NUL
@echo off
echo %3 >> %2
for /f %%f in (%1) do @(
	for /f "tokens=1,2 delims=:" %%i in ("%%f") do @(
		if /I %%i==TYPE (
			echo %%i = %%j >> %2
		) else if /I %%i==LOCATION (
	        echo %%i = %%j >> %2
    	) else if /I %%i==SIZE (
			echo %%i = %%j >> %2
		) else (
            for /F "delims=\" %%y in ("%%i") do (
                if 1==0 (
                    echo EFI_FILE_NAME = %%i >> %2
                ) else if /I %%y==$(BUILD_DIR) (
                    if not exist %%~dpni__.pkg (
                        echo EFI_FILE_NAME = %%i >> %2
                    ) else (
                        echo EFI_FILE_NAME = %%~dpni__.pkg >> %2						        
                    )
                ) else (
                    echo EFI_FILE_NAME = %%i >> %2
                )
            )
		)
	)
)
<<KEEP
	$(SILENT)Build\GenRomLayout.bat <<$(BUILD_DIR)\RomLayout.txt
$(ROM_IMAGE:)=^)^
)
<<KEEP
    @if not exist $(BUILD_DIR)\RomLayout.ini @copy file_that_does_not_exist x > NUL
    $(ECHO)     end >> $(BUILD_DIR)\RomLayout.ini
    $(ECHO) end >> $(BUILD_DIR)\RomLayout.ini
    $(ECHO)     {0, 0, 0, 0} >> $(BUILD_DIR)\RomLayout.c
    $(ECHO) }; >> $(BUILD_DIR)\RomLayout.c

!IF $(PI_SPECIFICATION_VERSION)>=0x00010000
FWBUILD_FLAGS = $(FWBUILD_FLAGS) /p 1.0
!ENDIF
FWBUILD_FLAGS = $(FWBUILD_FLAGS) /d /c $(BUILD_DIR)\RomLayout.ini /m $(ROM_LAYOUT_EX)
!IF "$(AMI_DEBUGGER_SUPPORT)"=="1" && "$(PeiDebugger_SUPPORT)"=="1"
FWBUILD_FLAGS = $(FWBUILD_FLAGS) /b $(BUILD_DIR)\peisym.lst
!ENDIF

# create a final ROM image
ROM:
    $(MAKE) /$(MAKEFLAGS) /f $(BUILD_DIR)\beforefv.mak all
	@echo all : > $(BUILD_DIR)\beforefv.mak
    $(FWBUILD) $(AMI_ROM) $(FWBUILD_FLAGS)

!IF "$(DEBUG_MODE)"=="1"
DEBUG_MODE_STRING=on
!ELSE
DEBUG_MODE_STRING=off
!ENDIF

!IF $(EFI_SPECIFICATION_VERSION)==0x1000A
EFI_VERSION_STRING=1.10
!ELSEIF $(EFI_SPECIFICATION_VERSION)==0x20000
EFI_VERSION_STRING=2.0
!ELSEIF $(EFI_SPECIFICATION_VERSION)==0x2000A
EFI_VERSION_STRING=2.1
!ELSEIF $(EFI_SPECIFICATION_VERSION)==0x20014
EFI_VERSION_STRING=2.2
!ELSEIF $(EFI_SPECIFICATION_VERSION)==0x2001E
EFI_VERSION_STRING=2.3
!ELSEIF $(EFI_SPECIFICATION_VERSION)==0x2001F
EFI_VERSION_STRING=2.3.1
!ENDIF
!IF $(PI_SPECIFICATION_VERSION) < 0x00010000
PI_VERSION_STRING=0.91
!ELSEIF $(PI_SPECIFICATION_VERSION) == 0x00010000
PI_VERSION_STRING=1.0
!ELSEIF $(PI_SPECIFICATION_VERSION) == 0x0001000A
PI_VERSION_STRING=1.1
!ELSEIF $(PI_SPECIFICATION_VERSION) == 0x00010014
PI_VERSION_STRING=1.2
!ENDIF

#This is target that can be used by OEM modules for any custom
#build steps that need to be performed after ROM generation.
AFTER_ROM:
!IF $(BRIEF)
#in brief mode ROM info is printed during ROM file generation
#    $(FWBUILD) $(AMI_ROM) /s
!ELSE
    $(FWBUILD) $(AMI_ROM) /v
!ENDIF

!IF "$(TARGET)"!="END"
$(TARGET) : END
!ENDIF
#IMPORTANT: This has to be the last step of the build process.
#Any build process customizations must happen prior to this point
#Use AFTER_ROM or AFTER_FV targets for any custom build steps.
END:
    @echo TARGET: $(TARGET). UEFI Version: $(EFI_VERSION_STRING). PI Version: $(PI_VERSION_STRING)
    @echo ROM IMAGE: $(AMI_ROM). ROM TYPE: $(PROCESSOR). DEBUG MODE: $(DEBUG_MODE_STRING)
    @echo All output modules were successfully built.
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
