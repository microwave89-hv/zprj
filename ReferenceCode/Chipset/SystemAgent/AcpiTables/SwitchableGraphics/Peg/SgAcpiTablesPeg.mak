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
EDK: SGPEGASL

SGPEGASL: $(BUILD_DIR)\SGACPIPEG.ffs

ALLSGPEGSEC = $(BUILD_DIR)\SGACPIPEG.sec

!IF "$(ACPIPLATFORM_ASL_COMPILER)"==""
!ERROR It is an invalid path, please check your ASL compiler path.
!ENDIF

IASL = $(ACPIPLATFORM_ASL_COMPILER)  

#-----------------------------------------------------------------------#
#		Process SG asl files
#-----------------------------------------------------------------------#

$(BUILD_DIR)\SgSsdt.asl :  $(SGACPIPEG_DIR)\SgSsdt.ASL \
                            $(SGACPIPEG_DIR)\SgDgpu.ASL
    $(CP) /I$(SGACPIPEG_DIR) /C $(SGACPIPEG_DIR)\$(@F) > $@
# include the token.h if needed to check for SDL flags
#  /FItoken.h

SGAcpiTablesPeg_Includes = \
	$(SGACPIPEG_DIR)\

$(BUILD_DIR)\SgSsdt.aml: $(BUILD_DIR)\SgSsdt.asl
	$(SILENT)$(IASL) -I $(SGAcpiTablesPeg_Includes) -p $@  $**

$(ALLSGPEGSEC): $(BUILD_DIR)\SgSsdt.aml
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\SGACPIPEG.ffs: $(ALLSGPEGSEC) $(SGACPIPEG_DIR)\SgAcpiTablesPeg.mak
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=CACB3817-81E6-497e-87FF-C8FA8F24EC28\
		TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFS_CHECKSUM=1\
		RAWFILE=$(ALLSGPEGSEC) FFSFILE=$(BUILD_DIR)\SGACPIPEG.ffs COMPRESS=0 NAME=SGACPIPEG

