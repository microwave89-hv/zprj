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
## $Archive: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/PasswordEncode/PasswordEncodeBin.mak $
##
## $Author: Arunsb $
##
## $Revision: 3 $
##
## $Date: 5/08/14 4:46p $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/BIN/Modules/AMITSE2_0/AMITSE/PasswordEncode/PasswordEncodeBin.mak $
# 
# 3     5/08/14 4:46p Arunsb
# [TAG]  			EIP162197
# [Category]  	Improvement
# [Description]  	Password encode feature. Modify to encode using Hashing
# based on token.
# 
# 2     5/02/14 10:42p Arunsb
# If TSE_HASH_PASSWORD is not supported then CRYPTOLIB wont be linked
# 
# 1     5/01/14 6:33p Arunsb
# [TAG]  		EIP162197
# [Category]  	Improvement
# [Description]  	Password Encode Feature using hash algorithm
# [Files]  		PasswordEncode.c, PasswordEncode.h, PasswordEncodeBin.cif,
# PasswordEncodeBin.mak and PasswordEncodeBin.sdl
# 
## Intial version of TSE PassworEncodeBin file sources
##*****************************************************************##

# MAK file for the eModule:PasswordEncode

!if "$(TSE_HASH_PASSWORD)" == "1"
CRYPTOLIB_TEMP = $(CRYPTOLIB)
!else
CRYPTOLIB_TEMP =
!endif


PASSWORDENCODE_INCLUDES = \
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
	-I $(TSE_PWD_ENCODE_DIR) \
!if "$(UEFI_SOURCES_SUPPORT)" == "1"
	-I $(UEFISRC_DIR) \
!endif


All: $(BUILD_DIR)\$(TSE_PWD_ENCODE_DIR)\PasswordEncodeBin.obj

$(BUILD_DIR)\$(TSE_PWD_ENCODE_DIR)\PasswordEncodeBin.obj: $(PROJECT_DIR)\$(TSE_PWD_ENCODE_DIR)\PasswordEncode.c
	if not exist $(BUILD_DIR)\$(TSE_PWD_ENCODE_DIR) mkdir $(BUILD_DIR)\$(TSE_PWD_ENCODE_DIR)
	$(CC) $(CFLAGS) $(PASSWORDENCODE_INCLUDES) /DTSE_FOR_APTIO_4_50 /Fo$(BUILD_DIR)\$(TSE_PWD_ENCODE_DIR)\PasswordEncodeBin.obj  $(PROJECT_DIR)\$(TSE_PWD_ENCODE_DIR)\PasswordEncode.c

# MAK file for the eModule:PasswordEncodeBin
AMITSEBin: $(BUILD_DIR)\$(TSE_PWD_ENCODE_DIR)\PasswordEncodeBin.obj $(CRYPTOLIB_TEMP) 

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
