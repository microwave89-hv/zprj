##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 2010, American Megatrends, Inc.        **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
## $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/TseAdvanced.mak $
##
## $Author: Arunsb $
##
## $Revision: 14 $
##
## $Date: 10/18/12 5:53a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseAdvanced/TseAdvanced.mak $
# 
# 14    10/18/12 5:53a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 11    10/10/12 12:35p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 13    1/07/11 1:20a Mallikarjunanv
# [TAG]  		EIP47260
# [Description]  	Updated the changes made in EIP:47260 proprely
# 
# 12    12/29/10 6:12a Mallikarjunanv
# [TAG]  		EIP 47260
# [Category]  	Improvement
# [Description]  	Updated TSE_NVRAM_SUPPORT with
# TSE_NVRAM_DEFAULTS_SUPPORT sdl token name
# [Files]  		TseAdvanced.mak, TseAdvanced.sdl, TseAdvanced.c
# 
# 10    9/21/10 6:28p Madhans
# [TAG]    	-
# [Category]	BUILD ISSUE FIX
# [Symptom]	Build issues When TSEsource listed before TSE binary module
# [RootCause]   ExitPageElinkList Is added TSEadvanced.mak
# [Solution]	remove the ExitPageElinkList from TSEadvanced.mak
# [Files] TSEadvanced.mak
# # 
# 
# 9     6/04/10 12:51p Blaines
# Add ExitPageElinkList
# 
# 8     4/23/10 6:04p Madhans
# to cleanup.
# 
# 7     4/16/10 5:13p Madhans
# Changes for Tse 2.02. Please see Changelog.log for more details.
# 
# 6     2/19/10 1:04p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 5     2/19/10 8:11a Mallikarjunanv
## updated year in copyright message
## 
## 4     8/17/09 12:23p Presannar
## Removed include path to core dir
## 
## 3     6/24/09 6:10p Madhans
## Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
## 
## 2     6/12/09 7:43p Presannar
## Initial implementation of coding standards for AMITSE2.0
## 
## 1     6/04/09 8:05p Madhans
# 
# 2     5/07/09 10:36a Madhans
# Changes after Bin module
# 
# 1     4/28/09 11:16p Madhans
# Tse 2.0 Code complete Checkin.
## 
## 1     4/28/09 10:27p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 1     12/18/08 7:59p Madhans
## Intial version of TSE Lite sources
## 
## 
##*****************************************************************##
##*****************************************************************##

# MAK file for the eModule:TseLite

TSE_ADVANCED_INCLUDES = \
	-I $(TSE_ADVANCED_DIR) \
	-I $(TSE_STYLE_DIR) \
!if "$(UEFI_SOURCES_SUPPORT)" == "1"
	-I $(UEFISRC_DIR) \
!endif
	-I $(TSESRC_DIR) \
	-I $(TSESRC_DIR)\AMILOGO \
	-I $(TSELITESRC_DIR) \
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \

$(BUILD_DIR)\TseAdvanced.lib : TseAdvancedLib

TseAdvancedLib : $(BUILD_DIR)\TseAdvanced.mak TseAdvancedLibBin

$(BUILD_DIR)\TseAdvanced.mak : $(TSE_ADVANCED_DIR)\$(@B).cif $(TSE_ADVANCED_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TSE_ADVANCED_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

!if "$(TSE_NVRAM_DEFAULTS_SUPPORT)" == "1"	##EIP-47260: to build TSE without NVRAM module support
TseAdvancedLibBin : $(BUILD_DIR)\NVRAMDXE.lib
!else
#if nvram_support is disabled, then OEM should provide their own variable library name here
TseAdvancedLibBin :
!endif
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\TseAdvanced.mak all\
		"MY_INCLUDES=$(TSE_ADVANCED_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\TseAdvanced.lib\
		"CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50"


##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 2010, American Megatrends, Inc.        **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
