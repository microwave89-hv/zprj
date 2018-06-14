#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Core/Modules/FileSystem/FileSYstem.mak 4     12/09/05 11:08a Felixp $
#
# $Revision: 4 $
#
# $Date: 12/09/05 11:08a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Core/Modules/FileSystem/FileSYstem.mak $
# 
# 4     12/09/05 11:08a Felixp
# 
# 2     12/02/05 11:22a Felixp
# 
# 1     12/01/05 9:44a Felixp
# 
# 2     5/24/05 11:55a Felixp
# reference to EfiDebugLib removed
# 
# 1     4/26/05 6:05p Srinin
# 
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: SIMPLE_FILES_SYSTEM_MAK
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : FILE_SYSTEM

FILE_SYSTEM: $(BUILD_DIR)\FileSystem.mak FileSystemBin

$(BUILD_DIR)\FileSystem.mak : $(FILESYSTEM_DIR)\$(@B).cif $(FILESYSTEM_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FILESYSTEM_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

FileSystemBin: $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\FileSystem.mak all\
		GUID=93022F8C-1F09-47EF-BBB2-5814FF609DF5\
		ENTRY_POINT=SimpleFileSystemEntryPoint \
		TYPE=BS_DRIVER \
		COMPRESS=1\

#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2004, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             6145-F Northbelt Pkwy, Norcross, GA 30071            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

