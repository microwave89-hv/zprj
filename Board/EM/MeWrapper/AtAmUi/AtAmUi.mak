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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/ATAMUI/AtAmUi.mak 1     8/29/12 3:02a Klzhan $
#
# $Revision: 1 $
#
# $Date: 8/29/12 3:02a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/ATAMUI/AtAmUi.mak $
# 
# 1     8/29/12 3:02a Klzhan
# [TAG]  		EIPNone
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Support AT5
# [Files]  		AtAmUi.cif
# AtAmUi.dxs
# AtAmUi.mak
# AtAmUi.sdl
# AtAmUi.c
# AtAmUi.h
# AtAmUiString.c
# AtAmUiString.h
# 
# 2     2/23/12 8:58a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:08a Klzhan
# Initial Check in 
# 
# 2     9/15/11 2:12a Klzhan
# Remove AMI Lib.
# 
# 1     2/25/11 1:43a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:10a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            AmtWrapperDxe.mak
#
# Description:     Makfile for Amt Wrapper Dxe module
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
EDK : AtAmUi

AtAmUi : $(BUILD_DIR)\AtAmUi.mak AtAmUiBin

$(BUILD_DIR)\AtAmUi.mak : $(AtAmUi_DIR)\AtAmUi.mak $(BUILD_RULES)
	$(CIF2MAK) $(AtAmUi_DIR)\AtAmUi.cif $(CIF2MAK_DEFAULTS)

AtAmUi_INCLUDES=\
    $(EDK_INCLUDES)\
    $(MISCFRAMEWORK_INCLUDES)\
    $(ME_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(IndustryStandard_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    /IInclude\
    $(NB_INCLUDES)\
    /I$(AtAmDxe_DIR)\
    /I$(AtDxeLib_DIR)\

AtAmUi_LIBS=\
  $(EFISCRIPTLIB)\
  $(EFIDRIVERLIB)\
  $(EFICOMMONLIB)\
  $(PRINTLIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIGUIDLIB)\
  $(AmtProtocolLib_LIB)\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(AmtGuidLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueDxeServicesTableLib_LIB)\
  $(EdkIIGlueBasePrintLib_LIB) \
  $(AtDxeLib_LIB)\
  
AtAmUi_DEFINES = $(MY_DEFINES)\
  /D"__EDKII_GLUE_MODULE_ENTRY_POINT__=AtAmUiEntryPoint"\
  /D __EDKII_GLUE_DXE_REPORT_STATUS_CODE_LIB__ \
  /D __EDKII_GLUE_DXE_DEBUG_LIB_REPORT_STATUS_CODE__ \
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\
  /D __EDKII_GLUE_BASE_PCI_LIB_PCI_EXPRESS__ \
  /D __EDKII_GLUE_BASE_LIB__ \
  /D __EDKII_GLUE_BASE_MEMORY_LIB__ \
  /D __EDKII_GLUE_UEFI_DEVICE_PATH_LIB__ \
  /D __EDKII_GLUE_UEFI_LIB__\
  /D __EDKII_GLUE_DXE_MEMORY_ALLOCATION_LIB__ \


AtAmUiBin : $(AtAmUi_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AtAmUi.mak all\
		GUID=D2BC3092-92BB-4B21-A26B-CE6f7C3E9857\
		"MY_INCLUDES=$(AtAmUi_INCLUDES)" \
        	"MY_DEFINES=$(AtAmUi_DEFINES)"\
		ENTRY_POINT=AtAmUiEntryPoint\
		DEPEX1=$(AtAmUi_DIR)\AtAmUi.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
		TYPE=BS_DRIVER\
		COMPRESS=1

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
