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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgPei.mak 1     4/21/14 2:16p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:16p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TcgPei/TcgPei.mak $
# 
# 1     4/21/14 2:16p Fredericko
# 
# 1     10/08/13 12:02p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     10/03/13 1:51p Fredericko
# 
# 1     7/10/13 5:51p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 27    10/24/11 12:39p Fredericko
# WAIT_FOR_MEM token is deprecated. Use the StartupCmd_Selftest_State to
# control when TPM is first used. 
# 
# 26    9/27/11 10:20p Fredericko
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
all : tcgPei 

tcgPei : $(BUILD_DIR)\TcgPei.mak TcgPeiBin 

$(BUILD_DIR)\TcgPei.mak : $(TCGPEI_DIR)\$(@B).cif $(TCGPEI_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TCGPEI_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TCGPEI_CFLAGS=$(CFLAGS)\
    /I$(TcgPlatformSetupPeiPolicy_DIR)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TPM20_CRBLIB)\
    /I$(TCG_DIR)\Common\
    /I$(TCG_BOARD_OEM__DIR)\

!IFNDEF LIB_BUILD_DIR
!IF "$(PROCESSOR)"=="x64"
TCGLIB=$(BUILD_DIR)\IA32\TisLib.lib
!ELSE
TCGLIB=$(BUILD_DIR)\TisLib.lib
!ENDIF
!ENDIF #LIB_BUILD_DIR

TcgPeiBin : $(AMIPEILIB) $(BUILD_DIR)\AmiTcgLibPei.lib $(BUILD_DIR)\IA32\Tpm20CRBLib.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TcgPei.mak all\
		"CFLAGS=$(TCGPEI_CFLAGS) "\
		GUID=34989D8E-930A-4a95-AB04-2E6CFDFF6631\
		ENTRY_POINT=CommonTcgPeiEntryPoint \
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
