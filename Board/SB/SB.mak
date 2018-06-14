#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SB.mak 13    8/22/13 3:01a Barretlin $
#
# $Revision: 13 $
#
# $Date: 8/22/13 3:01a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Board/SB.mak $
# 
# 13    8/22/13 3:01a Barretlin
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	make sure CRB without SIO solution only for SharkBay
# MB/ULT CRB
# [Files]  		SB.sdl SB.mak
# 
# 12    7/30/13 3:05a Scottyang
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Support CRB without Super IO.
# [Files]  		SB.sdl, SB.mak
# 
# 11    5/28/13 11:33p Scottyang
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change IASL compiler path.
# [Files]  		SB.mak
# 
# 10    1/10/13 8:18a Scottyang
# [TAG]  		EIP111666
# [Category]  	New Feature
# [Description]  	Support OEM reset callback function Elink.
# [Files]  		SB.mak, SBCspLib.h, SBGeneric.c, SB.sdl, PchReset.c
# 
# 9     12/18/12 6:38a Scottyang
# [TAG] EIP109697
# [Category] Improvement
# [Description] Update PCH RC 0.8.1
# [Files] ReferenceCode\Chipset\LynxPoint\*.*, SBDxe.c, SBPEI.c, SB.sd,
# SbSetupData.c, GetSetupDate.c
# 
# 8     11/20/12 9:52p Scottyang
# [TAG] None
# [Category] Improvement
# 
# [Description] Change ASL build path by token. 
# 
# [Files] SB.sdl, SB.mak
# 
# 7     11/19/12 3:55a Scottyang
# [TAG]  		EIP106353
# [Category]  	Bug Fix
# [Severity]  	Critical
# [Symptom]  	The system has assert error when PFAT is Disabled and Debug
# Mode is Enabled.
# [RootCause]  	Use build time PFAT flag that make some code not run whrn
# PFAT disable.
# [Solution]  	Detect PFAT flag useing MSR. 
# [Files]  		SBGeneric, SB.mak
# 
# 6     10/23/12 3:11a Scottyang
# [TAG]      EIP84560
# [Category] Bug Fix
# [Symptom]  Can't enter Win8 after Win8 AHCI driver version:11.5.0.1122
# install.
# [Solution] fixed in EIP84560
# [Files]    sb.sdl, sb.mak, sata.asl
# 
# 5     9/26/12 3:48a Victortu
# [TAG]           None
# [Category]      Improvement
# [Description]   Update from EIP#95440 to resolve the RAID driver
# compatibility issue.
# [Files]         SB.mak, SB.sdl, SBDXE.c
# 
# 4     9/12/12 5:10a Victortu
# [TAG]           None
# [Category]      Improvement
# [Description]   Support OEM update VSCC table.
# [Files]         SB.H, SB.mak, SB.sdl, SBDXE.c
# 
# 3     7/27/12 6:03a Victortu
# Update to support ULT Platform.
# 
# 2     6/13/12 11:33p Victortu
# [TAG]           None
# [Category]      Improvement
# [Description]   Implement Warm Boot function for Secure Flash feature.
# [Files]         SB.H, SB.mak, SB.sdl, SBDxe.c, SBGeneric.c, SBPEI.c,
# SBSMI.c
# 
# 1     2/08/12 8:22a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         SB.mak
#
# Description:  This make file builds South bridge SEC,PEI & DXE
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************

all : SBPEI SBDXE SBRun SBCSPLibBin SBSATAIDE

BUILD_SB_BOARD_DIR = $(BUILD_DIR)\$(SB_BOARD_DIR)
BUILD_SB_CHIPSET_DIR = $(BUILD_DIR)\$(SB_CHIPSET_DIR)

CFLAGS = $(CFLAGS) /I$(SB_BOARD_DIR) /I$(SB_CHIPSET_DIR) 

#----------------------------------------------------------------------------
#           Generic SB dependencies
#----------------------------------------------------------------------------
$(BUILD_DIR)\SB.mak : $(SB_BOARD_DIR)\SBBoard.cif $(SB_CHIPSET_DIR)\SBCSP.cif $(BUILD_RULES)
    $(CIF2MAK) $(SB_BOARD_DIR)\SBBoard.cif $(CIF2MAK_DEFAULTS) $(SB_CHIPSET_DIR)\SBCSP.cif

#----------------------------------------------------------------------------
#           Add files into CSP Library
#----------------------------------------------------------------------------

$(BUILD_DIR)\AMICSPLIBInc.H : $(SB_BOARD_DIR)\sb.h $(SB_CHIPSET_DIR)\SBCspLib.h $(SB_BOARD_DIR)\SbSetupData.h
AMICSPLibBin : $(SBCSPLib)

SB_CSP_OBJECTS =\
$$(BUILD_DIR)\$(SB_CHIPSET_DIR)\SBGeneric.obj \
$$(BUILD_DIR)\$(SB_BOARD_DIR)\GetSetupData.obj
SB_RUN_LISTS = \
/D\"SB_RUN_RESET_CALLBACK_LIST=$(SbRuntimeResetElinkList)\"

$(SBCSPLib) : $(BUILD_DIR)\SB.mak SBCSPLibBin

SBCSPLibBin :
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Sb.mak all\
        NAME=AMISBCSPLib\
        MAKEFILE=$(BUILD_DIR)\Sb.mak\
        OBJECTS="$(SB_CSP_OBJECTS)"\
        TYPE=LIBRARY\
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES) $(PROJECT_CPU_INCLUDES)" \
        "CFLAGS=$(CFLAGS) $(SB_RUN_LISTS) /D\"SB_OEM_SETUP_CALLBACK_LIST=$(SbConfigurationList)\" /D\"SB_OEM_S3_WARMRESET_CALLBACK_LIST=$(SbS3WarmResetLink)\"" 
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Sb.mak all\
        BUILD_DIR=$(BUILD_DIR)\IA32\
        NAME=AMISBCSPLib\
        MAKEFILE=$(BUILD_DIR)\Sb.mak\
        OBJECTS="$(SB_CSP_OBJECTS)"\
        TYPE=PEI_LIBRARY\
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES) $(PROJECT_CPU_INCLUDES)" \
        "CFLAGS=$(CFLAGS) $(SB_RUN_LISTS) /D\"SB_OEM_SETUP_CALLBACK_LIST=$(SbConfigurationList)\" /D\"SB_OEM_S3_WARMRESET_CALLBACK_LIST=$(SbS3WarmResetLink)\""

#----------------------------------------------------------------------------
#           Add files for SB SEC code
#----------------------------------------------------------------------------
CREATE_SB_SEC : $(BUILD_DIR)\SBSECInit.OBJ

SB_SEC_ASM_FLAGS = /c /nologo /Sa $(SB_INCLUDES)
!if "$(SEC_CREATE_PE32)" == "1"
SB_SEC_ASM_FLAGS = $(SB_SEC_ASM_FLAGS) /coff
!endif

$(BUILD_DIR)\SBSECInit.OBJ : $(SB_BOARD_DIR)\SBSECInit.asm
  $(ASM) $(SB_SEC_ASM_FLAGS) /I$(SB_BOARD_DIR) /Fo$(BUILD_DIR)\SBSECInit.obj $(SB_BOARD_DIR)\SBSECInit.asm

#----------------------------------------------------------------------------
#       Create SB PEI Component
#----------------------------------------------------------------------------
SBPEI : $(BUILD_DIR)\SBGPIO.h $(BUILD_DIR)\SB.mak SBPEIBin

$(BUILD_DIR)\SBGPIO.h:
	copy << $(BUILD_DIR)\sbgpio.bat
@echo off
for /L %%i in (0, 1, 9) do (
        @echo #ifdef GPIO_00%%i>> $(BUILD_DIR)\SBGPIO.h
	@echo { %%i, GPIO_00%%i },>> $(BUILD_DIR)\SBGPIO.h
	@echo #endif>> $(BUILD_DIR)\SBGPIO.h
)
for /L %%i in (10, 1, 95) do (
        @echo #ifdef GPIO_0%%i>> $(BUILD_DIR)\SBGPIO.h
	@echo { %%i, GPIO_0%%i },>> $(BUILD_DIR)\SBGPIO.h
	@echo #endif>> $(BUILD_DIR)\SBGPIO.h
)
        @echo { 0xFFFF, 0xFFFF }>> $(BUILD_DIR)\SBGPIO.h
<<
	$(BUILD_DIR)\sbgpio.bat

SB_PEI_OBJECTS = $$(BUILD_DIR)\$(SB_BOARD_DIR)\SBPeiBoard.obj \
$$(BUILD_DIR)\$(SB_BOARD_DIR)\GetSetupData.obj \
$$(BUILD_DIR)\$(SB_CHIPSET_DIR)\SBPei.obj

SBPEIBin : $(AMIPEILIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SB.mak all\
        NAME=SBPEI\
        MAKEFILE=$(BUILD_DIR)\SB.mak \
!IF "$(x64_BUILD)"=="1"
	BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
	BUILD_DIR=$(BUILD_DIR)\
!ENDIF
        OBJECTS="$(SB_PEI_OBJECTS)" \
        GUID=C1FBD624-27EA-40d1-AA48-94C3DC5C7E0D \
        "CFLAGS=$(CFLAGS) /D\"SB_OEM_SETUP_CALLBACK_LIST=$(SbConfigurationList)\""\
        ENTRY_POINT=SBPEI_Init \
        TYPE=PEIM \
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES) $(ME_INCLUDES)" \
        DEPEX1=$(SB_BOARD_DIR)\SBPEI.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        COMPRESS=0

# FILE GUID for SBPEI BIN
#// {C1FBD624-27EA-40d1-AA48-94C3DC5C7E0D}
#DEFINE_GUID(<<name>>,
#0xc1fbd624, 0x27ea, 0x40d1, 0xaa, 0x48, 0x94, 0xc3, 0xdc, 0x5c, 0x7e, 0xd);

#----------------------------------------------------------------------------
#       Create SB DXE Component
#----------------------------------------------------------------------------
SBDXE : $(BUILD_DIR)\SB.MAK SBDXEBin

#$(BUILD_DIR)\SBDXE.mak : $(SB_BOARD_DIR)\SBBoard.cif $(SB_CHIPSET_DIR)\SBCSP.cif $(BUILD_RULES)
#   $(CIF2MAK) $(SB_BOARD_DIR)\SBDXEBoard.cif $(CIF2MAK_DEFAULTS) $(SB_CHIPSET_DIR)\SBDXE.cif

SB_DXE_OBJECTS = $(BUILD_SB_BOARD_DIR)\SBDxeBoard.obj \
$(BUILD_SB_BOARD_DIR)\GetSetupData.obj \
$(BUILD_SB_CHIPSET_DIR)\SBSmm.obj \
$(BUILD_SB_CHIPSET_DIR)\SBDxe.obj

SBDXEBin : $(AMICSPLib) $(AMIDXELIB) $(DxeKscLib_LIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SB.mak all\
        NAME=SBDXE\
        MAKEFILE=$(BUILD_DIR)\SB.mak \
        OBJECTS="$(SB_DXE_OBJECTS)" \
        GUID=B7D19491-E55A-470d-8508-85A5DFA41974 \
        ENTRY_POINT=SBDXE_Init \
	"CFLAGS=$(CFLAGS) $(ACPI_PLATFORM_INCLUDES) $(DxeKscLib_INCLUDES) $(INTEL_PCH_INCLUDES) $(ME_INCLUDES) /D\"OEM_HDA_VERB_TABLE=$(OEM_HDA_VERB_TABLE)\" /D\"OEM_HDA_VERB_TABLE_CONTENT=$(OEM_HDA_VERB_TABLE_CONTENT)\" /D\"SAVE_RESTORE_CALLBACK_LIST=$(SbTimerSaveRestoreRegistersCallbacks)\" /D\"SB_OEM_SETUP_CALLBACK_LIST=$(SbConfigurationList)\" /D\"OEM_SPI_VSCC_TABLE=$(OEM_SPI_VSCC_TABLE)\" /D\"BUS_OVERRIDE_GUIDS_FOR_RAID=$(BusOverrideGuidsforUefiRaid)\""\
        TYPE=BS_DRIVER \
        DEPEX1=$(SB_BOARD_DIR)\SBDXE.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

# FILE GUID for SBDXE BIN
#// {B7D19491-E55A-470d-8508-85A5DFA41974}
#DEFINE_GUID(<<name>>,
#0xb7d19491, 0xe55a, 0x470d, 0x85, 0x8, 0x85, 0xa5, 0xdf, 0xa4, 0x19, 0x74);

#----------------------------------------------------------------------------
#       Create SB Runtime DXE Component
#----------------------------------------------------------------------------
SBRun : $(BUILD_DIR)\SB.MAK SBRunBin

SB_RUN_OBJECTS = $(BUILD_SB_CHIPSET_DIR)\SBRun.obj

SBRunBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\SB.mak all\
        NAME=SBRun\
        MAKEFILE=$(BUILD_DIR)\SB.mak \
        OBJECTS="$(SB_RUN_OBJECTS)" \
        "CFLAGS=$(CFLAGS) /I$(SB_BOARD_DIR)"\
        GUID=E23F86E1-056E-4888-B685-CFCD67C179D4 \
        ENTRY_POINT=SBRun_Init \
        TYPE=RT_DRIVER \
        DEPEX1=$(SB_BOARD_DIR)\SBRun.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

# FILE GUID for SBRun BIN
#// {E23F86E1-056E-4888-B685-CFCD67C179D4}
#DEFINE_GUID(<<name>>, 
#0xe23f86e1, 0x56e, 0x4888, 0xb6, 0x85, 0xcf, 0xcd, 0x67, 0xc1, 0x79, 0xd4);

#        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
#----------------------------------------------------------------------------
#       SB Debugger Initialization
#----------------------------------------------------------------------------
PEI_SB_DBG_FLAGS = $(CFLAGS) \
!IF "$(USB_DEBUG_TRANSPORT)" == "1"
    /DUSB_DEBUGGER
!ENDIF

$(BUILD_SB_BOARD_DIR)\SBPeiDebugger.obj : $(PROJECT_DIR)\$(SB_BOARD_DIR)\SBPeiDebugger.c
    $(CC) $(PEI_SB_DBG_FLAGS) $(INTEL_PCH_INCLUDES) /Fo$(BUILD_SB_BOARD_DIR)\SBPeiDebugger.obj $(PROJECT_DIR)\$(SB_BOARD_DIR)\SBPeiDebugger.c

!IF "$(CRB_UART_CONFIG)" == "1"
CORE_PEIBin   : $(BUILD_SB_BOARD_DIR)\SBPeiDebugger.obj $(AMICSPLib)
!ENDIF

PeiDbgPortBin : $(BUILD_SB_BOARD_DIR)\SBPeiDebugger.obj $(AMICSPLib)

IchEhciDbgBin : $(BUILD_SB_BOARD_DIR)\SBPeiDebugger.obj $(AMICSPLib)

SBSATAIDE: $(BUILD_DIR)\SBSATAIDE.ffs
#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
$(BUILD_DIR)\SATA.aml $(BUILD_DIR)\IDE.aml : $(BUILD_DIR)\SATA.asl $(BUILD_DIR)\IDE.asl
	$(SILENT)$(IASL) -p $@ $*.asl

$(BUILD_DIR)\SATA.sec $(BUILD_DIR)\IDE.sec : $(BUILD_DIR)\SATA.aml $(BUILD_DIR)\IDE.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW


$(BUILD_DIR)\SBSATAIDE.ffs: $(BUILD_DIR)\SATA.sec $(BUILD_DIR)\IDE.sec 
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\SBSATAIDE.pkg

PACKAGE.INF
[.]
BASE_NAME                   = SBSATAIDE
FFS_FILEGUID                = 22046D50-F390-498c-92E5-5BA4F8E7F8B6
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\SATA.sec
	$(PROJECT_DIR)\$(BUILD_DIR)\IDE.sec
  }
}
<<KEEP

#-----------------------------------------------------------------------#
#		Process SBSATAIDE asl files
#-----------------------------------------------------------------------#
$(BUILD_DIR)\SATA.asl $(BUILD_DIR)\IDE.asl : $(INTEL_SATA_ASL_FILE) $(INTEL_IDE_ASL_FILE)
    $(CP) /I$(SB_CHIPSET_DIR) /FItoken.h /FItokenAsl.h /C $(SB_CHIPSET_DIR)\$(@F) > $@
# include the token.h if needed to check for SDL flags
#  /FItoken.h

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
