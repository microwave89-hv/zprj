#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgPeiAfterMem/TcgPeiAfterMem.mak 1     4/21/14 2:16p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:16p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgPeiAfterMem/TcgPeiAfterMem.mak $
# 
# 1     4/21/14 2:16p Fredericko
# 
# 1     10/08/13 12:03p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 1:57p Fredericko
# 
# 1     7/10/13 5:51p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 3     12/12/11 3:32p Fredericko
# [TAG]  		EIP76865
# [Category]  	Improvement
# [Description]  	Dual Support for TCM and TPM. System could hang in TXT
# if txt is enabled in setup
# [Files]  		AmiTcgPlatfompeilib.c, AmiTcgPlatformPpi.cif,
# AmiTcgPlatformPpi.h, AmiTcgPlatformProtocol.cif,
# AmiTcgPlatformProtocol.h,
# EMpTcmPei.c, TcgDxe.cif, TcgPei.cif, TcgPeiAfterMem.cif,
# TcgPeiAfterMem.mak, TcgTcmPeiAfterMem.c, xTcgDxe.c, xTcgPei.c, 
# xTcgPeiAfterMem.c 
# 
# 2     9/27/11 10:23p Fredericko
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
# 1     8/22/11 1:45p Fredericko
# [TAG]  		EIP61168
# [Category]  	Improvement
# [Description]  	Reload TCG PPI from memory when Memory is Installed
# [Files]  		TcgPeiAfterMem.cif
# TcgPeiAfterMem.c
# xTcgPeiAfterMem.c
# TcgPeiAfterMem.mak
# 
# 25    4/22/11 8:49p Fredericko
# Changes for building in x32 bit mode.
# 
# 24    3/29/11 12:56p Fredericko
# 
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		TCGPEI.MAK
#
# Description:	Make file for the TcgPei component
#
#<AMI_FHDR_END>
#**********************************************************************
all : tcgPeiAftermem

tcgPeiAftermem : $(BUILD_DIR)\TcgPeiAftermem.mak TcgPeiBinMem

$(BUILD_DIR)\TcgPeiAftermem.mak : $(TCGPEI_DIR)\$(@B).cif $(TCGPEI_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TCGPEI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TCGPEIMEM_CFLAGS=$(CFLAGS)\
    /I$(TcgPlatformSetupPeiPolicy_DIR)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(TCG_BOARD_OEM__DIR)\

TCG_CORE_POSTMEM_OBJECTS = \
$(BUILD_DIR)\$(TCGPEI_DIR)\TcgPeiAfterMem.obj \
$(BUILD_DIR)\$(TCGPEI_DIR)\TcgTcmPeiAfterMem.obj \
$(BUILD_DIR)\$(TCGPEI_DIR)\xTcgPeiAfterMem.obj

!IFNDEF LIB_BUILD_DIR
!IF "$(PROCESSOR)"=="x64"
TCGLIB=$(BUILD_DIR)\IA32\TisLib.lib.
AMITCMLIB = $(BUILD_DIR)\IA32\AmiTcmlib.lib
Tpm20Crb_lib = $(BUILD_DIR)\IA32\Tpm20CRBLib.lib
!ELSE
TCGLIB=$(BUILD_DIR)\TisLib.lib
AMITCMLIB = $(BUILD_DIR)\AmiTcmlib.lib
!ENDIF
!ENDIF #LIB_BUILD_DIR


TcgPeiBinMem : $(AMIPEILIB) $(BUILD_DIR)\AmiTcgLibPei.lib 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgPeiAftermem.mak all\
		"CFLAGS=$(TCGPEIMEM_CFLAGS) "\
		GUID=12345678-930A-4a95-AB04-2E6CFDFF6631\
        "OBJECTS=$(TCG_CORE_POSTMEM_OBJECTS)" \
		ENTRY_POINT=ReInstallTcgServiceAfterMem \
		TYPE=PEIM \
		DEPEX1=$(TCGPEI_DIR)\TcgPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		EXT_HEADERS=$(BUILD_DIR)\token.h \
		COMPRESS=1\
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
