#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
#
# $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Build/CmosManager.mak 23    6/15/10 2:26p Michaela $
#
# $Revision: 23 $
#
# $Date: 6/15/10 2:26p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Core/CMOS Build/CmosManager.mak $
# 
# 23    6/15/10 2:26p Michaela
# 
# 22    3/05/10 4:55p Michaela
# 
# 21    12/03/09 6:48p Michaela
# 1. Clean-up the SEC target code
# 
# 2. Define CMOS_IS_COLD_BOOT_MAPPING environment
#    variable passed to C-source for cold boot
#    detection function overriding
# 
# 20    11/12/09 6:06p Michaela
# Fixed build dependencies so that client make files can put
# a dependency on SspTokens.h for rebuilding only if SSP files
# change or a project rebuild is invoked.
# 
# 19    11/10/09 9:14p Michaela
# 
# 18    7/29/09 10:01a Michaela
# updates Aptio Enhancement EIP 22205
# (no code changes)
# 
# 17    7/23/09 1:30p Michaela
# Fix PE32 related build issue
# 
# 16    6/15/09 5:12p Michaela
# 
# 15    6/02/09 3:28p Michaela
# For label: 4.6.3_CMOSMGR_11
# 
# 14    3/11/09 3:38p Michaela
# 
# 13    2/23/09 6:04p Michaela
# --Added $(AMICSPLib) dependency for exported SB CMOS
#   access functions
# --Removed Tokens.ssp
# 
# 12    1/08/09 12:54p Michaela
# >removed COPY_INCLUDES target because CmosAccess32.inc and
# CmosAccessSec.inc
#  are now in the INCLUDE directory
# 
# 11    12/15/08 12:58p Michaela
# Removed copying of CmosAccess32.inc and CmosAccessSec.inc
# 
# 10    11/25/08 3:20p Michaela
# Updates for Label 4.6.3_CMOSMGR_08
# - Assembly macro fixes
# - Added assembly macros
# - Moved loading defaults into DXE phase
# - Updated help file example
# 
# 9     11/17/08 3:57p Michaela
# --CMOS Buffer feature is depreciated
# --Development debugging code is removed
# --The DXE driver is invoked through the DXE INIT_LIST
# 
# 8     11/14/08 9:32a Michaela
# **CMOS Manager PEI phase is now linked to CORE_PEIBin and
# the entry point is called via PeiCoreInitialize INIT_LIST Elink
# **CMOS_PORT_MAPPING Elink is pass to C source via
# build environment variable.
# **Added PeiCmosBoard.obj and CmosBoard.obj for PEI/DXE phase
# board-specific access functions.
# **AFTER_ROM target modified to search for 
# CMOS_MANAGER_API string in CORE_PEI FFS and update
# the pointer in Startup.FFS
# 
# 7     11/07/08 5:14p Michaela
# Updated to make CMOS manager available in all phases 
# of the boot process:
# 
# A CMOS API Pointer is maintained in CMOS and accessible
# via provided macros in C and assembly source.
# 
# 6     3/25/08 3:06p Michaela
# CmosManager.ssp is now forced to be the first file in the SSP file list
# 
# 5     2/29/08 9:35p Michaela
# - removed redundant source file in DXE
# 
# 4     2/27/08 11:28a Michaela
# Modified dependencies to prevent build errors under certain conditions
# 
# 3     2/26/08 12:51p Michaela
# Fixed build dependency issues
# 
# 2     2/22/08 3:21p Olegi
# Added GENERATE_CMOS_TOKENS target.
# 
# 1     2/22/08 2:29p Michaela
# 
# 1     2/04/08 6:00p MichaelA $
# Created
# 
#**********************************************************************

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
#
# Name:	CmosManager.mak
#
# Description:	
#       This is a make file used to build the CMOS manager component
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>


#<AMI_GHDR_START>
#----------------------------------------------------------------------------
#
# Name:    Entry_Functions
#
# Description:        
#      This page provides links to descriptions of the PEI and DXE phase 
#      entrypoint functions for the CMOS Manager module.
#
# Fields:  Phase  Entrypoint  Description
# ------------------------------------------------------------------
# PEI CmosManagerPeiEntry          Main PEI phase entry point
# PEI CmosManagerAfterMemoryEntry  PEI after memory detection entry point
# DXE CmosManagerDxeEntry          Main DXE phase entry point
# DXE CmosManagerSmmEntry          Entry into SMM (Runtime) CMOS access support driver
#
#----------------------------------------------------------------------------
#<AMI_GHDR_END>

!INCLUDE $(BUILD_DIR)\timestamp.mak

PREPARE : GENERATE_CMOS_TOKENS

CMOS_MANAGER_COMPONENTS=\
    CMOS_MANAGER_PEI \
    CMOS_MANAGER_DXE \
!IF $(CMOS_SMM_SUPPORT)
    CMOS_MANAGER_SMM \
!ENDIF


all : $(CMOS_MANAGER_COMPONENTS)



#---------------------------------------------------------------------------
#		Shared module make file dependencies
#---------------------------------------------------------------------------

CMOS_MANAGER_MAK_DEPS = \
    $(CMOS_MANAGER_DIR)\CmosManager.mak



#----------------------------------------------------------------------------
# Generate SSP output files in the build directory
#----------------------------------------------------------------------------
#
# DEFAULT SETUP APPEARANCE AND ORDER
#
# Template.ssp			(Order of the SSP files is important)
#	|
#	+--CmosBoard.ssp  
#	|
#	+--ADDON_SSPs		(other Modules can add SSP files here and if they
#	    :               define a duplicate name with the same mask the
#       :               duplicate name will override the one defined in
#                       CmosBoard.ssp)
#
#
#  AmiSsp2.exe is only executed if an SSP file is modified or if a project
#  rebuild is invoked.  (Note: modifying SDL forces a project rebuild.)
#
#       * Client modules should place a dependency on the SspTokens.h
#         output files to ensure rebuild in the case CMOS Manager is
#         rebuilt.
#
#----------------------------------------------------------------------------

SSP_FILE_LIST = $(SSP_FILE_LIST) \
$(CMOS_MANAGER_DIR)\Template.ssp \
$(CMOS_MANAGER_DIR)\CmosBoard.ssp \
$(ADDON_SSP_FILES)

UPDATE_PROJECT_LOG:
    type << >> $(BUILD_DIR)\SSP.log
     Project build: $(TODAY) @ $(NOW)
<<

SSP_FILES = $(**:\=\\)
$(BUILD_DIR)\SSP.log: $(SSP_FILE_LIST)
    type << > $(BUILD_DIR)\SspFileList.txt
include "$(SSP_FILES: ="^
include ")"
<<
    @$(SSP) $(BUILD_DIR)\ -s2 -efi $(BUILD_DIR)\SspFileList.txt
!IF EXIST($(BUILD_DIR)\$(CMOS_MANAGER_DIR))
    -del /S /Q $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\* > NUL
!ENDIF
    type << >> $(BUILD_DIR)\SSP.log
CMOS Manager build: $(TODAY) @ $(NOW)
<<

GENERATE_CMOS_TOKENS: $(BUILD_DIR)\SSP.log UPDATE_PROJECT_LOG


#---------------------------------------------------------------------------
#		CMOS Manager SEC object component
#---------------------------------------------------------------------------
CMOSMGR_SEC_ASM_FLAGS = /c /nologo /Sa /I$(CMOS_MANAGER_DIR) \
    /Fl$(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SEC\ \
!if "$(SEC_CREATE_PE32)" == "1"
    /coff
!endif

$(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SEC\CmosManagerSec.obj : $(CMOS_MANAGER_DIR)\CmosManagerSec.asm
!IF !EXIST($(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SEC)
	mkdir $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SEC
!ENDIF
  $(ASM) $(CMOSMGR_SEC_ASM_FLAGS) /Fo$(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SEC\ $(CMOS_MANAGER_DIR)\CmosManagerSec.asm



#---------------------------------------------------------------------------
#		CMOS Manager PEI library component
#---------------------------------------------------------------------------

CMOS_MANAGER_PEI : $(BUILD_DIR)\CmosManagerPei.mak CmosManagerPeiBin

CORE_PEIBin : $(BUILD_DIR)\CmosManagerPei.lib

$(BUILD_DIR)\CmosManagerPei.lib : CMOS_MANAGER_PEI

$(BUILD_DIR)\CmosManagerPei.mak : $(CMOS_MANAGER_MAK_DEPS) $(BUILD_RULES)
!IF !EXIST($(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI)
	mkdir $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI
!ENDIF
	$(CIF2MAK) $(CMOS_MANAGER_DIR)\CmosManager.cif $(CIF2MAK_DEFAULTS)

CMOS_PEI_CFLAGS = \
    $(CFLAGS) \
    $(CMOS_MGR_CFLAGS) \
    /D\"CMOS_PORT_MAPPING=$(CMOS_PORT_MAPPING)\" \
    /D\"CMOS_IS_BSP_MAPPING=$(CMOS_IS_BSP_MAPPING)\" \
    /D\"CMOS_IS_FIRST_BOOT_MAPPING=$(CMOS_IS_FIRST_BOOT_MAPPING)\" \
    /D\"CMOS_BATTERY_TEST_MAPPING=$(CMOS_BATTERY_TEST_MAPPING)\" \
    /D\"CMOS_IS_USABLE_MAPPING=$(CMOS_IS_USABLE_MAPPING)\" \
    /D\"CMOS_IS_COLD_BOOT_MAPPING=$(CMOS_IS_COLD_BOOT_MAPPING)\" \
    /DPEI_COMPILE 
    

{$(PROJECT_DIR)\Core\EM\CmosManager}.c{$(BUILD_DIR)\Core\EM\CmosManager\Pei}.obj:: 
	$(CC) $(CMOS_PEI_CFLAGS) /Fo$(BUILD_DIR)\Core\EM\CmosManager\Pei\ $<

CMOS_MANAGER_PEI_OBJECTS = \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI\CmosTables.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI\CmosAccess.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI\CmosBoard.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI\CmosManager.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI\CmosManagerHob.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\PEI\CmosManagerPei.obj

CmosManagerPeiBin : $(AMIPEILIB) $(AMICSPLib) $(CMOS_MANAGER_PEI_OBJECTS)
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\CmosManagerPei.mak all \
		NAME=CmosManagerPei \
        "OBJECTS=" \
	    "CFLAGS=$(CMOS_PEI_CFLAGS)" \
        TYPE=PEI_LIBRARY \
        LIBRARY_NAME=$(BUILD_DIR)\CmosManagerPei.lib



#---------------------------------------------------------------------------
#		CMOS Manager DXE library component
#---------------------------------------------------------------------------

CMOS_MANAGER_DXE: $(BUILD_DIR)\CmosManagerDxe.mak CmosManagerDxeBin

CORE_DXEBin : $(BUILD_DIR)\CmosManagerDxe.lib

$(BUILD_DIR)\CmosManagerDxe.lib : CMOS_MANAGER_DXE

$(BUILD_DIR)\CmosManagerDxe.mak : $(CMOS_MANAGER_MAK_DEPS) $(BUILD_RULES)
!IF !EXIST($(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE)
	mkdir $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE
!ENDIF
	$(CIF2MAK) $(CMOS_MANAGER_DIR)\CmosManager.cif $(CIF2MAK_DEFAULTS)

CMOS_DXE_CFLAGS = \
    $(CFLAGS) \
    $(CMOS_MGR_CFLAGS) \
    /D\"CMOS_PORT_MAPPING=$(CMOS_PORT_MAPPING)\" \
    /D\"CMOS_IS_BSP_MAPPING=$(CMOS_IS_BSP_MAPPING)\" \
    /D\"CMOS_IS_FIRST_BOOT_MAPPING=$(CMOS_IS_FIRST_BOOT_MAPPING)\" \
    /D\"CMOS_BATTERY_TEST_MAPPING=$(CMOS_BATTERY_TEST_MAPPING)\" \
    /D\"CMOS_IS_USABLE_MAPPING=$(CMOS_IS_USABLE_MAPPING)\" \
    /D\"CMOS_IS_COLD_BOOT_MAPPING=$(CMOS_IS_COLD_BOOT_MAPPING)\" 

{$(PROJECT_DIR)\Core\EM\CmosManager}.c{$(BUILD_DIR)\Core\EM\CmosManager\Dxe}.obj::
	$(CC) $(CMOS_DXE_CFLAGS) /Fo$(BUILD_DIR)\Core\EM\CmosManager\Dxe\ $<

CMOS_MANAGER_DXE_OBJECTS = \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosAccess.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosBoard.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosManager.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosManagerHob.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosManagerDxe.obj 

CmosManagerDxeBin :  $(AMICSPLib) $(AMIDXELIB) $(CMOS_MANAGER_DXE_OBJECTS)
	@set INCLUDE=%%INCLUDE%%
    echo $(CMOS_PORT_MAPPING)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\CmosManagerDxe.mak all \
		NAME=CmosManagerDxe \
        "CFLAGS=$(CMOS_DXE_CFLAGS)" \
		"OBJECTS=" \
        TYPE=LIBRARY \
        LIBRARY_NAME=$(BUILD_DIR)\CmosManagerDxe.lib \
        LIBRARIES=\


#---------------------------------------------------------------------------
#		CMOS Manager SMM DXE driver component
#---------------------------------------------------------------------------


CMOS_MANAGER_SMM: $(BUILD_DIR)\CmosManagerSmm.mak CmosManagerSmmBin

$(BUILD_DIR)\CmosManagerSmm.mak : $(CMOS_MANAGER_MAK_DEPS) $(BUILD_RULES)
!IF !EXIST($(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SMM)
	mkdir $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SMM
!ENDIF
	$(CIF2MAK) $(CMOS_MANAGER_DIR)\CmosManager.cif $(CIF2MAK_DEFAULTS)

CMOS_SMM_CFLAGS = \
    $(CFLAGS) \
    $(CMOS_MGR_CFLAGS) \
    /D\"CMOS_PORT_MAPPING=$(CMOS_PORT_MAPPING)\" \
    /D\"CMOS_IS_BSP_MAPPING=$(CMOS_IS_BSP_MAPPING)\" \
    /D\"CMOS_IS_FIRST_BOOT_MAPPING=$(CMOS_IS_FIRST_BOOT_MAPPING)\" \
    /D\"CMOS_BATTERY_TEST_MAPPING=$(CMOS_BATTERY_TEST_MAPPING)\"\
    /D\"CMOS_IS_USABLE_MAPPING=$(CMOS_IS_USABLE_MAPPING)\" \
    /D\"CMOS_IS_COLD_BOOT_MAPPING=$(CMOS_IS_COLD_BOOT_MAPPING)\" \
    /DSMM_COMPILE 

{$(PROJECT_DIR)\Core\EM\CmosManager}.c{$(BUILD_DIR)\Core\EM\CmosManager\Smm}.obj::
	$(CC) $(CMOS_SMM_CFLAGS) /Fo$(BUILD_DIR)\Core\EM\CmosManager\Smm\ $<

# CmosAccess and CmosBoard are not SMM-buid dependent
CMOS_MANAGER_SMM_OBJECTS = \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosAccess.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\DXE\CmosBoard.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SMM\CmosTables.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SMM\CmosManager.obj \
    $(BUILD_DIR)\$(CMOS_MANAGER_DIR)\SMM\CmosManagerSmm.obj

CmosManagerSmmBin :  $(AMICSPLib) $(AMIDXELIB) $(CMOS_MANAGER_SMM_OBJECTS)
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\CmosManagerSmm.mak all \
		GUID=6869C5B3-AC8D-4973-8B37-E354DBF34ADD\
		NAME=CmosManagerSmm \
		ENTRY_POINT=CmosManagerSmmEntry\
		"OBJECTS=" \
        "CFLAGS=$(CMOS_SMM_CFLAGS)" \
        TYPE=BS_DRIVER \
        DEPEX1=$(CMOS_MANAGER_DIR)\CmosManagerSmm.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1


#---------------------------------------------------------------------------
#		CMOS Manager setup database build script
#---------------------------------------------------------------------------

!IF "$(CMOS_SETUP_SUPPORT)" == "1"

SetupSdbs : $(BUILD_DIR)\CmosSetup.sdb

$(BUILD_DIR)\CmosSetup.sdb : $(CMOS_MANAGER_DIR)\$(@B).sd $(CMOS_MANAGER_DIR)\$(@B).uni
    $(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(CMOS_MANAGER_DIR)\$(@B).uni
    $(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(CMOS_MANAGER_DIR)\$(@B).sd

!ENDIF

#---------------------------------------------------------------------------
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
