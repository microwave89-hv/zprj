#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/MiscSubclass/MiscSubclass.mak 1     2/08/12 4:36a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 4:36a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/NorthBridge/Haswell/Intel SystemAgent NB Chipset/SystemAgentWrap/MiscSubclass/MiscSubclass.mak $
# 
# 1     2/08/12 4:36a Yurenlai
# Intel Haswell/NB eChipset initially releases.
#
#*************************************************************************

#---------------------------------------------------------------------------
#		Create SmBiosMemory DXE driver
#---------------------------------------------------------------------------
all: MiscSubclass MiscSubclassSDB MiscSubclassDxe

#MiscSubclass: $(BUILD_DIR)\MiscSubclass.mak MiscSubclassBin
MiscSubclass: $(BUILD_DIR)\MiscSubclass.mak

$(BUILD_DIR)\MiscSubclass.mak : $(MiscSubclass_DIR)\$(@B).cif $(MiscSubclass_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MiscSubclass_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MiscSubclass_OBJECTS = \
$(BUILD_DIR)\$(MiscSubclass_DIR)\MiscSubclass.obj \
$(BUILD_DIR)\MiscSubclassStrings.obj \
        
#MiscSubclassBin : $(PRINTLIB) $(EFIDRIVERLIB) $(EDKGUIDLIB) $(EFIPROTOCOLLIB) $(EFIIFRSUPPORTLIB)
#     	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
#		/f $(BUILD_DIR)\MiscSubclass.mak all\
#		GUID=EDA39402-F375-4496-92D3-83B43CB8A76A\
#    	"MY_INCLUDES=$(SmBiosMemory_INCLUDES)" \
#		ENTRY_POINT=MiscSubclass\
#		TYPE=BS_DRIVER\
#        "OBJECTS=$(MiscSubclass_OBJECTS)"\
#        DEPEX1=$(SmBiosMemory_DIR)\SmBiosMemory.dxs\
#		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
#		COMPRESS=1

#---------------------------------------------------------------------------
#		Create MiscSubclass Setup Screens
#---------------------------------------------------------------------------
MiscSubclassSDB : $(BUILD_DIR)\MiscSubclass.mak 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\MiscSubclass.mak all\
        TYPE=SDB NAME=MiscSubclass
    	$(STRGATHER) -dump -lang $(SUPPORTED_LANGUAGES: = -lang )\
        -db $(BUILD_DIR)\MiscSubclass.sdb\
        -bn MiscSubclass\
        -oh $(BUILD_DIR)\MiscSubclassStrings.h\
        -oc $(BUILD_DIR)\MiscSubclassStrings.c
        $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(BUILD_DIR)\MiscSubclassStrings.c

#----------------------------------------------------------------------------
#       Create MiscSubclass DXE Component
#----------------------------------------------------------------------------
MiscSubclassDxe : $(BUILD_DIR)\MiscSubclass.mak MiscSubclassDxeBin

MiscSubclass_DXE_OBJECTS = $(BUILD_DIR)\$(MiscSubclass_DIR)\MiscSubclassDxe.obj \
$(BUILD_DIR)\MiscSubclassStrings.obj \

MiscSubclassDxeBin : $(AMICSPLib) $(AMIDXELIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\MiscSubclass.mak all\
        NAME=MiscSubclassDxe\
        MAKEFILE=$(BUILD_DIR)\MiscSubclass.mak \
        OBJECTS="$(MiscSubclass_DXE_OBJECTS)" \
        GUID=16271FCA-55D9-4a33-93FC-5A3EB128DE21 \
        ENTRY_POINT=MiscSubclassDxe_Init \
        "CFLAGS=$(CFLAGS) /I$(NB_CHIPSET_DIR) /I$(NB_BOARD_DIR) /I$(SB_CHIPSET_DIR) /I$(SB_BOARD_DIR)"\
        "EXT_HEADERS=$(BUILD_DIR)\token.h"\
        TYPE=BS_DRIVER \
        DEPEX1=$(MiscSubclass_DIR)\MiscSubclassDxe.dxs DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        COMPRESS=1

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************