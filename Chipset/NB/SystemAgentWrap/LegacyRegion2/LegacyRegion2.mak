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

all : LegacyRegion2

LegacyRegion2 : $(BUILD_DIR)\LegacyRegion2.mak LegacyRegion2Bin

$(BUILD_DIR)\LegacyRegion2.mak : $(LEGACY_REGION2_DIR)\$(@B).cif $(LEGACY_REGION2_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(LEGACY_REGION2_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

LegacyRegion2Bin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\LegacyRegion2.mak all\
		GUID=FE6F8ACD-55A6-4c6b-B448-64E659DE94B3 \
		ENTRY_POINT=InitializeLegacyRegion2 \
		DEPEX1=$(LEGACY_REGION2_DIR)\LegacyRegion2.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		TYPE=BS_DRIVER \
		COMPRESS=1\

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
