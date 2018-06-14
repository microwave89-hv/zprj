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
# Name: lpit.mak
#
# Description: MAke file to build Aptio ACPI ASL components
# 
#
#<AMI_FHDR_END>
#*************************************************************************
all : Lpit

Lpit : $(BUILD_DIR)\Lpit.ffS

Lpit_Includes = \
	$(EDK_INCLUDES)\

Lpit_Defines = \
    /D"TIANO_RELEASE_VERSION=0x00080006"\

Lpit_ACPIS = \
    $(BUILD_DIR)\Lpit.acpi\

$(BUILD_DIR)\Lpit.asl: $(BUILD_DIR)\token.mak $(LPIT_DIR)\lpit.mak
	copy << $@
<<

$(BUILD_DIR)\Lpit.exe : $(LPIT_DIR)\lpit.act $(LPIT_DIR)\lpit.h
	@CL $(CFLAGS) $(Lpit_Defines) /Fo$(BUILD_DIR)\ $(Lpit_Includes) /TC $(LPIT_DIR)\lpit.act
	@Link  /OUT:$(BUILD_DIR)\Lpit.exe /NODEFAULTLIB /ENTRY:main $(BUILD_DIR)\Lpit.obj

$(BUILD_DIR)\Lpit.acpi : $(BUILD_DIR)\Lpit.exe
	$(GENACPI) $(BUILD_DIR)\Lpit.exe $(BUILD_DIR)\Lpit.acpi

$(BUILD_DIR)\Lpit.sec : $(Lpit_ACPIS)
  $(GENSECTION) -I $** -O $@ -S EFI_SECTION_RAW

$(BUILD_DIR)\Lpit.ffs: $(BUILD_DIR)\Lpit.sec $(LPIT_DIR)\lpit.mak
	$(MAKE) /f Core\FFS.mak \
		BUILD_DIR=$(BUILD_DIR) \
        GUID=9DD795EB-41E8-4591-8E63-5EF4AA33B908\
		TYPE=EFI_FV_FILETYPE_FREEFORM \
        FFS_CHECKSUM=1\
		RAWFILE=$(BUILD_DIR)\Lpit.sec FFSFILE=$(BUILD_DIR)\Lpit.ffs COMPRESS=0 NAME=Lpit




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
