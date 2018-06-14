#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**              5555 Oak brook Pkwy, Norcorss, GA 30093             **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSE.mak 43    5/02/14 9:37a Premkumara $
#
# $Revision: 43 $
#
# $Date: 5/02/14 9:37a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSE.mak $
# 
# 43    5/02/14 9:37a Premkumara
# [TAG]  		EIP162662
# [Category]  	Improvement
# [Description]  	Configuring adding RT access to variable in HPKTool
# using SDL token
# [Files]  		AMITSE.sdl, AMITSE.mak
# 
# 42    5/02/14 5:40a Arunsb
# [TAG]  		EIP156258
# [Category]  	Improvement
# [Description]  	Providing ELINK option to suppress the handle
# comparison on dynamic parsing
# [Files]  		AMITSE.mak, AMITSE.sdl, commonoem.c, commonoem.h and Parse.c
# 
# 41    5/02/14 4:39a Premkumara
# [TAG]  		EIP95647
# [Category]  	Improvement
# [Description]  	Dynamic Forms need to hide.
# [Files]  		AMITSE.mak, AMITSE.sdl, CommonOem.c, Parse.c
# 
# 40    5/02/14 3:43a Premkumara
# [TAG]  		EIP151966
# [Category]  	Improvement
# [Description]  	Added the implementation for getting the BIOS build
# year dynamically 
# from TimeStamp.h file and updated the Build year in copyright message
# in both Setup and POST.
# [Files]  		style.c,style.c,style.c,notify.c,minisetupext.c,CommonHelper
# .c,
# AmiTSEStr.uni,AMITSE.mak
# 
# 39    4/16/14 2:54p Arunsb
# [TAG]  		EIP154326
# [Category]  	Bug Fix
# [Severity]  	Normal
# [Symptom]  	Build error if we have more TSE ELinks
# [RootCause]  	Make file echo throwing build error if we have too many
# ELinks
# [Solution]  	echo removed and used redirections
# [Files]  		amitse.mak
# 
# 38    2/11/14 7:37p Arunsb
# Copyright version modified
# 
# 37    12/04/13 3:00a Premkumara
# [TAG]	EIP139099
# [Category]	New Feature
# [Description]	Supress formset other than
# EFI_HII_PLATFORM_SETUP_FORMSET_GUID and
# EFI_HII_DRIVER_HEALTH_FORMSET_GUID through elink based on token
# [Files]	AMITSE.sdl, AMITSE.mak, CommonOem.c, Hii.c, Parse.c,
# TseUefiHii.h
# 
# 36    4/18/13 9:56a Arunsb
# Copyright year changed to 2013
# 
# 35    4/17/13 1:50a Arunsb
# [TAG]  		EIP100539
# [Category]  	Improvement
# [Description]  	HpkTool should generate proper header for StdDefaults
# [Files]  		amitse.mak and uefihpktool.exe
# 
# 34    3/29/13 8:39a Arunsb
# [TAG]  			EIP111061 
# [Category]  	Improvement
# [Description]  	Provide support for efivarstore opcode
# [Files]  		Parse.c, amitse.mak and tseuefihii.h
# 
# 33    3/25/13 8:51a Premkumara
# [TAG]  		EIP116315
# [Category]  	Improvement
# [Description]  	Display control prompt string for password control.
# (for String on CHAP secret popup)
# [Files]  		- AMITSE.sdl
# - CommonHelper.c
# - FakeToken.c
# - AmiTSEStr.uni
# - TseLite\PopupPassword.c
# - uefi2.1\UefiWapper21.c
# - uefi2.0\UefiWapper20.c
# - uefi2.0\HiiCallback.c
# - uefi2.0\hii.h
# - uefi2.0\hii.c 
# 
# 32    2/13/13 2:15a Arunsb
# [TAG]  		EIP111742
# [Category]  	Improvement
# [Description]  	ChangeLogo romhole PI compatibility.
# Support for romhole with changelogo in PI 0.9 also.
# [Files]  		amitse.mak
# 
# 31    10/18/12 5:30a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 21    10/10/12 12:21p Arunsb
## Synched the source for v2.16.1232 backup with Aptio
# 
# 29    9/25/12 9:27a Rajashakerg
# [TAG]  		EIP92053 
# [Category]  	Improvement
# [Description]  	Need support define Root page order using elinks
# [Files]  		AMITSE.sdl, Menu.c, AMIVfr.h, AMITSE.mak, commonoem.c
# 
# 28    9/25/12 7:47a Rajashakerg
# [TAG]  		EIP94424 
# [Category]  	Improvement
# [Description]  	Some form can't normal display when add Hii item will
# in runtime during
# [Files]  		AMITSE.sdl, AMITSE.mak
# 
# 27    5/29/12 3:01a Arunsb
# [TAG]  		EIP91109
# [Category]  	Improvement
# [Description]  	Sync the Aptio IV source for AptioV
# 
# 26    4/27/12 9:23a Arunsb
# [TAG]  		EIP88895 
# [Category]  	Improvement
# [Description]  	Changing GetUefiSpecVersion as board module hook and
# also controlling callback spec version from TSE
# [Files]  		Amitse.sdl, amitse.mak and commonhelper.c
# 
# 25    2/03/12 5:43a Premkumara
# Updated Copyright year to 2012
# 
# 24    2/02/12 1:08a Premkumara
# Updated ROMHOLE_GUID with TSE_ROMHOLE_MAKFILE_GUID for ROMHOLE
# 
# 23    2/02/12 12:41a Premkumara
# [TAG]  		EIP75136 
# [Category]  	New Feature
# [Description]  	Generic support for logos in RomHoles
# [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h
# 
# 22    1/31/12 1:15p Premkumara
# [TAG]  		EIP75136 
# [Category]  	New Feature
# [Description]  	Generic support for logos in RomHoles
# [Files]  		CommomHelper.c, AMITSE.sdl, AMITSE.mak, LogoLib.h,
# Postmgmt.c, AMILogo.h
# 
# 21    12/21/11 5:09a Arunsb
# [TAG]  		EIP70892
# [Category]  	Improvement
# [Description]  	Provisioning to set manufacturing default language too
# [Files]  		amitse.mak and uefihpktoo.exe
# 
# 20    7/21/11 2:14a Arunsb
# Copyright version updated to 2011
# 
# 19    7/01/11 5:20p Madhans
# [TAG]  		EIP60910 
# [Category]  	New Feature
# [Description]  	PNG image support in TSE.
# [Files]  		 LogoLib.h, AMITSE.sdl, CommonHelper.c, logo.c, png.c,
# png.h, pnguncmp.c, TseAdvanced.cif
# 
# 18    6/19/11 4:07p Arunsb
# [TAG]           EIP58712
# [Category]      New Feature
# [Description]   To disable the BIOS Signon Message and TSE copyright
# version in post screen.
# [Files]         amitse.sdl, amitse.mak, commonhelper.c and notify.c
# 
# 17    4/29/11 4:26p Arunsb
# For 2.13 public patch release signon message hiding feature is omitted
# 
# 15    1/12/11 12:13p Madhans
# To Update the CopyRight Year in SignOn message.
# 
# 14    12/28/10 1:48p Mallikarjunanv
# [TAG]  		EIP 51007
# [Category]  	Improvement
# [Description]  	Provided the sdl Token to customize the path of Setup
# ini 
# [Files]  		AMITSE.sdl
# AMITSE.mak
# 
# 13    12/23/10 6:13p Madhans
# [TAG] - EIP 50400 
# [Category]- Enhancment
# [Severity]- Mordarate
# [Symptom]- Neede Information on the ROM about Logo Type and Size
# support. 
# [RootCause] - ChangeLogo need to validate of the Logo file is support
# in the ROM image or not.
# [Solution]- TSE creates $LGO$ section. Uses SETUP_BMP_LOGO_SUPPORT,
# SETUP_JPEG_LOGO_SUPPORT, SETUP_GIF_LOGO_SUPPORT SETUP_PCX_LOGO_SUPPORT
# for Image type support. And Uses MAX_POST_GC_MODE SDL (Assign one of
# Max GC_MODEx SDL token) token for Size.
# Clone MAX_POST_GC_MODE SDL token and Update the right Max Mode
# supported in the project.
# [Files] - amitse.sdl and amitse.mak
# 
# 12    9/21/10 6:09p Madhans
# [TAG]    	-
# [Category]	BUILD ISSUE FIX
# [Symptom]	Build issues when Build called with Today and Now parameters
# [RootCause]  Dater.mak is not created if today and Now parameters are
# passed
# [Solution]	use timestamp.mak indtead of dater.mak
# [Files] amitse.mak
# 
# 11    9/16/10 8:39p Madhans
# Updated for TSE 2.10. Refer changelog.log for more deatils.
# 
## 16    8/27/10 4:54a Mallikarjunanv
## EIP-39334: support to build TSE without the CSM module support
## 
## 15    7/28/10 4:47a Mallikarjunanv
## EIP-29951: TSE Device Path Name support updated
## 
## 14    7/12/10 4:48p Madhans
## EIP 39113: Sign ON Message Support.
## 
## 13    4/21/10 12:13p Madhans
## 
## 12    4/13/10 5:12p Madhans
## EIP: 37439 To support extended OEM Key support.
## 
## 11    4/05/10 10:36a Madhans
## EIP 37036 : To make TSE 2.01 Binary module to work with older Cores
## 
## 10    4/02/10 5:02p Madhans
## EIP 36875. Support to add OEM multiple header files to TSE 2.x.
## 
## 9     2/26/10 1:28p Madhans
## Bootonly source module need AMITSEStrTokens.h
## 
## 8     2/19/10 2:30p Madhans
## 
## 5     10/28/09 5:34p Madhans
## 1. Support to Add the String from other modules to TSE.
## 2. Clean of GIF and Image code Control them with minimal code from TSE
## binary.
## 
## 
## 4     9/15/09 9:05a Sudhirv
## added support for default langue handling
## 
## 3     7/30/09 7:50a Mallikarjunanv
## updated the code to move the exit page option elinks to Tse Binary
## 
## 2     7/14/09 6:32p Blaines
## For GTSE first Release.,
## 
## 1     6/04/09 7:49p Madhans
## AMI TSE Advanced.
# 
# 2     5/07/09 10:31a Madhans
# Changes After Bin module.
## 
## 3     5/06/09 12:28p Mallikarjunanv
## updated with tse bin support
## 
## 2     5/05/09 3:26p Madhans
## include the external UNI in the end to not to affect the index
## 
## 1     4/28/09 10:24p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 2     1/30/09 6:06p Madhans
## Function headers added. 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AMITSE.mak
#
# Description:	AMI TSE BIN module makefile for Aptio.
#
#<AMI_FHDR_END>
#**********************************************************************
TSE_BINARY_INCLUDES = \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSE_BOARD_DIR) \
	-I $(PROJECT_DIR)\Include\Protocol

!INCLUDE Build\TimeStamp.mak

!IF "$(TSE_SDBS)"!=""
TSE_SDBS = -db $(TSE_SDBS: = -db )
!ENDIF

!IF "$(AMITSE_VERSION)"!=""
#Dummy variable to append space
SPACE_APPEND=
AMITSE_VERSION=$(AMITSE_VERSION) $(SPACE_APPEND) 
!ENDIF

all : AMITSE

!IF "$(TSE_ROMHOLE_SUPPORT)" == "1"	
AMITSE : SetupData SignONPack $(BUILD_DIR)\AMITSE.mak AMITSESDB AMITSEHpk AMITSEBin $(BUILD_DIR)\SmLogo.FFS $(BUILD_DIR)\OEMLogo.FFS ROMHOLESupport $(BUILD_DIR)\ROMHOLE.ffs
!ELSE
AMITSE : SetupData SignONPack $(BUILD_DIR)\AMITSE.mak AMITSESDB AMITSEHpk AMITSEBin $(BUILD_DIR)\SmLogo.FFS $(BUILD_DIR)\OEMLogo.FFS
!ENDIF

$(BUILD_DIR)\AMITSE.mak : $(TSEBIN_DIR)\$(@B).cif $(TSEBIN_DIR)\$(@B).mak $(BUILD_RULES) ELinkList OemHeaderList
	$(CIF2MAK) $(TSEBIN_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

ElinkList :
   @copy << $(BUILD_DIR)\AMITSEElinks.h

#define HOOK_LIST_FROM_ELINKS $(AMITSE_Hooks)
#define CONTROL_KEY_MAP_LIST $(CONTROL_KEY_MAP_LIST)
#define EXIT_PAGE_OPTIONS_LIST $(EXIT_PAGE_OPTIONS_LIST)
#define OEM_KEY_CALLBACK_FN $(OEM_KEY_CALLBACK_LIST)
#define AMITSE_HIDDEN_PAGE_LIST $(AMITSE_HIDDEN_PAGE_LIST)
#define AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST $(AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST)
#define AMITSE_ROOT_PAGE_ORDER $(AMITSE_ROOT_PAGE_ORDER)
#define PASSWORD_ENOCDE_LIST $(PASSWORD_ENOCDE_LIST)
#define AMITSE_FILTER_CLASSGUID_FORMSETS $(AMITSE_FILTER_CLASSGUID_FORMSETS)
#define AMITSE_SUPPRESS_DYNAMIC_FORMSET_LIST $(AMITSE_SUPPRESS_DYNAMIC_FORMSET_LIST)
#define AMITSE_DYNAMICPARSING_HANDLE_SUPPRESS_LIST $(AMITSE_DYNAMICPARSING_HANDLE_SUPPRESS_LIST)

<<

OemHeaderList:$(AMITSE_OEM_HEADER_LIST) $(BUILD_DIR)\token.mak
	type << >$(BUILD_DIR)\AMITSEOem.h
!IF "$(AMITSE_OEM_HEADER_LIST)"!=""
#include<$(AMITSE_OEM_HEADER_LIST: =>^
#include<)>
!ENDIF
<<

!if "$(UEFI_2_1_SUPPORT)" == "1"
IFRSUPPORTLIB = $(UEFIEFIIFRSUPPORTLIB)
!else
IFRSUPPORTLIB = $(EFIIFRSUPPORTLIB)
!endif

AMITSE_Objects = $(AMITSE_Objects) \
		 $(BUILD_DIR)\$(TSEBIN_DIR)\bootflow.obj \
		 $(BUILD_DIR)\$(TSEBIN_DIR)\commonoem.obj \
		 $(BUILD_DIR)\$(TSEBIN_DIR)\HookList.obj \
		 $(BUILD_DIR)\$(TSEBIN_DIR)\CommonHelper.obj \
		 $(BUILD_DIR)\$(TSEBIN_DIR)\KeyMon.obj \
		 

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
EDK : AMITSEHpk
AMITSEBin : $(MINISETUPLIB) $(EFIDRIVERLIB) $(IFRSUPPORTLIB) $(EDKFRAMEWORKGUIDLIB) $(EFIDRIVERLIB)
!else
AMITSEBin : $(MINISETUPLIB) $(AMIDXELIB)
!endif
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AMITSE.mak all\
		"MY_INCLUDES=$(TSE_BINARY_INCLUDES)"\
		GUID=B1DA0ADF-4F77-4070-A88E-BFFE1C60529A\
		ENTRY_POINT=MiniSetupApplication\
		TYPE=BS_DRIVER HAS_RESOURCES=1 LIBRARIES= \
		RESOURCE=$(BUILD_DIR)\setupdat.bin\
		SECTION_GUID=FE612B72-203C-47B1-8560-A66D946EB371\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		COMPRESS=1\
		SDB_FILES=\
		"VFR_PACKS=$(BUILD_DIR)\AMITSEStr.hpk $(VFR_PACKS)"\
		"OBJECTS=$(AMITSE_Objects)"\
		"CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50 /DTSE_CALLBACK_SPEC_VERSION=$(TSE_CALLBACK_SPEC_VERSION)"

#        "STRING_CONSUMERS=$(TSE_STRING_CONSUMERS_LIST)"\
#		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\

SetupData :
#The actual NVRAM size is $(NVRAM_SIZE) - $(NVRAM_HEADER_SIZE)
    $(ECHO) SET /A NVRAM_SIZE=$(NVRAM_SIZE)-$(NVRAM_HEADER_SIZE) > $(BUILD_DIR)\HPKTOOL.bat
## EIP-51007: changed the ini file path as sdl Token
    $(ECHO) $(HPKTOOL) -i$(IFR_DIR_LIST: = -i) -f$(INI_FILE_PATH)\
        -o$(BUILD_DIR)\setupdata_asm.asm -do$(BUILD_DIR)\NVRAM.bin\
!IF "$(MANUFACTURING_MODE_SUPPORT)"=="1"
        -dm -ml$(DEFAULT_LANGUAGE)\
!ENDIF
############################################################################
## Adding RT attribute to DEFAULT_VAR_ATTRIBUTE in command-line
## based on token RT_ACCESS_SUPPORT_IN_HPKTOOL
## when token is enabled RT will add to DEFAULT_VAR_ATTRIBUTE to form 0x07
#############################################################################
!IF "$(RT_ACCESS_SUPPORT_IN_HPKTOOL)"=="1"
	-RT\
!ENDIF
#############################################################################
        -dl$(DEFAULT_LANGUAGE)\
        -ds%%NVRAM_SIZE%% -dp$(SETUP_ORPHAN_PAGES_AS_ROOT_PAGE) -dn$(NVRAM_RECORD_CHECKSUM_SUPPORT) -de$(FLASH_ERASE_POLARITY) -vs$(EFI_SPECIFICATION_VERSION) -h$(AMITSE_HPK_FILE_ORDER) >> $(BUILD_DIR)\HPKTOOL.bat
    $(BUILD_DIR)\HPKTOOL.bat
	$(ASM) /c /nologo /Fo$(BUILD_DIR)\ $(BUILD_DIR)\setupdata_asm.asm
	$(ASMLINK) $(BUILD_DIR)\setupdata_asm.obj, $(BUILD_DIR)\setupdat.exe, $(BUILD_DIR)\setupdata_asm.map,,,
	exe2bin $(BUILD_DIR)\setupdat.exe $(BUILD_DIR)\setupdat.bin
	-$(DEL) pkgtmp*.tmp

$(BUILD_DIR)\SmLogo.ffs : $(TSEBIN_DIR)\SmLogo.bmp
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=63819805-67BB-46ef-AA8D-1524A19A01E4 \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

$(BUILD_DIR)\OEMLogo.ffs : $(OEMLogo_FILE_PATH)
!IF "$(TSE_OEM_POSTLOGO_SUPPORT)" == "1"
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
# Don't change the GUID. ChangeLogo expects this GUID.
	GUID=294B1CEF-9BEB-42D5-9971-0C8963CDAF02 \
	TYPE=EFI_FV_FILETYPE_FREEFORM \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)
!ENDIF

$(BUILD_DIR)\AMITSEStrTokens.h : AMITSEHpk

AMITSEHpk : $(BUILD_DIR)\AMITSE.mak AMITSESDB
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AMITSE.mak all\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		STRING_CONSUMERS=$(TSEBIN_DIR)\FakeTokens.c\
		TYPE=SDB NAME=AMITSE 

    $(MAKE) /$(MAKEFLAGS) /a $(BUILD_DEFAULTS) TYPE=SDB\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		"STRING_CONSUMERS=$(TSE_STRING_CONSUMERS_LIST)"\
		"STRGATHER_FLAGS=-db $(BUILD_DIR)\AMITSE.sdb $(TSE_SDBS)"\
        /f $(BUILD_DIR)\AMITSE.mak $(BUILD_DIR)\AMITSEStrTokens.h
# EIP-75136 ROMHOLE Support start
##################################################################################################
#	ROMHOLE generation									##
#	Generating FV_HOLE_VOL.inf file for ROMHole						##
##################################################################################################

!IF "$(TSE_ROMHOLE_SUPPORT)" == "1"

!IF EXIST ($(BUILD_DIR)\FV_HOLE_VOL.inf )
	del $(BUILD_DIR)\FV_HOLE_VOL.inf 
!ENDIF
	echo [options]													>>	$(BUILD_DIR)\FV_HOLE_VOL.inf 
# This is a dummy base address to store logos in ROMHOLE.This address has no effect in ROMHOLE.
	echo EFI_BASE_ADDRESS		=	0xFFFE0000						>>	$(BUILD_DIR)\FV_HOLE_VOL.inf 
	echo EFI_FILE_NAME			=	$(BUILD_DIR)\FV_HOLE_VOL.FV		>>	$(BUILD_DIR)\FV_HOLE_VOL.inf 
	echo EFI_NUM_BLOCKS			=	$(ROMHOLE_NUMBER_OF_BLOCK)		>>	$(BUILD_DIR)\FV_HOLE_VOL.inf 
	echo EFI_BLOCK_SIZE			=	$(ROMHOLE_BLOCK_SIZE) 			>>	$(BUILD_DIR)\FV_HOLE_VOL.inf 
	echo IGNORE_COMPRESSION		=	TRUE 	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo [attributes] 						>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_READ_DISABLED_CAP	=	TRUE 	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_READ_ENABLED_CAP	=	TRUE 	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_READ_STATUS		=	TRUE 	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_WRITE_DISABLED_CAP	=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_WRITE_ENABLED_CAP	=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_WRITE_STATUS		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_LOCK_CAP			=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_LOCK_STATUS		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_STICKY_WRITE		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_MEMORY_MAPPED		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ERASE_POLARITY		=	1		>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_CAP		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_2		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_4		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_8		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_16		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_32		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_64		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_128		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_256		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_512		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_1K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_2K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_4K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_8K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_16K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_32K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_ALIGNMENT_64K		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_READ_LOCK_CAP		=	TRUE	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_READ_LOCK_STATUS	=	TRUE 	>> 	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_WRITE_LOCK_CAP		=	TRUE 	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_WRITE_LOCK_STATUS	=	TRUE	>> 	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo EFI_FVB2_ALIGNMENT		=	8		>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
	echo [files]							>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
!IF "$(TSE_OEM_POSTLOGO_SUPPORT)" == "1"
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\OEMLogo__.pkg	>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
!ENDIF
	echo EFI_FILE_NAME	=	$(BUILD_DIR)\Logo__.pkg		>>	$(BUILD_DIR)\FV_HOLE_VOL.inf
!ENDIF

ROMHOLESupport:	
!IF $(PI_SPECIFICATION_VERSION) >= 0x00010000
   $(FWBUILD) Build\ROMHOLE.fv /f $(BUILD_DIR)\FV_HOLE_VOL.inf /p 1.0
!ELSE
   $(FWBUILD) Build\ROMHOLE.fv /f $(BUILD_DIR)\FV_HOLE_VOL.inf
!ENDIF

$(BUILD_DIR)\ROMHOLE.ffs: Build\ROMHOLE.fv
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=$(TSE_ROMHOLE_MAKFILE_GUID)\
	TYPE=EFI_FV_FILETYPE_RAW\
	FFS_ALIGNMENT=1 FFS_CHECKSUM=0\
	RAWFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)

#####################################################################################################################################
# EIP-75136 ROMHOLE Support End
# Signon Pack
SignONPack : 
    copy << $(BUILD_DIR)\logomode.c
    #include "token.h"
    MAX_POST_GC_MODE
<<
    copy << $(BUILD_DIR)\logomode.bat
    $(CP) /EP $(BUILD_DIR)\logomode.c > $(BUILD_DIR)\mode.txt
    @for /F "tokens=4,5 delims=,}" %%B in ($(BUILD_DIR)\mode.txt) do @(
					set MAX_X=%%B
 				    set MAX_Y=%%C )
    @echo LOGO_X EQU %MAX_X% > $(BUILD_DIR)\LogoRes.inc
    @echo LOGO_Y EQU %MAX_Y% >> $(BUILD_DIR)\LogoRes.inc
<<
    $(BUILD_DIR)\logomode.bat
    $(SILENT)copy << $(BUILD_DIR)\sgn.asm  > NUL
.586p 
.model	flat,C 
.data

include $(BUILD_DIR)\LogoRes.inc
!IF "$(SETUP_BMP_LOGO_SUPPORT)" == "1"
BMP_SUPPORT EQU 01h
!ELSE
BMP_SUPPORT EQU 00h
!endif

!IF "$(SETUP_JPEG_LOGO_SUPPORT)" == "1"
JPEG_SUPPORT EQU 02h
!ELSE
JPEG_SUPPORT EQU 00h
!endif

!IF "$(SETUP_GIF_LOGO_SUPPORT)" == "1"
GIF_SUPPORT EQU 04h
!ELSE
GIF_SUPPORT EQU 00h
!endif

!IF "$(SETUP_PCX_LOGO_SUPPORT)" == "1"
PCX_SUPPORT EQU 08h
!ELSE
PCX_SUPPORT EQU 00h
!endif

!IF "$(SETUP_PNG_LOGO_SUPPORT)" == "1"
PNG_SUPPORT EQU 10h
!ELSE
PNG_SUPPORT EQU 00h
!endif


public	_SgnOn

_SgnOn	label	byte

	db	24h, 'S', 'G', 'N', 24h
	db	2h
	dw	0	        ;Reserved
	db	'$(AMITSE_VERSION)Copyright (C) %04x American Megatrends, Inc.',0h
	db	'$(BIOS_SIGNON_MESSAGE2)',0h
    db  24h,'L','G','O',24h
    db  1h
    dd  BMP_SUPPORT+JPEG_SUPPORT+GIF_SUPPORT+PCX_SUPPORT+PNG_SUPPORT
    dw  LOGO_Y
    dw  LOGO_X
end
<<KEEP
	$(ASM) /c /nologo /Fo$(BUILD_DIR)\ $(BUILD_DIR)\sgn.asm
	$(ASMLINK) $(BUILD_DIR)\sgn.obj, $(BUILD_DIR)\sgn.exe, $(BUILD_DIR)\sgn.map,,,
	exe2bin $(BUILD_DIR)\sgn.exe $(BUILD_DIR)\sgn.bin
    $(MAKE) /f Core\FFS.mak BUILD_DIR=$(BUILD_DIR) \
	    GUID=A59A0056-3341-44b5-9C9C-6D76F7673817 \
        HAS_RESOURCES=1 \
		RESOURCE=$(BUILD_DIR)\sgn.bin\
		SECTION_GUID=2EBE0275-6458-4af9-91ED-D3F4EDB100AA\
		TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFSFILE=$(BUILD_DIR)\SignON.FFS COMPRESS=0 NAME=SignON

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Norcross, Georgia 30093          **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
