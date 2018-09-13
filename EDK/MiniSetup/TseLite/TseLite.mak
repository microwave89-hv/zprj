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
## $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/TseLite.mak $
##
## $Author: Arunsb $
##
## $Revision: 7 $
##
## $Date: 10/18/12 6:01a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/TseLite/TseLite.mak $
# 
# 7     10/18/12 6:01a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 8     10/10/12 12:38p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 6     4/23/10 6:05p Madhans
# 
# 5     2/19/10 1:04p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 5     2/19/10 8:18a Mallikarjunanv
## updated year in copyright message
## 
## 4     8/17/09 12:27p Presannar
## Removed include path to Core dir
## 
## 3     6/24/09 6:11p Madhans
## Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
## 
## 2     6/12/09 7:44p Presannar
## Initial implementation of coding standards for AMITSE2.0
## 
## 1     6/04/09 8:05p Madhans
# 
# 1     4/28/09 11:07p Madhans
# Tse 2.0 Code complete Checkin.
## 
## 3     4/28/09 9:40p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 2     2/05/09 10:15a Madhans
## Style Module created.
## 
## 1     12/18/08 7:59p Madhans
## Intial version of TSE Lite sources
## 
## 
##*****************************************************************##
##*****************************************************************##

# MAK file for the eModule:TseLite

TSELITE_INCLUDES = \
	-I $(UEFISRC_DIR) \
	-I $(TSE_STYLE_DIR) \
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

$(BUILD_DIR)\TseLiteLocal.lib : TseLiteLib

TseLiteLib : $(BUILD_DIR)\TseLite.mak TseLiteLibBin

$(BUILD_DIR)\TseLite.mak : $(TSELITESRC_DIR)\$(@B).cif $(TSELITESRC_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TSELITESRC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

TseLiteLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\TseLite.mak all\
		"MY_INCLUDES=$(TSELITE_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\TseLiteLocal.lib\
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
