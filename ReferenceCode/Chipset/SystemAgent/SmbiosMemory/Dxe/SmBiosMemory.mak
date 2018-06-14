#---------------------------------------------------------------------------
#		Create SmBiosMemory DXE driver
#---------------------------------------------------------------------------
EDK: SmBiosMemorySDB SmBiosMemory 

SmBiosMemory: $(BUILD_DIR)\SmBiosMemory.mak SmBiosMemoryBin

$(BUILD_DIR)\SmBiosMemory.mak : $(SmBiosMemory_DIR)\$(@B).cif $(SmBiosMemory_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(SmBiosMemory_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

SmBiosMemory_OBJECTS = \
    $(BUILD_DIR)\$(SmBiosMemory_DIR)\SmBiosMemory.obj \
    $(BUILD_DIR)\SmBiosMemoryStrings.obj \

SmBiosMemory_INCLUDES=\
    $(EdkIIGlueLib_INCLUDES)\
    $(EDK_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(NB_INCLUDES)\
    /I$(UefiEfiIfrSupportLib_DIR)\

SmBiosMemory_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=SmbiosMemoryEntryPoint"\
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_HII_LIB__

SmBiosMemory_LIBS=\
    $(EDKGUIDLIB)\
    $(EFICOMMONLIB)\
    $(EFIPROTOCOLLIB)\
!IF $(EFI_SPECIFICATION_VERSION) >= 0x0002000A
    $(UEFIEFIIFRSUPPORTLIB)\
!ENDIF
    $(INTEL_SA_PROTOCOL_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
    $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
    $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueHiiLib_LIB)\
    $(EFIDRIVERLIB)\
    $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
    $(EdkIIGlueBasePrintLib_LIB) \
    $(EDKPROTOCOLLIB)\

SmBiosMemoryBin : $(SmBiosMemory_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\SmBiosMemory.mak all\
    GUID=EDA39402-F375-4496-92D3-83B43CB8A76A\
    "MY_INCLUDES=$(SmBiosMemory_INCLUDES)" \
    "MY_DEFINES=$(SmBiosMemory_DEFINES)"\
    ENTRY_POINT=_ModuleEntryPoint\
    TYPE=BS_DRIVER\
    EDKIIModule=DXEDRIVER\
    "OBJECTS=$(SmBiosMemory_OBJECTS)"\
    DEPEX1=$(SmBiosMemory_DIR)\SmBiosMemory.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1

#---------------------------------------------------------------------------
#    Create SmBiosMemory Setup Screens
#---------------------------------------------------------------------------
SmBiosMemorySDB : $(BUILD_DIR)\SmBiosMemory.mak 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
    /f $(BUILD_DIR)\SmBiosMemory.mak all\
    TYPE=SDB NAME=SmBiosMemory
    $(STRGATHER) -dump -lang $(SUPPORTED_LANGUAGES: = -lang )\
    -db $(BUILD_DIR)\SmBiosMemory.sdb\
    -oh $(BUILD_DIR)\SmBiosMemoryStrDefs.h\
    -bn SmBiosMemoryStrings\
    -oc $(BUILD_DIR)\SmBiosMemoryStrings.c	
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(BUILD_DIR)\SmBiosMemoryStrings.c