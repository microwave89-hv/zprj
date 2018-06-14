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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/Wdt/WdtDxe/WdtDxe.mak 3     9/26/12 3:43a Victortu $
#
# $Revision: 3 $
#
# $Date: 9/26/12 3:43a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/Wdt/WdtDxe/WdtDxe.mak $
# 
# 3     9/26/12 3:43a Victortu
# Lynx Point PCH Chipset Framework Reference Code Beta 0.7.0
# 
# 2     2/24/12 2:31a Victortu
# Updated to support 4.6.5.3_IntelEDK_1117_Patch7_00.
# 
# 1     2/08/12 9:32a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
EDK : WdtDxe
WdtDxe : $(BUILD_DIR)\WdtDxe.mak WdtDxeBin

$(BUILD_DIR)\WdtDxe.mak : $(WdtDxe_DIR)\$(@B).cif $(BUILD_RULES)
  $(CIF2MAK) $(WdtDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

WdtDxe_INCLUDES=\
	$(EdkIIGlueLib_INCLUDES)\
	$(INTEL_PCH_INCLUDES)\
	$(WdtCommonLib_INCLUDES)

WdtDxe_LIBS=\
!IF "$(x64_BUILD)"=="1"
	$(EdkIIGlueBaseLibX64_LIB)\
!ELSE
	$(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
	$(EdkIIGlueBaseIoLibIntrinsic_LIB)\
	$(EdkIIGlueBaseMemoryLib_LIB)\
	$(EdkIIGlueBasePciLibPciExpress_LIB)\
	$(EdkIIGlueDxeReportStatusCodeLib_LIB)\
	$(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
	$(EdkIIGlueUefiBootServicesTableLib_LIB)\
    $(EdkIIGlueDxeServicesTableLib_LIB)\
    $(EDKPROTOCOLLIB)\
    $(EdkIIGlueDxeHobLib_LIB)\
	$(INTEL_PCH_PROTOCOL_LIB)\
	$(EFIGUIDLIB)\
	$(WdtCommonDxeLib_LIB)

WdtDxe_DEFINES=\
	$(MY_DEFINES)\
	/D"__EDKII_GLUE_MODULE_ENTRY_POINT__=WdtDxeEntryPoint"\
	/D __EDKII_GLUE_BASE_IO_LIB_INTRINSIC__ \
	/D __EDKII_GLUE_BASE_MEMORY_LIB__ \
	/D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
	/D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
	/D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
    /D __EDKII_GLUE_DXE_SERVICES_TABLE_LIB__\
    /D __EDKII_GLUE_DXE_HOB_LIB__

WdtDxeBin : $(WdtDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\WdtDxe.mak all\
		"MY_INCLUDES=$(WdtDxe_INCLUDES)"\
		"MY_DEFINES=$(WdtDxe_DEFINES)"\
		GUID=5AAB83E5-F027-4ca7-BFD0-16358CC9E453\
		ENTRY_POINT=_ModuleEntryPoint \
		EDKIIModule=DXEDRIVER\
		TYPE=BS_DRIVER \
		DEPEX1=$(WdtDxe_DIR)\WdtDxe.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1

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
