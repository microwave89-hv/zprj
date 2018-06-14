#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
#**********************************************************************
#
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccPlatform/IccPlatform.mak 5     9/27/12 6:23a Klzhan $
#
# $Revision: 5 $
#
# $Date: 9/27/12 6:23a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Icc/IccPlatform/IccPlatform.mak $
# 
# 5     9/27/12 6:23a Klzhan
# Fix build error
# 
# 4     9/19/12 5:54a Klzhan
# 1. Fix Build Error when Performance is on(IccPlatform.mak).
# 2. Avoid time-out in ICC setup Page when return from Shell.
# 3. Remove un-used wait for Fw Init Done.
# 
# 3     4/24/12 12:28a Klzhan
# 
# 2     2/23/12 8:57a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:06a Klzhan
# Initial Check in 
# 
# 4     9/06/11 6:38a Klzhan
# Remove __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__
# 
# 3     7/27/11 3:21a Klzhan
# Add Elinks for PCIE and PCI config.
# Note: Don't List GBE port on this Elink.
# 
# 2     7/15/11 12:45a Klzhan
# 
# 1     2/25/11 1:42a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:10a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            IccPlatform.mak
#
# Description:     MakFile for Platform-specific ICC code
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : IccPlatform 

$(BUILD_DIR)\IccPlatform.mak : $(IccPlatform_DIR)\$(@B).cif $(BUILD_RULES)
  $(CIF2MAK) $(IccPlatform_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IccPlatform : $(BUILD_DIR)\IccPlatform.mak IccPlatform_Bin

IccPlatform_INCLUDES=\
	$(EDK_INCLUDES)\
	$(EdkIIGlueLib_INCLUDES)\
	$(ME_INCLUDES)\
	$(MISCFRAMEWORK_INCLUDES)\
	$(INTEL_MCH_INCLUDES)\
	$(NB_INCLUDES)\
	$(INTEL_PCH_INCLUDES)\
	$(ICC_INCLUDES)\
	/I$(PROJECT_DIR)\
        /IInclude\

IccPlatform_LIBS=\
	$(EDKPROTOCOLLIB)\
	$(EDKFRAMEWORKPROTOCOLLIB)\
        $(EFISCRIPTLIB)\
	$(EFIGUIDLIB)\
	$(MeProtocolLib_LIB)\
	$(MeLibDxe_LIB)\
	$(EdkIIGlueBaseLib_LIB)\
	$(EdkIIGlueBasePrintLib_LIB)\
!IF "$(x64_BUILD)"=="1"
	$(EdkIIGlueBaseLibX64_LIB)\
!ELSE
	$(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
	$(EdkIIGlueBaseMemoryLib_LIB)\
	$(EdkIIGlueDxeReportStatusCodeLib_LIB)\
	$(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
	$(EdkIIGluePeiDxeDebugLibReportStatusCode_LIB)\
	$(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
	$(EdkIIGlueUefiBootServicesTableLib_LIB)\
	$(EdkIIGlueUefiLib_LIB)\
	$(EdkIIGlueDxeMemoryAllocationLib_LIB)\
	$(EdkIIGlueDxeServicesTableLib_LIB)\
	$(EdkIIGlueBasePciCf8Lib_LIB)\
	$(EFIDRIVERLIB)\
	$(INTEL_PCH_PROTOCOL_LIB)\

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF
	
IccPlatform_DEFINES=\
	$(MY_DEFINES)\
        $(DxeCpuBuildDefine)\
	/D"__EDKII_GLUE_MODULE_ENTRY_POINT__=IccPlatformEntryPoint"\
	/D __EDKII_GLUE_BASE_MEMORY_LIB__ \
	/D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
	/D __EDKII_GLUE_PEI_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
	/D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

ICC_ELINKS = \
/D\"OEM_CLOCK_UPDATE_FUNC=$(OEMClockUpdateFunc)\"\
!IF "$(OEMPCIEClockConfig)" == ""
/D\"PCIE_CLOCK_CONFIG=$(PCIEClockConfig)\"\
!ELSE
/D\"PCIE_CLOCK_CONFIG=$(OEMPCIEClockConfig)\"\
!ENDIF
!IF "$(OEMPCIClockConfig)" == ""
/D\"PCI_CLOCK_CONFIG=$(PCIClockConfig)\"
!ELSE
/D\"PCI_CLOCK_CONFIG=$(OEMPCIClockConfig)\"
!ENDIF


IccPlatform_Bin : $(IccPlatform_LIBS) $(OemClock_LIB)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\IccPlatform.mak all\
		"MY_INCLUDES=$(IccPlatform_INCLUDES)"\
		"MY_DEFINES=$(IccPlatform_DEFINES)"\
		"CFLAGS=$(CFLAGS) $(ICC_ELINKS)" \
		GUID=14257B56-BDA2-4faf-8E4F-C885DF75583C\
		ENTRY_POINT=_ModuleEntryPoint \
		EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(IccPlatform_DIR)\IccPlatform.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************