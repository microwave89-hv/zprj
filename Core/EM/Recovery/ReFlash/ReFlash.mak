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
# $Header: /Alaska/BIN/Core/Modules/Recovery/ReFlash.mak 15    5/22/12 5:10p Artems $
#
# $Revision: 15 $
#
# $Date: 5/22/12 5:10p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Core/Modules/Recovery/ReFlash.mak $
# 
# 15    5/22/12 5:10p Artems
# [TAG]  		EIP88314
# [Category]  	Improvement
# [Description]  	Recovery takes a long time for large flash size
# Rewrite reflash code to not give control back to TSE until finished
# reporting progress via DisplayProgress API of AMI Post manager
# [Files]  		Reflash.c Reflash.h ReflashWorker.c Reflash.mak Reflash.vfr
# Reflash.uni
# 
# 14    12/05/11 1:48p Artems
# EIP 74623: Add capabilities similar to ones in SMIFlash module
# 
# 13    11/29/11 3:33p Artems
# Fixed build error when FtRecovery module is present but disabled
# 
# 12    11/12/11 6:47p Artems
# Added fault tolerant recovery support
# 
# 11    11/30/10 5:04p Felixp
# Bug fix: VfrCompile build error when ReflashFunctions eLink list
# contains more than one function.
# 
# 10    11/17/10 5:27p Felixp
# $(BUILD_DIR)\ReFlash.mak dependency is updated.
# 
# 9     11/17/10 2:52p Felixp
# Enhencement (EIP 36355):
# The Reflash component is updated to be extensible with external
# eModules. 
# The eModules can contribute content for the Recovery setup page, 
# and provide callback function that will be periodically called 
# once BIOS update is completed.The external eModules can be used 
# to implement update of non-standard firmware components. 
# For example, update of the non-shared EC firmware.
# 
# 8     10/01/10 2:14p Felixp
# Previous changes related to descrete EC firmware update are rolled back
# for the Core labeling.
# 
# 6     2/23/10 9:20p Felixp
# Support of the ReFlash String Override via REFLASH_SDBS eLink (EIP
# 32696).
# 
# 5     7/09/09 5:59p Oleksiyy
# Files clean-up, some headers added
# 
# 4     12/29/06 2:58p Felixp
# RecoveryDxeLib removed. Functionality moved to Flash.lib
# 
# 3     8/24/06 9:19a Felixp
# x64 Support
# 
# 1     11/08/05 4:04a Felixp
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	ReFlash.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : ReFlash

SetupData : ReFlash

ReFlash : $(BUILD_DIR)\ReFlash.mak ReFlashBin

$(BUILD_DIR)\ReFlash.mak : $(ReFlash_DIR)\$(@B).cif $(ReFlash_DIR)\$(@B).mak $(BUILD_RULES) $(REFLASH_CIFS) $(BUILD_DIR)\token.h
	$(CIF2MAK) $(ReFlash_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS) $(REFLASH_CIFS)

REFLASH_LISTS = \
/D\"REFLASH_FUNCTION_LIST=$(ReflashFunctions)\"\
/D\"OEM_BEFORE_FLASH_UPDATE_CALLBACK_LIST=$(OemBeforeFlashUpdateList)\"\
/D\"OEM_AFTER_FLASH_UPDATE_CALLBACK_LIST=$(OemAfterFlashUpdateList)\"

ReFlashBin : $(AMIDXELIB) $(FLASHLIB)
	type << >$(BUILD_DIR)\ReflashDefinitions.h
!IF "$(REFLASH_DEFINITIONS)"!=""
#include<$(REFLASH_DEFINITIONS: =>^
#include<)>
!ENDIF
<<
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\ReFlash.mak all\
		GUID=70e1a818-0be1-4449-bfd4-9ef68c7f02a8\
		ENTRY_POINT=ReFlashEntry\
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=BS_DRIVER \
        MY_INCLUDES=/I$(ReFlash_DIR)\
        "CFLAGS=$(CFLAGS) $(REFLASH_LISTS)"\
		COMPRESS=1 HAS_RESOURCES=1\
!IF "$(REFLASH_SDBS: =)"!=""
        "MY_SDBS=-db $(REFLASH_SDBS: = -db )"\
!ENDIF

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