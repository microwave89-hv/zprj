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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformDxe/AmiTcgPlatformDxe.mak 1     4/21/14 2:17p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:17p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformDxe/AmiTcgPlatformDxe.mak $
# 
# 1     4/21/14 2:17p Fredericko
# 
# 1     10/08/13 12:04p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:55p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 7     9/27/11 10:31p Fredericko
# [TAG]  		EIP67286
# [Category]  	Improvement
# [Description]  	changes for Tcg Setup policy
# [Files]  		Tcg.sdl
# TcgPei.cif
# TcgPei.mak
# xtcgPei.c
# xTcgPeiAfterMem.c
# TcgPeiAfterMem.mak
# TcgDxe.cif
# TcgDxe.mak
# xTcgDxe.c
# AmiTcgPlatformPeilib.c
# AmiTcgPlatformDxelib.c
# 
# 6     9/02/11 6:16p Fredericko
# 
# 4     5/31/11 1:56p Daniels
# [TAG]  		EIP58387
# [Category]  	Improvement
# [Description]  	Add StrGather flags to allow strings to be overridden
# with TCGDXE_SDBS eLink.
# [Files]  		AmiTcgPlatformDxe.sdl, AmiTcgPlatformDxe.mak
# 
# 3     4/22/11 8:58p Fredericko
# Changes for x32bit mode build
# 
# 2     3/29/11 2:26p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
#
#
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:		AmiTcgPlatformDxe
#
# Description:	Make file for AmiTcgPlatformDxe
#
#<AMI_FHDR_END>
#************************************************************************
all : AmiTcgPlatformDxe $(BUILD_DIR)\AmiTcgLibDxe.lib 



#---------------------------------------------------------------------------
#			$(BUILD_DIR)\AmiTcgLibDxe.lib
#---------------------------------------------------------------------------
$(BUILD_DIR)\AmiTcgLibDxe.lib : $(BUILD_DIR)\AmiTcgPlatformDxe.mak MakeAmiTcgDxeLib

AMITCGLIB_CFLAGS=$(CFLAGS)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(AMI_TCG_PLATFORM_DXE_DIR)

AMI_TCG_LIB_OBJECTS = \
	$(BUILD_DIR)\$(AMI_TCG_PLATFORM_DXE_DIR)\AmiTcgPlatformDxeLib.obj \


!IFNDEF LIB_BUILD_DIR
!IF "$(PROCESSOR)"=="x64"
AMITCMLIB = $(BUILD_DIR)\IA32\AmiTcmlib.lib
!ELSE
AMITCMLIB = $(BUILD_DIR)\AmiTcmlib.lib
!ENDIF
!ENDIF #LIB_BUILD_DIR

MakeAmiTcgDxeLib: $(BUILD_DIR)\AmiTcmlib.lib
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AmiTcgPlatformDxe.mak all\
        "CFLAGS=$(AMITCGLIB_CFLAGS) "\
        OBJECTS="$(AMI_TCG_LIB_OBJECTS)"\
        NAME=AmiTcgLibDxe\
        MAKEFILE=$(BUILD_DIR)\AmiTcgPlatformDxe.mak \
        TYPE=LIBRARY


#---------------------------------------------------------------------------
#			Making AmiTcgPlatformDxe
#---------------------------------------------------------------------------
AmiTcgPlatformDxe : $(BUILD_DIR)\AmiTcgPlatformDxe.mak AmiTcgPlatformDxebin

$(BUILD_DIR)\AmiTcgPlatformDxe.mak : $(AMI_TCG_PLATFORM_DXE_DIR)\$(@B).cif $(AMI_TCG_PLATFORM_DXE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMI_TCG_PLATFORM_DXE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


TCGDXEOVERRIDE_CFLAGS=$(CFLAGS)\
    /I$(TcgPlatformSetupPolicy_DIR)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(TCG_DIR)\protocol\TcgService\
    /I$(TCG_DIR)\protocol\TpmDevice\
	/I$(PROJECT_DIR)\Include\Protocol\

AmiTcgPlatformDXE_OBJECTS = \
$(BUILD_DIR)\$(AMI_TCG_PLATFORM_DXE_DIR)\AmiTcgPlatformDxe.obj \


AmiTcgPlatformDxebin: $(AMIDXELIB) $(BUILD_DIR)\AmiTcgLibDxe.lib 
	@echo CFLAGS=$(CFLAGS)
	@echo TCGDXEOVERRIDE_CFLAGS=$(TCGDXEOVERRIDE_CFLAGS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTcgPlatformDxe.mak all\
		"CFLAGS=$(TCGDXEOVERRIDE_CFLAGS)"\
   		"CPFLAGS=$(TCGDXEOVERRIDE_CFLAGS)"\
		GUID=A29A63E3-E4E7-495f-8A6A-07738300CBB3 \
		ENTRY_POINT=AmiTcgPlatformDXE_Entry \
		TYPE=BS_DRIVER \
        "OBJECTS=$(AmiTcgPlatformDXE_OBJECTS)"\
		DEPEX1=$(AMI_TCG_PLATFORM_DXE_DIR)\AmiTcgPlatformDxe.dxs  \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1  HAS_RESOURCES=1\
!IF "$(TCGDXE_SDBS: =)"==""
        "STRGATHER_FLAGS=-db $(BUILD_DIR)\$(AMI_TCG_PLATFORM_DXE_DIR)\AmiTcgPlatformDxeString.sdb"\
!ELSE
        "STRGATHER_FLAGS=-db $(BUILD_DIR)\$(AMI_TCG_PLATFORM_DXE_DIR)\AmiTcgPlatformDxeString.sdb -db $(TCGDXE_SDBS: = -db )"\
!ENDIF
#---------------------------------------------------------------------------

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
