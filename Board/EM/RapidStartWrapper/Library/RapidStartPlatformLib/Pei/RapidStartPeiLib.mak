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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartPeiLib/RapidStartPeiLib.mak 1     10/15/12 4:41a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 10/15/12 4:41a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartPeiLib/RapidStartPeiLib.mak $
# 
# 1     10/15/12 4:41a Bensonlai
# [TAG]  		EIPNone
# [Category]  	Improvement
# [Description]  	[Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# [Files]  		RapidStartPeiLib.cif
# RapidStartPeiLib.sdl
# RapidStartPeiLib.mak
# RapidStartPeiLib.c
# RapidStartPeiLib.h
# RapidStartPeiLib.inf
# RapidStartPeiLib.lib
# PeiCryptLib.lib
# OpensslLib.lib
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: RapidStartPeiLib.mak
#
# Description: Component description file for the RapidStart Peim library
#
#<AMI_FHDR_END>
#**********************************************************************

all : RapidStartPeiLib

$(RapidStartPeiLib_LIB) : RapidStartPeiLib

RapidStartPeiLib : $(BUILD_DIR)\RapidStartPeiLib.mak RapidStartPeiLibBin

$(BUILD_DIR)\RapidStartPeiLib.mak : $(RapidStartPeiLib_DIR)\$(@B).cif $(RapidStartPeiLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RapidStartPeiLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartPeiLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\RapidStartPeiLib.mak all\
	"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(NB_INCLUDES) $(INTEL_MCH_INCLUDES) $(INTEL_PCH_INCLUDES) $(RAPIDSTART_INCLUDES)" \
	TYPE=PEI_LIBRARY \
        LIBRARY_NAME=$(RapidStartPeiLib_LIB)
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
