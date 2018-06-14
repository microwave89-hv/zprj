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

#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/DPTF/DptfAcpiTables/DptfAcpiTables.mak 5     6/02/13 8:18a Joshchou $
#
# $Revision: 5 $
#
# $Date: 6/02/13 8:18a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/DPTF/DptfAcpiTables/DptfAcpiTables.mak $
# 
# 5     6/02/13 8:18a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change IASL compiler path to
# $(ACPIPLATFORM_ASL_COMPILER) in SharkBay project.
# 
# 4     1/28/13 10:02p Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Change the build tool path.
# 
# 3     11/20/12 4:24a Joshchou
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Create Token for OEM clone
# 
# 2     9/26/12 1:58a Victortu
# 
# 1     4/24/12 9:25a Victortu
# Intel DPTF initialization.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: DptfAcpiTables.mak
#
# Description: MAke file to build Intel DPTF ACPI ASL components
#
#<AMI_FHDR_END>
#**********************************************************************
#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
EDK : DPTFACPI

ALLDPTFSEC = $(BUILD_DIR)\Dptf.sec

DPTFACPI : $(BUILD_DIR)\DptfAcpiTables.ffs

$(BUILD_DIR)\Dptf.aml : $(INTEL_DPTF_ASL_FILE)
  $(ASLEXPANDER) $(INTEL_DPTF_ASL_FILE) $(BUILD_DIR)\Dptf.asl $(PROJECT_CPU_ROOT)\Include
  $(IASL) -p $(BUILD_DIR)\Dptf.aml $(BUILD_DIR)\Dptf.asl

$(BUILD_DIR)\Dptf.sec: $(BUILD_DIR)\Dptf.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\DptfAcpiTables.ffs: $(ALLDPTFSEC) $(INTEL_DPTF_ACPI_TABLE_DIR)\DptfAcpiTables.mak
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\DptfAcpiTables.pkg
PACKAGE.INF
[.]
BASE_NAME                   = DptfAcpiTables
FFS_FILEGUID                = EA139578-FEA0-4dd2-91B5-6953819EF1E4
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
            $(PROJECT_DIR)\$(BUILD_DIR)\Dptf.sec
  }
}
<<KEEP
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
