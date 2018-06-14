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

#*************************************************************************
# $Header: /Alaska/BIN/Modules/CryptoPkg/CryptoAPI.mak 1     6/13/11 5:19p Alexp $
#
# $Revision: 1 $
#
# $Date: 6/13/11 5:19p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/CryptoPkg/CryptoAPI.mak $
# 
# 1     6/13/11 5:19p Alexp
# 
# 2     5/11/11 12:59p Alexp
# renamed cryptolib macro name
# 
# 1     5/06/11 6:11p Alexp
# initial module release
# 
# 5     5/06/11 6:04p Alexp
# link PEI Crypto Lib module
# 
# 4     5/06/11 4:39p Alexp
# add help header
# 
# 3     4/07/11 12:22p Alexp
# 
# 2     4/04/11 7:19p Alexp
# 
# 1     3/10/11 4:52p Alexp
# 
# 1     2/18/11 5:42p Alexp
# 
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: CryptoApi.mak
#
# Description: Build rules to build PEI, DXE and SMM Crypto drivers
#   
#
#<AMI_FHDR_END>
#*************************************************************************
all : CryptoAPI

BUILD_CryptoAPI_DIR = $(BUILD_DIR)\$(CryptoAPI_DIR)
BUILD_CryptoAPIIA32_DIR = $(BUILD_DIR)\IA32\$(CryptoAPI_DIR)

CryptoAPI : CryptLib $(BUILD_DIR)\CryptoAPI.mak CryptoAPIDxeBin \
!IF "$(CryptoPPI_SUPPORT)" == "1"
 CryptoAPIPeiBin 
!ENDIF

#dummy target. Will be used to build Crypto Library if sources are present
CryptLib:

$(BUILD_DIR)\CryptoAPI.mak : $(CryptoAPI_DIR)\CryptoAPI.cif $(CryptoAPI_DIR)\CryptoAPI.mak $(BUILD_RULES)
    $(CIF2MAK) $(CryptoAPI_DIR)\CryptoAPI.cif $(CIF2MAK_DEFAULTS)

CryptoAPI_PEI_OBJECTS = \
    $(BUILD_CryptoAPIIA32_DIR)\CryptoPei.obj

CryptoAPI_DXE_OBJECTS = \
    $(BUILD_CryptoAPI_DIR)\CryptoDxe.obj

CryptoAPI_INCLUDES= \
    /I $(CryptoAPI_DIR)\
    /I $(Cryptlib_DIR)\
    /I $(ReFlash_DIR)\
    /I$(CORE_DIR)

!IF "$(CryptoPPI_SUPPORT)" == "1"
CryptoAPIPeiBin : $(AMIPEILIB) $(CRYPTOLIBPEI)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CryptoAPI.mak all\
        NAME=CryptoPei\
        MAKEFILE=$(BUILD_DIR)\CryptoAPI.mak \
        BUILD_DIR=$(BUILD_DIR)\IA32\
        GUID=D6D2FBA6-EF60-4C38-A83E-6769814D23B0 \
        ENTRY_POINT=CryptoPei_Init \
        "MY_INCLUDES=$(CryptoAPI_INCLUDES)"\
        "CFLAGS=$(CFLAGS) /D PEI_BUILD" \
        OBJECTS="$(CryptoAPI_PEI_OBJECTS)" \
        DEPEX1=$(CryptoAPI_DIR)\CryptoPei.DXS DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
        TYPE=PEIM COMPRESS=1
!ENDIF

CryptoAPIDxeBin : $(AMIDXELIB) $(CRYPTOLIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\CryptoAPI.mak all\
        NAME=CryptoDxe\
        MAKEFILE=$(BUILD_DIR)\CryptoAPI.mak \
        GUID=20D8FFFE-15C3-4ea9-9D28-CFE2745D78F3 \
        ENTRY_POINT=CryptoDxe_Init\
        DEPEX1=$(CryptoAPI_DIR)\CryptoDxe.DXS DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
        "MY_INCLUDES=$(CryptoAPI_INCLUDES) "\
        OBJECTS="$(CryptoAPI_DXE_OBJECTS)" \
        TYPE=RT_DRIVER COMPRESS=1

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
