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
#<AMI_FHDR_START>
#
# Name: CppcGuidLib.mak
#
# Description: Make file to build Intel CPPC GuidLib components
#
#<AMI_FHDR_END>
#*************************************************************************
all : CppcGuidLib

$(CppcGuidLib_LIB) : CppcGuidLib

CppcGuidLib : $(BUILD_DIR)\CppcGuidLib.mak CppcGuidLibBin

$(BUILD_DIR)\CppcGuidLib.mak : $(INTEL_CPPC_GUIDLIB_DIR)\$(@B).cif $(INTEL_CPPC_GUIDLIB_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(INTEL_CPPC_GUIDLIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

CppcGuidLib_INCLUDES=\
	$(EDK_INCLUDES)\
	$(EdkIIGlueLib_INCLUDES)

CppcGuidLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\CppcGuidLib.mak all\
		"MY_INCLUDES=$(CppcGuidLib_INCLUDES)" \
		TYPE=LIBRARY

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