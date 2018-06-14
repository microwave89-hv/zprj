#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#**********************************************************************
# $Header: /Alaska/SOURCE/Modules/HardwareSignatureManagement/HardwareSignatureManagement.mak 3     1/09/14 8:02a Albertlin $
#
# $Date: 1/09/14 8:02a $
#
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/HardwareSignatureManagement/HardwareSignatureManagement.mak $ 
# 
# 3     1/09/14 8:02a Albertlin
# [TAG]           EIP147244
# [Category]      Not Specified
# [Description]   BIOS need to report changed hardware signature when
# BIOS setup was modified.
# [Files]         HardwareSignatureManagement.mak
# 
# 2     12/12/12 3:42a Sophiachen
# [TAG]  		EIP106129
# [Category]  	New Feature
# [Description]  	After BIOS firmware update, the hardware signature will
# be changed.
# [Files]  		HardwareSignatureManagement.c,
# HardwareSignatureManagement.mak, HardwareSignatureManagement.sdl
# 
# 1     9/25/12 8:57a Sophiachen
# [TAG]  		EIP96258
# [Category]  	New Feature
# [Description]  	Update the Hardware Signature of the ACPI table FACS
# field can notify ACPI OS whether any hardware configuration change.
# [Files]  		HardwareSignatureManagement.cif
# HardwareSignatureManagement.mak
# HardwareSignatureManagement.dxs
# HardwareSignatureManagement.sdl
# HardwareSignatureManagement.c
# HardwareChangeDetect.c
# 
#**********************************************************************


#**********************************************************************
#<AMI_FHDR_START>
#
# Name: HardwareSignatureManagement.mak
#
# Description: Make file for the Hardware signature Management component    
#
#<AMI_FHDR_END>
#**********************************************************************

all : HwSignatureManagement

HwSignatureManagement : $(BUILD_DIR)\HardwareSignatureManagement.mak HwSignatureManagementBin

$(BUILD_DIR)\HardwareSignatureManagement.mak : $(HARDWARE_SIGNATURE_DIR)\$(@B).cif $(HARDWARE_SIGNATURE_DIR)\$(@B).mak $(BUILD_RULES)
    $(CIF2MAK) $(HARDWARE_SIGNATURE_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

HwSignatureManagementBin : $(AMIDXELIB) 
    $(MAKE) /$(MAKEFLAGS) $(BUILD_DEFAULTS)\
        /f $(BUILD_DIR)\HardwareSignatureManagement.mak all\
        GUID=B7EE4835-84CE-4b15-BF52-2D11574CE470 \
        ENTRY_POINT=HardwareSignatureEntryPoint\
        DEPEX1=$(HARDWARE_SIGNATURE_DIR)\HardwareSignatureManagement.dxs \
        TYPE=BS_DRIVER \
        COMPRESS=1\

SMIFlashBin : $(BUILD_DIR)\HardwareSignatureManagement.obj $(BUILD_DIR)\HardwareChangeDetect.obj

{$(HARDWARE_SIGNATURE_DIR)}.c{$(BUILD_DIR)}.obj::
	$(CC) $(CFLAGS) /I $(HARDWARE_SIGNATURE_DIR)  \
    /Fo$(BUILD_DIR)\ $<

$(BUILD_DIR)\HardwareSignatureManagement.obj : $(HARDWARE_SIGNATURE_DIR)\HardwareSignatureManagement.c

$(BUILD_DIR)\HardwareChangeDetect.obj : $(HARDWARE_SIGNATURE_DIR)\HardwareChangeDetect.c

#<EIP147244 >
#---------------------------------------------------------------------------
#        Link Callback Lib to Setup
#---------------------------------------------------------------------------
AMITSEBin : $(BUILD_DIR)\HardwareSignatureManagement.obj $(BUILD_DIR)\HardwareChangeDetect.obj
#<EIP147244 >

#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************