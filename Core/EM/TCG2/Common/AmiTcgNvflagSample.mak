#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/TCG2/Common/AmiTcgNvflagSample/AmiTcgNvflagSample.mak 1     4/21/14 2:17p Fredericko $Revision:
#
# $Date: 4/21/14 2:17p $Log: 
# 
#*************************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: AmiTcgNvflagSample.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
all : AmiTcgNvflagSample

#---------------------------------------------------------------------------
#			Making AmiTcgNvflagSample
#---------------------------------------------------------------------------
AmiTcgNvflagSample : $(BUILD_DIR)\AmiTcgNvflagSample.mak AmiTcgNvflagSamplebin

$(BUILD_DIR)\AmiTcgNvflagSample.mak : $(AMI_TCG_NVFLAG_SAMPLE_DIR)\$(@B).cif $(AMI_TCG_NVFLAG_SAMPLE_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(AMI_TCG_NVFLAG_SAMPLE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

MODULE_CFLAGS=$(CFLAGS)\
	/I$(TCG_DIR)\
	/I$(TPM12_DIR)\
    /I$(TCG_DIR)\Common\
    /I$(AMI_TCG_PLATFORM_DXE_DIR)\
    /I$(TCG_DIR)\protocol\TcgService\
    /I$(TCG_DIR)\protocol\TpmDevice\
	/I$(PROJECT_DIR)\Include\Protocol\

AmiTcgNvflagSample_OBJECTS = \
$(BUILD_DIR)\$(AMI_TCG_NVFLAG_SAMPLE_DIR)\AmiTcgNvflagSample.obj \

AmiTcgNvflagSamplebin: $(AMIDXELIB) $(BUILD_DIR)\AmiTcmlib.lib
    	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\AmiTcgNvflagSample.mak all\
		"CFLAGS=$(MODULE_CFLAGS)"\
		GUID=50F6096D-7C98-4c78-9A1D-C5A1833B6A88 \
		ENTRY_POINT=AmiTcgPpiNvflagEntry \
		TYPE=BS_DRIVER \
        "OBJECTS=$(AmiTcgNvflagSample_OBJECTS)"\
		DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
		COMPRESS=1
#---------------------------------------------------------------------------

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
