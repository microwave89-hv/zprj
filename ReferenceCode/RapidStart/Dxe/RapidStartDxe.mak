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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartDxe/RapidStartDxe.mak 3     10/15/12 5:41a Bensonlai $
#
# $Revision: 3 $
#
# $Date: 10/15/12 5:41a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartDxe/RapidStartDxe.mak $
# 
# 3     10/15/12 5:41a Bensonlai
# [Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# 
# 2     9/26/12 3:28a Yurenlai
# [TAG]           None
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Beta Version 0.7.0.
# [Description]   ReferenceCode\RapidStart\*.*, RapidStartPeiLib.h
# 
# 1     4/19/12 8:03a Yurenlai
# Initial check in.
#
#*************************************************************************

all : RapidStartDxe

RapidStartDxe : $(BUILD_DIR)\RapidStartDxe.mak RapidStartDxe_Bin

$(BUILD_DIR)\RapidStartDxe.mak : $(RapidStartDxe_DIR)\$(@B).cif $(RapidStartDxe_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RapidStartDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartDxe_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(EDK_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  $(PROJECT_INCLUDES)\
  $(MISCFRAMEWORK_INCLUDES)\
  $(PLATFORM_INFO_PROTOCOL_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\
  $(NB_INCLUDES)\
  $(ME_INCLUDES)\
  /I$(GfxDisplayLibDxe_DIR)\
  $(RAPIDSTART_INCLUDES)\
  /I$(IntelPlatformProtocolLib_DIR)\

RapidStartDxe_LIBS=\
  $(EDKPROTOCOLLIB)\
  $(INTEL_PCH_PROTOCOL_LIB)\
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
  $(RapidStartProtocolLib_LIB)\
  $(RapidStartGuidLib_LIB)\
  $(RapidStartDxeLib_LIB)\
  $(PchPlatformDxeLib_LIB)\
  $(RapidStartCommonSmmLib_LIB)\
  $(RcFviDxeLib_LIB)\
  $(GfxDisplayLibDxe_LIB)\

RapidStartDxe_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=RapidStartDxeEntryPoint"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \

RapidStartDxe_Bin : $(RapidStartDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS)  $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\RapidStartDxe.mak all\
		"MY_INCLUDES=$(RapidStartDxe_INCLUDES)"\
		"MY_DEFINES=$(RapidStartDxe_DEFINES)"\
		GUID=b6b9295f-cabf-4cec-bb14-fe4246f2173a\
		ENTRY_POINT=_ModuleEntryPoint \
		EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(RapidStartDxe_DIR)\RapidStartDxe.dxs \
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
