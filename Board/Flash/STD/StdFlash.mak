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
# $Header: /Alaska/SOURCE/Flash_Combined_2/Core/STD/StdFlash.mak 3     10/25/10 5:55a Calvinchen $Revision:
#
# $Date: 10/25/10 5:55a $Log:
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
all : STDFlash

STDFlash : $(BUILD_DIR)\StdFlash.mak StdFlashBin

#---------------------------------------------------------------------------
#			Generic STD FLASH dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\StdFlash.mak : $(STDFlash_DIR)\$(@B).cif $(STDFlash_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(STDFlash_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#			Create STD Flash Library
#---------------------------------------------------------------------------
StdFlashBin :
                @set INCLUDE=%%INCLUDE%%
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\STDFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3)" \
                NAME=STDFlash \
                TYPE=LIBRARY LIBRARY_NAME=$(STDFLASHLIB)
!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
                $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR)\
                "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
                /f $(BUILD_DIR)\STDFlash.mak all\
                "CFLAGS=$(CFLAGS:/W4=/W3)"\
                BUILD_DIR=$(BUILD_DIR)\IA32\
                TYPE=PEI_LIBRARY NAME=STDFlash
!ENDIF

$(STDFLASHLIB) : STDFlash

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