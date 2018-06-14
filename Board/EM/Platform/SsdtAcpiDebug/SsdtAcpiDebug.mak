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
all : BuildACPIDEBUG

BuildACPIDEBUG : $(BUILD_DIR)\ACPIDEBUG.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\SsdtAcpiDebug.aml : $(INTEL_ACPIDEBUG_ASL_FILE) 
  @cl /C /EP $(INTEL_ACPIDEBUG_ASL_FILE) > $(BUILD_DIR)\SsdtAcpiDebug.asl
  $(IASL) -p $(BUILD_DIR)\SsdtAcpiDebug.aml $(BUILD_DIR)\SsdtAcpiDebug.asl

$(BUILD_DIR)\SsdtAcpiDebug.sec: $(BUILD_DIR)\SsdtAcpiDebug.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with SsdtAcpiDebug tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in Acpiplatform.c

$(BUILD_DIR)\ACPIDEBUG.ffs: $(BUILD_DIR)\SsdtAcpiDebug.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\SsdtAcpiDebug.pkg

PACKAGE.INF
[.]
BASE_NAME                   = ACPIDEBUG
FFS_FILEGUID                = 94AB6AED-9719-48ef-831C-2E9C29758C33                              
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\SsdtAcpiDebug.sec
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
