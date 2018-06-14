#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/NVMe/NvmeController.mak 1     9/04/14 7:45a Anandakrishnanl $
#
# $Date: 9/04/14 7:45a $
#
# $Log: /Alaska/SOURCE/Modules/NVMe/NvmeController.mak $
# 
# 1     9/04/14 7:45a Anandakrishnanl
# [TAG]  		EIP180861
# [Category]  	Improvement
# [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
# [Files]  		NvmeController.cif
# NvmeController.sdl
# NvmeController.mak
# NvmeController.c
# NvmeController.h
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/NVMe/NvmeController.mak $
# 
# 1     9/04/14 7:45a Anandakrishnanl
# [TAG]  		EIP180861
# [Category]  	Improvement
# [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
# [Files]  		NvmeController.cif
# NvmeController.sdl
# NvmeController.mak
# NvmeController.c
# NvmeController.h
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         NvmeController.mak
#
# Description:  Make file for NvmeController Lib
#
#<AMI_FHDR_END>
#**********************************************************************
all : NvmeController

NVMECONTROLLERLIB_OBJECTS=\
$(BUILD_DIR)\$(NVME_DIR)\NvmeController.obj\

$(NVMECONTROLLERLIB) : NvmeController

NvmeController : $(BUILD_DIR)\NvmeController.mak NvmeControllerBin

$(BUILD_DIR)\NvmeController.mak : $(NVME_DIR)\NvmeController.cif $(NVME_DIR)\NvmeController.mak $(BUILD_RULES)
	$(CIF2MAK) $(NVME_DIR)\NvmeController.cif $(CIF2MAK_DEFAULTS)

NvmeControllerBin :
	$(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
		/f $(BUILD_DIR)\NvmeController.mak all\
		MAKEFILE=$(NVME_DIR)\NvmeController.mak\
		"OBJECTS=$(NVMECONTROLLERLIB_OBJECTS)"\
		"EXT_HEADERS=$(BUILD_DIR)\token.h"\
		TYPE=LIBRARY LIBRARY_NAME=$(NVMECONTROLLERLIB)
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2014, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
