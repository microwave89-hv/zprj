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

all : SmBusMemoryDown

SmBusMemoryDown : $(BUILD_DIR)\SmBusMemoryDown.mak SmBusMemoryDownBin

$(BUILD_DIR)\SmBusMemoryDown.mak : $(SMBUS_MEMORYDOWN_DIR)\$(@B).cif $(SMBUS_MEMORYDOWN_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(SMBUS_MEMORYDOWN_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmBusMemoryDownBin : $(AMIDXELIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SmBusMemoryDown.mak all\
		GUID=F6A59595-BB9F-415b-A7F3-DC7C09387BE6 \
		ENTRY_POINT=InitSmBusMemoryDown \
		DEPEX1=$(SMBUS_MEMORYDOWN_DIR)\SmBusMemoryDown.dxs\
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
