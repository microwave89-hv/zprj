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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AmtWrapperDxe.mak 2     2/23/12 8:58a Klzhan $
#
# $Revision: 2 $
#
# $Date: 2/23/12 8:58a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtWrapperDxe/AmtWrapperDxe.mak $
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
EDK : AmtWrapperDxe

AmtWrapperDxe : $(BUILD_DIR)\AmtWrapperDxe.mak AmtWrapperDxeBin

$(BUILD_DIR)\AmtWrapperDxe.mak : $(AmtWrapperDxe_DIR)\$(@B).cif $(AmtWrapperDxe_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmtWrapperDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtWrapperDxe_INCLUDES=\
	$(EDK_INCLUDES)\
	$(MISCFRAMEWORK_INCLUDES)\
	$(ME_INCLUDES)\
	$(INTEL_MCH_INCLUDES)\
	$(INTEL_PCH_INCLUDES)\
	$(IndustryStandard_INCLUDES)\
        $(EdkIIGlueLib_INCLUDES)\
        /IInclude\
        $(NB_INCLUDES)


AmtWrapperDxe_LIBS=\
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
  
AmtWrapperDxeBin : $(AmtWrapperDxe_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AmtWrapperDxe.mak all\
		GUID=D77C900D-A1C7-41c5-B989-0C3D37FCA432\
		"MY_INCLUDES=$(AmtWrapperDxe_INCLUDES)" \
		ENTRY_POINT=AmtWrapperDxeEntryPoint\
		DEPEX1=$(AmtWrapperDxe_DIR)\AmtWrapperDxe.dxs\
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
