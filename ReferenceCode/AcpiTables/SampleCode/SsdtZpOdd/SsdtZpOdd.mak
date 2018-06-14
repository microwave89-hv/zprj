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
# Name: SsdtZpOdd.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildZPODD

BuildZPODD : $(BUILD_DIR)\SsdtZpOdd.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\SsdtZpOdd.aml $(BUILD_DIR)\SsdtZpOddult.aml: $(BUILD_DIR)\SsdtZpOdd.asl $(BUILD_DIR)\SsdtZpOddult.asl
	$(SILENT)$(IASL) -p $@ $*.asl

$(BUILD_DIR)\SsdtZpOdd.sec $(BUILD_DIR)\SsdtZpOddult.sec: $(BUILD_DIR)\SsdtZpOdd.aml $(BUILD_DIR)\SsdtZpOddult.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with ZpOdd tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in Acpiplatform.c

$(BUILD_DIR)\SsdtZpOdd.ffs: $(BUILD_DIR)\SsdtZpOdd.sec $(BUILD_DIR)\SsdtZpOddult.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\SsdtZpOdd.pkg

PACKAGE.INF
[.]
BASE_NAME                   = ZpOdd
FFS_FILEGUID                = E42A76A1-D4B3-4c26-A1BB-84A3502A779F
 FFS_FILETYPE               = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\SsdtZpOdd.sec
	$(PROJECT_DIR)\$(BUILD_DIR)\SsdtZpOddult.sec
  }
}
<<KEEP

#-----------------------------------------------------------------------#
#		Process SG asl files
#-----------------------------------------------------------------------#
$(BUILD_DIR)\SsdtZpOdd.asl : $(INTEL_ZPODD_ASL_FILE)
    $(CP) /I$(INTEL_SSDTZPODD_DIR) /FItoken.h /C $(INTEL_ZPODD_ASL_FILE) > $(BUILD_DIR)\SsdtZpOdd.asl

$(BUILD_DIR)\SsdtZpOddult.asl : $(INTEL_ZPODDULT_ASL_FILE)
    $(CP) /I$(INTEL_SSDTZPODD_DIR) /FItoken.h /C $(INTEL_ZPODDULT_ASL_FILE) > $(BUILD_DIR)\SsdtZpOddult.asl


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
