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
# $Header: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeFirmwarePerformanceLib/EdkIIGlueDxeFirmwarePerformanceLib.mak 1     1/20/12 3:59a Jeffch $
#
# $Revision: 1 $
#
# $Date: 1/20/12 3:59a $
#**********************************************************************
# Revision History
# ----------------
# $Log: /Alaska/SOURCE/Modules/SharkBayRefCodes/IntelEDK/EdkIIGlue/EdkIIGlueDxeFirmwarePerformanceLib/EdkIIGlueDxeFirmwarePerformanceLib.mak $
# 
# 1     1/20/12 3:59a Jeffch
# 
# 1     11/17/11 9:32p Wesleychen
# Add firmware performance support from Intel EDK117 Client Framework
# PatchV7 package.
# 
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	EdkIIGlueDxeFirmwarePerformanceLib.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************
$(EdkIIGlueDxeFirmwarePerformanceLib_LIB) : EdkIIGlueDxeFirmwarePerformanceLib

EdkIIGlueDxeFirmwarePerformanceLib : $(BUILD_DIR)\EdkIIGlueDxeFirmwarePerformanceLib.mak EdkIIGlueDxeFirmwarePerformanceLibBin

$(BUILD_DIR)\EdkIIGlueDxeFirmwarePerformanceLib.mak : $(EdkIIGlueDxeFirmwarePerformanceLib_DIR)\$(@B).cif $(EdkIIGlueDxeFirmwarePerformanceLib_DIR)\$(@B).mak $(BUILD_RULES)
	$(CIF2MAK) $(EdkIIGlueDxeFirmwarePerformanceLib_DIR)\$(@B).cif $(CIF2MAK_DEFAULTS)
	
EdkIIGlueDxeFirmwarePerformanceLibBin : $(CPUIA32LIB)

EdkIIGlueDxeFirmwarePerformanceLibBin : $(EdkIIGlueUefiDevicePathLib_LIB) $(EdkIIGlueBasePeCoffGetEntryPointLib_LIB) $(EdkIIGlueBaseTimerLibLocalApic_LIB) $(EdkIIGlueUefiLib_LIB) $(EdkIIGlueBaseTimerLibTsc_LIB) $(EDKGUIDLIB) $(ARCHPROTOCOLLIB)
	$(MAKE) /$(MAKEFLAGS) $(EDKIIGLUE_DEFAULTS)\
		BUILD_DIR=$(BUILD_DIR)\
		/f $(BUILD_DIR)\EdkIIGlueDxeFirmwarePerformanceLib.mak all\
		TYPE=LIBRARY "PARAMETERS=LIBRARY_NAME=$$(EdkIIGlueDxeFirmwarePerformanceLib_LIB)"

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
