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
# $Header: /Alaska/BIN/Board/Board.mak 18    8/16/12 12:29p Artems $
#
# $Revision: 18 $
#
# $Date: 8/16/12 12:29p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Board/Board.mak $
# 
# 18    8/16/12 12:29p Artems
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	Added OEM hook to PublishNestedFv function
# [Files]  		Board.sdl Board.mak ReportFv2.c
# 
# 17    5/25/12 10:33a Artems
# [TAG]  		EIP N/A
# [Category]  	Improvement
# [Description]  	Moved ReportFvDxe function to DxeIpl
# [Files]  		Board.mak Recovery.c DxeIpl.c
# 
# 16    8/24/11 8:09a Felixp
# Enhancement(EIP 64107): 
#   Changes to support UEFI 2.3.1 and PI 1.2 specifications.
#   Make wil is updated to indicate that ForwardCompatibility eModule is
# required to use the component with older Cores.
# 
# 15    2/04/11 8:05p Artems
# EIP 39461: Flexible ROM layout support
# 
# 14    11/25/09 5:31p Felixp
# Support for two hooks added in ReportFv.c:
# ProcessFvBeforePublishing - called before publishing FV
# ProcessDxeFvInDxeIpl - called for the DXE accessible FV's from the
# ReportFvDxeIpl
# 
# 13    8/11/09 12:10p Felixp
# Improvement (EIP 24966). Requires 4.6.2_CSPLibrary_012 or newer.
# New method of contributing files to CspLib library.
# 1. AMI_CSP_LIB_LIBRARY_PATH is removed (not used)
# 2. AMI_CSP_LIB_OBJS is replaced with dependency from AMICSPLibBin
# Item #1 is a cleanup. 
# Items #2 is improvement. Old macros based approach only worked for
# modules that are above than CspLib in the project tree.
# 
# 12    6/25/09 6:09p Robert
# Updated Comments and function headers
# 
# 11    5/22/09 5:40p Felixp
# Suport for Core 4.6.3.6.
# Build commands to compile ROM layout strucuture
# ($(BUILD_DIR)\RomLayout.c) 
# and link it with PEI Core are added.
# 
# 10    3/05/09 1:30p Felixp
# Improvement EIP 18496:
#   eLinks are exposed for the following porting functions defined in
# OemPort:
#     IsRecovery, NoConfigChanges, IsMfgMode, IsResetConfigMode,
# IsDefaultConfigMode
# 
# 9     8/24/06 7:19p Felixp
# AMIPEILIB removed from the list of CSP LIB Objects
# 
# 7     7/06/06 6:28p Felixp
# $(PROJECT_DIR) added to the .c to .obj rule. This is needed to ITP
# source level debugging.
# 
# 6     7/06/06 11:55a Sivagarn
# - Included support to build OEM DXE & PEI drivers
# - Included support for OEM setup options
# 
# 4     4/05/05 3:35p Sivagarn
#  - Removed PlatformBootMode.C file from the make process 
#  - Included OEMPort.C
#  - Created additional functions from board into the CSPLibrary
# 
# 2     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 7     11/18/04 6:27p Felixp
# support for multiple FVs added (ReportFV file added)
# 
# 3     3/10/04 3:50p Robert
# PlatformBootMode.c was added to the build process
# 
# 2     12/09/03 11:50a Felixp
# Comments changed for the better HelpBuiler compatibility.
# 
#**********************************************************************

#<AMI_FHDR_START>
#-----------------------------------------------------------------------
# Name:			Board.MAK
#
# Description:	This make file builds board related DXE & PEI modules
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>
!IFDEF CORE_COMBINED_VERSION
!IF $(CORE_COMBINED_VERSION)<0x4028b && "$(ForwardCompatibility_SUPPORT)"!="1"
BOARD_ERROR_MESSAGE=To use this version of the Board module with Cores older than 4.6.5.1,^
add ForwardCompatibility eModule to your project^
($$/Alaska/BIN/Core/Compatibility/Forward/ForwardCompatibility.cif).
!ERROR $(BOARD_ERROR_MESSAGE)
!ENDIF
!ENDIF

all : OEMPEI OEMDXE OEMSDB $(BUILD_DIR)\RomLayout.ffs
#---------------------------------------------------------------------------

BOARD_BUILD_DIR=$(BUILD_DIR)\$(BOARD_DIR)

CREATE_BOARD_BUILD_DIR:
	if not exist $(BOARD_BUILD_DIR) mkdir $(BOARD_BUILD_DIR)

BOARD_OBJECTS = \
$(BOARD_BUILD_DIR)\ReportFV2.obj \

BOARD_HEADERS = \

{$(PROJECT_DIR)\$(BOARD_DIR)}.c{$(BOARD_BUILD_DIR)}.obj::
	$(CC) /Fo$(BOARD_BUILD_DIR)\ $(CFLAGS)\
    /D\"ProcessFvBeforePublishing=$(ProcessFvBeforePublishing)\"\
    /D\"ProcessNestedFvBeforePublishing=$(ProcessNestedFvBeforePublishing)\"\
    /D\"ProcessDxeFvInDxeIpl=$(ProcessDxeFvInDxeIpl)\"\
    $<

$(BOARD_OBJECTS) : $(BOARD_HEADERS)

!IF !EXIST($(BOARD_BUILD_DIR))
$(BOARD_OBJECTS) : CREATE_BOARD_BUILD_DIR
!ENDIF

$(BOARD_BUILD_DIR)\ReportFV2.obj : $(BUILD_DIR)\token.h

$(BUILD_DIR)\RomLayout.obj : $(BUILD_DIR)\RomLayout.c
    $(CC) /Fo$@ $(CFLAGS) $(BUILD_DIR)\RomLayout.c

CORE_PEIBin : $(BOARD_BUILD_DIR)\ReportFV2.obj

$(BUILD_DIR)\RomLayout.ffs : $(BUILD_DIR)\RomLayout.obj $(BUILD_DIR)\Board.mak
	$(MAKE) /$(MAKEFLAGS) EXT_OBJS= $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Board.mak bin\
        NAME=RomLayout OBJECTS=$(BUILD_DIR)\RomLayout.obj\
        MAKEFILE=$(BUILD_DIR)\Board.mak \
        TYPE=BINARY
    $(MAKE) /f Core\FFS.mak \
        BUILD_DIR=$(BUILD_DIR) \
        GUID=0DCA793A-EA96-42d8-BD7B-DC7F684E38C1 \
        TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFSFILE=$@ COMPRESS=0 NAME=$(@B)\
        RESOURCE=$(BUILD_DIR)\RomLayout.bin \
        SECTION_GUID=88A15A4F-977D-4682-B17C-DA1F316C1F32 \

#---------------------------------------------------------------------------
#			Generic Board dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\Board.mak : $(BOARD_DIR)\Board.cif $(BUILD_RULES)
	$(CIF2MAK) $(BOARD_DIR)\Board.cif $(CIF2MAK_DEFAULTS)
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#			Add files into CSP Library
#---------------------------------------------------------------------------
AMICSPLibBin : $(BUILD_DIR)\OemPort.obj $(BUILD_DIR)\OemPortList.obj

{$(PROJECT_DIR)\$(BOARD_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(BOARD_DIR) /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\OemPortList.obj : $(BUILD_DIR)\Token.h $(BOARD_DIR)\Board.mak
    $(CC) /Fo$@ $(CFLAGS) <<$(BUILD_DIR)\OemPortList.c
#include <Pei.h>
typedef BOOLEAN (ONE_PARAM_FUNCTION)(
    IN EFI_PEI_SERVICES **PeiServices
);
typedef BOOLEAN (TWO_PARAM_FUNCTION)(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST VOID *ReadVariablePpi
);

extern ONE_PARAM_FUNCTION $(IsRecovery) EndOfOneParamList;
extern ONE_PARAM_FUNCTION $(NoConfigChanges) EndOfOneParamList;
extern TWO_PARAM_FUNCTION $(IsMfgMode) EndOfTwoParamList;
extern TWO_PARAM_FUNCTION $(IsResetConfigMode) EndOfTwoParamList;
extern TWO_PARAM_FUNCTION $(IsDefaultConfigMode) EndOfTwoParamList;

ONE_PARAM_FUNCTION* IsRecoveryList[] = {$(IsRecovery) NULL};
ONE_PARAM_FUNCTION* NoConfigChangesList[] = {$(NoConfigChanges) NULL};
TWO_PARAM_FUNCTION* IsMfgModeList[] = {$(IsMfgMode) NULL};
TWO_PARAM_FUNCTION* IsResetConfigModeList[] = {$(IsResetConfigMode) NULL};
TWO_PARAM_FUNCTION* IsDefaultConfigModeList[] = {$(IsDefaultConfigMode) NULL};
<<KEEP

#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#		Create BOARD PEI Component
#---------------------------------------------------------------------------
OEMPEI : $(BUILD_DIR)\board.mak OEMPEIBin

BOARD_PEI_OBJECTS = $(BOARD_BUILD_DIR)\OemPei.obj

OEMPEIBin : $(AMIPEILIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Board.mak all\
		NAME=OEMPEI\
		MAKEFILE=$(BUILD_DIR)\Board.mak \
		OBJECTS="$(BOARD_PEI_OBJECTS)" \
		GUID=6E59DF06-62D3-40b0-82B5-175CF84A94E4 \
		ENTRY_POINT=OEMPEI_Init \
		TYPE=PEIM \
		DEPEX1=$(BOARD_DIR)\OEMPEI.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0

# FILE GUID for OEMPEI BIN
#// {6E59DF06-62D3-40b0-82B5-175CF84A94E4}
#DEFINE_GUID(<<name>>, 
#0x6e59df06, 0x62d3, 0x40b0, 0x82, 0xb5, 0x17, 0x5c, 0xf8, 0x4a, 0x94, 0xe4);
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#		Create OEM DXE Component
#---------------------------------------------------------------------------
OEMDXE : $(BUILD_DIR)\Board.MAK OEMDXEBin

BOARD_DXE_OBJECTS = $(BOARD_BUILD_DIR)\OemDxe.obj

OEMDXEBin : $(AMICSPLib) $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Board.mak all\
		NAME=OEMDXE\
		MAKEFILE=$(BUILD_DIR)\Board.mak \
		OBJECTS="$(BOARD_DXE_OBJECTS)" \
		GUID=BFE205C9-5B17-4f8f-9375-89614AF8E199 \
		ENTRY_POINT=OEMDXE_Init \
		TYPE=BS_DRIVER \
		DEPEX1=$(BOARD_DIR)\OEMDXE.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1

# FILE GUID for OEMDXE BIN
#// {BFE205C9-5B17-4f8f-9375-89614AF8E199}
#DEFINE_GUID(<<name>>, 
#0xbfe205c9, 0x5b17, 0x4f8f, 0x93, 0x75, 0x89, 0x61, 0x4a, 0xf8, 0xe1, 0x99);
#---------------------------------------------------------------------------


#---------------------------------------------------------------------------
#		Create OEM Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\Board.mak OEMSDB
SetupBin : $(BUILD_DIR)\OemSetup.obj

OEMSDB :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\Board.mak all\
		TYPE=SDB NAME=OEM MAKEFILE=$(BUILD_DIR)\Board.Mak STRING_CONSUMERS=$(BOARD_DIR)\Oem.sd
$(BUILD_DIR)\OemSetup.obj : $(BOARD_DIR)\OemSetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(BOARD_DIR)\OemSetup.c

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
