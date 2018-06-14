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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartGuidLib/RapidStartGuidLib.mak 3     10/15/12 5:40a Bensonlai $
#
# $Revision: 3 $
#
# $Date: 10/15/12 5:40a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartGuidLib/RapidStartGuidLib.mak $
# 
# 3     10/15/12 5:40a Bensonlai
# [Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# 
# 2     9/26/12 3:31a Yurenlai
# [TAG]           None
# [Category]      Improvement
# [Severity]      Important
# [Description]   Update Intel Rapid Start Technology Framework Reference
# Code Beta Version 0.7.0.
# [Description]   ReferenceCode\RapidStart\*.*, RapidStartPeiLib.h
# 
# 1     4/19/12 8:04a Yurenlai
# Initial check in.
#
#*************************************************************************
all : RapidStartGuidLib

$(RapidStartGuidLib_LIB) : RapidStartGuidLib

RapidStartGuidLib : $(BUILD_DIR)\RapidStartGuidLib.mak RapidStartGuidLibBin

$(BUILD_DIR)\RapidStartGuidLib.mak : $(RapidStartGuidLib_DIR)\$(@B).cif $(RapidStartGuidLib_DIR)\$(@B).mak $(BUILD_RULES)
  $(CIF2MAK) $(RapidStartGuidLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartGuidLib_INCLUDES =\
            $(EDK_INCLUDES)\
            $(INTEL_PCH_INCLUDES)\
            $(EdkIIGlueLib_INCLUDES)\
            $(RAPIDSTART_INCLUDES)\

RapidStartGuidLibBin : 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
            /f $(BUILD_DIR)\RapidStartGuidLib.mak all\
            "MY_INCLUDES=$(RapidStartGuidLib_INCLUDES)" \
            TYPE=LIBRARY
!IF "$(x64_BUILD)"=="1" 
            $(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
            /f $(BUILD_DIR)\RapidStartGuidLib.mak all\
            "MY_INCLUDES=$(RapidStartGuidLib_INCLUDES)" \
            TYPE=PEI_LIBRARY
!ENDIF
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
