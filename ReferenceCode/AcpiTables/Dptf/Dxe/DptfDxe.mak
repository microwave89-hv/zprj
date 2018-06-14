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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/DPTF/DptfDxe/DptfDxe.mak 2     9/26/12 2:00a Victortu $
#
# $Revision: 2 $
#
# $Date: 9/26/12 2:00a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/DPTF/DptfDxe/DptfDxe.mak $
# 
# 2     9/26/12 2:00a Victortu
# 
# 1     4/24/12 9:25a Victortu
# Intel DPTF initialization.
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: DptfDxe.mak
#
# Description: MAke file to build Intel DPTF components
#
#<AMI_FHDR_END>
#*************************************************************************
EDK : DptfDxe

DptfDxe : $(BUILD_DIR)\DptfDxe.mak DptfDxeBin

DptfDxe_OBJECTS = \
$(BUILD_DIR)\$(INTEL_DPTF_DXE_DIR)\Dptf.obj

$(BUILD_DIR)\DptfDxe.mak : $(INTEL_DPTF_DXE_DIR)\$(@B).cif $(INTEL_DPTF_DXE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(INTEL_DPTF_DXE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

DptfDxe_LIBS =\
	$(EDKPROTOCOLLIB)\
	$(EFIPROTOCOLLIB)\
	$(ARCHPROTOCOLLIB)\
	$(EDKFRAMEWORKPROTOCOLLIB)\
	$(EFISCRIPTLIB)\
	$(EdkIIGlueBaseLib_LIB)\
	$(EdkIIGlueBasePciExpressLib_LIB)\
	$(EdkIIGlueUefiBootServicesTableLib_LIB)\
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
	$(EFIDRIVERLIB)\
	$(AcpiProtocolLib_LIB)\
	$(DptfGuidLib_LIB)\

DptfDxe_INCLUDES= $(EDK_INCLUDES)\
	$(IndustryStandard_INCLUDES)\
	$(EdkIIGlueLib_INCLUDES)\
	$(DPTF_INCLUDES)\
	/I ReferenceCode\AcpiTables\
	/I$(ArchProtocolLib_DIR)\Cpu\
	/I$(INTEL_SYSTEM_AGENT_DIR)\Include\

DptfDxeBin: $(DptfDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\DptfDxe.mak all \
	NAME=DptfDxe\
	MAKEFILE=$(BUILD_DIR)\DptfDxe.mak \
	"MY_INCLUDES=$(DptfDxe_INCLUDES)"\
	GUID=918ABA30-3D8D-4bb5-B849-45CC4FC7DE7C\
	ENTRY_POINT=InitializeDptf \
	TYPE=RT_DRIVER\
	"OBJECTS=$(DptfDxe_OBJECTS)"\
	DEPEX1=$(INTEL_DPTF_DXE_DIR)\Dptf.dxs\
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