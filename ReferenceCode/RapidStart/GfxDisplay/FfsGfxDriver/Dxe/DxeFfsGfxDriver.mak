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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/DxeFfsGfxDriver/DxeFfsGfxDriver.mak 1     10/15/12 5:02a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 10/15/12 5:02a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/DxeFfsGfxDriver/DxeFfsGfxDriver.mak $
# 
# 1     10/15/12 5:02a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	[Category] Improvement
# [Severity] Important
# [Description] Update Intel Rapid Start Graphics Driver for Shark Bay
# Platform 5.0.1.1001, please increase your FV_BB_BLOCKS size if you
# compile fail that caused by FV_BB size too small.
# [Files] ReferenceCode\RapidStart\GfxDisplay\FfsGfxDriver\Pei\*.*,
# ReferenceCode\RapidStart\GfxDisplay\FfsGfxDriver\Dxe\*.*
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: DxeFfsGfxDriver.mak
#
# Description: Component description file for DxeFfsGfxDriver.
#
#<AMI_FHDR_END>
#**********************************************************************

all : DxeFfsGfxDriver

DxeFfsGfxDriver : $(BUILD_DIR)\DxeFfsGfxDriver.ffs

$(BUILD_DIR)\DxeFfsGfxDriver.ffs : $(DxeFfsGfxDriver_PATH)\DxeFfsGfxDriver.efi
  $(MAKE) /f Core\FFS.mak \
  NAME=DxeFfsGfxDriver \
  BUILD_DIR=$(BUILD_DIR) \
  SOURCE_DIR=$(DxeFfsGfxDriver_PATH) \
  GUID=6FD1DCC5-B5B9-4a82-8728-8D854428A4A3 \
  TYPE=EFI_FV_FILETYPE_DRIVER  \
  PEFILE=$** FFSFILE=$@ COMPRESS=1 NAME=$(**B)

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
