#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Board/CMOS Messages/CmosMessages.mak 2     6/15/10 2:22p Michaela $
#
# $Revision: 2 $
#
# $Date: 6/15/10 2:22p $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/CMOS Manager/CMOS Board/CMOS Messages/CmosMessages.mak $
# 
# 2     6/15/10 2:22p Michaela
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CmosMessages.mak
#
# Description: Make file for the CmosMessages.obj
#
#<AMI_FHDR_END>
#**********************************************************************

AMITSEBin :  $(BUILD_DIR)\CmosMessages.obj

$(BUILD_DIR)\CmosMessages.obj : $(PROJECT_DIR)\$(CMOS_MANAGER_DIR)\CmosMessages.c
	$(CC) $(CFLAGS) -I $(TSEBIN_DIR)\Inc -I $(TSEBIN_DIR) -ICore /Fo$(BUILD_DIR)\ $(PROJECT_DIR)\$(CMOS_MANAGER_DIR)\CmosMessages.c

AMITSESDB : CmosMessagesSDB
CMOS_MANAGER_MAK_DEPS = \
    $(CMOS_MANAGER_DIR)\CmosManagerMessages.cif \
    $(CMOS_MANAGER_DIR)\CmosMessages.mak

$(BUILD_DIR)\CmosMessages.mak : $(CMOS_MANAGER_MAK_DEPS) $(BUILD_RULES)
	$(CIF2MAK) $(CMOS_MANAGER_DIR)\CmosManagerMessages.cif $(CIF2MAK_DEFAULTS)

CmosMessagesSDB : $(BUILD_DIR)\CmosMessages.mak
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\CmosMessages.mak all\
		"UNI_INCLUDE_PATH=$(TSEBIN_DIR) $(TSE_UNI_INCLUDE_PATH)"\
		"STRING_CONSUMERS=$(CMOS_MANAGER_DIR)\CmosMessages.c"\
		TYPE=SDB NAME=CmosMessages

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
