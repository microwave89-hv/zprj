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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxeLib/RapidStartDxeLib.mak 1     10/15/12 4:41a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 10/15/12 4:41a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartDxeLib/RapidStartDxeLib.mak $
# 
# 1     10/15/12 4:41a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	[Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# 
# [Files]  		RapidStartDxeLib.cif
# RapidStartDxeLib.sdl
# RapidStartDxeLib.mak
# RapidStartDxeLib.c
# RapidStartDxeLib.h
# RapidStartDxeLib.inf
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: RapidStartDxeLib.mak
#
# Description: Component description file for the RapidStartDxeLib.
#
#<AMI_FHDR_END>
#**********************************************************************

all : RapidStartDxeLib

$(RapidStartDxeLib_LIB) : RapidStartDxeLib

RapidStartDxeLib : $(BUILD_DIR)\RapidStartDxeLib.mak RapidStartDxeLibBin

$(BUILD_DIR)\RapidStartDxeLib.mak : $(RapidStartDxeLib_DIR)\$(@B).cif $(RapidStartDxeLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RapidStartDxeLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartDxeLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\RapidStartDxeLib.mak all\
	"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(INTEL_MCH_INCLUDES) $(INTEL_PCH_INCLUDES) $(RAPIDSTART_INCLUDES)" \
	TYPE=LIBRARY \
        LIBRARY_NAME=$(RapidStartDxeLib_LIB)
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
