#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseDebugLibNull/EdkIIGlueBaseDebugLibNull.mak 1     1/20/12 3:48a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:48a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseDebugLibNull/EdkIIGlueBaseDebugLibNull.mak $
# 
# 1     1/20/12 3:48a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     1/20/12 3:27a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:09a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:50a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBaseDebugLibNull.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueBaseDebugLibNull_LIB) : EdkIIGlueBaseDebugLibNull

EdkIIGlueBaseDebugLibNull : $(BUILD_DIR)\EdkIIGlueBaseDebugLibNull.mak EdkIIGlueBaseDebugLibNullBin

$(BUILD_DIR)\EdkIIGlueBaseDebugLibNull.mak : $(EdkIIGlueBaseDebugLibNull_DIR)\$(@B).cif $(EdkIIGlueBaseDebugLibNull_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBaseDebugLibNull_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueBaseDebugLibNullBin : $(EdkIIGlueBaseLib_LIB) $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGlueBasePrintLib_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseDebugLibNull.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseDebugLibNull_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseDebugLibNull.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseDebugLibNull_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseDebugLibNull.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseDebugLibNull_LIB)"
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2009, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
