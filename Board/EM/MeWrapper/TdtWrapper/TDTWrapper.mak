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
#
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TDTWrapper.mak 3     2/23/13 6:33a Klzhan $
#
# $Revision: 3 $
#
# $Date: 2/23/13 6:33a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/TdtWrapper/TDTWrapper.mak $
# 
# 3     2/23/13 6:33a Klzhan
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Fix build error when OFDB disabled
# 
# 2     1/24/13 3:51a Klzhan
# [TAG]  		EIP113197 
# [Category]  	Improvement
# [Description]  	Block AFU when DTimer is running out.
# [Files]  		TDTWrapper.dxs
# TDTWrapper.c
# TDTWrapper.mak
# TDTWrapper.sdl
# TDTSetup.sd
# TDTSetup.uni
# TdtCallback.h
# TDTWrapper.cif
# 
# 1     2/08/12 1:07a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:40a Klzhan
# Initial Check-in
# 
# 2     12/03/10 5:56a Klzhan
# Fix Build error.
# 
# 1     12/03/10 5:09a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: TDTDxe.mak
#
# Description:
#
#<AMI_FHDR_END>
#**********************************************************************
# MAK file for the ModulePart:TDTPlatformPolicy
!IFDEF OFBD_SUPPORT

!IF $(OFBD_SUPPORT) == 1
all : TdtWrapper TdtOfbd
!ELSE #!IF $(OFBD_SUPPORT) == 1
all : TdtWrapper
!ENDIF

!ELSE #!IFDEF OFBD_SUPPORT
all : TdtWrapper
!ENDIF

BUILD_TDTWRAPPER_DIR = $(BUILD_DIR)\$(TdtWrapper_DIR)

TdtWrapper : $(BUILD_DIR)\TdtWrapper.mak TdtWrapperBin

$(BUILD_DIR)\TdtWrapper.mak : $(TdtWrapper_DIR)\$(@B).cif $(TdtWrapper_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(TdtWrapper_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


# MAK file for the eModule:TdtWrapper
TdtAm_INCLUDES =\
  $(TDT_INCLUDES)\
  $(ME_INCLUDES)

TdtWrapper_OBJECTS = $(BUILD_TDTWRAPPER_DIR)\TdtWrapper.obj

TdtWrapper_CFLAGS = $(CFLAGS)

TdtWrapperBin : $(AMIDXELIB) $(AMICSPLib) $(MeLibDxe_LIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\TdtWrapper.mak all\
            "MY_INCLUDES=$(TdtAm_INCLUDES)"\
            NAME=TdtWrapper\
            MAKEFILE=$(BUILD_DIR)\TdtWrapper.mak \
            "CFLAGS=$(TdtWrapper_CFLAGS) /I$(TdtWrapper_DIR)"\
            GUID=CA5E3DF0-940A-48f1-8C14-DB2FB5998B36\
            OBJECTS="$(TdtWrapper_OBJECTS)" \
            ENTRY_POINT=TdtWrapperEntryPoint\
            TYPE=BS_DRIVER \
            DEPEX1=$(TdtWrapper_DIR)\TdtWrapper.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
            COMPRESS=1

#---------------------------------------------------------------------------
#               Create TDT OFBD Library
#---------------------------------------------------------------------------
TdtOfbd : $(BUILD_DIR)\TdtWrapper.mak TdtOfbdLibBin

TDT_OFBD_INCLUDES =\
/I$(OFBD_DIR)\
/I$(MeProtocolLib_DIR)\
/I$(AtAmDxe_DIR)\
$(ME_INCLUDES)

TdtOfbd_OBJECTS = $(BUILD_TDTWRAPPER_DIR)\TdtOfbd.obj
           
TdtOfbdLibBin : $(AMIDXELIB)
            @set INCLUDE=%%INCLUDE%%
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\TdtWrapper.mak all\
            "MY_INCLUDES=$(TDT_OFBD_INCLUDES)" \
            "CFLAGS=$(CFLAGS:/W4=/W3)" \
            OBJECTS="$(TdtOfbd_OBJECTS)" \
            TYPE=LIBRARY LIBRARY_NAME=$(TDTOFBDLIB)

$(TDTOFBDLIB) : TdtOfbd
#---------------------------------------------------------------------------
#               Create Intel TDT Setup Screens
#---------------------------------------------------------------------------
SetupSdbs : $(BUILD_DIR)\TdtWrapper.mak TDTSetupSDB

TDTSetupSDB :
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\TdtWrapper.mak all \
            TYPE=SDB NAME=TdtWrapper STRING_CONSUMERS=$(TdtWrapper_DIR)\TDTSetup.sd


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