#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/CSP_MEUD.mak 5     5/14/15 4:33a Tristinchou $
#
# $Revision: 5 $
#
# $Date: 5/14/15 4:33a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/OFBD Intel ME Update/CSP_MEUD/ME80/CSP_MEUD.mak $
# 
# 5     5/14/15 4:33a Tristinchou
# [TAG]  		EIP215437
# [Category]  	New Feature
# [Description]  	ME capsule update support on SharkBay
# 
# 4     8/23/13 4:14a Tristinchou
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	Fix build error with CrescentBay project.
# 
# 3     9/07/12 4:46a Klzhan
# Support ME 9.
# 
# 2     3/08/12 6:00a Klzhan
# Support AFU new command
# 
# 1     4/22/11 2:47a Klzhan
# Initial check - in
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	CSP_MEUD.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
#---------------------------------------------------------------------------
#		Create CSP ME FW Update Component
#---------------------------------------------------------------------------
all : CSP_MEUD

CSP_MEUD : $(BUILD_DIR)\CSP_MEUD.mak CSP_MEUDBin

$(BUILD_DIR)\CSP_MEUD.mak : $(MEUD_CSP_DIR)\CSP_MEUD.cif $(MEUD_CSP_DIR)\CSP_MEUD.mak $(BUILD_RULES)
	$(CIF2MAK) $(MEUD_CSP_DIR)\CSP_MEUD.cif $(CIF2MAK_DEFAULTS)

CSP_MEUD_DEFINES=\
  $(MY_DEFINES) /D __EDKII_GLUE_BASE_MEMORY_LIB__\
  /D __EDKII_GLUE_EDK_DXE_RUNTIME_DRIVER_LIB__\
  /D __EDKII_GLUE_UEFI_BOOT_SERVICES_TABLE_LIB__\

CSP_MEUD_INCLUDES = \
  $(EdkIIGlueLib_INCLUDES)\
  $(ME_INCLUDES) \
  $(EdkIIGlueLib_INCLUDES) \
  $(ME_INCLUDES) \
  $(MeLibSmm_DIR) \
  $(MeProtocolLib_DIR) \
  $(MeProtocolLib_DIR)\SmmHeci \
  /I$(PROJECT_DIR)\Core\EM\OFBD\
!IFDEF INTEL_COUGAR_POINT_INCLUDE_DIR
  /I$(INTEL_COUGAR_POINT_INCLUDE_DIR)
!ELSE
  /I$(INTEL_PCH_INCLUDE_DIR)
!ENDIF


CSP_MEUD_LIBS=\
  $(MeLibSmm_LIB)\
  $(EfiScriptLib_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\
  $(EFIPROTOCOLLIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGluePeiDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueUefiBootServicesTableLib_LIB)\
  $(EdkIIGlueUefiDevicePathLib_LIB)\
  $(EdkIIGlueBasePciLibPciExpress_LIB)\
  $(EdkIIGlueBasePciExpressLib_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EFIGUIDLIB)\
  $(EDKPROTOCOLLIB)\
  $(EdkIIGlueBaseIoLibIntrinsic_LIB)\
  $(EdkIIGlueBaseMemoryLib_LIB)\
  $(EdkIIGlueEdkDxeRuntimeDriverLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(EdkIIGlueDxeHobLib_LIB)\

CSP_MEUDBin : $(CSP_MEUD_LIBS)
	@set INCLUDE=%%INCLUDE%%
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
	/f $(BUILD_DIR)\CSP_MEUD.mak all\
	"MY_INCLUDES=$(CSP_MEUD_INCLUDES)" \
	"MY_DEFINES=$(CSP_MEUD_DEFINES)"\
        NAME=CSP_MEUD \
	TYPE=LIBRARY LIBRARY_NAME=$(CSP_MEUDLIB)

$(CSP_MEUDLIB) : CSP_MEUD
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************