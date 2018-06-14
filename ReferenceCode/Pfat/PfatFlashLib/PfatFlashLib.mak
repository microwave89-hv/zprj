#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/PfatFlashLib.mak 3     12/19/12 7:22p Fredericko $
#
# $Revision: 3 $
#
# $Date: 12/19/12 7:22p $
#
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/Pfatflashlib/PfatFlashLib.mak $
# 
# 3     12/19/12 7:22p Fredericko
# [TAG]  		EIP109350
# [Category]  	Bug Fix
# [Solution]  	Building error when the token of BUILD_PEI_FLASH_LIB = 1
# for PFAT module
# [Files]  		PfatFlashLib.c
# PfatFlashLib.mak
# 
# 2     9/17/12 4:27p Fredericko
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PfatFlashLib.mak
#
# Description:	Make file for PfatFlashLib
#
#<AMI_FHDR_END>
#**********************************************************************
all : PfatFlashLib

PfatFlashLib : $(BUILD_DIR)\PfatFlashLib.mak PfatFlashLibBin

#---------------------------------------------------------------------------
#			
#---------------------------------------------------------------------------
$(BUILD_DIR)\PfatFlashLib.mak : $(PfatFlashLib_DIR)\$(@B).cif $(PfatFlashLib_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(PfatFlashLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

#---------------------------------------------------------------------------
#			
#---------------------------------------------------------------------------
PFAT_CFLAGS = $(CFLAGS:/W4=/W3) \
    /I$(CpuProtocolLib_DIR) \

PfatFlashLibBin :  
                @set INCLUDE=%%INCLUDE%%
                $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\PfatFlashLib.mak all\
                "CFLAGS=$(PFAT_CFLAGS) /D_DXE_FLASH_LIB_" \
                NAME=PfatFlashLib \
                TYPE=LIBRARY LIBRARY_NAME=$(PFATFLASHLIB)
!IF "$(x64_BUILD)"=="1" && "$(BUILD_PEI_FLASH_LIB)"=="1"
                $(MAKE) /$(MAKEFLAGS) BUILD_ROOT=$(BUILD_DIR)\
                "EXT_OBJS=$(**:Build\=Build\IA32\)" PROJECT_DIR=$(PROJECT_DIR)\
                /f $(BUILD_DIR)\PfatFlashLib.mak all\
                "CFLAGS=$(PFAT_CFLAGS)"\
                BUILD_DIR=$(BUILD_DIR)\IA32\
                TYPE=PEI_LIBRARY NAME=PfatFlashLib
!ENDIF

$(PFATFLASHLIB) : PfatFlashLib
#-----------------------------------------------------------------------
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
