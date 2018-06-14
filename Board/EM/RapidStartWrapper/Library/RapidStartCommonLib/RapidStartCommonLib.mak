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
# $Header: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartCommonLib/RapidStartCommonLib.mak 1     10/15/12 4:40a Bensonlai $
#
# $Revision: 1 $
#
# $Date: 10/15/12 4:40a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/Intel Fast Flash Standby/iRST_SharkBay/RapidStartWrapper/RapidStartCommonLib/RapidStartCommonLib.mak $
# 
# 1     10/15/12 4:40a Bensonlai
# [TAG]  		None
# [Category]  	Improvement
# [Description]  	[Category] Improvement
# [Severity] Important
# [Description] Rename all IFFS sting to Rapid Start.
# [Files] Board\EM\RapidStartWrapper\*.*, ReferenceCode\RapidStart\*.*
# [Files]  		RapidStartCommonLib.cif
# RapidStartCommonLib.sdl
# RapidStartCommonLib.mak
# RapidStartCommonLib.c
# RapidStartCommonLib.h
# RapidStartCommonLib.inf
#
#**********************************************************************
#<AMI_FHDR_START>
#
# Name: RapidStartCommonLib.mak
#
# Description: Component description file for the RapidStart Common code PEIM/SMM/DXE library.
#
#<AMI_FHDR_END>
#**********************************************************************

all : RapidStartCommonSmmLib RapidStartCommonDxeLib RapidStartCommonPeiLib

$(RapidStartCommonSmmLib_LIB) : RapidStartCommonSmmLib
$(RapidStartCommonDxeLib_LIB) : RapidStartCommonDxeLib
$(RapidStartCommonPeiLib_LIB) : RapidStartCommonPeiLib

RapidStartCommonSmmLib : $(BUILD_DIR)\RapidStartCommonLib.mak RapidStartCommonSmmLibBin
RapidStartCommonDxeLib : $(BUILD_DIR)\RapidStartCommonLib.mak RapidStartCommonDxeLibBin
RapidStartCommonPeiLib : $(BUILD_DIR)\RapidStartCommonLib.mak RapidStartCommonPeiLibBin

$(BUILD_DIR)\RapidStartCommonLib.mak : $(RapidStartCommonLib_DIR)\$(@B).cif $(RapidStartCommonLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(RapidStartCommonLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

RapidStartCommonSmmLibBin : $(PchPlatformLib)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\RapidStartCommonLib.mak all\
	"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(NB_INCLUDES) $(INTEL_PCH_INCLUDES) $(RAPIDSTART_INCLUDES)" \
	TYPE=LIBRARY \
	LIBRARIES=\
        LIBRARY_NAME=$(RapidStartCommonSmmLib_LIB)

RapidStartCommonDxeLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
	/f $(BUILD_DIR)\RapidStartCommonLib.mak all\
	"MY_INCLUDES=$(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(NB_INCLUDES) $(INTEL_PCH_INCLUDES) $(RAPIDSTART_INCLUDES)" \
	TYPE=LIBRARY \
	LIBRARIES=\
        LIBRARY_NAME=$(RapidStartCommonDxeLib_LIB)

RapidStartCommonPeiLibBin :
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS) BUILD_DIR=$(BUILD_DIR)\IA32\
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
!ENDIF
	/f $(BUILD_DIR)\RapidStartCommonLib.mak all\
	"MY_INCLUDES=/I$(BUILD_DIR) $(EDK_INCLUDES) $(EdkIIGlueLib_INCLUDES) $(NB_INCLUDES) $(INTEL_PCH_INCLUDES) $(RAPIDSTART_INCLUDES)" \
	TYPE=PEI_LIBRARY \
	LIBRARIES=\
        LIBRARY_NAME=$(RapidStartCommonPeiLib_LIB)

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
