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
# $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NB.mak 7     4/01/13 9:55p Ireneyang $
#
# $Revision: 7 $
#
# $Date: 4/01/13 9:55p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Board/NB.mak $               
# 
# 7     4/01/13 9:55p Ireneyang
# [TAG]          None
# [Severity]     Improvement
# [Description]  Reduce boot time through PEG.
# [Files]        NB.mak; NBDxe.c; NBPEI.c; NBPPI.h; Sa.asl;
#                PcieComplex.c; GraphicsInit.c; PciExpressInit.c;
# 
# 4     3/12/13 2:31a Ireneyang
# [TAG]          None
# [Severity]     Improvement
# [Description]  Remove related SaSsdt acpi data to DSDT
# [Files]        SaInit.c; INTELGFX.ASL; Sa.asl; SaSsdt.asl; 
#                SaSsdtTables.sdl; NBDxe.c; NB.mak;
# 
# 3     1/03/13 7:32a Jeffch
# [TAG]          None
# [Severity]     Spec update
# [Description]  Follow MRC error report status.
# [Files]        NBPei.c; NB.mak;
# 
# 2     10/14/12 12:42a Jeffch
# [TAG]          None
# [Severity]     Important
# [Description]  Update by XTU4.0.
# [Files]        NB.h, GetSetupData.c, NbSetupData.h
# [TAG]          None
# [Severity]     Important
# [Description]  Follow Update by Mahobay.
# [Files]        NB.sdl, NB.mak.c; NBDXEBoard.c
# 
# 1     2/08/12 4:32a Yurenlai
# Intel Haswell/NB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         NB.mak
#
# Description:  This make file builds north bridge SEC,PEI & DXE
#               components and link them to respective binary
#
#<AMI_FHDR_END>
#*************************************************************************

!IFNDEF NB_MAK_INCLUSION_FLAG
NB_MAK_INCLUSION_FLAG = 1

all : NBPEI NBDXE NBCSPLibBin

BUILD_NB_BOARD_DIR = $(BUILD_DIR)\$(NB_BOARD_DIR)
BUILD_NB_CHIPSET_DIR = $(BUILD_DIR)\$(NB_CHIPSET_DIR)

#----------------------------------------------------------------------------
#           Generic NB dependencies
#----------------------------------------------------------------------------
$(BUILD_DIR)\NB.mak : $(NB_BOARD_DIR)\NBBoard.cif $(NB_CHIPSET_DIR)\NBCSP.cif $(BUILD_RULES)
    $(CIF2MAK) $(NB_BOARD_DIR)\NBBoard.cif $(CIF2MAK_DEFAULTS) $(NB_CHIPSET_DIR)\NBCSP.cif

$(BUILD_DIR)\nbint15.obj: $(NB_BOARD_DIR)\nbint15.asm
	$(ASM) /c /nologo /Fo$(BUILD_DIR)\ $(NB_BOARD_DIR)\nbint15.asm
#----------------------------------------------------------------------------
#           Add files into CSP Library
#----------------------------------------------------------------------------
$(BUILD_DIR)\AMICSPLIBInc.H : $(NB_BOARD_DIR)\nb.h $(NB_CHIPSET_DIR)\NBCspLib.h $(NB_BOARD_DIR)\NbSetupData.h
AMICSPLibBin : $(NBCSPLib)

NB_CSP_OBJECTS =\
$$(BUILD_DIR)\$(NB_CHIPSET_DIR)\NBGeneric.obj \
$$(BUILD_DIR)\$(NB_CHIPSET_DIR)\NBPciCSP.obj \
$$(BUILD_DIR)\$(NB_BOARD_DIR)\GetSetupData.obj

$(NBCSPLib) : $(BUILD_DIR)\NB.mak NBCSPLibBin 

NBCSPLibBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Nb.mak all\
		NAME=AMINBCSPLib\
        MAKEFILE=$(BUILD_DIR)\Nb.mak\
		OBJECTS="$(NB_CSP_OBJECTS)"\
		TYPE=LIBRARY\
        "CFLAGS=$(CFLAGS) /D\"NB_OEM_SETUP_CALLBACK_LIST=$(NbConfigurationList)\"" 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Nb.mak all\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		NAME=AMINBCSPLib\
        MAKEFILE=$(BUILD_DIR)\Nb.mak\
		OBJECTS="$(NB_CSP_OBJECTS)"\
		TYPE=PEI_LIBRARY\
        "CFLAGS=$(CFLAGS) /D\"NB_OEM_SETUP_CALLBACK_LIST=$(NbConfigurationList)\""

#----------------------------------------------------------------------------
#           Add files for NB SEC code
#----------------------------------------------------------------------------
CREATE_NB_SEC : $(BUILD_DIR)\NBSECInit.OBJ

NB_SEC_ASM_FLAGS = /c /nologo /Sa
!if "$(SEC_CREATE_PE32)" == "1"
NB_SEC_ASM_FLAGS = $(NB_SEC_ASM_FLAGS) /coff
!endif

$(BUILD_DIR)\NBSECInit.OBJ : $(NB_BOARD_DIR)\NBSECInit.asm
  $(ASM) $(NB_SEC_ASM_FLAGS) /I$(NB_BOARD_DIR) /Fo$(BUILD_DIR)\NBSECInit.obj $(NB_BOARD_DIR)\NBSECInit.asm

#----------------------------------------------------------------------------
#       Create NB PEI Component
#----------------------------------------------------------------------------
NBPEI : $(BUILD_DIR)\NB.mak NBPEIBin

NB_PEI_OBJECTS = $$(BUILD_DIR)\$(NB_BOARD_DIR)\NBPeiBoard.obj \
$$(BUILD_DIR)\$(NB_BOARD_DIR)\GetSetupData.obj \
$$(BUILD_DIR)\$(NB_CHIPSET_DIR)\NBPei.obj

NBPEIBin : $(AMIPEILIB) $(AMICSPLib) $(INTEL_SA_PPI_LIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\NB.mak all\
        NAME=NBPEI\
        MAKEFILE=$(BUILD_DIR)\NB.mak \
!IF "$(x64_BUILD)"=="1"
		BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
		BUILD_DIR=$(BUILD_DIR)\
!ENDIF
        "CFLAGS=$(CFLAGS) /I$(NB_BOARD_DIR) /D\"NB_OEM_SETUP_CALLBACK_LIST=$(NbConfigurationList)\""\
        OBJECTS="$(NB_PEI_OBJECTS)" \
        GUID=79AA6086-035A-4ad9-A89A-A6D5AA27F0E2 \
        ENTRY_POINT=NBPEI_Init \
        TYPE=PEIM \
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES) $(INTEL_MCH_INCLUDES) $(SwitchableGraphics_INCLUDES) $(EdkIIGlueLib_INCLUDES)" \
        DEPEX1=$(NB_BOARD_DIR)\NBPEI.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        COMPRESS=0

# FILE GUID for NBPEI BIN
#// {79AA6086-035A-4ad9-A89A-A6D5AA27F0E2}
#DEFINE_GUID(<<name>>,
#0x79aa6086, 0x35a, 0x4ad9, 0xa8, 0x9a, 0xa6, 0xd5, 0xaa, 0x27, 0xf0, 0xe2);

#----------------------------------------------------------------------------
#       Create NB DXE Component
#----------------------------------------------------------------------------
NBDXE : $(BUILD_DIR)\NB.MAK NBDXEBin


NB_DXE_OBJECTS = $(BUILD_NB_BOARD_DIR)\NBDxeBoard.obj \
$(BUILD_NB_BOARD_DIR)\GetSetupData.obj \
$(BUILD_NB_CHIPSET_DIR)\NBSmm.obj \
$(BUILD_NB_CHIPSET_DIR)\NBDxe.obj

!IF "$(CSM_SUPPORT)"=="1"
CSMCOREBin : $(BUILD_NB_BOARD_DIR)\NBDxeBoard.obj
!ENDIF

NBDXEBin : $(AMICSPLib) $(AMIDXELIB) $(SaGuidLib_LIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\NB.mak all\
        NAME=NBDXE\
        MAKEFILE=$(BUILD_DIR)\NB.mak \
        "CFLAGS=$(CFLAGS) $(ACPI_PLATFORM_INCLUDES) /I$(NB_BOARD_DIR) /D\"NB_OEM_SETUP_CALLBACK_LIST=$(NbConfigurationList)\""\
        OBJECTS="$(NB_DXE_OBJECTS)" \
        GUID=E4ECD0B2-E277-4f2b-BECB-E4D75C9A812E \
        ENTRY_POINT=NBDXE_Init \
        TYPE=BS_DRIVER \
        "MY_INCLUDES=$(INTEL_PCH_INCLUDES) $(INTEL_MCH_INCLUDES) $(ME_INCLUDES)" \
        DEPEX1=$(NB_BOARD_DIR)\NBDXE.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

# FILE GUID for NBDXE BIN
#// {E4ECD0B2-E277-4f2b-BECB-E4D75C9A812E}
#DEFINE_GUID(<<name>>,
#0xe4ecd0b2, 0xe277, 0x4f2b, 0xbe, 0xcb, 0xe4, 0xd7, 0x5c, 0x9a, 0x81, 0x2e);

!ENDIF

#----------------------------------------------------------------------------
#		Create NB ACPI Object
#----------------------------------------------------------------------------
$(BUILD_DIR)\NbAcpi.obj: $(NB_CHIPSET_DIR)\NbAcpi.c
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(NB_CHIPSET_DIR)\NbAcpi.c /I$(NB_CHIPSET_DIR) /I$(NB_BOARD_DIR)

AcpiModeEnableBin: $(BUILD_DIR)\NbAcpi.obj


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
