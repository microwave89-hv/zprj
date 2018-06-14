#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/GfxDisplayLibPei/GfxDisplayLibPei.mak 2     10/15/12 5:07a Bensonlai $
#
# $Revision: 2 $
#
# $Date: 10/15/12 5:07a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/GfxDisplayLibPei/GfxDisplayLibPei.mak $
# 
# 2     10/15/12 5:07a Bensonlai
# [Category] Improvement
# [Severity] Important
# [Description] Update Intel Rapid Start Graphics Driver for Shark Bay
# Platform 5.0.1.1001, please increase your FV_BB_BLOCKS size if you
# compile fail that caused by FV_BB size too small.
# [Files] ReferenceCode\RapidStart\GfxDisplay\FfsGfxDriver\Pei\*.*,
# ReferenceCode\RapidStart\GfxDisplay\FfsGfxDriver\Dxe\*.*
# 
# 1     9/26/12 3:53a Yurenlai
# [TAG]           None
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Beta Version 0.7.0.
# [Description]   ReferenceCode\RapidStart\*.*, RapidStartPeiLib.h
#
#*************************************************************************

all : GfxDisplayLibPei

$(GfxDisplayLibPei_LIB) : GfxDisplayLibPei

GfxDisplayLibPei : $(BUILD_DIR)\GfxDisplayLibPei.mak GfxDisplayLibPeiBin

$(BUILD_DIR)\GfxDisplayLibPei.mak : $(GfxDisplayLibPei_DIR)\$(@B).cif $(GfxDisplayLibPei_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(GfxDisplayLibPei_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

GfxDisplayLibPei_INCLUDES =\
            $(EDK_INCLUDES)\
            $(RAPIDSTART_INCLUDES)\

GfxDisplayLibPeiBin : 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\GfxDisplayLibPei.mak all\
            "MY_INCLUDES=$(GfxDisplayLibPei_INCLUDES)" \
            TYPE=PEI_LIBRARY
#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2012, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
