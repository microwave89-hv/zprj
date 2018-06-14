#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Flash_Combined_2/Core/Flash.mak 6     7/21/11 5:09a Calvinchen $
#
# $Revision: 6 $
#
# $Date: 7/21/11 5:09a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Flash_Combined_2/Core/Flash.mak $
# 
# 6     7/21/11 5:09a Calvinchen
# [TAG]  		EIP60956
# [Category]  	Improvement
# [Description]  	Added "OemFlashValidTableList" eLink for OEM/ODM
# invalidates the flash part supports those they don't needed.
# [Files]  		Flash.sdl
# Flash.mak
# FlashWrite.c
# Flash.chm
# 
# 5     10/25/10 5:56a Calvinchen
# Added support for PEI Flash Library.
# 
# 4     1/14/09 10:43p Calvinchen
# Added support for OemflashWriteEnable/Disable eLink.
# 
# 3     8/26/08 2:53a Calvinchen
# Fixed Building failed if $(CFLAGS) = /W4.
# 
# 1     12/18/06 3:39p Robert
# Initial Check in
# 
# 1     10/31/06 2:30p Sivagarn
# Initial Checkin
# 
#
#**********************************************************************

#<AMI_FHDR_START>
#
# Name:	Flash.mak
#
# Description:
#
#<AMI_FHDR_END>
#**********************************************************************
all : Flash

!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
Flash : $(BUILD_DIR)\Flash.mak FlashBin FlashPeiBin
!ELSE
Flash : $(BUILD_DIR)\Flash.mak FlashBin
!ENDIF
#---------------------------------------------------------------------------
#			Generic FLASH dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\Flash.mak : $(Flash_DIR)\$(@B).cif $(Flash_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(Flash_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#			Generic FLASH eList
#---------------------------------------------------------------------------
FLASH_E_LISTS = \
/D\"FLASH_LIST=$(FlashList)\"\
/D\"OEM_FLASH_WRITE_ENABLE_LIST=$(OemFlashWriteEnableList)\"\
/D\"OEM_FLASH_WRITE_DISABLE_LIST=$(OemFlashWriteDisableList)\"\
/D\"OEM_FLASH_VALID_TABLE_LIST=$(OemFlashValidTableList)\"

#---------------------------------------------------------------------------
#			Create Flash Library
#---------------------------------------------------------------------------
FlashBin :  $(AMIDXELIB) $(AMICSPLib) $(FLASHLISTLIB)
            @set INCLUDE=%%INCLUDE%%
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\Flash.mak all LIBRARIES= \
            TYPE=LIBRARY NAME=Flash LIBRARY_NAME=$(FLASHLIB)\
            "CFLAGS=$(CFLAGS:/W4=/W3) $(FLASH_E_LISTS) /D_DXE_FLASH_LIB_"
		    
!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
FlashPeiBin: $(AMICSPLib) $(FLASHLISTLIB)
            $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR)\
            "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
            /f $(BUILD_DIR)\Flash.mak all\
            BUILD_DIR=$(BUILD_DIR)\IA32\
            TYPE=PEI_LIBRARY NAME=Flash\
            "CFLAGS=$(CFLAGS:/W4=/W3) $(FLASH_E_LISTS)"
!ENDIF

$(FLASHLIB) : Flash

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
