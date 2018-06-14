#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
# $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRB.mak 7     3/17/14 2:45a Chaseliu $
#
# $Revision: 7 $
#
# $Date: 3/17/14 2:45a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/CRB/CRB.mak $
# 
# 7     3/17/14 2:45a Chaseliu
# Add CRBTse for EIP151535
# 
# 6     6/05/13 4:42a Thomaschen
# Removing AMI_SEC_ROM before compile.
# 
# 4     4/16/13 5:19a Thomaschen
# Modify for compile order.
# 
# 3     8/25/12 4:49a Wesleychen
# Clear temp files by NMAKE-generated to avoid files overflow.
# 
# 2     2/24/12 8:54a Victortu
# Use SharkBay RomImage module.
# 
# 1     2/12/12 10:38p Victortu
# Intel SharkBay CRB initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         CRB.mak
#
# Description:  This make file builds Chipset Reference Board SEC,PEI & DXE
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************
!IFNDEF PI_SPECIFICATION_VERSION
PI_SPECIFICATION_VERSION = 0
!ENDIF

PREPARE : RemoveSecRom

RemoveSecRom :
  if exist $(AMI_SEC_ROM) del $(AMI_SEC_ROM)

all : CRBPEI CRBDXE CRBSMI CRBCSPLibBin
#following definitions moved in CRB.sdl as a Path Tokens
BUILD_CRB_DIR = $(BUILD_DIR)\$(CRB_DIR)

#----------------------------------------------------------------------------
#           Generic CRB dependencies
#----------------------------------------------------------------------------
$(BUILD_DIR)\CRB.mak : $(CRB_DIR)\CRBoard.cif $(BUILD_RULES)
    $(CIF2MAK) $(CRB_DIR)\CRBoard.cif $(CIF2MAK_DEFAULTS)

#----------------------------------------------------------------------------
#           Add files into CSP Library
#----------------------------------------------------------------------------
$(BUILD_DIR)\AMICSPLIBInc.H : $(CRB_DIR)\CRBLib.h
AMICSPLibBin : $(CRBCSPLib)

CRB_LIB_OBJECTS = $$(BUILD_DIR)\$(CRB_DIR)\CRBLib.obj

$(CRBCSPLib) : $(BUILD_DIR)\Crb.mak CRBCSPLibBin

CRBCSPLibBin :
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Crb.mak all\
        NAME=AMICRBCSPLib\
        MAKEFILE=$(BUILD_DIR)\Crb.mak\
        OBJECTS="$(CRB_LIB_OBJECTS)"\
        TYPE=LIBRARY
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Crb.mak all\
        BUILD_DIR=$(BUILD_DIR)\IA32\
        NAME=AMICRBCSPLib\
        MAKEFILE=$(BUILD_DIR)\Crb.mak\
        OBJECTS="$(CRB_LIB_OBJECTS)"\
        TYPE=PEI_LIBRARY

#----------------------------------------------------------------------------
#           Add files for CRB SEC code
#----------------------------------------------------------------------------
CREATE_CRB_SEC : $(BUILD_DIR)\CRBSEC.OBJ

CRB_SEC_ASM_FLAGS = /c /nologo /Sa
!if "$(SEC_CREATE_PE32)" == "1"
CRB_SEC_ASM_FLAGS = $(CRB_SEC_ASM_FLAGS) /coff
!endif

$(BUILD_DIR)\CRBSEC.OBJ : $(CRB_DIR)\CRBSEC.asm
  $(ASM) $(CRB_SEC_ASM_FLAGS) /I$(CRB_DIR) /Fo$(BUILD_DIR)\CRBSEC.obj $(CRB_DIR)\CRBSEC.asm

#----------------------------------------------------------------------------
#       Create CRB PEI Component
#----------------------------------------------------------------------------
CRBPEI : $(BUILD_DIR)\CRB.mak CRBPEIBin

CRB_PEI_OBJECTS = $(BUILD_CRB_DIR)\CRBPEI.obj

CRBPEIBin : $(AMIPEILIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CRB.mak all\
        NAME=CRBPEI\
        MAKEFILE=$(BUILD_DIR)\CRB.mak \
        OBJECTS="$(CRB_PEI_OBJECTS)" \
        GUID=0D1ED2F7-E92B-4562-92DD-5C82EC917EAE \
        ENTRY_POINT=CRBPEI_Init \
        TYPE=PEIM \
        "CFLAGS=$(CFLAGS) /I$(NB_CHIPSET_DIR) /I$(NB_BOARD_DIR) /I$(SB_CHIPSET_DIR) /I$(SB_BOARD_DIR) $(INTEL_PCH_INCLUDES)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        DEPEX1=$(CRB_DIR)\CRBPEI.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        COMPRESS=0

# FILE GUID for CRBPEI BIN
#// {0D1ED2F7-E92B-4562-92DD-5C82EC917EAE}
#DEFINE_GUID(<<name>>, 
#0xd1ed2f7, 0xe92b, 0x4562, 0x92, 0xdd, 0x5c, 0x82, 0xec, 0x91, 0x7e, 0xae);

#----------------------------------------------------------------------------
#       Create CRB DXE Component
#----------------------------------------------------------------------------
CRBDXE : $(BUILD_DIR)\CRB.MAK CRBDXEBin

CRB_DXE_OBJECTS = $(BUILD_CRB_DIR)\CRBDXE.obj \

CRBDXEBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CRB.mak all\
        NAME=CRBDXE\
        MAKEFILE=$(BUILD_DIR)\CRB.mak \
        OBJECTS="$(CRB_DXE_OBJECTS)" \
        GUID=16271FCA-55D9-4a33-93FC-5A3EB128DEB6 \
        ENTRY_POINT=CRBDXE_Init \
        "CFLAGS=$(CFLAGS) /I$(NB_CHIPSET_DIR) /I$(NB_BOARD_DIR) /I$(SB_CHIPSET_DIR) /I$(SB_BOARD_DIR)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        TYPE=BS_DRIVER \
        DEPEX1=$(CRB_DIR)\CRBDXE.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

# FILE GUID for CRBDXE BIN
#// {16271FCA-55D9-4a33-93FC-5A3EB128DEB6}
#DEFINE_GUID(<<name>>, 
#0x16271fca, 0x55d9, 0x4a33, 0x93, 0xfc, 0x5a, 0x3e, 0xb1, 0x28, 0xde, 0xb6);

#----------------------------------------------------------------------------
#       Create CRB SMI Component
#----------------------------------------------------------------------------
CRBSMI : $(BUILD_DIR)\CRB.MAK CRBSMIBin

CRB_SMI_OBJECTS = $(BUILD_CRB_DIR)\CRBSMI.obj

CRBSMIBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CRB.mak all\
        NAME=CRBSMI\
        MAKEFILE=$(BUILD_DIR)\CRB.mak \
        OBJECTS="$(CRB_SMI_OBJECTS)" \
        GUID=221F1D4F-034C-4bea-B2BB-B7A9672B06D7 \
        ENTRY_POINT=InitializeCRBSmm \
        "CFLAGS=$(CFLAGS) /I$(NB_CHIPSET_DIR) /I$(NB_BOARD_DIR) /I$(SB_CHIPSET_DIR) /I$(SB_BOARD_DIR)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
!IF $(PI_SPECIFICATION_VERSION) >= 0x1000A
        TYPE=SMM_DRIVER \
        DEPEX1=$(CRB_DIR)\CRBSMI.DXS \
!ELSE
        TYPE=BS_DRIVER \
        DEPEX1=$(CRB_DIR)\CRBSMI.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
!ENDIF
        COMPRESS=1

# FILE GUID for CRBSMI BIN
#// {221F1D4F-034C-4bea-B2BB-B7A9672B06D7}
#DEFINE_GUID(<<name>>, 
#0x221f1d4f, 0x34c, 0x4bea, 0xb2, 0xbb, 0xb7, 0xa9, 0x67, 0x2b, 0x6, 0xd7);

#----------------------------------------------------------------------------
#       Create CRB TSE Component
#----------------------------------------------------------------------------
AMITSEBin :  $(BUILD_DIR)\CRBTSE.obj

CRBTSE_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)

$(BUILD_DIR)\CRBTSE.obj : $(CRB_DIR)\CRBTse.c
  	$(CC) $(CRBTSE_CFLAGS) /Fo$(BUILD_DIR)\CRBTSE.obj $(CRB_DIR)\CRBTse.c
#----------------------------------------------------------------------------
#		Create CRB ACPI Object
#----------------------------------------------------------------------------
$(BUILD_DIR)\CrbAcpi.obj: $(CRB_DIR)\CrbAcpi.c
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(CRB_DIR)\CrbAcpi.c /I$(NB_CHIPSET_DIR) /I$(NB_BOARD_DIR) /I$(SB_CHIPSET_DIR) /I$(SB_BOARD_DIR)

AcpiModeEnableBin: $(BUILD_DIR)\CrbAcpi.obj

#----------------------------------------------------------------------------
#       Create CRB Setup Screens
#----------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\CRB.mak CRBSDB
SetupBin : $(BUILD_DIR)\CRBSetup.obj

CRBSDB :
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CRB.mak all\
        TYPE=SDB NAME=CRB STRING_CONSUMERS=$(CRB_DIR)\CRB.sd

$(BUILD_DIR)\CRBSetup.obj : $(CRB_DIR)\CRBSetup.c $(BUILD_DIR)\SetupStrTokens.h
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(CRB_DIR)\CRBSetup.c

#----------------------------------------------------------------------------
#       Nested FV
#----------------------------------------------------------------------------
BEFORE_FV:
	del $(BUILD_DIR)\FV_MAIN_NESTED__.ffs

!IF $(LZMA_SUPPORT)
FV_MAIN_CRB_DESCRIPTOR=FV(\
name=FV_MAIN, address=$(FV_MAIN_BASE),\
offset=$(FV_MAIN_BASE)-$(FLASH_BASE),\
size=$(FV_MAIN_BLOCKS)*$(FLASH_BLOCK_SIZE),\
!IF "$(FV_MAIN_NESTED)"!=""
file_list=$(BUILD_DIR)\FV_MAIN_NESTED.ffs $(FV_MAIN_OUTSIDE_NESTED),\
attr=ROM_AREA_FV_PEI+ROM_AREA_FV_DXE+ROM_AREA_FV_NFV_PRESENT+ROM_AREA_FV_SIGNED\
!ELSE
file_list=$(FV_MAIN),\
attr=ROM_AREA_FV_PEI+ROM_AREA_FV_DXE+ROM_AREA_FV_SIGNED\
!ENDIF
)
!ENDIF

END: CLEAN_TEMP

# Clean NMAKE-generated temporary files
CLEAN_TEMP:
    @if exist $(TEMP)\nm*.tmp del /F /S /Q $(TEMP)\nm*.tmp > NUL
    @if exist $(TMP)\nm*.tmp del /F /S /Q $(TMP)\nm*.tmp > NUL  

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
