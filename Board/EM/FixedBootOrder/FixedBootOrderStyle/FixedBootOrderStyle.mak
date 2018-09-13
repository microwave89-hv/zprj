#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Archive: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrderStyle.mak $
#
# $Author: Easonchen $
#
# $Revision: 1 $
#
# $Date: 6/28/12 11:42a $
#
#*****************************************************************
#*****************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Modules/Template/FixedBootOrder Demo/Board/em/FixedBootOrder/FixedBootOrderStyle.mak $
# 
# 1     6/28/12 11:42a Easonchen
# Make a new FixedBootOrder module by utilizing 4.6.4.1 BDS
# functionality.
# 
#
#*****************************************************************
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	FixedBootOrderStyle.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

OEM_BOOTORDDER_STYLE_INCLUDES = \
    -I $(TSE_STYLE_DIR) \
!if "$(UEFI_SOURCES_SUPPORT)" == "1"
    -I $(UEFISRC_DIR) \
!endif
	-I $(TSELITESRC_DIR) \
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
	-I $(PROJECT_DIR)\$(FixedBootOrder_DIR)\
	-I $(BUILD_DIR) \

$(BUILD_DIR)\FixedBootOrderStyle.lib : FixedBootOrderStyleLib

FixedBootOrderStyleLib : $(BUILD_DIR)\FixedBootOrderStyle.mak FixedBootOrderStyleLibBin

$(BUILD_DIR)\FixedBootOrderStyle.mak : $(FixedBootOrderStyle_DIR)\$(@B).cif $(FixedBootOrderStyle_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(FixedBootOrderStyle_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

FixedBootOrderStyleLibBin : 
    $(MAKE) /$(MAKEFLAGS) $(TSE_DEFAULTS)\
        /f $(BUILD_DIR)\FixedBootOrderStyle.mak all\
        "MY_INCLUDES=$(OEM_BOOTORDDER_STYLE_INCLUDES)"\
        TYPE=LIBRARY \
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        LIBRARY_NAME=$(BUILD_DIR)\FixedBootOrderStyle.lib\
        "CFLAGS=$(CFLAGS) /DTSE_FOR_APTIO_4_50"



#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
