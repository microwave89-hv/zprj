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
# $Header: /Alaska/SOURCE/Flash_Combined_2/Core/FWH/FwhFlash.mak 5     10/25/10 5:54a Calvinchen $
#
# $Revision: 5 $
#
# $Date: 10/25/10 5:54a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Flash_Combined_2/Core/FWH/FwhFlash.mak $
# 
# 5     10/25/10 5:54a Calvinchen
# Added support for PEI Flash Library.
# 
# 4     6/24/09 3:12a Calvinchen
# (EIP22177) Updated for Aptio Source Enhancement. 
#
# 3     1/20/09 11:58p Calvinchen
#
# 1     12/18/06 3:39p Robert
# Initial Check in
#
# 1     10/31/06 2:30p Sivagarn
# Initial Checkin
#
#
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: FWHFlash.mak
#
# Description:
#
#<AMI_FHDR_END>
#**********************************************************************
all : FWHFlash

FWHFlash : $(BUILD_DIR)\FWHFlash.mak FWHFlashBin

#---------------------------------------------------------------------------
#			Generic FWH FLASH dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\FWHFlash.mak : $(FWHFlash_DIR)\$(@B).cif $(FWHFlash_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(FWHFlash_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#			Create FWH Flash Library
#---------------------------------------------------------------------------
FWHFlashBin :
                @set INCLUDE=%%INCLUDE%%
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\FWHFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3)" \
                NAME=FWHFlash \
                TYPE=LIBRARY LIBRARY_NAME=$(FWHFLASHLIB)
!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
                $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR)\
                "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
                /f $(BUILD_DIR)\FWHFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3)"\
                BUILD_DIR=$(BUILD_DIR)\IA32\
                TYPE=PEI_LIBRARY NAME=FWHFlash
!ENDIF

$(FWHFLASHLIB) : FWHFlash

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