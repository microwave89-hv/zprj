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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Smbios131/Smbios131.mak 5     12/18/12 2:29a Klzhan $
#
# $Revision: 5 $
#
# $Date: 12/18/12 2:29a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/ME/MeWrapper/Smbios131/Smbios131.mak $
# 
# 5     12/18/12 2:29a Klzhan
# [TAG]  		EIP109707
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update ME RC 0.81
# [Files]  		Smbios131.sdl
# Smbios131.mak
# Smbios131.c
# Smbios131.dxs
# Smbios131.h
# Smbios131.cif
# 
# 4     7/02/12 11:38p Klzhan
# [TAG]  		EIP94113
# [Category]  	Spec Update
# [Severity]  	Important
# [Description]  	Update ME RC0.6
# [Files]  		Smbios131.sdl
# Smbios131.mak
# Smbios131.c
# Smbios131.dxs
# Smbios131.h
# Smbios131.cif
# 
# 3     4/24/12 12:32a Klzhan
# Update modulepart to latest
# 
# 2     2/23/12 8:57a Klzhan
# Support New EDK
# 
# 1     2/08/12 1:07a Klzhan
# Initial Check in 
# 
# 3     7/26/11 9:57a Klzhan
# Create token for some Bios capabilities parameters.
# 
# 2     7/26/11 8:37a Klzhan
# [TAG]  		EIP64542
# [Category]  	Improvement
# [Description]  	Replace Getvariable by GetNbSetupdata.
# [Files]  		Smbios131.sdl
# Smbios131.mak
# Smbios131.c
# Smbios131.dxs
# Smbios131.h
# Smbios131.cif
# 
# 1     2/25/11 1:40a Klzhan
# Initial Check-in
# 
# 1     12/03/10 5:09a Klzhan
# Initial Check-in.
# 
#
#**********************************************************************
#
#<AMI_FHDR_START>
#----------------------------------------------------------------------------
#
# Name:            Smbios131.c
#
# Description:     Create SMbios type 131.
#
#----------------------------------------------------------------------------
#<AMI_FHDR_END>
# MAK file for the ModulePart:AmtSmbios
all : AmtSmbios131

$(BUILD_DIR)\Smbios131.mak : $(Smbios131_DIR)\$(@B).cif $(Smbios131_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(Smbios131_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

AmtSmbios131 : $(BUILD_DIR)\Smbios131.mak AmtSmbios131Bin

AmtSmbios131_INCLUDES=\
    $(EdkIIGlueLib_INCLUDES)\
    $(INTEL_PLATFORM_PROTOCOL_INCLUDES)\
    /I$(EDK_SOURCE)\Foundation\Efi\Include\
    $(NB_INCLUDES)\
    $(ME_INCLUDES)\
    $(INTEL_PCH_INCLUDES)\
    $(INTEL_MCH_INCLUDES)\
    /I$(MePlatformPolicy_DIR)\
    /I$(PROJECT_DIR)\
    /IInclude\

AmtSmbios131_LIBS=\
  $(AmtLibDxe_LIB)\
  $(MeLibDxe_LIB)\
  $(MeChipsetDxeLib_LIB)\
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
  $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
  $(EdkIIGlueUefiLib_LIB)\
  $(IntelPlatformProtocolLib_LIB)\
  $(PchPlatformDxeLib_LIB)\
  
AmtSmbios131Bin : $(AmtSmbios131_LIBS)
	$(MAKE) /$(MAKEFLAGS) $(EDK_DEFAULTS)\
		/f $(BUILD_DIR)\Smbios131.mak all \
        NAME=Smbios131 \
        MAKEFILE=$(BUILD_DIR)\Smbios131.mak \
		"MY_INCLUDES=$(AmtSmbios131_INCLUDES)" \
		GUID=2b341c7b-0b32-4a65-9d46-e1b3abd4c25c \
		ENTRY_POINT=AmtSmbios131EntryPoint \
		DEPEX1=$(Smbios131_DIR)\Smbios131.dxs \
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
