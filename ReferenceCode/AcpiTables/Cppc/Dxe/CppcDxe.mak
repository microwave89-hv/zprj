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

#*************************************************************************
#<AMI_FHDR_START>
#
# Name: CppcDxe.mak
#
# Description: Make file to build Intel CPPC components
#
#<AMI_FHDR_END>
#*************************************************************************
EDK : CppcDxe

CppcDxe : $(BUILD_DIR)\CppcDxe.mak CppcDxeBin

CppcDxe_OBJECTS = \
$(BUILD_DIR)\$(INTEL_CPPC_DXE_DIR)\Cppc.obj

$(BUILD_DIR)\CppcDxe.mak : $(INTEL_CPPC_DXE_DIR)\$(@B).cif $(INTEL_CPPC_DXE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(INTEL_CPPC_DXE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CppcDxe_LIBS =\
    $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
	$(EDKPROTOCOLLIB)\
	$(EFIPROTOCOLLIB)\
	$(ARCHPROTOCOLLIB)\
	$(EDKFRAMEWORKPROTOCOLLIB)\
	$(EFISCRIPTLIB)\
	$(EdkIIGlueBaseLib_LIB)\
	$(EdkIIGlueBasePciExpressLib_LIB)\
	$(EdkIIGlueUefiLib_LIB)\
!IF "$(x64_BUILD)"=="1"
	$(EdkIIGlueBaseLibX64_LIB)\
!ELSE
	$(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
	$(EdkIIGlueDxeReportStatusCodeLib_LIB)\
	$(EdkIIGlueDxeServicesTableLib_LIB)\
	$(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
	$(EdkIIGlueDxeHobLib_LIB)\
	$(EdkIIGlueBasePciLibPciExpress_LIB)\
	$(EFIDRIVERLIB)\
	$(AcpiProtocolLib_LIB)\
	$(CppcGuidLib_LIB)\
	$(CpuProtocolLib_LIB)\
	$(CpuPlatformLib_LIB)\
	$(PchPlatformDxeLib_LIB)\

CppcDxe_INCLUDES= $(EDK_INCLUDES)\
	$(IndustryStandard_INCLUDES)\
	$(EdkIIGlueLib_INCLUDES)\
	$(CPPC_INCLUDES)\
	/I ReferenceCode\AcpiTables\
	/I$(ArchProtocolLib_DIR)\Cpu\
	$(PROJECT_CPU_INCLUDES)\
	/I$(PROJECT_CPU_ROOT)\Library\CpuPlatformLib\
	/I$(INTEL_SYSTEM_AGENT_DIR)\Include\

CppcDxeBin: $(CppcDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\CppcDxe.mak all \
	NAME=CppcDxe\
	MAKEFILE=$(BUILD_DIR)\CppcDxe.mak \
	"MY_INCLUDES=$(CppcDxe_INCLUDES)"\
	GUID=C07A1EB5-5C04-4100-817B-0A11BB5F15DC\
	ENTRY_POINT=InitializeCppc \
	TYPE=RT_DRIVER\
	"OBJECTS=$(CppcDxe_OBJECTS)"\
	DEPEX1=$(INTEL_CPPC_DXE_DIR)\Cppc.dxs\
	DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
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