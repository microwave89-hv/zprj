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
# Name: SsdtPtid.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildPTID

BuildPTID : $(BUILD_DIR)\PTID.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\ptid.aml : $(INTEL_PTID_ASL_FILE) 
  @cl /C /EP $(INTEL_PTID_ASL_FILE) > $(BUILD_DIR)\ptid.asl
  $(IASL) -p $(BUILD_DIR)\ptid.aml $(BUILD_DIR)\ptid.asl

$(BUILD_DIR)\ptid.sec: $(BUILD_DIR)\ptid.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with PTID tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in Acpiplatform.c

$(BUILD_DIR)\PTID.ffs: $(BUILD_DIR)\ptid.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\ptid.pkg

PACKAGE.INF
[.]
BASE_NAME                   = PTID
FFS_FILEGUID                = 95DFCAE5-BB28-4d6b-B1E2-3AF3A6BF434F
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\ptid.sec
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
