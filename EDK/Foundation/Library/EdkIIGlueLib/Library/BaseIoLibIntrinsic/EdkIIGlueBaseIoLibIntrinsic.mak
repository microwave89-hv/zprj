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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseIoLibIntrinsic/EdkIIGlueBaseIoLibIntrinsic.mak 1     1/20/12 3:48a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:48a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseIoLibIntrinsic/EdkIIGlueBaseIoLibIntrinsic.mak $
# 
# 1     1/20/12 3:48a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     1/20/12 3:27a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:10a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:50a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBaseIoLibIntrinsic.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


EDKIIGLUEBASEIOLIBINTRINSIC_OBJECTS=

!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
EDKIIGLUEBASEIOLIBINTRINSIC_OBJECTS=$(EDKIIGLUEBASEIOLIBINTRINSIC_OBJECTS)\
$$(BUILD_DIR)\$(EdkIIGlueBaseIoLibIntrinsic_DIR)\IoLib.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseIoLibIntrinsic_DIR)\IoLibMsc.obj\
$$(BUILD_DIR)\$(EdkIIGlueBaseIoLibIntrinsic_DIR)\IoHighLevel.obj
!ENDIF

$(EdkIIGlueBaseIoLibIntrinsic_LIB) : EdkIIGlueBaseIoLibIntrinsic

EdkIIGlueBaseIoLibIntrinsic : $(BUILD_DIR)\EdkIIGlueBaseIoLibIntrinsic.mak EdkIIGlueBaseIoLibIntrinsicBin

$(BUILD_DIR)\EdkIIGlueBaseIoLibIntrinsic.mak : $(EdkIIGlueBaseIoLibIntrinsic_DIR)\$(@B).cif $(EdkIIGlueBaseIoLibIntrinsic_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBaseIoLibIntrinsic_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
		
EdkIIGlueBaseIoLibIntrinsicBin : $(EdkIIGlueBaseLib_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseIoLibIntrinsic.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseIoLibIntrinsic_LIB)"\
		"OBJECTS=$(EDKIIGLUEBASEIOLIBINTRINSIC_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseIoLibIntrinsic.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseIoLibIntrinsic_LIB)"\
		"OBJECTS=$(EDKIIGLUEBASEIOLIBINTRINSIC_OBJECTS)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseIoLibIntrinsic.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseIoLibIntrinsic_LIB)"\
		"OBJECTS=$(EDKIIGLUEBASEIOLIBINTRINSIC_OBJECTS)"
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
