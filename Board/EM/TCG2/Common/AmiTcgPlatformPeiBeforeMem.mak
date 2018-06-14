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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformPei/AmiTcgPlatformPeiBeforeMem/AmiTcgPlatformPeiBeforeMem.mak 2     6/09/14 4:53p Fredericko $
#
# $Revision: 2 $
#
# $Date: 6/09/14 4:53p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgPlatform/AmiTcgPlatformPei/AmiTcgPlatformPeiBeforeMem/AmiTcgPlatformPeiBeforeMem.mak $
# 
# 2     6/09/14 4:53p Fredericko
# 
# 1     4/21/14 2:17p Fredericko
# 
# 1     10/08/13 12:04p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:54p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 4     9/27/11 10:29p Fredericko
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
# 3     4/22/11 8:56p Fredericko
# Changes for x32bit mode build
# 
# 2     3/29/11 2:22p Fredericko
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
# Name:		AmiTcgPlatformPeiBeforeMem.mak
#
# Description:	Make file for AmiTcgPlatformPeiBeforeMem
#
#<AMI_FHDR_END>
#************************************************************************
all : AmiTcgPlatformPeiBeforeMem  $(BUILD_DIR)\AmiTcgLibPei.lib

AmiTcgPlatformPeiBeforeMem : $(BUILD_DIR)\AmiTcgPlatformPeiBeforeMem.mak AmiTcgPlatformPeiBeforeMembin

$(BUILD_DIR)\AmiTcgPlatformPeiBeforeMem.mak : $(AMI_TCG_PLATFORM_PEI_DIR)\$(@B).cif $(AMI_TCG_PLATFORM_PEI_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMI_TCG_PLATFORM_PEI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\AmiTcgLibPei.lib : $(BUILD_DIR)\AmiTcgPlatformPeiBeforeMem.mak Make_AMITTCG_LIB

AMITCGLIB_CFLAGS=$(CFLAGS)\
    /I$(TcgPlatformSetupPeiPolicy_DIR)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(TCG_DIR)\Common\Tpm20Includes\
    /I$(AMI_TCG_PLATFORM_PEI_DIR)
    

AMI_TCG_LIB_OBJECTS = \
	$(BUILD_DIR)\$(AMI_TCG_PLATFORM_PEI_DIR)\AmiTcgPlatformPeiLib.obj 

!IFNDEF LIB_BUILD_DIR
!IF "$(PROCESSOR)"=="x64"
TCGLIB=$(BUILD_DIR)\IA32\TisLib.lib
AMITCMLIB = $(BUILD_DIR)\IA32\AmiTcmlib.lib
!ELSE
TCGLIB=$(BUILD_DIR)\TisLib.lib
AMITCMLIB = $(BUILD_DIR)\AmiTcmlib.lib
!ENDIF
!ENDIF #LIB_BUILD_DIR

Make_AMITTCG_LIB : $(TCGLIB) $(AMITCMLIB) $(AMICSPLib)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\AmiTcgPlatformPeiBeforeMem.mak all\
        "CFLAGS=$(AMITCGLIB_CFLAGS) "\
        OBJECTS="$(AMI_TCG_LIB_OBJECTS)"\
        NAME=AmiTcgLibPei\
        MAKEFILE=$(BUILD_DIR)\AmiTcgPlatformPeiBeforeMem.mak \
        TYPE=PEI_LIBRARY


#---------------------------------------------------------------------------
#			Making AmiTcgPlatformPei
#---------------------------------------------------------------------------
AMI_TCG_PEI_PLATFORM_OBJECTS_BEFORE_MEM = \
	$(BUILD_DIR)\$(AMI_TCG_PLATFORM_PEI_DIR)\AmiTcgPlatformPeiBeforeMem.obj \

TCGPEIOVERRIDE_CFLAGS=$(CFLAGS)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(AMI_TCG_PLATFORM_PEI_DIR)\

AmiTcgPlatformPeiBeforeMembin : $(AMIPEILIB)  $(BUILD_DIR)\AmiTcgLibPei.lib  
	    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTcgPlatformPeiBeforeMem.mak  all \
		"CFLAGS=$(TCGPEIOVERRIDE_CFLAGS) "\
        "CPFLAGS=$(TCGPEIOVERRIDE_CFLAGS) "\
		GUID=E9312938-E56B-4614-A252-CF7D2F377E26\
   		"OBJECTS=$(AMI_TCG_PEI_PLATFORM_OBJECTS_BEFORE_MEM)" \
		ENTRY_POINT=AmiTcgPlatformPEI_EntryBeforeMem \
		TYPE=PEIM \
		DEPEX1=$(AMI_TCG_PLATFORM_PEI_DIR)\AmiTcgPlatformPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0
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
