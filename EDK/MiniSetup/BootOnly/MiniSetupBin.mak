#//*****************************************************************//
#//*****************************************************************//
#//*****************************************************************//
#//**                                                             **//
#//**         (C)Copyright 2010, American Megatrends, Inc.        **//
#//**                                                             **//
#//**                     All Rights Reserved.                    **//
#//**                                                             **//
#//**   5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093  **//
#//**                                                             **//
#//**                     Phone (770)-246-8600                    **//
#//**                                                             **//
#//*****************************************************************//
#//*****************************************************************//
##*****************************************************************##
## $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/BootOnly/MiniSetupBin.mak $
##
## $Author: Arunsb $
##
## $Revision: 5 $
##
## $Date: 10/18/12 5:46a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/BootOnly/MiniSetupBin.mak $
# 
# 5     10/18/12 5:46a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 10    10/10/12 12:29p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 4     6/30/11 4:07a Arunsb
# [TAG]           EIP57661
# [Category]      New Feature
# [Description]   Boot manager algorithm for interaction with Driver
# Health protocol.
#                 Include directories added.
# [Files]         amitse.cif, amitse.sdl, faketokens.c, amitsestr.uni,
#                 commonhelper.c, uefisetup.ini, tsedrvhealth.h,
# amivfr.h, minisetupbin.mak,
#                 hiistring21.c, hiistring20.c, tseadvanced.c, special.c,
# special.h, boot.h, minisetup.h,
#                 uefi20wapper.c, formbrowser2.c, hii.c, parse.c and
# uefi21wapper.c.
# 
# 3     2/19/10 2:28p Madhans
# Build issue fix
# 
# 2     2/19/10 12:58p Madhans
# Updated for TSE 2.01. Refer Changelog.log for File change history.
## 
## 5     2/19/10 12:08p Madhans
## To depend on EFI_SPEC SDl token
## 
## 4     2/19/10 8:07a Mallikarjunanv
## updated year in copyright message
## 
## 3     2/17/10 7:02p Madhans
## If String not found in current lang Search in Default Lang. If not
## search in english.
## 
## 2     2/15/10 10:04p Madhans
## 
## 1     7/31/09 4:58p Presannar
## Initial Draft. Builkds HiiString depending upon UEFI HII specification
## version
## 
##*****************************************************************##
##*****************************************************************##


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
    -I $(TSESRC_DIR)\AMILOGO \
    -I $(TSE_STYLE_DIR) \
    -I $(TSELITESRC_DIR) \
!if "$(UEFI_SOURCES_SUPPORT)" == "1"
	-I $(UEFISRC_DIR) \
!endif

All: $(BUILD_DIR)\$(TSESRC_DIR)\MiniSetupBin.obj

$(BUILD_DIR)\$(TSESRC_DIR)\MiniSetupBin.obj: $(PROJECT_DIR)\$(TSESRC_DIR)\HiiString20.c $(TSESRC_DIR)\HiiString21.c
	if not exist $(BUILD_DIR)\$(TSESRC_DIR) mkdir $(BUILD_DIR)\$(TSESRC_DIR)
!IF $(EFI_SPECIFICATION_VERSION) > 0x20000
	$(CC) $(CFLAGS) $(MINISETUP_INCLUDES) /DDEFAULT_LANGUAGE_CODE="$(DEFAULT_LANGUAGE)" /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSESRC_DIR)\MiniSetupBin.obj  $(PROJECT_DIR)\$(TSESRC_DIR)\HiiString21.c
!ELSE
	$(CC) $(CFLAGS) $(MINISETUP_INCLUDES) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSESRC_DIR)\MiniSetupBin.obj  $(PROJECT_DIR)\$(TSESRC_DIR)\HiiString20.c
!ENDIF

# MAK file for the eModule:MiniSetupBin
AMITSEBin: $(BUILD_DIR)\$(TSESRC_DIR)\MiniSetupBin.obj 
