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
# $Header: /Alaska/SOURCE/Modules/NVMe/NvmeSmm/NvmeSmm.mak 3     7/15/15 5:04a Deepthins $
#
# $Revision: 3 $
#
# $Date: 7/15/15 5:04a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/NVMe/NvmeSmm/NvmeSmm.mak $
# 
# 3     7/15/15 5:04a Deepthins
# [TAG]  		EIP228506
# [Description]  	Legacy Os installation failing for NVME device in AMD
# platform
# [Files]  		NvmeSmm.mak
# 
# 2     12/10/14 5:16a Lavanyap
# [TAG]  		EIP185327
# [Category]  	Improvement
# [Description]  	Security Enhancement for SMIHandler in Aptio4.x NVMe
# Driver
# [Files]  		NvmeSmm.mak, NvmeSmm.c, NvmeSmm.h
# 
# 1     9/04/14 7:54a Anandakrishnanl
# [TAG]  		EIP180861
# [Category]  	Improvement
# [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
# [Files]  		NvmeSmm.cif
# NvmeSmm.mak
# NvmeSmm.dxs
# NvmeSmm.sdl
# NvmeSmm.c
# NvmeSmm.h
# NvmeDef.h
#
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:         NvmeSmm.mak
#
# Description:  Make file for NvmeSmm
#
#<AMI_FHDR_END>
#**********************************************************************
all : NvmeSmm

NvmeSmm : $(BUILD_DIR)\NvmeSmm.mak NvmeSmmBin

$(BUILD_DIR)\NvmeSmm.mak : $(NVME_SMM_DIR)\NvmeSmm.cif $(NVME_SMM_DIR)\$(@B).mak $(BUILD_RULES) 
    $(CIF2MAK) $(NVME_SMM_DIR)\NvmeSmm.cif $(CIF2MAK_DEFAULTS)

NVME_SMM_LIB = $(AMIDXELIB) \
               $(NVMECONTROLLERLIB) \
               $(BUILD_DIR)\AmiBufferValidationLib.lib

NVME_SMM_INCLUDES=\
        /I$(NVME_DIR)\

NvmeSmmBin : $(NVME_SMM_LIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\NvmeSmm.mak all\
        GUID=E5E2C9D9-5BF5-497E-8860-94F81A09ADE0\
        ENTRY_POINT=NvmeSmmDriverEntryPoint\
        "MY_INCLUDES=$(NVME_SMM_INCLUDES)"\
        TYPE=SMM_DRIVER\
        COMPRESS=1

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
