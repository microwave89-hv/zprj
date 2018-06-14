#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi S3 Save/SgTpvAcpiS3Save.mak 4     1/15/13 5:06a Joshchou $
#
# $Revision: 4 $
#
# $Date: 1/15/13 5:06a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi S3 Save/SgTpvAcpiS3Save.mak $
# 
# 4     1/15/13 5:06a Joshchou
# [TAG]  		EIP107237
# [Category]  	New Feature
# [Description]  	Support  SG function onULT platform.
# 
# 3     10/16/12 4:46a Joshchou
# [TAG]  		None
# [Category]  	New Feature
# [Description]  	Update for SA and ACPI RC 0.7.1
# [Files]  		SgTpvAcpiS3Save.mak
# 
# 2     9/09/12 10:53p Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Tpv module support for sharkbay.
# [Files]  		SgTpvAcpiS3Save.mak
# SgTpvAcpiS3Save.c
# SgTpvAcpiS3Save.dxs
# 
# 1     6/27/11 5:27a Alanlin
# [TAG]  		EIP61848
# [Category]  	New Feature
# [Description]  	Initial check-in.Integrated SwitchableGraphics Intel
# Reference code 0.6.0
# [Files]  		SgTpvAcpiS3Save.cif
# SgTpvAcpiS3Save.sdl
# SgTpvAcpiS3Save.mak
# SgTpvAcpiS3Save.c
# SgTpvAcpiS3Save.dxs
# 
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: SgTpvAcpiS3Save.mak
#
# Description: Make file to build SG TPV ACPI components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
SgTpv : SgTpvAcpiS3Save

SgTpvAcpiS3Save: $(BUILD_DIR)\SgTpvAcpiS3Save.mak SgTpvAcpiS3SaveBin

#---------------------------------------------------------------------------
#			Generic SgTpvAcpiTables dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\SgTpvAcpiS3Save.mak : $(SGTPV_ACPIS3_DIR)\SgTpvAcpiS3Save.cif $(BUILD_RULES)
	$(CIF2MAK) $(SGTPV_ACPIS3_DIR)\SgTpvAcpiS3Save.cif $(CIF2MAK_DEFAULTS)


#---------------------------------------------------------------------------
#		Create SgTpvAcpiS3Save DXE Component
#---------------------------------------------------------------------------
                              
SgTpvAcpiS3SaveBin :  $(AMIDXELIB) $(AMICSPLib) $(INTEL_SA_PROTOCOL_LIB) $(CpuPlatformLib_LIB) $(PchPlatformSmmLib_LIB) 
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\SgTpvAcpiS3Save.mak all\
		GUID=C18B8105-AB89-44de-8D37-50B31FAE5D1E\
		"MY_INCLUDES= $(ACPI_PLATFORM_INCLUDES) $(PLATFORM_INFO_INCLUDES) $(PROJECT_CPU_INCLUDES) /I $(INTEL_SA_PROTOCOL_LIB_DIR)"\
		ENTRY_POINT=SgTpvAcpiS3Save_Init\
		OBJECTS="$(SgTpvAcpiS3Save_OBJECTS)" \
		TYPE=BS_DRIVER \
		DEPEX1=$(SGTPV_ACPIS3_DIR)\SgTpvAcpiS3Save.dxs\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX\
		COMPRESS=1


#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
