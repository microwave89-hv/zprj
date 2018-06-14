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
# Name: SgAcpiTables.mak
#
# Description: MAK file for the ModulePart:SgAcpiTables
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : BuildSaSsdt

BuildSaSsdt : $(BUILD_DIR)\SaSsdt.ffs

#-----------------------------------------------------------------------
# ASL compiler definition
#-----------------------------------------------------------------------
IASL = $(SILENT)iasl4.exe 
#-----------------------------------------------------------------------
$(BUILD_DIR)\SaSsdt.aml : $(INTEL_SASSDT_ASL_FILE) 
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_IgdOGBDA_ASL_FILE) > $(BUILD_DIR)\IgdOGBDA.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_IgdOMOBF_ASL_FILE) > $(BUILD_DIR)\IgdOMOBF.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_IgdOPRN_ASL_FILE) > $(BUILD_DIR)\IgdOPRN.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_IgdOSBCB_ASL_FILE) > $(BUILD_DIR)\IgdOSBCB.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_INTELGFX_ASL_FILE) > $(BUILD_DIR)\INTELGFX.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_SA_ASL_FILE) > $(BUILD_DIR)\SA.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_SAPCIEDSM_ASL_FILE) > $(BUILD_DIR)\SAPCIEDSM.asl
  $(CP) /FI$(BUILD_DIR)\tokenasl.h $(INTEL_SASSDT_ASL_FILE) > $(BUILD_DIR)\SASSDT.asl
  $(ASLEXPANDER) $(BUILD_DIR)\SASSDT.asl $(BUILD_DIR)\SASSDT_BUILD.asl $(BUILD_DIR) 
  $(IASL) -p $(BUILD_DIR)\SaSsdt.aml $(BUILD_DIR)\SASSDT_BUILD.asl


$(BUILD_DIR)\SaSsdt.sec: $(BUILD_DIR)\SaSsdt.aml
  $(GENSECTION) -I $*.aml -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\SaSsdt.ffs: $(BUILD_DIR)\SaSsdt.sec $(SaSsdtTables_DIR)\SaSsdtTables.mak
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=AAA99A23-13B6-4C31-BB8B-299E8EC04FA4\
		TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFS_CHECKSUM=1\
		RAWFILE=$(BUILD_DIR)\SaSsdt.sec FFSFILE=$(BUILD_DIR)\SaSsdt.ffs COMPRESS=0 NAME=SaSsdt

