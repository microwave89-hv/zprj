##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 1985-2010, American Megatrends, Inc.   **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**           5555 Oakbrook Pkwy   , Norcross, GA 30071         **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
## $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/Ezport.mak $
##
## $Author: Arunsb $
##
## $Revision: 6 $
##
## $Date: 10/18/12 6:05a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Ezport/Ezport.mak $
# 
# 6     10/18/12 6:05a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 7     10/10/12 12:42p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 5     2/19/10 1:02p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 5     2/19/10 8:15a Mallikarjunanv
## updated year in copyright message
## 
## 4     8/17/09 12:23p Presannar
## Removed Include path to Core directory
## 
## 3     6/24/09 6:10p Madhans
## Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
## 
## 2     6/12/09 2:36p Blaines
## Update coding standard
## 
## 1     6/04/09 8:05p Madhans
# 
# 1     4/28/09 11:15p Madhans
# Tse 2.0 Code complete Checkin.
## 
## 3     4/28/09 9:39p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 2     4/24/09 9:35p Blaines
## 
## 1     12/18/08 7:59p Madhans
## Intial version of TSE Lite sources
## 
## 
##*****************************************************************##
##*****************************************************************##

# MAK file for the eModule:TseLite

TSE_STYLE_INCLUDES = \
	-I $(TSE_STYLE_DIR) \
!if "$(UEFI_SOURCES_SUPPORT)" == "1"
	-I $(UEFISRC_DIR) \
!endif
	-I $(TSESRC_DIR) \
	-I $(TSESRC_DIR)\AMILOGO \
	-I $(TSELITESRC_DIR) \
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \

$(BUILD_DIR)\TseStyle.lib : TseStyleLib

TseStyleLib : $(BUILD_DIR)\Ezport.mak TseStyleLibBin

$(BUILD_DIR)\Ezport.mak : $(TSE_STYLE_DIR)\$(@B).cif $(TSE_STYLE_DIR)\$(@B).mak $(BUILD_RULES) 
	$(CIF2MAK) $(TSE_STYLE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

TseStyleLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\Ezport.mak all\
		"MY_INCLUDES=$(TSE_STYLE_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\TseStyle.lib\
		"CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50"

##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 1985-2010, American Megatrends, Inc.   **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**           5555 Oakbrook Pkwy   , Norcross, GA 30071         **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
