#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartWrapperSmm.mak 1     12/27/12 2:23a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 12/27/12 2:23a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartWrapperSmm.mak $
# 
# 1     12/27/12 2:23a Bensonlai
# [TAG]  		EIP110680
# [Category]  	New Feature
# [Description]  	When iRST application is run under OS, and change
# timer.
# BIOS should update the changed to Setup option as well.
# [Files]  		Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.c
# Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.h
# Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.mak
# Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.dxs
# Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.sdl
# Board\EM\RapidStartWrapper\Smm\RapidStartWrapperSmm.cif
# Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.cif
# Board\EM\RapidStartWrapper\AcpiTables\RapidStartWrapperAcpiTables.sdl
# Board\EM\RapidStartWrapper\AcpiTables\Ssdt\RapidStartWrapper.asl
# Board\EM\RapidStartWrapper\RapidStartSetup\RapidStartSetup.sd
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	RapidStartWrapperSmm.mak
#
# Description: Make file to build RapidStartWrapperSmm components
#
#<AMI_FHDR_END>
#**********************************************************************

EDK : RapidStartWrapperSmm

RapidStartWrapperSmm : $(BUILD_DIR)\RapidStartWrapperSmm.mak RapidStartWrapperSmmBin

$(BUILD_DIR)\RapidStartWrapperSmm.mak : $(RapidStartWrapperSmm_DIR)\$(@B).cif $(RapidStartWrapperSmm_DIR)\$(@B).mak $(BUILD_RULES)
      $(CIF2MAK) $(RapidStartWrapperSmm_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartWrapperSmm_INCLUDES=\
      $(RAPIDSTART_INCLUDES)\
      $(EdkIIGlueLib_INCLUDES)\

RapidStartWrapperSmm_DEFINES = $(MY_DEFINES)\
      /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=RapidStartWrapperSmmEntryPoint"\
      /D __EDKII_GLUE_BASE_LIB__ \
      /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
      /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
      /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \
      /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
      /D __EDKII_GLUE_SMM_RUNTIME_DXE_REPORT_STATUS_CODE_LIB__ \
      /D __EDKII_GLUE_UEFI_LIB__ \
      /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__ \
      /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
      /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \

RapidStartWrapperSmm_LIB =\
      $(EFIPROTOCOLLIB)\
      $(EDKPROTOCOLLIB)\
      $(EDKFRAMEWORKPROTOCOLLIB)\
      $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
      $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
      $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
      $(ArchProtocolLib)\
      $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
      $(EdkIIGlueBaseMemoryLib_LIB)\
      $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
      $(EdkIIGlueDxeServicesTableLib_LIB)\
      $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
      $(EdkIIGlueSmmRuntimeDxeReportStatusCodeLib_LIB)\
      $(EdkIIGlueBasePciLibPciExpress_LIB)\
      $(EdkIIGlueUefiLib_LIB)\
      $(EdkIIGlueUefiBootServicesTableLib_LIB)\
      $(EdkIIGlueUefiDevicePathLib_LIB)\
      $(RapidStartProtocolLib_LIB)\
      $(RapidStartGuidLib_LIB)\

RapidStartWrapperSmmBin: $(RapidStartWrapperSmm_LIB)
      $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
      /f $(BUILD_DIR)\RapidStartWrapperSmm.mak all \
      "MY_INCLUDES=$(RapidStartWrapperSmm_INCLUDES)" \
      "MY_DEFINES=$(RapidStartWrapperSmm_DEFINES)" \
      GUID=760DCD41-FF47-41d8-91B2-BC527D6C5823\
      ENTRY_POINT=_ModuleEntryPoint \
      TYPE=BS_DRIVER\
      EDKIIModule=SMMDRIVER\
      DEPEX1=$(RapidStartWrapperSmm_DIR)\RapidStartWrapperSmm.dxs\
      DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX  \
      COMPRESS=1

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
