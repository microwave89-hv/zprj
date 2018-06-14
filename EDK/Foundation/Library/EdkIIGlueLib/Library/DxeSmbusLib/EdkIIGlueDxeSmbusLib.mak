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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeSmbusLib/EdkIIGlueDxeSmbusLib.mak 1     1/20/12 3:55a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:55a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeSmbusLib/EdkIIGlueDxeSmbusLib.mak $
# 
# 1     1/20/12 3:55a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:17a Wesleychen
# Intel EDK initially releases.
# 
# 1     9/18/09 1:55a Iminglin
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueDxeSmbusLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueDxeSmbusLib_LIB) : EdkIIGlueDxeSmbusLib

EdkIIGlueDxeSmbusLib : $(BUILD_DIR)\EdkIIGlueDxeSmbusLib.mak EdkIIGlueDxeSmbusLibBin

$(BUILD_DIR)\EdkIIGlueDxeSmbusLib.mak : $(EdkIIGlueDxeSmbusLib_DIR)\$(@B).cif $(EdkIIGlueDxeSmbusLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueDxeSmbusLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)		

EdkIIGlueDxeSmbusLibBin : $(EdkIIGlueBaseMemoryLib_LIB) $(EdkIIGlueUefiBootServicesTableLib_LIB) $(EFIPROTOCOLLIB) $(EDKFRAMEWORKPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeSmbusLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeSmbusLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueDxeSmbusLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeSmbusLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeSmbusLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeSmbusLib_LIB)"
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