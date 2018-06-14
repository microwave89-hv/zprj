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

all : IntelSaGopDriver IgbGOPDriver

IntelSaGopDriver : $(BUILD_DIR)\IntelSaGopDriver.mak IntelSaGopDriverBin  

IgbGOPDriver: $(BUILD_DIR)\BmpDummyName.ffs $(BUILD_DIR)\IntelGopDriver.ffs


$(BUILD_DIR)\IntelSaGopDriver.mak : $(IntelSaGopDriver_DIR)\$(@B).cif $(IntelSaGopDriver_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IntelSaGopDriver_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IntelSaGopDriver_INCLUDES=\
        $(PLATFORM_INFO_INCLUDES)\
        $(DxeKscLib_INCLUDES)\
        $(INTEL_MCH_INCLUDES)\

IntelSaGopDriverBin :  $(AMIDXELIB) $(DxeKscLib_LIB) $(AMICSPLib)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\IntelSaGopDriver.mak all\
		GUID=5c266089-e103-4d43-9ab5-12d7095be2af\
        "MY_INCLUDES=$(IntelSaGopDriver_INCLUDES)"\
		ENTRY_POINT=IntelSaGopPolicyEntryPoint\
        DEPEX1=$(IntelSaGopDriver_DIR)\IntelSaGopDriver.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		TYPE=BS_DRIVER\
		COMPRESS=1

$(BUILD_DIR)\BmpDummyName.ffs : $(OEM_INTEL_GOP_VBT_BIN_FILE)
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=878AC2CC-5343-46F2-B563-51F89DAF56BA \
	TYPE=EFI_FV_FILETYPE_RAW \
	RAWFILE=$** FFSFILE=$@ COMPRESS=0 NAME=BmpDummyName

$(BUILD_DIR)\IntelGopDriver.ffs : $(OEM_INTEL_GOP_EFI_DRIVER_FILE)
	$(MAKE) /f Core\FFS.mak \
	BUILD_DIR=$(BUILD_DIR) \
	GUID=5BBA83E6-F027-4ca7-BFD0-16358CC9E123 \
	TYPE=EFI_FV_FILETYPE_DRIVER \
	DEPEX1=$(IntelSaGopDriver_DIR)\IntelGopDriver.dxs\
	DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
	PEFILE=$** FFSFILE=$@ COMPRESS=0 NAME=IntelGopDriver

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
