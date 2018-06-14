#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#*************************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatServices.mak 3     9/25/12 6:14p Fredericko $
#
# $Revision: 3 $
#
# $Date: 9/25/12 6:14p $
#
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelPfat/PfatServices.mak $
# 
# 3     9/25/12 6:14p Fredericko
# 
# 2     9/17/12 4:19p Fredericko
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	PfatService.mak
#
# Description: Make file for PfatServices component
#
#<AMI_FHDR_END>
#**********************************************************************
# MAK file for the eModule:PowerManagement

EDK : PfatServices

BUILD_PfatServices_DIR = $(BUILD_DIR)\$(PfatServices_DIR)

$(BUILD_DIR)\PfatServices.mak : $(PfatServices_DIR)\PfatServices.cif $(BUILD_RULES)
    $(CIF2MAK) $(PfatServices_DIR)\PfatServices.cif $(CIF2MAK_DEFAULTS)

PfatServices : $(BUILD_DIR)\PfatServices.MAK PfatServicesBin

PfatServices_OBJECTS = \
    $(BUILD_PfatServices_DIR)\PfatServices.obj \
    
PfatServices_MY_INCLUDES= \
    $(EDK_INCLUDES)\
    $(PROJECT_CPU_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_PLATFORM_PROTOCOL_INCLUDES)

PfatServices_DEFINES = $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=InstallPfatProtocol"\
    /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
    /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
    /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
    /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
    /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
    /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_RUNTIME_SERVICES_TABLE_LIB__ \
    /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
    /D __EDKII_GLUE_DXE_HOB_LIB__ \
    /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__

PfatServices_LIBS =\
  $(EDKPROTOCOLLIB)\
  $(EFISCRIPTLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIGUIDLIB)\
  $(PpmAslUpdateLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(IntelPlatformProtocolLib_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EFIDRIVERLIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiRuntimeServicesTableLib_LIB)\
  $(EdkIIGlueUefiDevicePathLib_LIB) \
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueUefiRuntimeServicesTableLib_LIB) \
  $(EdkIIGlueDxeHobLib_LIB)\
  $(CpuProtocolLib_LIB)\
  $(PchPlatformDxeLib_LIB)



PfatServicesBin : $(PfatServices_LIBS)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\PfatServices.mak all\
    NAME=PfatServices\
    MAKEFILE=$(BUILD_DIR)\PfatServices.mak \
    "MY_INCLUDES=$(PfatServices_MY_INCLUDES)" \
    "MY_DEFINES=$(PfatServices_DEFINES)"\
    OBJECTS="$(PfatServices_OBJECTS)" \
    GUID=6D4BAA0B-F431-4370-AF19-99D6209239F6\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=RT_DRIVER \
    EDKIIModule=SMMDRIVER\
    DEPEX1=$(PfatServices_DIR)\PfatServices.DXS \
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
    COMPRESS=1
#-----------------------------------------------------------------------
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**     5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093            **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
