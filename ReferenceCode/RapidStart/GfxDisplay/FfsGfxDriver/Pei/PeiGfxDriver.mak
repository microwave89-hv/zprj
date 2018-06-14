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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/PeiGfxDriver/PeiGfxDriver.mak 1     10/15/12 4:46a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 10/15/12 4:46a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/PeiGfxDriver/PeiGfxDriver.mak $
# 
# 1     10/15/12 4:46a Bensonlai
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
# Name: PeiGfxDriver.mak
#
# Description: Component description file for PeiGfxDriver.
#
#<AMI_FHDR_END>
#**********************************************************************

all : PeiGfxDriver

PeiGfxDriver : $(BUILD_DIR)\PeiGfxDriver.ffs

PeiGfxDriver_INCLUDES=\
  $(EdkIIGlueLib_INCLUDES)\
  $(EDK_INCLUDES)

$(BUILD_DIR)\PeiGfxDriver.ffs : $(PeiGfxDriver_PATH)\PeiGfxDriver.efi
  $(MAKE) $(EDKIIGLUE_DEFAULTS) /f Core\FFS.mak \
  CPFLAGS="$(GLOBAL_DEFINES) /D TIANO_RELEASE_VERSION=0x00080006 $(EXTRA_DEFINES) $(PeiGfxDriver_INCLUDES)" \
  NAME=PeiGfxDriver \
  BUILD_DIR=$(BUILD_DIR) \
  SOURCE_DIR=$(PeiGfxDriver_PATH) \
  GUID=B9846521-FF99-4953-8FA2-85C9ADCCE5AF \
  TYPE=EFI_FV_FILETYPE_PEIM  \
  EDKIIModule=EFI_FV_FILETYPE_PEIM\
  DEPEX1=$(PeiGfxDriver_PATH)\PeiGfxDriver.dxs DEPEX1_TYPE=EFI_SECTION_PEI_DEPEX \
  PEFILE=$** FFSFILE=$@ COMPRESS=0 NAME=$(**B)

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
