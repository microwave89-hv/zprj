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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgBinaries/TcgBins.mak 1     4/21/14 2:16p Fredericko $
#
# $Revision: 1 $
#
# $Date: 4/21/14 2:16p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgBinaries/TcgBins.mak $
# 
# 1     4/21/14 2:16p Fredericko
# 
# 1     10/08/13 12:03p Fredericko
# Initial Check-In for Tpm-Next module
# 
# 1     7/10/13 5:52p Fredericko
# [TAG]  		EIP120969
# [Category]  	New Feature
# [Description]  	TCG (TPM20)
# 
# 2     3/29/11 2:47p Fredericko
# 
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
# Name:		TcgDxe.MAK
#
# Description:	Make file for the tcgdxe component
#
#<AMI_FHDR_END>
#**********************************************************************
all : TcgBinaries

TcgBinaries : $(BUILD_DIR)\LEGX16.ffs $(BUILD_DIR)\MPTPM.ffs $(BUILD_DIR)\TPM32BIN.ffs

$(BUILD_DIR)\MPTPM.ffs: $(TCG_BINS_DIR)\$(@B).bin
	$(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
		NAME=$(@B) \
		BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(TCG_BINS_DIR) \
		GUID=7D113AA9-6280-48c6-BACE-DFE7668E8307 \
		TYPE=EFI_FV_FILETYPE_FREEFORM \
		COMPRESS=1\
		BINFILE=$(TCG_BINS_DIR)\$(@B).bin FFSFILE=$@ 


#
# Create TPM32BIN.ffs
#
$(BUILD_DIR)\TPM32BIN.ffs : $(TCG_BINS_DIR)\$(@B).bin
	$(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
		NAME=$(@B) \
		BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(TCG_BINS_DIR) \
		GUID=0AA31BC6-3379-41e8-825A-53F82CC0F254 \
		TYPE=EFI_FV_FILETYPE_FREEFORM \
		COMPRESS=1\
		BINFILE=$(TCG_BINS_DIR)\$(@B).bin FFSFILE=$@ 

#
# Create LEG16.ffs
#
$(BUILD_DIR)\LEGX16.ffs : $(TCG_BINS_DIR)\$(@B).bin
	$(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
		NAME=$(@B) \
		BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(TCG_BINS_DIR) \
		GUID=142204E2-C7B1-4af9-A729-923758D96D03 \
		TYPE=EFI_FV_FILETYPE_FREEFORM \
		COMPRESS=1\
		BINFILE=$** FFSFILE=$@ 
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
