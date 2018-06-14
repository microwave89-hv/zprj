# /*++
# 
# --*/
all : FirmwareVerInfo

FirmwareVerInfo : $(BUILD_DIR)\FirmwareVerInfo.mak FirmwareVerInfoBin

$(BUILD_DIR)\FirmwareVerInfo.mak : $(FirmwareVerInfo_DIR)\FirmwareVerInfo.cif $(FirmwareVerInfo_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(FirmwareVerInfo_DIR)\FirmwareVerInfo.cif $(CIF2MAK_DEFAULTS)

FirmwareVerInfo_INCLUDES = \
    $(EDK_INCLUDES)\
    /I Include\
    $(INTEL_PCH_INCLUDES)

FirmwareVerInfo_LIB_LINKS =\
    $(EFIDRIVERLIB)

FirmwareVerInfoBin : $(FirmwareVerInfo_LIB_LINKS)
    $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
        /f $(BUILD_DIR)\FirmwareVerInfo.mak all\
        NAME=FirmwareVerInfo\
        "MY_INCLUDES=$(FirmwareVerInfo_INCLUDES)"\
        GUID=132A6630-FEB5-4ba2-85FB-FD2635379257\
        ENTRY_POINT=FirmwareVerInfoEntryPoint\
        DEPEX1=$(FirmwareVerInfo_DIR)\FirmwareVerInfo.dxs \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
        TYPE=BS_DRIVER\
        COMPRESS=1
