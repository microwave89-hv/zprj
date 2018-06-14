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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctDxeAcpi/IsctAcpi.mak 3     7/11/14 10:37a Mirayang $
#
# $Revision: 3 $
#
# $Date: 7/11/14 10:37a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ISCT/IsctDxeAcpi/IsctAcpi.mak $
# 
# 3     7/11/14 10:37a Mirayang
# Fix iRST bulid error.
# 
# 2     3/27/13 9:14a Bensonlai
# [TAG]  		EIP118307
# [Category]  	New Feature
# [Description]  	Implementation of the ISCT Platform Design
# Specification 0.8.
# [Files]  		Isct.asl, IsctAcpi.c, IsctAcpi.mak
# 
# 1     9/02/12 11:19p Bensonlai
# Intel Smart Connect Technology initially releases.
#
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: IsctAcpi.mak
#
# Description: Make file to build IsctAcpi components
#
#
#<AMI_FHDR_END>
#**********************************************************************

all : IsctAcpi

IsctAcpi : $(BUILD_DIR)\IsctAcpi.mak IsctAcpi_Bin

$(BUILD_DIR)\IsctAcpi.mak : $(IsctAcpi_DIR)\$(@B).cif $(IsctAcpi_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(IsctAcpi_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

IsctAcpi_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(EDK_INCLUDES)\
  $(PLATFORM_INFO_PROTOCOL_INCLUDES)\
  /I$(ISCT_PLATFORM_DIR)\
  /I$(IntelPlatformProtocolLib_DIR)\
  $(INTEL_MCH_INCLUDES)\

IsctAcpi_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(EFIGUIDLIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EDKFRAMEWORKGUIDLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeServicesTableLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiDevicePathLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(IsctGuidLib_LIB)\
  $(IsctProtocolLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\
  $(INTEL_SA_PROTOCOL_LIB)\

IsctAcpi_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=IsctDxeEntryPoint"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \
  /D __EDKII_GLUE_DXE_HOB_LIB__ \

IsctAcpi_Bin : $(IsctAcpi_LIBS)
	$(MAKE) /$(MAKEFLAGS)  $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\IsctAcpi.mak all\
		"MY_INCLUDES=$(IsctAcpi_INCLUDES)"\
		"MY_DEFINES=$(IsctAcpi_DEFINES)"\
		GUID=4839023B-4C12-4EB2-B2B8-C91B42D878A0 \
		ENTRY_POINT=_ModuleEntryPoint \
		EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(IsctAcpi_DIR)\IsctAcpi.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1\

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
