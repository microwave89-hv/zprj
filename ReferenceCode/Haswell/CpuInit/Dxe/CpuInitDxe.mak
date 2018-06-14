# MAK file for the eModule:PowerManagement

EDK : CpuInitDxe

BUILD_CpuInitDxe_DIR = $(BUILD_DIR)\$(CpuInitDxe_DIR)

$(BUILD_DIR)\CpuInitDxe.mak : $(CpuInitDxe_DIR)\CpuInitDxe.cif $(BUILD_RULES)
    $(CIF2MAK) $(CpuInitDxe_DIR)\CpuInitDxe.cif $(CIF2MAK_DEFAULTS)

CpuInitDxe : $(BUILD_DIR)\CpuInitDxe.MAK CpuInitDxeBin 

CpuInitDxe_OBJECTS = \
    $(BUILD_CpuInitDxe_DIR)\CacheData.obj \
    $(BUILD_CpuInitDxe_DIR)\CpuFvi.obj \
    $(BUILD_CpuInitDxe_DIR)\MachineCheck.obj \
    $(BUILD_CpuInitDxe_DIR)\MemoryAttribute.obj \
    $(BUILD_CpuInitDxe_DIR)\Microcode.obj \
    $(BUILD_CpuInitDxe_DIR)\MpCommon.obj \
    $(BUILD_CpuInitDxe_DIR)\MpService.obj \
    $(BUILD_CpuInitDxe_DIR)\PiMpService.obj \
    $(BUILD_CpuInitDxe_DIR)\MtrrSync.obj \
    $(BUILD_CpuInitDxe_DIR)\Features.obj \
    $(BUILD_CpuInitDxe_DIR)\ProcessorData.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\Cpu.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\MpFuncs.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\Exception.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\MpCpu.obj \
!IFDEF PeiDebugger_SUPPORT
!IF $(PeiDebugger_SUPPORT)
    $(BUILD_CpuInitDxe_DIR)\CpuInitDxeDbgr.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\MemoryOperationDbgr.obj \
!ELSE
    $(BUILD_CpuInitDxe_DIR)\CpuInitDxe.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\MemoryOperation.obj \
!ENDIF
!ELSE
    $(BUILD_CpuInitDxe_DIR)\CpuInitDxe.obj \
    $(BUILD_CpuInitDxe_DIR)\x64\MemoryOperation.obj \
!ENDIF
    $(BUILD_DIR)\CpuInitDxeStrings.obj \

CpuInitDxe_MY_INCLUDES= \
    $(EdkIIGlueLib_INCLUDES)\
    $(EDK_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    /I$(PROJECT_CPU_ROOT)\CpuInit\Dxe\
    /I$(PROJECT_CPU_ROOT)\CpuInit\Dxe\x64\
    /I$(PROJECT_CPU_ROOT)\CpuSmm\Include\
    /I$(UefiEfiIfrSupportLib_DIR)\
    /I$(PROJECT_CPU_ROOT)\
    /I$(PROJECT_CPU_ROOT)\Include\
    /IBoard\EM\Platform\SMBIOSUpdateData

CpuInitDxe_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InitializeCpu"\
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_LIB__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_LIB__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_DXE_HOB_LIB__ \
    /D REQUEST_EBDA_SIZE="$(REQUEST_EBDA_SIZE)" \
!IFDEF AMI_PEI_DEBUG_SUPPORT
!IF $(AMI_PEI_DEBUG_SUPPORT)
    /D __AMI_PEI_DEBUG_SUPPORT__
!ENDIF
!ENDIF    
!IF $(CPU_MODULE_CREATE_SMBIOS_TABLES)
    /D__CREATE_CPU_SMBIOS__
!ENDIF    
    
CpuInitDxe_LIBS =\
    $(EFIGUIDLIB)\
    $(EDKFRAMEWORKPROTOCOLLIB)\
    $(EDKPROTOCOLLIB)\
    $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
    $(EdkIIGlueBaseLib_LIB)\
    $(EdkIIGlueBaseMemoryLib_LIB)\
    $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
    $(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueUefiLib_LIB)\
    $(EdkIIGlueBasePciLibPciExpress_LIB)\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
    $(EdkIIGlueBaseTimerLibLocalApic_LIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
    $(EdkIIGlueHiiLib_LIB)\
    $(EFIDRIVERLIB)\
    $(UEFIEFIIFRSUPPORTLIB)\
    $(CpuProtocolLib_LIB)\
    $(CpuGuidLib_LIB)\
    $(CPUIA32LIB)\
    $(CpuPlatformLib_LIB)\
    $(PchPlatformDxeLib_LIB)\
    $(RcFviDxeLib_LIB)\
    $(BootGuardRevocationLib_LIB)\
    $(BootGuardLib_LIB)


CpuInitDxeBin : $(CpuInitDxe_LIBS)
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(BUILD_DIR)\CpuInitDxeStrings.c
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\CpuInitDxe.mak all\
    NAME=CpuInitDxe\
    MAKEFILE=$(BUILD_DIR)\CpuInitDxe.mak \
    "MY_INCLUDES=$(CpuInitDxe_MY_INCLUDES)" \
    "MY_DEFINES=$(CpuInitDxe_DEFINES)"\
    OBJECTS="$(CpuInitDxe_OBJECTS)" \
    GUID=62D171CB-78CD-4480-8678-C6A2A797A8DE\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER \
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(CpuInitDxe_DIR)\CpuInitDxe.DXS \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1

#---------------------------------------------------------------------------
#    Create Cpu SDB data
#---------------------------------------------------------------------------
SetupSdbs : CpuDxeSDB

CpuDxeSDB : $(BUILD_DIR)\CpuInitDxe.mak 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
    /f $(BUILD_DIR)\CpuInitDxe.mak all\
    TYPE=SDB NAME=CpuInitDxe
    $(STRGATHER) -dump -lang $(SUPPORTED_LANGUAGES: = -lang )\
    -db $(BUILD_DIR)\CpuInitDxe.sdb\
    -oh $(BUILD_DIR)\CpuInitDxeStrDefs.h\
    -bn CpuInitDxeStrings\
    -oc $(BUILD_DIR)\CpuInitDxeStrings.c
#    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(BUILD_DIR)\CpuInitDxeStrings.c

