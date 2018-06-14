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
## $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/AMITSEBoard.mak $
##
## $Author: Arunsb $
##
## $Revision: 6 $
##
## $Date: 10/18/12 6:34a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/AMITSEBoard/AMITSEBoard.mak $
# 
# 6     10/18/12 6:34a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 7     10/10/12 12:25p Arunsb
## Synched the source for v2.16.1232 backup with Aptio
# 
# 5     2/19/10 12:58p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 6     2/19/10 8:04a Mallikarjunanv
## updated year in copyright message
## 
## 5     1/29/10 5:15p Madhans
## Support to add strings from other modules without changing TSE sources.
## 
## 4     1/27/10 4:30a Mallikarjunanv
## Added support for AMITSESDB
## 
## 3     12/02/09 9:21a Mallikarjunanv
## Fixed ithe eip 30925 by updating with new Elink TSE_LIB_INCLUDES for
## board module 
## 
## 2     6/24/09 6:33p Madhans
## Coding Standards
# 
# 2     6/24/09 11:54a Blaines
# Coding standard update
# 
# 1     6/09/09 9:53a Madhans
# TSE 2.00.1201
## 
## 1     6/04/09 7:49p Madhans
## AMI TSE Advanced.
# 
# 1     4/28/09 11:03p Madhans
# Tse 2.0 Code complete Checkin.
## 
## 1     4/28/09 10:25p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 
##*****************************************************************##
##*****************************************************************##

# MAK file for the eModule:TseLite

TSE_BOARD_INCLUDES = $(TSE_LIB_INCLUDES)

$(BUILD_DIR)\AMITseBoard.lib : AMITseBoardLib

AMITseBoardLib : $(BUILD_DIR)\AMITseBoard.mak AMITseBoardBin 

$(BUILD_DIR)\AMITseBoard.mak : $(TSE_BOARD_DIR)\$(@B).cif $(TSE_BOARD_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TSE_BOARD_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AMITseBoardBin : 
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AMITseBoard.mak all\
		"MY_INCLUDES=$(TSE_BOARD_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\AMITseBoard.lib\
		"CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50"

AMITSESDB : TseBoardSDB

TseBoardSDB : $(BUILD_DIR)\AMITseBoard.mak
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AMITseBoard.mak all\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		"STRING_CONSUMERS=$(TSE_BOARD_DIR)\OemTokens.c"\
		TYPE=SDB NAME=AMITseBoard
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

