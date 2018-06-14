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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxePolicyInit/RapidStartDxePolicyInit.mak 5     6/21/13 6:01a Joshchou $
#
# $Revision: 5 $
#
# $Date: 6/21/13 6:01a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxePolicyInit/RapidStartDxePolicyInit.mak $
# 
# 5     6/21/13 6:01a Joshchou
# [TAG]  		EIP126792
# [Category]  	Bug Fix
# [Severity]  	Minor
# [Symptom]  	Can't do AMI capsule when Intel Rapid Start eanble
# [RootCause]  	CMOS RapidStartFlag does not clear.
# [Solution]  	Clear RapidStartFlag when cold boot.
# 
# 4     1/13/13 7:47a Bensonlai
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Disabling the RapidStart while STAT mode in the IDE
# mode
# [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
# RapidStartDxePolicyInit.mak, RapidStartSetup.c, RapidStartSetup.mak,
# RapidStartSetup.sd, RapidStartSetup.sdl
# 
# 3     12/07/12 1:17a Bensonlai
# [TAG]  		None
# [Category]  	Bug Fix
# [Severity]  	Normal
# [Symptom]  	When installed memory size less than HDD partition size of
# teh RapidStart, it still can work.
# [RootCause]  	The RAPID_START_PERSISTENT_DATA wasn't updated in the
# BdsAllDriversConnectedCallback().
# [Solution]  	Get the real total size of memory directly.
# [Files]  		RapidStartDxePolicyInit.c, RapidStartDxePolicyInit.h,
# RapidStartDxePolicyInit.mak
# 
# 2     11/15/12 12:38a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Move the RAPID_START_PARTITION_DETECT_BEFORE_SETUP to
# RapidStartDxePolicyInit.c.
# 
# 1     10/15/12 4:40a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	[Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# 
# [Category] Improvement
# [Severity] Important
# [Description] Implementation of the LOCK_DISABLE_RAPID_START_IF_NO_SSD
# using EDKII.
# [Files] Board\EM\RapidStartWrapper\Dxe\RapidStartDxePolicyInit\*.*
# [Files]  		RapidStartDxePolicyInit.cif
# RapidStartDxePolicyInit.sdl
# RapidStartDxePolicyInit.mak
# RapidStartDxePolicyInit.h
# RapidStartDxePolicyInit.c
# RapidStartDxePolicyInit.dxs
# RapidStartDxePolicyInit.inf
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: RapidStartDxePolicyInit.mak
#
# Description: Component description file for the RapidStartDxePolicyInit DXE driver.
#
#<AMI_FHDR_END>
#**********************************************************************

All : RapidStartDxePolicyInit

RapidStartDxePolicyInit : $(BUILD_DIR)\RapidStartDxePolicyInit.mak RapidStartDxePolicyInitBin

$(BUILD_DIR)\RapidStartDxePolicyInit.mak : $(RapidStartDxePolicyInit_DIR)\$(@B).cif $(RapidStartDxePolicyInit_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(RapidStartDxePolicyInit_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartDxePolicyInit_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(EDK_INCLUDES)\
  $(RAPIDSTART_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\
  $(INTEL_MCH_INCLUDES)\

RapidStartDxePolicyInit_LIBS=\
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
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(RapidStartProtocolLib_LIB)\
  $(RapidStartDxeLib_LIB)\
  $(PchPlatformDxeLib_LIB)\
  $(RapidStartCommonDxeLib_LIB)\

RapidStartDxePolicyInit_DEFINES=\
  $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=RapidStartDxePolicyInitEntryPoint"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__ \

RapidStartDxePolicyInitBin : $(RapidStartDxePolicyInit_LIBS)
  $(MAKE) /$(MAKEFLAGS)  $(EDKIIGLUE_DEFAULTS)\
  /f $(BUILD_DIR)\RapidStartDxePolicyInit.mak all\
  "MY_INCLUDES=$(RapidStartDxePolicyInit_INCLUDES)"\
  "MY_DEFINES=$(RapidStartDxePolicyInit_DEFINES)"\
  GUID=DDB412A6-E3F3-4e9e-90A3-2A991270219C\
  ENTRY_POINT=_ModuleEntryPoint \
  EDKIIModule=DXEDRIVER\
  TYPE=BS_DRIVER \
  DEPEX1=$(RapidStartDxePolicyInit_DIR)\RapidStartDxePolicyInit.dxs \
  DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
  COMPRESS=1\

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
