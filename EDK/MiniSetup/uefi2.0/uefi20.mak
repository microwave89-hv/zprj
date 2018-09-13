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
## $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/uefi20.mak $
##
## $Author: Arunsb $
##
## $Revision: 8 $
##
## $Date: 10/18/12 6:00a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/uefi2.0/uefi20.mak $
# 
# 8     10/18/12 6:00a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 9     10/10/12 12:39p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 7     4/23/10 6:12p Madhans
# 
# 6     2/19/10 1:04p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 6     2/19/10 8:20a Mallikarjunanv
## updated year in copyright message
## 
## 5     10/28/09 5:38p Madhans
## 
## 4     8/17/09 12:28p Presannar
## Removed Include Path to Core Dir
## 
## 3     6/24/09 6:11p Madhans
## Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
## 
## 2     6/12/09 7:44p Presannar
## Initial implementation of coding standards for AMITSE2.0
## 
## 1     6/04/09 8:05p Madhans
# 
# 1     4/28/09 11:09p Madhans
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

UEFI20_INCLUDES = \
	-I $(TSESRC_DIR) \
!if "$(TSE_STYLE_SOURCES_SUPPORT)" == "1"
	-I $(TSE_STYLE_DIR) \
!endif
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(TSESRC_DIR)\AMILOGO \
	-I $(TSELITESRC_DIR) \
	-I $(UEFISRC_DIR) \
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \

$(BUILD_DIR)\Uefi20Local.lib : Uefi20Lib

Uefi20Lib : $(BUILD_DIR)\Uefi20.mak Uefi20LibBin

$(BUILD_DIR)\Uefi20.mak : $(UEFISRC_DIR)\$(@B).cif $(UEFISRC_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(UEFISRC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

Uefi20LibBin : 
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\Uefi20.mak all\
		"MY_INCLUDES=$(UEFI20_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\Uefi20Local.lib\
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
