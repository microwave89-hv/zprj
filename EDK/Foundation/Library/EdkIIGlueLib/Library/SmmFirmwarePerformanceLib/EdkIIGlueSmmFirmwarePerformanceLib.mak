#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueSmmFirmwarePerformanceLib/EdkIIGlueSmmFirmwarePerformanceLib.mak 1     1/20/12 3:59a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueSmmFirmwarePerformanceLib/EdkIIGlueSmmFirmwarePerformanceLib.mak $
# 
# 1     1/20/12 3:59a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     9/27/11 6:22a Wesleychen
# Intel EDK initially releases.
# 
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueSmmFirmwarePerformanceLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************


$(EdkIIGlueSmmFirmwarePerformanceLib_LIB) : EdkIIGlueSmmFirmwarePerformanceLib

EdkIIGlueSmmFirmwarePerformanceLib : $(BUILD_DIR)\EdkIIGlueSmmFirmwarePerformanceLib.mak EdkIIGlueSmmFirmwarePerformanceLibBin

$(BUILD_DIR)\EdkIIGlueSmmFirmwarePerformanceLib.mak : $(EdkIIGlueSmmFirmwarePerformanceLib_DIR)\$(@B).cif $(EdkIIGlueSmmFirmwarePerformanceLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueSmmFirmwarePerformanceLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
	
EdkIIGlueSmmFirmwarePerformanceLibBin : $(EdkIIGlueBaseTimerLibLocalApic_LIB) $(EdkIIGlueUefiLib_LIB) $(EdkIIGlueBaseTimerLibTsc_LIB) $(EDKGUIDLIB) $(ARCHPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueSmmFirmwarePerformanceLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueSmmFirmwarePerformanceLib_LIB)"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGlueSmmFirmwarePerformanceLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueSmmFirmwarePerformanceLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueSmmFirmwarePerformanceLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueSmmFirmwarePerformanceLib_LIB)"
!ENDIF
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2011, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************