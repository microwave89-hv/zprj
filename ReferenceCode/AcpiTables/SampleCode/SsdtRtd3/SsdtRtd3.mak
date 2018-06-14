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
# Name: SsdtRtd3.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildRTD3

BuildRTD3 : $(BUILD_DIR)\Ult0Rtd3.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  
#-----------------------------------------------------------------------
$(BUILD_DIR)\Ult0Rtd3.aml : $(INTEL_RTD3_ASL_FILE) 
  @cl /C /EP $(INTEL_RTD3_ASL_FILE) > $(BUILD_DIR)\Ult0Rtd3.asl
  @cl /C /EP $(INTEL_RTD3_COMMON_ASL_FILE) > $(BUILD_DIR)\RTD3Common.asl
  @cl /C /EP $(INTEL_RTD3_PCIE_ASL_FILE) > $(BUILD_DIR)\RTD3Pcie.asl
  $(IASL) -p $(BUILD_DIR)\Ult0Rtd3.aml $(BUILD_DIR)\Ult0Rtd3.asl

$(BUILD_DIR)\Ult0Rtd3.sec: $(BUILD_DIR)\Ult0Rtd3.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

#Note. Expand the package with RTD3 tables. 
# DXE phase will load the tables 
# and update Aml contents if provided in Acpiplatform.c

$(BUILD_DIR)\Ult0Rtd3.ffs: $(BUILD_DIR)\Ult0Rtd3.sec
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\Ult0Rtd3.pkg

PACKAGE.INF
[.]
BASE_NAME                   = Ult0Rtd3
FFS_FILEGUID                = 7FFC3536-0A8A-448B-95F4-39F5B9F09ADD
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
	$(PROJECT_DIR)\$(BUILD_DIR)\Ult0Rtd3.sec
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
