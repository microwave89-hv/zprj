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
## $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseOEM/TseOEM.mak $
##
## $Author: Arunsb $
##
## $Revision: 5 $
##
## $Date: 10/18/12 6:34a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseOEM/TseOEM.mak $
# 
# 5     10/18/12 6:34a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 5     10/10/12 12:31p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 4     2/19/10 12:59p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 4     2/19/10 8:09a Mallikarjunanv
## updated year in copyright message
## 
## 3     6/24/09 6:33p Madhans
## Coding Standards.
# 
# 2     6/24/09 11:56a Blaines
# Coding standard update
# 
# 1     6/09/09 9:53a Madhans
# TSE 2.00.1201
## 
## 1     6/04/09 7:49p Madhans
## AMI TSE Advanced.
# 
# 1     4/28/09 11:08p Madhans
# Tse 2.0 Code complete Checkin.
## 
## 1     4/28/09 10:27p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 
##*****************************************************************##
##*****************************************************************##

# MAK file for the eModule:TseOEM

TSEOEM_INCLUDES = \
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
	-I $(BUILD_DIR)

EDK : TseOEMLib

$(BUILD_DIR)\TseOEMLocal.lib : TseOEMLib

TseOEMLib : $(BUILD_DIR)\TseOEM.mak TseOEMLibBin

$(BUILD_DIR)\TseOEM.mak : $(TSEOEMSRC_DIR)\$(@B).cif $(TSEOEMSRC_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TSEOEMSRC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TseOEMLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\TseOEM.mak all\
		"MY_INCLUDES=$(TSEOEM_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\TseOEMLocal.lib\
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
