#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/CsmVideo/CsmVideo.mak 2     4/27/07 5:18p Olegi $
#
# $Revision: 2 $
#
# $Date: 4/27/07 5:18p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CSM/Generic/Thunk/CsmVideo/CsmVideo.mak $
# 
# 2     4/27/07 5:18p Olegi
# 
# 1     12/29/06 3:33p Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CsmVideo.mak
#
# Description:	CSM Video make file
#
#<AMI_FHDR_END>
#**********************************************************************
all : CsmVideo

CsmVideo : $(BUILD_DIR)\CsmVideo.mak CsmVideoBin

$(BUILD_DIR)\CsmVideo.mak : $(CsmVideo_DIR)\$(@B).cif $(CsmVideo_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CsmVideo_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CsmVideoBin : $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CsmVideo.mak all\
		GUID=29CF55F8-B675-4f5d-8F2F-B87A3ECFD063\
		ENTRY_POINT=BiosVideoDriverEntryPoint\
        EXT_HEADERS=$(BUILD_DIR)\Token.h\
		TYPE=BS_DRIVER \
		COMPRESS=1
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2006, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************