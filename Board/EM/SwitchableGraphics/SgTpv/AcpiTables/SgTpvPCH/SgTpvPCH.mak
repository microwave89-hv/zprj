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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPCH/SgTpvPCH.mak 2     6/02/13 8:14a Joshchou $
#
# $Revision: 2 $
#
# $Date: 6/02/13 8:14a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPCH/SgTpvPCH.mak $
# 
# 2     6/02/13 8:14a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change IASL compiler path to
# $(ACPIPLATFORM_ASL_COMPILER) in SharkBay project.
# 
# 1     1/15/13 6:01a Joshchou
# [TAG]  		EIP107237
# [Category]  	Improvement
# [Description]  	Create componet for SG support on PCH
# [Files]  		SgTpvPCH.cif
# SgTpvPCH.sdl
# SgTpvPCH.mak
# 
# 3     11/20/12 3:48a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Create Token for OEM clone
# 
# 2     9/09/12 11:01p Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Tpv module support for sharkbay.
# [Files]  		OEMSSDT.mak
# OEMSSDT.asl
# OEMNVdGPU.asl
# OEMNViGPU.asl
# OEMNViGDmisc.asl
# OEMNvVentura.asl
# OEMNvGPS.asl
# OEMSSDT.cif
# 
# 1     12/12/11 9:10p Alanlin
# 
# 
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: OEMSSDT.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
SGPCHASL: $(BUILD_DIR)\SGTPVPCHssdt.ffs


#-----------------------------------------------------------------------------
#       SG SSDT ACPI Tables
#-----------------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\OpSSDTPCH.aml $(BUILD_DIR)\NvSSDTPCH.aml $(BUILD_DIR)\AtiSSDTPCH.aml: $(BUILD_DIR)\OpSSDTPCH.asl $(BUILD_DIR)\NvSSDTPCH.asl $(BUILD_DIR)\AtiSSDTPCH.asl
	$(SILENT)$(IASL) -p $@ $*.asl

$(BUILD_DIR)\OpSSDTPCH.sec $(BUILD_DIR)\NvSSDTPCH.sec $(BUILD_DIR)\ATIssdtPCH.sec: $(BUILD_DIR)\OpSSDTPCH.aml $(BUILD_DIR)\NvSSDTPCH.aml $(BUILD_DIR)\AtiSSDTPCH.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with multiple SG SSDT tables. 
# DXE phase will load the tables depending on present Mxm Gfx card 
# and update Aml contents if provided in AcpiTables.c
$(BUILD_DIR)\SGTPVPCHssdt.ffs: $(BUILD_DIR)\OpSSDTPCH.sec $(BUILD_DIR)\NvSSDTPCH.sec $(BUILD_DIR)\AtiSSDTPCH.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\SGTPVPCHssdt.pkg

PACKAGE.INF
[.]
BASE_NAME                   = SgTpvPCHACPI
FFS_FILEGUID                = 9B65FE7C-855E-43cc-A170-A2A685F3655F
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\OpSSDTPCH.sec
	$(PROJECT_DIR)\$(BUILD_DIR)\NvSSDTPCH.sec
	$(PROJECT_DIR)\$(BUILD_DIR)\AtiSSDTPCH.sec
  }
}
<<KEEP
#-----------------------------------------------------------------------#
#		Process SG asl files
#-----------------------------------------------------------------------#
$(BUILD_DIR)\OpSSDTPCH.asl $(BUILD_DIR)\NvSSDTPCH.asl $(BUILD_DIR)\AtiSSDTPCH.asl : $(INTEL_OPSSDTPCH_ASL_FILE) $(INTEL_NVSSDTPCH_ASL_FILE) $(INTEL_ATISSDTPCH_ASL_FILE)
    $(CP) /I$(SG_TPVPCH_DIR) /FItoken.h /C $(SG_TPVPCH_DIR)\$(@F) > $@
# include the token.h if needed to check for SDL flags
#  /FItoken.h

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
