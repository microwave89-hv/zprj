# MAK file for the ModulePart:TxtBiosAcm binary
all: $(BUILD_DIR)\BiosAcm.ffs $(TxtBiosAcm_DIR)\TxtBiosAcm.mak

$(BUILD_DIR)\HSW_BIOSAC.bin :
  COPY $(TxtBiosAcmFile) $(BUILD_DIR)\HSW_BIOSAC.bin $(SILENT_OUT)

$(BUILD_DIR)\BiosAcm.ffs : $(BUILD_DIR)\HSW_BIOSAC.bin
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=2d27c618-7dcd-41f5-bb10-21166be7e143\
		TYPE=EFI_FV_FILETYPE_RAW \
        FFS_ALIGNMENT=5 FFS_CHECKSUM=0\
		RAWFILE=$(BUILD_DIR)\HSW_BIOSAC.bin FFSFILE=$(BUILD_DIR)\BiosAcm.ffs COMPRESS=0 NAME=BiosAcm