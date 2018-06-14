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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePciPlatform/MePciPlatform.mak 3     9/27/12 4:52a Klzhan $
#
# $Revision: 3 $
#
# $Date: 9/27/12 4:52a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/MePciPlatform/MePciPlatform.mak $
# 
# 3     9/27/12 4:52a Klzhan
# [TAG]  		EIP102254
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update ME RC 0.7
# 
# 2     2/23/12 8:57a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:05a Klzhan
# Initial Check in 
# 
# 1     2/25/11 1:41a Klzhan
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
# Name:            MePciPlatform.h
#
# Description:     
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
All : MePciPlatform

MePciPlatform : $(BUILD_DIR)\MePciPlatform.mak MePciPlatformBin

$(BUILD_DIR)\MePciPlatform.mak : $(MePciPlatform_DIR)\$(@B).cif $(MePciPlatform_DIR)\$(@B).mak $(BUILD_RULES)
        $(CIF2MAK) $(MePciPlatform_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MePciPlatform_INCLUDES=\
  $(EDK_INCLUDES) \
  $(ME_INCLUDES) \
  $(MISCFRAMEWORK_INCLUDES) \
  $(NB_INCLUDES)\
  $(SB_INCLUDES)\
  $(EdkIIGlueLib_INCLUDES)\
  $(INTEL_PCH_INCLUDES)\

MePciPlatform_LIBS=\
  $(EFIDRIVERLIB)\
  $(MeProtocolLib_LIB)\
  $(MeLibDxe_LIB)\
  $(EdkIIGlueBaseLib_LIB)\
!IF "$(x64_BUILD)"=="1"
  $(EdkIIGlueBaseLibX64_LIB)\
!ELSE
  $(EdkIIGlueBaseLibIA32_LIB)\
!ENDIF
  $(EdkIIGlueDxeReportStatusCodeLib_LIB)\
  $(EdkIIGlueDxeDebugLibReportStatusCode_LIB)\
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EDKFRAMEWORKPROTOCOLLIB)\

DxeCpuBuildDefine = \
!IF "$(x64_BUILD)"=="1" 
  /DMDE_CPU_X64\
!ELSE
  /DMDE_CPU_IA32\
!ENDIF

MePciPlatform_DEFINES = \
            $(DxeCpuBuildDefine)\

MePciPlatformBin : $(MePciPlatform_LIBS) 
        $(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
                /f $(BUILD_DIR)\MePciPlatform.mak all\
                GUID=459C70C3-9344-4484-9F93-7822530D0D11\
                "MY_INCLUDES = $(MePciPlatform_INCLUDES)" \
                "MY_DEFINES=$(MePciPlatform_DEFINES)"\
                ENTRY_POINT=MePciPlatformEntryPoint\
                DEPEX1=$(MePciPlatform_DIR)\MePciPlatform.dxs\
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
