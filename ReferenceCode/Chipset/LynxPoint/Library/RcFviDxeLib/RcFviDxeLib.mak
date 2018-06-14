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
# $Header: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/RcFviDxeLib/RcFviDxeLib.mak 1     2/08/12 8:50a Yurenlai $
#
# $Revision: 1 $
#
# $Date: 2/08/12 8:50a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/BIN/Chipset/Intel/SouthBridge/LynxPoint/Intel Pch SB Refcode/PchLib/RcFviDxeLib/RcFviDxeLib.mak $
# 
# 1     2/08/12 8:50a Yurenlai
# Intel Lynx Point/SB eChipset initially releases.
# 
# 
#*************************************************************************
all : RcFviDxeLib

$(RcFviDxeLib_LIB) : RcFviDxeLib

RcFviDxeLib : $(BUILD_DIR)\RcFviDxeLib.mak RcFviDxeLibBin

$(BUILD_DIR)\RcFviDxeLib.mak : $(RcFviDxeLib_DIR)\$(@B).cif $(RcFviDxeLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(RcFviDxeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RcFviDxeLib_INCLUDES=\
            $(EDK_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\

RcFviDxeLib_LIB_LINKS =\
            $(EdkIIGlueUefiBootServicesTableLib_LIB)\
            $(EdkIIGlueDxeServicesTableLib_LIB)\
            $(EdkIIGlueDxeMemoryAllocationLib_LIB)\
            $(EDKFRAMEWORKPROTOCOLLIB)\
    
RcFviDxeLibBin:
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\RcFviDxeLib.mak all \
            "MY_INCLUDES=$(RcFviDxeLib_INCLUDES)" \
            TYPE=LIBRARY \
            LIBRARY_NAME=$(RcFviDxeLib_LIB)

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
