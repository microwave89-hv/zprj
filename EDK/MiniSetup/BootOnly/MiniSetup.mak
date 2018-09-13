##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 2004, American Megatrends, Inc.        **##
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
## $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/MiniSetup.mak $
##
## $Author: Arunsb $
##
## $Revision: 9 $
##
## $Date: 10/18/12 5:58a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/BootOnly/MiniSetup.mak $
# 
# 9     10/18/12 5:58a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 12    10/10/12 12:36p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 8     4/02/10 6:13p Madhans
# EIP 37036 : To make TSE 2.01 Binary module to work with older Cores
# 
# 7     2/26/10 8:53p Madhans
# For TSE 2.01.1024. refer changelog.log for file checkin history .
## 
## 8     2/26/10 1:29p Madhans
## Bootonly source module need AMITSEStrTokens.h
## 
## 7     2/19/10 8:14a Mallikarjunanv
## updated year in copyright message
## 
## 6     2/17/10 1:02p Madhans
## minisetupstr.uni removed and Strings token are refered from
## AMITSEStrTokens.h
## 
## 5     10/28/09 5:37p Madhans
## 
## 4     8/17/09 12:22p Presannar
## Removed include directory Core
## 
## 3     6/24/09 6:09p Madhans
## Made TSE_USE_EDK_LIBRARY=OFF to not to refer EDK module.
## 
## 2     6/12/09 7:41p Presannar
## Initial implementation of coding standards
## 
## 1     6/04/09 8:05p Madhans
# 
# 1     4/28/09 11:12p Madhans
# Tse 2.0 Code complete Checkin.
## 
## 5     4/28/09 9:39p Madhans
## Tse 2.0 Code complete Checkin.
## 
## 4     3/31/09 3:58p Madhans
## 
## 3     2/05/09 10:15a Madhans
## Style Module created.
## 
## 2     1/30/09 6:06p Madhans
## Function headers added. 
## 
## 1     12/18/08 7:58p Madhans
## Intial version of TSE Lite sources
##*****************************************************************##

# MAK file for the eModule:MiniSetup

MINISETUP_INCLUDES = \
	-I $(TSESRC_DIR)\AMILogo \
	-I $(TSESRC_DIR) \
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \

!if "$(TseLite_SUPPORT)" == "1"
MINISETUP_INCLUDES = 	-I $(UEFISRC_DIR) $(MINISETUP_INCLUDES) -I $(TSELITESRC_DIR) -I $(TSE_STYLE_DIR)
!endif


$(BUILD_DIR)\MiniSetupLocal.lib : MiniSetupLib

MiniSetupLib : $(BUILD_DIR)\MiniSetup.mak MiniSetupLibBin

$(BUILD_DIR)\MiniSetup.mak : $(TSESRC_DIR)\$(@B).cif $(TSESRC_DIR)\$(@B).mak $(BUILD_RULES) $(BUILD_DIR)\AMITSEStrTokens.h
	$(CIF2MAK) $(TSESRC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

MiniSetupLibBin : 
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\MiniSetup.mak all\
		"MY_INCLUDES=$(MINISETUP_INCLUDES)"\
		TYPE=LIBRARY \
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\MiniSetupLocal.lib\
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
