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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSmbios/AmtSmbios.mak 2     2/23/12 8:59a Klzhan $
#
# $Revision: 2 $
#
# $Date: 2/23/12 8:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSmbios/AmtSmbios.mak $
# 
# 2     2/23/12 8:59a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:09a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:44a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:11a Klzhan
# Initial Check-in.
#
#**********************************************************************
#
#<AMI_FHDR_START>
#---------------------------------------------------------------------------
# Name:		AMTSmbios.dxs
#
# Description:	AMT Smbios Makfile.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>
# MAK file for the ModulePart:AmtSmbios
all : AmtSmbios

$(BUILD_DIR)\AmtSmbios.mak : $(AmtSmbios_DIR)\$(@B).cif $(AmtSmbios_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AmtSmbios_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtSmbios : $(BUILD_DIR)\AmtSmbios.mak AmtSmbiosBin

AmtSmbios_INCLUDES=\
    $(ME_INCLUDES)\
    $(EDK_INCLUDES)\
    $(EdkIIGlueLib_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    $(NB_INCLUDES)\
    /I$(BOARD_DIR) \
    $(MISCFRAMEWORK_INCLUDES)\


AmtSmbios_LIBS=\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(EDKPROTOCOLLIB)\
  $(EFIDRIVERLIB)\
  $(CPUIA32LIB)\
  $(VaProtocolLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueUefiLib_LIB)\

AmtSmbiosBin : $(AmtSmbios_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AmtSmbios.mak all \
        NAME=AmtSmbios \
        MAKEFILE=$(BUILD_DIR)\AmtSmbios.mak \
		"MY_INCLUDES=$(AmtSmbios_INCLUDES)" \
		GUID=A8C67255-E029-4b1a-968E-ECA6E9C11C73 \
		ENTRY_POINT=AmtSmbiosEntryPoint \
		DEPEX1=$(AmtSmbios_DIR)\AmtSmbios.dxs \
        DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		TYPE=BS_DRIVER \
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