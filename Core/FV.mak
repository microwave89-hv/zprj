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
# $Header: /Alaska/BIN/Core/FV.mak 12    9/10/12 4:43p Artems $
#
# $Revision: 12 $
#
# $Date: 9/10/12 4:43p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/FV.mak $
# 
# 12    9/10/12 4:43p Artems
# [TAG]  		EIP88859
# [Category]  	Improvement
# [Description]  	Build error in GenRomLayout.bat when too many FFS files
# or file name is too long.
# Added support to handle long strings in batch files
# [Files]  		Fv.mak, Core.mak
# 
# 11    6/23/11 4:37p Artems
# EIP 61949: apriori list make doesn't work. Made changes to use FWBuild
# for apriori list generation
# 
# 10    2/05/11 1:42p Artems
# Added PEI apriori list support
# Added Nested FV support
# Added PI 1.0-1.1 support
# 
# 9     11/05/10 1:44p Felixp
# Improvement(EIP 46043):
#  The build script that generates firmware volume description files
# (Build\FV_xxx.inf) is updated 
#   to support longer file lists.
# 
# 8     1/26/10 5:03p Felixp
# Support for generation of the DXE apriori file is added. 
# The list of FFS files that should be added to the DXE a priori list is
# specified 
# as a part of FV descriptor using DXE_APRIORI_FILE_LIST parameter.
# 
# 7     8/27/09 10:44a Felixp
# Support for OPTIMIZE_SIZE and TOP_DOWN_ALLOCATION FV flags is added.
# 
# 6     5/08/09 6:06p Felixp
# support for ROM holes (FFS files with fixed addresses) is added
# 
# 5     5/08/09 12:15a Felixp
# Ifrastructure to simplify ROM layout customization(EIP 18426).
# Build process and source code that deals with ROM layout 
# is updated in order to simplify ROM layout customization.
# 
# 4     12/29/06 4:02p Felixp
# 
# 2     7/22/05 2:20a Felixp
# support for non-FFS Firmware Volume GUID added
# 
# 1     1/28/05 12:43p Felixp
# 
# 2     1/18/05 3:21p Felixp
# PrintDebugMessage renamed to Trace
# 
# 1     12/23/04 9:41a Felixp
# 
# 4     7/13/04 2:23p Felixp
# 
# 3     7/13/04 10:42a Felixp
# 
# 2     1/08/04 4:46p Felixp
# comments improved
# 
# 1     12/05/03 4:15p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	FV.mak
#
# Description:	This makefile is used to create firmware volume.
#	The following macros have to be defined:
#	BUILD_DIR - build directory that has all the input FFS files. 
#		    The output file $(NAME).fv will be created in this directory.
#	ADDRESS - starting memory address for the firmware volume.
#	NAME - name of the output firmware volume file (just name, no extension)
#	BLOCKS - number of firmware device blocks occupied by the firmware volume
#	BLOCK_SIZE - size of firmware device block in bytes 
#   GENFVIMAGE - full name (path+name) of the GenFvImage utility
#   FILE_LIST - space separated list of FFS files to be included into FV
#   ERASE_POLARITY - 0 or 1. Firmware device erase polarity. 
#	The following optional macros may be defined:
#   DXE_APRIORI_FILE_LIST - space separated list of FFS files to be added to the DXE a priori list
#
#<AMI_FHDR_END>
#**********************************************************************

!IF "$(PEI_APRIORI_FILE_LIST)"!="" && DEFINED(PI_SPECIFICATION_VERSION)
!IF $(PI_SPECIFICATION_VERSION)<0x00010000
!UNDEF PEI_APRIORI_FILE_LIST
!ENDIF
!ENDIF

!IF "$(FILE_LIST)"==""
!IF "$(FILE_LIST_FILE)"==""
!ERROR Empty file list for Firmware volume $(NAME)
!ELSE
!INCLUDE $(FILE_LIST_FILE)
!ENDIF
!ENDIF

# Delete extra spaces and spaces before and after the colon
FILE_LIST1=$(FILE_LIST:     = )
FILE_LIST2=$(FILE_LIST1:    = )
FILE_LIST3=$(FILE_LIST2:   = )
FILE_LIST4=$(FILE_LIST3:  = )
FILE_LIST5=$(FILE_LIST4:  = )
FILE_LIST6=$(FILE_LIST5: :=:) #delete space before the colon
FILE_LIST_CLEAN=$(FILE_LIST6:: =:) #delete space after the colon

all: 
	@copy << $(BUILD_DIR)\$(NAME).inf > NUL
[options]
EFI_BASE_ADDRESS        = $(ADDRESS)
EFI_FILE_NAME           = $(BUILD_DIR)\$(NAME).FV
EFI_NUM_BLOCKS          = $(BLOCKS)
EFI_BLOCK_SIZE          = $(BLOCK_SIZE)
!IFDEF FV_GUID
EFI_FV_GUID             = $(FV_GUID)
!ENDIF
!IFDEF OPTIMIZE_SIZE
OPTIMIZE_SIZE           = $(OPTIMIZE_SIZE)
!ENDIF
!IFDEF TOP_DOWN_ALLOCATION
TOP_DOWN_ALLOCATION     = $(TOP_DOWN_ALLOCATION)
!ENDIF
!IF "$(GLOBAL_COMPRESSION)"=="0"
IGNORE_COMPRESSION = TRUE
!ENDIF
[attributes]
EFI_READ_DISABLED_CAP   = TRUE
EFI_READ_ENABLED_CAP    = TRUE
EFI_READ_STATUS         = TRUE
EFI_WRITE_DISABLED_CAP  = TRUE
EFI_WRITE_ENABLED_CAP   = TRUE
EFI_WRITE_STATUS        = TRUE
EFI_LOCK_CAP            = TRUE
EFI_LOCK_STATUS         = TRUE
EFI_STICKY_WRITE        = TRUE
EFI_MEMORY_MAPPED       = TRUE
EFI_ERASE_POLARITY      = $(ERASE_POLARITY)
EFI_ALIGNMENT_CAP       = TRUE
EFI_ALIGNMENT_2         = TRUE
EFI_ALIGNMENT_4         = TRUE
EFI_ALIGNMENT_8         = TRUE
EFI_ALIGNMENT_16        = TRUE
EFI_ALIGNMENT_32        = TRUE
EFI_ALIGNMENT_64        = TRUE
EFI_ALIGNMENT_128       = TRUE
EFI_ALIGNMENT_256       = TRUE
EFI_ALIGNMENT_512       = TRUE
EFI_ALIGNMENT_1K        = TRUE
EFI_ALIGNMENT_2K        = TRUE
EFI_ALIGNMENT_4K        = TRUE
EFI_ALIGNMENT_8K        = TRUE
EFI_ALIGNMENT_16K       = TRUE
EFI_ALIGNMENT_32K       = TRUE
EFI_ALIGNMENT_64K       = TRUE
#//PI 1.1 New Attribute for PI 1.0 spec
EFI_READ_LOCK_CAP      = TRUE
EFI_READ_LOCK_STATUS   = TRUE
EFI_WRITE_LOCK_CAP     = TRUE
EFI_WRITE_LOCK_STATUS  = TRUE
EFI_FVB2_ALIGNMENT     = 8
<<
    $(ECHO) ^ $(BUILD_DIR)\GenFvList.bat <<$(BUILD_DIR)\$(NAME)FileList.txt $(BUILD_DIR)\$(NAME).inf [files] >> $(BUILD_DIR)\beforefv.mak
$(FILE_LIST_CLEAN: =^
) 
<<KEEP
!IF "$(DXE_APRIORI_FILE_LIST)"!=""
    $(ECHO) ^ $(BUILD_DIR)\GenFvList.bat <<$(BUILD_DIR)\$(NAME)DxeAprioriIn.txt $(BUILD_DIR)\$(NAME).inf [dxeapriori] >> $(BUILD_DIR)\beforefv.mak
$(DXE_APRIORI_FILE_LIST: =^
) 
<<KEEP
!ENDIF
!IF "$(PEI_APRIORI_FILE_LIST)"!=""
    $(ECHO) ^ $(BUILD_DIR)\GenFvList.bat <<$(BUILD_DIR)\$(NAME)PeiAprioriIn.txt $(BUILD_DIR)\$(NAME).inf [peiapriori] >> $(BUILD_DIR)\beforefv.mak
$(PEI_APRIORI_FILE_LIST: =^
) 
<<KEEP
!ENDIF
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