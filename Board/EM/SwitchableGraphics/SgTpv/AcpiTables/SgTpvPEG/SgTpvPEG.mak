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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/SgTpvPEG.mak 2     6/02/13 8:13a Joshchou $
#
# $Revision: 2 $
#
# $Date: 6/02/13 8:13a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/SgTpvPEG/SgTpvPEG.mak $
# 
# 2     6/02/13 8:13a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change IASL compiler path to
# $(ACPIPLATFORM_ASL_COMPILER) in SharkBay project.
# 
# 1     1/15/13 5:57a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Create componet for SG ASL code support on PEG 
# [Files]  		SgTpvPEG.cif
# SgTpvPEG.sdl
# SgTpvPEG.mak
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
SGPEGASL: $(BUILD_DIR)\SGTPVssdt.ffs

#-----------------------------------------------------------------------------
#       SG SSDT ACPI Tables
#-----------------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\OpSSDT.aml $(BUILD_DIR)\NvSSDT.aml $(BUILD_DIR)\AtiSSDT.aml: $(BUILD_DIR)\OpSSDT.asl $(BUILD_DIR)\NvSSDT.asl $(BUILD_DIR)\AtiSSDT.asl
	$(SILENT)$(IASL) -p $@ $*.asl

$(BUILD_DIR)\OpSSDT.sec $(BUILD_DIR)\NvSSDT.sec $(BUILD_DIR)\ATIssdt.sec: $(BUILD_DIR)\OpSSDT.aml $(BUILD_DIR)\NvSSDT.aml $(BUILD_DIR)\AtiSSDT.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with multiple SG SSDT tables. 
# DXE phase will load the tables depending on present Mxm Gfx card 
# and update Aml contents if provided in AcpiTables.c
$(BUILD_DIR)\SGTPVssdt.ffs: $(BUILD_DIR)\OpSSDT.sec $(BUILD_DIR)\NvSSDT.sec $(BUILD_DIR)\AtiSSDT.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\SGTPVssdt.pkg

PACKAGE.INF
[.]
BASE_NAME                   = SgTpvACPI
FFS_FILEGUID                = 6A061113-FE54-4A07-A28E-0A69359EB069
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\OpSSDT.sec
	$(PROJECT_DIR)\$(BUILD_DIR)\NvSSDT.sec
	$(PROJECT_DIR)\$(BUILD_DIR)\AtiSSDT.sec
  }
}
<<KEEP
#-----------------------------------------------------------------------#
#		Process SG asl files
#-----------------------------------------------------------------------#
$(BUILD_DIR)\OpSSDT.asl $(BUILD_DIR)\NvSSDT.asl $(BUILD_DIR)\AtiSSDT.asl : $(INTEL_OPSSDT_ASL_FILE) $(INTEL_NVSSDT_ASL_FILE) $(INTEL_ATISSDT_ASL_FILE)
    $(CP) /I$(SG_TPVPEG_DIR) /FItoken.h /C $(SG_TPVPEG_DIR)\$(@F) > $@
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
