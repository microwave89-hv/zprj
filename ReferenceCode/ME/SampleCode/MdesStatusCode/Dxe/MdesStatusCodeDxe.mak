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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeSampleCode/MdesStatusCodeDxe/MdesStatusCodeDxe.mak 1     4/06/12 8:57a Klzhan $
#
# $Revision: 1 $
#
# $Date: 4/06/12 8:57a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeSampleCode/MdesStatusCodeDxe/MdesStatusCodeDxe.mak $
# 
# 1     4/06/12 8:57a Klzhan
# 
# 4     3/27/12 5:17a Klzhan
# Correct TYPE of this modulepart.
# 
# 3     10/19/11 9:19a Calvinchen
# [TAG]  		EIP65695
# [Category]  	Bug Fix
# [Severity]  	Normal
# [Symptom]  	Support HECI protocol in SMM for ME 8.0
# [Solution]  	Removed "EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB" from Make
# file.
# 
# 2     9/27/11 5:03a Klzhan
# Fix build error
# 
# 1     9/27/11 4:46a Klzhan
# 
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            MdesStatusCodeDrv.mak
#
# Description:     Mdes Status Code driver
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
all : MdesStatusCodeDrv

MdesStatusCodeDrv : $(BUILD_DIR)\MdesStatusCodeDxe.mak MdesStatusCodeDrvBin

$(BUILD_DIR)\MdesStatusCodeDxe.mak : $(MdesStatusCodeDrv_DIR)\$(@B).cif $(MdesStatusCodeDrv_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(MdesStatusCodeDrv_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)


MdesStatusCodeDrv_INCLUDES=\
  $(EDK_INCLUDES)\
  $(ME_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(EdkIIGlueInclude)\
  $(IndustryStandard_INCLUDES)\
  -I$(MeProtocolLib_DIR)\
  -I$(INTEL_COUGAR_POINT_INCLUDE_DIR)

MdesStatusCodeDrv_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=MdesStatusCodeDrvEntryPoint"\
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__  


MdesStatusCodeDrv_LIB_LINKS =\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(INTEL_PCH_PROTOCOL_LIB)\
  $(EdkIIGlueBasePrintLib_LIB) \
  $(EdkIIGlueUefiLib_LIB)\
  $(TdtProtocolLib_LIB)\
  $(ProtocolLib_LIB)\
  $(EFISCRIPTLIB)\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(AmtGuidLib_LIB)\
  $(EFIGUIDLIB)\
  $(EDKPROTOCOLLIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGluePeiDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EFIDRIVERLIB)\
  $(EdkIIGlueDxeServicesTableLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(MeProtocolLib_LIB)
# MAK file for the eModule:TdtDxe

MdesStatusCodeDrvBin : $(MdesStatusCodeDrv_LIB_LINKS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\MdesStatusCodeDxe.mak all\
		"MY_INCLUDES=$(MdesStatusCodeDrv_INCLUDES)"\
        	"MY_DEFINES=$(MdesStatusCodeDrv_DEFINES)"\
		GUID=df5cd25a-8e55-46ba-8cda-bc7db7bf9c64 \
		ENTRY_POINT=_ModuleEntryPoint \
		TYPE=BS_DRIVER \
        	EDKIIModule=DXEDRIVER\
		DEPEX1=$(MdesStatusCodeDrv_DIR)\MdesStatusCodeDxe.dxs \
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