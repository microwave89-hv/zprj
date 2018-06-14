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
## $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseAdvanced/TseAdvancedBin.mak $
##
## $Author: Arunsb $
##
## $Revision: 7 $
##
## $Date: 10/18/12 5:45a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/TseAdvanced/TseAdvancedBin.mak $
# 
# 7     10/18/12 5:45a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 9     10/10/12 12:28p Arunsb
## Synched the source for v2.16.1232 backup with Aptio
# 
# 6     2/03/12 2:31a Arunsb
# [TAG]  		EIP74967
# [Category]  	Improvement
# [Description]  	Publishing add/del boot/driver option from TSE to
# setup.
# [Files]  		TseAdvancedBin.sdl, TseAdvancedBin.mak, TseAdvancedBin.cif,
# AddDelBootDrvOpts.sd and AddDelBootDrvOpts.uni
# 
# 5     2/26/10 8:46p Madhans
# For Tse 2.01.1204. Refer Changelog.log file change history
## 
## 7     2/23/10 8:33p Madhans
## For GTSE support.
## 
## 6     2/19/10 8:06a Mallikarjunanv
## updated year in copyright message
## 
## 5     2/15/10 10:06p Madhans
## -I flag not required
## 
## 4     2/05/10 6:03p Madhans
## Mouse.c is moved to Binary to contol TSE_MOUSE_SUPPORT from binary
## 
## 3     12/04/09 9:35a Mallikarjunanv
## EIP:31683 - To compatible with new WDK added $(LIBEXE) in place of LIB
## 
## 2     6/24/09 6:33p Madhans
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
# 1     5/06/09 8:14p Madhans
# Tse 2.0 Bin Module Initial Checkin.
## 
## 1     5/06/09 8:10p Madhans
## Tse 2.0 Binary Modules
## 
## 1     12/18/08 7:59p Madhans
## Intial version of TSE Lite sources
## 
## 
##*****************************************************************##
##*****************************************************************##

# MAK file for the eModule:TseLite


!if "$(TseLite_SUPPORT)" == "1"
$(BUILD_DIR)\FixedTseLiteLocal.lib : TseLiteLib TseFixedLiteLibBin
!else
$(BUILD_DIR)\FixedTseLiteLocal.lib : TseFixedLiteLibBin
!endif

TseFixedLiteLibBin : $(TSELITELIB)
	COPY /y $(TSELITELIB) $(BUILD_DIR)\FixedTseLiteLocal.lib
## Fix to EIP:31683 - To compatible with new WDK added $(LIBEXE) in place of LIB
	$(LIBEXE) /REMOVE:Build\EDK\MiniSetup\TseLite\TseLitehelper.obj $(BUILD_DIR)\FixedTseLiteLocal.lib

MINISETUP_INCLUDES = \
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \
	-I $(TSE_STYLE_DIR)

All: $(BUILD_DIR)\$(TSE_ADVANCED_DIR)\mouse.obj

$(BUILD_DIR)\$(TSE_ADVANCED_DIR)\mouse.obj: $(PROJECT_DIR)\$(TSE_ADVANCED_DIR)\mouse.c 
	if not exist $(BUILD_DIR)\$(TSE_ADVANCED_DIR) mkdir $(BUILD_DIR)\$(TSE_ADVANCED_DIR)
	$(CC) $(CFLAGS) $(MINISETUP_INCLUDES) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSE_ADVANCED_DIR)\mouse.obj  $(PROJECT_DIR)\$(TSE_ADVANCED_DIR)\mouse.c

# MAK file for the eModule:MiniSetupBin
AMITSEBin: $(BUILD_DIR)\$(TSE_ADVANCED_DIR)\mouse.obj 

#EIP74967 add/del boot option and driver option
SetupSdbs : $(BUILD_DIR)\AddDelBootDrvOpts.sdb

$(BUILD_DIR)\AddDelBootDrvOpts.sdb : $(TSE_ADVANCED_DIR)\AddDelBootDrvOpts.sd $(TSE_ADVANCED_DIR)\AddDelBootDrvOpts.uni
	$(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\AddDelBootDrvOpts.sdb $(TSE_ADVANCED_DIR)\AddDelBootDrvOpts.uni
	$(STRGATHER) -scan -db $(BUILD_DIR)\AddDelBootDrvOpts.sdb -od $(BUILD_DIR)\AddDelBootDrvOpts.sdb $(TSE_ADVANCED_DIR)\AddDelBootDrvOpts.sd

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
