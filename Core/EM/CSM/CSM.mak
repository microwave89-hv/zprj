#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/CSM/Generic/Core/csm.mak 37    9/08/15 2:25p Olegi $
#
# $Revision: 37 $
#
# $Date: 9/08/15 2:25p $
#**********************************************************************

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:         CSMCORE.MAK
#
# Description:  Make file for the CSM component
#
#<AMI_FHDR_END>
#**********************************************************************

all : CSMCORE

!IF $(CORE_COMBINED_VERSION) <	262795
!ERROR This version of CSM is compatible with Core 4.6.5.1 or later.
!ELSE
CSMCORE : CSMELINKFUNCTIONS $(BUILD_DIR)\csmcore.mak LEGACY_ROM CSMCOREBin 
!ENDIF

!IFDEF LEGACY_TO_EFI_BOOT_SUPPORT
!IF $(LEGACY_TO_EFI_BOOT_SUPPORT) == 1
!ERROR LEGACY_TO_EFI_BOOT_SUPPORT detected: disable or remove LegacyToEfiBoot module. This version of CSM implements all features of LegacyToEfiBoot.
!ENDIF
!ENDIF

CSMELINKFUNCTIONS :
    type << >$(BUILD_DIR)\CsmElinkFunctions.h
#define CSM_GET_OPROM_VIDEO_SWITCHING_MODE_FUNCTIONS $(CSM_GET_OPROM_VIDEO_SWITCHING_MODE_FUNCTIONS:},=},\^
)
#define CSM_GET_CUSTOM_PCI_PIRQ_MASK_FUNCTIONS $(CSM_GET_CUSTOM_PCI_PIRQ_MASK_FUNCTIONS:},=},\^
)
#define CSM_GET_GATE_A20_INFORMATION_FUNCTIONS $(CSM_GET_GATE_A20_INFORMATION_FUNCTIONS:},=},\^
)
#define CSM_GET_NMI_INFORMATION_FUNCTIONS $(CSM_GET_NMI_INFORMATION_FUNCTIONS:},=},\^
)
#define CSM_GET_OEM_INT_DATA_FUNCTIONS $(CSM_GET_OEM_INT_DATA_FUNCTIONS:},=},\^
)
#define CSM_GET_PLATFORM_HANDLE_FUNCTIONS $(CSM_GET_PLATFORM_HANDLE_FUNCTIONS:},=},\^
)
#define CSM_GET_PLATFORM_PCI_EMBEDDED_ROM_FUNCTIONS $(CSM_GET_PLATFORM_PCI_EMBEDDED_ROM_FUNCTIONS:},=},\^
)
#define CSM_GET_PLATFORM_EMBEDDED_ROM_FUNCTIONS $(CSM_GET_PLATFORM_EMBEDDED_ROM_FUNCTIONS:},=},\^
)
#define CSM_CHECK_OEM_PCI_SIBLINGS_FUNCTIONS $(CSM_CHECK_OEM_PCI_SIBLINGS_FUNCTIONS:},=},\^
)
#define CSM_ENABLE_OEM_PCI_SIBLINGS_FUNCTIONS $(CSM_ENABLE_OEM_PCI_SIBLINGS_FUNCTIONS:},=},\^
)
#define CSM_GET_ROUTING_TABLE_FUNCTIONS $(CSM_GET_ROUTING_TABLE_FUNCTIONS:},=},\^
)
#define CSM_BSP_UPDATE_PRT_FUNCTIONS $(CSM_BSP_UPDATE_PRT_FUNCTIONS:},=},\^
)
#define CSM_BSP_PREPARE_TO_BOOT_FUNCTIONS $(CSM_BSP_PREPARE_TO_BOOT_FUNCTIONS:},=},\^
)
#define CSM_INIT_LEGACY_MEMORY_FUNCTIONS $(CSM_INIT_LEGACY_MEMORY_FUNCTIONS:},=},\^
)
#define CSM_16_CALL_COMPANION_FUNCTIONS $(CSM_16_CALL_COMPANION_FUNCTIONS:},=},\^
)
<<

$(BUILD_DIR)\csmcore.mak : $(CSMCORE_DIR)\csmcore.cif $(CSMCORE_DIR)\csm.mak $(BUILD_RULES)
        $(CIF2MAK) $(CSMCORE_DIR)\csmcore.cif $(CIF2MAK_DEFAULTS)

$(BUILD_DIR)\thunk.obj: $(X86THUNK_DIR)\thunk.c $(BUILD_DIR)\token.h $(CSMCORE_DIR)\csm.h
        $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(PROJECT_DIR)\$(X86THUNK_DIR)\thunk.c /I$(CSMCORE_DIR)

CSMCOREBin : $(BUILD_DIR)\thunk.obj $(AMIDXELIB) $(AMICSPLib)
        $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
                /f $(BUILD_DIR)\csmcore.mak all\
                GUID=A062CF1F-8473-4aa3-8793-600BC4FFE9A8 \
                ENTRY_POINT=CsmEntryPoint \
                "CFLAGS=$(CFLAGS) /I$(CSMCORE_DIR)"\
                TYPE=BS_DRIVER \
                EXT_HEADERS=$(BUILD_DIR)\token.h\
                BINFILE=$(BUILD_DIR)\ROMs.bin \
                SECTION_GUID=E6F4F8F7-4992-47b2-8302-8508745E4A23 \
                COMPRESS=1\

LEGACY_ROM: $(BUILD_DIR)\ROMs.inf
        $(PACKOPROM) /o$(BUILD_DIR)\ROMs.bin $(BUILD_DIR)\ROMs.inf

$(BUILD_DIR)\ROMs.inf: $(OEM_SERVICE_ROM_LIST) $(CSM_OEM_BIN_FILE) $(CSM_CUSTOM_INFS)
    @copy << $@
[MODULE]
ModuleID = 1
VendorID = 0
DeviceID = 0
File = $(AMILEGACY16_BIN)
!if "$(PCI_ROMS_OUTSIDE_CSM)"=="0"
$(PCI_OPT_ROM_LIST)
!endif
!if "$(PXE_BASECODE_ROM)"=="1"
[MODULE]
ModuleID = 2
VendorID = 0
DeviceID = 0
File = $(PXE_BASECODE_ROM_FILE)
!endif

!if "$(OEM_SERVICE_ROM_LIST)"!=""
[MODULE]
ModuleID = 2
VendorID = 0
DeviceID = 0
File = $(OEM_SERVICE_ROM_LIST: =^

[MODULE]^
ModuleID = 2^
VendorID = 0^
DeviceID = 0^
File = )

!endif
!if "$(CSM_OEM_SUPPORT)"=="1"
[MODULE]
ModuleID = 3
VendorID = 0
DeviceID = 0
File = $(CSM_OEM_BIN_FILE)

!endif
<<

!if "$(CSM_CUSTOM_INFS)"!=""
    copy $@+$(CSM_CUSTOM_INFS: =+) $@
!endif


#---------------------------------------------------------------------------
#		Create CSM Setup Screens
#---------------------------------------------------------------------------
SetupSdbs: $(BUILD_DIR)\csm.sdb
SetupBin: $(BUILD_DIR)\csmsetup.obj

$(BUILD_DIR)\csm.sdb : $(CSM_SETUP_DIR)\csm.sd $(CSM_SETUP_DIR)\csm.uni
	$(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\csm.sdb $(CSM_SETUP_DIR)\csm.uni
	$(STRGATHER) -scan -db $(BUILD_DIR)\csm.sdb -od $(BUILD_DIR)\csm.sdb $(CSM_SETUP_DIR)\csm.sd

$(BUILD_DIR)\csmsetup.obj: $(CSM_SETUP_DIR)\csmsetup.c $(BUILD_DIR)\SetupStrTokens.h
	$(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(CSM_SETUP_DIR)\csmsetup.c
#---------------------------------------------------------------------------


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**           5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093      **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
