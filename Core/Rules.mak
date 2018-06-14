#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/BIN/Core/Rules.mak 83    11/03/11 2:21p Felixp $
#
# $Revision: 83 $
#
# $Date: 11/03/11 2:21p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Rules.mak $
# 
# 83    11/03/11 2:21p Felixp
# [TAG]  		EIP61003
# [Category]  	Improvement
# [Description]  	Support for setting of the debug parameters when
# DEBUG_MODE is 0.
# 
# 82    11/03/11 12:27p Felixp
# [TAG]  		EIP74554 
# [Category]  	Improvement
# [Description]  	Support generation of the assembly listing file.
# [Files]  		Core.sdl, Rules.mak
# 
# 81    10/27/11 3:27p Felixp
# Improvement:
# Make sure all externally callable targets have dependency from the
# $(DIRS), 
# which is a list of targets that create intermediate file directories.
# 
# 80    6/27/11 5:36p Felixp
# 1. DUAL_INSTANCE_LIBRARIES_BUILD_DIR macro is added.
# 2. Use PEI instance of AmiCspLib when PEI components are built
# 
# 79    6/16/11 9:12a Felixp
# Enhancements: 
# 1. Make sure $(BUILD_DIR)\$(NAME)CcOptions.txt is regenerated during
# every build.
# 2. Define SMM_BUILD macro during the compilation of PI SMM drivers (SMM
# and Combined DXE/SMM).
# 
# 78    2/05/11 1:44p Artems
# Added PI 1.1 support (SMM driver build rules)
# 
# 77    11/17/10 11:09a Felixp
# New Rules.mak parameter MY_SDBS is added. 
# It can be used to extend list of module's SDB files. 
# The list of module's SDB files is a concatenation of the 
# list of SDB files generated from module's UNI files and MY_SDB files. 
# The MY_SDB macro has to be in the format -db <sdb-file>. 
# For example, "MY_SDBS=-db $(BUILD_DIR)\S1.sdb -db $(BUILD_DIR)\S1.sdb"
# 
# 76    6/09/10 11:04p Felixp
# Command to delete .i files after VFR processing is removed.
# It is no longer needed because updated VFR compiler is no longer
# placing 
# .i files into the project root directory.
# 
# 75    6/09/10 10:44p Felixp
# New build type RESOURCES is added to rules.mak. 
# The type is used to build only HII resources of the component.
# 
# 74    5/07/10 12:41p Felixp
# PEI_PHASE and DXE_PAHSE macros are renamed to PEI_BUILD and DXE_BUILD
# 
# 73    5/07/10 12:22p Felixp
# Predefined PEI_PHASE and DXE_PHASE macros are added.
# The macros can be used in the in the source code that used in PEI and
# DXE to 
# implemented phase specific behavior.
# 
# 72    3/19/10 6:02p Felixp
# Support USE_CC_RESPONSE_FILE for GUID_LIBRARY builds.
# 
# 71    3/18/10 5:49p Felixp
# Bug fix in USE_LINKER_RESPONSE_FILE processing
# 
# 70    3/18/10 5:23p Felixp
# Bug fix in USE_CC_RESPONSE_FILE processing
# 
# 69    3/18/10 5:12p Felixp
# New SDL token USE_CC_RESPONSE_FILE is added.
# When this token is enabled, all C-compiler(CC) options are passed via
# the response file. 
# The token should be enabled when the length of the CC command line
# exceeds 
# the maximum supported limit. The token is disabled by default.
# 
# 68    2/23/10 8:28p Felixp
# String Override Support(EIP 32696).
# Rules.mak is updated to run .uni file processing utility (StrGather)
# with the special -override flag. The flag instructs the utility to use
# last instance of the string, if more than one instance is available. 
# NOTE: This feature requires new version of the Tools module
# (4.5.5_Tools_30 or newer).
# 
# 67    11/13/09 5:05p Felixp
# Don't generate debug information for components of type BINARY.
# 
# 66    11/06/09 9:24a Felixp
# 1. PE32-based .bin Files Support
#   New built type BINARY is added. 
#   The type is used to generate FFS files containing raw binary data. 
#   The binary file is created from the PE32/PE32+ file by stripping the
# headers. 
#   NOTE: This feature requires new version of the Tools module. 
# 2. New SDL token USE_LINKER_RESPONSE_FILE is added.
#   When this token is enabled, all linked options are passed via the
# response file. 
#   The token should be enabled when the length of the linker command
# line exceeds 
#   the maximum supported limit. The token is disabled by default.
# 
# 64    10/09/09 5:11p Felixp
# UEFI 2.1-related changes.
# 
# 63    5/04/09 2:00p Felixp
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
# 62    3/05/09 9:52a Felixp
# Minor bug fix: Dual mode libraries (libraries with PEI and DXE
# instances) INIT_LIST problem. 
# Description: Compilation of the dual mode libraries with 
#   INIT_LIST in x64 mode (x64_SUPPORT=1) was failing.
# Symptoms: Build fails with "Don't know how to build Build\IA32\Token.h"
# error.
# Details: $(BUILD_DIR)\Token.h replaced with $(BUILD_ROOT)\Token.h
# 
# 61    1/02/09 12:49p Felixp
# C preprocessor copyright message is suppressed.
# 
# 60    12/16/08 3:50p Felixp
# Support for "Step out" operation in the debugger.
#   x64 debuggers implemen "Step out" operation using exception directory
# within PE32+ image. 
#   In previous versions of the Core exception directory was stripped out
# by the build process to reduce PE32 image size. 
#   Current version of the code preserves exception directory when
# generation of debug informataon is enabled (DEBUG_INFO token is set to
# "on"). 
# 
# 59    10/31/08 11:22a Felixp
# 
# 58    10/22/08 3:57p Felixp
# Some of the linker warnings are eliminated (.efi files are no longer
# built as .dll files. They are built as .exe files).
# 
# 57    10/10/08 9:51a Felixp
# 
# 56    10/10/08 9:50a Felixp
#  - Component VFR files were compiled when HAS_RESOURCES was set to zero
#  - Workaround for ML64 added
# 
# 55    5/09/08 5:05p Felixp
# Minor bug fix: Rules.mak based build of the componentns with .efi files
# did not work.
# 
# 54    12/14/07 12:38p Felixp
# 
# 53    12/14/07 12:30p Felixp
# DEST_DIR usage removed (DEST_DIR is not defined by cif2mak if more than
# one cif file used).
# 
# 52    10/22/07 6:11p Felixp
# New FFS_ALIGNMENT switch added to support FFS data alignment
# 
# 51    9/05/07 6:49p Felixp
# Disable debugging features is DEBUG_MODE is zero
# 
# 50    9/05/07 1:42a Felixp
# 1. Debugging-related tokens updated to use boolean tokens instead of
# enumeration
# 2. Support for ROM_IMAGE_SIZE is added.
# 
# 49    8/02/07 1:27a Felixp
# 
# 48    6/01/07 2:53p Felixp
# TE image support added. (PE_IMAGE_FORMAT macro that is used to
# supppress TE image generation passed to FFS.mak)
# 
# 47    3/30/07 4:43p Felixp
# Support for FFS_CHECKSUM added to control FFS checksum generation.
# 
# 46    3/13/07 9:54a Felixp
# Global and CPU architecture specific macros are now passed 
# to C preprocessor (used during DepEx and VFR compilation)
# 
# 45    2/23/07 2:30p Felixp
# Support for custom string consumers added (MY_STRING_CONSUMERS).
# 
# 44    12/28/06 6:24p Felixp
# Support for 32-bit C compiler from Windows Server 2003 SP1 DDK
# (3790.1830) added
# 
# 43    11/11/06 11:47a Felixp
# Support for date/time stamps(All executables generated with the
# identical date/time stamp)
# 
# 36    10/03/06 8:56a Felixp
# Support for a build family specific build rules.
# MY_DEFINES macro added to list all module specific macro definitions
# 
# 35    9/26/06 9:01a Felixp
# Multilanguage support added. New FontTool is required.
# 
# 34    9/07/06 1:48p Felixp
# 
# 33    8/24/06 9:06a Felixp
# Preliminary x64 support (work in progress)
# 
# 32    7/14/06 9:55a Pavell
# 
# 31    6/22/06 2:55p Andriyn
# Fix EDK modules compiling
# 
# 30    5/19/06 6:14p Felixp
# 1. Support for EDK-based modules added.
# 2. MY_INCLUDES macro added to specify list of include directories
# 
# 28    5/12/06 3:07p Felixp
# EDK support added
# 
# 25    3/30/06 6:05p Felixp
# Support for compiler version auto-detection added.
# 
# 24    2/24/06 2:43p Felixp
# 
# 23    2/23/06 6:44p Felixp
# Change in string handling. Skip source scanning if STRING_CONSUMERS is
# blank.
# This is needed to support binary modules with strings.
# 
# 22    7/29/05 4:16p Robert
# Updated Init Parts rule to allow use in libraries
# 
# 20    7/14/05 6:36p Felixp
# SDL tokens for ECHO and DEL added
# 
# 18    6/17/05 3:25p Felixp
# Setup support: sd files handling
# 
# 17    6/16/05 10:42a Felixp
# 1. Tokens.c added. It has variables representing SDL tokens.
# 2. InitList.c extended to support 2 init lists
# 
# 15    5/24/05 12:47a Felixp
# ignore unsupported languages
# 
# 14    5/23/05 6:01p Felixp
# CreateSdb target added
# STRING_TOKEN definition added to avery StrToken.h
# FFS file dependecies from RAWFILE and SECTION added
# 
# 12    4/08/05 7:40a Felixp
# strings
# 
# 11    4/04/05 4:54p Felixp
# dependency fix in .uni files processing
# 
# 10    3/28/05 7:03p Felixp
# 
# 9     3/28/05 7:02p Felixp
# del command to delete .i files
# 
# 8     3/22/05 10:31p Felixp
# support for EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER added
# 
# 5     3/17/05 1:26p Felixp
# processing of multiple .uni files added
# 
# 2     3/02/05 5:27p Felixp
# Support for resources (strings, forms, fonts, etc.) added
# 
# 5     1/20/05 11:34a Felixp
# support for prebuilt objects, libraries and .efi files
# 
# 4     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 2     12/24/04 2:39p Felixp
# 
# 1     12/23/04 9:41a Felixp
# 
# 7     12/15/04 9:06p Felixp
# LegacyBoot application added
# Minor build process improvements
# 
# 6     11/01/04 7:59a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	Rules.mak
#
# Description:	Build Rules Template
#
#<AMI_FHDR_END>
#**********************************************************************
.SUFFIXES: .asm .c .vfr .dll .uni

!IFNDEF BUILD_ROOT
BUILD_ROOT=$(BUILD_DIR)
!ELSEIFNDEF BUILD_DIR
BUILD_DIR=$(BUILD_ROOT)
!ENDIF

!INCLUDE $(BUILD_ROOT)\token.mak
!INCLUDE $(BUILD_ROOT)\timestamp.mak
!INCLUDE Core\Languages.mak
!IF EXIST ($(BUILD_ROOT)\selectivedebugmodules.mak)
!INCLUDE $(BUILD_ROOT)\selectivedebugmodules.mak
!ENDIF

EXTRA_INCLUDES=$(MY_INCLUDES) $(EXTRA_INCLUDES)
EXTRA_DEFINES=$(MY_DEFINES) $(EXTRA_DEFINES)

FINAL_CFLAGS=$(CFLAGS) $(EXTRA_CFLAGS) $(FORCE_INCLUDE)
FINAL_LFLAGS=$(LFLAGS) $(EXTRA_LFLAGS)
FINAL_AFLAGS=$(AFLAGS) $(EXTRA_AFLAGS)
FINAL_AFLAGS16=$(AFLAGS16) $(EXTRA_AFLAGS16)
LIBFLAGS=/NOLOGO
#C preprocessor flags (used by DepEx parser and VFR compiler)
CPFLAGS=/nologo $(GLOBAL_DEFINES) $(EXTRA_DEFINES) $(EXTRA_INCLUDES)

#Check if this is a PEI module or DXE module
!IF "$(TYPE)"=="PEIM"||"$(TYPE)"=="PEI_CORE"||"$(TYPE)"=="PEI_LIBRARY"||"$(TYPE)"=="PEI_GUID_LIBRARY"
COMPONENT_BUILD_RULES=PEI
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /DPEI_BUILD
DUAL_INSTANCE_LIBRARIES_BUILD_DIR=$(BUILD_ROOT)\IA32
!ELSE
COMPONENT_BUILD_RULES=DXE
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /DDXE_BUILD
!IF "$(TYPE)"=="SMM_DRIVER"||"$(TYPE)"=="DXESMM_DRIVER"
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /DSMM_BUILD
DUAL_INSTANCE_LIBRARIES_BUILD_DIR=$(BUILD_ROOT)
!ENDIF
!ENDIF

!IF "$(DEBUG_MODE)"!="1"
# Debugging is disabled.
# Use release mode settings 
# (unless debug flags have been defined for the release mode)
!IFNDEF OPTIMIZATION
OPTIMIZATION=1
!ENDIF
!IFNDEF DEBUG_INFO
DEBUG_INFO=0
!ENDIF
!IFNDEF DEBUG_CODE
DEBUG_CODE=0
!ENDIF
COMPONENT_OPTIMIZATION=$(OPTIMIZATION)
COMPONENT_DEBUG_INFO=$(DEBUG_INFO)
COMPONENT_DEBUG_CODE=$(DEBUG_CODE)
!ELSEIF "$(SELECTIVE_DEBUG_ENABLE)"=="1"
COMPONENT_OPTIMIZATION=$(SELECTIVE_OPTIMIZATION)
COMPONENT_DEBUG_INFO=$(SELECTIVE_DEBUG_INFO)
COMPONENT_DEBUG_CODE=$(SELECTIVE_DEBUG_CODE)
!ELSEIF "$(COMPONENT_BUILD_RULES)"=="PEI" && "$(INDEPENDENT_PEI_DEBUG_SETTINGS)"=="1"
COMPONENT_OPTIMIZATION=$(PEI_OPTIMIZATION)
COMPONENT_DEBUG_INFO=$(PEI_DEBUG_INFO)
COMPONENT_DEBUG_CODE=$(PEI_DEBUG_CODE)
!ELSE
COMPONENT_OPTIMIZATION=$(OPTIMIZATION)
COMPONENT_DEBUG_INFO=$(DEBUG_INFO)
COMPONENT_DEBUG_CODE=$(DEBUG_CODE)
!ENDIF

#Set debug mode specific flags
#1. Optimization
!IF "$(COMPONENT_OPTIMIZATION)"=="1"
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /O1
!ENDIF
#2. Debug information
!IF "$(COMPONENT_DEBUG_INFO)"=="1" && "$(TYPE)"!="BINARY"
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /Fd$(BUILD_DIR)\ /Zi /Gm
EXTRA_LFLAGS=$(EXTRA_LFLAGS) /MAP /DEBUG /PDB:$*.pdb
EXTRA_AFLAGS=$(EXTRA_AFLAGS) /Zi /Zf /Zd
!ENDIF
#3. Debug code
!IF "$(COMPONENT_DEBUG_CODE)"=="1"
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /DEFI_DEBUG
EXTRA_AFLAGS=$(EXTRA_AFLAGS) /DDEBUG /DEFI_DEBUG
!ENDIF
#Done setting debug mode specific flags

!IF "$(PROCESSOR_RULES)"!=""
!INCLUDE $(PROCESSOR_RULES)
MAKEFILES=$(MAKEFILES) $(PROCESSOR_RULES)
!ENDIF

!IF "$(FAMILY_RULES)"!=""
!INCLUDE $(FAMILY_RULES)
MAKEFILES=$(MAKEFILES) $(FAMILY_RULES)
#This is here for backward compatibility/
#Old labels of EDK module need this
!ELSEIF "$(FAMILY)"=="EDK"
EXTRA_CFLAGS=$(EXTRA_CFLAGS) /X $(EDK_INCLUDES)
!ENDIF

!IFNDEF MAKEFILE
MAKEFILE=$(BUILD_ROOT)\$(NAME).mak
!ENDIF
MAKEFILES=$(MAKEFILES) $(MAKEFILE)

!IFNDEF FFS_FILE
FFS_FILE=$(BUILD_ROOT)\$(NAME).ffs
!ENDIF

!IFNDEF LIB_BUILD_DIR
LIB_BUILD_DIR=$(BUILD_DIR)
!ENDIF

!IF "$(TYPE)"=="PEI_DXE_LIBRARY"
all:
	$(MAKE) /$(MAKEFLAGS)\
        /f $(MAKEFILE) all\
		TYPE=LIBRARY $(PARAMETERS)
!IF DEFINED(CCPEI) && "$(CCPEI)"!="$(CC)"
	$(MAKE) /$(MAKEFLAGS) BUILD_DIR=$$(LIB_BUILD_DIR)\
		/f $(MAKEFILE) all\
		TYPE=PEI_LIBRARY $(PARAMETERS)
!ENDIF
!ENDIF

!IF "$(TYPE)"=="LEGACY16"
.SOURCEGRULE .asm.obj
	$(ASM16) $(FINAL_AFLAGS16) /Fo$D\ $<
!ELSE
#Workaround for ML64
#If ML64 absolute path contains spaces,
#it fails to process multiple files.
#To workaround the issue, group file processing is disabled for ML64
!IF "$(PROCESSOR)"=="x64"
.SOURCERULE .asm.obj
	$(ASM) $(FINAL_AFLAGS) /Fo$D\ $<
!ELSE
.SOURCEGRULE .asm.obj
	$(ASM) $(FINAL_AFLAGS) /Fo$D\ $<
!ENDIF
!ENDIF

!IF "$(USE_CC_RESPONSE_FILE)"=="1"
CC_COMMAND_LINE=@$(BUILD_DIR)\$(NAME)CcOptions.txt
!ELSE
CC_COMMAND_LINE=$(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES)
!ENDIF
!IF "$(GENERATE_CC_LISTING_FILE)"=="1"
.SOURCEGRULE .c.obj
	$(CC) $(CC_COMMAND_LINE) /Fa$D\ /FAs /Fo$D\ $<
!ELSE
.SOURCEGRULE .c.obj
	$(CC) $(CC_COMMAND_LINE) /Fo$D\ $<
!ENDIF

.SOURCERULE .vfr.hpk
	$(VFRCOMPILE) -ppflag "/EP $(CPFLAGS)" -od $D -ibin -i INCLUDE -i Build -i $(PROJECT_DIR) $(VFR_INCLUDES) $<

STRGATHER_PARSE_FLAGS=-i INCLUDE -parse -newdb -db $@ $<
!IFDEF UNI_INCLUDE_PATH
STRGATHER_PARSE_FLAGS=-i $(UNI_INCLUDE_PATH) $(STRGATHER_PARSE_FLAGS)
!ENDIF
.SOURCERULE .uni.sdb
	$(STRGATHER) $(STRGATHER_PARSE_FLAGS)

!IF "$(TYPE)"=="SDB" || "$(TYPE)"=="RESOURCES"
HAS_RESOURCES=1
!ENDIF

!IFNDEF OBJECTS
.SOURCEVAR OBJECTS=.obj(.c,.asm)
!ENDIF
!IFNDEF HEADERS
.SOURCEVAR HEADERS=.h
!ENDIF
!IFNDEF DEPEX1
.SOURCEVAR DEPEX1=.dxs
!ENDIF
!IFNDEF LIBRARIES
.SOURCEVAR LIBRARIES=.lib
!ENDIF
!IFNDEF PRECOMPILED_OBJS
.SOURCEVAR PRECOMPILED_OBJS=.obj
!ENDIF
!IFNDEF EFI_FILE
.SOURCEVAR EFI_FILE=.efi
!ENDIF

!IF !DEFINED(SDB_FILES) && "$(HAS_RESOURCES)"=="1"
.SOURCEVAR SDB_FILES=.sdb(.uni)
!ENDIF
!IFNDEF STRGATHER_FLAGS
.SOURCEVAR STRGATHER_FLAGS=.sdb(.uni) : -db $F
!ENDIF
!IF !DEFINED(VFR_PACKS) && "$(HAS_RESOURCES)"=="1"
.SOURCEVAR VFR_PACKS=.hpk(.vfr)
!ENDIF
!IFNDEF STRING_CONSUMERS
STRING_CONSUMERS = $(MY_STRING_CONSUMERS)
.SOURCEVAR CFILES=.c
.SOURCEVAR VFRFILES=.vfr
.SOURCEVAR SDFILES=.sd
!IF "$(CFILES)"!=""
STRING_CONSUMERS=$(STRING_CONSUMERS) $(CFILES)
!ENDIF
!IF "$(VFRFILES)"!=""
STRING_CONSUMERS=$(STRING_CONSUMERS) $(VFRFILES)
!ENDIF
!IF "$(SDFILES)"!=""
STRING_CONSUMERS=$(STRING_CONSUMERS) $(SDFILES)
!ENDIF
!ENDIF

HEADERS=$(HEADERS) $(EXT_HEADERS)
ALL_EXT_OBJS_TMP=$(EXT_OBJS) $(LIBRARIES) $(PRECOMPILED_OBJS)
!IF "$(COMPONENT_BUILD_RULES)"=="PEI" && EXIST (Build\IA32\AmiCSPLib.lib)
ALL_EXT_OBJS=$(ALL_EXT_OBJS_TMP:Build\AmiCSPLib.lib=Build\IA32\AmiCSPLib.lib)
!ELSE
ALL_EXT_OBJS=$(ALL_EXT_OBJS_TMP)
!ENDIF
PACKS = $(VFR_PACKS)

!IF "$(OBJECTS)"!=""
$(OBJECTS) : $(HEADERS) $(MAKEFILES)
!ENDIF

!IF "$(VFR_PACKS)"!=""
$(VFR_PACKS) : $(HEADERS) $(MAKEFILES)
!ENDIF

!IF "$(SDB_FILES)"!=""
$(SDB_FILES) : $(HEADERS) $(MAKEFILES)
!ENDIF

!IF "$(TYPE)"=="BS_DRIVER"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_DRIVER
PE_TYPE=$(TYPE)
DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX
!ELSEIF "$(TYPE)"=="RT_DRIVER"
SUBSYSTEM = EFI_RUNTIME_DRIVER
FV_TYPE=EFI_FV_FILETYPE_DRIVER
PE_TYPE=$(TYPE)
DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX
!ELSEIF "$(TYPE)"=="SMM_DRIVER"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_SMM
PE_TYPE=BS_DRIVER
DEPEX1_TYPE=EFI_SECTION_SMM_DEPEX
!ELSEIF "$(TYPE)"=="DXESMM_DRIVER"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_COMBINED_SMM_DXE
PE_TYPE=BS_DRIVER
!ELSEIF "$(TYPE)"=="APPLICATION"
SUBSYSTEM = EFI_APPLICATION
FV_TYPE=EFI_FV_FILETYPE_APPLICATION
PE_TYPE=$(TYPE)
!ELSEIF "$(TYPE)"=="PEI_CORE"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_PEI_CORE
PE_TYPE=BS_DRIVER
!ELSEIF "$(TYPE)"=="DXE_CORE"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_DXE_CORE
PE_TYPE=BS_DRIVER
!ELSEIF "$(TYPE)"=="SMM_CORE"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_SMM_CORE
PE_TYPE=BS_DRIVER
DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX
!ELSEIF "$(TYPE)"=="PEIM"
SUBSYSTEM = EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_PEIM
PE_TYPE=BS_DRIVER
DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX
!ELSEIF "$(TYPE)"=="COMBINED"
SUBSYSTEM=EFI_BOOT_SERVICE_DRIVER
FV_TYPE=EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER
PE_TYPE=BS_DRIVER
!ELSEIF "$(TYPE)"=="LIBRARY" || "$(TYPE)"=="PEI_LIBRARY"
!UNDEF TYPE
TYPE=LIBRARY
!ELSEIF "$(TYPE)"=="PEI_GUID_LIBRARY" || "$(TYPE)"=="GUID_LIBRARY"
!IF "$(TYPE)"=="PEI_GUID_LIBRARY"
FORCE_INCLUDE=/FIPEI.h
!ELSE
FORCE_INCLUDE=/FIEFI.h
!ENDIF
!UNDEF TYPE
TYPE=GUID_LIBRARY
!ELSEIF "$(TYPE)"=="SDB"
!ELSEIF "$(TYPE)"=="RESOURCES"
!ELSEIF "$(TYPE)"=="LEGACY16" || "$(TYPE)"=="BINARY"
FV_TYPE=EFI_FV_FILETYPE_FREEFORM
!IFNDEF BINFILE
BINFILE=$(BUILD_DIR)\$(NAME).bin

bin : $(DIRS) $(BUILD_DIR)\$(NAME).bin

!IF "$(TYPE)"=="BINARY"
$(BUILD_DIR)\$(NAME).bin : $(BUILD_DIR)\$(NAME).dll
    pe2bin $(BUILD_DIR)\$(NAME).dll $(BUILD_DIR)\$(NAME).bin
!ELSE
$(BUILD_DIR)\$(NAME).bin : $(OBJECTS)
	$(ASMLINK) $(ASMLINKFLAGS) $(OBJECTS: =+), $(BUILD_DIR)\$(NAME).exe, $(BUILD_DIR)\$(NAME).map,,,
!IFNDEF POST_PROCESS
	exe2bin $(BUILD_DIR)\$(NAME).exe $(BUILD_DIR)\$(NAME).bin
!ELSE
	exe2bin $(BUILD_DIR)\$(NAME).exe $(BUILD_DIR)\$(NAME)1.bin
	$(POST_PROCESS) $(BUILD_DIR)\$(NAME)1.bin $(BUILD_DIR)\$(NAME).bin
!ENDIF # !IFNDEF POST_PROCESS
!ENDIF # !IF "$(TYPE)"=="BINARY"
!ENDIF # !IFNDEF BINFILE
!ELSEIF "$(TYPE)"=="PEI_DXE_LIBRARY"
!ELSEIF "$(TYPE)"==""
!ERROR Error in the makefile of component $(NAME): 'TYPE' is undefined
!ELSE
!ERROR Error in the makefile of component $(NAME): TYPE $(TYPE) is unsupported
!ENDIF

!IF "$(TYPE)"=="BINARY"
EXTRA_LFLAGS = $(EXTRA_LFLAGS) /NOENTRY /FIXED
!ELSE
EXTRA_LFLAGS = $(EXTRA_LFLAGS) /ENTRY:$(ENTRY_POINT)
!ENDIF

# Linkers newer than VC6 can directly generate .efi files.
# However, we use FWIMAGE to generate .efi files because
# FWIMAGE can set date/time stamp to a predefined value
# This is useful for baniray reproducibility of the BIOS
!IF "$(COMPONENT_DEBUG_INFO)"=="1"
FWIMAGE_KEEP_EXCEPTION_TABLE=-e
!ENDIF

{$(BUILD_DIR)}.dll{$(BUILD_DIR)}.efi:
	$(FWIMAGE) -t $(TODAY),$(NOW) $(FWIMAGE_KEEP_EXCEPTION_TABLE) $(PE_TYPE) $< $@

!IF "$(TYPE)"=="APPLICATION" && "$(BUILD_FFS)"!="1"
all : $(BUILD_DIR)\$(NAME).efi
!ELSEIF "$(TYPE)"=="LIBRARY" || "$(TYPE)"=="GUID_LIBRARY"
!IFNDEF LIBRARY_NAME
LIBRARY_NAME=$(BUILD_DIR)\$(NAME).lib
!ENDIF
all : $(LIBRARY_NAME)

!IF "$(TYPE)"=="GUID_LIBRARY"
$(LIBRARY_NAME) : $(HEADERS)
	$(SILENT)if not exist $(BUILD_DIR)\$(@B) md $(BUILD_DIR)\$(@B)
!IF "$(USE_CC_RESPONSE_FILE)"=="1"
	$(CC) @<<$(BUILD_DIR)\$(NAME)CcOptions.txt
$(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES) /TC /DGUID_VARIABLE_DEFINITION /Fo$(BUILD_DIR)\$(@B)\\ $**
<<KEEP
!ELSE
	$(CC) $(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES) /TC /DGUID_VARIABLE_DEFINITION /Fo$(BUILD_DIR)\$(@B)\\ $**
!ENDIF
	$(SILENT)cd $(BUILD_DIR)\$(@B)
	$(LIBEXE) $(LIBFLAGS) /OUT:$(PROJECT_DIR)\$@ $(**F:.h=.obj)
	$(SILENT)cd $(MAKEDIR)
!ENDIF
!ELSEIF "$(TYPE)"=="SDB"
all : CreateSdb
!ELSEIF "$(TYPE)"=="RESOURCES"
all : CreateAllPacks
!ELSEIF "$(TYPE)"=="PEI_DXE_LIBRARY"
!ELSE
all : $(FFS_FILE)
!ENDIF

# Strings and VFRs processing
!IF "$(SDB_FILES)"!=""
!IF "$(OBJECTS)"!=""||"$(VFR_PACKS)"!=""
$(OBJECTS) $(VFR_PACKS) : $(BUILD_DIR)\$(NAME)StrTokens.h
!ENDIF

PACKS=$(BUILD_DIR)\$(NAME)Str.hpk $(PACKS)
STRGATHER_DUMP_FLAGS=-dump -lang $(SUPPORTED_LANGUAGES: = -lang ) -bn $(NAME) -hpk $(BUILD_DIR)\$(NAME)Str.hpk -oh $(BUILD_DIR)\$(NAME)StrTokens.h -override

CreateSdb : $(DIRS) $(SDB_FILES) $(STRING_CONSUMERS)
!IF "$(STRING_CONSUMERS)"!=""
	$(STRGATHER) -scan $(STRGATHER_FLAGS) $(MY_SDBS) -od $(BUILD_DIR)\$(NAME).sdb $(STRING_CONSUMERS)
!ENDIF

$(BUILD_DIR)\$(NAME)StrTokens.h $(BUILD_DIR)\$(NAME)Str.hpk : $(DIRS) $(SDB_FILES) $(STRING_CONSUMERS)
!IF "$(STRING_CONSUMERS)"==""
    $(STRGATHER) $(STRGATHER_DUMP_FLAGS) $(STRGATHER_FLAGS) $(MY_SDBS)
!ELSE
	$(STRGATHER) -scan $(STRGATHER_FLAGS) $(MY_SDBS) -od $(BUILD_DIR)\$(NAME).sdb $(STRING_CONSUMERS)
    $(STRGATHER) $(STRGATHER_DUMP_FLAGS) -db $(BUILD_DIR)\$(NAME).sdb
!ENDIF
	$(ECHO) #ifndef VFRCOMPILE >> $(BUILD_DIR)\$(NAME)StrTokens.h
	$(ECHO) #ifndef STRING_TOKEN >> $(BUILD_DIR)\$(NAME)StrTokens.h
	$(ECHO) #define STRING_TOKEN(x) x >> $(BUILD_DIR)\$(NAME)StrTokens.h
	$(ECHO) #endif >> $(BUILD_DIR)\$(NAME)StrTokens.h
	$(ECHO) #endif >> $(BUILD_DIR)\$(NAME)StrTokens.h
    $(STRING_PACK_POST_PROCESS_COMMAND)
!ENDIF

CreateAllPacks : $(DIRS) $(PACKS)

!IF "$(PACKS)"!=""
!IF	"$(ITK_SUPPORT)"=="1"
$(FFS_FILE) : $(BUILD_DIR)\$(NAME).hii

$(BUILD_DIR)\$(NAME).hii: $(PACKS)
	$(HIIPACK)	create -g $(GUID) -p $(PACKS) -o $(BUILD_DIR)\$(NAME).hii
!ENDIF
!IF "$(EMBEDDED_RESOURCES)"=="1"
EXTRA_LFLAGS = $(EXTRA_LFLAGS) $(BUILD_DIR)\$(NAME)Resources.obj
$(BUILD_DIR)\$(NAME).dll : $(BUILD_DIR)\$(NAME)Resources.obj
$(BUILD_DIR)\$(NAME)Resources.obj : $(PACKS)
	$(AMIRC) /j /o$@ $**
!ELSE
SECTION=$(NAME)Resources.sec
$(FFS_FILE) : $(BUILD_DIR)\$(NAME)Resources.sec
$(BUILD_DIR)\$(NAME)Resources.sec : $(PACKS)
	$(AMIRC) /s /o$@ $**
!ENDIF
!ENDIF

# sources have priority over the binary
!IF "$(TYPE)"!="LEGACY16" && "$(TYPE)"!="BINARY" && ("$(EFI_FILE)"==""||"$(OBJECTS)"!=""||"$(ALL_EXT_OBJS)"!="  ")
!UNDEF EFI_FILE
EFI_FILE=$(BUILD_DIR)\$(NAME).efi
!ENDIF

efi : $(DIRS) $(EFI_FILE)

!IFDEF RAWFILE
FFS_DEPS=$(FFS_DEPS) $(PROJECT_DIR)\$(RAWFILE)\
!ENDIF
!IFDEF SECTION
FFS_DEPS=$(FFS_DEPS)  $(BUILD_DIR)\$(SECTION)\
!ENDIF

$(FFS_FILE) : $(EFI_FILE) $(MAKEFILES) Core\FFS.mak $(DEPEX1) $(DEPEX2) $(BINFILE) $(FFS_DEPS)
	$(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
		NAME=$(NAME) \
		BUILD_DIR=$(BUILD_ROOT) SOURCE_DIR=$(SOURCE_DIR) \
		GUID=$(GUID) \
		TYPE=$(FV_TYPE) \
		FFSFILE=$@ COMPRESS=$(COMPRESS) \
        "EXTRA_DEFINES=$(EXTRA_DEFINES)" "EXTRA_INCLUDES=$(EXTRA_INCLUDES)" "CPFLAGS=$(CPFLAGS)"\
!IF "$(EFI_FILE)"!=""
		PEFILE=$(EFI_FILE) \
!ENDIF
!IF "$(DEPEX1)"!=""
		DEPEX1=$(DEPEX1) DEPEX1_TYPE=$(DEPEX1_TYPE) \
!ENDIF
!IFDEF DEPEX2
		DEPEX2=$(DEPEX2) DEPEX2_TYPE=$(DEPEX2_TYPE) \
!ENDIF
!IFDEF BINFILE
		BINFILE=$(BINFILE) \
!ENDIF
!IFDEF RAWFILE
		RAWFILE=$(RAWFILE) \
!ENDIF
!IFDEF SECTION
		SECTION=$(SECTION) \
!ENDIF
!IFDEF FFS_CHECKSUM
        FFS_CHECKSUM=$(FFS_CHECKSUM) \
!ENDIF
!IFDEF FFS_ALIGNMENT
        FFS_ALIGNMENT=$(FFS_ALIGNMENT) \
!ENDIF
!IFDEF PE_IMAGE_FORMAT
        PE_IMAGE_FORMAT=$(PE_IMAGE_FORMAT) \
!ENDIF

!IFDEF INIT_LIST
INIT_LIST_DEFINES=/D"INIT_LIST=$(INIT_LIST)"
!IFDEF INIT_LIST2
INIT_LIST_DEFINES=$(INIT_LIST_DEFINES) /D"INIT_LIST2=$(INIT_LIST2)"
!ENDIF
!IF "$(TYPE)"=="LIBRARY"
$(LIBRARY_NAME) : $(BUILD_DIR)\$(NAME)_INIT_LIST.obj
LIBFLAGS = $(LIBFLAGS) $(BUILD_DIR)\$(NAME)_INIT_LIST.obj
!ELSE
EXTRA_LFLAGS = $(EXTRA_LFLAGS) $(BUILD_DIR)\$(NAME)_INIT_LIST.obj
$(BUILD_DIR)\$(NAME).dll : $(BUILD_DIR)\$(NAME)_INIT_LIST.obj
!ENDIF # !IF "$(TYPE)"=="LIBRARY"
$(BUILD_DIR)\$(NAME)_INIT_LIST.obj : $(PROJECT_DIR)\Core\InitList.c $(BUILD_ROOT)\token.h
	$(CC) $(FINAL_CFLAGS) $(INIT_LIST_DEFINES) /Fo$@ $(PROJECT_DIR)\Core\InitList.c
!ENDIF # !IFDEF INIT_LIST

#We no longer need build-through-lib mode.
#Let's keep IF statement is case we will want to change it in the future
#!IF "$(BUILD_BASE_LIB)"=="1" && "$(OBJECTS)"!=""
#$(BUILD_DIR)\$(NAME)Base.lib : $(OBJECTS)
#	$(LIBEXE) $(LIBFLAGS) /OUT:$@ $(OBJECTS)
#$(BUILD_DIR)\$(NAME).dll :  $(BUILD_DIR)\$(NAME)Base.lib $(ALL_EXT_OBJS) $(MAKEFILE)
#	$(LINK) $(FINAL_LFLAGS) $(BUILD_DIR)\$(NAME)Base.lib $(ALL_EXT_OBJS)
#!ELSE
!IF "$(USE_CC_RESPONSE_FILE)"=="1"
$(BUILD_DIR)\$(NAME).dll : $(BUILD_DIR)\$(NAME)CcOptions.txt

# This target is required to make sure 
# $(BUILD_DIR)\$(NAME)CcOptions.txt is regenerated during every build 
CcOptionsPhonyTargetWithTheLongName:

$(BUILD_DIR)\$(NAME)CcOptions.txt : CcOptionsPhonyTargetWithTheLongName
    $(SILENT)copy << $@
$(FINAL_CFLAGS) $(EXTRA_DEFINES) $(EXTRA_INCLUDES)
<<
!ENDIF
$(BUILD_DIR)\$(NAME).dll : $(OBJECTS) $(ALL_EXT_OBJS) $(MAKEFILES)
!IF "$(USE_LINKER_RESPONSE_FILE)"=="1"
	$(LINK) @<<$(BUILD_DIR)\$(NAME)LinkerOptions.txt
$(FINAL_LFLAGS) $(OBJECTS) $(ALL_EXT_OBJS)
<<KEEP
!ELSE
	$(LINK) $(FINAL_LFLAGS) $(OBJECTS) $(ALL_EXT_OBJS)
!ENDIF
#!ENDIF
!IF "$(TYPE)"=="LIBRARY"
!IF "$(USE_CC_RESPONSE_FILE)"=="1"
$(LIBRARY_NAME) : $(BUILD_DIR)\$(NAME)CcOptions.txt
!ENDIF
$(LIBRARY_NAME) : $(OBJECTS) $(ALL_EXT_OBJS)
!IF "$(USE_LINKER_RESPONSE_FILE)"=="1"
	$(LIBEXE) @<<$(BUILD_DIR)\$(NAME)LibOptions.txt
$(LIBFLAGS) /OUT:$@ $(OBJECTS) $(ALL_EXT_OBJS)
<<KEEP
!ELSE
	$(LIBEXE) $(LIBFLAGS) /OUT:$@ $(OBJECTS) $(ALL_EXT_OBJS)
!ENDIF
!ENDIF
!IF EXIST ($(BUILD_ROOT)\targets.mak)
!INCLUDE $(BUILD_ROOT)\targets.mak
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************