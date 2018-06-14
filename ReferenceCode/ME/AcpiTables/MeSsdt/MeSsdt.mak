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
# Name: MeSsdt.mak
#
# Description: MAK file for the ModulePart:MeSsdt
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildMeSsdt

BuildMeSsdt : $(BUILD_DIR)\MeSsdt.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\MeSsdt.aml : $(INTEL_MESSDT_ASL_FILE) 
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_MESSDT_ASL_FILE) > $(BUILD_DIR)\MeSsdt.asl
  $(ASLEXPANDER) $(BUILD_DIR)\MeSsdt.asl $(BUILD_DIR)\MeSsdt_Temp.asl $(BUILD_DIR) 
  $(IASL) -p $(BUILD_DIR)\MeSsdt.aml $(BUILD_DIR)\MeSsdt_Temp.asl


$(BUILD_DIR)\MeSsdt.sec: $(BUILD_DIR)\MeSsdt.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\MeSsdt.ffs: $(BUILD_DIR)\MeSsdt.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\MeSsdt.pkg

PACKAGE.INF
[.]
BASE_NAME                   = MeSsdt
FFS_FILEGUID                = 9A8F82D5-39B1-48DA-92DC-A22DA8834DF6
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\MeSsdt.sec
  }
}
<<KEEP

