#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/BoardInfo/AmiBoardInfo.mak 14    9/18/13 3:54a Thomaschen $
#
# $Revision: 14 $
#
# $Date: 9/18/13 3:54a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Core/EM/BoardInfo/AmiBoardInfo.mak $
# 
# 14    9/18/13 3:54a Thomaschen
# Improved solution of EIP107638.
# 
# 10    6/05/13 5:00a Thomaschen
# Updated for EIP107638.
# 
# 9     2/12/13 11:28p Wesleychen
#  - Add eLink "SB_OSCM_ASL" support.
#  - Add eLink "ASL_PCI0_INI" for Thunderbolt support.
# 
# 8     1/29/13 12:27a Wesleychen
# Update Core to 4.6.5.4.
# 
# 13    5/04/12 5:48p Oleksiyy
# [TAG]  		EIP89379
# [Category]  	Improvement
# [Description]  	Add generic support for changing iasl compiler.
# [Files]  		ACPI.sdl and AmiBoardInfo.mak
# 
# 12    1/26/12 3:19p Oleksiyy
# [TAG]  		EIP80854
# [Category]  	New Feature
# [Description]  	Global _OSC control method is not available to read
# system wide capabilities in multiple ASL files.
# [Files]  		ACPI.sdl and AmiBoardInfo.mak
# 
# 11    9/30/11 5:41p Yakovlevs
# [TAG]  		EIP66222
# [Category]  	New Feature
# [Description]  	Modify PCI bus driver to get board info from separate
# FFS section
# [Files]  		AmiBoaardInfo.mak; 
# AmiBoaardInfo.sdl;
# PciBoard.c
# AmiBoaardInfo.h
# 
# 10    6/17/11 12:28p Yakovlevs
# [TAG]  		EIP54238
# [Category]  	Improvement
# [Description]  	Add ASLPREPROCESS_FLAG for the dsdt.asl proprocessing
# [Files]  		AmiBoardInfo.sdl; AmiBoardInfo.mak
# 
# 9     3/24/11 11:40a Oleksiyy
# [TAG]  		EIP56433 
# [Category]  	Improvement
# [Description]  	Elink table of include dirs for aslexpander is added.
# [Files]  		AmiBoardInfo.sdl, AmiBoardInfo.mak.
# 
# 8     12/16/10 10:41a Oleksiyy
# [TAG]  		EIP50035 
# [Category]  	Improvement
# [Description]  	#Ifdef support in ASL code generically added.
# [Files]  		ACPI.sdl and AmiBoardInfo.mak
# 
# 7     5/07/09 6:11p Yakovlevs
# fixed BUILD error with ACPI_MODULE_VER token
# 
# 6     5/05/09 3:16p Felixp
# Disable ACPI module dependent code if ACPI_MODULE_VER is less or equal
# than 30
# 
# 5     5/05/09 1:07p Felixp
# Formatting update: File headers are updated.
# 
# 4     5/05/09 12:53p Yakovlevs
# Fixed build issue in x64 mode. Default AFLAGS used /Cp switch to
# preserve case for PUBLIC identifiers. 
# 
# 1     4/28/09 1:20p Yakovlevs
# Added new ModulePart - Ami Board Info. 
# This module groups together all VeB generated outpit files as well as
# DSDT generation.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AmiBoardInfo.mak
#
# Description:	Make file to create AmiBoardInfo Driver
#
#<AMI_FHDR_END>
#**********************************************************************

all : AmiBoardInfo

AmiBoardInfo : $(BUILD_DIR)\AmiBoardInfo.mak OemPirBin AmiBoardInfoBin

$(BUILD_DIR)\AmiBoardInfo.mak : $(AmiBoardInfo_DIR)\$(@B).cif $(AmiBoardInfo_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmiBoardInfo_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

OemPirBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\AmiBoardInfo.mak bin \
        "OBJECTS=$(BUILD_DIR)\$(AmiBoardInfo_DIR)\PciBoard.obj"\
        "MY_DEFINES=/DPCIIRQ_REMAP"\
        "EXT_HEADERS=$(BUILD_DIR)\oempir.h $(BUILD_DIR)\mppciirq.h $(BUILD_DIR)\BusNumXlat.h"\
        NAME=oempirall\
        MAKEFILE=$(BUILD_DIR)\AmiBoardInfo.mak\
		TYPE=BINARY

AmiBoardInfoBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS) \
		/f $(BUILD_DIR)\AmiBoardInfo.mak all \
		GUID=9F3A0016-AE55-4288-829D-D22FD344C347 \
        "AFLAGS=$(AFLAGS:/Cp=)"\
        "AFLAGSx64=$(AFLAGSx64:/Cp=)"\
		ENTRY_POINT=AmiBoardEntryPoint \
		TYPE=BS_DRIVER \
        EXT_HEADERS=$(BUILD_DIR)\token.h\
        "OBJECTS=$(BUILD_DIR)\$(AmiBoardInfo_DIR)\AmiBoardInfo.obj"\
		COMPRESS=1\
        RESOURCE=$(BUILD_DIR)\oempirall.bin \
        SECTION_GUID=E6F4F8F7-4992-47b2-8302-8508745E4A23


!IF "$(ACPI_SUPPORT)"=="1" && "$(ACPI_MODULE_VER)"!=""
!IF $(ACPI_MODULE_VER) > 30

AmiBoardInfoBin : $(BUILD_DIR)\dsdt.obj

#----------------------------------------------------------------------------
# In order to build AML tables (DSDT.AML & SSDT.AML)
# ASL compiler have to be ran with DSDT.ASL and SSDT.ASL files corespondingly.
#-----------------------------------------------------------------------
#                        GENERATE ASL -> ASM Code
#-----------------------------------------------------------------------

$(BUILD_DIR)\dsdt.obj: $(PROJECT_DIR)\DSDT.ASL $(IO_ASLS) $(PCI_ASLS) $(BUILD_DIR)\token.mak
#dsdt.asl must be in the project directory; otherwise, will not be able to include various include files, esp. pcitree.asl
!IF "$(IFDEF_ASL_SUPPORT)"=="1"
    $(ASLEXPANDER) $(PROJECT_DIR)\DSDT.ASL $(PROJECT_DIR)\DSDT_Temp.ASL $(PROJECT_DIR) $(ASL_EXP_INCLUDE_PATH)
    $(CP) /EP /C /FI$(BUILD_DIR)\tokenasl.h $(ASLPREPROCESS_FLAG) $(PROJECT_DIR)\DSDT_Temp.ASL > $(PROJECT_DIR)\DSDT.ASL
!ENDIF
!IFDEF ASL_FLAGS
    $(ACPI_ASL_COMPILER) $(ASL_FLAGS) $(PROJECT_DIR)\DSDT.ASL 
!ELSE
	$(ACPI_ASL_COMPILER) -tc -vi $(PROJECT_DIR)\DSDT.ASL 
!ENDIF
    move $(PROJECT_DIR)\DSDT.hex $(BUILD_DIR)\DSDT.c
    $(CC) $(CFLAGS) /Fo$@ $(BUILD_DIR)\DSDT.c

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
!IF "$(PlatformAcpiTables_SUPPORT)"=="0"
Core\Em\ACPI\asllib.asl\
!ENDIF
Core\Em\ACPI\amlupd.asl\
$(GENERIC_ASL_BEFORE_PCITREE)\
$(BUILD_DIR)\PCItree.asl\
$(GENERIC_ASL)\
!IF "$(A_SIOW)"=="00" #IO_ASLS
!IFDEF CRB_EC_SUPPORT
!IF "$(CRB_EC_SUPPORT)"=="0"
$(PROJECT_DIR)\$(AcpiAslWrap_DIR)\PlatformPS2Wake.ASL\
!ENDIF
!ELSE
!IF "$(CRB_SIO_SUPPORT)"=="0"
!IF "$(AcpiAslWrap_SUPPORT)"!="0"
$(PROJECT_DIR)\$(AcpiAslWrap_DIR)\PlatformPS2Wake.ASL\
!ENDIF #AcpiAslWrap_SUPPORT!=0
!ENDIF #CRB_SIO_SUPPORT == 0
!ENDIF #CRB_EC_SUPPORT
!ENDIF #IO_ASLS
!IFDEF CRB_EC_SUPPORT
!IF "$(CRB_EC_SUPPORT)"=="0"
$(INTEL_EC_ASL)
!ENDIF
!ELSE
$(INTEL_EC_ASL)
!ENDIF

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
!IF "$(SIO_SUPPORT)"=="1"
!IF "$(PlatformAcpiTables_SUPPORT)"=="1"
			\_SB.PCI0.LPCB.SIOS(Arg0)  //- SB name for INTEL LPCB
!ELSE
                        \_SB.PCI0.SBRG.SIOS(Arg0)
!ENDIF #PlatformAcpiTables_SUPPORT
!ENDIF #SIO_SUPPORT
!endif
		}
	}
	Method(WAK, 1) {		// METHOD CALLED FROM _WAK (oemDSDT.asl) RIGHT AFTER WAKE UP
			$(ASL_WAK)
!if "$(A_SIOW)"=="01" #IO_ASLS
!IF "$(SIO_SUPPORT)"=="1"
!IF "$(PlatformAcpiTables_SUPPORT)"=="1"
			\_SB.PCI0.LPCB.SIOW(Arg0) //- SB name for INTEL LPCB
!ELSE
                        \_SB.PCI0.SBRG.SIOW(Arg0)
!ENDIF #PlatformAcpiTables_SUPPORT
!ENDIF #SIO_SUPPORT
!endif
	}

!IF "$(PlatformAcpiTables_SUPPORT)"=="0"
	Method(\_SB._OSC,4){
          $(SB_OSCM_ASL)
          Return(Arg3)	
        }
!ELSE
        Method(OSCM, 4){
          $(SB_OSCM_ASL)
          Return(0)
        }
!ENDIF #PlatformAcpiTables_SUPPORT

	Method(PINI, 0) {		// METHOD CALLED FROM _INI of PCI0 (oemDSDT.asl) RIGHT WHEN ENTER OS
            $(ASL_PCI0_INI)
        }

}	// End of ASL File

<<

#----------------------------------------------------------------------------
!ENDIF
!ENDIF

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
