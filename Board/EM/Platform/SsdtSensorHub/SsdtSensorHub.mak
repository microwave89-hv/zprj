#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
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
# Name: SsdtAcpiDebug.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildSENSORHUB

BuildSENSORHUB : $(BUILD_DIR)\SENSORHUB.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\SsdtSensorHub.aml : $(INTEL_SENSORHUB_ASL_FILE)
  @cl /C /EP $(INTEL_SENSORHUB_ASL_FILE) > $(BUILD_DIR)\SsdtSensorHub.asl
  $(IASL) -p $(BUILD_DIR)\SsdtSensorHub.aml $(BUILD_DIR)\SsdtSensorHub.asl

$(BUILD_DIR)\SsdtSensorHub.sec: $(BUILD_DIR)\SsdtSensorHub.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with SsdtSensorHub tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in Acpiplatform.c

$(BUILD_DIR)\SENSORHUB.ffs: $(BUILD_DIR)\SsdtSensorHub.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\SsdtSensorHub.pkg

PACKAGE.INF
[.]
BASE_NAME                   = SENSORHUB
FFS_FILEGUID                = A3201EEC-1612-4577-8924-CB32D542D22C      
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\SsdtSensorHub.sec
  }
}
<<KEEP


#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
