##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**    C)Copyright 1985-2010, American Megatrends, Inc.         **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**  5555 Oakbrook Pkwy, Building 200,Norcross, Georgia 30093   **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
##*****************************************************************##
## $Archive: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Uefi21.mak $
##
## $Author: Arunsb $
##
## $Revision: 8 $
##
## $Date: 10/18/12 6:04a $
##
##*****************************************************************##
##*****************************************************************##
## Revision History
## ----------------
## $Log: /Alaska/SOURCE/Modules/AMITSE2_0/AMITSE/Uefi2.1/Uefi21.mak $
# 
# 8     10/18/12 6:04a Arunsb
# Updated for 2.16.1235 QA submission
## 
## 6     10/10/12 12:41p Arunsb
## Synched the source for v2.16.1232, backup with Aptio
# 
# 7     3/29/11 1:26p Madhans
# To remove /Od Option. It is not needed.
# 
# 6     10/14/10 5:07p Madhans
# 
# 5     4/23/10 6:12p Madhans
# 
# 4     4/16/10 5:13p Madhans
# Changes for Tse 2.02. Please see Changelog.log for more details.
# 
# 3     2/19/10 8:50p Madhans
## 
## 2     11/19/09 5:39p Presannar
## Include Path to CORE to be compatible with existing Implementation. To
## be removed in the Next release label
## 
## 1     7/24/09 6:54p Presannar
## 
## 3     4/24/09 7:54p Presannar
## TSE 2.0 UEFI 2.1 Code Complete
## 
## 2     3/31/09 4:15p Madhans
## UEFI Wrapper improvments.
## 
## 1     1/09/09 2:38p Presannar
## UEFI 2.1 Hii Related Code - Initial Drop
## 
## 
##*****************************************************************##
##*************************************************************************
##<AMI_FHDR_START>
##
## Name:  Uefi21.mak
##
## Description:
##
##<AMI_FHDR_END>
##*************************************************************************

# MAK file for the eModule:UEFI2.1

Uefi21_INCLUDES = \
	-I $(TSESRC_DIR) \
	-I $(TSE_STYLE_DIR) \
	-I $(TSESRC_DIR)\AMILOGO \
	-I $(TSELITESRC_DIR) \
	-I $(UEFISRC_DIR) \
	-I $(TSEBIN_DIR) \
	-I $(TSEBIN_DIR)\Inc \
!if "$(TSE_BOARD_SOURCE_SUPPORT)" == "1"
	-I $(TSE_BOARD_DIR)\
!endif
	-I $(PROJECT_DIR)\Include\Protocol \
	-I $(PROJECT_DIR) \
	-I $(PROJECT_DIR)\Include \
	-I $(BUILD_DIR) \
!if "$(TSE_USE_EDK_LIBRARY)" == "1"
	-I $(EDK_SOURCE)\Foundation\Library\Dxe\UefiEfiIfrSupportLib \
!endif
!if "$(TSE_USE_EDK_LIBRARY)" != "1"
	-I $(PROJECT_DIR)\Core \
!endif

!if "$(TSE_USE_EDK_LIBRARY)" == "1"
TSE_DEFAULTS = $(EDK_DEFAULTS)
!else
TSE_DEFAULTS = $(BUILD_DEFAULTS)
!endif

$(BUILD_DIR)\Uefi21Local.lib : Uefi21Lib

Uefi21Lib : $(BUILD_DIR)\Uefi21.mak Uefi21LibBin

$(BUILD_DIR)\Uefi21.mak : $(UEFISRC_DIR)\$(@B).cif $(UEFISRC_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(UEFISRC_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

Uefi21LibBin : 
	$(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
		/f $(BUILD_DIR)\Uefi21.mak all\
		"MY_INCLUDES=$(Uefi21_INCLUDES)"\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR)"\
		TYPE=LIBRARY \
        	"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		LIBRARY_NAME=$(BUILD_DIR)\Uefi21Local.lib\
		"CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50"

##*****************************************************************##
##*****************************************************************##
##**                                                             **##
##**    C)Copyright 1985-2010, American Megatrends, Inc.         **##
##**                                                             **##
##**                     All Rights Reserved.                    **##
##**                                                             **##
##**           6145-F Northbelt Pkwy, Norcross, GA 30071         **##
##**                                                             **##
##**                     Phone (770)-246-8600                    **##
##**                                                             **##
##*****************************************************************##
##*****************************************************************##
