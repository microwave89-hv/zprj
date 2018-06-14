#/*++
#Copyright (c) 2009 - 2011 Intel Corporation. All rights reserved.
#This software and associated documentation (if any) is furnished
#under a license and may only be used or copied in accordance
#with the terms of the license. Except as permitted by such
#license, no part of this software or documentation may be
#reproduced, stored in a retrieval system, or transmitted in any
#form or by any means without the express written consent of
#Intel Corporation.
#
#Module Name:
#
#  TxtPolicyInitDxeLib.mak
#
#Abstract:
#
#  Make file for the TxtPolicyInitDxeLib component
#
#--*/
all : TxtOneTouchDxe

TxtOneTouchDxe : $(BUILD_DIR)\TxtOneTouchDxe.mak TxtOneTouchDxeBin

$(BUILD_DIR)\TxtOneTouchDxe.mak : $(TxtOneTouchDxe_DIR)\$(@B).cif $(TxtOneTouchDxe_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(TxtOneTouchDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

TxtOneTouchDxeIncludes=\
  $(MISCFRAMEWORK_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  /I$(INTEL_PCH_DIR)\
  $(PROJECT_CPU_INCLUDES)\
  $(TXT_INCLUDES)\

TxtOneTouchDxeDefines=\
  $(MY_DEFINES)\
    /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=DriverEntry"\
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

TxtOneTouchDxeLibs=\
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
    $(EFISCRIPTLIB)\
    $(CpuProtocolLib_LIB)\
    $(CpuGuidLib_LIB)\
    $(CPUIA32LIB)\
    $(CpuSampleCodeProtocolLib_LIB)\
    $(INTEL_PCH_PROTOCOL_LIB)

TxtOneTouchDxeBin :  $(TxtOneTouchDxeLibs)
    $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
    /f $(BUILD_DIR)\TxtOneTouchDxe.mak all\
    "MY_INCLUDES=$(TxtOneTouchDxeIncludes)"\
    "MY_DEFINES=$(TxtOneTouchDxeDefines)"\
    "GUID=67791e00-0c05-4ae7-a921-fc4057221653"\
    "AFLAGS=$(AFLAGS) $(TxtOneTouchDxeIncludes)"\
    ENTRY_POINT=_ModuleEntryPoint \
    TYPE=BS_DRIVER \
    EDKIIModule=DXEDRIVER\
    DEPEX1=$(TxtOneTouchDxe_DIR)\TxtOneTouchDxe.dxs\
    DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
    COMPRESS=1\
