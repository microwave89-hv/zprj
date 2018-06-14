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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SataDriver/SataDriver.mak 2     1/10/13 8:28a Scottyang $
#
# $Revision: 2 $
#
# $Date: 1/10/13 8:28a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Chipset/SataDriver/SataDriver.mak $
# 
# 2     1/10/13 8:28a Scottyang
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	Create token for SataDriver path.
# [Files]  		SataDriver.sdl, SataDriver.mak
# 
# 1     2/08/12 8:37a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name:	SatsDriver.mak
#
# Description:	Make file for the Sata Uefi Driver.
#
#<AMI_FHDR_END>
#*************************************************************************
all : $(BUILD_DIR)\SataDriver.ffs

SataDriver_INCLUDES=\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(EDK_INCLUDES)

$(BUILD_DIR)\SataDriver.ffs : $(OEM_SATA_EFI_DRIVER_FILE) $(SataDriver_DIR)\$(@B).mak Core\FFS.mak
            $(MAKE) /$(MAKEFLAGS) /f Core\FFS.mak \
            CPFLAGS="$(GLOBAL_DEFINES) /D TIANO_RELEASE_VERSION=0x00080006 $(EXTRA_DEFINES) $(SataDriver_INCLUDES)" \
            BUILD_DIR=$(BUILD_DIR) SOURCE_DIR=$(SataDriver_DIR) \
            GUID=91B4D9C1-141C-4824-8D02-3C298E36EB3F\
            NAME=$(@B)\
            TYPE=EFI_FV_FILETYPE_DRIVER \
            DEPEX1=$(SataDriver_DIR)\SataDriver.dxs\
            DEPEX1_TYPE=EFI_SECTION_DXE_DEPEX \
            PEFILE=$(OEM_SATA_EFI_DRIVER_FILE) FFSFILE=$@ COMPRESS=1 \
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