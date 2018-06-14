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
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TcgDxe.mak 1     4/21/14 2:16p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:16p $
#**********************************************************************
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgDxe/TcgDxe.mak $
# 
# 1     4/21/14 2:16p Fredericko
# 
# 1     10/08/13 12:03p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 1:59p Fredericko
# 
# 1     7/10/13 5:51p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 29    9/27/11 10:25p Fredericko
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
# 28    3/29/11 1:12p Fredericko
# 
# 27    3/28/11 2:17p Fredericko
# [TAG]        EIP 54642
# [Category] Improvement
# [Description] 1. Checkin Files related to TCG function override 
# 2. Include TCM and TPM auto detection
# [Files] Affects all TCG files
# 
# 26    6/30/10 3:05p Fredericko
# Modified for building EMpCallBin32.asm
# 
# 25    5/19/10 5:26p Fredericko
# Updated AMI copy right header
# EIP 37653
# 
# 24    4/21/10 11:49a Fredericko
# Changes on the way Post strings are created for PPI display for
# multi-language support
# 
# 23    4/20/10 12:35p Fredericko
# Included dependency on SetupStrTokens.h. 
# 
# 22    3/23/10 6:53p Fredericko
# Tcglegacy support is currently it's own subcomponent
# 
# 21    3/19/10 4:15p Fredericko
# modified for legacy IO interface support
# 
# 20    6/01/09 4:08p Fredericko
# Changes for building Tcgdxe ffs when TCM_SUPPORT is enabled or
# Disabled.
# 
# 19    4/30/09 6:15p Fredericko
# Updated Header Date
# 
# 18    4/30/09 5:31p Fredericko
# Removed unneccesary directories paths and AMI company Header Address
# changes
# 
# 17    2/05/09 5:10p Fredericko
# USE BUILD_DEFAULTS instead of EDK_DEFAULTS and removal of all EDK paths
# 
# 16    4/10/08 5:29p Fredericko
# Print Library added
# 
# 15    11/02/07 4:26p Fredericko
# Changes to support Montevina Build process
# 
# 1     10/26/07 9:41a Fasihm
# Changed the Link order of the Libraries.
# Need to remove after TCG is labeled again.
# 
# 14    9/26/07 4:52p Fredericko
# 
# 13    9/04/07 6:10p Fredericko
# Cflags defined to make compiler use \W4 switch instead of \W3 switch
# 
# 12    9/04/07 10:16a Fredericko
# Use of AMIDXELIB.
# 
# 11    7/13/07 2:53p Rameshraju
# Added the TPM post meesage based on the UNI string.
# 
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:		TcgDxe.MAK
#
# Description:	Make file for the tcgdxe component
#
#<AMI_FHDR_END>
#**********************************************************************
all : TCGDXE 

TCGDXE : $(BUILD_DIR)\tcgdxe.mak tcgdxeBin #$(BUILD_DIR)\LEGX16.ffs $(BUILD_DIR)\MPTPM.ffs $(BUILD_DIR)\TPM32BIN.ffs
!IF "$(AMI_ZTEIC_SUPPORT)" == "1"
TCGDXE : $(BUILD_DIR)\tcgdxe.mak tcgdxeBin 
!ENDIF

$(BUILD_DIR)\tcgdxe.mak : $(TCGDXE_DIR)\$(@B).cif $(TCGDXE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TCGDXE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TCGDXE_CFLAGS=$(CFLAGS) \
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TPM20_CRBLIB)\
    /I$(TCG_DIR)\Common\
	/I$(PROJECT_DIR)\Include\Protocol\
    /I$(TCG_DIR)\Protocol\
    /I$(TcgPlatformSetupPolicy_DIR)\


!IF "$(x64_BUILD)" != "0"
$(BUILD_DIR)\$(TCGDXE_DIR)\EMpCallBin.obj : $(TCGDXE_DIR)\EMpCallBin.asm 
    $(ASM) /c /nologo /Fo$$(BUILD_DIR)\$(TCG_DIR)\EMpCallBin.obj $(TCG_DIR)\EMpCallBin.asm 
!ELSE
$(BUILD_DIR)\$(TCGDXE_DIR)\EMpCallBin32.obj : $(TCGDXE_DIR)\EMpCallBin32.asm 
    $(ASM) /c /nologo /Fo$$(BUILD_DIR)\$(TCGDXE_DIR)\EMpCallBin32.obj $(TCGDXE_DIR)\EMpCallBin32.asm 
!ENDIF


TCGDXE_OBJECTS = \
$(BUILD_DIR)\$(TCGDXE_DIR)\TpmDxe.obj \
$(BUILD_DIR)\$(TCGDXE_DIR)\TcgDxe.obj \
$(BUILD_DIR)\$(TCGDXE_DIR)\TcgDxe20.obj \
$(BUILD_DIR)\$(TCGDXE_DIR)\xTcgDxe.obj \
$(BUILD_DIR)\$(TCGDXE_DIR)\EMpTcmDxe.obj\
!IF "$(x64_BUILD)" == "0"
$(BUILD_DIR)\$(TCGDXE_DIR)\EMpCallBin32.obj\
!ENDIF
!IF "$(x64_BUILD)" == "1"
$(BUILD_DIR)\$(TCGDXE_DIR)\EMpCallBin.obj\
!ENDIF


tcgdxeBin : $(AMIDXELIB) $(BUILD_DIR)\TisLib.lib $(BUILD_DIR)\Tpm20CRBLib.lib
	@echo CFLAGS=$(CFLAGS)
	@echo TCGDXE_CFLAGS=$(TCGDXE_CFLAGS)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\tcgdxe.mak all\
		"CFLAGS=$(TCGDXE_CFLAGS)"\
		GUID=5E9CABA3-F2B1-497a-ADAC-24F575E9CDE9 \
		ENTRY_POINT=CommonTcgDxEntryPoint \
		TYPE=BS_DRIVER \
        "OBJECTS=$(TCGDXE_OBJECTS)"\
		DEPEX1=$(TCGDXE_DIR)\tcgdxe.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1  HAS_RESOURCES=1\
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
