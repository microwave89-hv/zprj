#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
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
#<AMI_FHDR_START>
#
# Name: DptfAcpiTablesFfrd.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildDptfAcpiTablesFfrd

BuildDptfAcpiTablesFfrd : $(BUILD_DIR)\DptfAcpiTablesFfrd.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------

$(BUILD_DIR)\DptfAcpiTablesFfrd.aml : $(INTEL_DptfAcpiTablesFfrd_DIR)\DptfFfrd.asl 
  $(ASLEXPANDER) $(INTEL_DptfAcpiTablesFfrd_DIR)\DptfFfrd.asl $(BUILD_DIR)\DptfFfrd.asl $(PROJECT_CPU_ROOT)\Include
  $(IASL) -p $(BUILD_DIR)\DptfAcpiTablesFfrd.aml $(BUILD_DIR)\DptfFfrd.asl

$(BUILD_DIR)\DptfAcpiTablesFfrd.sec: $(BUILD_DIR)\DptfAcpiTablesFfrd.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with DptfAcpiTablesFfrd tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in Acpiplatform.c

$(BUILD_DIR)\DptfAcpiTablesFfrd.ffs: $(BUILD_DIR)\DptfAcpiTablesFfrd.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\DptfAcpiTablesFfrd.pkg

PACKAGE.INF
[.]
BASE_NAME                   = DptfAcpiTablesFfrd
FFS_FILEGUID                = 2820908B-87F6-446b-A100-74EEE36E2918
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\DptfAcpiTablesFfrd.sec
  }
}
<<KEEP


#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
