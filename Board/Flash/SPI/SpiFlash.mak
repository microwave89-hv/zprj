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
# $Header: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/SpiFlash.mak 2     4/24/13 11:11p Thomaschen $
#
# $Revision: 2 $
#
# $Date: 4/24/13 11:11p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/Projects/Intel/Haswell/LynxPoint_SharkBay-DT_Crb_1AQQW/Board/Flash/SPI/SpiFlash.mak $
# 
# 2     4/24/13 11:11p Thomaschen
# 
# 5     10/25/10 5:55a Calvinchen
# Added support for PEI Flash Library.
# 
# 4     6/24/09 3:14a Calvinchen
# (EIP22177) Updated for Aptio Source Enhancement. 
#
# 3     4/27/09 3:19a Calvinchen
# 1.Added support for Winbond 25Q128
# 2.(EIP20459) Added Multiple SPI CSP component support.
#
# 2     8/26/08 2:54a Calvinchen
# 1.Added support for AMTME 25DF641.
# 2.Fixed Fail to un-protect ATMEL flash.
# 3.Fixed building failed if $(CFLAGS) = /W4.
#
# 1     3/13/08 6:31a Calvinchen
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
# Name: FlashSrc.mak
#
# Description:
#
#<AMI_FHDR_END>
#**********************************************************************
all : SPIFlash

!IFNDEF SPI_CSP_DIR
SPI_CSP_DIR = $(SPIFlash_DIR)\Template
!ENDIF
SPIFlash : $(BUILD_DIR)\SPIFlash.mak SPIFlashBin

#---------------------------------------------------------------------------
#			Generic SPIFLASH dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\SPIFlash.mak : $(SPIFlash_DIR)\$(@B).cif $(SPI_CSP_DIR)\SpiCspSrc.cif $(SPIFlash_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SPIFlash_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(SPI_CSP_DIR)\SpiCspSrc.cif

#---------------------------------------------------------------------------
#			Create SPIFlash Library
#---------------------------------------------------------------------------
SPI_INCLUDES = \
/I $(SPIFlash_DIR)

SPIFLASH_OBJECTS = $(BUILD_DIR)\$(SPIFlash_DIR)\SpiIdentify.obj \
                   $(BUILD_DIR)\$(SPI_CSP_DIR)\SpiFlash.obj

SPIFlashBin :
                @set INCLUDE=%%INCLUDE%%
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\SPIFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3) $(SPI_INCLUDES)"\
                NAME=SPIFlash \
                OBJECTS="$(SPIFLASH_OBJECTS)" \
                TYPE=LIBRARY LIBRARY_NAME=$(SPIFLASHLIB)
!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
                $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR)\
                "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
                /f $(BUILD_DIR)\SPIFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3) $(SPI_INCLUDES)"\
                BUILD_DIR=$(BUILD_DIR)\IA32\
                TYPE=PEI_LIBRARY NAME=SPIFlash
!ENDIF

$(SPIFLASHLIB) : SPIFlash

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
