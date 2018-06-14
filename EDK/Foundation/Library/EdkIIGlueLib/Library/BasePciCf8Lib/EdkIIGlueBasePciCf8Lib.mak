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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePciCf8Lib/EdkIIGlueBasePciCf8Lib.mak 1     1/20/12 3:53a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:53a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueBasePciCf8Lib/EdkIIGlueBasePciCf8Lib.mak $
# 
# 1     1/20/12 3:53a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:15a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:51a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueBasePciCf8Lib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueBasePciCf8Lib_LIB) : EdkIIGlueBasePciCf8Lib

EdkIIGlueBasePciCf8Lib : $(BUILD_DIR)\EdkIIGlueBasePciCf8Lib.mak EdkIIGlueBasePciCf8LibBin

$(BUILD_DIR)\EdkIIGlueBasePciCf8Lib.mak : $(EdkIIGlueBasePciCf8Lib_DIR)\$(@B).cif $(EdkIIGlueBasePciCf8Lib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueBasePciCf8Lib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)

EdkIIGlueBasePciCf8Lib_LIB_LINKS=\
!IF "$(PROCESSOR)"=="IA32" || "$(PROCESSOR)"=="x64"
$(EdkIIGlueBaseIoLibIntrinsic_LIB)
!ENDIF	

EdkIIGlueBasePciCf8LibBin : $(EdkIIGlueBasePciCf8Lib_LIB_LINKS)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePciCf8Lib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePciCf8Lib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueBasePciCf8Lib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePciCf8Lib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueBasePciCf8Lib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueBasePciCf8Lib_LIB)"
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
