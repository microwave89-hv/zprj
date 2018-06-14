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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/TCGSmm/TCGSmm.mak 1     4/21/14 2:18p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:18p $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/TCGSmm/TCGSmm.mak $
# 
# 1     4/21/14 2:18p Fredericko
# 
# 2     12/10/13 12:57p Fredericko
# 
# 1     10/08/13 12:05p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 2     7/11/13 6:12p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20).
# 
# 1     7/10/13 5:57p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 4     12/07/11 4:30p Fredericko
# [TAG]  		EIP59683
# [Category]  	Improvement
# [Description]  	Allow selection between writing to SMI port as a word
# or as a Byte.
# Some platforms might require word writes to the SMI Status port.
# [Files]  		Tcg.cif, Tcg.sdl, Tcg_ppi1_2_Ex.asl, TcgSmm.mak, TcgSmm.c
# 
# 3     8/09/10 2:32p Fredericko
# 
# 2     5/20/10 8:50a Fredericko
# Included File Header
# Included File Revision History 
# EIP 37653
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:  TCGSmm.mak
#
# Description:
# Make file for TCG SMM module
#
#<AMI_FHDR_END>
#*************************************************************************
all : TCGSmm

TCGSmm : $(BUILD_DIR)\TCGSmm.mak TCGSmmBin

$(BUILD_DIR)\TCGSmm.mak : $(TCGSmm_DIR)\TCGSmm.cif $(TCGSmm_DIR)\TCGSmm.mak $(BUILD_RULES)
	$(CIF2MAK) $(TCGSmm_DIR)\TCGSmm.cif $(CIF2MAK_DEFAULTS)

TcgSmmFlags=$(CFLAGS) \
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
	/I$(PROJECT_DIR)\Include\Protocol\

TCGSmmBin : $(AMIDXELIB) $(AMICSPLib) 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TCGSmm.mak all\
        "CFLAGS=$(TcgSmmFlags) "\
        "CPFLAGS=$(TcgSmmFlags) "\
		GUID=FD93F9E1-3C73-46e0-B7B8-2BBA3F718F6C\
		ENTRY_POINT=TCGSmmInit\
		TYPE=BS_DRIVER \
		COMPRESS=1\
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