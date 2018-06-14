#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/Wdt/WdtPei/WdtPei.mak 2     2/24/12 2:32a Victortu $
#
# $Revision: 2 $
#
# $Date: 2/24/12 2:32a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/Wdt/WdtPei/WdtPei.mak $
# 
# 2     2/24/12 2:32a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:33a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
EDK : WdtPei
WdtPei : $(BUILD_DIR)\WdtPei.mak WdtPeiBin

$(BUILD_DIR)\WdtPei.mak : $(WdtPei_DIR)\$(@B).cif $(BUILD_RULES)
  $(CIF2MAK) $(WdtPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

WdtPei_INCLUDES=\
	$(EdkIIGlueLib_INCLUDES)\
	$(INTEL_PCH_INCLUDES)\
	$(WdtCommonLib_INCLUDES)\

WdtPei_DEFINES=$(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=WdtPeiEntryPoint"\
  /D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
  /D __EDKII_GLUE_PEI_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_PEI_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_PEI_SERVICES_LIB__ \
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_PEI_HOB_LIB__ \
!IF "$(WDT_SUPPORT_ENABLED)"=="1"
  /D WDT_SUPPORT_ENABLED
!ENDIF

WdtPei_LIBS =\
  $(IntelPchPpiLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueBaseLibIA32_LIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGluePeiDebugLibReportStatusCode_LIB)\
  $(EdkIIGluePeiReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiServicesLib_LIB) \
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(WdtCommonPeiLib_LIB)\
  $(EDKFRAMEWORKPPILIB)\
  $(EdkIIGluePeiHobLib_LIB)

WdtPeiBin : $(WdtPei_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) \
		/f $(BUILD_DIR)\WdtPei.mak all \
		"MY_INCLUDES = $(WdtPei_INCLUDES)" \
		"MY_DEFINES = $(WdtPei_DEFINES)" \
		GUID=1D88C542-9DF7-424a-AA90-02B61F286938 \
		ENTRY_POINT=_ModuleEntryPoint \
		EDKIIModule=PEIM\
		TYPE=PEIM \
		DEPEX1=$(WdtPei_DIR)\WdtPei.dxs \
		DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
		COMPRESS=0

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
