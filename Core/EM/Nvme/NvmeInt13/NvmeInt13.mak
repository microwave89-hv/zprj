#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/NVMe/NvmeInt13/NvmeInt13.mak 1     9/04/14 7:56a Anandakrishnanl $
#
# $Revision: 1 $
#
# $Date: 9/04/14 7:56a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/NVMe/NvmeInt13/NvmeInt13.mak $
# 
# 1     9/04/14 7:56a Anandakrishnanl
# [TAG]  		EIP180861
# [Category]  	Improvement
# [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
# [Files]  		NvmeInt13.cif
# NvmeInt13.c
# NvmeInt13.h
# NvmeInt13.sdl
# NvmeInt13.mak
# NvmeInt13.inf
# NvmeInt13.dxs
#
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:         NvmeInt13.mak
#
# Description:  Make file for NvmeInt13
#
#<AMI_FHDR_END>
#**********************************************************************

all: NVMEINT13 

$(BUILD_DIR)\NvmeInt13.mak: $(NVME_INT13_DIR)\NvmeInt13.cif $(NVME_INT13_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(CIF2MAK_DEFAULTS) $(NVME_INT13_DIR)\NvmeInt13.cif 

NVMEINT13: $(BUILD_DIR)\NvmeInt13.mak NVMEINT13BIN

NVME_INT13_INCLUDES=\
        /I$(NVME_DIR)\

NVME_OBJECTS = \
$(BUILD_DIR)\$(NVME_INT13_DIR)\NvmeInt13.obj \

NVMEINT13BIN: $(AMIDXELIB)
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NvmeInt13.mak all\
		GUID=C9A6DE36-FDFF-4FAF-8343-85D9E3470F43\
		"OBJECTS=$(NVME_OBJECTS)"\
        "MY_INCLUDES=$(NVME_INT13_INCLUDES)"\
		ENTRY_POINT=NvmeInt13EntryPoint\
		TYPE=BS_DRIVER\
		COMPRESS=1\
		DEPEX1=$(NVME_INT13_DIR)\NvmeInt13.dxs \

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093    **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
