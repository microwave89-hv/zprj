#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/AutoUpdate.mak 1     8/30/11 8:17a Klzhan $
#
# $Revision: 1 $
#
# $Date: 8/30/11 8:17a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/AutoUpdate.mak $
# 
# 1     8/30/11 8:17a Klzhan
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	AutoUpdate.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : MEAUTOUPD 

SetupData : MEAUTOUPD

MEAUTOUPD : $(BUILD_DIR)\AutoUpdate.mak MEAUTOUPDBin $(BUILD_DIR)\MERegion.ffs

$(BUILD_DIR)\AutoUpdate.mak : $(MEAUPD_DIR)\$(@B).cif $(MEAUPD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MEAUPD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MEUDMSG_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)\

MEAUTOUPDBin : $(AMIDXELIB) $(FLASHLIB) $(CSP_MEUDLIB) $(BUILD_DIR)\MELib.lib
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AutoUpdate.mak all\
		GUID=39d1830f-259b-4d7e-b1a3-074135b4c934\
		ENTRY_POINT=AUTOUPDEntry\
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=BS_DRIVER \
		COMPRESS=1

$(BUILD_DIR)\MERegion.ffs: $(ME_UPDATE_BINARY_FILE)
	$(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
	GUID=feaaa7a6-cb95-4670-b499-877fa6ca6bae \
	TYPE=EFI_FV_FILETYPE_FREEFORM  \
	BINFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************