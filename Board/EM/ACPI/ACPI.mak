#//**********************************************************************
#//**********************************************************************
#//**                                                                  **
#//**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#//**                                                                  **
#//**                       All Rights Reserved.                       **
#//**                                                                  **
#//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
#//**                                                                  **
#//**                       Phone: (770)-246-8600                      **
#//**                                                                  **
#//**********************************************************************
#//**********************************************************************
#**********************************************************************
# $Header: /Alaska/BIN/Modules/ACPI/Template/Board/ACPI.mak 46    3/10/14 6:03p Oleksiyy $
#
# $Date: 3/10/14 6:03p $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/ACPI/Template/Board/ACPI.mak $
# 
# 46    3/10/14 6:03p Oleksiyy
# [TAG]  		EIP156376
# [Category]  	Improvement
# [Description]  	PREPARE directive is used now to guaranty that
# AcpiOemElinks.h will be generated as sooner than it may be included in
# any file.
# [Files]  		ACPI.sdl
# ACPI.mak
# 
# 45    8/06/12 11:30a Oleksiyy
# [TAG]  		EIP93878
# [Category]  	Improvement
# [Description]  	Improve T_ACPI_OEM_ID and T_ACPI_OEM_TBL_ID to acpi
# table.
# [Files]  		ACPI.mak
# 
# 44    10/25/11 5:53p Oleksiyy
# [TAG]  		EIP71540 
# [Category]  	Improvement
# [Description]  	Fix of "any amount of spaces in table IDs replaced with
# only one". 
# [Files]  		ACPI.mak and AcpiCore.c
# 
# 43    5/14/11 2:59p Yakovlevs
# [TAG]  		EIP 56526
# [Category]  	New Feature
# [Description]  	ACPI Manipulation Protocol. PI 1.2 Spec Vol 5 Section
# 9.
# [Files]  		AcpiCore.c; AcpiCore.h; AcpiSdtPrivate.h; Aml.c; AmlChild.c;
# AmlNamespace.c; AmlOption.c; AmlString.c AcpiSdt.c; 
# Protocol\AcpiSdt.h. 
# 
# 42    3/18/11 4:09p Oleksiyy
# [TAG]  		EIP53402 
# [Category]  	Improvement
# [Description]  	Improving backward computability and architecture.
# [Files]  		ACPI.mak, AcpiCore.cif, S3Save.cif, S3Save.mak,
# S3Restore.mak, BootScriptExecutor.c, S3Common.cif, S3SaveState.h,
# S3smmSaveState.h
# 
# 41    2/03/11 4:19p Oleksiyy
# [TAG]  		EIP53402
# [Category]  	Improvement
# [Description]  	Create new label of ACPI with separate S3 Functionality
# 
# [Files]  		Acpi.cif; Acpi.sdl; Acpi.mak
# 
# 40    12/22/10 5:09p Oleksiyy
# [TAG]  		EIP49816 
# [Category]  	Improvement
# [Description]  	Function OemAcpiSetPlatformId added as eLink
# [Files]  		ACPi.mak, ACPI.sdl and OEM_ACPI.c
# 
# 39    8/11/09 12:42p Markw
# Link CSP library.
# 
# 38    5/08/09 12:18p Yakovlevs
# Made Acpi Driver use AMI Board  Info Protocol if available without
# breaking compatibility
# 
# 37    3/26/09 4:47p Oleksiyy
# New ACPI Core realization - improves logic, execution time and memory
# usage of ACPI module.
# 
# 1     2/18/09 3:50p Oleksiyy
# 
# 35    12/01/08 6:53p Yakovlevs
# 
# 34    11/08/07 4:54p Felixp
# MPS_TABLE_SUPPORT updated with dependency from CSM_SUPPORT
# 
# 33    6/10/07 10:38p Yakovlevs
# Fixed issue for LegacyFree systems. 
# All PTS and WAK objects was excluded from DSDT.ASL if no SIO. 
# Now excluded only SIO WAKE/PTS methods.  
# 
# 32    6/05/07 3:41p Felixp
# 
# 30    4/24/07 6:29p Felixp
# Dependency expression for AcpiS3Save added
# 
# 29    4/23/07 1:30p Felixp
# Boot Script related code moved from Core to ACPI module. 
# Boot Script related code moved from Core to ACPI module.
# PEI code added to S3 Resume PPI. DXE code added to AcpiS3Save driver.
# 
# 28    3/21/07 7:09p Yakovlevs
# Added support for ACPI 3.0 Header Revision.
# 
# 27    3/19/07 12:23p Felixp
# Dependency from token.h added
# 
# 26    3/19/07 12:16p Felixp
# MP Table object file added to ACPI_DXE_OBJECTS
# 
# 25    1/23/07 3:13p Markw
# Link CSP library to S3 Resume.
# 
# 24    11/11/06 10:35a Felixp
# Previous changes removed
# 
# 22    8/01/06 4:01p Robert
# reorganized make file
# 
# 21    5/24/06 6:22p Ambikas
# 
# 20    5/24/06 3:47p Ambikas
# 
# 19    3/13/06 10:14a Felixp
# 
# 17    1/25/06 11:49a Felixp
# Path to ASL and IASL removed
# 
# 16    12/12/05 11:35a Felixp
# 
# 14    12/02/05 11:43a Felixp
# 
# 13    12/02/05 11:42a Felixp
# 
# 12    12/02/05 11:12a Felixp
# include token.mak removed
# 
# 11    12/01/05 12:20p Felixp
# Dependency for ACPI Setup Data from $(BUILD_DIR)\ACPI.mak added
# 
# 10    12/01/05 11:50a Markw
# 
# 9     10/14/05 6:10p Felixp
# Dependency Expression for AcpiS3Save removed
# 
# 8     6/30/05 2:41p Felixp
# acpi.sd an acpi.uni moved from ACPI-Core to ACPI-Board
# 
# 7     6/29/05 5:45p Yakovlevs
# 
# 6     5/25/05 1:14p Yakovlevs
# dsdt.aml dependencies list updated
# 
# 5     5/12/05 10:16a Markw
# Added ACPIS3Wake.asm and AcpiPeiS3Func.c to build. Removed redunant
# termal and fan from make file. It also exists in e-links.
# 
# 4     5/05/05 6:40p Yakovlevs
# 
# 3     4/29/05 3:21p Markw
# 
# 2     4/29/05 12:19p Sivagarn
# Created S3 related drivers
# 
# 1     3/24/05 5:00p Sivagarn
# Initial Checkin
# 
# 
#**********************************************************************

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
# Name:		Acpi.mak
#
# Description:	Make file for the Acpi component
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>

#-----------------------------------------------------------------------
# General definitions and rules
#-----------------------------------------------------------------------
all : BuildACPI 
!IF "$(AmiBoardInfo_SUPPORT)" != "1"
all : BuildASL
DSDT_GUID = 11D8AC35-FB8A-44d1-8D09-0B5606D321B9 # This one is for V 2.0+
!ENDIF
PREPARE : $(BUILD_DIR)\AcpiOemElinks.h
$(BUILD_DIR)\AcpiOemElinks.h : $(BUILD_DIR)\token.h
    $(ECHO) #define OEM_LIST $(OemUpdateHeader) > $(BUILD_DIR)\AcpiOemElinks.h
!IF "$(T_ACPI_OEM_ID:|=a)"!="$(T_ACPI_OEM_ID)"
    $(ECHO) #define ACPI_OEM_ID_MAK $(T_ACPI_OEM_ID:|=") >> $(BUILD_DIR)\AcpiOemElinks.h
!ELSE
    $(ECHO) #define ACPI_OEM_ID_MAK "$(T_ACPI_OEM_ID)" >> $(BUILD_DIR)\AcpiOemElinks.h
!ENDIF
!IF "$(T_ACPI_OEM_TBL_ID:|=a)"!="$(T_ACPI_OEM_TBL_ID)"
    $(ECHO) #define ACPI_OEM_TBL_ID_MAK $(T_ACPI_OEM_TBL_ID:|=") >> $(BUILD_DIR)\AcpiOemElinks.h
!ELSE
    $(ECHO) #define ACPI_OEM_TBL_ID_MAK "$(T_ACPI_OEM_TBL_ID)" >> $(BUILD_DIR)\AcpiOemElinks.h
!ENDIF

$(BUILD_DIR)\AMICSPLIBInc.h : $(ACPI_CORE_DIR)\AcpiS3.h 

ACPI_CORE_DIR = $(PROJECT_DIR)\Core\Em\ACPI
ASL_CORE_DIR = $(ACPI_CORE_DIR)
ACPI_BOARD_DIR = $(PROJECT_DIR)\Board\Em\ACPI
ASL_BOARD_DIR = $(ACPI_BOARD_DIR)
ACPI_TOOLS_DIR	= $(PROJECT_DIR)\TOOLS

ACPI_BUILD_DIR	= $(BUILD_DIR)
BUILD_ACPI_CORE_DIR = $(BUILD_DIR)\Core\Em\ACPI
BUILD_ACPI_BOARD_DIR = $(BUILD_DIR)\Board\Em\ACPI




#-----------------------------------------------------------------------
# Rules for building ACPI DXE driver
#-----------------------------------------------------------------------
BuildACPI : $(BUILD_DIR)\ACPI.mak ACPIBin

ACPI_DXE_OBJECTS = $(BUILD_ACPI_CORE_DIR)\Acpicore.obj \
$(BUILD_ACPI_BOARD_DIR)\OEM_ACPI.obj \
!IFDEF PI_SPECIFICATION_VERSION
!IF $(PI_SPECIFICATION_VERSION)>=0x10014
$(BUILD_ACPI_CORE_DIR)\AcpiSdt.obj \
$(BUILD_ACPI_CORE_DIR)\Aml.obj \
$(BUILD_ACPI_CORE_DIR)\AmlChild.obj \
$(BUILD_ACPI_CORE_DIR)\AmlNamespace.obj \
$(BUILD_ACPI_CORE_DIR)\AmlOption.obj \
$(BUILD_ACPI_CORE_DIR)\AmlString.obj \
!ENDIF
!ENDIF
!IF "$(MPS_TABLE_SUPPORT)"=="1"
$(BUILD_ACPI_CORE_DIR)\MPTable.obj \
!IF "$(AmiBoardInfo_SUPPORT)" != "1"
$(BUILD_ACPI_CORE_DIR)\MpPciIrq.obj
!ENDIF
!ENDIF

$(BUILD_DIR)\ACPI.mak : $(ACPI_CORE_DIR)\acpicore.cif $(ACPI_BOARD_DIR)\acpiBsp.cif $(ACPI_BOARD_DIR)\acpi.mak $(BUILD_RULES)
	$(CIF2MAK) $(ACPI_CORE_DIR)\acpicore.cif $(ACPI_BOARD_DIR)\acpiBsp.cif $(CIF2MAK_DEFAULTS)

ACPIBin : $(AMIDXELIB) $(AMICSPLib)
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\ACPI.mak all\
		MAKEFILE=$(BUILD_DIR)\ACPI.MAK \
		NAME=ACPI\
		OBJECTS="$(ACPI_DXE_OBJECTS)" \
		GUID=16D0A23E-C09C-407d-A14A-AD058FDD0CA1 \
		ENTRY_POINT=AcpiNewCoreEntry \
        "EXT_HEADERS=$(BUILD_DIR)\token.h\
        $(BUILD_DIR)\AcpiOemElinks.h" \
		TYPE=BS_DRIVER \
        "MY_INCLUDES=/I$(ACPI_BOARD_DIR)" \
		DEPEX1=$(ACPI_BOARD_DIR)\ACPI.DXS\
		COMPRESS=1

#-----------------------------------------------------------------------
!IF "$(AmiBoardInfo_SUPPORT)"!="1"
#-----------------------------------------------------------------------
# MAK file for the ModulePart:ASL_CORE

BuildASL : $(BUILD_DIR)\asl.ffs

$(BUILD_DIR)\asl.ffs: $(PROJECT_DIR)\dsdt.aml
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
		GUID=$(DSDT_GUID) \
		TYPE=EFI_FV_FILETYPE_FREEFORM \
		BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

#----------------------------------------------------------------------------
# In order to build AML tables (DSDT.AML & SSDT.AML)
# ASL compiler have to be ran with DSDT.ASL and SSDT.ASL files corespondingly.
#-----------------------------------------------------------------------
#                        GENERATE ASL -> ASM Code
#-----------------------------------------------------------------------

!if "$(ACPI_ASL_COMPILER)" == "ASL.exe"
$(PROJECT_DIR)\dsdt.aml: $(PROJECT_DIR)\DSDT.ASL $(IO_ASLS) $(PCI_ASLS) $(BUILD_DIR)\token.mak
	$(ACPI_ASL_COMPILER) /Fo=$@ $(PROJECT_DIR)\DSDT.ASL
!elseif "$(ACPI_ASL_COMPILER)" == "IASL.exe"
$(PROJECT_DIR)\dsdt.aml: $(PROJECT_DIR)\DSDT.ASL $(IO_ASLS) $(PCI_ASLS) $(BUILD_DIR)\token.mak
#dsdt.asl must be in the project directory; otherwise, will not be able to include various include files, esp. pcitree.asl
	$(ACPI_ASL_COMPILER) -p dsdt $(PROJECT_DIR)\DSDT.ASL
!endif

!if "$(ACPI_SSDT_TBL)" == "1"
$(ACPI_BUILD_DIR)\ssdt.aml: $(ASL_BOARD_DIR)\ssdt.asl
!if "$(ACPI_ASL_COMPILER)" == "ASL.exe"
	@$(ACPI_ASL_COMPILER) /Fa=$@ $**
!elseif "$(ACPI_ASL_COMPILER)" == "IASL.exe"
	@$(ACPI_ASL_COMPILER) -o $(BUILD_DIR)\ssdt.aml $**
!endif
!endif

#-----------------------------------------------------------------------#
# Description of ASL files that take part in building ACPI DSDT table
# amlUpd.asl	- OperationRegion and Field names to refer to BIOS exchange memory area
# token.asl     - SDL tokens stored in ASL name format 
# aslLib.asl	- standard ASL routines (GPRW - generic PRW routine. MCTH - string compare routine)
# PCItree.asl	- file is generated by AMISDL. Defines PCI Devices tree, PCI IRQ routing information
# oemDSDT.asl	- defines Root PCI bridge resources (_CRS), _PTS(prepare to sleep),_WAK(after wake up) routines
# irqLink.asl	- Irq routing devices LINKx
# ioRoute.asl	- Chipset specific routines to route/release IO/DMA resources on ISA/LPC bus. Used only if Positive decoding is selected
# FAN.asl	- OEM Fan device(s) objects
# TZ.asl	- OEM Thermal Zone(s) objects
# SI.asl	- OEM System Indication objects
#-----------------------------------------------------------------------
DSDT_ASLS = \
$(BUILD_DIR)\token.asl\
Core\Em\ACPI\asllib.asl\
Core\Em\ACPI\amlupd.asl\
$(GENERIC_ASL_BEFORE_PCITREE)\
$(BUILD_DIR)\PCItree.asl\
$(SB_CHIPSET_DIR)\IRQLink.asl\
#$(ASL_CORE_DIR)\irqLink.asl\
#!IF "$(A_CPU)" == "1"
#$(ASL_CORE_DIR)\cpu.asl\
#!endif
#!if "$(A_FAN)"=="1" || "$(A_THERMAL)"== "1"
#$(ASL_CORE_DIR)\FAN.asl\
#!endif
#!if "$(A_THERMAL)" == "1"
#$(ASL_CORE_DIR)\TZ.asl\
#!endif
#!if "$(A_SI)"=="1"
#$(ASL_CORE_DIR)\SI.asl\
#!endif
$(GENERIC_ASL)

ASL_SRC = $(**:\=\\)

#-----------------------------------------------------------------------#
#                         DSDT.ASL GENERATOR		                #
#-----------------------------------------------------------------------#
# Include any Make flag dependent ASL code in this module,
# otherwise use OEM ASL files within ACPI_BSP_DIR for OEM modifications
#
# Note. 1. Do not change an order ASL files appear in above defined DSDT_ASLS list
# 	2. Any module can include own ASL files to the target DSDT.ASL 
#	by adding the files to the dependency list as follows:
#	$(PROJECT_DIR)\DSDT.ASL: $(PATH)\module.asl
#-----------------------------------------------------------------------#
$(PROJECT_DIR)\DSDT.ASL: $(DSDT_ASLS)
	copy << $@

//==========================================================================
//                     DO NOT EDIT THIS FILE                                
// This file was generated automatically using NMAKE build process(ACPI.MAK)
// If OEM changes needed, edit ASL file(s) with extension "*.asl"           
//==========================================================================
DefinitionBlock (
	"ami.aml",
	"DSDT",
!IF "$(ACPI_BUILD_TABLES_3_0)"=="1"
    0x02,	// DSDT revision.
!ELSE
	0x01,	// DSDT revision.
!ENDIF
			// A Revision field value greater than or equal to 2 signifies that integers 
			// declared within the Definition Block are to be evaluated as 64-bit values
	"$(T_ACPI_OEM_ID)", // OEM ID (6 byte string)
	"$(T_ACPI_OEM_TBL_ID)", // OEM table ID  (8 byte string)
	0x0$(PROJECT_BUILD) // OEM version of DSDT table (4 byte Integer)
	)

// BEGIN OF ASL SCOPE
{
// Miscellaneous services enabled in Project
	include ("$(ASL_SRC: ="^)
	include (")")
// Sleep states supported by Chipset/Board.
//----------------------------------------------------------------------
// SSx - BIOS setup controlled enabled _Sx Sleep state status
// Values to be written to SLP_TYPE register are provided by SBACPI.SDL (South Bridge ACPI ModulePart)
	Name(\_S0, Package(4){$(A_S0_PKG)})	// mandatory System state
!if "$(A_S1)"=="1"
	if(SS1) { Name(\_S1, Package(4){$(A_S1_PKG)})}
!endif
!if "$(A_S2)"=="1"
	if(SS2) { Name(\_S2, Package(4){$(A_S2_PKG)})}
!endif
!if "$(A_S3)"=="1"
	if(SS3) { Name(\_S3, Package(4){$(A_S3_PKG)})}
!endif
!if "$(A_S4)"=="1"
 	if(SS4) { Name(\_S4, Package(4){$(A_S4_PKG)})}
!endif
	Name(\_S5, Package(4){$(A_S5_PKG)})	// mandatory System state

	Method(PTS, 1) {		// METHOD CALLED FROM _PTS (oemDSDT.asl) PRIOR TO ENTER ANY SLEEP STATE
		If(Arg0)		// entering any sleep state
		{
			$(ASL_PTS)
!if "$(A_SIOW)"=="01" #IO_ASLS
			\_SB.PCI0.SBRG.SIOS(Arg0)
!endif
		}
	}
	Method(WAK, 1) {		// METHOD CALLED FROM _WAK (oemDSDT.asl) RIGHT AFTER WAKE UP
			$(ASL_WAK)
!if "$(A_SIOW)"=="01" #IO_ASLS
			\_SB.PCI0.SBRG.SIOW(Arg0)
!endif
	}
}	// End of ASL File

<<
!ENDIF

#---------------------------------------------------------------------------
#		Create NB Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\ACPI.mak ACPISDB

ACPISDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\ACPI.mak all\
		TYPE=SDB NAME=ACPI STRING_CONSUMERS=$(ACPI_BOARD_DIR)\ACPI.sd
#---------------------------------------------------------------------------



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
