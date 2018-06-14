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

# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/DPTF/DptfGuidLib/DptfGuidLib.mak 1     4/24/12 9:27a Victortu $
#
# $Revision: 1 $
#
# $Date: 4/24/12 9:27a $
#*************************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/DPTF/DptfGuidLib/DptfGuidLib.mak $
# 
# 1     4/24/12 9:27a Victortu
#
#*************************************************************************
#<AMI_FHDR_START>
#
# Name: DptfGuidLib.mak
#
# Description: MAke file to build Intel DPTF GuidLib components
#
#<AMI_FHDR_END>
#*************************************************************************
all : DptfGuidLib

$(DptfGuidLib_LIB) : DptfGuidLib

DptfGuidLib : $(BUILD_DIR)\DptfGuidLib.mak DptfGuidLibBin

$(BUILD_DIR)\DptfGuidLib.mak : $(INTEL_DPTF_GUIDLIB_DIR)\$(@B).cif $(INTEL_DPTF_GUIDLIB_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(INTEL_DPTF_GUIDLIB_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

DptfGuidLib_INCLUDES=\
	$(EDK_INCLUDES)\
	$(EdkIIGlueLib_INCLUDES)

DptfGuidLibBin :
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		/f $(BUILD_DIR)\DptfGuidLib.mak all\
		"MY_INCLUDES=$(DptfGuidLib_INCLUDES)" \
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