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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMSSDT.mak 4     6/02/13 8:15a Joshchou $
#
# $Revision: 4 $
#
# $Date: 6/02/13 8:15a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/SwitchableGraphics/Sg TPV/Sg Acpi Tables/OEMSSDT/OEMSSDT.mak $
# 
# 4     6/02/13 8:15a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change IASL compiler path to
# $(ACPIPLATFORM_ASL_COMPILER) in SharkBay project.
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
all : BuildOEMSSDT

BuildOEMSSDT : $(BUILD_DIR)\OEMSSDT.ffs

#---------------------------------------------------------------------------
#			Generic AcpiPlatform dependencies
#---------------------------------------------------------------------------
$(BUILD_DIR)\OEMSSDT.mak : $(SG_OEMSSDT_DIR)\OEMSSDT.cif $(BUILD_RULES)
	$(CIF2MAK) $(SG_OEMSSDT_DIR)\OEMSSDT.cif $(CIF2MAK_DEFAULTS)


#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\OEMSSDT.aml : $(BUILD_DIR)\OEMSSDT.asl 
#    @cl /C /EP $(AOACACPI_ASL_FILE) > $(BUILD_DIR)\AoacAcpi.asl
#	$(IASL) -p $(BUILD_DIR)\OEMSSDT.aml $(SGOEMSSDT_ASL_FILE)
	$(IASL) -p $@ $*.asl

$(BUILD_DIR)\OEMSSDT.sec: $(BUILD_DIR)\OEMSSDT.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with OEMSSDT tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in SgTpvAcpiTables.c

$(BUILD_DIR)\OEMSSDT.ffs: $(BUILD_DIR)\OEMSSDT.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\OEMSSDT.pkg

PACKAGE.INF
[.]
BASE_NAME                   = OEMSSDT
FFS_FILEGUID                = 5B232086-350A-42c7-A70E-3497B5765D85
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\OEMSSDT.sec
  }
}
<<KEEP

#-----------------------------------------------------------------------#
#		Process SG asl files
#-----------------------------------------------------------------------#
$(BUILD_DIR)\OEMSSDT.asl : $(SGOEMSSDT_ASL_FILE)
    $(CP) /I$(SG_OEMSSDT_DIR) /FItoken.h /C $(SG_OEMSSDT_DIR)\$(@F) > $@
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
