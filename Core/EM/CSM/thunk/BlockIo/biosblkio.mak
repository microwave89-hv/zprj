#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#************************************************************************//
# $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/biosblkio.mak 3     1/12/10 11:50a Olegi $
#
# $Revision: 3 $
#
# $Date: 1/12/10 11:50a $
#************************************************************************//
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/INT13/biosblkio.mak $
# 
# 3     1/12/10 11:50a Olegi
# Copyright message updated.
# 
# 2     12/02/05 11:44a Felixp
# 
# 1     2/15/05 11:00a Olegi
# Initial VSS check-in.
# 
#
#************************************************************************//
all : CsmBlockIo 

CsmBlockIo : $(BUILD_DIR)\biosblkio.mak CsmBlockIoBin

$(BUILD_DIR)\biosblkio.mak : $(CSMBLOCKIO_DIR)\int13thunk.cif $(CSMBLOCKIO_DIR)\biosblkio.mak $(BUILD_RULES)
	$(CIF2MAK) $(CSMBLOCKIO_DIR)\int13thunk.cif $(CIF2MAK_DEFAULTS)

CsmBlockIoBin: $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\biosblkio.mak all\
		GUID=25ACF158-DD61-4e64-9A49-55851E9A26C7\
		ENTRY_POINT=CsmBlockIoEntryPoint \
		TYPE=BS_DRIVER \
		COMPRESS=1\

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************