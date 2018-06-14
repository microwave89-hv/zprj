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
# $Header: /Alaska/SOURCE/Flash_Combined_2/Core/LPC/LpcFlash.mak 5     10/25/10 5:55a Calvinchen $
#
# $Revision: 5 $
#
# $Date: 10/25/10 5:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Flash_Combined_2/Core/LPC/LpcFlash.mak $
# 
# 5     10/25/10 5:55a Calvinchen
# Added support for PEI Flash Library.
# 
# 4     6/24/09 3:13a Calvinchen
# (EIP22177) Updated for Aptio Source Enhancement. 
#
# 3     11/13/08 1:33a Calvinchen
# Fixed Boot Block recovery and re-flash BIOS failed with using SST
# 49LF160C.
#
# 1     12/18/06 3:39p Robert
# Initial Check in
#
# 2     11/22/06 10:46a Robert
# removed redundant addition of AMIDXELIB.  It is included in main make
# file for the component
#
# 1     10/31/06 2:30p Sivagarn
# Initial Checkin
#
#
#**********************************************************************

#<AMI_FHDR_START>
#
# Name: FlashSrc.mak
#
# Description:
#
#<AMI_FHDR_END>
#**********************************************************************
all : LPCFlash

LPCFlash : $(BUILD_DIR)\LPCFlash.mak LPCFlashBin

#---------------------------------------------------------------------------
#			Generic LPC FLASH dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\LPCFlash.mak : $(LPCFlash_DIR)\LPCFlash.cif $(LPCFlash_DIR)\LPCFlash.mak $(BUILD_RULES)
    $(CIF2MAK) $(LPCFlash_DIR)\LPCFlash.cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#			Create LPC Flash Library
#---------------------------------------------------------------------------
LPCFlashBin :
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\LPCFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3)" \
                NAME=LPCFlash \
                TYPE=LIBRARY LIBRARY_NAME=$(LPCFLASHLIB)
!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
                $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR)\
                "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
                /f $(BUILD_DIR)\LPCFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3)"\
                BUILD_DIR=$(BUILD_DIR)\IA32\
                TYPE=PEI_LIBRARY NAME=LPCFlash
!ENDIF

$(LPCFLASHLIB) : LPCFlash

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