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
# $Header: /Alaska/BIN/Core/FFS.mak 25    2/05/11 1:43p Artems $
#
# $Revision: 25 $
#
# $Date: 2/05/11 1:43p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/FFS.mak $
# 
# 25    2/05/11 1:43p Artems
# Added Nested FV support
# 
# 24    10/19/10 10:37p Felixp
# UI Seciton generation command is updated to support strings with
# spaces.
# 
# 23    8/30/10 11:27p Felixp
# Improvement(EIP 43254):
# Support for override of the module name string that is included into
# the FFS file user interface section is added.
# The string can be overridden using UI_NAME macro.
# 
# 22    8/20/10 12:51p Felixp
# LZMA compression support
# 
# 21    3/19/10 12:41p Felixp
# 
# 20    3/18/10 5:49p Felixp
# New SDL token USE_CP_RESPONSE_FILE is added.
# When this option is enabled, all C-preprocessor(CP) options are passed
# via the response file.
# The token should be enabled when the length of the CP command line
# exceeds
# maximum supported limit. The token is disabled by default.
# 
# 19    11/23/09 6:18p Felixp
# Version FFS section support is added.
# 
# 18    10/22/07 6:11p Felixp
# New FFS_ALIGNMENT switch added to support FFS data alignment
# 
# 17    9/05/07 6:15p Felixp
# TE Image support is disabled.
# This is work in progress. TE image support will be enabled in the
# future Core versions.
# 
# 16    6/01/07 2:51p Felixp
# TE image support added.
# File header comments improved
# 
# 15    3/30/07 4:43p Felixp
# Support for FFS_CHECKSUM added to control FFS checksum generation.
# 
# 14    3/18/07 1:52p Felixp
# TE image support is commented out. More testing is required before this
# can be enabled
# 
# 13    3/18/07 12:44p Felixp
# Support for TE images added
# 
# 12    3/13/07 9:54a Felixp
# Global and CPU architecture specific macros are now passed 
# to C preprocessor (used during DepEx and VFR compilation)
# 
# 11    2/27/07 2:37p Markw
# 
# 10    10/03/06 8:56a Felixp
# EXTRA_INCLUDES and EXTRA_DEFINES macros added to pass include
# directories and macro definitions for dependency expression
# preprocessing
# 
# 9     8/24/06 9:06a Felixp
# Preliminary x64 support (work in progress)
# 
# 8     5/19/06 6:14p Felixp
# 1. Support for EDK-based modules added.
# 2. MY_INCLUDES macro added to specify list of include directories
# 
# 7     1/10/06 9:42a Felixp
# do not create UI section for RAW files
# 
# 6     1/09/06 11:27a Felixp
# Support for UI section added
# 
# 4     1/05/06 2:38p Felixp
# support of UI sections added
# 
# 3     11/07/05 3:00p Davidd
# $(SILENT_OUT) removed for GenSection since new version of the utility
# supports silent execution.
# 
# 2     11/07/05 10:07a Felixp
# support for FREFORM_GUID sections added (to support AMI resource
# sections)
# 
# 1     1/28/05 12:43p Felixp
# 
# 5     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 3     1/14/05 12:35p Markw
# RAWFILE now can be anywhere in the project directory
# 
# 2     1/12/05 3:16p Felixp
# support for separetely built sections added
# 
# 1     12/23/04 9:41a Felixp
# 
# 9     12/03/04 6:12p Felixp
# brief build mode added
# 
# 8     11/03/04 7:36p Felixp
# package file handling chaned:
# 1. package file is now recreated during every build
# 2. we no longer need dummy attrib utility
# 
# 7     7/13/04 10:42a Felixp
# 
# 6     4/10/04 2:17p Felixp
# 
# 5     4/07/04 1:02p Felixp
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
# Name:	FFS.mak
#
# Description:	
# This makefile defines process of Firmware File System File creation.
# The following macros have to be defined:
#       BUILD_DIR - temporary files derectory
#       SOURCE_DIR - source files derectory
#	GUID - GUID of the FFS file to be created
#	TYPE - FFS File Type.
#		Possible Values:
#			EFI_FV_FILETYPE_APPLICATION
#			EFI_FV_FILETYPE_FREEFORM
#			EFI_FV_FILETYPE_RAW
#			EFI_FV_FILETYPE_PEIM
#			EFI_FV_FILETYPE_PEI_CORE
#			EFI_FV_FILETYPE_COMBINED_PEIM_DRIVER
#			EFI_FV_FILETYPE_DXE_CORE
#			EFI_FV_FILETYPE_DRIVER
#           EFI_FV_FILETYPE_FIRMWARE_VOLUME_IMAGE
#       FFSFILE - FFS File Name (including path)
# The following macros may be defined:
#	COMPRESS - disables/enable compression within FFS file
#		Possible values: 
#			1 - enable compression
#           <any other value> - disable compression
#	DEPEX1,DEPEX1_TYPE - First Dependency Expression source file name(including path) and type
#	DEPEX2,DEPEX2_TYPE - Second Dependency Expression source file(including path) name and type
#		Possible Values for DEPEX1_TYPE,DEPEX2_TYPE:
#			EFI_SECTION_PEI_DEPEX
#			EFI_SECTION_DXE_DEPEX
#	PEFILE - PE File Name
#	BINFILE - Binary File Name
#	RAWFILE - File Name
#	SECTION - File Name (without path, BUILD_DIR used)
#   RESOURCE, SECTION_GUID - Resource File Name and GUID of the resource section. 
#       The $(RESOURCE) file will be encapsulated into section of type EFI_SECTION_FREEFORM_SUBTYPE_GUID
#       with GUID set to $(SECTION_GUID).
#   EXTRA_INCLUDES - List include directories for dependency expression preprocessing
#   EXTRA_DEFINES - List of macro definitions for dependency expression preprocessing
#   FFS_CHECKSUM - 0 or 1. Enables/Disables FFS file checksum
#   FFS_ALIGNMENT - FFS file data alignment. Supported values are from 0 to 7.
#       FFS_ALIGNMENT value  -   FFS Data Alignment 
#       0 or not specified - no alignment requirements
#       1 - 16 bytes
#       2 - 128 bytes
#       3 - 512 bytes
#       4 - 1K 
#       5 - 4K 
#       6 - 32K 
#       7 - 64K 
#   VERSION - Build Number to be inserted into the version section
#   VERSIONSTRING - Version string to be inserted into the version section
#<AMI_FHDR_END>
#**********************************************************************
!INCLUDE $(BUILD_DIR)\token.mak

PKGFILE=$(FFSFILE:.ffs=)
!IF "$(PKGFILE)"=="$(FFSFILE)"
PKGFILE=$(FFSFILE:.FFS=)
!IF "$(PKGFILE)"=="$(FFSFILE)"
PKGFILE=$(FFSFILE:.Ffs=)
!ENDIF
!ENDIF
PKGFILE=$(PKGFILE)__.pkg

all : $(PKGFILE)

!IFDEF DEPEX1
$(PKGFILE) : $(BUILD_DIR)\$(NAME)_DPX1.tmp
$(BUILD_DIR)\$(NAME)_DPX1.tmp : $(DEPEX1)
!IF "$(USE_CP_RESPONSE_FILE)"=="1"
  $(CP) @<<$(BUILD_DIR)\$(NAME)CpOptions.txt $(DEPEX1) > $*.tmp1
$(CPFLAGS)
<<KEEP
!ELSE
  $(CP) $(CPFLAGS) $(DEPEX1) > $*.tmp1
!ENDIF
  $(GENDEPEX) -I $*.tmp1 -O $@ $(SILENT_OUT)
  $(SILENT)del $*.tmp1
!ENDIF

!IFDEF DEPEX2
$(PKGFILE) : $(BUILD_DIR)\$(NAME)_DPX2.tmp
$(BUILD_DIR)\$(NAME)_DPX2.tmp : $(DEPEX2)
!IF "$(USE_CP_RESPONSE_FILE)"=="1"
  $(CP) @<<$(BUILD_DIR)\$(NAME)CpOptions.txt $(DEPEX2) > $*.tmp1
$(CPFLAGS)
<<KEEP
!ELSE
  $(CP) $(CPFLAGS) $(DEPEX2) > $*.tmp1
!ENDIF
  $(GENDEPEX) -I $*.tmp1 -O $@ $(SILENT_OUT)
  $(SILENT)del $*.tmp1
!ENDIF

!IFDEF PEFILE
$(PKGFILE) : $(PEFILE)
!ENDIF
!IFDEF BINFILE
$(PKGFILE) : $(BINFILE)
!ENDIF
!IFDEF RAWFILE
$(PKGFILE) : $(PROJECT_DIR)\$(RAWFILE)
!ENDIF
!IFDEF SECTION
$(PKGFILE) : $(BUILD_DIR)\$(SECTION)
!ENDIF
!IFDEF RESOURCE
!IF "$(SECTION_GUID)"==""
!ERROR SECTION_GUID for resource $(RESOURCE) is not defined
!ENDIF
$(PKGFILE) : $(RESOURCE)
!ENDIF
!IF "$(CREATE_UI_SECTION)"=="1" && "$(TYPE)"!="EFI_FV_FILETYPE_FREEFORM" && "$(TYPE)"!="EFI_FV_FILETYPE_RAW"
!IFNDEF UI_NAME
UI_NAME=$(NAME)
!ENDIF
!ENDIF

!IF DEFINED(VERSION) || DEFINED(VERSIONSTRING)
!IFNDEF VERSION
VERSION=0
!ENDIF
!ENDIF

!IF "$(LZMA_SUPPORT)" == "1"
COMPRESSION_TYPE = LZMA
!ELSE
COMPRESSION_TYPE = dummy
!ENDIF

!IF "$(COMPRESS)"==""
!ERROR COMPRESS variable is undefined for module $(NAME).
!ENDIF

!IF "$(FFS_CHECKSUM)"=="0"
FFS_ATTRIB_CHECKSUM=FALSE
!ELSE
FFS_ATTRIB_CHECKSUM=TRUE
!ENDIF

$(PKGFILE) :
  @copy << $(PKGFILE) > NUL
PACKAGE.INF
[.]
BASE_NAME                   = DummyName
FFS_FILEGUID                = $(GUID)
FFS_FILETYPE                = $(TYPE)
FFS_ATTRIB_CHECKSUM         = $(FFS_ATTRIB_CHECKSUM)
!IFDEF FFS_ALIGNMENT
FFS_ALIGNMENT               = $(FFS_ALIGNMENT)
!ENDIF

IMAGE_SCRIPT =
{
!IFDEF DEPEX1
    $(NAME)_DPX1.dpx
	{
		TYPE = $(DEPEX1_TYPE)
		BIN = $(BUILD_DIR)\$(NAME)_DPX1.tmp
	}
!ENDIF
!IFDEF DEPEX2
 	$(NAME)_DPX2.dpx
 	{
		TYPE = $(DEPEX2_TYPE)
		BIN = $(BUILD_DIR)\$(NAME)_DPX2.tmp
	}
!ENDIF
!IF $(COMPRESS)==1
  Compress ($(COMPRESSION_TYPE)) {
!ENDIF
!IFDEF PEFILE
    $(NAME)_PE.pe
    {
        TYPE = EFI_SECTION_PE32
	 		BIN = $(PEFILE)
    }
!ENDIF
!IFDEF BINFILE
    $(NAME)_BIN.sec
    {
        TYPE = EFI_SECTION_RAW
        BIN = $(BINFILE)
    }
!ENDIF
!IFDEF SECTION
  	$(BUILD_DIR)\$(SECTION)
!ENDIF
!IFDEF RESOURCE
    $(NAME)_RES.sec
    {
        TYPE = EFI_SECTION_FREEFORM_SUBTYPE_GUID
        BIN  = $(RESOURCE)
        GUID = $(SECTION_GUID)
    }
!ENDIF
!IF DEFINED(FV_FILE) || DEFINED(FV_DESC)
	$(NAME)_FV.sec
	{
		TYPE = EFI_SECTION_FIRMWARE_VOLUME_IMAGE
!IFNDEF FV_DESC
		BIN = FV_FILE
!ELSE
		FV_DESC = $(FV_DESC)
!ENDIF
	}
!ENDIF
!IF "$(CREATE_UI_SECTION)"=="1" && "$(TYPE)"!="EFI_FV_FILETYPE_FREEFORM" && "$(TYPE)"!="EFI_FV_FILETYPE_RAW"
    $(NAME)_UI.sec
    {
        TYPE = EFI_SECTION_USER_INTERFACE
        STRING = $(UI_NAME)
    }
!ENDIF
!IFDEF VERSION
    $(NAME)_VER.sec
    {
        TYPE = EFI_SECTION_VERSION
        BUILD_NO = VERSION
        STRING = $(VERSIONSTRING)
    }
!ENDIF
!IF $(COMPRESS)==1
  }
!ENDIF
!IFDEF RAWFILE
  $(PROJECT_DIR)\$(RAWFILE)
!ENDIF
}
<<KEEP
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
