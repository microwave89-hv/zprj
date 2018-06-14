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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseCacheMaintenanceLib/EdkIIGlueBaseCacheMaintenanceLib.mak 1     1/20/12 3:48a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:48a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBaseCacheMaintenanceLib/EdkIIGlueBaseCacheMaintenanceLib.mak $
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
# 1     9/18/09 1:49a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBaseCacheMaintenanceLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
EdkIIGlueBaseCacheMaintenanceLib_OBJECTS=\
$$(BUILD_DIR)\$(EdkIIGlueBaseCacheMaintenanceLib_DIR)\x86Cache.obj
!ENDIF

$(EdkIIGlueBaseCacheMaintenanceLib_LIB) : EdkIIGlueBaseCacheMaintenanceLib

EdkIIGlueBaseCacheMaintenanceLib : $(BUILD_DIR)\EdkIIGlueBaseCacheMaintenanceLib.mak EdkIIGlueBaseCacheMaintenanceLibBin

$(BUILD_DIR)\EdkIIGlueBaseCacheMaintenanceLib.mak : $(EdkIIGlueBaseCacheMaintenanceLib_DIR)\$(@B).cif $(EdkIIGlueBaseCacheMaintenanceLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBaseCacheMaintenanceLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueBaseCacheMaintenanceLibBin : $(EdkIIGlueBaseLib_LIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseCacheMaintenanceLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseCacheMaintenanceLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBaseCacheMaintenanceLib_OBJECTS)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBaseCacheMaintenanceLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseCacheMaintenanceLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBaseCacheMaintenanceLib_OBJECTS)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBaseCacheMaintenanceLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBaseCacheMaintenanceLib_LIB)"\
		"OBJECTS=$(EdkIIGlueBaseCacheMaintenanceLib_OBJECTS)"
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
