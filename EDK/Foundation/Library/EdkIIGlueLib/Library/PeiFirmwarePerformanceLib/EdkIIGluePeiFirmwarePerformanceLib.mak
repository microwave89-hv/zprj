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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiFirmwarePerformanceLib/EdkIIGluePeiFirmwarePerformanceLib.mak 1     1/20/12 3:58a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:58a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGluePeiFirmwarePerformanceLib/EdkIIGluePeiFirmwarePerformanceLib.mak $
# 
# 1     1/20/12 3:58a Jeffch
# Create Intel EDK 1117 Patch 7.
# 
# 1     11/17/11 9:31p Wesleychen
# EdkIIGluePeiFirmwarePerformanceLib
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGluePeiFirmwarePerformanceLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EdkIIGluePeiFirmwarePerformanceLib_LIB) : EdkIIGluePeiFirmwarePerformanceLib

EdkIIGluePeiFirmwarePerformanceLib : $(BUILD_DIR)\EdkIIGluePeiFirmwarePerformanceLib.mak EdkIIGluePeiFirmwarePerformanceLibBin

$(BUILD_DIR)\EdkIIGluePeiFirmwarePerformanceLib.mak : $(EdkIIGluePeiFirmwarePerformanceLib_DIR)\$(@B).cif $(EdkIIGluePeiFirmwarePerformanceLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGluePeiFirmwarePerformanceLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
	
EdkIIGluePeiFirmwarePerformanceLibBin : $(CPUIA32LIB)

EdkIIGluePeiFirmwarePerformanceLibBin : $(EdkIIGlueBaseTimerLibLocalApic_LIB) $(EdkIIGlueBaseTimerLibTsc_LIB) $(EdkIIGluePeiHobLib_LIB) $(EDKGUIDLIB) $(ARCHPROTOCOLLIB)
!IF "$(x64_BUILD)"=="1"
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\IA32\
		/f $(BUILD_DIR)\EdkIIGluePeiFirmwarePerformanceLib.mak all\
		TYPE=PEI_LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiFirmwarePerformanceLib_LIB)"
!ELSE
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGluePeiFirmwarePerformanceLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGluePeiFirmwarePerformanceLib_LIB)"
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
