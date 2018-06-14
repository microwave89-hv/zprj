##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 2011, American Megatrends, Inc.        **##
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
## $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Legacy/LegacyBin.mak $
##
## $Author: Arunsb $
##
## $Revision: 3 $
##
## $Date: 10/18/12 5:50a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/Legacy/LegacyBin.mak $
# 
# 3     10/18/12 5:50a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 3     10/10/12 12:33p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 2     6/29/11 12:46p Rajashakerg
# [TAG]  		EIP47086
# [Category]  	New Feature
# [Description]  	Right clicking from the Main page is not exiting from
# BIOS setup.
# 
# [Files]  		minisetup.h, Ezport\style.h,Ezport\EzportBin.sdl,
# Ezport\EzportBin.mak, Ezport\ezport.c, Ezport\EzportBin.cif,
# EzportPlus\style.h, EzportPlus\EzportPlusBin.sdl, EzportPlusBin.mak,
# EzportPlus\EzportPlusBin.cif, EzportPlus\ezportplus.c, Legacy\style.h,
# Legacy\EzportPlusBin.sdl, Legacy\LegacyBin.mak, Legacy\LegacyBin.cif,
# Legacy\legacy.c, TseLiteBin.sdl, TseLite.cif, Memo.c, frame.c,
# application.h, application.c, commonoem.h, CommonHelper.c
# 
# 1     3/28/11 11:49p Madhans
# [TAG]  		EIP54968
# [Category]  	Improvement
# [Description]  	To Support different style modules in TSE generically
# [Files]  		Ezport module updated. EzportPlus and Legacy Styles Modules
# added.
## 
## 1     9/16/10 6:37p Blaines
## 
## 1     9/16/10 6:32p Blaines
## 
## 5     2/19/10 8:10a Mallikarjunanv
## updated year in copyright message
## 
## 4     2/12/10 7:18a Mallikarjunanv
## added dependency to add BOARD Module path
## 
## 3     12/02/09 9:25a Mallikarjunanv
## Fixed ithe eip 30917 by Updated the mak file to include the TseOem.h
## in HotkeyBin.c. 
## 
## 2     6/24/09 6:33p Madhans
## Coding Standards
# 
# 2     6/24/09 11:55a Blaines
# Coding standard update
# 
# 1     6/09/09 9:53a Madhans
# TSE 2.00.1201
## 
## 1     6/04/09 7:49p Madhans
## AMI TSE Advanced.
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

all : $(BUILD_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.obj \
      $(BUILD_DIR)\$(TSE_STYLE_DIR)\HotclickBin.obj

$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.obj: $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.c $(TSE_STYLE_DIR)\HotkeyBin.h  HotKeyElinkList
	if not exist $(BUILD_DIR)\$(TSE_STYLE_DIR) mkdir $(BUILD_DIR)\$(TSE_STYLE_DIR)
!IF	"$(TSE_BOARD_MODULE_SUPPORT)"=="1"
	$(CC) $(CFLAGS) -I $(BUILD_DIR) -I $(TSE_BOARD_DIR) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.obj  $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.c
!ELSE
	$(CC) $(CFLAGS) -I $(BUILD_DIR) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.obj  $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.c
!ENDIF

$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotclickBin.obj: $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotclickBin.c $(TSE_STYLE_DIR)\HotclickBin.h  HotClickElinkList
	if not exist $(BUILD_DIR)\$(TSE_STYLE_DIR) mkdir $(BUILD_DIR)\$(TSE_STYLE_DIR)
!IF	"$(TSE_BOARD_MODULE_SUPPORT)"=="1"
	$(CC) $(CFLAGS) -I $(BUILD_DIR) -I $(TSE_BOARD_DIR) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotclickBin.obj  $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotclickBin.c
!ELSE
	$(CC) $(CFLAGS) -I $(BUILD_DIR) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotclickBin.obj  $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotclickBin.c
!ENDIF

HotKeyElinkList:
	echo #define HOTKEY_LIST $(HOTKEY_LIST) > $(BUILD_DIR)\HotKeyElinks.h

#	cl $(CFLAGS) /DTSE_FOR_APTIO_4_50 -I $(BUILD_DIR) /Fo$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.obj $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.c

# MAK file for the eModule:LegacyBin
AMITSEBin: $(BUILD_DIR)\$(TSE_STYLE_DIR)\HotkeyBin.obj 

HotClickElinkList:
	echo #define HOTCLICK_LIST $(HOTCLICK_LIST) > $(BUILD_DIR)\HotClickElinks.h
#	cl $(CFLAGS) /DTSE_FOR_APTIO_4_50 -I $(BUILD_DIR) /Fo$(BUILD_DIR)\$(TSE_STYLE_DIR)\HotclickBin.obj $(PROJECT_DIR)\$(TSE_STYLE_DIR)\HotclickBin.c

# MAK file for the eModule:LegacyBin
AMITSEBin: $(BUILD_DIR)\$(TSE_STYLE_DIR)\HotclickBin.obj 

$(BUILD_DIR)\LegacyBin.mak : $(TSE_STYLE_DIR)\$(@B).cif $(TSE_STYLE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(TSE_STYLE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AMITSESDB : LegacySDB

LegacySDB : $(BUILD_DIR)\LegacyBin.mak
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\LegacyBin.mak all\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		"STRING_CONSUMERS=$(TSE_STYLE_DIR)\StyleTokens.c"\
		TYPE=SDB NAME=LegacyBin 

##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**         (C)Copyright 2011, American Megatrends, Inc.        **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
