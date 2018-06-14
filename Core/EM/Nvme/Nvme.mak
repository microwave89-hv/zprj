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
# $Header: /Alaska/SOURCE/Modules/NVMe/Nvme.mak 4     5/18/15 2:52a Karthikar $
#
# $Date: 5/18/15 2:52a $
#
# $Log: /Alaska/SOURCE/Modules/NVMe/Nvme.mak $
# 
# 4     5/18/15 2:52a Karthikar
# [TAG] EIP216763 
# [Category] Improvement
# [Description] Update the Aptio 4.x Nvme driver to Aptio 5.x Nvme driver
# Label 05
# [Files] Nvme.mak,NvmeBus.c, NvmeBus.h, NvmeController.c,
# NvmePassthru.c,NvmePassthru.h, NvmeSmm.c, NvmExpressPassThru.h
# 
# 3     5/14/15 2:38a Karthikar
# 
# 2     9/04/14 7:31a Anandakrishnanl
# [TAG]  		EIP180861
# [Category]  	Improvement
# [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
# [Files]  		
# Nvme.cif	
# Nvme.mak	
# Nvme.uni
# Nvme.chm	
# NvmeSetup.c
# NvmeBus.c
# NvmeComponentName.c
# NvmeIncludes.h
# NvmeBus.h
# [NvmeControllerLib]
# [NvmeSmm]
# [NVMEINT13]
# [NvmeProtocol]
# 
# 1     6/20/14 6:27a Anandakrishnanl
# [TAG]  		EIP172958
# [Category]  	New Feature
# [Description]  	Nvme Driver Intial Checkin
# [Files]  		Nvme.cif
# Nvme.sdl
# Nvme.mak
# Nvme.sd
# Nvme.uni
# Nvme.chm
# NvmeSetup.c
# NvmeBus.c
# NvmeController.c
# NvmeComponentName.c
# NvmeIncludes.h
# NvmeBus.h
# NvmeController.h
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/NVMe/Nvme.mak $
# 
# 4     5/18/15 2:52a Karthikar
# [TAG] EIP216763 
# [Category] Improvement
# [Description] Update the Aptio 4.x Nvme driver to Aptio 5.x Nvme driver
# Label 05
# [Files] Nvme.mak,NvmeBus.c, NvmeBus.h, NvmeController.c,
# NvmePassthru.c,NvmePassthru.h, NvmeSmm.c, NvmExpressPassThru.h
# 
# 3     5/14/15 2:38a Karthikar
# 
# 2     9/04/14 7:31a Anandakrishnanl
# [TAG]  		EIP180861
# [Category]  	Improvement
# [Description]  	Legacy Boot support in Aptio 4.x Nvme driver
# [Files]  		
# Nvme.cif	
# Nvme.mak	
# Nvme.uni
# Nvme.chm	
# NvmeSetup.c
# NvmeBus.c
# NvmeComponentName.c
# NvmeIncludes.h
# NvmeBus.h
# [NvmeControllerLib]
# [NvmeSmm]
# [NVMEINT13]
# [NvmeProtocol]
# 
# 1     6/20/14 6:27a Anandakrishnanl
# [TAG]  		EIP172958
# [Category]  	New Feature
# [Description]  	Nvme Driver Intial Checkin
# [Files]  		Nvme.cif
# Nvme.sdl
# Nvme.mak
# Nvme.sd
# Nvme.uni
# Nvme.chm
# NvmeSetup.c
# NvmeBus.c
# NvmeController.c
# NvmeComponentName.c
# NvmeIncludes.h
# NvmeBus.h
# NvmeController.h
# 
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: Nvme.mak
#
# Description:
#
#<AMI_FHDR_END>
#************************************************************************
all : Nvme 

Nvme : $(BUILD_DIR)\Nvme.mak NvmeBin

$(BUILD_DIR)\Nvme.mak : $(NVME_DIR)\$(@B).cif $(NVME_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(NVME_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

NvmeBin:  $(AMIDXELIB) $(NVMECONTROLLERLIB)
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Nvme.mak all\
        GUID=634E8DB5-C432-43BE-A653-9CA2922CC458\
        ENTRY_POINT=NvmeBusEntryPoint \
        TYPE=BS_DRIVER \
        COMPRESS=1 HAS_RESOURCES=1\
        "OBJECTS=$(BUILD_DIR)\$(NVME_DIR)\NvmeBus.obj\
                 $(BUILD_DIR)\$(NVME_DIR)\NvmeComponentName.obj\
                 $(BUILD_DIR)\$(NVME_DIR)\NvmePassthru.obj"

SetupSdbs :$(BUILD_DIR)\Nvme.mak  NVMESDB
SetupBin : $(BUILD_DIR)\NvmeSetup.obj

NVMESDB : 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\Nvme.mak all\
        TYPE=SDB NAME=Nvme MAKEFILE=$(BUILD_DIR)\Nvme.mak\
        "STRING_CONSUMERS=$(NVME_DIR)\Nvme.sd  $(NVME_DIR)\NvmeSetup.c "

$(BUILD_DIR)\NvmeSetup.obj : $(NVME_DIR)\NvmeSetup.c $(BUILD_DIR)\SetupStrTokens.h
    $(CC) $(CFLAGS) /Fo$(BUILD_DIR)\ $(NVME_DIR)\NvmeSetup.c 
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
