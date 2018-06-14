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
# Name: SgAcpiTablesPch.mak
#
# Description: MAK file for the ModulePart:SgAcpiTablesPch
# 
#
#<AMI_FHDR_END>
#*************************************************************************
EDK: SGPCHASL

SGPCHASL: $(BUILD_DIR)\SGACPIPCH.ffs

ALLSGPCHSEC = $(BUILD_DIR)\SGACPIPCH.sec

!IFNDEF IASL
IASL = iasl4.exe 	# Intel ASL compiler. Supports extended ACPI 2.0 asl objects
!ENDIF

#-----------------------------------------------------------------------#
#		Process SGPCH asl files
#-----------------------------------------------------------------------#

$(BUILD_DIR)\SgSsdtPch.asl : $(SGACPIPCH_DIR)\SgSsdtPch.ASL \
                             $(SGACPIPCH_DIR)\SgDgpuPch.ASL
    $(CP) /I$(SGACPIPCH_DIR) /FItoken.h /C $(SGACPIPCH_DIR)\$(@F) > $@
# include the token.h if needed to check for SDL flags
#  /FItoken.h

SgAcpiTablesPch_Includes = \
	$(SGACPIPCH_DIR)\

$(BUILD_DIR)\SgSsdtPch.aml: $(BUILD_DIR)\SgSsdtPch.asl
	$(SILENT)$(IASL) -I $(SgAcpiTablesPch_Includes) -p $@  $**

$(ALLSGPCHSEC): $(BUILD_DIR)\SgSsdtPch.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\SGACPIPCH.ffs: $(ALLSGPCHSEC) $(SGACPIPCH_DIR)\SgAcpiTablesPch.mak
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=CBCB3817-81E6-497e-87FF-C8FA8F24EC28\
		TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFS_CHECKSUM=1\
		RAWFILE=$(ALLSGPCHSEC) FFSFILE=$(BUILD_DIR)\SGACPIPCH.ffs COMPRESS=0 NAME=SGACPIPCH


