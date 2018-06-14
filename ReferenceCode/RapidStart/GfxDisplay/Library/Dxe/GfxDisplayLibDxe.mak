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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/GfxDisplayLibDxe/GfxDisplayLibDxe.mak 2     10/15/12 5:11a Bensonlai $
#
# $Revision: 2 $
#
# $Date: 10/15/12 5:11a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/GfxDisplayLibDxe/GfxDisplayLibDxe.mak $
# 
# 2     10/15/12 5:11a Bensonlai
# [Category] Improvement
# [Severity] Important
# [Description] Update Intel Rapid Start Graphics Driver for Shark Bay
# Platform 5.0.1.1001, please increase your FV_BB_BLOCKS size if you
# compile fail that caused by FV_BB size too small.
# [Files] ReferenceCode\RapidStart\GfxDisplay\FfsGfxDriver\Pei\*.*,
# ReferenceCode\RapidStart\GfxDisplay\FfsGfxDriver\Dxe\*.*
# 
# 1     9/26/12 3:51a Yurenlai
# [TAG]           None
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Beta Version 0.7.0.
# [Description]   ReferenceCode\RapidStart\*.*, RapidStartPeiLib.h
#
#*************************************************************************

all : GfxDisplayLibDxe

$(GfxDisplayLibDxe_LIB) : GfxDisplayLibDxe

GfxDisplayLibDxe : $(BUILD_DIR)\GfxDisplayLibDxe.mak GfxDisplayLibDxeBin

$(BUILD_DIR)\GfxDisplayLibDxe.mak : $(GfxDisplayLibDxe_DIR)\$(@B).cif $(GfxDisplayLibDxe_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(GfxDisplayLibDxe_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

GfxDisplayLibDxe_INCLUDES =\
            $(EDK_INCLUDES)\
            $(RAPIDSTART_INCLUDES)\
            $(INTEL_MCH_INCLUDES)\

GfxDisplayLibDxeBin : $(INTEL_SA_PROTOCOL_LIB)
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\GfxDisplayLibDxe.mak all\
            "MY_INCLUDES=$(GfxDisplayLibDxe_INCLUDES)" \
            TYPE=LIBRARY
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
