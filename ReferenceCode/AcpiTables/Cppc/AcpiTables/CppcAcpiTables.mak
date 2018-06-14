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
#<AMI_FHDR_START>
#
# Name: CppcAcpiTables.mak
#
# Description: MAke file to build Intel CPPC ACPI ASL components
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
EDK : CPPCACPI

ALLCPPCSEC = $(BUILD_DIR)\Cpc.sec\
             $(BUILD_DIR)\Cppc.sec\
             $(BUILD_DIR)\Pcct.sec

CPPCACPI : $(BUILD_DIR)\CppcAcpiTables.ffs

$(BUILD_DIR)\Cpc.aml : $(INTEL_CPC_ASL_FILE)
  @cl /C /EP $(INTEL_CPC_ASL_FILE) > $(BUILD_DIR)\Cpc.asl
  $(IASL) -p $(BUILD_DIR)\Cpc.aml $(BUILD_DIR)\Cpc.asl

$(BUILD_DIR)\Cppc.aml : $(INTEL_CPPC_ASL_FILE) 
  @cl /C /EP $(PROJECT_CPU_INCLUDES) $(INTEL_CPPC_ASL_FILE) > $(BUILD_DIR)\Cppc.asl
  $(IASL) -p $(BUILD_DIR)\Cppc.aml $(BUILD_DIR)\Cppc.asl

$(BUILD_DIR)\Pcct.aml : $(INTEL_PCCT_ASL_FILE) 
  @cl /C /EP $(INTEL_PCCT_ASL_FILE) > $(BUILD_DIR)\Pcct.asl
  $(IASL) -p $(BUILD_DIR)\Pcct.aml $(BUILD_DIR)\Pcct.asl

$(BUILD_DIR)\Cpc.sec: $(BUILD_DIR)\Cpc.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\Cppc.sec: $(BUILD_DIR)\Cppc.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\Pcct.sec: $(BUILD_DIR)\Pcct.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\CppcAcpiTables.ffs: $(ALLCPPCSEC) $(INTEL_CPPC_ACPI_TABLE_DIR)\CppcAcpiTables.mak
  $(GENFFSFILE) -B $(BUILD_DIR) -V -o $@ -P1 <<$(BUILD_DIR)\CppcAcpiTables.pkg
PACKAGE.INF
[.]
BASE_NAME                   = CppcAcpiTables
FFS_FILEGUID                = 60E31DE1-03EC-492a-9598-65A3C50E0F6B
FFS_FILETYPE                = EFI_FV_FILETYPE_FREEFORM
FFS_ATTRIB_CHECKSUM         = TRUE

IMAGE_SCRIPT =
{
  Compress (dummy) {
            $(PROJECT_DIR)\$(BUILD_DIR)\Cpc.sec
            $(PROJECT_DIR)\$(BUILD_DIR)\Cppc.sec
            $(PROJECT_DIR)\$(BUILD_DIR)\Pcct.sec
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
