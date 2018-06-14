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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSetup/AmtSetup.mak 3     4/24/12 12:38a Klzhan $
#
# $Revision: 3 $
#
# $Date: 4/24/12 12:38a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/AmtWrapper/AmtSetup/AmtSetup.mak $
# 
# 3     4/24/12 12:38a Klzhan
# Update modulepart to latest
# 
# 2     2/23/12 8:58a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:08a Klzhan
# Initial Check in 
# 
# 2     7/14/11 7:45a Klzhan
# Add "Disable ME" setup item.
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
# Name:		AMTSetup.sd
#
# Description:	AMT TSE makfile.
#
#---------------------------------------------------------------------------
#<AMI_FHDR_END>

#---------------------------------------------------------------------------
#		Create AMT Setup Screens
#---------------------------------------------------------------------------
All : AmtSetup

AmtSetup : $(BUILD_DIR)\AmtSetup.mak AmtSetupBin
#AmtSetup : $(BUILD_DIR)\AmtSetup.mak AmtSetupBin
AmtTseFunc_lib : $(BUILD_DIR)\AmtSetup.mak AmtTseSetupBin


SetupSdbs : $(BUILD_DIR)\AmtSetup.sdb

$(BUILD_DIR)\AmtSetup.sdb : $(AMT_SETUP_DIR)\$(@B).sd $(AMT_SETUP_DIR)\$(@B).uni
	$(STRGATHER) -i INCLUDE -parse -newdb -db $(BUILD_DIR)\$(@B).sdb $(AMT_SETUP_DIR)\$(@B).uni
	$(STRGATHER) -scan -db $(BUILD_DIR)\$(@B).sdb -od $(BUILD_DIR)\$(@B).sdb $(AMT_SETUP_DIR)\$(@B).sd

$(BUILD_DIR)\AmtSetup.mak : $(AMT_SETUP_DIR)\$(@B).cif $(AMT_SETUP_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMT_SETUP_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtSetup_INCLUDES= \
  $(EDK_INCLUDES) \
  $(MISCFRAMEWORK_INCLUDES) \
  $(ME_INCLUDES) \
  $(IndustryStandard_INCLUDES)\

AmtSetup_CFLAGS=$(CFLAGS) \
	-I $(TSEBIN_DIR)\Inc \
	-I $(TSEBIN_DIR)\
	-I ReferenceCode\ME\Protocol\
	-I Board\EM\MeWrapper\AmtWrapper\Protocol

AmtTseSetup_INCLUDES= \
		/I$(PROJECT_DIR) \
  		$(EDK_INCLUDES) \
  		$(MISCFRAMEWORK_INCLUDES) \
  		$(ME_INCLUDES) \
  		/IInclude\Protocol\
  		/IInclude\IndustryStandard\
  		/IInclude\

SetupData :  $(BUILD_DIR)\AmtTseFunc.obj

$(BUILD_DIR)\AmtTseFunc.obj : $(AMT_SETUP_DIR)\AmtTseFunc.c
		$(CC) $(AmtSetup_CFLAGS) /Fo$(BUILD_DIR)\ $(AMT_SETUP_DIR)\AmtTseFunc.c 

AMT_SETUPLIB_OBJECTS = $(BUILD_DIR)\$(AMT_SETUP_DIR)\AmtTseFunc.obj
AMT_SETUP_OBJECTS    = $(BUILD_DIR)\$(AMT_SETUP_DIR)\AmtSetup.obj

AMT_SETUP_LIBS=\
  $(EFIDRIVERLIB)\
  $(MeLibDxe_LIB)\
  $(EfiScriptLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIPROTOCOLLIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueBaseLib_LIB)\
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EFIGUIDLIB)\
  $(EDKPROTOCOLLIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\

AmtSetupBin : $(AMT_SETUP_LIBS)
		$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\AmtSetup.mak all \
		"MY_INCLUDES=$(AmtSetup_INCLUDES)"\
		GUID=773CB08B-511A-4bd5-85AD-41D4F4B64A52 \
		TYPE=BS_DRIVER \
		"OBJECTS=$(AMT_SETUP_OBJECTS)"\
		ENTRY_POINT=InitializeAmtSetup \
		DEPEX1=$(AMT_SETUP_DIR)\AmtSetup.dxs \
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1

#---------------------------------------------------------------------------
#               Create Restore BIOSExtesionSetup Restore Component
#---------------------------------------------------------------------------
AmtSMIFlashElink : $(BUILD_DIR)\AmtSetup.mak AmtSMIFlashElinkBin

AmtSMIFlashElinkObjs = $(BUILD_DIR)\$(AMT_SETUP_DIR)\AmtSMIFlashElink.obj

AmtSMIFlashElinkBin : $(AMIDXELIB) $(MeGuidLib_LIB)
            $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
            /f $(BUILD_DIR)\AmtSetup.mak all\
            "CFLAGS=$(CFLAGS:/W4=/W3) /I$(MeGuidLib_DIR)" \
            OBJECTS="$(AmtSMIFlashElinkObjs)" \
            NAME=AmtSetup \
            TYPE=LIBRARY LIBRARY_NAME=$(AMT_SMIFLASH_LIB)

$(AMT_SMIFLASH_LIB) : AmtSMIFlashElink
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